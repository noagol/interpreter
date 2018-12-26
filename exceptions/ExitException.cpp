//
// Created by EB on 26/12/2018.
//

#include "ExitException.h"
#include "../helpers/StringHelpers.h"


/**
 * Create Exit Exception object
 * @param msg exception message
 */
ExitException::ExitException(const char *msg, int code) : message(msg), exitCode(code) {}

/**
 * Create Exit Exception object
 * @param msg exception message
 */
ExitException::ExitException(const string msg, int code) : message(msg), exitCode(code) {}

/**
 * Gets the message of the exception
 */
const char *ExitException::what() const throw() {
    return format("%s\nExit code: %d", message, exitCode).c_str();
}