#include "TokenArray.h"

/**
 * hold a ist of tokens
 * @param st -  symbol table
 */
TokenArray::TokenArray(SymbolTable *st) : i(0), symbolTable(st) {}

/**
 *
 * @return current index
 */
int TokenArray::getIndex() {
    return i;
}

/**
 *
 * @return the next index if exist else return " "
 */
string TokenArray::next() {
    // check if we get to the end of the list
    if (isFinished()) {
        return "";
    } else {
        // return the token
        return array.at(i++);
    }
}

/**
 *
 * @return current token
 */
string TokenArray::peek() {
    return array.at(i);
}

/**
 *
 * @param index
 * @return the token in index place
 */
string TokenArray::get(int index) {
    return array.at(index);
}

/**
 * Add a list of tokens to the list
 * @param tokens - a list of tokens
 */
void TokenArray::add(vector<string> tokens) {
    vector<string>::iterator it;
    // goes all the list
    for (it = tokens.begin(); it != tokens.end(); it++) {
        // add token to the array
        array.push_back(*it);
    }
}

/**
 * Add a new token to the list
 * @param exp - expression
 */
void TokenArray::add(string exp) {
    array.push_back(exp);
}

/**
 * Move position to index
 * @param index
 */
void TokenArray::moveTo(int index) {
    i = index;
}

/**
 * @return true if we reached the end of the array
 */
bool TokenArray::isFinished() {
    return i >= array.size();
}

/**
 * @param token to get the expression from
 * @return expression pointer
 */
Expression *TokenArray::getExpression(const string &token) {
    if (token.empty()) {
        return nullptr;
    } else {
        return ExpressionParser(symbolTable, token).parse();
    }
}


/**
 * @return expression pointer of the next token
 */
Expression *TokenArray::getNextExpression() {
    string token = next();
    return getExpression(token);
}

/**
 * Get token from current index + offset
 * @param valueToAddToI offset
 * @return the token
 */
string TokenArray::getFrom(int valueToAddToI) {
    return get(getIndex() + valueToAddToI);
}

/**
 * Read tokens until the next end
 */
void TokenArray::skipToNextEnd() {
    string token;
    // Count number of open brackets {
    int numberOfOpeners = 0;
    // While the array is not at the end
    while (!isFinished()) {
        // Get the next token
        token = next();
        // Handle the token
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
    // No next end
    throw ParserException("Missing closing brackets");
}