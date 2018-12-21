#include "BiggerOrEqualThan.h"

/**
 * Checks >=
 * @param l left expression
 * @param r right expression
 */
BiggerOrEqualThan::BiggerOrEqualThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l >= r
 * @return l >= r
 */
double BiggerOrEqualThan::calculate() {
    return getLeft()->calculate() >= getRight()->calculate();
}

