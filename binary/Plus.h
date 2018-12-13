//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_PLUS_H

#include "../expressions/BinaryExpression.h"

#define PROJECT_ADVANCED_PLUS_H


class Plus : public BinaryExpression {
public:
    Plus(Expression *l, Expression *r) : BinaryExpression(l, r) {}

    double calculate() override {
        return getLeft()->calculate() + getRight()->calculate();
    }

    double calculate(SymbolTable *symbolTable) override {
        return getLeft()->calculate(symbolTable) + getRight()->calculate(symbolTable);
    }
};


#endif //PROJECT_ADVANCED_PLUS_H
