#include "Minus.h"

/**
 *  Minus operator : l-r
 * @param l left expression
 * @param r right expression
 */
Minus::Minus(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l - r
 * @return l - r
 */
double Minus::calculate() {
    return getLeft()->calculate() - getRight()->calculate();
}
