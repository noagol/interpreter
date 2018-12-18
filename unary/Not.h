//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_NOT_H
#define PROJECT_ADVANCED_NOT_H


#include "../expressions/UnaryExpression.h"

class Not : public UnaryExpression {
public:
    Not(Expression *exp) : UnaryExpression(exp) {}

    double calculate() override {
        return !getExpression()->calculate();
    }

};

#endif //PROJECT_ADVANCED_NOT_H
