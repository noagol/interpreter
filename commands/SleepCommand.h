
#ifndef PROJECT_ADVANCED_SLEEPCOMMAND_H

#include "BaseCommand.h"
#include "../exceptions/CommandException.h"
#include <chrono>
#include <thread>
#include <stdexcept>

#define PROJECT_ADVANCED_SLEEPCOMMAND_H


class SleepCommand : public BaseCommand {
public:
    SleepCommand(Parser *p);

    void doCommand() override;
};

#endif //PROJECT_ADVANCED_SLEEPCOMMAND_H
