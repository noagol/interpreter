//
// Created by noa on 18/12/2018.
//

#ifndef PROJECT_ADVANCED_CONNECTCOMMAND_H

#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include "BaseCommand.h"

#define PROJECT_ADVANCED_CONNECTCOMMAND_H


class ConnectCommand : public BaseCommand {
public:
    ConnectCommand(Parser *p) : BaseCommand(p) {}

    void doCommand() override {
        string ip = parser->getTokenArray()->next();

        Expression *portExp = parser->getNextExpression();
        int port = (int) portExp->calculate();
        delete (portExp);
        runClient(ip, port);
    }

    void runClient(string ip, int port) {
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        char buffer[256];

        /* Create a socket point */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        server = gethostbyname(ip.c_str());

        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);

        /* Now connect to the server */
        if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR connecting");
            exit(1);
        }

        /* Now ask for a message from the user, this message
           * will be read by server
        */

        printf("Please enter the message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);

        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        /* Now read server response */
        bzero(buffer,256);
        n = read(sockfd, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("%s\n",buffer);
    }

};


#endif //PROJECT_ADVANCED_CONNECTCOMMAND_H
