

#ifndef PROJECT_ADVANCED_PLUS_H

#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_PLUS_H


class Plus : public BinaryExpression {
public:
    Plus(Expression *l, Expression *r);

    double calculate() override;
};


#endif //PROJECT_ADVANCED_PLUS_H
