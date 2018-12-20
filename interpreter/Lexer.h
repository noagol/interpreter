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
            tokens->push_back(currentToken);
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
                string token = readInteger();
                return Token(NUMBER, token);
            }

            // Handle variables and commands
            if (isalpha(this->currentChar) || this->currentChar == '_') {
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

    }

    bool isStartOrEnd(char c) {
        return c == '{' || c == '}';
    }

    bool isNameBreaker(char c) {
        return isOperator(c) || c == ',' || isWhitespace(c);
    }

    bool isOperator(char c) {
        return isBinaryOperator(c) || isStartOperator(c) || isEndOperator(c);
    }

    bool isBinaryOperator(char c) {
        return c == '<' || c == '>' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/';
    }

    bool isStartOperator(char c) {
        return c == '(' || c == '!' || c == '-';
    }

    bool isEndOperator(char c) {
        return c == ')';
    }

    bool isWhitespace(char c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t';
    }
};

//    void lexer() {
//        string mergedToken;
//        Token lastToken;
//        while (this->currentChar != '\0') {
//            currentToken = getNextToken();
//            if (currentToken.getType() == NAME || currentToken.getType() == NUMBER) {
//                // Handle names
//                if (lastToken.getType() == BINARY_OPERATOR) {
//                    // Part of expression
//                    mergedToken += currentToken.getValue();
//                } else {
//                    // If expression ended here
//                    if (!mergedToken.empty()) {
//                        tokenArray->add(mergedToken);
//                        mergedToken = "";
//                    }
//                    // May be another expression
//                    mergedToken += currentToken.getValue();
//                }
//            } else if (currentToken.getType() == OPERATOR) {
//                if (lastToken.getType() != OPERATOR) {
//                    // Operator as part of expression
//                    mergedToken += currentToken.getValue();
//                } else {
//                    // Two subsequent operators
//                    throw LexerException(format("Two subsequent operators %s", input));
//                }
//            } else if (currentToken.getType() == ASSIGNMENT_OPERATOR) {
//                // Handle assignment operators
//                if (!mergedToken.empty()) {
//                    // Add the value before
//                    tokenArray->add(mergedToken);
//                    // Add the assignment operator '='
//                    tokenArray->add(currentToken.getValue());
//                    // Clear the merged token value
//                    mergedToken = "";
//                } else {
//                    // Assignment to an empty name
//                    throw LexerException(format("Assignment to empty variable %s", input));
//                }
//            } else if (currentToken.getType() == STRING || currentToken.getType() == START_CODE_BLOCK ||
//                       currentToken.getType() == END_CODE_BLOCK) {
//                if (!mergedToken.empty()) {
//                    tokenArray->add(mergedToken);
//                    mergedToken = "";
//                }
//                tokenArray->add(currentToken.getValue());
//            } else {
//                throw LexerException("Unknown token type");
//            }
//            lastToken = currentToken;
//        }
//        if (!mergedToken.empty()) {
//            tokenArray->add(mergedToken);
//        }
//    }


#endif //PROJECT_ADVANCED_NEWLEXER_H
