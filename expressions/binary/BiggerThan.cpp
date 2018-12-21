#include "BiggerThan.h"

/**
 * Checks >
 * @param l left expression
 * @param r right expression
 */
BiggerThan::BiggerThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l > r
 * @return l > r
 */
double BiggerThan::calculate() {
    return getLeft()->calculate() > getRight()->calculate();
}

