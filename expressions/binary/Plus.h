//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_PLUS_H

#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_PLUS_H


class Plus : public BinaryExpression {
public:
    Plus(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() + getRight()->calculate();
    }
};


#endif //PROJECT_ADVANCED_PLUS_H
