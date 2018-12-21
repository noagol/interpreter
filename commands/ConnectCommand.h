//
// Created by noa on 18/12/2018.
//

#ifndef PROJECT_ADVANCED_CONNECTCOMMAND_H

#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include "BaseCommand.h"

#define RETRIES_COUNT 100
#define RETRIES_SLEEP 2

#define PROJECT_ADVANCED_CONNECTCOMMAND_H


class ConnectCommand : public BaseCommand {
    static bool shouldStop;
public:
    ConnectCommand(Parser *p) : BaseCommand(p) {
    }

    void doCommand() override {
        string ip = parser->getTokenArray()->next();

        Expression *portExp = parser->getNextExpression();
        int port = (int) portExp->calculate();
        delete (portExp);
        if (1 > port || port > 65535) {
            throw CommandException(format("Port value out of range: %d", port));
        }

        thread clientThread(runClient, ip, port, parser->getSymbolTable(), parser->getBindTable());
        clientThread.detach();
    }

    static void runClient(string ip, int port, SymbolTable *symbolTable, BindTable *bindTable) {
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        /* Create a socket point */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        server = gethostbyname(ip.c_str());

        if (server == NULL) {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(port);

        /* Now connect to the server */
        int tries = 0;

        while (tries < RETRIES_COUNT) {
            if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) >= 0) {
                break;
            }
            sleep(RETRIES_SLEEP);
            tries++;
        }
        // If we were unable to connect
        if (tries == RETRIES_COUNT - 1) {
            perror("Unable to connect");
            exit(1);
        }

        vector<string> changes;
        vector<string>::iterator it;
        string updateMessage;
        while (!shouldStop) {
            if (symbolTable->areThereAnyChanges()) {
                changes = symbolTable->getChangedKeys();

                for (it = changes.begin(); it != changes.end(); it++) {
                    if (bindTable->variableExists(*it)) {
                        updateMessage = format("set %s %f\r\n", bindTable->getPathByVariable(*it),
                                               symbolTable->get(*it));
                        n = write(sockfd, updateMessage.c_str(), updateMessage.size());

                        // Check if message sent
                        if (n < 0) {
                            perror("ERROR writing to socket");
                            exit(1);
                        }
                    }
                }
            }
            this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 250));
        }
    }

    static void stop() {
        shouldStop = true;
    }

};

bool ConnectCommand::shouldStop = false;


#endif //PROJECT_ADVANCED_CONNECTCOMMAND_H
