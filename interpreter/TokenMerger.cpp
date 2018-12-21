#include "TokenMerger.h"

/**
 * Create a token merger
 * @param unmergedTokens list of tokens
 * @param ta token array
 */
TokenMerger::TokenMerger(vector<Token> *unmergedTokens, TokenArray *ta) : tokens(unmergedTokens), tokenArray(ta),
                                                                          pos(0) {
    updateTokens();
}

/**
 * Merge tokens
 */
void TokenMerger::merge() {
    while (this->currentToken.getType() != END_OF_INPUT) {
        tokenArray->add(getNextToken());
        advance();
    }
}

/**
 * Get next token
 * @return token
 */
string TokenMerger::getNextToken() {
    // Get Expression
    if (currentToken.getType() == START_OPERATOR || currentToken.getType() == NUMBER ||
        currentToken.getType() == NAME) {
        return readExpression();
    }

    // Get single token
    if (isSingleToken()) {
        return currentToken.getValue();
    }

    // Unknown type
    throw LexerException("Unable to split to tokens");
}

/**
 * Read an expression
 * @return string of the merged expression
 */
string TokenMerger::readExpression() {
    string expression;
    // Loop the token array
    while (this->currentToken.getType() != END_OF_INPUT) {
        if (this->currentToken.getType() == START_OPERATOR || this->currentToken.getType() == END_OPERATOR) {
            // Start operators - e.g. ( ! ...
            expression += this->currentToken.getValue();
            if (isExpressionTerminator(nextToken) && this->currentToken.getType() == END_OPERATOR) {
                return expression;
            }
        } else if (this->currentToken.getType() == BINARY_OPERATOR) {
            // Binary operators - e.g. * + - ...
            if (this->lastToken.getType() == NUMBER || this->lastToken.getType() == NAME ||
                lastToken.getType() == START_OPERATOR || lastToken.getType() == END_OPERATOR) {
                expression += this->currentToken.getValue();
            } else {
                throw LexerException("Binary operator after not a number or variable");
            }
        } else if (this->currentToken.getType() == NUMBER) {
            // Numbers
            if (isExpressionTerminator(nextToken)) {
                // Expression is finished here
                expression += this->currentToken.getValue();
                return expression;
            } else {
                // Add to expression
                expression += this->currentToken.getValue();
            }
        } else if (this->currentToken.getType() == NAME) {
            // Names
            if (isExpressionTerminator(nextToken)) {
                // Expression is finished here
                expression += this->currentToken.getValue();
                return expression;
            } else if (nextToken.getType() == ASSIGNMENT_OPERATOR) {
                if (expression.empty()) {
                    return currentToken.getValue();
                } else {
                    throw LexerException("Assign to an expression");
                }
            } else {
                // Add to expression
                expression += this->currentToken.getValue();
            }
        } else if (this->currentToken.getType() == ASSIGNMENT_OPERATOR) {
            // Assignment operator
            if (lastToken.getType() != NAME || expression.empty()) {
                throw LexerException("Assign to non name argument");
            }
            return currentToken.getValue();
        } else {
            if (expression.empty()) {
                throw LexerException("Unable to read expression");
            } else {
                // Read one too many
                pos--;
                updateTokens();
                return expression;
            }
        }

        advance();
    }

}

/**
 * Check if the token is always single
 * @return true if so
 */
bool TokenMerger::isSingleToken() {
    TOKEN_TYPE type = currentToken.getType();
    return type == START_CODE_BLOCK || type == END_CODE_BLOCK
           || type == STRING || type == ASSIGNMENT_OPERATOR || type == COMMAND;
}

/**
 * Check if token expression terminator
 * @param token the token
 * @return true if one of the types
 */
bool TokenMerger::isExpressionTerminator(Token &token) {
    return token.getType() == NUMBER || token.getType() == NAME
           || token.getType() == END_OF_INPUT || token.getType() == STRING
           || token.getType() == START_CODE_BLOCK || token.getType() == END_CODE_BLOCK
           || token.getType() == COMMAND;
}

/**
 * Get token from offset
 * @param i offset
 * @return tokens[pos + i]
 */
Token TokenMerger::getFromOffset(int i) {
    if (this->pos + i > tokens->size() - 1) {
        // End of input
        return Token(END_OF_INPUT, "");
    } else if (this->pos + i < 0) {
        // Start of input
        return Token(START_OF_INPUT, "");
    } else {
        // Get the token
        return tokens->at(pos + i);
    }
}

/**
 * Update pointer tokens
 */
void TokenMerger::updateTokens() {
    this->lastToken = getFromOffset(-1);
    this->currentToken = getFromOffset(0);
    this->nextToken = getFromOffset(1);
}

/**
 * Advance position
 */
void TokenMerger::advance() {
    pos++;
    updateTokens();
}

/**
 * Free allocated memory
 */
TokenMerger::~TokenMerger() {
    delete (tokens);
}
