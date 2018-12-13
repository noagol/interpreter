//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_PRINTCOMMAND_H
#define PROJECT_ADVANCED_PRINTCOMMAND_H

#include <iostream>
#include "Command.h"

class PrintCommand : public Command {

public:
    PrintCommand() {}

    int doCommand(vector<string> *params) override {
        string s = params->at(1);
        if (s.at(0) == '\"') {
            cout << s.substr(1, s.size() - 2) << endl;
        } else {
            // cout << call dijstra << endl;
            cout << s << endl;
        }
    }
};

#endif //PROJECT_ADVANCED_PRINTCOMMAND_H
