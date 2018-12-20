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
#include <ConnectCommand.h>
#include "../expressions/TokenArray.h"
#include "Lexer.h"
#include "Parser.h"
#include "../expressions/CommandExpression.h"
#include "Lexer.h"

class Interpreter {
    Parser *parser;
    TokenArray *tokenArray;
    CommandTable *commandTable;
    BindTable *bindTable;
    SymbolTable *symbolTable;
public:
    Interpreter() : commandTable(new CommandTable()),
                    bindTable(new BindTable()), symbolTable(new SymbolTable()) {
        tokenArray = new TokenArray(symbolTable);
        parser = new Parser(tokenArray, commandTable, bindTable, symbolTable);
        initialize();
    }

    void executeFromFile(const string &path) {
        ifstream myFile(path);
        string line;
        if (!myFile.good()) {
            throw runtime_error("File not found");
        }

        if (myFile.is_open()) {
            line = readCodeBlock(myFile);
            while (!line.empty()) {
                excuteFromLine(line);
                line = readCodeBlock(myFile);
            }
            myFile.close();
        } else {
            throw runtime_error("Unable to open file");
        }
    }

    string readCodeBlock(ifstream &myFile) {
        string line;
        string buffer;
        while (getline(myFile, buffer)) {
            line += buffer;
            if (startswith(line, "while") || startswith(line, "if")) {
                line += readCodeBlock(myFile);
            }
        }

        return line;
    }

    void excuteFromLine(const string &line) {
        Lexer(tokenArray, line).lex();
        parser->parse();
    }

    ~Interpreter() {
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
        ct->add(CONNECT_COMMAND, new CommandExpression(new ConnectCommand(parser)));

    }


};

#endif //PROJECT_ADVANCED_H_H
