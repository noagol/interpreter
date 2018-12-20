//
// Created by EB on 14/12/2018.
//

#ifndef PROJECT_ADVANCED_EXPRESSIONQUEUE_H
#define PROJECT_ADVANCED_EXPRESSIONQUEUE_H

#include <queue>
#include "Expression.h"
#include "../exceptions/ParserException.h"
#include "../expressions/ExpressionParser.h"

using namespace std;

class TokenArray {
    ExpressionParser expressionParser;
    vector<string> array;
    int i;
public:
    TokenArray(SymbolTable *st) : i(0), expressionParser(st) {}

    int getIndex() {
        return i;
    }

    string next() {
        return array.at(i++);
    }

    string peek() {
        return array.at(i);
    }

    string get(int index) {
        return array.at(index);
    }

    void add(vector<string> tokens) {
        vector<string>::iterator it;
        for (it = tokens.begin(); it != tokens.end(); it++) {
            array.push_back(*it);
        }
    }

    void add(string exp) {
        array.push_back(exp);
    }

    void moveBy(int index) {
        i += index;
    }

    void moveTo(int index) {
        i = index;
    }

    bool isFinished() {
        return i >= array.size();
    }

    Expression *getExpression(const string &token) {
        return expressionParser.parse(token);
    }

    Expression *getNextExpression() {
        string token = next();
        return expressionParser.parse(token);
    }

    string getFrom(int valueToAddToI) {
        return get(getIndex() + valueToAddToI);
    }

    void skipToNextEnd() {
        string token;
        int numberOfOpeners = 0;
        while (!isFinished()) {
            token = next();
            if (token == "{") {
                numberOfOpeners++;
            } else if (token == "}" && numberOfOpeners == 0) {
                return;
            } else if (token == "}" && numberOfOpeners > 0) {
                numberOfOpeners--;
            } else if (numberOfOpeners < 0) {
                throw invalid_argument("Bad implementation on skip to end");
            }
        }

        throw ParserException("Missing closing brackets");
    }
};

#endif //PROJECT_ADVANCED_EXPRESSIONQUEUE_H
