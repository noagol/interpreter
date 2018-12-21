#include "Parser.h"

Parser::Parser(TokenArray *ta, CommandTable *ct, BindTable *bt, SymbolTable *st) :
        commandTable(ct),
        bindTable(bt),
        symbolTable(st),
        tokenArray(ta) {}

void Parser::parse() {
    while (!tokenArray->isFinished() && tokenArray->peek() != "}") {
        parseCommand();
    }
}

bool Parser::parseCommand() {
    string token = tokenArray->next();
    if (isCommand(token)) {
        Expression *command = commandTable->get(token);
        command->calculate();
    } else if (isVariable(token)) {
        string nextToken = tokenArray->next();
        if (nextToken == "=") {
            Expression *command = commandTable->get(nextToken);
            command->calculate();
        } else {
            throw ParserException(format("Undefined command given: %s %s", token, nextToken));
        }
    } else {
        throw ParserException(format("Undefined token: %s", token));
    }
}

Expression *Parser::getNextExpression() {
    return tokenArray->getNextExpression();
}


bool Parser::isCommand(string &key) {
    return commandTable->exists(key);
}

bool Parser::isVariable(string &key) {
    return symbolTable->exists(key);
}

CommandTable *Parser::getCommandTable() {
    return commandTable;
}

BindTable *Parser::getBindTable() {
    return bindTable;
}

SymbolTable *Parser::getSymbolTable() {
    return symbolTable;
}

TokenArray *Parser::getTokenArray() {
    return tokenArray;
}

Parser::~Parser() {
    delete commandTable;
    delete symbolTable;
    delete bindTable;
}

