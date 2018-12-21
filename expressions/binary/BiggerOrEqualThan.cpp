//
// Created by EB on 20/12/2018.
//

#include "BiggerOrEqualThan.h"

BiggerOrEqualThan::BiggerOrEqualThan(Expression *l, Expression *r) : BinaryExpression(l, r) {}

double BiggerOrEqualThan::calculate() {
    return getLeft()->calculate() >= getRight()->calculate();
}

