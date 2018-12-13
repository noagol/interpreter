//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_NUMBER_H

#include "Expression.h"

#define PROJECT_ADVANCED_NUMBER_H


class Number : public Expression {
    double number;

public:
    Number(double num) : number(num) {}

    double calculate() override {
        return number;
    }

    double calculate(SymbolTable *symbolTable) override {
        return number;
    }

};

#endif //PROJECT_ADVANCED_NUMBER_H
