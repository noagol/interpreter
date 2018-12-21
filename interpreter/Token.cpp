#include "Token.h"

/**
 * Creates a default empty token
 */
Token::Token() : type(UNKNOWN), value() {}

/**
 * Create a Token object
 * @param t type
 * @param v value
 */
Token::Token(TOKEN_TYPE t, const string &v) : type(t), value(v) {}

/**
 * Get the type
 * @return type
 */
TOKEN_TYPE Token::getType() const {
    return type;
}

/**
 * Get the value
 * @return value
 */
const string Token::getValue() const {
    return value;
}