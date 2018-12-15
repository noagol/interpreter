//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_LOOPCOMMAND_H
#define PROJECT_ADVANCED_LOOPCOMMAND_H

#include <list>
#include <Parser.h>
#include "Command.h"
#include "ConditionParser.h"

#define ADVANCED_IFCOMMAND_H


class LoopCommand : public ConditionParser {
public:
    LoopCommand() : ConditionParser() {}

    void doCommand() override {
        Expression *condition = readCondition();
        string startToken = TokenArray::getInstance()->next();
        if (startToken != "{") {
            throw ParserException("Missing opening brackets in if command");
        }

        int startPosition = TokenArray::getInstance()->getIndex();

        while ((bool) condition->calculate()) {
            TokenArray::getInstance()->moveTo(startPosition);
            Parser parser = Parser();
            parser.parse();
        }
        TokenArray::getInstance()->skipToNextEnd();

        delete (condition);
    }
};

#endif //PROJECT_ADVANCED_LOOPCOMMAND_H
