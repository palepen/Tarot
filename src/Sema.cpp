#include "../includes/Sema.h"

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

        // for (auto &it : ast[i - 1]->body->statements)
        // {
        //     it->dump(0);
        // }

        auto resolvedBody = resolveBlock(*ast[i - 1]->body);
        if (!resolvedBody)
        {
            error = true;
            continue;
        }
        currentFunction->body = std::move(resolvedBody);
    }
    if (error)
        return {};

    return resolvedTree;
}

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
        return resolveReturnStatement(*returnStmt);

    llvm_unreachable("unexpected Statement");
}

std::unique_ptr<ResolvedReturnStmt> Sema::resolveReturnStatement(const ReturnStatement &returnStmt)
{
    if (currentFunction->type.kind == Type::Kind::Void && returnStmt.expr)
        return report(returnStmt.location, "Unexpected return value in void function");

    currentFunction->dump(0);

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
  
    if (const auto *declRefExpr = dynamic_cast<const DeclRefExpression *>(&expr))
        return resolveDeclarationRefExpr(*declRefExpr);

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

    // Might Give Error check originally (*callExpr->identifier, true) => changed to (*dre, true)
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