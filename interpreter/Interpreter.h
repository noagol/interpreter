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
    Interpreter();

    void executeFromFile(const string &path);

    string readLine(ifstream &myFile);

    string readCodeBlock(ifstream &myFile);

    void executeFromLine(const string &line);

    ~Interpreter();

private:
    void initialize();

    void destroy();

    void initCommands();

};

#endif //PROJECT_ADVANCED_H_H
