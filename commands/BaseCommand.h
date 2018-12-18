//
// Created by EB on 18/12/2018.
//

#ifndef PROJECT_ADVANCED_BASECOMMAND_H
#define PROJECT_ADVANCED_BASECOMMAND_H

#include <Parser.h>
#include "Command.h"

class BaseCommand : public Command {
protected:
    Parser *parser;
public:
    BaseCommand(Parser *p) : parser(p) {}
};

#endif //PROJECT_ADVANCED_BASECOMMAND_H
