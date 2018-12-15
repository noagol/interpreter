//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_VAR_H
#define PROJECT_ADVANCED_VAR_H

#include <string>
#include "Expression.h"

using namespace std;

class Var : public Expression {
    string name;
public:
    Var(string n) : name(n) {}

    double calculate() override {
        return SymbolTable::getInstance()->get(name);
    }
};

#endif //PROJECT_ADVANCED_VAR_H
