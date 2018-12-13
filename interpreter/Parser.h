#ifndef ADVANCED_PARSER_H
#define ADVANCED_PARSER_H

#include <string>
#include <vector>
#include <Command.h>
#include <CommandTable.h>

using namespace std;

class Parser {
    CommandTable* commandTable;
public:
    Parser(CommandTable* ct){
        commandTable = ct;
    }

    Command *parseLine(vector<string> *line) {
        return commandTable->get(line->at(0));
    }
};


#endif //ADVANCED_PARSER_H