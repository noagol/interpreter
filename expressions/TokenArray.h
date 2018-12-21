
#ifndef PROJECT_ADVANCED_EXPRESSIONQUEUE_H

#include <queue>
#include "Expression.h"
#include "../exceptions/ParserException.h"
#include "../expressions/ExpressionParser.h"

#define PROJECT_ADVANCED_EXPRESSIONQUEUE_H


using namespace std;

class TokenArray {
    vector<string> array;
    SymbolTable *symbolTable;
    int i;
public:
    TokenArray(SymbolTable *st);

    int getIndex();

    string next();

    string peek();

    string get(int index);

    void add(vector<string> tokens);

    void add(string exp);

    void moveTo(int index);

    bool isFinished();

    Expression *getExpression(const string &token);

    Expression *getNextExpression();

    string getFrom(int valueToAddToI);

    void skipToNextEnd();
};

#endif //PROJECT_ADVANCED_EXPRESSIONQUEUE_H
