#ifndef SEMA_H
#define SEMA_H
#include <optional>
#include "Resolved.h"
#include "Parser.h"

class Sema
{
public:
    std::vector<std::unique_ptr<FunctionDecl>> ast;

    class ScopeRAII
    {
        Sema *sema;

    public:
        explicit ScopeRAII(Sema *sema) : sema(sema)
        {
            sema->scopes.emplace_back();
        }

        ~ScopeRAII()
        {
            sema->scopes.pop_back();
        }
    };
    explicit Sema(std::vector<std::unique_ptr<FunctionDecl>> &ast) : ast(std::move(ast)) {}

    std::vector<std::vector<ResolvedDecl *>> scopes;
    ResolvedFunctionDecl *currentFunction;
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolveAST();
    std::optional<Type> resolveType(Type parsedType);
    std::unique_ptr<ResolvedFunctionDecl> resolveFunctionDeclaration(const FunctionDecl &function);
    std::unique_ptr<ResolvedParamDecl> resolveParamDecl(const ParameterDecl &param);
    std::unique_ptr<ResolvedBlock> resolveBlock(const Block &block);
    std::unique_ptr<ResolvedStatement> resolveStatement(const Statement &stmt);
    std::unique_ptr<ResolvedReturnStmt> resolveReturnStatement(const ReturnStatement &returnStmt);
    std::pair<ResolvedDecl *, int> lookupDecl(const std::string id);
    std::unique_ptr<ResolvedExpression> resolveExpression(const Expression &expr);
    std::unique_ptr<ResolvedDeclarationRefExpr> resolveDeclarationRefExpr(const DeclRefExpression &declRefExpr, bool isCallee = false);
    std::unique_ptr<ResolvedCallExpr> resolveCallExpression(const CallExpression &callExpr);
    std::unique_ptr<ResolvedFunctionDecl> createBuiltinPrintln();
    std::unique_ptr<ResolvedUnaryOperator> resolveUnaryOperator(const UnaryOperator &unary);
    std::unique_ptr<ResolvedBinaryOperator> resolveBinaryOperator(const BinaryOperator &binary);
    std::unique_ptr<ResolvedGroupingExpression> resolveGroupingExpression(const GroupingExpression &grouping);


    bool insertDeclToCurrentScope(ResolvedDecl &decl);
};

#endif