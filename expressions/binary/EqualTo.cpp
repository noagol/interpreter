#include "EqualTo.h"

/**
 * Checks ==
 * @param l left expression
 * @param r right expression
 */
EqualTo::EqualTo(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l == r
 * @return l == r
 */
double EqualTo::calculate() {
    return getLeft()->calculate() == getRight()->calculate();
}