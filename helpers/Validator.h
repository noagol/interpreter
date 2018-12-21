//
// Created by EB on 21/12/2018.
//

#ifndef PROJECT_ADVANCED_VALIDATOR_H
#define PROJECT_ADVANCED_VALIDATOR_H

#include <string>

using namespace std;

/**
 * @param c character
 * @return true if c is start operator
 */
static bool isStartOperator(char c) {
    return c == '(' || c == '!' || c == '-';
}

/**
 * @param c character
 * @return true if c is end operator
 */
static bool isEndOperator(char c) {
    return c == ')';
}

/**
 * @param c character
 * @return true if c is white space
 */
static bool isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v';
}

/**
 * @param c character
 * @return true if c is binary operator
 */
static bool isBinaryOperator(char c) {
    return c == '<' || c == '>' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/';
}

/**
 * @param c character
 * @return true if c is { or }
 */
static bool isStartOrEnd(char c) {
    return c == '{' || c == '}';
}

/**
 * @param c character
 * @return true if c is operator
 */
static bool isOperator(char c) {
    return isBinaryOperator(c) || isStartOperator(c) || isEndOperator(c);
}

/**
 * @param c character
 * @return true if c is name breaker
 */
static bool isNameBreaker(char c) {
    return isOperator(c) || c == ',' || isWhitespace(c);
}

/**
 * @param c character
 * @return true if c is variable start character
 */
static bool isVariableStart(char c) {
    return isalpha(c) || c == '_';
}


#endif //PROJECT_ADVANCED_VALIDATOR_H
