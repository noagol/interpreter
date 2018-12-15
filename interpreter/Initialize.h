//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_INITIALIZE_H
#define PROJECT_ADVANCED_INITIALIZE_H

#include <SleepCommand.h>
#include <PrintCommand.h>
#include <DefineVarCommand.h>
#include <AssignmentCommand.h>
#include <BindCommand.h>
#include <IfCommand.h>
#include <LoopCommand.h>

class Initialize {
private:
    static void initCommands() {
        CommandTable *ct = CommandTable::getInstance();
        ct->add(OPEN_DATA_SERVER_COMMAND, new CommandExpression(new OpenServerCommand()));
        ct->add(SLEEP_COMMAND, new CommandExpression(new SleepCommand()));
        ct->add(PRINT_COMMAND, new CommandExpression(new PrintCommand()));
        ct->add(VAR_COMMAND, new CommandExpression(new DefineVarCommand()));
        ct->add(BIND_COMMAND, new CommandExpression(new BindCommand()));
        ct->add(ASSIGNMENT_COMMAND, new CommandExpression(new AssignmentCommand()));
        ct->add(IF_COMMAND, new CommandExpression(new IfCommand()));
        ct->add(WHILE_COMMAND, new CommandExpression(new LoopCommand()));
    }

public:
    static void init() {
        initCommands();
    }
};

#endif //PROJECT_ADVANCED_INITIALIZE_H
