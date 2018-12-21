
#ifndef PROJECT_ADVANCED_DEFINEVARCOMMAND_H

#include "Command.h"
#include "../expressions/TokenArray.h"
#include "BaseCommand.h"
#include "../exceptions/CommandException.h"

#define PROJECT_ADVANCED_DEFINEVARCOMMAND_H


class DefineVarCommand : public BaseCommand {
public:
    DefineVarCommand(Parser *p);

    void doCommand() override;
};

#endif //PROJECT_ADVANCED_DEFINEVARCOMMAND_H
