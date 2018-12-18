#ifndef PROJECT_ADVANCED_BINDCOMMAND_H
#define PROJECT_ADVANCED_BINDCOMMAND_H

#include <BindTable.h>
#include "../expressions/TokenArray.h"
#include "../commands/BaseCommand.h"


class BindCommand : public BaseCommand {
public:
    BindCommand(Parser *p) : BaseCommand(p) {}

    void doCommand() override {
        string path = parser->getTokenArray()->next();
        if (path.at(0) != '"' || path.at(path.size() - 1) != '"') {
            throw ParserException("Invalid argument to bind command");
        }

        string varName = parser->getTokenArray()->getFrom(-3);
        parser->getBindTable()->insert(varName, path);
    }
};

#endif //PROJECT_ADVANCED_BINDCOMMAND_H
