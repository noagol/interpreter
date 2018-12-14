//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_PRINTCOMMAND_H
#define PROJECT_ADVANCED_PRINTCOMMAND_H

#include <iostream>
#include "Command.h"
#include "../expressions/TokenArray.h"
#include "../exceptions/CompilationException.h"
#include "../expressions/ExpressionParser.h"

class PrintCommand : public Command {

public:
    PrintCommand() {}

    int doCommand() override {
        string token = TokenArray::getInstance()->next();

        if (token.at(0) == '\"') {
            // String
            cout << token.substr(1, token.size() - 2) << endl;
        } else {
            // Expression
            Expression *expression = ExpressionParser::parse(token);
            cout << expression->calculate() << endl;
            delete (expression);
        }

        return 0;
//
//        if (type == STRING_TOKEN) {
//            Token<string> s = (Token<string>) t;
//            cout << ((string) t->getValue()) << endl;
//        } else if (type == DOUBLE_TOKEN) {
//            cout << ((double) t->getValue()) << endl;
//        } else {
//            throw CompilationException("Invalid argument for print");
//        }


    }
};

#endif //PROJECT_ADVANCED_PRINTCOMMAND_H
