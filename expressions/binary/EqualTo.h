//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_EQUALTO_H
#define PROJECT_ADVANCED_EQUALTO_H

#include "../BinaryExpression.h"

class EqualTo : public BinaryExpression {
public:
    EqualTo(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() == getRight()->calculate();
    }
};



#endif //PROJECT_ADVANCED_EQUALTO_H
