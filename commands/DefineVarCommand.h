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
    DefineVarCommand(Parser *p) : BaseCommand(p) {};

    void doCommand() override {
        // Get variable name
        string varName = parser->getTokenArray()->next();
        // Check if its a command name
        if (parser->getCommandTable()->exists(varName)) {
            throw ParserException(format("Unable to define variable: Name \"%s\" is a saved name", varName));
        }
        // Add to symbol table
        parser->getSymbolTable()->add(varName, 0.0);
    }
};

#endif //PROJECT_ADVANCED_DEFINEVARCOMMAND_H
