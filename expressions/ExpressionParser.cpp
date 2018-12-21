#include "ExpressionParser.h"

/**
 * Create expression parser object to convert "10 * 5" to new Mult(new Number(10),
 * @param st
 * @param expression
 */
ExpressionParser::ExpressionParser(SymbolTable *st, const string &expression) :
symbolTable(st), values(), operators(), tokens(expression), pos(0) {
    currentChar = tokens.at(pos);
    lastType = INPUT_START;
}

Expression *ExpressionParser::parse() {
    // Iterate through the string
    while (currentChar != '\0') {
        if (isWhitespace(currentChar)) {
            // Skip white spaces
            advance();
            continue;
        } else if (currentChar == '(') {
            // Push ( to the operator stack
            advance();
            operators.push(OPEN_BRACKETS);
            lastType = START_OP;
        } else if (isdigit(currentChar)) {
            // Read a number
            values.push(new Number(readNumber()));
            lastType = VALUE;
        } else if (mayBeUnary(currentChar) && isUnaryExpected()) {
            // Unary expression expected
            values.push(readUnaryExpression());
            lastType = UNARY_OP;
        } else if (currentChar == ')') {
            // Handle closing brackets
            advance();
            // Pop operators until open brackets
            while (!operators.empty() && operators.top() != OPEN_BRACKETS) {
                popOperator();
            }

            if (!operators.empty()) {
                operators.pop();
            }
        } else if (isVariableStart(currentChar)) {
            // Variable identified
            values.push(new Var(readVariable(), symbolTable));
            lastType = VARIABLE;
        } else {
            OPERATORS op = getOperator();
            advance();
            while (!operators.empty() &&
                   precedence(operators.top()) >= precedence(op)) {
                popOperator();
            }

            operators.push(op);
        }
    }

    while (!operators.empty()) {
        popOperator();
    }

    return values.top();
}

void ExpressionParser::popOperator() {
    OPERATORS op = operators.top();
    operators.pop();

    if (op == NEGATIVE || op == LOGICAL_NOT || op == OPEN_BRACKETS) {
        if (values.empty()) {
            throw invalid_argument("Invalid expression");
        }
        Expression *val = values.top();
        values.pop();

        values.push(applyOpUnary(val, op));
        lastType = UNARY_OP;
    } else {
        // Binary
        if (values.empty()) {
            throw invalid_argument("Invalid expression");
        }
        Expression *val2 = values.top();
        values.pop();

        if (values.empty()) {
            throw invalid_argument("Invalid expression");
        }
        Expression *val1 = values.top();
        values.pop();
        values.push(applyOpBinary(val1, val2, op));
        lastType = BINARY_OP;
    }
}


int ExpressionParser::precedence(OPERATORS op) {
    if (op == PLUS || op == MINUS)
        return 1;
    if (op == MULT || op == DIV)
        return 2;
    return 0;
}

// Function to perform arithmetic operations.
Expression *ExpressionParser::applyOpBinary(Expression *a, Expression *b, OPERATORS op) {
    switch (op) {
        case PLUS:
            return new Plus(a, b);
        case MINUS:
            return new Minus(a, b);
        case MULT:
            return new Mult(a, b);
        case DIV:
            return new Div(a, b);
        case SMALLER_THAN:
            return new SmallerThan(a, b);
        case SMALLER_OR_EQUAL:
            return new SmallerOrEqualThan(a, b);
        case BIGGER_THAN:
            return new BiggerThan(a, b);
        case BIGGER_OR_EQUAL:
            return new BiggerOrEqualThan(a, b);
        case EQUAL:
            return new EqualTo(a, b);
        case NOT_EQUAL:
            return new NotEqualTo(a, b);
        default:
            throw ParserException("Invalid operator type");
    }
}

Expression *ExpressionParser::applyOpUnary(Expression *a, OPERATORS op) {
    switch (op) {
        case NEGATIVE:
            return new Neg(a);
        case LOGICAL_NOT:
            return new Not(a);
        case OPEN_BRACKETS:
            return a;
        default:
            throw ParserException("Invalid operator type");
    }
}


OPERATORS ExpressionParser::getOperator() {
    bool nextIsEqual = (peekNext() == '=');

    switch (currentChar) {
        case '+':
            return PLUS;
        case '-':
            if (values.empty()) {
                return NEGATIVE;
            } else {
                return MINUS;
            }
        case '/':
            return DIV;
        case '*':
            return MULT;
        case '<':
            if (nextIsEqual) {
                advance();
                return SMALLER_OR_EQUAL;
            } else {
                return SMALLER_THAN;
            }
        case '>':
            if (nextIsEqual) {
                advance();
                return BIGGER_OR_EQUAL;
            } else {
                return BIGGER_THAN;
            }
        case '!':
            if (nextIsEqual) {
                advance();
                return NOT_EQUAL;
            } else {
                return LOGICAL_NOT;
            }
        case '=':
            if (nextIsEqual) {
                advance();
                return EQUAL;
            } else {
                throw ParserException("Invalid operator given");
            }
        case '(':
            return OPEN_BRACKETS;
        default:
            throw ParserException("Invalid operator given");
    }
}

void ExpressionParser::advance() {
    pos++;
    if (this->pos > tokens.size() - 1) {
        // End of input
        this->currentChar = '\0';
    } else {
        this->currentChar = tokens.at(pos);
    }
}

double ExpressionParser::readNumber() {
    string token;
    while (this->currentChar != '\0' && (isdigit(this->currentChar) || currentChar == '.')) {
        token.push_back(this->currentChar);
        advance();
    }

    return stod(token);
}

string ExpressionParser::readVariable() {
    string token;
    while (this->currentChar != '\0' && (isalnum(this->currentChar) || currentChar == '_')) {
        token.push_back(this->currentChar);
        advance();
    }

    return token;
}

char ExpressionParser::peekNext() {
    if (this->pos > tokens.size() - 1) {
        // End of input
        return '\0';
    } else {
        return tokens.at(pos);
    }
}

EXPRESSION_TYPES ExpressionParser::getType(OPERATORS op) {
    switch (op) {
        case PLUS:
        case MINUS:
        case DIV:
        case MULT:
        case SMALLER_THAN:
        case BIGGER_THAN:
        case SMALLER_OR_EQUAL:
        case BIGGER_OR_EQUAL:
        case EQUAL:
        case NOT_EQUAL:
            return BINARY_OP;
        case NEGATIVE:
        case LOGICAL_NOT:
            return UNARY_OP;
        case OPEN_BRACKETS:
            return START_OP;
        case CLOSE_BRACKETS:
            return END_OP;
    }
}

bool ExpressionParser::isUnaryExpected() {
    return (lastType == BINARY_OP || lastType == START_OP || lastType == INPUT_START);
}

bool ExpressionParser::mayBeUnary(char c) {
    return c == '-' || c == '!';
}

Expression *ExpressionParser::readUnaryExpression() {
    char c = currentChar;
    advance();
    Expression *expression;
    if (isdigit(peekNext())) {
        expression = new Number(readNumber());
    } else if (isVariableStart(currentChar)) {
        expression = new Var(readVariable(), symbolTable);
    } else if (mayBeUnary(peekNext())) {
        expression = readUnaryExpression();
    } else if (peekNext() == '(') {
        // Recursively parse
        string expr = advanceToNextEnd();
        expression = ExpressionParser(symbolTable, expr).parse();
    } else {
        throw ParserException(format("Invalid expression given. Expected unary expression %s", tokens));
    }

    if (c == '-') {
        return new Neg(expression);
    } else if (c == '!') {
        return new Not(expression);
    } else {
        throw ParserException(format("Bad implementation - unhandled unary operator %c", c));
    }
}

string ExpressionParser::advanceToNextEnd() {
    string expression;
    int numberOfOpeners = 0;

    while (currentChar != '\0') {
        expression += currentChar;
        advance();
        if (currentChar == '(') {
            numberOfOpeners++;
        } else if (currentChar == ')' && numberOfOpeners == 0) {
            expression += currentChar;
            advance();
            return expression;
        } else if (currentChar == ')' && numberOfOpeners > 0) {
            numberOfOpeners--;
        } else if (numberOfOpeners < 0) {
            throw invalid_argument("Bad implementation on skip to end");
        }
    }

    throw ParserException(format("Missing closing parentheses: %s", tokens));
}