
#ifndef PROJECT_ADVANCED_COMMANDEXPRESSION_H

#include "../commands/Command.h"
#include "Expression.h"

#define PROJECT_ADVANCED_COMMANDEXPRESSION_H


class CommandExpression : public Expression {
    Command *command;
public:
    CommandExpression(Command *c);

    double calculate() override;

    ~CommandExpression();
};

#endif //PROJECT_ADVANCED_COMMANDEXPRESSION_H
