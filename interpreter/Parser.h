#ifndef ADVANCED_PARSER_H
#define ADVANCED_PARSER_H

#include <vector>
#include <string>
#include "../tables/CommandTable.h"
#include "../tables/SymbolTable.h"
#include "../expressions/ExpressionParser.h"
#include "../expressions/TokenArray.h"

using namespace std;

class Parser {
public:
    Parser() {}

    void parseUntil(string endSign) {
        while (!TokenArray::getInstance()->isFinished() || TokenArray) {
            parseCommand();
        }
    }

    void parse() {
        while (!TokenArray::getInstance()->isFinished()) {
            parseCommand();
        }
    }

    bool parseCommand() {
        string token = TokenArray::getInstance()->next();
        if (isCommand(token)) {
            Expression *command = CommandTable::getInstance()->get(token);
            command->calculate();
        }
    }

    bool isCommand(string &key) {
        return CommandTable::getInstance()->exists(key);
    }
};


#endif //ADVANCED_PARSER_H