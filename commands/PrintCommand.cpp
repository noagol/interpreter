#include "PrintCommand.h"

/**
 * Command class for print
 * @param p - parser
 */
PrintCommand::PrintCommand(Parser *p) : BaseCommand(p) {}

/**
 * Print an expression
 */
void PrintCommand::doCommand() {
    // get the expression to print
    string token = parser->getTokenArray()->next();
    // check if the expression is not empty
    if (token.empty()) {
        throw CommandException("Not enough arguments for print command. Expected 1: 0 given");
    }
    // check if the token is string
    if (token.at(0) == '\"' && token.at(token.size() - 1) == '\"') {
        // String
        cout << token.substr(1, token.size() - 2) << endl;
    } else { // the token is expression
        Expression *expression = parser->getTokenArray()->getExpression(token);
        // not enough arguments
        if (expression == nullptr) {
            throw CommandException(format("Invalid expression for print: %s", token));
        }
        cout << expression->calculate() << endl;
        delete (expression);
    }
}
