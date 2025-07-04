#ifndef RESOLVED_H
#define RESOLVED_H
#include <vector>
#include <memory>
#include "Source.h"
#include "Type.h"
#include "Utils.h"
#include "TokenType.h"
#include "Conainer.h"

struct ResolvedStatement
{
    SourceLocation location;
    ResolvedStatement(SourceLocation location) : location(location) {}

    virtual ~ResolvedStatement() = default;

    virtual void dump(size_t dump = 0) const = 0;
};

struct ResolvedExpression : public ConstantValueContainer<double>, public ResolvedStatement
{
    Type type;

    ResolvedExpression(SourceLocation location, Type type)
        : ResolvedStatement(location), type(type) {}
};

struct ResolvedDecl
{
    SourceLocation location;
    std::string identifier;
    Type type;

    ResolvedDecl(SourceLocation location, std::string identifier, Type type) : location(location), identifier(identifier), type(type) {}

    virtual ~ResolvedDecl() = default;

    virtual void dump(size_t level = 0) const = 0;
};
struct ResolvedBlock
{
    SourceLocation location;
    std::vector<std::unique_ptr<ResolvedStatement>> statements;

    ResolvedBlock(SourceLocation location, std::vector<std::unique_ptr<ResolvedStatement>> statements) : location(location), statements(std::move(statements)) {}

    void dump(size_t level = 0) const;
};

struct ResolvedParamDecl : public ResolvedDecl
{
    ResolvedParamDecl(SourceLocation location, std::string identifier, Type type) : ResolvedDecl(location, std::move(identifier), type) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedNumberLiteral : public ResolvedExpression
{
    double value;
    ResolvedNumberLiteral(SourceLocation location, double value) : ResolvedExpression(location, Type::builtInNumber()), value(value) {}
    void dump(size_t level = 0) const override;
};

struct ResolvedFunctionDecl : ResolvedDecl
{
    std::vector<std::unique_ptr<ResolvedParamDecl>> params;
    std::unique_ptr<ResolvedBlock> body;

    ResolvedFunctionDecl(SourceLocation location, std::string identifier, Type type, std::vector<std::unique_ptr<ResolvedParamDecl>> params, std::unique_ptr<ResolvedBlock> body) : ResolvedDecl(location, identifier, type), params(std::move(params)), body(std::move(body)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedDeclarationRefExpr : public ResolvedExpression
{
    const ResolvedDecl *decl;

    ResolvedDeclarationRefExpr(SourceLocation location, ResolvedDecl &decl) : ResolvedExpression(location, decl.type), decl(&decl) {};
    void dump(size_t level = 0) const override;
};

struct ResolvedCallExpr : public ResolvedExpression
{
    const ResolvedFunctionDecl *callee;
    std::vector<std::unique_ptr<ResolvedExpression>> arguments;

    ResolvedCallExpr(SourceLocation location, const ResolvedFunctionDecl &callee, std::vector<std::unique_ptr<ResolvedExpression>> arguments) : ResolvedExpression(location, callee.type), callee(&callee), arguments(std::move(arguments)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedReturnStmt : public ResolvedStatement
{
    std::unique_ptr<ResolvedExpression> expr;

    ResolvedReturnStmt(SourceLocation location,
                       std::unique_ptr<ResolvedExpression> expr = nullptr)
        : ResolvedStatement(location),
          expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedBinaryOperator : public ResolvedExpression
{
    std::unique_ptr<ResolvedExpression> lhs;
    std::unique_ptr<ResolvedExpression> rhs;
    TokenType op;

    ResolvedBinaryOperator(SourceLocation location, std::unique_ptr<ResolvedExpression> lhs, std::unique_ptr<ResolvedExpression> rhs, TokenType op) : ResolvedExpression(location, lhs->type), lhs(std::move(lhs)), rhs(std::move(rhs)), op(op) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedUnaryOperator : public ResolvedExpression
{
    std::unique_ptr<ResolvedExpression> operand;
    TokenType op;

    ResolvedUnaryOperator(SourceLocation loc, std::unique_ptr<ResolvedExpression> operand, TokenType op) : ResolvedExpression(loc, operand->type), operand(std::move(operand)), op(op) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedGroupingExpression : public ResolvedExpression
{
    std::unique_ptr<ResolvedExpression> expr;

    ResolvedGroupingExpression(SourceLocation loc, std::unique_ptr<ResolvedExpression> expr) : ResolvedExpression(loc, expr->type), expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedIfStatement : public ResolvedStatement
{
    std::unique_ptr<ResolvedExpression> condition;
    std::unique_ptr<ResolvedBlock> trueBlock;
    std::unique_ptr<ResolvedBlock> falseBlock;

    ResolvedIfStatement(SourceLocation location,
                        std::unique_ptr<ResolvedExpression> condition,
                        std::unique_ptr<ResolvedBlock> trueBlock,
                        std::unique_ptr<ResolvedBlock> falseBlock = nullptr)
        : ResolvedStatement(location),
          condition(std::move(condition)),
          trueBlock(std::move(trueBlock)),
          falseBlock(std::move(falseBlock)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedWhileStatement : public ResolvedStatement
{
    std::unique_ptr<ResolvedExpression> condition;
    std::unique_ptr<ResolvedBlock> body;

    ResolvedWhileStatement(SourceLocation location,
                           std::unique_ptr<ResolvedExpression> condition,
                           std::unique_ptr<ResolvedBlock> body) : ResolvedStatement(location),
                                                                  condition(std::move(condition)),
                                                                  body(std::move(body)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedVarDecl : public ResolvedDecl
{
    std::unique_ptr<ResolvedExpression> initializer;
    bool isMutable;

    ResolvedVarDecl(SourceLocation location,
                    std::string identifier,
                    Type type,
                    bool isMutable,
                    std::unique_ptr<ResolvedExpression> initializer = nullptr)
        : ResolvedDecl(location, std::move(identifier), type),
          initializer(std::move(initializer)),
          isMutable(isMutable) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedDeclStatement : public ResolvedStatement
{
    std::unique_ptr<ResolvedVarDecl> varDecl;

    ResolvedDeclStatement(SourceLocation location,
                          std::unique_ptr<ResolvedVarDecl> varDecl)
        : ResolvedStatement(location),
          varDecl(std::move(varDecl)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedAssignment : public ResolvedStatement
{
    std::unique_ptr<ResolvedDeclarationRefExpr> variable;
    std::unique_ptr<ResolvedExpression> expr;

    ResolvedAssignment(SourceLocation location,
                       std::unique_ptr<ResolvedDeclarationRefExpr> variable,
                       std::unique_ptr<ResolvedExpression> expr)
        : ResolvedStatement(location),
          variable(std::move(variable)),
          expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};
#endif