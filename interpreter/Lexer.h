//
// Created by EB on 18/12/2018.
//

#ifndef PROJECT_ADVANCED_NEWLEXER_H
#define PROJECT_ADVANCED_NEWLEXER_H

#include <string>
#include <vector>
#include "Token.h"
#include "../exceptions/LexerException.h"
#include "../helpers/StringHelpers.h"
#include "../expressions/TokenArray.h"
#include "TokenMerger.h"
#include "../helpers/Validator.h"
#include "../tables/CommandTable.h"

using namespace std;

class Lexer {
    string input;
    unsigned long int pos;
    char currentChar;
    Token currentToken;
    Token lastToken;
    TokenArray *tokenArray;
    CommandTable *commandTable;
public:
    Lexer(TokenArray *ta, CommandTable *ct, const string &inputStr);

    void lex();

    vector<Token> *readTokens();

    void advance();

    void skipWhitespaces();

    string readInteger();

    string readName();

    string readBinaryOperator();

    string readStartOperator();

    string readEndOperator();

    string readString();

    Token readStartOrEnd();

    Token getNextToken();

    bool isCommand(const string &str);
};

#endif //PROJECT_ADVANCED_NEWLEXER_H
