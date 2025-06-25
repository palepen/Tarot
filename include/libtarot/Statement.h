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

struct Block
{
    SourceLocation location;
    std::vector<std::unique_ptr<Statement>> statements;

    Block(SourceLocation location)
        : location(location) {}

    Block(SourceLocation location, std::vector<std::unique_ptr<Statement>> statements)
        : location(location), statements(std::move(statements)) {}

    void dump(size_t level = 0) const;
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

    BinaryOperator(SourceLocation location, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs, TokenType op) : Expression(location), lhs(std::move(lhs)), rhs(std::move(rhs)), op(op) {}

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
        : Expression(location), expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};

struct IfStatement : public Statement
{
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> trueBlock;
    std::unique_ptr<Block> falseBlock;

    IfStatement(SourceLocation loc, std::unique_ptr<Expression> condition,
                std::unique_ptr<Block> trueBlock,
                std::unique_ptr<Block> falseBlock = nullptr) : Statement(loc), condition(std::move(condition)), trueBlock(std::move(trueBlock)), falseBlock(std::move(falseBlock)) {}

    void dump(size_t level = 0) const override;
};

struct WhileStatement : public Statement
{
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> body;

    WhileStatement(SourceLocation loc, std::unique_ptr<Expression> condition, std::unique_ptr<Block> body) : Statement(loc), condition(std::move(condition)), body(std::move(body)) {}

    void dump(size_t level = 0) const override;
};


#endif