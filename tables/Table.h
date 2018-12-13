//
// Created by elad on 09/12/18.
//

#ifndef ADVANCED_TABLE_H
#define ADVANCED_TABLE_H

#include <map>

using namespace std;

template<class T>
class Table {
    map<string, T *> table;
public:
    void add(const char *key, T *value) {
        table[key] = value;
    }

    void add(string &key, T *value) {
        table[key] = value;
    }

    T *get(string &key) {
        T *value = table.at(key);
        if (value) {
            return value;
        } else {
            throw invalid_argument("Key is not present in table");
        }
    }

    ~Table() {
        typename map<string, T *>::iterator it;
        for (it = table.begin(); it != table.end(); ++it) {
            delete (it->second);
        }
    }

};

#endif //ADVANCED_TABLE_H
