//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H
#define PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H

#include <CommandTable.h>
#include "Command.h"
#include "../expressions/TokenArray.h"
#include "BaseCommand.h"

class AssignmentCommand : public BaseCommand {
public:
    AssignmentCommand(Parser *p) : BaseCommand(p) {};

    void doCommand() override {
        string varName = parser->getTokenArray()->getFrom(-2);
        if (!parser->getSymbolTable()->exists(varName)) {
            throw ParserException("Variable is not defined");
        }

        string token = parser->getTokenArray()->next();
        if (parser->getCommandTable()->exists(token)) {
            Expression *command = parser->getCommandTable()->get(token);
            command->calculate();
        } else {
            Expression *expression = parser->getTokenArray()->getExpression(token);
            parser->getSymbolTable()->add(varName, expression->calculate());
            delete (expression);
        }
    }
};

#endif //PROJECT_ADVANCED_ASSIGNMENTCOMMAND_H
