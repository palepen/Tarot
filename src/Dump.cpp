#include <iostream>
#include "libtarot/Statement.h"
#include "libtarot/Utils.h"
#include "libtarot/TokenType.h"
#include "libtarot/Declaration.h"
#include "libtarot/Resolved.h"

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

void GroupingExpression::dump(size_t level) const
{
  std::cerr << indent(level) << "Grouping Expression";

  expr->dump(level + 1);
}

void IfStatement::dump(size_t level) const
{
  std::cerr << indent(level) << "IfStatement\n";

  condition->dump(level + 1);
  trueBlock->dump(level + 1);
  if (falseBlock)
    falseBlock->dump(level + 1);
}

void FunctionDecl::dump(size_t level) const
{
  std::cerr << indent(level) << "FunctionDecl: " << identifier << ":" << type.name << '\n';
  for (auto &&param : params)
  {
    param->dump(level + 1);
  }

  body->dump(level + 1);
};

void ParameterDecl::dump(size_t level) const
{
  std::cerr << indent(level) << "ParamDecl: " << identifier << "\n";
}

void Block::dump(size_t level) const
{
  std::cerr << indent(level) << "Block\n";
  for (auto &&stmt : statements)
  {
    stmt->dump(level + 1);
  }
}

void WhileStatement::dump(size_t level) const
{
  std::cerr << indent(level) << "WhileStatement\n";

  condition->dump(level + 1);
  body->dump(level + 1);
}

void ResolvedNumberLiteral::dump(size_t level) const
{

  std::cerr << indent(level) << "ResolvedNumberLiteral: '" << value << "'\n";
  if (auto val = getConstantValue())
    std::cerr << indent(level) << "| Value: '" << *val << "'\n";
}

void ResolvedDeclarationRefExpr::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedDeclRefExpr: @(" << decl->identifier << "\n";
}

void ResolvedCallExpr::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedCallExpr: @(" << &callee << ")" << callee->identifier << "\n";
  for (auto &&arg : arguments)
  {
    arg->dump(level + 1);
  }
}

void ResolvedBlock::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedBlock\n";

  for (auto &&stmt : statements)
  {
    if (stmt)
      stmt->dump(level + 1);
  }
}

void ResolvedParamDecl::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedParamDecl: @(" << this << ")" << identifier << ":" << "\n";
};

void ResolvedFunctionDecl::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedFunctionDecl: @(" << this << ")" << identifier << ":" << "\n";

  for (auto &&params : params)
  {
    params->dump(level + 1);
  }

  if (body)
    body->dump(level + 1);
}

void ResolvedReturnStmt::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedReturnStmt\n";

  if (expr)
    expr->dump(level + 1);
}

void ResolvedBinaryOperator::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedBinaryOperator: '" << getOpStr(op) << '\'' << '\n';

  lhs->dump(level + 1);
  rhs->dump(level + 1);
}

void ResolvedUnaryOperator::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedUnaryOperator: '" << getOpStr(op) << '\'' << '\n';

  if (auto val = getConstantValue())
    std::cerr << indent(level) << "| value: " << *val << '\n';

  operand->dump(level + 1);
}

void ResolvedGroupingExpression::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedGroupingExpr:\n";
  expr->dump(level + 1);
}

void ResolvedIfStatement::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedIfStatement\n";

  condition->dump(level + 1);
  trueBlock->dump(level + 1);
  if (falseBlock)
    falseBlock->dump(level + 1);
}

void ResolvedWhileStatement::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedWhileStatement\n";

  condition->dump(level + 1);
  body->dump(level + 1);
}

void VarDecl::dump(size_t level) const
{
  std::cerr << indent(level) << "VarDecl: " << identifier;
  if (type)
    std::cerr << ':' << type->name;
  std::cerr << '\n';

  if (initializer)
    initializer->dump(level + 1);
}

void DeclStatement::dump(size_t level) const
{
  std::cerr << indent(level) << "DeclStmt:\n";
  varDecl->dump(level + 1);
}

void ResolvedVarDecl::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedVarDecl: @(" << this << ") "
            << identifier << ':' << '\n';
  if (initializer)
    initializer->dump(level + 1);
}

void ResolvedDeclStatement::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedDeclStmt:\n";
  varDecl->dump(level + 1);
}

void Assignment::dump(size_t level) const
{
  std::cerr << indent(level) << "Assignment:\n";
  variable->dump(level + 1);
  expr->dump(level + 1);
}

void ResolvedAssignment::dump(size_t level) const
{
  std::cerr << indent(level) << "ResolvedAssignment:\n";
  variable->dump(level + 1);
  expr->dump(level + 1);
}
