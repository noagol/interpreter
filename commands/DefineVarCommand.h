//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_DEFINEVARCOMMAND_H
#define PROJECT_ADVANCED_DEFINEVARCOMMAND_H

#include "Command.h"
#include "../expressions/TokenArray.h"

class DefineVarCommand : public Command {
public:
    DefineVarCommand() {};

    void doCommand() override {
        string varName = TokenArray::getInstance()->next();
        SymbolTable::getInstance()->add(varName, 0.0);
    }
};

#endif //PROJECT_ADVANCED_DEFINEVARCOMMAND_H
