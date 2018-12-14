//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_SLEEPCOMMAND_H

#include "Command.h"
#include "../expressions/TokenArray.h"
#include <chrono>
#include <thread>
#include <stdexcept>

#define PROJECT_ADVANCED_SLEEPCOMMAND_H


class SleepCommand : public Command {
public:
    SleepCommand() {}

    int doCommand() override {
        // Get sleep argument
        string token = TokenArray::getInstance()->next();

        // Parse expression
        Expression *expression = ExpressionParser::parse(token);
        int sleepTime = (int) expression->calculate();

        // Remove allocated memory
        delete (expression);

        if (sleepTime < 0) {
            // Invalid sleep time
            throw invalid_argument("Negative time for sleep");
        }

        // Sleep
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) sleepTime));

        return 0;
    }
};

#endif //PROJECT_ADVANCED_SLEEPCOMMAND_H
