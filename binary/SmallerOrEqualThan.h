//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_SMALLEROREQUALTHAN_H
#define PROJECT_ADVANCED_SMALLEROREQUALTHAN_H

#include "../expressions/BinaryExpression.h"

class SmallerThan : public BinaryExpression {
public:
    SmallerThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() + getRight()->calculate();
    }

    double calculate(SymbolTable *symbolTable) override {
        return getLeft()->calculate(symbolTable) <= getRight()->calculate(symbolTable);
    }
};


#endif //PROJECT_ADVANCED_SMALLEROREQUALTHAN_H
