//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_DEFINEVARCOMMAND_H
#define PROJECT_ADVANCED_DEFINEVARCOMMAND_H

#include "Command.h"
#include "../expressions/TokenArray.h"
#include "BaseCommand.h"

class DefineVarCommand : public BaseCommand {
public:
    DefineVarCommand(Parser *p):BaseCommand(p) {};

    void doCommand() override {
        string varName = parser->getTokenArray()->next();
       parser->getSymbolTable()->add(varName, 0.0);
    }
};

#endif //PROJECT_ADVANCED_DEFINEVARCOMMAND_H
