#ifndef ADVANCED_COMMANDTABLE_H
#define ADVANCED_COMMANDTABLE_H

#include "DynamicTable.h"
#include "../commands/Command.h"
#include "../commands/OpenServerCommand.h"
#include "../expressions/CommandExpression.h"

#define PRINT_COMMAND "print"
#define SLEEP_COMMAND "sleep"
#define OPEN_DATA_SERVER_COMMAND "openDataServer"
#define VAR_COMMAND "var"
#define ASSIGNMENT_COMMAND "="
#define BIND_COMMAND "bind"

using namespace std;

class CommandTable : public DynamicTable<Expression> {
    static CommandTable *instance;
public:
    CommandTable() {

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
