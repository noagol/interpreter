#include "Not.h"

/**
 * Not operator
 * @param exp
 */
Not::Not(Expression *exp) : UnaryExpression(exp) {}

/**
 * calculate logical not
 * @return ! expr
 */
double Not::calculate() {
    return !getExpression()->calculate();
}