//
// Created by EB on 26/12/2018.
//

#ifndef PROJECT_ADVANCED_EXITEXCEPTION_H
#define PROJECT_ADVANCED_EXITEXCEPTION_H


#include <exception>
#include <string>

using namespace std;

class ExitException : public exception {
    const string message;
    const int exitCode;
public:
    ExitException(const char *msg, int code);

    ExitException(const string msg, int code);

    const char *what() const throw();
};


#endif //PROJECT_ADVANCED_EXITEXCEPTION_H
