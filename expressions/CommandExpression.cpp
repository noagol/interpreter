#include "CommandExpression.h"

/**
 * Object adapter for commands which inherits Expression
 * @param c - command
 */
CommandExpression::CommandExpression(Command *c) : command(c) {}

/**
 * Call do command of the command the object holds
 * @return
 */
double CommandExpression::calculate() {
    command->doCommand();
    return 0;
}

/**
 * Delete allocated command
 */
CommandExpression::~CommandExpression() {
    delete (command);
}