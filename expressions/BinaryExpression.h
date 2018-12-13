//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_BINARYEXPRESSION_H

#include "Expression.h"

#define PROJECT_ADVANCED_BINARYEXPRESSION_H


class BinaryExpression : public Expression {
    Expression *left;
    Expression *right;

public:
    BinaryExpression(Expression *l, Expression *r) :
            left(l), right(r) {
    }

    ~BinaryExpression() override {
        delete (left);
        delete (right);
    }

    Expression *getLeft() const {
        return left;
    }

    Expression *getRight() const {
        return right;
    }

};

#endif //PROJECT_ADVANCED_BINARYEXPRESSION_H
