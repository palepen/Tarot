#ifndef RESOLVED_H
#define RESOLVED_H
#include <vector>
#include <memory>
#include "Source.h"
#include "Type.h"
#include "Indent.h"
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

void ResolvedNumberLiteral::dump(size_t level) const {
  std::cerr << indent(level) << "ResolvedNumberLiteral: '" << value << "'\n";
}

struct ResolvedDeclarationRefExpr : public ResolvedExpression
{
    const ResolvedDecl *decl;

    ResolvedDeclarationRefExpr(SourceLocation location, ResolvedDecl &decl) : ResolvedExpression(location, decl.type), decl(&decl) {};
    void dump(size_t level = 0) const override;
};

void ResolvedDeclarationRefExpr::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedDeclRefExpr: @(" << decl->identifier << "\n";
}

struct ResolvedCallExpr : public ResolvedExpression 
{
    const ResolvedFunctionDecl *callee;
    std::vector<std::unique_ptr<ResolvedExpression>> arguments;

    ResolvedCallExpr(SourceLocation location, const ResolvedFunctionDecl &callee, std::vector<std::unique_ptr<ResolvedExpression>> arguments) : ResolvedExpression(location, callee.type), callee(&callee), arguments(std::move(arguments)) {} 

    void dump(size_t level = 0) const override;
};

void ResolvedCallExpr::dump(size_t level) const 
{
    std::cerr << indent(level) << "ResolvedCallExpr: @(" << &callee << ")" << callee->identifier << "\n";

    for(auto &&arg : arguments){
        arg->dump(level + 1);
    } 
}


void ResolvedBlock::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedBlock\n";

    for(auto &&stmt : statements) 
    {
        stmt->dump(level + 1);
    }
}


void ResolvedParamDecl::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedParamDecl: @(" << this << ")" << identifier << ":" << "\n";
};


void ResolvedFunctionDecl::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedFunctionDecl: @(" << this << ")" << identifier << ":" << "\n";

    for (auto &&params : params){
        params->dump(level + 1);
    }

    body->dump(level + 1);
}

struct ResolvedReturnStmt : public ResolvedStatement {
  std::unique_ptr<ResolvedExpression> expr;

  ResolvedReturnStmt(SourceLocation location,
                     std::unique_ptr<ResolvedExpression> expr = nullptr)
      : ResolvedStatement(location),
        expr(std::move(expr)) {}

  void dump(size_t level = 0) const override;
};

void ResolvedReturnStmt::dump(size_t level) const {
  std::cerr << indent(level) << "ResolvedReturnStmt\n";

  if (expr)
    expr->dump(level + 1);
}

#endif