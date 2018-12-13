

#ifndef ADVANCED_IFCOMMAND_H
#define ADVANCED_IFCOMMAND_H

#include <list>
#include "Command.h"

class IfCommand : public Command{
    vector<Command> commands;
    IfCommand(vector<Command>* comm){
        this->commands = *comm;
    }

    int doCommand(vector<string>* params) override {

    }
};



#endif //ADVANCED_IFCOMMAND_H