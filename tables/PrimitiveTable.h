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
    void add(const char *key, T value) {
        lock.lock();
        table[key] = value;
        changed.push_back(key);
        lock.unlock();
    }

    void add(string key, T value) {
        lock.lock();
        table[key] = value;
        changed.push_back(key);
        lock.unlock();
    }

    void update(string key, T v) {
        if (!exists(key)) {
            throw invalid_argument(format("Unable to update missing key %s", key));
        } else {
            lock.lock();
            table[key] = v;
            changed.push_back(key);
            lock.unlock();
        }
    }

    vector<string> getChangedKeys() {
        lock.lock();
        vector<string> changedCopy = changed;
        changed = vector<string>();
        lock.unlock();
        return changedCopy;
    }

    bool areThereAnyChanges() {
        lock.lock();
        bool b = !changed.empty();
        lock.unlock();
        return b;
    }

    T get(string &key) {
        if (exists(key)) {
            lock.lock();
            T t = table.at(key);
            lock.unlock();
            return t;
        } else {
            throw invalid_argument("Key is not present in table");
        }

    }

    bool exists(string &key) {
        lock.lock();
        bool b = (table.find(key) != table.end());
        lock.unlock();
        return b;
    }

    ~PrimitiveTable() {}

};

#endif //PROJECT_ADVANCED_PRIMITIVETABLE_H
