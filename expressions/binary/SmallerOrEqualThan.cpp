#include "SmallerOrEqualThan.h"
/**
 * Checks <=
 * @param l left expression
 * @param r right expression
 */
SmallerOrEqualThan::SmallerOrEqualThan(Expression *l, Expression *r) :
        BinaryExpression(l, r) {}
/**
 * calculate l <= r
 * @return l <= r
 */
double SmallerOrEqualThan::calculate() {
    return getLeft()->calculate() <= getRight()->calculate();
}