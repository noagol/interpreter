//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_PRINTCOMMAND_H
#define PROJECT_ADVANCED_PRINTCOMMAND_H

#include <iostream>
#include "BaseCommand.h"
#include "../exceptions/CommandException.h"

class PrintCommand : public BaseCommand {

public:
    PrintCommand(Parser *p) : BaseCommand(p) {}

    void doCommand() override {
        string token = parser->getTokenArray()->next();
        if (token.empty()) {
            throw CommandException("Not enough arguments for print command. Expected 1: 0 given");
        }

        if (token.at(0) == '\"' && token.at(token.size() - 1) == '\"') {
            // String
            cout << token.substr(1, token.size() - 2) << endl;
        } else {
            // Expression
            Expression *expression = parser->getTokenArray()->getExpression(token);
            if (expression == nullptr) {
                throw CommandException(format("Invalid expression for print: %s", token));
            }
            cout << expression->calculate() << endl;
            delete (expression);
        }
    }
};

#endif //PROJECT_ADVANCED_PRINTCOMMAND_H
