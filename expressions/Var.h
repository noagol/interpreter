
#ifndef PROJECT_ADVANCED_VAR_H

#include <string>
#include <SymbolTable.h>
#include "Expression.h"

#define PROJECT_ADVANCED_VAR_H


using namespace std;

class Var : public Expression {
    SymbolTable *symbolTable;
    string name;
public:
    Var(const string &n, SymbolTable *st);

    double calculate() override;
};

#endif //PROJECT_ADVANCED_VAR_H
