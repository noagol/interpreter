#ifndef ADVANCED_OPENSERVERCOMMAND_H
#define ADVANCED_OPENSERVERCOMMAND_H

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include "BaseCommand.h"
#include "../exceptions/CommandException.h"
#include <string>


class OpenServerCommand : public BaseCommand {
    static bool shouldStop;
public:
    OpenServerCommand(Parser *p);

    void doCommand() override;

    static void runServer(int port, int timesPerSecond,
                                      BindTable *bindTable, SymbolTable *symbolTable) ;

    static void updateVariables(string updateData, BindTable *bindTable,
                                SymbolTable *symbolTable);

    static void stop();
};



#endif //ADVANCED_OPENSERVERCOMMAND_H
