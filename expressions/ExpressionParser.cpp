#include "ExpressionParser.h"

/**
 * Create expression parser object to convert "10 * 5" to new Mult(new Number(10), new Number(5))
 * @param st symbol table
 * @param expression string
 */
ExpressionParser::ExpressionParser(SymbolTable *st, const string &expression) :
        symbolTable(st), values(), operators(), tokens(expression), pos(0) {
    currentChar = tokens.at(pos);
    lastType = INPUT_START;
}

/**
 * Parse an expression
 * @return a pointer to the parsed expression
 */
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
            lastType = getType(op);
            operators.push(op);
        }
    }

    // Pop all the operators from the stack
    while (!operators.empty()) {
        popOperator();
    }

    // Return the final expression
    return values.top();
}

/**
 * Pop operator and merge with values
 */
void ExpressionParser::popOperator() {
    // Get operator
    OPERATORS op = operators.top();
    operators.pop();

    if (op == NEGATIVE || op == LOGICAL_NOT || op == OPEN_BRACKETS) {
        // Unary operators
        if (values.empty()) {
            throw invalid_argument("Invalid expression");
        }
        Expression *val = values.top();
        values.pop();

        values.push(applyOpUnary(val, op));
        lastType = UNARY_OP;
    } else {
        // Binary operators
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

/**
 * Get the precedence of an operator
 * @param op operator
 * @return precedence value
 */
int ExpressionParser::precedence(OPERATORS op) {
    if (op == PLUS || op == MINUS)
        return 1;
    if (op == MULT || op == DIV)
        return 2;
    return 0;
}

/**
 * Apply an oparator to two expressions
 * @param a first
 * @param b second
 * @param op operator
 * @return Merge expression
 */
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

/**
 * Apply unary operator to an expression
 * @param a argument
 * @param op unary operator
 * @return the merged expression
 */
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

/**
 * Get operator of current char
 * @return operator
 */
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

/**
 * Advance to next position
 */
void ExpressionParser::advance() {
    pos++;
    if (this->pos > tokens.size() - 1) {
        // End of input
        this->currentChar = '\0';
    } else {
        this->currentChar = tokens.at(pos);
    }
}

/**
 * Read a number from the expression
 * @return number value
 */
double ExpressionParser::readNumber() {
    string token;
    while (this->currentChar != '\0' && (isdigit(this->currentChar) || currentChar == '.')) {
        token.push_back(this->currentChar);
        advance();
    }

    return stod(token);
}

/**
 * Read a variable from the expression
 * @return variable name
 */
string ExpressionParser::readVariable() {
    string token;
    while (this->currentChar != '\0' && (isalnum(this->currentChar) || currentChar == '_')) {
        token.push_back(this->currentChar);
        advance();
    }

    return token;
}

/**
 * Peek the next character
 * @return next char
 */
char ExpressionParser::peekNext() {
    if (this->pos > tokens.size() - 1) {
        // End of input
        return '\0';
    } else {
        return tokens.at(pos);
    }
}

/**
 * Get type of a given operator
 * @param op operator
 * @return expression type
 */
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

/**
 * Is unary expression
 * @return true if unary is expected
 */
bool ExpressionParser::isUnaryExpected() {
    return (lastType == BINARY_OP || lastType == START_OP || lastType == INPUT_START);
}

/**
 * Check if a char may be unary expression
 * @param c char
 * @return c may be unary
 */
bool ExpressionParser::mayBeUnary(char c) {
    return c == '-' || c == '!';
}

/**
 * Read unary expression
 * @return unary expression
 */
Expression *ExpressionParser::readUnaryExpression() {
    // Initialize
    char c = currentChar;
    // Move to next
    advance();
    Expression *expression;

    if (isdigit(peekNext())) {
        // Read number
        expression = new Number(readNumber());
    } else if (isVariableStart(currentChar)) {
        // Read variable
        expression = new Var(readVariable(), symbolTable);
    } else if (mayBeUnary(peekNext())) {
        // Read unary expression recursivly
        expression = readUnaryExpression();
    } else if (peekNext() == '(') {
        // Recursively parse
        string expr = advanceToNextEnd();
        expression = ExpressionParser(symbolTable, expr).parse();
    } else {
        throw ParserException(format("Invalid expression given. Expected unary expression %s", tokens));
    }

    // Wrap the expression
    if (c == '-') {
        return new Neg(expression);
    } else if (c == '!') {
        return new Not(expression);
    } else {
        throw ParserException(format("Bad implementation - unhandled unary operator %c", c));
    }
}

/**
 * Advance until next )
 * @return the expression read - (***)
 */
string ExpressionParser::advanceToNextEnd() {
    string expression;
    int numberOfOpeners = 0;

    // Read until end
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

    // No closing brackets
    throw ParserException(format("Missing closing parentheses: %s", tokens));
}