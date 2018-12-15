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


    void test9() {
        string input = "var x = 5 if x<6 { print 100 } print \"end\"";
        cout << "100 end expected: " << endl;
        run(input);

    }

    void test10() {
        string input = "var x = 5 if x<6 { print 1 if 3>x { print 2 } } print \"end\"";
        cout << "1 end expected: " <<endl;
        run(input);
        cout << endl;
    }

    void test11() {
        string input = "var x = 5 if x>6 { print 1 if 3>x { print 2 } } print \"end\"";
        cout << "end expected: " <<endl;
        run(input);
        cout << endl;
    }

    void test12() {
        string input = "var i = 0 while i<5 { print i i = i+1 }";
        cout << "0-4 expected: " <<endl;
        run(input);
        cout << endl;
    }

    void test13() {
        string input = "var i = -(5*5) print i";
        cout << "-25 expected: " <<endl;
        run(input);
        cout << endl;
    }

    void test14() {
        // BUGGGGGG
        string input = "var i = (5*(5+10)+1) print i";
        cout << "-74 expected: " <<endl;
        run(input);
        cout << endl;
    }
};

#endif //PROJECT_ADVANCED_INTERPRETERTESTS_H
