//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_EXPRESSION_H
#define PROJECT_ADVANCED_EXPRESSION_H


#include "../tables/SymbolTable.h"

class Expression {
public:
    virtual double calculate() = 0;

    virtual ~Expression() {}
};


#endif //PROJECT_ADVANCED_EXPRESSION_H
