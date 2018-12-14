#ifndef ADVANCED_PARSER_H
#define ADVANCED_PARSER_H

#include <vector>
#include <string>
#include "../tables/CommandTable.h"
#include "../tables/SymbolTable.h"
#include "../expressions/ExpressionParser.h"
#include "../tokens/CommandToken.h"
#include "../tokens/SymbolToken.h"
#include "../tokens/StringToken.h"
#include "../tokens/DoubleToken.h"
#include "../expressions/TokenArray.h"

using namespace std;

class Parser {
public:
    Parser() {}

    static void parse() {
        while (!TokenArray::getInstance()->isFinished()) {
            parseCommand();
        }
    }

    static bool parseCommand() {
        string token = TokenArray::getInstance()->next();
        if (isCommand(token)) {
            Command *command = CommandTable::getInstance()->get(token);
            int incBy = command->doCommand();
            TokenArray::getInstance()->move(incBy);
        }
    }

    static bool isCommand(string &key) {
        return CommandTable::getInstance()->exists(key);
    }
};


#endif //ADVANCED_PARSER_H