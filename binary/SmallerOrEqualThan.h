//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_SMALLEROREQUALTHAN_H
#define PROJECT_ADVANCED_SMALLEROREQUALTHAN_H

#include "../expressions/BinaryExpression.h"

class SmallerOrEqualThan : public BinaryExpression {
public:
    SmallerOrEqualThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() <= getRight()->calculate();
    }
};


#endif //PROJECT_ADVANCED_SMALLEROREQUALTHAN_H
