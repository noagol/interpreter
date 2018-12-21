//
// Created by EB on 20/12/2018.
//

#ifndef PROJECT_ADVANCED_TOKENMERGER_H
#define PROJECT_ADVANCED_TOKENMERGER_H

#include <vector>
#include "Token.h"
#include "../expressions/TokenArray.h"
#include "../exceptions/LexerException.h"
#include "../helpers/StringHelpers.h"

using namespace std;

class TokenMerger {
    vector<Token> *tokens;
    unsigned long int pos;
    TokenArray *tokenArray;
    Token lastToken;
    Token currentToken;
    Token nextToken;
public:
    TokenMerger(vector<Token> *unmergedTokens, TokenArray *ta);

    void merge();

    string getNextToken();

    string readExpression();

    bool isSingleToken();

    bool isExpressionTerminator(Token &token);

    Token getFromOffset(int i);

    void updateTokens();

    void advance();

    ~TokenMerger();
};

#endif //PROJECT_ADVANCED_TOKENMERGER_H
