//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_PRIMITIVETABLE_H
#define PROJECT_ADVANCED_PRIMITIVETABLE_H

#include <map>

using namespace std;

template<class T>
class PrimitiveTable {
    map<string, T> table;
public:
    void add(const char *key, T value) {
        table[key] = value;
    }

    void add(string &key, T value) {
        table[key] = value;
    }

    T get(string &key) {
        if (exists(key)) {
            return table.at(key);
        } else {
            throw invalid_argument("Key is not present in table");
        }
    }

    bool exists(string &key) {
        return table.find(key) != table.end();
    }

    ~PrimitiveTable() {}

};

#endif //PROJECT_ADVANCED_PRIMITIVETABLE_H
