//
// Created by noa on 21/12/2018.
//

#ifndef PROJECT_ADVANCED_COMMANDEXCEPTION_H
#define PROJECT_ADVANCED_COMMANDEXCEPTION_H

#include <exception>

using namespace std;

class CommandException : public exception {
    const string message;
public:
    CommandException(const char *msg) : message(msg) {}

    CommandException(const string msg) : message(msg) {}


    const char *what() const throw() {
        return message.c_str();
    }
};

#endif //PROJECT_ADVANCED_COMMANDEXCEPTION_H
