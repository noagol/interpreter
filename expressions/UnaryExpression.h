//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_UNARYEXPRESSION_H

#include "Expression.h"

#define PROJECT_ADVANCED_UNARYEXPRESSION_H


class UnaryExpression : public Expression {
    Expression *expression;

public:
    UnaryExpression(Expression *exp) :
            expression(exp) {}

    ~UnaryExpression() override {
        delete (expression);
    }

    Expression *getExpression() const {
        return expression;
    }

};

#endif //PROJECT_ADVANCED_UNARYEXPRESSION_H
