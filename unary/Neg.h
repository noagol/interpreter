//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_NEG_H

#include "../expressions/UnaryExpression.h"

#define PROJECT_ADVANCED_NEG_H


class Neg : public UnaryExpression {
public:
    Neg(Expression *num) : UnaryExpression(num) {}

    double calculate() override {
        return -1 * getNumber()->calculate();
    }

};


#endif //PROJECT_ADVANCED_NEG_H
