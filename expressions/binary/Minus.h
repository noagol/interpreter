
#ifndef PROJECT_ADVANCED_MINUS_H

#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_MINUS_H


class Minus : public BinaryExpression {
public:
    Minus(Expression *l, Expression *r);

    double calculate() override;
};


#endif //PROJECT_ADVANCED_MINUS_H
