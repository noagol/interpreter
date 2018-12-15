//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H
#define PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H

#include <CommandTable.h>
#include "Command.h"
#include "../expressions/TokenArray.h"

class AssignmentCommand : public Command {
public:
    void doCommand() override {
        string varName = TokenArray::getInstance()->get(TokenArray::getInstance()->getIndex() - 2);
        if (!SymbolTable::getInstance()->exists(varName)) {
            throw ParserException("Variable is not defined");
        }

        string token = TokenArray::getInstance()->next();
        if (CommandTable::getInstance()->exists(token)) {
            Expression *command = CommandTable::getInstance()->get(token);
            command->calculate();
        } else {
            Expression *expression = ExpressionParser::parse(token);
            SymbolTable::getInstance()->add(varName, expression->calculate());
            delete (expression);
        }
    }
};

#endif //PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H
