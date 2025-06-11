#include "libtarot/Resolved.h"
#include <iostream>

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