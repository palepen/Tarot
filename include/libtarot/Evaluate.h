#ifndef EVALUATE_H
#define EVALUATE_H
#include <optional>

#include "Resolved.h"

class ConstantExpressionEvaluator
{
public:
    std::optional<double> evaluate(const ResolvedExpression &expr, bool allowSideEffects);
    std::optional<double> evaluateUnaryOperator(const ResolvedUnaryOperator &upOp, bool allowSideEffects);
    std::optional<double> evaluateBinaryOperator(const ResolvedBinaryOperator &unOp, bool allowSideEffects);
    std::optional<double> evaluateDeclRefExpr(const ResolvedDeclarationRefExpr &dre, bool allowSideEffects);

};

#endif