#include "Mult.h"

/**
 *  Mult operator : l*r
 * @param l left expression
 * @param r right expression
 */
Mult::Mult(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l * r
 * @return l * r
 */
double Mult::calculate() {
    return getLeft()->calculate() * getRight()->calculate();
}
