#include "../includes/Codegen.h"
#include <map>
// set the module name ot translation_unit
//  to set the cpu architecture prefered to use setTargetTriple
Codegen::Codegen(
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree,
    std::string_view sourcePath)
    : resolvedTree(std::move(resolvedTree)),
      builder(context),
      module("<translation_unit", context)
{
    module.setSourceFileName(sourcePath);
    module.setTargetTriple(llvm::sys::getDefaultTargetTriple());
}

// we need to make all the functions available to other functions so the resolution happens in 2 passes
//  first makes the function available and next we resolve the bodies
llvm::Module *Codegen::generateIR()
{
    for (auto &&function : resolvedTree)
        generateFunctionDecl(*function);

    for (auto &&function : resolvedTree)
        generateFunctionBody(*function);

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

    // we create a map to reference the IR
    std::map<const ResolvedDecl *, llvm::Value *> declarations;

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

        ++idx;
    }

    // now the block is generated
    generateBlock(*functionDecl.body);

    // remove the stack pointer after the body generation
    allocaInsertPoint->eraseFromParent();
    allocaInsertPoint = nullptr;
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

llvm::Value Codegen::generateStatement(const ResolvedStatement &stmt)
{
    if (auto *expr = dynamic_cast<const ResolvedExpression *>(&stmt))
    {
        return generateExpression(*expr);
    }

    if (auto *returnStmt = dynamic_cast<const ResolvedReturnStmt *>(&stmt))
    {
        return generateResolvedReturnStmt(*returnStmt);
    }

    llvm_unreachable("unknown statement");
}    