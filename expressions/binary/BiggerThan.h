//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_BIGGERTHAN_H
#define PROJECT_ADVANCED_BIGGERTHAN_H

#include "../BinaryExpression.h"

class BiggerThan : public BinaryExpression {
public:
    BiggerThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() > getRight()->calculate();
    }
};

#endif //PROJECT_ADVANCED_BIGGERTHAN_H
