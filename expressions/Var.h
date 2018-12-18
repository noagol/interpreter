//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_VAR_H
#define PROJECT_ADVANCED_VAR_H

#include <string>
#include "Expression.h"

using namespace std;

class Var : public Expression {
    SymbolTable *symbolTable;
    string name;
public:
    Var(const string& n, SymbolTable *st) : name(n), symbolTable(st) {}

    double calculate() override {
        return symbolTable->get(name);
    }
};

#endif //PROJECT_ADVANCED_VAR_H
