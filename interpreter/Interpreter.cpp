#include <EntercCommand.h>
#include "../commands/ExitCommand.h"
#include "Interpreter.h"
#include "../exceptions/ExitException.h"

/**
 * Interpreter main class
 */
Interpreter::Interpreter() : commandTable(new CommandTable()),
                             bindTable(new BindTable()), symbolTable(new SymbolTable()) {
    tokenArray = new TokenArray(symbolTable);
    parser = new Parser(tokenArray, commandTable, bindTable, symbolTable);
    initialize();
}

/**
 * Execute a code in a given file
 * @param path to the file
 */
void Interpreter::executeFromFile(const string &path) {
    // Open the file
    ifstream myFile(path);
    string line;
    if (!myFile.good()) {
        throw runtime_error("File not found");
    }

    if (myFile.is_open()) {
        // Read line or a code block
        line = readLine(myFile);
        while (!line.empty()) {
            try {
                executeFromLine(line);
            } catch (ExitException& ex) {
                // Program exited
                break;
            }
            line = readLine(myFile);
        }
        // Close the file
        myFile.close();
    } else {
        throw runtime_error("Unable to open file");
    }
}

/**
 * Read line of code for execute
 * @param myFile
 * @return
 */
string Interpreter::readLine(ifstream &myFile) {
    // Read a line
    string line;
    getline(myFile, line);

    if (startswith(line, WHILE_COMMAND) || startswith(line, IF_COMMAND)) {
        // Handle conditional commands
        line += readCodeBlock(myFile);
    }

    // Return the code to execute
    return line;
}

/**
 * Read code block until a '}'
 * @param myFile open file stream
 * @return the code block
 */
string Interpreter::readCodeBlock(ifstream &myFile) {
    string line;
    string buffer;

    // Read lines until }
    while (getline(myFile, buffer)) {
        line += buffer;
        if (endswith(strip(buffer), "}")) {
            return line;
        }
        if (startswith(line, WHILE_COMMAND) || startswith(line, IF_COMMAND)) {
            // Recursively read code block
            line += readCodeBlock(myFile);
        }
    }

    return line;
}

/**
 * Execute a line of code
 * @param line the line to run
 */
void Interpreter::executeFromLine(const string &line) {
    Lexer(tokenArray, commandTable, line).lex();
    parser->parse();
}

/**
 * Destroy the object
 */
Interpreter::~Interpreter() {
    destroy();
    delete (parser);
    delete (tokenArray);
}

/**
 * Initialize the object
 */
void Interpreter::initialize() {
    initCommands();
}

/**
 * Sends a signal to running threads to stop
 */
void Interpreter::destroy() {
    OpenServerCommand::stop();
    ConnectCommand::stop();
    // Let the threads shut down correctly
    this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 250));
}

/**
 * Initialize the commands
 */
void Interpreter::initCommands() {
    commandTable->add(OPEN_DATA_SERVER_COMMAND, new CommandExpression(new OpenServerCommand(parser)));
    commandTable->add(SLEEP_COMMAND, new CommandExpression(new SleepCommand(parser)));
    commandTable->add(PRINT_COMMAND, new CommandExpression(new PrintCommand(parser)));
    commandTable->add(VAR_COMMAND, new CommandExpression(new DefineVarCommand(parser)));
    commandTable->add(BIND_COMMAND, new CommandExpression(new BindCommand(parser)));
    commandTable->add(ASSIGNMENT_COMMAND, new CommandExpression(new AssignmentCommand(parser)));
    commandTable->add(IF_COMMAND, new CommandExpression(new IfCommand(parser)));
    commandTable->add(WHILE_COMMAND, new CommandExpression(new LoopCommand(parser)));
    commandTable->add(CONNECT_COMMAND, new CommandExpression(new ConnectCommand(parser)));
    commandTable->add(EXIT_COMMAND, new CommandExpression(new ExitCommand(parser)));
    commandTable->add(ENTERC_COMMAND, new CommandExpression(new EntercCommand(parser)));
}