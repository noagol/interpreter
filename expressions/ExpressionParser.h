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
    SymbolTable *symbolTable;
    stack<Expression *> values;
    stack<OPERATORS> operators;
public:
    ExpressionParser(SymbolTable *st) : symbolTable(st), values(), operators() {}

    Expression *parse(string tokens) {
        unsigned long int i;
        string var = "";

        // Iterate through the string
        for (i = 0; i < tokens.length(); i++) {
            if (tokens[i] == ' ') {
                if (!var.empty()) {
                    values.push(new Var(var, symbolTable));
                    var = "";
                }
            } else if (tokens[i] == '(') {
                operators.push(OPEN_BRACKETS);
            } else if (isdigit(tokens[i])) {
                if (!var.empty()) {
                    var.push_back(tokens[i]);
                    continue;
                }

                double val = 0;
                while (i < tokens.length() &&
                       isdigit(tokens[i])) {
                    val = (val * 10) + (tokens[i] - '0');
                    i++;
                }
                i--;
                values.push(new Number(val));
            } else if (tokens[i] == '-' && i + 1 < tokens.size() && isdigit(tokens[i + 1])) {
                i++;
                if (!var.empty()) {
                    var.push_back(tokens[i]);
                    continue;
                }

                double val = 0;

                while (i < tokens.length() &&
                       isdigit(tokens[i])) {
                    val = (val * 10) + (tokens[i] - '0');
                    i++;
                }
                i--;
                values.push(new Number(val * -1));
            } else if (tokens[i] == ')') {
                while (!operators.empty() && operators.top() != OPEN_BRACKETS) {
                    popOperator();
                }

                if (!operators.empty()) {
                    operators.pop();
                }
            } else if (isChar(tokens.at(i))) {
                if (var.empty()) {
                    var = tokens.at(i);
                } else {
                    var.push_back(tokens.at(i));
                }
            } else {
                if (!var.empty()) {
                    values.push(new Var(var, symbolTable));
                    var = "";
                }

                OPERATORS op = getOperator(&tokens, i);
                while (!operators.empty() && precedence(operators.top())
                                             >= precedence(op)) {
                    popOperator();
                }

                operators.push(op);
            }
        }

        if (!var.empty()) {
            values.push(new Var(var, symbolTable));
            var = "";
        }

        while (!operators.empty()) {
            popOperator();
        }

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


    int precedence(OPERATORS op) {
        if (op == PLUS || op == MINUS)
            return 1;
        if (op == MULT || op == DIV)
            return 2;
//        if (op == NEGATIVE)
//            return 3;
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


    OPERATORS getOperator(string *token, unsigned long int& i) {
        bool nextIsEqual = false;

        if (i + 1 < token->size()) {
            nextIsEqual = (token->at(i + 1) == '=');
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
                    i++;
                    return SMALLER_OR_EQUAL;
                } else {
                    return SMALLER_THAN;
                }
            case '>':
                if (nextIsEqual) {
                    i++;
                    return BIGGER_OR_EQUAL;
                } else {
                    return BIGGER_THAN;
                }
            case '!':
                if (nextIsEqual) {
                    i++;
                    return NOT_EQUAL;
                } else {
                    return LOGICAL_NOT;
                }
            case '=':
                if (nextIsEqual) {
                    i++;
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
