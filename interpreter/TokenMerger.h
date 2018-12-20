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
    TokenMerger(vector<Token> *unmergedTokens, TokenArray *ta) : tokens(unmergedTokens), tokenArray(ta), pos(0) {
        updateTokens();
    }

    void merge() {
        while (this->currentToken.getType() != END_OF_INPUT) {
            tokenArray->add(getNextToken());
            advance();
        }
    }

    string getNextToken() {
        if (currentToken.getType() == START_OPERATOR || currentToken.getType() == NUMBER ||
            currentToken.getType() == NAME) {
            return readExpression();
        }

        if (isSingleToken()) {
            return currentToken.getValue();
        }

        throw LexerException("Unable to split to tokens");

    }

    string readExpression() {
        string expression;
        while (this->currentToken.getType() != END_OF_INPUT) {
            if (this->currentToken.getType() == START_OPERATOR || this->currentToken.getType() == END_OPERATOR) {
                // Start operators - e.g. ( ! ...
                expression += this->currentToken.getValue();
                if (isExpressionTerminator(nextToken) && this->currentToken.getType() == END_OPERATOR) {
                    return expression;
                }
            } else if (this->currentToken.getType() == BINARY_OPERATOR) {
                // Binary operators - e.g. * + - ...
                if (this->lastToken.getType() == NUMBER || this->lastToken.getType() == NAME ||
                        lastToken.getType() == START_OPERATOR || lastToken.getType() == END_OPERATOR) {
                    expression += this->currentToken.getValue();
                } else {
                    throw LexerException("Binary operator after not a number or variable");
                }
            } else if (this->currentToken.getType() == NUMBER) {
                // Numbers
                if (isExpressionTerminator(nextToken)) {
                    // Expression is finished here
                    expression += this->currentToken.getValue();
                    return expression;
                } else {
                    // Add to expression
                    expression += this->currentToken.getValue();
                }
            } else if (this->currentToken.getType() == NAME) {
                // Names
                if (isExpressionTerminator(nextToken)) {
                    // Expression is finished here
                    expression += this->currentToken.getValue();
                    return expression;
                } else if (nextToken.getType() == ASSIGNMENT_OPERATOR) {
                    if (expression.empty()) {
                        return currentToken.getValue();
                    } else {
                        throw LexerException("Assign to an expression");
                    }
                }
//                else if (lastToken.getType() == END_OPERATOR || lastToken.getType() == BINARY_OPERATOR) {
//                    // Expression ended
//                    pos--;
//                    updateTokens();
//                    return expression;
//                }
                else {
                    // Add to expression
                    expression += this->currentToken.getValue();
                }
            } else if (this->currentToken.getType() == ASSIGNMENT_OPERATOR) {
                if (lastToken.getType() != NAME || expression.empty()) {
                    throw LexerException("Assign to non name argument");
                }
                return currentToken.getValue();
            } else {
                if (expression.empty()) {
                    throw LexerException("Unable to read expression");
                } else {
                    // Read one too many
                    pos--;
                    updateTokens();
                    return expression;
                }
            }

            advance();
        }

    }

    bool isSingleToken() {
        TOKEN_TYPE type = currentToken.getType();
        return type == START_CODE_BLOCK || type == END_CODE_BLOCK
               || type == STRING || type == ASSIGNMENT_OPERATOR;
    }

    bool isExpressionTerminator(Token &token) {
        return token.getType() == NUMBER || token.getType() == NAME ||
               token.getType() == END_OF_INPUT || token.getType() == STRING;
    }

    Token getFromOffset(int i) {
        if (this->pos + i > tokens->size() - 1) {
            // End of input
            return Token(END_OF_INPUT, "");
        } else if (this->pos + i < 0) {
            // Start of input
            return Token(START_OF_INPUT, "");
        } else {
            // Get the token
            return tokens->at(pos + i);
        }
    }

    void updateTokens() {
        this->lastToken = getFromOffset(-1);
        this->currentToken = getFromOffset(0);
        this->nextToken = getFromOffset(1);
    }

    void advance() {
        pos++;
        updateTokens();
    }

    ~TokenMerger() {
        delete (tokens);
    }

};

#endif //PROJECT_ADVANCED_TOKENMERGER_H
