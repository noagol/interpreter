

#ifndef PROJECT_ADVANCED_NOTEQUALTO_H
#define PROJECT_ADVANCED_NOTEQUALTO_H

#include "../BinaryExpression.h"

class NotEqualTo : public BinaryExpression {
public:
    NotEqualTo(Expression *l, Expression *r) ;

    double calculate() override;
};

#endif //PROJECT_ADVANCED_NOTEQUALTO_H
