#include "ConditionParser.h"

/**
 * Base class for condition command
 * @param p - parser
 */
ConditionParser::ConditionParser(Parser *p) : BaseCommand(p) {}

/**
 *
 * @return the condition
 */
Expression *ConditionParser::readCondition() {
    return parser->getNextExpression();
}
