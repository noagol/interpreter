#ifndef ADVANCED_OPENSERVERCOMMAND_H
#define ADVANCED_OPENSERVERCOMMAND_H
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "Command.h"
#include <thread>

class OpenServerCommand : public Command{
public:
    int doCommand(vector<string>* params) override {
        // Validate
        if (params->size() != 2){
            throw invalid_argument("Bad number of inputs to OpenServerCommand");
        }

        // Extract params
        int port = stoi(params->at(1));
        int timesPerSecond = stoi(params->at(2));
        runServer(port, timesPerSecond);
        return 3;
    }

    void runServer(int port, int timesPerSecond){
        int server;
        struct sockaddr_in address;

        // Creating socket file descriptor
        server = socket(AF_INET, SOCK_STREAM, 0);

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( port );

        // Forcefully attaching socket to the port 8080
        bind(server, (struct sockaddr *)&address,
             sizeof(address));

        // Run thread
//        thread serverThread(handleRequests, server, &address);

    }

    static void handleRequests(int server, struct sockaddr_in *address){
        // The value read from the socket
        int valueRead;

        // Client socket identifier
        int clientSocket;

        // Address length
        int addrlen = sizeof(address);

        // For debug
//        char *hello = "Hello from server";
//        char buffer[1024] = {0};
//        listen(server, 5);
//        while (true){
//            // accepting a client
//            clientSocket = accept(server, (struct sockaddr *)address,
//                                (socklen_t*)&addrlen);
//
//            valueRead = read( clientSocket , buffer, 1024);
//            printf("%s\n",buffer );
//            send(clientSocket , hello , strlen(hello) , 0 );
//            printf("Hello message sent\n");
//        }

    }
};


#endif //ADVANCED_OPENSERVERCOMMAND_H
