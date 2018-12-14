#ifndef ADVANCED_COMMANDTABLE_H

#define PRINT_COMMAND "print"
#define SLEEP_COMMAND "sleep"
#define OPEN_DATA_SERVER_COMMAND "openDataServer"

#include <SleepCommand.h>
#include <PrintCommand.h>
#include "Table.h"
#include "../commands/Command.h"
#include "../commands/OpenServerCommand.h"

using namespace std;

#define ADVANCED_COMMANDTABLE_H


class CommandTable : public Table<Command> {
    static CommandTable *instance;
public:
    CommandTable() {
        add(OPEN_DATA_SERVER_COMMAND, new OpenServerCommand());
        add(SLEEP_COMMAND, new SleepCommand());
        add(PRINT_COMMAND, new PrintCommand());
    };

    static CommandTable *getInstance() {
        if (!instance) {
            instance = new CommandTable();
            return instance;
        } else {
            return instance;
        }
    }
};

CommandTable *CommandTable::instance = nullptr;

#endif //ADVANCED_COMMANDTABLE_H
