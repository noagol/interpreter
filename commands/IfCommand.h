

#ifndef ADVANCED_IFCOMMAND_H

#include <list>
#include <Parser.h>
#include "Command.h"
#include "ConditionParser.h"

#define ADVANCED_IFCOMMAND_H


class IfCommand : public ConditionParser {
public:
    IfCommand() : ConditionParser() {}

    void doCommand() override {
        Expression *condition = readCondition();
        string startToken = TokenArray::getInstance()->next();
        if (startToken != "{") {
            throw ParserException("Missing opening brackets in if command");
        }

        if ((bool) condition->calculate()) {
            Parser parser = Parser();
            parser.parse();
        } else {
            TokenArray::getInstance()->skipToNextEnd();
        }

        delete (condition);
    }
};


#endif //ADVANCED_IFCOMMAND_H