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
public:
    ConditionParser(Expression *cond) : condition(cond) {}

    bool checkCondition() const {
        return (bool) condition->calculate();
    }
};

#endif //PROJECT_ADVANCED_CONDITIONPARSER_H
