#include "Neg.h"

/**
 * Neg
 * @param exp
 */
Neg::Neg(Expression *exp) : UnaryExpression(exp) {}

/**
 * calculate - exp
 *
 */
double Neg::calculate() {
    return -1 * getExpression()->calculate();
}