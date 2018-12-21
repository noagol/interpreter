//
// Created by noa on 21/12/2018.
//

#ifndef PROJECT_ADVANCED_COMMANDEXCEPTION_H
#define PROJECT_ADVANCED_COMMANDEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class CommandException : public exception {
    const string message;
public:
    CommandException(const char *msg);

    CommandException(const string msg);


    const char *what() const throw();
};

#endif //PROJECT_ADVANCED_COMMANDEXCEPTION_H
