//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_CONDITIONPARSER_H
#define PROJECT_ADVANCED_CONDITIONPARSER_H

#include "../expressions/Expression.h"
#include "Command.h"
#include "../expressions/TokenArray.h"
#include "../expressions/ExpressionParser.h"

class ConditionParser : public Command {
public:
    ConditionParser() {}

    Expression* readCondition() {
        string c = TokenArray::getInstance()->next();
        return ExpressionParser().parse(c);
    }

};

#endif //PROJECT_ADVANCED_CONDITIONPARSER_H
