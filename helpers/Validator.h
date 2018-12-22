//
// Created by EB on 21/12/2018.
//

#ifndef PROJECT_ADVANCED_VALIDATOR_H
#define PROJECT_ADVANCED_VALIDATOR_H

#include <string>
#include <vector>
#include "StringHelpers.h"

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

/**
 * Check if given string is a numeric string or not
 * @param str input string
 * @return true if a number
 */
static bool isNumber(const string& str) {
    // std::find_first_not_of searches the string for the first character
    // that does not match any of the characters specified in its arguments
    return !str.empty() &&
           (str.find_first_not_of("[0123456789]") == std::string::npos);
}

/**
 * Function to validate an IP address
 * @param ip the ip to check
 * @return true if a valid ip
 */
static bool validateIp(string ip) {
    // split the string into tokens
    vector<string> list = split(&ip, '.');

    // if token size is not equal to four
    if (list.size() != 4)
        return false;

    // validate each token
    for (string str : list) {
        // verify that string is number or not and the numbers
        // are in the valid range
        if (!isNumber(str) || stoi(str) > 255 || stoi(str) < 0)
            return false;
    }

    return true;
}



#endif //PROJECT_ADVANCED_VALIDATOR_H
