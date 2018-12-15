//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_COMMANDEXPRESSION_H
#define PROJECT_ADVANCED_COMMANDEXPRESSION_H

#include <Command.h>
#include "Expression.h"

class CommandExpression : public Expression {
    Command *command;
public:
    CommandExpression(Command *c) : command(c) {}

    double calculate() override {
        command->doCommand();
        return 0;
    }

    ~CommandExpression() {
        delete (command);
    }
};

#endif //PROJECT_ADVANCED_COMMANDEXPRESSION_H
