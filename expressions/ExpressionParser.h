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

using namespace std;


class ExpressionParser {
public:
    static Expression *parse(string tokens) {
        unsigned long int i;
        // stack to store integer values.
        stack<Expression *> values;
        // stack to store operators.
        stack<char> operators;

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
                continue;
            } else if (tokens[i] == '(') {
                // Current token is an opening
                // brace, push it to operators stack
                operators.push(tokens[i]);
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
                while (!operators.empty() && operators.top() != '(') {
                    Expression *val2 = values.top();
                    values.pop();

                    Expression *val1 = values.top();
                    values.pop();

                    char op = operators.top();
                    operators.pop();

                    values.push(applyOp(val1, val2, op));
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
                    Expression *val2 = values.top();
                    values.pop();

                    Expression *val1 = values.top();
                    values.pop();

                    char op = operators.top();
                    operators.pop();

                    values.push(applyOp(val1, val2, op));
                }

                // Push current token to 'ops'.
                operators.push(tokens[i]);
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

            char op = operators.top();
            operators.pop();

            values.push(applyOp(val1, val2, op));
        }

        // Top of 'values' contains result, return it.
        return values.top();
    }

    static int precedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    // Function to perform arithmetic operations.
    static Expression *applyOp(Expression *a, Expression *b, char op) {
        switch (op) {
            case '+':
                return new Plus(a, b);
            case '-':
                return new Minus(a, b);
            case '*':
                return new Mult(a, b);
            case '/':
                return new Div(a, b);
            default:
                throw invalid_argument("Expected operator");
        }
    }

    static bool isChar(char c) {
        return 'A' <= c && c <= 'z';
    }
};

#endif //PROJECT_ADVANCED_EXPRESSIONPARSER_H
