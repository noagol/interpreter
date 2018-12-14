//
// Created by EB on 14/12/2018.
//

#ifndef PROJECT_ADVANCED_COMPILATIONEXCEPTION_H

#include <exception>

using namespace std;

#define PROJECT_ADVANCED_COMPILATIONEXCEPTION_H


class CompilationException : public exception {
    const char *message;
public:
    CompilationException(const char *msg) : message(msg) {}

    const char *what() const throw() {
        return message;
    }
};

#endif //PROJECT_ADVANCED_COMPILATIONEXCEPTION_H
