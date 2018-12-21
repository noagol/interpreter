
#ifndef PROJECT_ADVANCED_SMALLERTHAN_H
#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_SMALLERTHAN_H


class SmallerThan : public BinaryExpression {
public:
    SmallerThan(Expression *l, Expression *r) ;

    double calculate() override;
};


#endif //PROJECT_ADVANCED_SMALLERTHAN_H
