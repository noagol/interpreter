
#include "AssignmentCommand.h"

/**
 * Command for assigning variables
 * @param p -parser
 */
AssignmentCommand::AssignmentCommand(Parser *p) : BaseCommand(p) {};

/**
 * Assign a value to a variable.
 */
void AssignmentCommand::doCommand() {
    string varName = parser->getTokenArray()->getFrom(-2);
    // check if the var exists in the Symbol Table
    if (!parser->getSymbolTable()->exists(varName)) {
        throw CommandException(format("Variable %s is not defined", varName));
    }
    // get next expression
    string token = parser->getTokenArray()->next();

    // If the expression is a command
    if (parser->getCommandTable()->exists(token)) {
        Expression *command = parser->getCommandTable()->get(token);
        command->calculate();
    } else { // If the token is expression
        Expression *expression = parser->getTokenArray()->getExpression(token);
        if (expression == nullptr) {
            throw CommandException("No arguments to assignment command");
        }
        parser->getSymbolTable()->add(varName, expression->calculate());
        delete (expression);
    }
}
