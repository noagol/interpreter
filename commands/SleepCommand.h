//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_SLEEPCOMMAND_H

#include "Command.h"
#include <chrono>
#include <thread>
#include <stdexcept>

#define PROJECT_ADVANCED_SLEEPCOMMAND_H


class SleepCommand : public Command {
public:
    SleepCommand() {}

    int doCommand(vector<string> *params) override {
        // exp = Diextra(params[0])
        // sleep(exp.calculate())
        int sleepTime = stoi(params->at(1));
        if (sleepTime < 0) {
            throw invalid_argument("Negative time for sleep");
        } else {
            this_thread::sleep_for(std::chrono::milliseconds((unsigned int) sleepTime));
        }
    }
};

#endif //PROJECT_ADVANCED_SLEEPCOMMAND_H
