//
// Created by EB on 14/12/2018.
//

#ifndef PROJECT_ADVANCED_EXPRESSIONQUEUE_H
#define PROJECT_ADVANCED_EXPRESSIONQUEUE_H

#include <queue>
#include "Expression.h"
#include "../exceptions/ParserException.h"

using namespace std;

class TokenArray {
    static TokenArray *instance;

    vector<string> array;
    int i;
public:
    TokenArray() : i(0) {}

    int getIndex(){
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

    void move(int moveBy) {
        i += moveBy;
    }

    bool isFinished() {
        return i >= array.size();
    }

    static TokenArray *getInstance() {
        if (!instance) {
            instance = new TokenArray();
            return instance;
        } else {
            return instance;
        }
    }
};

TokenArray *TokenArray::instance = nullptr;

#endif //PROJECT_ADVANCED_EXPRESSIONQUEUE_H
