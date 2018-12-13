//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_MINUS_H

#include "../expressions/BinaryExpression.h"

#define PROJECT_ADVANCED_MINUS_H


class Minus : public BinaryExpression {
public:
    Minus(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() - getRight()->calculate();
    }

};


#endif //PROJECT_ADVANCED_MINUS_H