//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_NOTEQUALTO_H
#define PROJECT_ADVANCED_NOTEQUALTO_H

#include "../BinaryExpression.h"

class NotEqualTo : public BinaryExpression {
public:
    NotEqualTo(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() != getRight()->calculate();
    }
};

#endif //PROJECT_ADVANCED_NOTEQUALTO_H
