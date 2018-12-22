
#ifndef PROJECT_ADVANCED_BASECOMMAND_H
#define PROJECT_ADVANCED_BASECOMMAND_H

#include "../interpreter/Parser.h"
#include "Command.h"

class BaseCommand : public Command {
protected:
    Parser *parser;
public:
    BaseCommand(Parser *p);
};

#endif //PROJECT_ADVANCED_BASECOMMAND_H
