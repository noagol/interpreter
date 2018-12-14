

#ifndef ADVANCED_COMMAND_H
#define ADVANCED_COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual int doCommand() = 0;
};

#endif //ADVANCED_COMMAND_H