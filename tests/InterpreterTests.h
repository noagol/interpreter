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
        string input = "sleep 5000";

        lexer(input);
        cout << "Start sleep" << endl;
        Parser::parse();
        cout << "End sleep" << endl;
    }

    void test2() {
        string input = "print \"abcd\"";
        lexer(input);
        Parser::parse();
    }

    void test3() {
        string input = "print 5*2";
        lexer(input);
        Parser::parse();
    }

    void test4() {
        string input = "openDataServer 5400 10 sleep 10000000";
        lexer(input);
        Parser::parse();
    }

};

#endif //PROJECT_ADVANCED_INTERPRETERTESTS_H
