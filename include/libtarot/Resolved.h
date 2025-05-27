#ifndef RESOLVED_H
#define RESOLVED_H
#include <vector>
#include <memory>
#include "Source.h"
#include "Type.h"
#include "Utils.h"
#include "TokenType.h"

struct ResolvedStatement
{
    SourceLocation location;
    ResolvedStatement(SourceLocation location) : location(location) {}

    virtual ~ResolvedStatement() = default;

    virtual void dump(size_t dump = 0) const = 0;

};

struct ResolvedExpression : public ResolvedStatement 
{
    Type type;

    ResolvedExpression(SourceLocation location, Type type) 
    : ResolvedStatement(location), type(type) {}
};

struct ResolvedDecl
{
    SourceLocation location;
    std::string  identifier;
    Type type;

    ResolvedDecl(SourceLocation location, std::string identifier, Type type): location(location), identifier(identifier), type(type) {}

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

    ResolvedFunctionDecl(SourceLocation location, std::string identifier, Type type, std::vector<std::unique_ptr<ResolvedParamDecl>> params, std::unique_ptr<ResolvedBlock> body) : ResolvedDecl(location, identifier, type) , params(std::move(params)), body(std::move(body)) {}

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



struct ResolvedReturnStmt : public ResolvedStatement {
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

    ResolvedBinaryOperator(SourceLocation location, std::unique_ptr<ResolvedExpression> lhs, std::unique_ptr<ResolvedExpression> rhs, TokenType op) : ResolvedExpression(location, lhs->type), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedUnaryOperator : public ResolvedExpression
{
    std::unique_ptr<ResolvedExpression> operand;
    TokenType op;

    ResolvedUnaryOperator(SourceLocation loc, std::unique_ptr<ResolvedExpression> operand, TokenType op) : ResolvedExpression(loc, operand->type), operand(std::move(operand)), op(op) {}

    void dump(size_t level = 0) const override;
};

#endif