#include <iostream>
#include "binary/Plus.h"
#include "expressions/Number.h"

using namespace std;

int main() {

    double a = (new Plus(new Plus(new Number(4), new Number(-2)), new Number(1)))->calculate();
    cout << a << endl;
    return 0;
}
