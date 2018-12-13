//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_CONDITIONPARSER_H
#define PROJECT_ADVANCED_CONDITIONPARSER_H

#include "../expressions/Expression.h"
#include "Command.h"

class ConditionParser : public Command {

private:
    Expression *condition;
    vector<Command> *commands;
public:
    ConditionParser(Expression *cond, vector<Command>* command) :
            condition(cond), commands(command) {}

    Expression *getCondition() const {
        return condition;
    }

    vector<Command> *getCommands() const {
        return commands;
    }


};

#endif //PROJECT_ADVANCED_CONDITIONPARSER_H
