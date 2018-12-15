//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_INTERPRETERTESTS_H
#define PROJECT_ADVANCED_INTERPRETERTESTS_H

#include <string>
#include <iostream>
#include <Initialize.h>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

class InterpreterTest {
public:
    void run(string &input) {
        Initialize::init();
        lexer(input);
        Parser parser = Parser();
        parser.parse();
    }

    void test1() {
        string input = "sleep 5000";
        cout << "Start sleep" << endl;
        run(input);
        cout << "End sleep" << endl;
    }

    void test2() {
        string input = "print \"abcd\"";
        run(input);
    }

    void test3() {
        string input = "print 5*2";
        run(input);

    }

    void test4() {
        string input = "openDataServer 5402 10 sleep 10000000";
        run(input);
    }

    void test5() {
        string input = "var x = 5*5*5 print x";
        run(input);
    }

    void test6() {
        string input = "var y = 7 var x0 = 5*y*5 print x0";
        run(input);
    }

    void test7() {
        string input = "var x = bind \"/dsasd/dsadsa\" print x";
        run(input);
    }

    void test8() {
        string input = "var x = 5 x = 7 print x";
        cout << "7 expected: ";
        run(input);
        cout << endl;
    }
};

#endif //PROJECT_ADVANCED_INTERPRETERTESTS_H
