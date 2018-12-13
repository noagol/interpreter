//
// Created by elad on 09/12/18.
//

#ifndef ADVANCED_TABLE_H
#define ADVANCED_TABLE_H
#include <map>

using namespace std;

template <class T>
class Table{
    map<string, T> table;
public:
    void add(string& key, T value){
        table[key] = value;
    }

    T get(string& key) {
        T value = table.at(key);
        if (value){
            return value;
        } else {
            throw invalid_argument("Key is not present in table");
        }
    }


};
#endif //ADVANCED_TABLE_H
