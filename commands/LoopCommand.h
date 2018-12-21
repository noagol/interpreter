//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_LOOPCOMMAND_H
#define PROJECT_ADVANCED_LOOPCOMMAND_H

#include <list>
#include <Parser.h>
#include "Command.h"
#include "ConditionParser.h"
#include "../exceptions/CommandException.h"

#define ADVANCED_IFCOMMAND_H


class LoopCommand : public ConditionParser {
public:
    LoopCommand(Parser *p) : ConditionParser(p) {}

    void doCommand() override {
        Expression *condition = readCondition();
        string startToken = parser->getTokenArray()->next();
        if (startToken != "{") {
            throw CommandException("Missing opening brackets in if command");
        }

        int startPosition = parser->getTokenArray()->getIndex();

        while ((bool) condition->calculate()) {
            parser->getTokenArray()->moveTo(startPosition);
            parser->parse();
        }
        parser->getTokenArray()->skipToNextEnd();

        delete (condition);
    }
};

#endif //PROJECT_ADVANCED_LOOPCOMMAND_H
