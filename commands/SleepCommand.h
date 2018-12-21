//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_SLEEPCOMMAND_H

#include "BaseCommand.h"
#include "../exceptions/CommandException.h"
#include <chrono>
#include <thread>
#include <stdexcept>

#define PROJECT_ADVANCED_SLEEPCOMMAND_H


class SleepCommand : public BaseCommand {
public:
    SleepCommand(Parser *p) : BaseCommand(p) {}

    void doCommand() override {
        // Parse expression
        Expression *expression = parser->getNextExpression();
        if (expression == nullptr) {
            throw CommandException("Not enough arguments for sleep command. Expected 1, 0 given");
        }
        int sleepTime = (int) expression->calculate();
        // Remove allocated memory
        delete (expression);

        // Validate
        if (sleepTime < 0) {
            // Invalid sleep time
            throw CommandException(format("Negative time for sleep: %d", sleepTime));
        }

        // Sleep
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) sleepTime));
    }
};

#endif //PROJECT_ADVANCED_SLEEPCOMMAND_H
