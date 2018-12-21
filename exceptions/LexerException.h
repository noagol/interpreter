//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_BASEEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

#define PROJECT_ADVANCED_BASEEXCEPTION_H


class LexerException : public exception {
    const string message;
public:
    LexerException(const char *msg);

    LexerException(const string msg);

    const char *what() const throw();
};

#endif //PROJECT_ADVANCED_BASEEXCEPTION_H
