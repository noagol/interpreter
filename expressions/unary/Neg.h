//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_NEG_H

#include "../UnaryExpression.h"

#define PROJECT_ADVANCED_NEG_H


class Neg : public UnaryExpression {
public:
    Neg(Expression *exp) : UnaryExpression(exp) {}

    double calculate() override {
        return -1 * getExpression()->calculate();
    }

};
#endif //PROJECT_ADVANCED_NEG_H
