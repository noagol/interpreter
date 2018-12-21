#include "Number.h"

/**
 * Base class to number
 * @param num
 */
Number::Number(double num) : number(num) {}

/**
 *
 * @return the number
 */
double Number::calculate() {
    return number;
}
