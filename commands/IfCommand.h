

#ifndef ADVANCED_IFCOMMAND_H

#include <list>
#include "Command.h"
#include "ConditionParser.h"

#define ADVANCED_IFCOMMAND_H


class IfCommand : public ConditionParser {
public:
    IfCommand(Expression *cond, vector<Command> *command) :
            ConditionParser(cond, command) {}

    void doCommand() override {
        if (getCondition()->calculate()) {
            typename vector<Command>::iterator it;
            for (it = getCommands()->begin(); it != getCommands()->end(); ++it) {

            }
        }
    }
};


#endif //ADVANCED_IFCOMMAND_H