//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_DIV_H

#include "../BinaryExpression.h"
#include "../../exceptions/ParserException.h"

#define PROJECT_ADVANCED_DIV_H


class Div : public BinaryExpression {
public:
    Div(Expression *l, Expression *r) ;

    double calculate() override ;
};


#endif //PROJECT_ADVANCED_DIV_H
