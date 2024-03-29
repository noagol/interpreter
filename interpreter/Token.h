//
// Created by EB on 18/12/2018.
//

#ifndef PROJECT_ADVANCED_TOKEN_H
#define PROJECT_ADVANCED_TOKEN_H

#include <string>

enum TOKEN_TYPE {
    UNKNOWN, NAME, NUMBER, BINARY_OPERATOR,
    ASSIGNMENT_OPERATOR, STRING,
    START_CODE_BLOCK, END_CODE_BLOCK,
    START_OPERATOR, END_OPERATOR,
    START_OF_INPUT, END_OF_INPUT, COMMAND
};

using namespace std;

class Token {
    TOKEN_TYPE type;
    string value;
public:
    Token();

    Token(TOKEN_TYPE t, const string &v);

    TOKEN_TYPE getType() const;

    const string getValue() const;
};

#endif //PROJECT_ADVANCED_TOKEN_H
