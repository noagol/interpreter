#include "DefineVarCommand.h"

/**
 * Command class to define var
 * @param p - parser
 */
DefineVarCommand::DefineVarCommand(Parser *p) : BaseCommand(p) {};

/**
 * Add a variable to the command table
 */
void DefineVarCommand::doCommand() {
    // Get variable name
    string varName = parser->getTokenArray()->next();
    // Check if its a command name
    if (parser->getCommandTable()->exists(varName)) {
        throw CommandException(format("Unable to define variable: Name \"%s\" is a saved name", varName));
    }
    // Add to symbol table
    parser->getSymbolTable()->add(varName, 0.0);
}