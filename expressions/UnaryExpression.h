
#ifndef PROJECT_ADVANCED_UNARYEXPRESSION_H

#include "Expression.h"

#define PROJECT_ADVANCED_UNARYEXPRESSION_H


class UnaryExpression : public Expression {
    Expression *expression;

public:
    UnaryExpression(Expression *exp);

    Expression *getExpression() const;

    ~UnaryExpression() override;

};

#endif //PROJECT_ADVANCED_UNARYEXPRESSION_H
