
#ifndef PROJECT_ADVANCED_SMALLEROREQUALTHAN_H
#include "../BinaryExpression.h"

#define PROJECT_ADVANCED_SMALLEROREQUALTHAN_H


class SmallerOrEqualThan : public BinaryExpression {
public:
    SmallerOrEqualThan(Expression *l, Expression *r) ;

    double calculate() override ;
};


#endif //PROJECT_ADVANCED_SMALLEROREQUALTHAN_H
