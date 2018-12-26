#ifndef ADVANCED_COMMANDTABLE_H
#define ADVANCED_COMMANDTABLE_H

#include "DynamicTable.h"
#include "../commands/Command.h"
#include "../expressions/Expression.h"

#define PRINT_COMMAND "print"
#define SLEEP_COMMAND "sleep"
#define OPEN_DATA_SERVER_COMMAND "openDataServer"
#define VAR_COMMAND "var"
#define ASSIGNMENT_COMMAND "="
#define BIND_COMMAND "bind"
#define IF_COMMAND "if"
#define WHILE_COMMAND "while"
#define CONNECT_COMMAND "connect"
#define EXIT_COMMAND "exit"


using namespace std;

class CommandTable : public DynamicTable<Expression> {
public:
    CommandTable() {};
};

#endif //ADVANCED_COMMANDTABLE_H
