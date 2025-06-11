#include <llvm/Support/ErrorHandling.h>

#include "libtarot/Evaluate.h"

std::optional<double> ConstantExpressionEvaluator::evaluate(const ResolvedExpression &expr, bool allowSideEffects)
{
    if (std::optional<double> val = expr.getConstantValue())
        return val;
    if (const auto *numberLiteral = dynamic_cast<const ResolvedNumberLiteral *>(&expr))
    {
        return numberLiteral->value;
    }

    if (const auto *groupingExpr = dynamic_cast<const ResolvedGroupingExpression *>(&expr))
    {
        return (evaluate(*groupingExpr->expr, allowSideEffects));
    }

    if (const auto *unaryOp = dynamic_cast<const ResolvedUnaryOperator *>(&expr))
    {
        return evaluateUnaryOperator(*unaryOp, allowSideEffects);
    }

    return std::nullopt;
}

std::optional<bool> toBool(std::optional<double> d)
{
    if (!d)
        return std::nullopt;

    return d != 0.0;
}

std::optional<double> ConstantExpressionEvaluator::evaluateUnaryOperator(const ResolvedUnaryOperator &unOp, bool allowSideEffects)
{
    std::optional<double> operand = evaluate(*unOp.operand, allowSideEffects);

    if (!operand)
        return std::nullopt;

    if (unOp.op == TokenType::EXCL)
        return !*toBool(operand);

    if (unOp.op == TokenType::MINUS)
        return -*operand;

    llvm_unreachable("unexpected unary operator");
}

std::optional<double> ConstantExpressionEvaluator::evaluateBinaryOperator(const ResolvedBinaryOperator &binOp, bool allowSideEffects)
{
    std::optional<double> lhs = evaluate(*binOp.lhs, allowSideEffects);

    if (!lhs && !allowSideEffects)
        return std::nullopt;

    if (binOp.op == TokenType::PIPEPIPE)
    {
        if (toBool(lhs) == true)
            return 1.0;
        std::optional<double> rhs = evaluate(*binOp.rhs, allowSideEffects);

        if (toBool(rhs) == true)
            return 1.0;

        if (lhs && rhs)
            return 0.0;

        return std::nullopt;
    }

    if (binOp.op == TokenType::AMPAMP)
    {
        if (toBool(lhs) == false)
            return 0.0;
        std::optional<double> rhs = evaluate(*binOp.rhs, allowSideEffects);

        if (toBool(rhs) == false)
            return 0.0;

        if (lhs && rhs)
            return 1.0;

        return std::nullopt;
    }

    if (!lhs)
        return std::nullopt;

    std::optional<double> rhs = evaluate(*binOp.rhs, allowSideEffects);
    if (!rhs)
        return std::nullopt;

    switch (binOp.op)
    {
    case TokenType::ASTERISK:
        return (*lhs) * (*rhs);
    case TokenType::SLASH:
        return (*lhs) / (*rhs);
    case TokenType::PLUS:
        return (*lhs) + (*rhs);
    case TokenType::MINUS:
        return (*lhs) - (*rhs);
    case TokenType::LT:
        return (*lhs) < (*rhs);
    case TokenType::GT:
        return (*lhs) > (*lhs);
    case TokenType::EQUALEQUAL:
        return (*lhs) == (*rhs);
    default:
        llvm_unreachable("unexpected binary operator");
    }
}
