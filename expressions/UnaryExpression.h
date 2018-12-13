//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_UNARYEXPRESSION_H

#include "Expression.h"

#define PROJECT_ADVANCED_UNARYEXPRESSION_H


class UnaryExpression : public Expression {
    Expression *number;

public:
    UnaryExpression(Expression *num) :
            number(num) {
    }

    ~UnaryExpression() override {
        delete (number);
    }

    Expression *getNumber() const {
        return number;
    }

};

#endif //PROJECT_ADVANCED_UNARYEXPRESSION_H
