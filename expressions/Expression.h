
#ifndef PROJECT_ADVANCED_EXPRESSION_H
#define PROJECT_ADVANCED_EXPRESSION_H

/**
 * Expression base class
 */
class Expression {
public:
    virtual double calculate() = 0;

    virtual ~Expression() {}
};


#endif //PROJECT_ADVANCED_EXPRESSION_H
