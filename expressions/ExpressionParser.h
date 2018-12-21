//
// Created by EB on 14/12/2018.
//

#ifndef PROJECT_ADVANCED_EXPRESSIONPARSER_H
#define PROJECT_ADVANCED_EXPRESSIONPARSER_H

#include <bits/stdc++.h>
#include "../expressions/binary/Plus.h"
#include "../expressions/binary/Minus.h"
#include "../expressions/binary/Mult.h"
#include "../expressions/binary/Div.h"
#include "Number.h"
#include "Var.h"
#include "../expressions/binary/SmallerOrEqualThan.h"
#include "../expressions/binary/BiggerThan.h"
#include "../expressions/binary/BiggerOrEqualThan.h"
#include "../expressions/binary/EqualTo.h"
#include "../expressions/binary/NotEqualTo.h"
#include "../expressions/binary/SmallerThan.h"
#include "../exceptions/ParserException.h"
#include "../expressions/unary/Neg.h"
#include "../expressions/unary/Not.h"
#include "../helpers/Validator.h"

using namespace std;

/**
 * Operators types
 */
enum OPERATORS {
    PLUS, MINUS, DIV, MULT, SMALLER_THAN,
    BIGGER_THAN, SMALLER_OR_EQUAL, BIGGER_OR_EQUAL,
    EQUAL, NOT_EQUAL, OPEN_BRACKETS, NEGATIVE,
    LOGICAL_NOT, CLOSE_BRACKETS
};

/**
 * Expression types
 */
enum EXPRESSION_TYPES {
    BINARY_OP, UNARY_OP, INPUT_START, VALUE, VARIABLE, START_OP, END_OP
};

class ExpressionParser {
    SymbolTable *symbolTable;
    stack<Expression *> values;
    stack<OPERATORS> operators;
    string tokens;
    unsigned long int pos;
    char currentChar;
    EXPRESSION_TYPES lastType;
public:
    ExpressionParser(SymbolTable *st, const string &expression);

    Expression *parse();

    void popOperator();

    int precedence(OPERATORS op);

    Expression *applyOpBinary(Expression *a, Expression *b, OPERATORS op);

    Expression *applyOpUnary(Expression *a, OPERATORS op);

    OPERATORS getOperator();

    void advance();

    double readNumber();

    string readVariable();

    char peekNext();

    EXPRESSION_TYPES getType(OPERATORS op);

    bool isUnaryExpected();

    bool mayBeUnary(char c);

    Expression *readUnaryExpression();

    string advanceToNextEnd();
};

#endif //PROJECT_ADVANCED_EXPRESSIONPARSER_H
