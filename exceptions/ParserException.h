//
// Created by EB on 14/12/2018.
//

#ifndef PROJECT_ADVANCED_COMPILATIONEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

#define PROJECT_ADVANCED_COMPILATIONEXCEPTION_H


class ParserException : public exception {
    const string message;
public:
    ParserException(const char *msg);

    ParserException(const string msg);

    const char *what() const throw();
};

#endif //PROJECT_ADVANCED_COMPILATIONEXCEPTION_H
