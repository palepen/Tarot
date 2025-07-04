#include "libtarot/Sema.h"
#include "libtarot/ControlFlow.h"
#include <llvm/Support/ErrorHandling.h>
#include <map>

std::vector<std::unique_ptr<ResolvedFunctionDecl>> Sema::resolveAST()
{
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree;
    auto println = createBuiltinPrintln();
    ScopeRAII(this);

    insertDeclToCurrentScope(*resolvedTree.emplace_back(std::move(println)));

    bool error = false;
    for (auto &&fn : ast)
    {
        auto resolvedFunctionDecl = resolveFunctionDeclaration(*fn);

        if (!resolvedFunctionDecl || !insertDeclToCurrentScope(*resolvedFunctionDecl))
        {
            error = true;
            continue;
        }

        resolvedTree.emplace_back(std::move(resolvedFunctionDecl));
    }
    if (error)
        return {};

    for (size_t i = 1; i < resolvedTree.size(); ++i)
    {
        currentFunction = resolvedTree[i].get();

        ScopeRAII(this);
        for (auto &&param : currentFunction->params)
        {
            insertDeclToCurrentScope(*param);
        }

        auto resolvedBody = resolveBlock(*ast[i - 1]->body);
        if (!resolvedBody)
        {
            error = true;
            continue;
        }
        currentFunction->body = std::move(resolvedBody);
        error |= runFlowSensitiveChecks(*currentFunction);
    }

    if (bailOnError_ && error)
        return {};

    return resolvedTree;
}

bool Sema::checkReturnOnAllPaths(const ResolvedFunctionDecl &fn, const CFG &cfg)
{
    if (fn.type.kind == Type::Kind::Void)
        return false;

    int returnCount = 0;
    bool exitReached = false;

    std::set<int> visited;
    std::vector<int> worklist;
    worklist.emplace_back(cfg.entry);

    while (!worklist.empty())
    {
        int bb = worklist.back();
        worklist.pop_back();

        if (!visited.emplace(bb).second)
            continue;

        exitReached |= bb == cfg.exit;

        const auto &[preds, succs, stmts] = cfg.basicBlocks[bb];

        if (!stmts.empty() && dynamic_cast<const ResolvedReturnStmt *>(stmts[0]))
        {
            ++returnCount;
            continue;
        }

        for (auto &&[succ, reachable] : succs)
            if (reachable)
                worklist.emplace_back(succ);
    }

    if (exitReached || returnCount == 0)
    {
        report(fn.location,
               returnCount > 0
                   ? "non-void function doesn't return a value on every path"
                   : "non-void function doesn't return a value");
    }

    return exitReached || returnCount == 0;
}

bool Sema::runFlowSensitiveChecks(const ResolvedFunctionDecl &fn)
{
    CFG cfg = CFGBuilder().build(fn);
    bool error = false;
    error |= checkReturnOnAllPaths(fn, cfg);
    error |= checkVariableInitialization(fn, cfg);

    return error;
};

std::optional<Type> Sema::resolveType(Type parsedType)
{
    if (parsedType.kind == Type::Kind::Custom)
        return std::nullopt;
    return parsedType;
}

std::unique_ptr<ResolvedFunctionDecl> Sema::resolveFunctionDeclaration(const FunctionDecl &function)
{
    std::optional<Type> type = resolveType(function.type);

    if (!type)
        return report(function.location, "Function '" + function.identifier + "' has invalid '" + function.type.name + "' type");

    if (function.identifier == "main")
    {
        if (type->kind != Type::Kind::Void)
            return report(function.location, "main function is expected to have 'void' type");
        if (function.params.size())
            return report(function.location, "main function is expected to have no arguments");
    }

    std::vector<std::unique_ptr<ResolvedParamDecl>> resolvedParams;

    ScopeRAII paramScope(this);

    for (auto &&param : function.params)
    {
        auto resolvedParam = resolveParamDecl(*param);

        if (!resolvedParam || !insertDeclToCurrentScope(*resolvedParam))
            return nullptr;

        resolvedParams.emplace_back(std::move(resolvedParam));
    }

    return std::make_unique<ResolvedFunctionDecl>(function.location, function.identifier, *type, std::move(resolvedParams), nullptr);
}

std::unique_ptr<ResolvedParamDecl> Sema::resolveParamDecl(const ParameterDecl &param)
{
    std::optional<Type> type = resolveType(param.type);

    if (!type || type->kind == Type::Kind::Void)
    {
        return report(param.location, "parameter '" + param.identifier + "' has invalid '" + param.type.name + "' type");
    }

    return std::make_unique<ResolvedParamDecl>(param.location, param.identifier, *type);
}

std::unique_ptr<ResolvedBlock> Sema::resolveBlock(const Block &block)
{
    std::vector<std::unique_ptr<ResolvedStatement>> resolvedStatements;

    bool error = false;
    int reportUnreachableCount = 0;

    ScopeRAII blockScope(this);
    for (auto &&stmt : block.statements)
    {
        auto resolvedStatement = resolveStatement(*stmt);

        error |= !resolvedStatements.emplace_back(std::move(resolvedStatement));
        if (error)
            continue;
        if (reportUnreachableCount == 1)
        {
            report(stmt->location, "unreachable statement", true);
            ++reportUnreachableCount;
        }

        if (dynamic_cast<ReturnStatement *>(stmt.get()))
            ++reportUnreachableCount;
    }

    if (error)
        return nullptr;

    return std::make_unique<ResolvedBlock>(block.location, std::move(resolvedStatements));
}

std::unique_ptr<ResolvedStatement> Sema::resolveStatement(const Statement &stmt)
{

    if (auto *expr = dynamic_cast<const Expression *>(&stmt))
    {
        return resolveExpression(*expr);
    }

    if (auto *returnStmt = dynamic_cast<const ReturnStatement *>(&stmt))
    {
        return resolveReturnStatement(*returnStmt);
    }

    if (auto *ifStmt = dynamic_cast<const IfStatement *>(&stmt))
        return resolveIfStatement(*ifStmt);

    if (auto *whileStmt = dynamic_cast<const WhileStatement *>(&stmt))
        return resolveWhileStatement(*whileStmt);

    if (auto *declStmt = dynamic_cast<const DeclStatement *>(&stmt))
        return resolveDeclStatement(*declStmt);

    if (auto *assignment = dynamic_cast<const Assignment *>(&stmt))
        return resolveAssignment(*assignment);

    llvm_unreachable("unexpected Statement");
}

std::unique_ptr<ResolvedReturnStmt> Sema::resolveReturnStatement(const ReturnStatement &returnStmt)
{
    if (currentFunction->type.kind == Type::Kind::Void && returnStmt.expr)
        return report(returnStmt.location, "Unexpected return value in void function");

    if (currentFunction->type.kind != Type::Kind::Void && !returnStmt.expr)
        return report(returnStmt.location, "expected a return value");

    std::unique_ptr<ResolvedExpression> resolvedExpr;
    if (returnStmt.expr)
    {
        resolvedExpr = resolveExpression(*returnStmt.expr);
        if (!resolvedExpr)
            return nullptr;

        if (currentFunction->type.kind != resolvedExpr->type.kind)
            return report(resolvedExpr->location, "unexpected return type");
        resolvedExpr->setConstantValue(cee.evaluate(*resolvedExpr, false));
    }

    return std::make_unique<ResolvedReturnStmt>(returnStmt.location, std::move(resolvedExpr));
}

std::pair<ResolvedDecl *, int> Sema::lookupDecl(const std::string id)
{
    int scopeIdx = 0;

    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it)
    {

        for (auto &&decl : *it)
        {
            if (decl->identifier != id)
                continue;

            return {decl, scopeIdx};
        }
        ++scopeIdx;
    }

    return {nullptr, -1};
}

std::unique_ptr<ResolvedExpression> Sema::resolveExpression(const Expression &expr)
{

    if (const auto *number = dynamic_cast<const NumberLiteral *>(&expr))
        return std::make_unique<ResolvedNumberLiteral>(number->location, std::stod(number->value));

    if (const auto *callExpr = dynamic_cast<const CallExpression *>(&expr))
        return resolveCallExpression(*callExpr);

    if (const auto *declRefExpr = dynamic_cast<const DeclRefExpression *>(&expr))
        return resolveDeclarationRefExpr(*declRefExpr);

    if (const auto *binaryOperator = dynamic_cast<const BinaryOperator *>(&expr))
        return resolveBinaryOperator(*binaryOperator);

    if (const auto *unaryOperator = dynamic_cast<const UnaryOperator *>(&expr))
        return resolveUnaryOperator(*unaryOperator);

    if (const auto *groupingExpr = dynamic_cast<const GroupingExpression *>(&expr))
        return resolveGroupingExpression(*groupingExpr);

    llvm_unreachable("unexpected Expression");
}

std::unique_ptr<ResolvedDeclarationRefExpr> Sema::resolveDeclarationRefExpr(const DeclRefExpression &declRefExpr, bool isCallee)
{
    ResolvedDecl *decl = lookupDecl(declRefExpr.identifier).first;

    if (!decl)
        return report(declRefExpr.location, "symbol '" + declRefExpr.identifier + "' not found");

    if (!isCallee && dynamic_cast<ResolvedFunctionDecl *>(decl))
        return report(declRefExpr.location, "expected to call function '" + declRefExpr.identifier + "'");

    return std::make_unique<ResolvedDeclarationRefExpr>(declRefExpr.location, *decl);
}

std::unique_ptr<ResolvedCallExpr> Sema::resolveCallExpression(const CallExpression &callExpr)
{
    const auto *dre = dynamic_cast<const DeclRefExpression *>(callExpr.callee.get());
    if (!dre)
    {
        return report(callExpr.location, "expression cannot be called as a function");
    }

    varOrReturn(resolvedCallee, resolveDeclarationRefExpr(*dre, true));

    const auto *resolvedFunctionDecl = dynamic_cast<const ResolvedFunctionDecl *>(resolvedCallee->decl);
    if (!resolvedFunctionDecl)
        return report(callExpr.location, "argument mismatch in function call");

    std::vector<std::unique_ptr<ResolvedExpression>> resolvedArguments;
    int idx = 0;

    for (auto &&arg : callExpr.arguments)
    {
        varOrReturn(resolvedArg, resolveExpression(*arg));

        if (resolvedArg->type.kind != resolvedFunctionDecl->params[idx]->type.kind)
            return report(resolvedArg->location, "unexpected type of argument");
        resolvedArg->setConstantValue(cee.evaluate(*resolvedArg, false));
        idx++;
        resolvedArguments.emplace_back(std::move(resolvedArg));
    }

    return std::make_unique<ResolvedCallExpr>(callExpr.location, *resolvedFunctionDecl, std::move(resolvedArguments));
}

std::unique_ptr<ResolvedFunctionDecl> Sema::createBuiltinPrintln()
{
    SourceLocation loc{"<builtin>", 0, 0};

    auto param = std::make_unique<ResolvedParamDecl>(loc, "n", Type::builtInNumber());
    std::vector<std::unique_ptr<ResolvedParamDecl>> params;
    params.emplace_back(std::move(param));

    auto block = std::make_unique<ResolvedBlock>(loc, std::vector<std::unique_ptr<ResolvedStatement>>());

    return std::make_unique<ResolvedFunctionDecl>(loc, "println", Type::builtInVoid(), std::move(params), std::move(block));
}

bool Sema::insertDeclToCurrentScope(ResolvedDecl &decl)
{

    const auto &[foundDecl, scopeIdx] = lookupDecl(decl.identifier);
    if (foundDecl && scopeIdx == 0)
    {
        report(decl.location, "Redeclaration of '" + decl.identifier + "'");
        return false;
    }

    if (scopes.empty())
    {
        scopes.emplace_back();
    }
    scopes.back().emplace_back(&decl);
    return true;
}

std::unique_ptr<ResolvedUnaryOperator> Sema::resolveUnaryOperator(const UnaryOperator &unary)
{
    varOrReturn(resolvedRHS, resolveExpression(*unary.operand));

    if (resolvedRHS->type.kind == Type::Kind::Void)
    {
        return report(resolvedRHS->location, "void expressions cannot be used as an operand to unary operator");
    }

    return std::make_unique<ResolvedUnaryOperator>(unary.location, std::move(resolvedRHS), unary.op);
}

std::unique_ptr<ResolvedBinaryOperator> Sema::resolveBinaryOperator(const BinaryOperator &binOp)
{
    varOrReturn(resolvedLHS, resolveExpression(*binOp.lhs));
    varOrReturn(resolvedRHS, resolveExpression(*binOp.rhs));

    if (resolvedLHS->type.kind == Type::Kind::Void)
        return report(resolvedLHS->location, "void expression cannot be used as a LHS operand to binary operator");

    if (resolvedRHS->type.kind == Type::Kind::Void)
        return report(resolvedRHS->location, "void expression cannot be used as a RHS operand to binary operator");

    return std::make_unique<ResolvedBinaryOperator>(binOp.location, std::move(resolvedLHS), std::move(resolvedRHS), binOp.op);
}

std::unique_ptr<ResolvedGroupingExpression> Sema::resolveGroupingExpression(const GroupingExpression &grouping)
{
    varOrReturn(resolvedExpr, resolveExpression(*grouping.expr));
    return std::make_unique<ResolvedGroupingExpression>(grouping.location, std::move(resolvedExpr));
}

std::unique_ptr<ResolvedIfStatement> Sema::resolveIfStatement(const IfStatement &ifStmt)
{
    varOrReturn(condition, resolveExpression(*ifStmt.condition));

    if (condition->type.kind != Type::Kind::Number)
        return report(condition->location, "expected number in condtion");

    varOrReturn(resolvedTrueBlock, resolveBlock(*ifStmt.trueBlock));

    std::unique_ptr<ResolvedBlock> resolvedFalseBlock;
    if (ifStmt.falseBlock)
    {
        resolvedFalseBlock = resolveBlock(*ifStmt.falseBlock);
        if (!resolvedFalseBlock)
            return nullptr;
    }

    condition->setConstantValue(cee.evaluate(*condition, false));

    return std::make_unique<ResolvedIfStatement>(ifStmt.location, std::move(condition), std::move(resolvedTrueBlock), std::move(resolvedFalseBlock));
}

std::unique_ptr<ResolvedWhileStatement> Sema::resolveWhileStatement(const WhileStatement &stmt)
{
    varOrReturn(cond, resolveExpression(*stmt.condition));

    if (cond->type.kind != Type::Kind::Number)
        return report(cond->location, "expected number in condition");

    varOrReturn(body, resolveBlock(*stmt.body));

    cond->setConstantValue(cee.evaluate(*cond, false));

    return std::make_unique<ResolvedWhileStatement>(stmt.location, std::move(cond), std::move(body));
}

std::unique_ptr<ResolvedDeclStatement> Sema::resolveDeclStatement(const DeclStatement &declStmt)
{
    varOrReturn(resolvedVarDecl, resolveVarDecl(*declStmt.varDecl));

    if (!insertDeclToCurrentScope(*resolvedVarDecl))
        return nullptr;

    return std::make_unique<ResolvedDeclStatement>(declStmt.location, std::move(resolvedVarDecl));
}

std::unique_ptr<ResolvedVarDecl> Sema::resolveVarDecl(const VarDecl &varDecl)
{
    if (!varDecl.type && !varDecl.initializer)
        return report(varDecl.location, "an uninitialized variable is expected to have a type specifier");

    std::unique_ptr<ResolvedExpression> resolvedInitializer = nullptr;
    if (varDecl.initializer)
    {
        resolvedInitializer = resolveExpression(*varDecl.initializer);
        if (!resolvedInitializer)
            return nullptr;
    }

    Type resolvableType = varDecl.type.value_or(resolvedInitializer->type);
    std::optional<Type> type = resolveType(resolvableType);

    if (!type || type->kind == Type::Kind::Void)
        return report(varDecl.location, "variable '" + varDecl.identifier + "' has invalid '" + resolvableType.name + "' type");

    if (resolvedInitializer)
    {
        if (resolvedInitializer->type.kind != type->kind)
            return report(resolvedInitializer->location, "initializer type mismatch");

        resolvedInitializer->setConstantValue(cee.evaluate(*resolvedInitializer, false));
    }

    return std::make_unique<ResolvedVarDecl>(varDecl.location, varDecl.identifier, *type, varDecl.isMutable, std::move(resolvedInitializer));
}

std::unique_ptr<ResolvedAssignment> Sema::resolveAssignment(const Assignment &assignment)
{
    varOrReturn(resolvedLHS, resolveDeclarationRefExpr(*assignment.variable));
    varOrReturn(resolvedRHS, resolveExpression(*assignment.expr));

    if (dynamic_cast<const ResolvedParamDecl *>(resolvedLHS->decl))
        return report(resolvedLHS->location, "parameters are immutable and cannot be assigned");

    auto *var = dynamic_cast<const ResolvedVarDecl *>(resolvedLHS->decl);

    if (resolvedRHS->type.kind != resolvedLHS->type.kind)
        return report(resolvedRHS->location, "assigned value type doesn't match variable type");

    resolvedRHS->setConstantValue(cee.evaluate(*resolvedRHS, false));

    return std::make_unique<ResolvedAssignment>(assignment.location, std::move(resolvedLHS), std::move(resolvedRHS));
}

bool Sema::checkVariableInitialization(const ResolvedFunctionDecl &fn, const CFG &cfg)
{
    enum class State
    {
        Bottom,
        Unassigned,
        Assigned,
        Top
    };

    using Lattice = std::map<const ResolvedVarDecl *, State>;

    auto joinStates = [](State s1, State s2)
    {
        if (s1 == s2)
            return s1;

        if (s1 == State::Bottom)
            return s2;

        if (s2 == State::Bottom)
            return s1;

        return State::Top;
    };

    std::vector<Lattice> curLattices(cfg.basicBlocks.size());
    std::vector<std::pair<SourceLocation, std::string>> pendingErrors;

    bool changed = true;
    while (changed)
    {
        changed = false;
        pendingErrors.clear();

        for (int bb = cfg.entry; bb != cfg.exit; --bb)
        {
            Lattice tmp;

            const auto &[preds, succs, stmts] = cfg.basicBlocks[bb];

            for (auto &&pred : preds)
                for (auto &&[decl, state] : curLattices[pred.first])
                    tmp[decl] = joinStates(tmp[decl], state);

            for (auto it = stmts.rbegin(); it != stmts.rend(); ++it)
            {
                const ResolvedStatement *stmt = *it;
                if (const auto *decl = dynamic_cast<const ResolvedDeclStatement *>(stmt))
                {
                    tmp[decl->varDecl.get()] = decl->varDecl->initializer ? State::Assigned : State::Unassigned;
                    continue;
                }

                if (auto *assignment = dynamic_cast<const ResolvedAssignment *>(stmt))
                {
                    const auto *var = dynamic_cast<const ResolvedVarDecl *>(assignment->variable->decl);

                    if (!var->isMutable && tmp[var] != State::Unassigned)
                    {
                        std::string msg = '\'' + var->identifier + "' cannot be mutated";
                        pendingErrors.emplace_back(assignment->location, std::move(msg));
                    }

                    tmp[var] = State::Assigned;
                    continue;
                }
                if (const auto *dre = dynamic_cast<const ResolvedDeclarationRefExpr *>(stmt))
                {
                    const auto *var = dynamic_cast<const ResolvedVarDecl *>(dre->decl);

                    if (var && tmp[var] != State::Assigned)
                    {
                        std::string msg = '\'' + var->identifier + "' is not initialized";
                        pendingErrors.emplace_back(dre->location, std::move(msg));
                    }

                    continue;
                }
            }

            if (curLattices[bb] != tmp)
            {
                curLattices[bb] = tmp;
                changed = true;
            }
        }
    }
    for (auto &&[loc, msg] : pendingErrors)
        report(loc, msg);

    return !pendingErrors.empty();
}