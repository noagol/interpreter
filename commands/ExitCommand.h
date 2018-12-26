//
// Created by EB on 26/12/2018.
//

#ifndef PROJECT_ADVANCED_EXITCOMMAND_H
#define PROJECT_ADVANCED_EXITCOMMAND_H


#include "Command.h"
#include "BaseCommand.h"

class ExitCommand : public BaseCommand {
public:
    ExitCommand(Parser *p) : BaseCommand(p) {}

    void doCommand() override;
};


#endif //PROJECT_ADVANCED_EXITCOMMAND_H
