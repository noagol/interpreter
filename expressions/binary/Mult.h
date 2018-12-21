
#ifndef PROJECT_ADVANCED_MUL_H

#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_MUL_H
class Mult : public BinaryExpression {
public:
    Mult(Expression *l, Expression *r) ;

    double calculate() override;
};

#endif //PROJECT_ADVANCED_MUL_H
