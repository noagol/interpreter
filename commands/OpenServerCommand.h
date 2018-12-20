#ifndef ADVANCED_OPENSERVERCOMMAND_H
#define ADVANCED_OPENSERVERCOMMAND_H

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include "BaseCommand.h"


class OpenServerCommand : public BaseCommand {
public:
    OpenServerCommand(Parser *p) : BaseCommand(p) {}

    void doCommand() override {
        // Extract params
        Expression *portExp = parser->getNextExpression();
        int port = (int) portExp->calculate();
        delete (portExp);

        Expression *hzExp = parser->getNextExpression();
        int timesPerSecond = (int) hzExp->calculate();
        delete (hzExp);

        // Run the server
        thread serverThread(runServer, port, timesPerSecond);
        serverThread.detach();
    }

    static void runServer(int port, int timesPerSecond) {
        int sockfd, newsockfd, portno, clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;

        /* First call to socket() function */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        /* Initialize socket structure */
        bzero((char *) &serv_addr, sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);

        /* Now bind the host address using bind() call.*/
        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR on binding");
            exit(1);
        }

        /* Now start listening for the clients, here process will
           * go in sleep mode and will wait for the incoming connection
        */

        listen(sockfd, 5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

        while (true) {
            /* Accept actual connection from the client */

            if (newsockfd < 0) {
                perror("ERROR on accept");
                exit(1);
            }

            /* If connection is established then start communicating */
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);

            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }

            printf("Here is the message: %s\n", buffer);
        }
    }


//    void runServer(int port, int timesPerSecond) {
//        int server;
//        struct sockaddr_in address;
//
//        // Creating socket file descriptor
//        server = socket(AF_INET, SOCK_STREAM, 0);
//
//        address.sin_family = AF_INET;
//        address.sin_addr.s_addr = INADDR_ANY;
//        address.sin_port = htons(port);
//
//        // Forcefully attaching socket to the port 8080
//        bind(server, (struct sockaddr *) &address,
//             sizeof(address));
//
//        // Run thread
//        thread serverThread(handleRequests, server, &address, timesPerSecond);
//        serverThread.detach();
//    }
//
//    static void handleRequests(int server, struct sockaddr_in *address, int timesPerSecond) {
//        // The value read from the socket
//        int valueRead;
//
//        // Client socket identifier
//        int clientSocket;
//
//        // Address length
//        int addrlen = sizeof(address);
//
//        // For debug
//        char buffer[1024] = {0};
//        listen(server, 5);
//        while (true) {
//            sleep(1 / timesPerSecond);
//            // accepting a client
//            clientSocket = accept(server, (struct sockaddr *) address,
//                                  (socklen_t *) &addrlen);
//
//            valueRead = read(clientSocket, buffer, 1024);
//            printf("%s\n", buffer);
//        }
//
//    }
};


#endif //ADVANCED_OPENSERVERCOMMAND_H
