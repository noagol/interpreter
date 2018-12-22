

#ifndef ADVANCED_IFCOMMAND_H

#include <list>
#include "Command.h"
#include "ConditionParser.h"
#include "../exceptions/CommandException.h"

#define ADVANCED_IFCOMMAND_H


class IfCommand : public ConditionParser {
public:
    IfCommand(Parser *p);

    void doCommand() override;
};


#endif //ADVANCED_IFCOMMAND_H