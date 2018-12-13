#ifndef ADVANCED_COMMANDTABLE_H
#define ADVANCED_COMMANDTABLE_H

#include "Table.h"
#include "../commands/Command.h"
#include "../commands/OpenServerCommand.h"

using namespace std;

class CommandTable : public Table<Command> {
public:
    CommandTable() {
        
        string openDataServer = "openDataServer";
        OpenServerCommand c = OpenServerCommand();
        //add(openDataServer, OpenServerCommand());
    };
};

#endif //ADVANCED_COMMANDTABLE_H
