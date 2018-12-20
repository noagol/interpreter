//
// Created by EB on 15/12/2018.
//

#ifndef PROJECT_ADVANCED_STRINGHELPERS_H
#define PROJECT_ADVANCED_STRINGHELPERS_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <exception>

using namespace std;

// base case of recursion, no more arguments
void format_impl(std::stringstream &ss, const char *format) {
    while (*format) {
        if (*format == '%' && *++format != '%') // %% == % (not a format directive)
            throw std::invalid_argument("not enough arguments !\n");
        ss << *format++;
    }
}

template<typename Arg, typename... Args>
void format_impl(std::stringstream &ss, const char *format, Arg arg, Args... args) {
    while (*format) {
        if (*format == '%' && *++format != '%') {
            auto current_format_qualifier = *format;
            switch (current_format_qualifier) {
                case 'd' :
                    if (!std::is_integral<Arg>()) throw std::invalid_argument("%d introduces integral argument");
                    // etc.
            }
            // it's true you'd have to handle many more format qualifiers, but on a safer basis
            ss << arg; // arg type is deduced
            return format_impl(ss, ++format, args...); // one arg less
        }
        ss << *format++;
    } // the format string is exhausted and we still have args : throw
    throw std::invalid_argument("Too many arguments\n");
}

template<typename... Args>
std::string format(const char *fmt, Args... args) {
    std::stringstream ss;
    format_impl(ss, fmt, args...);
    return ss.str();
}


bool startswith(const string &base, const string &prefix) {
    return !base.compare(0, prefix.size(), prefix);
}

static vector<string> split(string *str, char delimeter) {
    unsigned int i = 0;
    unsigned int a = 0;
    vector<string> l;
    for (i = 0; i < str->length(); i++) {
        if (str->at(i) == delimeter) {
            l.push_back(str->substr(a, i - a));
            a = i + 1;
        }
    }
    l.push_back(str->substr(a, i));

    return l;
}

#endif //PROJECT_ADVANCED_STRINGHELPERS_H
