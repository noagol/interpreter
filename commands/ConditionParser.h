//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_CONDITIONPARSER_H
#include "../interpreter/Parser.h"
#include "../commands/BaseCommand.h"
#define PROJECT_ADVANCED_CONDITIONPARSER_H

class ConditionParser : public BaseCommand {
public:
    ConditionParser(Parser *p);

    Expression *readCondition();
};

#endif //PROJECT_ADVANCED_CONDITIONPARSER_H
