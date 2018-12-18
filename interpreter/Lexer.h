//
// Created by elad on 09/12/18.
//

#ifndef ADVANCED_LEXER_H
#define ADVANCED_LEXER_H

#include <vector>
#include <sstream>
#include <iterator>
#include "../exceptions/LexerException.h"
#include "../expressions/TokenArray.h"

using namespace std;

class Lexer {
    TokenArray* tokenArray;
public:
    Lexer(TokenArray *tArray) : tokenArray(tArray) {}

    void lexer(const string &input) {
        string token;
        bool stringMode = false;
        unsigned long int i;
        for (i = 0; i < input.length(); i++) {
            if (isWhitespace(input.at(i)) && !stringMode) {
                if (!token.empty()) {
                    tokenArray->add(token);
                    token = "";
                }
            } else if (input.at(i) == '"') {
                stringMode = !stringMode;
                token.push_back('"');
            } else {
                token.push_back(input.at(i));
            }
        }

        if (stringMode) {
            throw LexerException("String has not been terminated");
        }
        if (!token.empty()) {
            tokenArray->add(token);
        }
    }

    bool isWhitespace(char c) {
        return c == ' ' || c == '\n' || c == '\r' || c == '\t';
    }
};


//static vector<string> lexer(string const &input) {
//    istringstream buffer(input);
//    vector<string> ret;
//
//    copy(istream_iterator<string>(buffer),
//         istream_iterator<string>(),
//         back_inserter(ret));
//    return ret;
//}

#endif //ADVANCED_LEXER_H