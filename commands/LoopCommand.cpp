#include "LoopCommand.h"

/**
 * Condition - Loop
 * @param p - parser
 */
LoopCommand::LoopCommand(Parser *p) : ConditionParser(p) {}

/**
 * Execute command loop the condition is met
 */
void LoopCommand::doCommand() {
    // get the condition
    Expression *condition = readCondition();
    // get the next expression
    string startToken = parser->getTokenArray()->next();
    // check if after the condition get {
    if (startToken != "{") {
        throw CommandException("Missing opening brackets in if command");
    }
    // save the index of the start
    int startPosition = parser->getTokenArray()->getIndex();
    // Check condition
    while ((bool) condition->calculate()) {
        // go to the start of the loop
        parser->getTokenArray()->moveTo(startPosition);
        // Run commands
        parser->parse();
    }
    // skip to the next end token '}'
    parser->getTokenArray()->skipToNextEnd();
    delete (condition);
}
