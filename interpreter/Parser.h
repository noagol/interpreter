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
    Parser(TokenArray *ta, CommandTable *ct, BindTable *bt, SymbolTable *st);

    void parse();

    bool parseCommand();

    Expression *getNextExpression();

    bool isCommand(string &key);

    bool isVariable(string &key);

    CommandTable *getCommandTable();

    BindTable *getBindTable();

    SymbolTable *getSymbolTable();

    TokenArray *getTokenArray();

    ~Parser();
};


#endif //ADVANCED_PARSER_H