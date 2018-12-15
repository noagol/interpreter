//
// Created by EB on 14/12/2018.
//

#ifndef PROJECT_ADVANCED_EXPRESSIONPARSER_H
#define PROJECT_ADVANCED_EXPRESSIONPARSER_H

#include <bits/stdc++.h>
#include "../binary/Plus.h"
#include "../binary/Minus.h"
#include "../binary/Mult.h"
#include "../binary/Div.h"
#include "Number.h"
#include "Var.h"
#include "../binary/SmallerOrEqualThan.h"
#include "../binary/BiggerThan.h"
#include "../binary/BiggerOrEqualThan.h"
#include "../binary/EqualTo.h"
#include "../binary/NotEqualTo.h"
#include "../binary/SmallerThan.h"
#include "../exceptions/ParserException.h"
#include "../unary/Neg.h"
#include "../unary/Not.h"

using namespace std;

enum OPERATORS {
    PLUS, MINUS, DIV, MULT, SMALLER_THAN,
    BIGGER_THAN, SMALLER_OR_EQUAL, BIGGER_OR_EQUAL,
    EQUAL, NOT_EQUAL, OPEN_BRACKETS, NEGATIVE, LOGICAL_NOT
};

class ExpressionParser {
    // stack to store integer values.
    stack<Expression *> values;
    // stack to store operators.
    stack<OPERATORS> operators;
public:
    ExpressionParser() : values(), operators() {}

    Expression *parse(string tokens) {
        unsigned long int i;
        string var = "";

        // Iterate through the string
        for (i = 0; i < tokens.length(); i++) {
            if (tokens[i] == ' ') {
                // Current token is a whitespace,
                // skip it.
                if (!var.empty()) {
                    values.push(new Var(var));
                    var = "";
                }
            } else if (tokens[i] == '(') {
                // Current token is an opening
                // brace, push it to operators stack
                operators.push(OPEN_BRACKETS);
            } else if (isdigit(tokens[i])) {
                // Current token is a number, push
                // it to stack for numbers.
                if (!var.empty()) {
                    var.push_back(tokens[i]);
                    continue;
                }

                double val = 0;

                // There may be more than one
                // digits in number.
                while (i < tokens.length() &&
                       isdigit(tokens[i])) {
                    val = (val * 10) + (tokens[i] - '0');
                    i++;
                }
                i--;
                values.push(new Number(val));
            } else if (tokens[i] == ')') {
                // Closing brace encountered, solve
                // entire brace.
                while (!operators.empty() && operators.top() != OPEN_BRACKETS) {
                    popOperator();
                }

                // pop opening brace.
                operators.pop();
            } else if (isChar(tokens.at(i))) {
                if (var.empty()) {
                    var = tokens.at(i);
                } else {
                    var.push_back(tokens.at(i));
                }
            } else {
                // Current token is an operator.
                // While top of 'ops' has same or greater
                // precedence to current token, which
                // is an operator. Apply operator on top
                // of 'ops' to top two elements in values stack.
                if (!var.empty()) {
                    values.push(new Var(var));
                    var = "";
                }

                while (!operators.empty() && precedence(operators.top())
                                             >= precedence(tokens[i])) {
                    popOperator();
                }

                // Push current token to 'ops'.
                operators.push(getOperator(&tokens, i));
            }
        }


        // Entire expression has been parsed at this
        // point, apply remaining ops to remaining
        // values.

        if (!var.empty()) {
            values.push(new Var(var));
            var = "";
        }

        while (!operators.empty()) {
            popOperator();
        }

        // Top of 'values' contains result, return it.
        return values.top();
    }

    void popOperator() {
        OPERATORS op = operators.top();
        operators.pop();

        if (op == NEGATIVE || op == LOGICAL_NOT || op == OPEN_BRACKETS) {
            if (values.empty()) {
                throw invalid_argument("Invalid expression");
            }
            Expression *val = values.top();
            values.pop();

            values.push(applyOpUnary(val, op));
        } else {
            // Binary
            if (values.empty()) {
                throw invalid_argument("Invalid expression");
            }
            Expression *val2 = values.top();
            values.pop();

            if (values.empty()) {
                throw invalid_argument("Invalid expression");
            }
            Expression *val1 = values.top();
            values.pop();
            values.push(applyOpBinary(val1, val2, op));
        }
    }


    int precedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    // Function to perform arithmetic operations.
    Expression *applyOpBinary(Expression *a, Expression *b, OPERATORS op) {
        switch (op) {
            case PLUS:
                return new Plus(a, b);
            case MINUS:
                return new Minus(a, b);
            case MULT:
                return new Mult(a, b);
            case DIV:
                return new Div(a, b);
            case SMALLER_THAN:
                return new SmallerThan(a, b);
            case SMALLER_OR_EQUAL:
                return new SmallerOrEqualThan(a, b);
            case BIGGER_THAN:
                return new BiggerThan(a, b);
            case BIGGER_OR_EQUAL:
                return new BiggerOrEqualThan(a, b);
            case EQUAL:
                return new EqualTo(a, b);
            case NOT_EQUAL:
                return new NotEqualTo(a, b);
            default:
                throw ParserException("Invalid operator type");
        }
    }

    Expression *applyOpUnary(Expression *a, OPERATORS op) {
        switch (op) {
            case NEGATIVE:
                return new Neg(a);
            case LOGICAL_NOT:
                return new Not(a);
            case OPEN_BRACKETS:
                return a;
            default:
                throw ParserException("Invalid operator type");
        }
    }


    OPERATORS getOperator(string *token, int i) {
        bool nextIsEqual = false;

        if (i + 1 < token->size()) {
            nextIsEqual = token->at(i + 1) == '=';
        }

        switch (token->at(i)) {
            case '+':
                return PLUS;
            case '-':
                if (values.empty()) {
                    return NEGATIVE;
                } else {
                    return MINUS;
                }
            case '/':
                return DIV;
            case '*':
                return MULT;
            case '<':
                if (nextIsEqual) {
                    return SMALLER_OR_EQUAL;
                } else {
                    return SMALLER_THAN;
                }
            case '>':
                if (nextIsEqual) {
                    return BIGGER_OR_EQUAL;
                } else {
                    return BIGGER_THAN;
                }
            case '!':
                if (nextIsEqual) {
                    return NOT_EQUAL;
                } else {
                    return LOGICAL_NOT;
                }
            case '=':
                if (nextIsEqual) {
                    return EQUAL;
                } else {
                    throw ParserException("Invalid operator given");
                }
            case '(':
                return OPEN_BRACKETS;
            default:
                throw ParserException("Invalid operator given");
        }
    }


    static bool isChar(char c) {
        return 'A' <= c && c <= 'z';
    }
};

#endif //PROJECT_ADVANCED_EXPRESSIONPARSER_H
