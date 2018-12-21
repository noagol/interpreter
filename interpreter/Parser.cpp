#include "Parser.h"

/**
 * Create a code parser object
 * @param ta token array
 * @param ct command table
 * @param bt bind table
 * @param st symbol table
 */
Parser::Parser(TokenArray *ta, CommandTable *ct, BindTable *bt, SymbolTable *st) :
        commandTable(ct),
        bindTable(bt),
        symbolTable(st),
        tokenArray(ta) {}

/**
 * Parse tokens from the token array
 */
void Parser::parse() {
    while (!tokenArray->isFinished() && tokenArray->peek() != "}") {
        parseCommand();
    }
}

/**
 * Parse a single command
 * @return
 */
void Parser::parseCommand() {
    // Get next token
    string token = tokenArray->next();

    if (isCommand(token)) {
        // Handle commands
        Expression *command = commandTable->get(token);
        command->calculate();
    } else if (isVariable(token)) {
        // Handle variables
        string nextToken = tokenArray->next();
        if (nextToken == "=") {
            Expression *command = commandTable->get(nextToken);
            command->calculate();
        } else {
            throw ParserException(format("Undefined command given: %s %s", token, nextToken));
        }
    } else {
        // Unknown token
        throw ParserException(format("Undefined token: %s", token));
    }
}

/**
 * Get the next expression
 * @return expression allocated on the heap
 */
Expression *Parser::getNextExpression() {
    return tokenArray->getNextExpression();
}

/**
 * check if a token is a command
 * @param key token
 * @return true if command
 */
bool Parser::isCommand(string &key) {
    return commandTable->exists(key);
}

/**
 * check if a token is a variable
 * @param key token
 * @return true if variable
 */
bool Parser::isVariable(string &key) {
    return symbolTable->exists(key);
}

/**
 * @return pointer to the command table
 */
CommandTable *Parser::getCommandTable() {
    return commandTable;
}

/**
 * @return pointer to the bind table
 */
BindTable *Parser::getBindTable() {
    return bindTable;
}

/**
 * @return pointer to the symbol table
 */
SymbolTable *Parser::getSymbolTable() {
    return symbolTable;
}

/**
 * @return pointer to the token array
 */
TokenArray *Parser::getTokenArray() {
    return tokenArray;
}

/**
 * delete allocated memory
 */
Parser::~Parser() {
    delete commandTable;
    delete symbolTable;
    delete bindTable;
}

