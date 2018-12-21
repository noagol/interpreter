//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_PRINTCOMMAND_H
#define PROJECT_ADVANCED_PRINTCOMMAND_H

#include <iostream>
#include "BaseCommand.h"
#include "../exceptions/CommandException.h"

class PrintCommand : public BaseCommand {

public:
    PrintCommand(Parser *p) ;

    void doCommand() override ;
};

#endif //PROJECT_ADVANCED_PRINTCOMMAND_H
