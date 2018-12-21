#include "Div.h"

/**
 *  Div operator : l/r
 * @param l left expression
 * @param r right expression
 */
Div::Div(Expression *l, Expression *r) : BinaryExpression(l, r) {}

/**
 * calculate l / r
 * @return l / r
 */
double Div::calculate() {
    // get left expression
    double rightValue = getRight()->calculate();
    // check div in 0
    if (rightValue == 0) {
        throw ParserException("Divide by zero exception");
    }
    // return left/right
    return getLeft()->calculate() / rightValue;
}
