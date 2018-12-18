//
// Created by EB on 18/12/2018.
//

#ifndef PROJECT_ADVANCED_H_H
#define PROJECT_ADVANCED_H_H

#include <SleepCommand.h>
#include <PrintCommand.h>
#include <AssignmentCommand.h>
#include <IfCommand.h>
#include <LoopCommand.h>
#include <BindCommand.h>
#include <DefineVarCommand.h>
#include <OpenServerCommand.h>
#include "../expressions/TokenArray.h"
#include "Lexer.h"
#include "Parser.h"
#include "../expressions/CommandExpression.h"

class Interpreter {
    Lexer *lexer;
    Parser *parser;
    TokenArray *tokenArray;
    CommandTable *commandTable;
    BindTable *bindTable;
    SymbolTable *symbolTable;
public:
    Interpreter() : commandTable(new CommandTable()),
                    bindTable(new BindTable()), symbolTable(new SymbolTable()) {
        tokenArray = new TokenArray(symbolTable);
        lexer = new Lexer(tokenArray);
        parser = new Parser(tokenArray, commandTable, bindTable, symbolTable);
        initialize();
    }

    void executeFromFile(const string &path) {

    }

    void excuteFromLine(const string &line) {
        lexer->lexer(line);
        parser->parse();
    }

    ~Interpreter() {
        delete (lexer);
        delete (parser);
        delete (tokenArray);
    }

private:
    void initialize() {
        initCommands();
    }

    void initCommands() {
        CommandTable *ct = parser->getCommandTable();
        ct->add(OPEN_DATA_SERVER_COMMAND, new CommandExpression(new OpenServerCommand(parser)));
        ct->add(SLEEP_COMMAND, new CommandExpression(new SleepCommand(parser)));
        ct->add(PRINT_COMMAND, new CommandExpression(new PrintCommand(parser)));
        ct->add(VAR_COMMAND, new CommandExpression(new DefineVarCommand(parser)));
        ct->add(BIND_COMMAND, new CommandExpression(new BindCommand(parser)));
        ct->add(ASSIGNMENT_COMMAND, new CommandExpression(new AssignmentCommand(parser)));
        ct->add(IF_COMMAND, new CommandExpression(new IfCommand(parser)));
        ct->add(WHILE_COMMAND, new CommandExpression(new LoopCommand(parser)));
    }


};

#endif //PROJECT_ADVANCED_H_H
