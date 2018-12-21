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

using namespace std;

class Lexer {
    string input;
    unsigned long int pos;
    char currentChar;
    Token currentToken;
    Token lastToken;
    TokenArray *tokenArray;

public:
    Lexer(TokenArray *ta, const string &inputStr) : tokenArray(ta), input(inputStr), pos(0),
                                                    currentToken(), lastToken() {
        currentChar = inputStr.at(pos);
    }


    void lex() {
        TokenMerger tokenMerger = TokenMerger(readTokens(), tokenArray);
        tokenMerger.merge();
    }


    vector<Token> *readTokens() {
        vector<Token> *tokens = new vector<Token>;
        while (this->currentChar != '\0') {
            lastToken = currentToken;
            currentToken = getNextToken();
            if (currentToken.getType() != END_OF_INPUT) {
                tokens->push_back(currentToken);
            }
        }
        return tokens;
    }

    void advance() {
        pos++;
        if (this->pos > input.size() - 1) {
            // End of input
            this->currentChar = '\0';
        } else {
            this->currentChar = input.at(pos);
        }
    }

    void skipWhitespaces() {
        while (this->currentChar != '\0' && isWhitespace(this->currentChar)) {
            advance();
        }
    }

    string readInteger() {
        string token;
        while (this->currentChar != '\0' && isdigit(this->currentChar)) {
            token.push_back(this->currentChar);
            advance();
        }
        return token;
    }

    string readName() {
        string token;
        while (this->currentChar != '\0' && !isNameBreaker(this->currentChar)) {
            token.push_back(this->currentChar);
            advance();
        }
        return token;
    }


    string readBinaryOperator() {
        string token;
        while (this->currentChar != '\0' && isBinaryOperator(this->currentChar)) {
            token.push_back(this->currentChar);
            advance();
        }
        return token;
    }

    string readStartOperator() {
        string token;
        while (this->currentChar != '\0' && isStartOperator(this->currentChar)) {
            token.push_back(this->currentChar);
            advance();
        }
        return token;
    }


    string readEndOperator() {
        string token;
        while (this->currentChar != '\0' && isEndOperator(this->currentChar)) {
            token.push_back(this->currentChar);
            advance();
        }
        return token;
    }

    string readString() {
        string token;
        // Read the first '"'
        token.push_back(this->currentChar);
        advance();

        // Read the characters
        while (this->currentChar != '\0' && this->currentChar != '"') {
            token.push_back(this->currentChar);
            advance();
        }

        if (this->currentChar == '"') {
            // Valid string
            token.push_back(this->currentChar);
            advance();
            return token;
        } else {
            // Missing end of string
            throw LexerException(format("Unterminated string expression given %s", token));
        }
    }

    Token readStartOrEnd() {
        string token;
        token.push_back(this->currentChar);
        advance();
        if (this->currentChar == '{') {
            return Token(START_CODE_BLOCK, token);
        } else {
            return Token(END_CODE_BLOCK, token);
        }
    }

    Token getNextToken() {
        while (this->currentChar != '\0') {
            // Handle whitespaces
            if (isWhitespace(this->currentChar)) {
                skipWhitespaces();
                continue;
            }

            // Handle numbers
            if (isdigit(this->currentChar)) {
                int i = 0;
                string token = readInteger();
                while (currentChar == '.') {
                    i++;
                    token += ".";
                    advance();
                    token += readInteger();
                }

                if (i == 0 || i == 1) {
                    // Integer or double
                    return Token(NUMBER, token);
                } else {
                    // Probably ip
                    return Token(STRING, token);
                }
            }

            // Handle variables and commands
            if (isVariableStart(this->currentChar)) {
                string token = readName();
                return Token(NAME, token);
            }

            // Handle operators
            if (isStartOperator(this->currentChar) && lastToken.getType() != NUMBER && lastToken.getType() != NAME) {
                string token = readStartOperator();
                return Token(START_OPERATOR, token);
            }

            if (isBinaryOperator(this->currentChar)) {
                string token = readBinaryOperator();
                if (token == "=") {
                    return Token(ASSIGNMENT_OPERATOR, token);
                } else {
                    return Token(BINARY_OPERATOR, token);
                }
            }


            if (isEndOperator(this->currentChar)) {
                string token = readEndOperator();
                return Token(END_OPERATOR, token);
            }

            // Handle strings
            if (this->currentChar == '"') {
                string token = readString();
                return Token(STRING, token);
            }

            // Handle { }
            if (isStartOrEnd(this->currentChar)) {
                return readStartOrEnd();
            }

            throw LexerException(format("Unknown format given: %s", this->input));
        }

        return Token(END_OF_INPUT, "");
    }


};

#endif //PROJECT_ADVANCED_NEWLEXER_H
