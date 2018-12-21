
#ifndef PROJECT_ADVANCED_NEG_H

#include "../UnaryExpression.h"

#define PROJECT_ADVANCED_NEG_H


class Neg : public UnaryExpression {
public:
    Neg(Expression *exp);

    double calculate() override;

};

#endif //PROJECT_ADVANCED_NEG_H
