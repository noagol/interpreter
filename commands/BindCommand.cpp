
#include "BindCommand.h"

/**
 * Bind Command
 * @param p parser
 */
BindCommand::BindCommand(Parser *p) : BaseCommand(p) {}


/**
 * bind a var to flightgear path
 */
void BindCommand::doCommand() {
    string argument = parser->getTokenArray()->next();
    // Get variable name
    string varName = parser->getTokenArray()->getFrom(-4);
    // Validate variable exists
    if (!parser->getSymbolTable()->exists(varName)) {
        throw CommandException(format("Undefined variable to Bind Command: %s", varName));
    }

    if (argument.at(0) == '"' && argument.at(argument.size() - 1) == '"') {
        // String
        // Insert to bind table
        parser->getBindTable()->insert(varName, argument.substr(1, argument.size() - 2));
    } else {
        // Variable
        // Check if in the bind table
        if (!parser->getBindTable()->variableExists(argument)) {
            throw CommandException(format("Variable %s has not been bind to a path", argument));
        }

        // Add to bind table
        parser->getBindTable()->insert(varName, parser->getBindTable()->getPathByVariable(argument));
    }
}

