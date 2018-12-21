
#ifndef PROJECT_ADVANCED_EQUALTO_H
#define PROJECT_ADVANCED_EQUALTO_H

#include "../BinaryExpression.h"

class EqualTo : public BinaryExpression {
public:
    EqualTo(Expression *l, Expression *r) ;

    double calculate() override;
};



#endif //PROJECT_ADVANCED_EQUALTO_H
