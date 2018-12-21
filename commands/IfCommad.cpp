#include "IfCommand.h"

/**
 * Condition - if
 * @param p - parset
 */
IfCommand::IfCommand(Parser *p) : ConditionParser(p) {}

/**
 * Execute command if the condition is met
 */
void IfCommand::doCommand() {
    // get the condition
    Expression *condition = readCondition();
    // get the next expression
    string startToken = parser->getTokenArray()->next();
    // check if after the condition get {
    if (startToken != "{") {
        throw CommandException("Missing opening brackets in if command");
    }
    // Check condition
    if ((bool) condition->calculate()) {
        // Run commands
        parser->parse();
    }
    // skip to the next end token '}'
    parser->getTokenArray()->skipToNextEnd();
    delete (condition);
}
