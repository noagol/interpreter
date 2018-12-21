#include "Plus.h"

/**
 *  Div operator : l+r
 * @param l left expression
 * @param r right expression
 */
Plus::Plus(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l + r
 * @return l + r
 */
double Plus::calculate() {
    return getLeft()->calculate() + getRight()->calculate();
}