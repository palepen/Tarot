#include "libtarot/Codegen.h"
#include "llvm/TargetParser/Host.h"
#include <map>
#include <iostream>
// set the module name ot translation_unit
//  to set the cpu architecture prefered to use setTargetTriple
Codegen::Codegen(
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> &resolvedTree,
    std::string_view sourcePath)
    : resolvedTree(std::move(resolvedTree)),
      builder(context),
      module("<translation_unit>", context)
{
    module.setSourceFileName(sourcePath);
    module.setTargetTriple(llvm::sys::getDefaultTargetTriple());
    allocaInsertPoint = nullptr;
}

// we need to make all the functions available to other functions so the resolution happens in 2 passes
//  first makes the function available and next we resolve the bodies
llvm::Module *Codegen::generateIR()
{
    for (auto &&function : resolvedTree)
    {
        generateFunctionDecl(*function);
    }

    for (auto &&function : resolvedTree)
    {
        generateFunctionBody(*function);
    }

    generateMainWrapper();

    return &module;
}

// gets type
llvm::Type *Codegen::generateType(Type type)
{
    if (type.kind == Type::Kind::Number)
        return builder.getDoubleTy();
    return builder.getVoidTy();
}

// args : function Declaration
void Codegen::generateFunctionDecl(const ResolvedFunctionDecl &functionDecl)
{
    auto *retType = generateType(functionDecl.type);

    std::vector<llvm::Type *> paramTypes;

    for (auto &&param : functionDecl.params)
    {
        paramTypes.emplace_back(generateType(param->type));
    }

    // the false representss the function is not variadic
    auto *type = llvm::FunctionType::get(retType, paramTypes, false);

    // creates a new function and binds it in module
    // External Linkage here means that the functions are visible outside the module
    llvm::Function::Create(type, llvm::Function::ExternalLinkage, functionDecl.identifier, module);
}

// In LLVM IR a set of instructions that execute together is placed inside a basic block
void Codegen::generateFunctionBody(const ResolvedFunctionDecl &functionDecl)
{

    // gets the functions name
    auto *function = module.getFunction(functionDecl.identifier);

    //  The basic block representing the body of the function is called entry
    // The idea is to insert a placeholder instruction at the beginning of the entry block and always insert the stack variables before this placeholder.
    auto *entryBB = llvm::BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(entryBB);
    // undef = placeholder
    llvm::Value *undef = llvm::UndefValue::get(builder.getInt32Ty());
    allocaInsertPoint = new llvm::BitCastInst(undef, undef->getType(), "alloca.placeholder", entryBB);
    // now we have created a block or stack where every instruction from now on in this block will stored in this stack
    // this stack is called insert point

    bool isVoid = functionDecl.type.kind == Type::Kind::Void;

    if (!isVoid)
    {
        retVal = allocateStackVariable(function, "retval");
        if (!retVal)
        {
            llvm_unreachable("Failed to allocate return value");
        }
    }
    retBB = llvm::BasicBlock::Create(context, "return", function);
    // set the args of a function
    int idx = 0;
    for (auto &&arg : function->args())
    {
        // we get the name
        const auto *paramDecl = functionDecl.params[idx].get();
        arg.setName(paramDecl->identifier);

        // we set value in stack

        llvm::Value *var = allocateStackVariable(function, paramDecl->identifier);
        builder.CreateStore(&arg, var);

        declarations[paramDecl] = var;

        ++idx;
    }

    // if (retBB->hasNPredecessorsOrMore(1))
    // {
    //     builder.CreateBr(retBB);
    //     retBB->insertInto(function);
    //     builder.SetInsertPoint(retBB);
    // }
    // now the block is generated

    if (functionDecl.identifier == "println")
        generateBuiltinPrintBody(functionDecl);
    else
        generateBlock(*functionDecl.body);

    // remove the stack pointer after the body generation
    allocaInsertPoint->eraseFromParent();
    allocaInsertPoint = nullptr;

    llvm::BasicBlock *currentBB = builder.GetInsertBlock();
    if (currentBB && !currentBB->getTerminator())
    {
        if (!isVoid && retBB)
        {
            builder.CreateBr(retBB);
        }
        else
        {
            builder.CreateRetVoid();
        }
    }

    // Emit the return block even if it’s empty — insert ret void
    if (isVoid && retBB)
    {
        builder.SetInsertPoint(retBB);
        if (!retBB->getTerminator())
        {
            builder.CreateRetVoid();
        }
    }
    else if (!isVoid && retBB && !retBB->getTerminator())
    {
        builder.SetInsertPoint(retBB);
        builder.CreateRet(builder.CreateLoad(builder.getDoubleTy(), retVal));
    }

    // Cleanup
    retVal = nullptr;
    retBB = nullptr;
    allocaInsertPoint = nullptr;
    declarations.clear();
    // builder.CreateRet(builder.CreateLoad(builder.getDoubleTy(), retVal));
}

llvm::AllocaInst *Codegen::allocateStackVariable(llvm::Function *function, const std::string_view identifier)
{
    llvm::IRBuilder<> tmpBuilder(context);
    tmpBuilder.SetInsertPoint(allocaInsertPoint);

    return tmpBuilder.CreateAlloca(tmpBuilder.getDoubleTy(), nullptr, identifier);
}

void Codegen::generateBlock(const ResolvedBlock &block)
{
    for (auto &&stmt : block.statements)
    {
        generateStatement(*stmt);

        if (dynamic_cast<const ResolvedReturnStmt *>(stmt.get()))
        {
            builder.ClearInsertionPoint();
            break;
        }
    }
}

llvm::Value *Codegen::generateStatement(const ResolvedStatement &stmt)
{
    if (auto *expr = dynamic_cast<const ResolvedExpression *>(&stmt))
    {
        return generateExpression(*expr);
    }

    if (auto *returnStmt = dynamic_cast<const ResolvedReturnStmt *>(&stmt))
    {
        return generateReturnStatement(*returnStmt);
    }

    if (auto *ifStmt = dynamic_cast<const ResolvedIfStatement *>(&stmt))
    {
        return generateIfStatement(*ifStmt);
    }

    if (auto *whileStmt = dynamic_cast<const ResolvedWhileStatement *>(&stmt))
    {
        return generateWhileStatement(*whileStmt);
    }

    llvm_unreachable("unknown statement");
}

llvm::Value *Codegen::generateReturnStatement(const ResolvedReturnStmt &stmt)
{
    if (stmt.expr)
        builder.CreateStore(generateExpression(*stmt.expr), retVal);

    return builder.CreateBr(retBB);
}

llvm::Value *Codegen::generateExpression(const ResolvedExpression &expr)
{
    if (auto val = expr.getConstantValue())
        return llvm::ConstantFP::get(builder.getDoubleTy(), *val);
    if (auto *number = dynamic_cast<const ResolvedNumberLiteral *>(&expr))
        return llvm::ConstantFP::get(builder.getDoubleTy(), number->value);

    if (auto *dre = dynamic_cast<const ResolvedDeclarationRefExpr *>(&expr))
        return builder.CreateLoad(builder.getDoubleTy(), declarations[dre->decl]);

    if (auto *call = dynamic_cast<const ResolvedCallExpr *>(&expr))
        return generateCallExpr(*call);

    if (auto *binOp = dynamic_cast<const ResolvedBinaryOperator *>(&expr))
        return generateBinaryOperator(*binOp);

    if (auto *unary = dynamic_cast<const ResolvedUnaryOperator *>(&expr))
        return generateUnaryOperator(*unary);

    if (auto *grouping = dynamic_cast<const ResolvedGroupingExpression *>(&expr))
        return generateExpression(*grouping->expr);

    llvm_unreachable("unexpected Expression");
}

llvm::Value *Codegen::generateCallExpr(const ResolvedCallExpr &call)
{
    llvm::Function *callee = module.getFunction(call.callee->identifier);

    std::vector<llvm::Value *> args;

    for (auto &&arg : call.arguments)
    {
        args.emplace_back(generateExpression(*arg));
    }

    return builder.CreateCall(callee, args);
}

void Codegen::generateBuiltinPrintBody(const ResolvedFunctionDecl &println)
{
    auto *type = llvm::FunctionType::get(builder.getInt32Ty(), {llvm::PointerType::get(builder.getInt8Ty(), 0)}, true);
    auto *printf = llvm::Function::Create(type, llvm::Function::ExternalLinkage, "printf", module);
    auto *format = builder.CreateGlobalString("%.15g\n");

    llvm::Value *param = builder.CreateLoad(builder.getDoubleTy(), declarations[println.params[0].get()]);
    builder.CreateCall(printf, {format, param});
}

void Codegen::generateMainWrapper()
{
    auto *builtinMain = module.getFunction("main");
    builtinMain->setName("__builtin_main");

    auto *main = llvm::Function::Create(llvm::FunctionType::get(builder.getInt32Ty(), {}, false), llvm::Function::ExternalLinkage, "main", module);

    auto *entry = llvm::BasicBlock::Create(context, "entry", main);
    builder.SetInsertPoint(entry);

    builder.CreateCall(builtinMain);
    builder.CreateRet(llvm::ConstantInt::getSigned(builder.getInt32Ty(), 0));
}

llvm::Value *Codegen::generateUnaryOperator(const ResolvedUnaryOperator &unary)
{
    llvm::Value *rhs = generateExpression(*unary.operand);

    if (unary.op == TokenType::MINUS)
        return builder.CreateFNeg(rhs);

    if (unary.op == TokenType::EXCL)
        return boolToDouble(builder.CreateNot(doubleToBool(rhs)));

    llvm_unreachable("unknown unary operator");
    return nullptr;
}

llvm::Value *Codegen::generateBinaryOperator(const ResolvedBinaryOperator &binOp)
{
    TokenType op = binOp.op;

    if (op == TokenType::AMPAMP || op == TokenType::PIPEPIPE)
    {
        llvm::Function *function = getCurrentFunction();
        bool isOr = op == TokenType::PIPEPIPE;

        auto *rhsTag = isOr ? "or.rhs" : "and.rhs";
        auto *mergeTag = isOr ? "or.merge" : "and.merge";

        auto *rhsBB = llvm::BasicBlock::Create(context, rhsTag, function);
        auto *mergeBB = llvm::BasicBlock::Create(context, mergeTag, function);

        llvm::BasicBlock *trueBB = isOr ? mergeBB : rhsBB;
        llvm::BasicBlock *falseBB = isOr ? rhsBB : mergeBB;

        generateConditionalOperator(*binOp.lhs, trueBB, falseBB);

        builder.SetInsertPoint(rhsBB);
        llvm::Value *rhs = doubleToBool(generateExpression(*binOp.rhs));
        builder.CreateBr(mergeBB);

        rhsBB = builder.GetInsertBlock();
        builder.SetInsertPoint(mergeBB);
        llvm::PHINode *phi = builder.CreatePHI(builder.getInt1Ty(), 2);

        for (auto it = pred_begin(mergeBB); it != pred_end(mergeBB); ++it)
        {
            if (*it == rhsBB)
                phi->addIncoming(rhs, rhsBB);
            else
                phi->addIncoming(builder.getInt1(isOr), *it);
        }

        return boolToDouble(phi);
    }

    llvm::Value *lhs = generateExpression(*binOp.lhs);
    llvm::Value *rhs = generateExpression(*binOp.rhs);


    switch (op)
    {
    case TokenType::PLUS:
        return builder.CreateFAdd(lhs, rhs);
    case TokenType::MINUS:
        return builder.CreateFSub(lhs, rhs);
    case TokenType::ASTERISK:
        return builder.CreateFMul(lhs, rhs);
    case TokenType::SLASH:
        return builder.CreateFDiv(lhs, rhs);
    case TokenType::LT:
        return boolToDouble(builder.CreateFCmpOLT(lhs, rhs));
    case TokenType::GT:
        return boolToDouble(builder.CreateFCmpOGT(lhs, rhs));
    case TokenType::EQUALEQUAL:
        return boolToDouble(builder.CreateFCmpOEQ(lhs, rhs));
    default:
        break;
    }

    llvm_unreachable("unexpected binary operator");
    return nullptr;
}

llvm::Value *Codegen::doubleToBool(llvm::Value *v)
{
    return builder.CreateFCmpONE(v, llvm::ConstantFP::get(builder.getDoubleTy(), 0.0), "to.bool");
}

llvm::Value *Codegen::boolToDouble(llvm::Value *v)
{
    return builder.CreateUIToFP(v, builder.getDoubleTy(), "to.double");
}

llvm::Function *Codegen::getCurrentFunction()
{
    return builder.GetInsertBlock()->getParent();
}

void Codegen::generateConditionalOperator(const ResolvedExpression &op, llvm::BasicBlock *trueBB, llvm::BasicBlock *falseBB)
{
    llvm::Function *function = getCurrentFunction();
    const auto *binop = dynamic_cast<const ResolvedBinaryOperator *>(&op);

    if (binop && binop->op == TokenType::PIPEPIPE)
    {
        llvm::BasicBlock *nextBB = llvm::BasicBlock::Create(context, "or.lhs.false", function);
        generateConditionalOperator(*binop->lhs, trueBB, nextBB);
        builder.SetInsertPoint(nextBB);
        generateConditionalOperator(*binop->rhs, trueBB, falseBB);

        return;
    }

    if (binop && binop->op == TokenType::AMPAMP)
    {
        llvm::BasicBlock *nextBB = llvm::BasicBlock::Create(context, "and.lhs.true", function);
        generateConditionalOperator(*binop->lhs, nextBB, falseBB);
        builder.SetInsertPoint(nextBB);
        generateConditionalOperator(*binop->rhs, trueBB, falseBB);
        return;
    }

    llvm::Value *val = doubleToBool(generateExpression(op));
    builder.CreateCondBr(val, trueBB, falseBB);
}

llvm::Value *Codegen::generateIfStatement(const ResolvedIfStatement &stmt)
{
    llvm::Function *function = getCurrentFunction();

    auto *trueBB = llvm::BasicBlock::Create(context, "if.true");
    auto *exitBB = llvm::BasicBlock::Create(context, "if.false");

    llvm::BasicBlock *elseBB = exitBB;

    if (stmt.falseBlock)
        elseBB = llvm::BasicBlock::Create(context, "if.false");

    llvm::Value *cond = generateExpression(*stmt.condition);

    builder.CreateCondBr(doubleToBool(cond), trueBB, elseBB);

    trueBB->insertInto(function);
    builder.SetInsertPoint(trueBB);
    generateBlock(*stmt.trueBlock);
    builder.CreateBr(exitBB);

    if (stmt.falseBlock)
    {
        elseBB->insertInto(function);
        builder.SetInsertPoint(elseBB);
        generateBlock(*stmt.falseBlock);
        builder.CreateBr(exitBB);
    }

    exitBB->insertInto(function);
    builder.SetInsertPoint(exitBB);
    return nullptr;
}

llvm::Value *Codegen::generateWhileStatement(const ResolvedWhileStatement &whileStmt)
{
    llvm::Function *function = getCurrentFunction();

    auto *header = llvm::BasicBlock::Create(context, "while.cond", function);
    auto *body = llvm::BasicBlock::Create(context, "while.body", function);
    auto *exit = llvm::BasicBlock::Create(context, "while.exit", function);

    builder.CreateBr(header);

    builder.SetInsertPoint(header);
    llvm::Value *cond = generateExpression(*whileStmt.condition);
    builder.CreateCondBr(doubleToBool(cond), body, exit);

    builder.SetInsertPoint(body);
    generateBlock(*whileStmt.body);
    builder.CreateBr(header);

    builder.SetInsertPoint(exit);
    return nullptr;
}
