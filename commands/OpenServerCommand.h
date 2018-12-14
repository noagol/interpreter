#ifndef ADVANCED_OPENSERVERCOMMAND_H
#define ADVANCED_OPENSERVERCOMMAND_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "Command.h"
#include <pthread.h>
#include "../expressions/ExpressionParser.h"
#include "../expressions/TokenArray.h"

class OpenServerCommand : public Command {
public:
    int doCommand() override {
        // Extract params
        Expression *portExp = ExpressionParser::parse(TokenArray::getInstance()->next());
        int port = (int) portExp->calculate();
        delete (portExp);

        Expression *hzExp = ExpressionParser::parse(TokenArray::getInstance()->next());
        int timesPerSecond = (int) hzExp->calculate();
        delete (hzExp);

        // Run the server
        runServer(port, timesPerSecond);
        return 0;
    }

    void runServer(int port, int timesPerSecond) {
        int server;
        struct sockaddr_in address;

        // Creating socket file descriptor
        server = socket(AF_INET, SOCK_STREAM, 0);

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        // Forcefully attaching socket to the port 8080
        bind(server, (struct sockaddr *) &address,
             sizeof(address));

        // Run thread
        thread serverThread(handleRequests, server, &address, timesPerSecond);
    }

    static void handleRequests(int server, struct sockaddr_in *address, int timesPerSecond) {
        // The value read from the socket
        int valueRead;

        // Client socket identifier
        int clientSocket;

        // Address length
        int addrlen = sizeof(address);

        // For debug
        char buffer[1024] = {0};
        listen(server, 5);
        while (true) {
            sleep(1 / timesPerSecond);
            // accepting a client
            clientSocket = accept(server, (struct sockaddr *) address,
                                  (socklen_t *) &addrlen);

            valueRead = read(clientSocket, buffer, 1024);
            printf("%s\n", buffer);
        }

    }
};


#endif //ADVANCED_OPENSERVERCOMMAND_H
