//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_CONDITIONPARSER_H
#define PROJECT_ADVANCED_CONDITIONPARSER_H

#include "../expressions/Expression.h"
#include "Command.h"

class ConditionParser : public Command {
    Expression condition;
    vector<Command>* commands;
public:
    ConditionParser(){}
};

#endif //PROJECT_ADVANCED_CONDITIONPARSER_H
