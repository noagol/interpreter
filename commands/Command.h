
#ifndef ADVANCED_COMMAND_H

#include <string>
#include <vector>

using namespace std;
#define ADVANCED_COMMAND_H

/**
 * Command interface
 */
class Command {
public:
    /**
     * execute a command
     */
    virtual void doCommand() = 0;

    /**
     * Destroy object
     */
    virtual ~Command() {}
};

#endif //ADVANCED_COMMAND_H