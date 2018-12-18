//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_SLEEPCOMMAND_H

#include "BaseCommand.h"
#include <chrono>
#include <thread>
#include <stdexcept>

#define PROJECT_ADVANCED_SLEEPCOMMAND_H


class SleepCommand : public BaseCommand {
public:
    SleepCommand(Parser* p):BaseCommand(p) {}

    void doCommand() override {
        // Parse expression
        Expression *expression = parser->getNextExpression();
        int sleepTime = (int) expression->calculate();

        // Remove allocated memory
        delete (expression);

        if (sleepTime < 0) {
            // Invalid sleep time
            throw invalid_argument("Negative time for sleep");
        }

        // Sleep
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) sleepTime));
    }
};

#endif //PROJECT_ADVANCED_SLEEPCOMMAND_H
