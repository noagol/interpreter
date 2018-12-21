#include "SmallerThan.h"

/**
 * Checks <
 * @param l left expression
 * @param r right expression
 */
SmallerThan::SmallerThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l < r
 * @return l < r
 */
double SmallerThan::calculate() {
    return getLeft()->calculate() < getRight()->calculate();
}