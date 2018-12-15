//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_SMALLERTHAN_H
#define PROJECT_ADVANCED_SMALLERTHAN_H

#include "../expressions/BinaryExpression.h"

class SmallerThan : public BinaryExpression {
public:
    SmallerThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() < getRight()->calculate();
    }
};


#endif //PROJECT_ADVANCED_SMALLERTHAN_H
