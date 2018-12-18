//
// Created by EB on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_CONDITIONPARSER_H
#define PROJECT_ADVANCED_CONDITIONPARSER_H

#include "../interpreter/Parser.h"
#include "../commands/BaseCommand.h"


class ConditionParser : public BaseCommand {
public:
    ConditionParser(Parser *p) : BaseCommand(p) {}

    Expression *readCondition() {
        return parser->getNextExpression();
    }

};

#endif //PROJECT_ADVANCED_CONDITIONPARSER_H
