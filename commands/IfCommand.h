

#ifndef ADVANCED_IFCOMMAND_H

#include <list>
#include <Parser.h>
#include "Command.h"
#include "ConditionParser.h"

#define ADVANCED_IFCOMMAND_H


class IfCommand : public ConditionParser {
public:
    IfCommand(Parser *p) : ConditionParser(p) {}

    void doCommand() override {
        Expression *condition = readCondition();
        string startToken = parser->getTokenArray()->next();
        if (startToken != "{") {
            throw CommandException("Missing opening brackets in if command");
        }

        if ((bool) condition->calculate()) {
            parser->parse();
        }

        parser->getTokenArray()->skipToNextEnd();

        delete (condition);
    }
};


#endif //ADVANCED_IFCOMMAND_H