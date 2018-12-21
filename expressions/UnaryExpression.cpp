#include "UnaryExpression.h"

/**
 * Base class for unary expression
 * @param exp - the expression
 */
UnaryExpression::UnaryExpression(Expression *exp) :
        expression(exp) {}

/**
 *
 * @return the expression
 */
Expression *UnaryExpression::getExpression() const {
    return expression;
}

/**
 * Free allocated memory
 */
UnaryExpression::~UnaryExpression() {
    delete (expression);
}