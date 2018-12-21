//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_MUL_H

#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_MUL_H
class Mult : public BinaryExpression {
public:
    Mult(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() * getRight()->calculate();
    }

};

#endif //PROJECT_ADVANCED_MUL_H