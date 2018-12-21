//
// Created by EB on 21/12/2018.
//

#ifndef PROJECT_ADVANCED_VALIDATOR_H
#define PROJECT_ADVANCED_VALIDATOR_H

#include <string>

using namespace std;

static bool isStartOperator(char c) {
    return c == '(' || c == '!' || c == '-';
}

static bool isEndOperator(char c) {
    return c == ')';
}

static bool isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

static bool isBinaryOperator(char c) {
    return c == '<' || c == '>' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/';
}

static bool isStartOrEnd(char c) {
    return c == '{' || c == '}';
}

static bool isOperator(char c) {
    return isBinaryOperator(c) || isStartOperator(c) || isEndOperator(c);
}

static bool isNameBreaker(char c) {
    return isOperator(c) || c == ',' || isWhitespace(c);
}

static bool isVariableStart(char c) {
    return isalpha(c) || c == '_';
}


#endif //PROJECT_ADVANCED_VALIDATOR_H
