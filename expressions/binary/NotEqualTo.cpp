#include "NotEqualTo.h"

/**
 * Checks !=
 * @param l left expression
 * @param r right expression
 */
NotEqualTo::NotEqualTo(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l != r
 * @return l != r
 */
double NotEqualTo::calculate() {
    return getLeft()->calculate() != getRight()->calculate();
}