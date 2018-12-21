#include "BinaryExpression.h"

/**
 * Base class for binary expression
 * @param l - left expression
 * @param r - right expression
 */
BinaryExpression::BinaryExpression(Expression *l, Expression *r) :
        left(l), right(r) {
}

/**
 *
 * @return left expression
 */
Expression *BinaryExpression::getLeft() const {
    return left;
}

/**
 *
 * @return right expression
 */
Expression *BinaryExpression::getRight() const {
    return right;
}

/**
 * Free allocated memory
 */
BinaryExpression::~BinaryExpression() {
    delete (left);
    delete (right);
}
