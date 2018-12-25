#include "BindTable.h"

/**
 * A table for holding all the variable binds in the program
 */
BindTable::BindTable() {
    variablePaths = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
                     "/instrumentation/altimeter/indicated-altitude-ft",
                     "/instrumentation/altimeter/pressure-alt-ft",
                     "/instrumentation/attitude-indicator/indicated-pitch-deg",
                     "/instrumentation/attitude-indicator/indicated-roll-deg",
                     "/instrumentation/attitude-indicator/internal-pitch-deg",
                     "/instrumentation/attitude-indicator/internal-roll-deg",
                     "/instrumentation/encoder/indicated-altitude-ft",
                     "/instrumentation/encoder/pressure-alt-ft",
                     "/instrumentation/gps/indicated-altitude-ft",
                     "/instrumentation/gps/indicated-ground-speed-kt",
                     "/instrumentation/gps/indicated-vertical-speed",
                     "/instrumentation/heading-indicator/indicated-heading-deg",
                     "/instrumentation/magnetic-compass/indicated-heading-deg",
                     "/instrumentation/slip-skid-ball/indicated-slip-skid",
                     "/instrumentation/turn-indicator/indicated-turn-rate",
                     "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                     "/controls/flight/aileron",
                     "/controls/flight/elevator",
                     "/controls/flight/rudder",
                     "/controls/flight/flaps",
                     "/controls/engines/current-engine/throttle",
                     "/engines/engine/rpm"};
}

/**
 * Get a path from the path list by the order that specified in generic_small.xml file
 * @param i index
 * @return the requested path
 */
string BindTable::getPathByIndex(int i) {
    return variablePaths.at(i);
}

/**
 * Insert a path and variable to the table
 * @param var the var name
 * @param path the flight gear path
 */
void BindTable::insert(const string &var, const string &path) {
    // Add to the map
    variableToPath[var] = path;

    if (pathExists(path)) {
        // If path already exists
        vector<string> vars = pathToVariables[path];
        vars.push_back(var);
        pathToVariables[path] = vars;
    } else {
        // Add a new vector
        pathToVariables[path] = (vector<string>) {var};
    }
}

/**
 * Get the bind path of a variable
 * @param var variable name
 * @return the path
 */
string BindTable::getPathByVariable(const string &var) {
    if (variableExists(var)) {
        return variableToPath.at(var);
    } else {
        throw invalid_argument("Key is not present in table");
    }
}

/**
 * Get a list of variables that bind to this path
 * @param path the path
 * @return a vector of variable names
 */
vector<string> BindTable::getVariablesByPath(const string &path) {
    if (pathExists(path)) {
        return pathToVariables.at(path);
    } else {
        throw invalid_argument("Key is not present in table");
    }
}

/**
 * Check whether a variable exists in the table
 * @param varName the name of the variable
 * @return true if exists, else false
 */
bool BindTable::variableExists(const string &varName) {
    return variableToPath.find(varName) != variableToPath.end();
}

/**
 * Check whether a path exists in the table
 * @param pathName the path
 * @return true if exists, else false
 */
bool BindTable::pathExists(const string &pathName) {
    return pathToVariables.find(pathName) != pathToVariables.end();
}
