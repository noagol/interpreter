//
// Created by EB on 26/12/2018.
//

#include "ExitCommand.h"
#include "../exceptions/ExitException.h"

void ExitCommand::doCommand() {
    throw ExitException("Program exited.", 0);
}
