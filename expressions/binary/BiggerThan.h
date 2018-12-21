
#ifndef PROJECT_ADVANCED_BIGGERTHAN_H
#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_BIGGERTHAN_H


class BiggerThan : public BinaryExpression {
public:
    BiggerThan(Expression *l, Expression *r) ;

    double calculate() override ;
};

#endif //PROJECT_ADVANCED_BIGGERTHAN_H
