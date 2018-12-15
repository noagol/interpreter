#include <iostream>
#include "binary/Plus.h"
#include "expressions/Number.h"
#include "expressions/ExpressionParser.h"

#include "tests/InterpreterTests.h"
#include "tables/CommandTable.h"

using namespace std;

int main() {
    InterpreterTest t = InterpreterTest();
    t.test14();
    return 0;
}
