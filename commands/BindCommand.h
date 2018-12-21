#ifndef PROJECT_ADVANCED_BINDCOMMAND_H
#define PROJECT_ADVANCED_BINDCOMMAND_H

#include <BindTable.h>
#include "../expressions/TokenArray.h"
#include "../commands/BaseCommand.h"


class BindCommand : public BaseCommand {
public:
    BindCommand(Parser *p) : BaseCommand(p) {}

    void doCommand() override {
        string argument = parser->getTokenArray()->next();
        // Get variable name
        string varName = parser->getTokenArray()->getFrom(-4);
        // Validate variable exists
        if (!parser->getSymbolTable()->exists(varName)) {
            throw ParserException(format("Undefined variable to Bind Command: %s", varName));
        }

        if (argument.at(0) == '"' && argument.at(argument.size() - 1) == '"') {
            // String
            // Insert to bind table
            parser->getBindTable()->insert(varName, argument.substr(1, argument.size() - 2));
        } else {
            // Variable
            // Check if in the bind table
            if (!parser->getBindTable()->variableExists(argument)) {
                throw ParserException(format("Variable %s has not been bind to a path", argument));
            }

            // Add to bind table
            parser->getBindTable()->insert(varName, parser->getBindTable()->getPathByVariable(argument));
        }
    }
};


#endif //PROJECT_ADVANCED_BINDCOMMAND_H
