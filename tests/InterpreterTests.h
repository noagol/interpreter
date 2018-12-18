//
// Created by noa on 13/12/2018.
//

#ifndef PROJECT_ADVANCED_INTERPRETERTESTS_H
#define PROJECT_ADVANCED_INTERPRETERTESTS_H

#include <string>
#include <iostream>
#include <Interpreter.h>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

class InterpreterTest {
public:
    void run(string &input) {
        Interpreter interpreter = Interpreter();
        interpreter.excuteFromLine(input);
    }

    void test1() {
        string input = "sleep 5000";
        cout << "Start sleep" << endl;
        run(input);
        cout << "End sleep" << endl;
    }

    void test2() {
        string input = "print \"abcd\"";
        cout << "abcd expected:" << endl;
        run(input);
    }

    void test3() {
        string input = "print 5*2";
        cout << "10 expected:" << endl;
        run(input);

    }

    void test4() {
        string input = "openDataServer 5402 10 sleep 100000";
        run(input);
    }

    void test5() {
        string input = "var x = 5*5*5 print x";
        cout << "125 expected:" << endl;
        run(input);
    }

    void test6() {
        string input = "var y = 7 var x0 = 5*y*5 print x0";
        cout << "175 expected:" << endl;
        run(input);
    }

    void test7() {
        string input = "var x = bind \"/dsasd/dsadsa\" print x";
        cout << "0 expected:" << endl;
        run(input);
    }

    void test8() {
        string input = "var x = 5 x = 7 print x";
        cout << "7 expected: " << endl;
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
        cout << "1 end expected: " << endl;
        run(input);
        cout << endl;
    }

    void test11() {
        string input = "var x = 5 if x>6 { print 1 if 3>x { print 2 } } print \"end\"";
        cout << "end expected: " << endl;
        run(input);
        cout << endl;
    }

    void test12() {
        string input = "var i = 0 while i<5 { print i i = i+1 }";
        cout << "0-4 expected: " << endl;
        run(input);
        cout << endl;
    }

    void test13() {
        string input = "var i = -(5*5) print i";
        cout << "-25 expected: " << endl;
        run(input);
        cout << endl;
    }

    void test14() {
        string input = "var i = (-5*(5+10)+1) print i";
        cout << "-74 expected: " << endl;
        run(input);
        cout << endl;
    }

    void test15() {
        string input = "var i = (-5*(5+10)+1+4)*2*-1 print i";
        cout << "140 expected: " << endl;
        run(input);
        cout << endl;
    }

    void test16() {
        string input = "var i = 2*((100/10)*3+1) print i";
        cout << "62 expected: " << endl;
        run(input);
        cout << endl;
    }
};

#endif //PROJECT_ADVANCED_INTERPRETERTESTS_H
