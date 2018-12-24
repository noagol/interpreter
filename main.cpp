
#include "tests/InterpreterTests.h"
#include "interpreter/Interpreter.h"

using namespace std;

int main(int argc, char **argv) {
//    // Validate
//    if (argc != 2) {
//        throw invalid_argument(format("Invalid number of arguments to "
//                                      "main given. Expected 1 given %d", argc - 1));
//    }
//
//    // Run the interpreter
//    Interpreter in = Interpreter();
//    in.executeFromFile(argv[1]);
    InterpreterTest a = InterpreterTest();
    a.Test();
    //a.expressions12();
    return 0;
}
