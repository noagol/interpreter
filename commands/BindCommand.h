#ifndef PROJECT_ADVANCED_BINDCOMMAND_H
#define PROJECT_ADVANCED_BINDCOMMAND_H

#include <BindTable.h>
#include "../expressions/TokenArray.h"
#include "../commands/BaseCommand.h"
#include "../exceptions/CommandException.h"

class BindCommand : public BaseCommand {
public:
    BindCommand(Parser *p);
    void doCommand() override ;
};


#endif //PROJECT_ADVANCED_BINDCOMMAND_H
