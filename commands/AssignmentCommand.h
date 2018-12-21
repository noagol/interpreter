

#ifndef PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H
#define PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H

#include <CommandTable.h>
#include "Command.h"
#include "../expressions/TokenArray.h"
#include "BaseCommand.h"
#include "../exceptions/CommandException.h"

class AssignmentCommand : public BaseCommand {
public:
    AssignmentCommand(Parser *p);

    void doCommand() override;
};

#endif //PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H
