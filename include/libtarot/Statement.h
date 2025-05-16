#ifndef STATEMENT_H
#define STATEMENT_H
#include "Source.h"
#include <iostream>
#include <memory>
#include <vector>
#include "Indent.h"

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

    void dump(size_t level = 0) const override{
        std::cerr << indent(level) << "ReturnStmt\n";

        if(expr){
            expr->dump(level + 1);
        }
    }
};

struct NumberLiteral : public Expression
{
    std::string value;
    
    NumberLiteral(SourceLocation location, std::string value) : Expression(location), value(value) {}

    void dump(size_t level = 0) const override{
        std::cerr << indent(level) << "NumberLiteral: '" << value << "'\n";
    }
};

struct DeclRefExpression : public Expression
{
    std::string identifier;
    
    DeclRefExpression(SourceLocation location, std::string identifier) : Expression(location), identifier(identifier) {}

    void dump(size_t level = 0) const override{
        std::cerr << indent(level) << "Identifier: '" << identifier << "'\n";
    }
};

struct CallExpression : public Expression
{
    std::unique_ptr<Expression> callee;
    std::vector<std::unique_ptr<Expression>> arguments;

    CallExpression(SourceLocation location, std::unique_ptr<Expression> callee, std::vector<std::unique_ptr<Expression>> arguments) : Expression(location), callee(std::move(callee)), arguments(std::move(arguments)){}

    void dump(size_t level = 0) const override {
        std::cerr << indent(level) << "Call Expr: \n";

        callee->dump(level + 1);

        for (auto &&arg : arguments){
            arg->dump(level + 1);
        }
    };
};




#endif