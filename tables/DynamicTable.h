//
// Created by elad on 09/12/18.
//

#ifndef ADVANCED_TABLE_H
#define ADVANCED_TABLE_H

#include <map>

using namespace std;

template<class T>
class DynamicTable {
    map<string, T *> table;
public:
    void add(const char *key, T *value);

    void add(string &key, T *value);

    T *get(string &key);

    bool exists(const string &key);

    ~DynamicTable();
};

template<class T>
void DynamicTable<T>::add(const char *key, T *value) {
    table[key] = value;
}

template<class T>
void DynamicTable<T>::add(string &key, T *value) {
    table[key] = value;
}

template<class T>
T *DynamicTable<T>::get(string &key) {
    if (exists(key)) {
        return table.at(key);
    } else {
        throw invalid_argument("Key is not present in table");
    }
}

template<class T>
bool DynamicTable<T>::exists(const string &key) {
    return table.find(key) != table.end();
}

template<class T>
DynamicTable<T>::~DynamicTable() {
    typename map<string, T *>::iterator it;
    for (it = table.begin(); it != table.end(); ++it) {
        delete (it->second);
    }
}


#endif //ADVANCED_TABLE_H
