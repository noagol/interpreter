#ifndef ADVANCED_PARSER_H
#define ADVANCED_PARSER_H

#include <vector>
#include <string>
#include "../tables/CommandTable.h"
#include "../tables/SymbolTable.h"
#include "../expressions/ExpressionParser.h"
#include "../expressions/TokenArray.h"
#include "../helpers/StringHelpers.h"

using namespace std;

class Parser {
public:
    Parser() {}

    void parse() {
        while (!TokenArray::getInstance()->isFinished() && TokenArray::getInstance()->peek() != "}") {
            parseCommand();
        }
    }

    bool parseCommand() {
        string token = TokenArray::getInstance()->next();
        if (isCommand(token)) {
            Expression *command = CommandTable::getInstance()->get(token);
            command->calculate();
        } else if (isVariable(token)) {
            string nextToken = TokenArray::getInstance()->next();
            if (nextToken == "=") {
                Expression *command = CommandTable::getInstance()->get(nextToken);
                command->calculate();
            } else {
                throw ParserException(format("Undefined command given: %s %s", token, nextToken));
            }
        } else {
            throw ParserException(format("Undefined token: %s", token));
        }
    }


    bool isCommand(string &key) {
        return CommandTable::getInstance()->exists(key);
    }

    bool isVariable(string &key) {
        return SymbolTable::getInstance()->exists(key);
    }
};


#endif //ADVANCED_PARSER_H