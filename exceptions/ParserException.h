//
// Created by EB on 14/12/2018.
//

#ifndef PROJECT_ADVANCED_COMPILATIONEXCEPTION_H

#include <exception>

using namespace std;

#define PROJECT_ADVANCED_COMPILATIONEXCEPTION_H


class ParserException : public exception {
    const string message;
public:
    ParserException(const char *msg) : message(msg) {}

    ParserException(const string msg) : message(msg) {}


    const char *what() const throw() {
        return message.c_str();
    }
};

#endif //PROJECT_ADVANCED_COMPILATIONEXCEPTION_H
