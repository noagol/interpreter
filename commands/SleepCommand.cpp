#include "SleepCommand.h"

/**
 * Command class for sleep
 * @param p - parser
 */
SleepCommand::SleepCommand(Parser *p) : BaseCommand(p) {}

/**
 * Go to sleep
 */
void SleepCommand::doCommand() {
    // Parse expression
    Expression *expression = parser->getNextExpression();
    // not enough arguments
    if (expression == nullptr) {
        throw CommandException("Not enough arguments for sleep command. Expected 1, 0 given");
    }
    // calculate the time
    int sleepTime = (int) expression->calculate();
    // Remove allocated memory
    delete (expression);
    // Validate
    if (sleepTime < 0) {
        // Invalid sleep time
        throw CommandException(format("Negative time for sleep: %d", sleepTime));
    }
    // Sleep
    this_thread::sleep_for(std::chrono::milliseconds((unsigned int) sleepTime));
}