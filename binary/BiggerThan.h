//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_BIGGERTHAN_H
#define PROJECT_ADVANCED_BIGGERTHAN_H

#include "../expressions/BinaryExpression.h"

class BiggerThan : public BinaryExpression {
public:
    BiggerThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() + getRight()->calculate();
    }

    double calculate(SymbolTable *symbolTable) override {
        return getLeft()->calculate(symbolTable) > getRight()->calculate(symbolTable);
    }
};

#endif //PROJECT_ADVANCED_BIGGERTHAN_H
