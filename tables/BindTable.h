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
    vector<string> variablePaths;
public:
    BindTable();

    string getPathByIndex(int i);

    void insert(const string &var, const string &path);

    string getPathByVariable(const string &var);

    vector<string> getVariablesByPath(const string &path);

    bool variableExists(const string &varName);

    bool pathExists(const string &pathName);
};

#endif //PROJECT_ADVANCED_BINDTABLE_H
