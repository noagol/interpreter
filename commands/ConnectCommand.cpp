#include "ConnectCommand.h"

/**
 * should Stop boolean to end thread
 */
bool ConnectCommand::shouldStop = false;
Status ConnectCommand::status = NOT_CONNECTED;

/**
 * Command class to open client
 * @param p - parser
 */
ConnectCommand::ConnectCommand(Parser *p) : BaseCommand(p) {}

/**
 * Open a new client
 */
void ConnectCommand::doCommand() {
    // get the ip
    string ip = parser->getTokenArray()->next();

    if (!validateIp(ip)) {
        throw CommandException(format("Invalid ip given to connect command: %s", ip));
    }

    // get port number
    Expression *portExp = parser->getNextExpression();
    int port = (int) portExp->calculate();
    delete (portExp);
    // validate
    if (1 > port || port > 65535) {
        throw CommandException(format("Port value out of range: %d", port));
    }
    // open new thread
    thread clientThread(runClient, ip, port, parser->getSymbolTable(), parser->getBindTable());
    clientThread.detach();
}

/**
 * connect to the simulator and update variables
 * @param ip of the server
 * @param port of the server
 * @param symbolTable the symbol table
 * @param bindTable the bind table
 */
void ConnectCommand::runClient(string ip, int port,
                               SymbolTable *symbolTable, BindTable *bindTable) {
    // Set status
    status = CONNECTING;

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    // Create a socket point
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(ip.c_str());

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        close(sockfd);
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    // Now connect to the server
    int tries = 0;

    while (tries < RETRIES_COUNT && !ConnectCommand::shouldStop) {
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) >= 0) {
            break;
        }
        sleep(RETRIES_SLEEP);
        tries++;
    }
    // If we were unable to connect
    if (tries == RETRIES_COUNT - 1) {
        perror("Unable to connect");
        status = NOT_CONNECTED;
        exit(1);
    }

    this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 5000));
    status = CONNECTED;

    // Update the server for changes
    vector<string> changes;
    vector<string>::iterator it;
    string updateMessage;
    while (!ConnectCommand::shouldStop) {
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
                        close(sockfd);
                        status = NOT_CONNECTED;
                        exit(1);
                    }
                }
            }
        }
        // Sleep a little and continue to check for updates
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 250));
    }

    // Close the socket
    close(sockfd);

    status = NOT_CONNECTED;
}

/**
 * Stop running threads
 */
void ConnectCommand::stop() {
    shouldStop = true;
}

Status ConnectCommand::getStatus() {
    return status;
}
