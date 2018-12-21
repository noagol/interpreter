
#ifndef PROJECT_ADVANCED_BINARYEXPRESSION_H

#include "Expression.h"

#define PROJECT_ADVANCED_BINARYEXPRESSION_H


class BinaryExpression : public Expression {
    Expression *left;
    Expression *right;

public:
    BinaryExpression(Expression *l, Expression *r);

    Expression *getLeft() const;

    Expression *getRight() const;

    ~BinaryExpression() override;

};

#endif //PROJECT_ADVANCED_BINARYEXPRESSION_H
