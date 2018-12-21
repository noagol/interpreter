#include "ParserException.h"

/**
 * Create Parser Exception object
 * @param msg exception message
 */
ParserException::ParserException(const char *msg) : message(msg) {}

/**
 * Create Parser Exception object
 * @param msg exception message
 */
ParserException::ParserException(const string msg) : message(msg) {}

/**
 * Gets the message of the exception
 */
const char *ParserException::what() const throw() {
    return message.c_str();
}