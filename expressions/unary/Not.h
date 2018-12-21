
#ifndef PROJECT_ADVANCED_NOT_H

#include "../UnaryExpression.h"

#define PROJECT_ADVANCED_NOT_H


class Not : public UnaryExpression {
public:
    Not(Expression *exp);

    double calculate() override;

};

#endif //PROJECT_ADVANCED_NOT_H
