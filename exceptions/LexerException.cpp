#include "LexerException.h"

/**
 * Create Lexer Exception object
 * @param msg exception message
 */
LexerException::LexerException(const char *msg) : message(msg) {}

/**
 * Create Lexer Exception object
 * @param msg exception message
 */
LexerException::LexerException(const string msg) : message(msg) {}

/**
 * Gets the message of the exception
 */
const char *LexerException::what() const throw() {
    return message.c_str();
}