#include "Var.h"

/**
 * Base class to var
 * @param n - number
 * @param st - symbol table
 */
Var::Var(const string &n, SymbolTable *st) : name(n), symbolTable(st) {}

/**
 *
 * @return the the value of var
 */
double Var::calculate() {
    return symbolTable->get(name);
}