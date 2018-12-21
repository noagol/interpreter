#include "CommandException.h"

/**
 * Create Command Exception object
 * @param msg exception message
 */
CommandException::CommandException(const char *msg) : message(msg) {}

/**
 * Create Command Exception object
 * @param msg exception message
 */
CommandException::CommandException(const string msg) : message(msg) {}

/**
 * Gets the message of the exception
 */
const char *CommandException::what() const throw() {
    return message.c_str();
}