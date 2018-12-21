
#ifndef PROJECT_ADVANCED_NUMBER_H

#include "Expression.h"

#define PROJECT_ADVANCED_NUMBER_H


class Number : public Expression {
    double number;

public:
    Number(double num) ;

    double calculate() override ;
};

#endif //PROJECT_ADVANCED_NUMBER_H
