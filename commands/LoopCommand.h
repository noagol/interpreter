

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
    LoopCommand(Parser *p);

    void doCommand() override ;
};

#endif //PROJECT_ADVANCED_LOOPCOMMAND_H
