//
// Created by elad on 09/12/18.
//

#ifndef ADVANCED_LEXER_H
#define ADVANCED_LEXER_H

#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

static vector<string> split(string const &input) {
    istringstream buffer(input);
    vector<string> ret;

    copy(istream_iterator<string>(buffer),
         istream_iterator<string>(),
         back_inserter(ret));
    return ret;
}


#endif //ADVANCED_LEXER_H