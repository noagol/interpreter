#ifndef PROJECT_ADVANCED_INTERPRETERTESTS_H
#define PROJECT_ADVANCED_INTERPRETERTESTS_H

#include <string>
#include <iostream>
#include "../interpreter/Interpreter.h"

using namespace std;

class InterpreterTest {
public:
    void run(string &input) {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromLine(input);
    }

    void test1() {
        string input = "sleep 2000";
        cout << "2 seconds sleep" << endl;
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
        string input = "var x = 5 if x < 6 { print 100 } print \"end\"";
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

    void test17() {
        string input = "connect 127.0.0.1 5402 sleep 10000000";
        run(input);
    }

    void test18() {
        string input = "var rudder = 1 if rudder == 1 { print \"a\" }";
        run(input);
    }

    void expressions1() {
        string input = "var x = 10 * 10 - 3 print x * 2";
        cout << "194 expected: " << endl;
        run(input);
    }

    void expressions2() {
        string input = "var x = -(10 * 10) - 3 print x * 2";
        cout << "-206 expected: " << endl;
        run(input);
    }

    void expressions3() {
        string input = "var x = --10*20 print x * 2";
        cout << "400 expected: " << endl;
        run(input);
    }


    void expressions4() {
        string input = "var x = 5 var y = 8 var z = --(x * y)+25*2-10 print z";
        cout << "80 expected: " << endl;
        run(input);
    }


    void expressions5() {
        string input = "var x = 5 var y = 8 var z = !(--(x * y)-(25*2-10)) print z";
        cout << "1 expected: " << endl;
        run(input);
    }

    void expressions6() {
        string input = "var h0 = 5 var y90 = 8 var z = (--(h0*y90)-(25*2-10)) print z";
        cout << "0 expected: " << endl;
        run(input);
    }

    void expressions7() {
        string input = "print 100 + 20*1.5 < 200*0.5 + 31";
        cout << "1 expected: " << endl;
        run(input);
    }

    void expressions8() {
        string input = "print 100 + 20*1.5";
        cout << "130 expected: " << endl;
        run(input);
    }

    void expressions9() {
        string input = "print 200*0.5 + 31";
        cout << "131 expected: " << endl;
        run(input);
    }

    void expressions10() {
        string input = "print -(200*0.5 + 31 + -(10*2*(1*2)))";
        cout << "-91 expected: " << endl;
        run(input);
    }

    void expressions11() {
        string input = "connect";
        cout << "-91 expected: " << endl;
        run(input);
    }

    void expressions12() {
        string input = "connect 127.0.0.1  9";
        cout << "-91 expected: " << endl;
        run(input);
    }

    void testFile1() {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromFile("../tests/files/simple.txt");
    }


    void testFile2() {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromFile("../tests/files/advanced.txt");
    }

    void testFile3() {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromFile("../tests/files/rudder_movement.txt");
    }

    void testFile4() {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromFile("../tests/files/main_example.txt");
    }

    void testFile5() {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromFile("../tests/files/main.txt");
    }

    void testFile6() {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromFile("../tests/files/nested_conditions.txt");
    }

    void testFile7() {
        Interpreter interpreter = Interpreter();
        interpreter.executeFromFile("../tests/files/x.txt");
    }

    void Test() {
        InterpreterTest t = InterpreterTest();
//        t.test1();
//        t.test2();
//        t.test3();
////        t.test4();
//        t.test5();
//        t.test6();
//        t.test7();
//        t.test8();
//        t.test9();
//        t.test10();
//        t.test11();
//        t.test12();
//        t.test13();
//        t.test14();
//        t.test15();
//        t.test16();
////        t.test17();
//        t.test18();
//
//
//        t.expressions1();
//        t.expressions2();
//        t.expressions3();
//        t.expressions4();
//        t.expressions5();
//        t.expressions6();
//        t.expressions7();
//        t.expressions8();
//        t.expressions9();
//        t.expressions10();
//
//
//        t.testFile1();
//        t.testFile2();
//        t.testFile3();
//        t.testFile4();
 //       t.testFile5();
//        t.testFile6();
        t.testFile7();

    }

};

#endif //PROJECT_ADVANCED_INTERPRETERTESTS_H
