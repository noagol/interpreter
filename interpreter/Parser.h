#ifndef ADVANCED_PARSER_H
#define ADVANCED_PARSER_H

#include "../tables/CommandTable.h"
#include "../tables/SymbolTable.h"
#include "../tables/BindTable.h"

#include "../expressions/TokenArray.h"
#include "../helpers/StringHelpers.h"

using namespace std;

class Parser {
    CommandTable *commandTable;
    BindTable *bindTable;
    SymbolTable *symbolTable;
    TokenArray *tokenArray;
public:
    Parser(TokenArray *ta, CommandTable *ct, BindTable *bt, SymbolTable *st) :
            commandTable(ct),
            bindTable(bt),
            symbolTable(st),
            tokenArray(ta) {}

    void parse() {
        while (!tokenArray->isFinished() && tokenArray->peek() != "}") {
            parseCommand();
        }
    }

    bool parseCommand() {
        string token = tokenArray->next();
        if (isCommand(token)) {
            Expression *command = commandTable->get(token);
            command->calculate();
        } else if (isVariable(token)) {
            string nextToken = tokenArray->next();
            if (nextToken == "=") {
                Expression *command = commandTable->get(nextToken);
                command->calculate();
            } else {
                throw ParserException(format("Undefined command given: %s %s", token, nextToken));
            }
        } else {
            throw ParserException(format("Undefined token: %s", token));
        }
    }

    Expression *getNextExpression() {
        return tokenArray->getNextExpression();
    }


    bool isCommand(string &key) {
        return commandTable->exists(key);
    }

    bool isVariable(string &key) {
        return symbolTable->exists(key);
    }

    CommandTable *getCommandTable() {
        return commandTable;
    }

    BindTable *getBindTable() {
        return bindTable;
    }

    SymbolTable *getSymbolTable() {
        return symbolTable;
    }

    TokenArray *getTokenArray() {
        return tokenArray;
    }

    ~Parser() {
        delete commandTable;
        delete symbolTable;
        delete bindTable;
    }
};


#endif //ADVANCED_PARSER_H