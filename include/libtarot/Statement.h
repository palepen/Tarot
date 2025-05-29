#ifndef STATEMENT_H
#define STATEMENT_H
#include "Source.h"
#include "TokenType.h"
#include <memory>
#include <vector>

struct Statement
{
    SourceLocation location;
    Statement(SourceLocation location) : location(location) {}

    virtual ~Statement() = default;
    virtual void dump(size_t level = 0) const = 0;
};

struct Expression : public Statement
{
    Expression(SourceLocation location) : Statement(location) {}
    virtual ~Expression() = default;
};

struct ReturnStatement : public Statement
{
    std::unique_ptr<Expression> expr;
    ReturnStatement(SourceLocation location, std::unique_ptr<Expression> expr) : Statement(location), expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};

struct NumberLiteral : public Expression
{
    std::string value;

    NumberLiteral(SourceLocation location, std::string value) : Expression(location), value(value) {}

    void dump(size_t level = 0) const override;
};

struct DeclRefExpression : public Expression
{
    std::string identifier;

    DeclRefExpression(SourceLocation location, std::string identifier) : Expression(location), identifier(identifier) {}

    void dump(size_t level = 0) const override;
};

struct CallExpression : public Expression
{
    std::unique_ptr<Expression> callee;
    std::vector<std::unique_ptr<Expression>> arguments;

    CallExpression(SourceLocation location, std::unique_ptr<Expression> callee, std::vector<std::unique_ptr<Expression>> arguments) : Expression(location), callee(std::move(callee)), arguments(std::move(arguments)) {}

    void dump(size_t level = 0) const override;
};

struct BinaryOperator : public Expression
{
    std::unique_ptr<Expression> lhs;
    std::unique_ptr<Expression> rhs;
    TokenType op;

    BinaryOperator(SourceLocation location, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs, TokenType op) : Expression(location), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    void dump(size_t level = 0) const override;
};

struct UnaryOperator : public Expression
{
    std::unique_ptr<Expression> operand;
    TokenType op;

    UnaryOperator(SourceLocation loc, std::unique_ptr<Expression> operand, TokenType op) : Expression(loc), operand(std::move(operand)), op(op) {}

    void dump(size_t level = 0) const override;
};

struct GroupingExpression : public Expression
{
    std::unique_ptr<Expression> expr;
    
    GroupingExpression(SourceLocation location, std::unique_ptr<Expression> expr)
    : Expression(location) , expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};
#endif