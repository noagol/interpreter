
#ifndef PROJECT_ADVANCED_CONNECTCOMMAND_H

#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include "BaseCommand.h"
#include "../exceptions/CommandException.h"


#define RETRIES_COUNT 100
#define RETRIES_SLEEP 2

#define PROJECT_ADVANCED_CONNECTCOMMAND_H


class ConnectCommand : public BaseCommand {
    static bool shouldStop;
public:
    ConnectCommand(Parser *p);


    void doCommand() override;

    static void runClient(string ip, int port, SymbolTable *symbolTable,
                          BindTable *bindTable);

    static void stop();

};

#endif //PROJECT_ADVANCED_CONNECTCOMMAND_H
