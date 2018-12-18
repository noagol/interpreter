//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_BINDTABLE_H
#define PROJECT_ADVANCED_BINDTABLE_H


#include <string>
#include <map>
#include <vector>

using namespace std;

class BindTable {
    map<string, string> variableToPath;
    map<string, vector<string>> pathToVariables;
public:
    BindTable() {}

    void insert(const string &var, const string &path) {
        variableToPath[var] = path;
        if (pathExists(path)) {
            vector<string> a = pathToVariables[path];
            a.push_back(var);
            pathToVariables[path] = a;
        } else {
            pathToVariables[path] = (vector<string>) {var};
        }
    }

    string getPathByVariable(const string &var) {
        if (variableExists(var)) {
            return variableToPath.at(var);
        } else {
            throw invalid_argument("Key is not present in table");
        }
    }

    vector<string> getVariablesByPath(const string &path) {
        if (pathExists(path)) {
            return pathToVariables.at(path);
        } else {
            throw invalid_argument("Key is not present in table");
        }
    }

    bool variableExists(const string &varName) {
        return variableToPath.find(varName) != variableToPath.end();
    }

    bool pathExists(const string &pathName) {
        return pathToVariables.find(pathName) != pathToVariables.end();
    }

//    static BindTable *getInstance() {
//        if (!instance) {
//            instance = new BindTable();
//            return instance;
//        } else {
//            return instance;
//        }
//    }
};

//BindTable *BindTable::instance = nullptr;


#endif //PROJECT_ADVANCED_BINDTABLE_H
