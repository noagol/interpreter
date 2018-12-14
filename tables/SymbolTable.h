//
// Created by elad on 09/12/18.
//

#ifndef ADVANCED_SYMBOLTABLE_H
#define ADVANCED_SYMBOLTABLE_H

#include "Table.h"

using namespace std;

class SymbolTable : public Table<double> {
    static SymbolTable *instance;
public:
    SymbolTable() {};

    static SymbolTable *getInstance() {
        if (!instance) {
            instance = new SymbolTable();
            return instance;
        } else {
            return instance;
        }
    }
};

SymbolTable *SymbolTable::instance = nullptr;

#endif //ADVANCED_SYMBOLTABLE_H
