#ifndef PROJECT_ADVANCED_BINDCOMMAND_H
#define PROJECT_ADVANCED_BINDCOMMAND_H

#include <BindTable.h>
#include "Command.h"
#include "../expressions/TokenArray.h"

class BindCommand : public Command{
public:
    void doCommand() override {
        string path  = TokenArray::getInstance()->next();
        if (path.at(0) != '"' || path.at(path.size()-1) != '"'){
            throw ParserException("Invalid argument to bind command");
        }

        string varName = TokenArray::getInstance()->get(TokenArray::getInstance()->getIndex() - 3);
        BindTable::getInstance()->insert(varName, path);
    }
};

#endif //PROJECT_ADVANCED_BINDCOMMAND_H
