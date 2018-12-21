
#ifndef PROJECT_ADVANCED_BIGGEROREQUALTHAN_H
#define PROJECT_ADVANCED_BIGGEROREQUALTHAN_H

#include "../BinaryExpression.h"

class BiggerOrEqualThan : public BinaryExpression {
public:
    BiggerOrEqualThan(Expression *l, Expression *r);

    double calculate() override;
};


#endif //PROJECT_ADVANCED_BIGGEROREQUALTHAN_H
