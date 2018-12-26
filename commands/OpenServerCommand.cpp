#include "OpenServerCommand.h"
#include "ConnectCommand.h"

/**
 * Command class to open server
 * @param p - parser
 */
OpenServerCommand::OpenServerCommand(Parser *p) : BaseCommand(p) {}

/**
 * Should Stop boolean to end thread
 */
bool OpenServerCommand::shouldStop = false;

/**
 * Open a new server
 */
void OpenServerCommand::doCommand() {
    // Port number
    Expression *portExp = parser->getNextExpression();
    // not enough arguments
    if (portExp == nullptr) {
        throw CommandException("Not enough arguments for openServerCommand. Expected: 2, 0 given");
    }
    int port = (int) portExp->calculate();
    delete (portExp);
    // validate
    if (1 > port || port > 65535) {
        throw CommandException(format("Port value out of range: %d", port));
    }

    // Times per second
    Expression *hzExp = parser->getNextExpression();
    // not enough arguments
    if (hzExp == nullptr) {
        throw CommandException("Not enough arguments for openServerCommand. Expected: 2, 1 given");
    }
    int timesPerSecond = (int) hzExp->calculate();
    delete (hzExp);
    // validate
    if (timesPerSecond < 1) {
        throw CommandException(format("Non positive value for hz on open data server: %d", timesPerSecond));
    }
    // Run the server in new thread
    thread serverThread(runServer, port, timesPerSecond, parser->getBindTable(), parser->getSymbolTable());
    serverThread.detach();
}

/**
 * Runs a server
 * @param port the port of the server
 * @param timesPerSecond how many time to read in a second
 * @param bindTable the bind table
 * @param symbolTable the symbol table
 */
void OpenServerCommand::runServer(int port, int timesPerSecond,
                                  BindTable *bindTable, SymbolTable *symbolTable) {
    int sockfd, newsockfd, portno, clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // First call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    // Now bind the host address using bind() call.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        close(sockfd);
        exit(1);
    }

    /** Now start listening for the clients, here process will
    go in sleep mode and will wait for the incoming connection
    **/
    int hz = (1000 / timesPerSecond);
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Accept actual connection from the client
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        close(sockfd);
        exit(1);
    }

    this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 2500));

//    // Wait for engine to start
//    double throttle = 0;
//    while (!shouldStop) {
//        try {
//            readValuesToBuffer(buffer, newsockfd);
//        } catch (runtime_error &ex) {
//            perror("ERROR reading from socket");
//            close(newsockfd);
//            close(sockfd);
//            exit(1);
//        }
//        // Split by ,
//        string updateData = string(buffer);
//        vector<string> sp = split(&updateData, ',');
//
//        throttle = stod(sp.at(THROTTLE_POSITION));
//        if (throttle == 0.2) {
//            // Engine start
//            if (ConnectCommand::getStatus() == NOT_CONNECTED) {
//                ConnectCommand::setStatus(CONNECTING);
//            }
//        } else if (throttle > 0.2 && ConnectCommand::getStatus() == CONNECTED) {
//            break;
//        }
//    }

    // Update variables
    while (!shouldStop) {
        /* If connection is established then start communicating */
        try {
            readValuesToBuffer(buffer, newsockfd);
        } catch (runtime_error &ex) {
            perror("ERROR reading from socket");
            close(newsockfd);
            close(sockfd);
            exit(1);
        }

        try {
            if (ConnectCommand::getStatus() == CONNECTED) {
                updateVariables(strip(string(buffer)), bindTable, symbolTable);
            }
        } catch (exception &ex) {
            cout << format("Unable to update variables because %s. Input from server: %s", ex.what(), buffer)
                 << endl;
        }

        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) hz));
    }

    // Close the socket
    if (newsockfd) {
        close(newsockfd);
    }
    close(sockfd);
}

void OpenServerCommand::readValuesToBuffer(char *buffer, int socket) {
    bzero(buffer, 1024);
    int i = 0;
    ssize_t n = 0;
    char last = '\0';
    while (i < 1024 && last != '\n' && n >= 0) {
        n = read(socket, buffer + i, 1);
        last = buffer[i];
        i++;
    }

    if (n < 0) {
        throw runtime_error("Error reading from socket");
    }
}


/**
 * Update variables using an update data from the server
 * @param updateData data from the server
 * @param bindTable the bind table
 * @param symbolTable the symbol table
 */
void OpenServerCommand::updateVariables(string updateData, BindTable *bindTable, SymbolTable *symbolTable) {
    // Split by ,
    vector<string> sp = split(&updateData, ',');

    string path;
    vector<string> variables;
    vector<string>::iterator it;
    double value;
    int i;
    // Update variables
    for (i = 0; i < 23; i++) {
        path = bindTable->getPathByIndex(i);
        if (bindTable->pathExists(path)) {
            value = stod(sp.at(i));
            variables = bindTable->getVariablesByPath(path);
            for (it = variables.begin(); it != variables.end(); it++) {
                symbolTable->update(*it, value, false);
            }
        }
    }
}

/**
 * Stop running threads
 */
void OpenServerCommand::stop() {
    shouldStop = true;
}
