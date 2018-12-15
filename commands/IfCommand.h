

#ifndef ADVANCED_IFCOMMAND_H

#include <list>
#include <Parser.h>
#include "Command.h"
#include "ConditionParser.h"

#define ADVANCED_IFCOMMAND_H


class IfCommand : public ConditionParser {
public:
    IfCommand(Expression *cond) : ConditionParser(cond) {}

    void doCommand() override {
        if (checkCondition()) {
            Parser parser = Parser();

        }
    }
};


#endif //ADVANCED_IFCOMMAND_H