//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_INTERPRETERTESTS_H
#define PROJECT_ADVANCED_INTERPRETERTESTS_H

#include <string>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

class InterpreterTest {
public:
    void test1() {
        string t = "sleep 5000";

        CommandTable commandTable = CommandTable();
        vector<string> s = lexer(t);
        Parser parser = Parser(&commandTable);
        Command *c = parser.parseLine(&s);
        cout << "Start sleep" << endl;
        c->doCommand(&s);
        cout << "End sleep" << endl;
    }

    void test2() {
        string t = "print \"abcd\"";

        CommandTable commandTable = CommandTable();
        vector<string> s = lexer(t);
        Parser parser = Parser(&commandTable);
        Command *c = parser.parseLine(&s);
        c->doCommand(&s);
    }

    void test3() {
        string t = "print 100    ";

        CommandTable commandTable = CommandTable();
        vector<string> s = lexer(t);
        Parser parser = Parser(&commandTable);
        Command *c = parser.parseLine(&s);
        c->doCommand(&s);
    }
};

#endif //PROJECT_ADVANCED_INTERPRETERTESTS_H