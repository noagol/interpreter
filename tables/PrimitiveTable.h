//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_PRIMITIVETABLE_H
#define PROJECT_ADVANCED_PRIMITIVETABLE_H

#include <map>
#include <mutex>
#include "../helpers/StringHelpers.h"

using namespace std;

template<class T>
class PrimitiveTable {
    map<string, T> table;
    vector<string> changed;
    mutex lock;
public:
    void add(const char *key, T value);

    void add(string key, T value);

    void update(string key, T v, bool addToChanged = true);

    vector<string> getChangedKeys();

    bool areThereAnyChanges();

    T get(string &key);

    bool exists(string &key);

    ~PrimitiveTable();

};

template<class T>
void PrimitiveTable<T>::add(const char *key, T value) {
    lock_guard<mutex> l(lock);
    table[key] = value;
    changed.push_back(key);
}

template<class T>
void PrimitiveTable<T>::add(string key, T value) {
    lock_guard<mutex> l(lock);
    table[key] = value;
    changed.push_back(key);
}

template<class T>
void PrimitiveTable<T>::update(string key, T v, bool addToChanged) {
    if (!exists(key)) {
        throw invalid_argument(format("Unable to update missing key %s", key));
    } else {
        lock_guard<mutex> l(lock);
        table[key] = v;
        if (addToChanged) {
            changed.push_back(key);
        }
    }
}

template<class T>
vector<string> PrimitiveTable<T>::getChangedKeys() {
    lock_guard<mutex> l(lock);
    vector<string> changedCopy = changed;
    changed = vector<string>();
    return changedCopy;
}

template<class T>
bool PrimitiveTable<T>::areThereAnyChanges() {
    lock_guard<mutex> l(lock);
    bool b = !changed.empty();
    return b;
}

template<class T>
T PrimitiveTable<T>::get(string &key) {
    if (exists(key)) {
        lock_guard<mutex> l(lock);
        T t = table.at(key);
        return t;
    } else {
        throw invalid_argument("Key is not present in table");
    }

}

template<class T>
bool PrimitiveTable<T>::exists(string &key) {
    lock_guard<mutex> l(lock);
    bool b = (table.find(key) != table.end());
    return b;
}

template<class T>
PrimitiveTable<T>::~PrimitiveTable() {}

#endif //PROJECT_ADVANCED_PRIMITIVETABLE_H
