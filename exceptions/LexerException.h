//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_BASEEXCEPTION_H

#include <exception>

using namespace std;

#define PROJECT_ADVANCED_BASEEXCEPTION_H


class LexerException : public exception {
    const char *message;
public:
    LexerException(const char *msg) : message(msg) {}

    const char *what() const throw() {
        return message;
    }
};

#endif //PROJECT_ADVANCED_BASEEXCEPTION_H
