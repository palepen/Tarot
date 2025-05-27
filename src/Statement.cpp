#include <iostream>
#include "libtarot/Statement.h"
#include "libtarot/Utils.h"
#include "libtarot/TokenType.h"


void ReturnStatement::dump(size_t level) const
{
    std::cerr << indent(level) << "ReturnStmt\n";

    if (expr)
    {
        expr->dump(level + 1);
    }
}

void NumberLiteral::dump(size_t level) const
{
    std::cerr << indent(level) << "NumberLiteral: '" << value << "'\n";
}

void DeclRefExpression::dump(size_t level) const
{
    std::cerr << indent(level) << "Identifier: '" << identifier << "'\n";
}

void CallExpression::dump(size_t level) const
{
    std::cerr << indent(level) << "Call Expr: \n";

    callee->dump(level + 1);

    for (auto &&arg : arguments)
    {
        arg->dump(level + 1);
    }
}


void BinaryOperator::dump(size_t level) const
{
    std::cerr << indent(level) << "BinaryOperator: '" << getOpStr(op) << '\'' << '\n';

    lhs->dump(level + 1);
    rhs->dump(level + 1);
}

void UnaryOperator::dump(size_t level) const 
{
    std::cerr << indent(level) << "UnaryOperator: '" << getOpStr(op) << '\'' << "\n";

    operand->dump(level + 1);
}