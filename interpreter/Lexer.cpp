#include "Lexer.h"

/**
 * Create a lexer object
 * @param ta token array
 * @param ct command table
 * @param inputStr the input to the lexer
 */
Lexer::Lexer(TokenArray *ta, CommandTable *ct, const string &inputStr) : tokenArray(ta), input(inputStr), pos(0),
                                                                         currentToken(), lastToken(), commandTable(ct) {
    currentChar = inputStr.at(pos);
}

/**
 * Split and add tokens the token array
 */
void Lexer::lex() {
    TokenMerger tokenMerger = TokenMerger(readTokens(), tokenArray);
    tokenMerger.merge();
}

/**
 * Read and classify to tokens
 * @return a vector of tokens
 */
vector<Token> *Lexer::readTokens() {
    vector<Token> *tokens = new vector<Token>;
    // Read token until the are no more
    while (this->currentChar != '\0') {
        // Save last token
        lastToken = currentToken;
        // Get next
        currentToken = getNextToken();
        // Add to token vector
        if (currentToken.getType() != END_OF_INPUT) {
            tokens->push_back(currentToken);
        }
    }
    // Return the token
    return tokens;
}

/**
 * Advance to next character
 */
void Lexer::advance() {
    pos++;
    if (this->pos > input.size() - 1) {
        // End of input
        this->currentChar = '\0';
    } else {
        this->currentChar = input.at(pos);
    }
}

/**
 * Skip whitespaces
 */
void Lexer::skip() {
    while (this->currentChar != '\0' && (isWhitespace(this->currentChar)|| isRedundent(this->currentChar))) {
        advance();
    }
}

/**
 * Read a number token
 * @return the string of the number
 */
string Lexer::readInteger() {
    string token;
    while (this->currentChar != '\0' && isdigit(this->currentChar)) {
        token.push_back(this->currentChar);
        advance();
    }
    return token;
}

/**
 * Read a name token
 * @return the name
 */
string Lexer::readName() {
    string token;
    while (this->currentChar != '\0' && !isNameBreaker(this->currentChar)) {
        token.push_back(this->currentChar);
        advance();
    }
    return token;
}

/**
 * Read binary operator
 * @return the operator
 */
string Lexer::readBinaryOperator() {
    string token;
    while (this->currentChar != '\0' && isBinaryOperator(this->currentChar)) {
        token.push_back(this->currentChar);
        advance();
    }
    return token;
}

/**
 * Read operator of - ( or !
 * @return the operator
 */
string Lexer::readStartOperator() {
    string token;
    while (this->currentChar != '\0' && isStartOperator(this->currentChar)) {
        token.push_back(this->currentChar);
        advance();
    }
    return token;
}

/**
 * Read end operator, eg ')'
 * @return the operator
 */
string Lexer::readEndOperator() {
    string token;
    while (this->currentChar != '\0' && isEndOperator(this->currentChar)) {
        token.push_back(this->currentChar);
        advance();
    }
    return token;
}

/**
 * Read string. e.g "abcd"
 * @return the string
 */
string Lexer::readString() {
    string token;
    // Read the first '"'
    token.push_back(this->currentChar);
    advance();

    // Read the characters
    while (this->currentChar != '\0' && this->currentChar != '"') {
        token.push_back(this->currentChar);
        advance();
    }

    if (this->currentChar == '"') {
        // Valid string
        token.push_back(this->currentChar);
        advance();
        return token;
    } else {
        // Missing end of string
        throw LexerException(format("Unterminated string expression given %s", token));
    }
}

/**
 * Read { or } tokens
 * @return the token
 */
Token Lexer::readStartOrEnd() {
    string token;
    token.push_back(this->currentChar);
    advance();
    if (this->currentChar == '{') {
        return Token(START_CODE_BLOCK, token);
    } else {
        return Token(END_CODE_BLOCK, token);
    }
}

/**
 * Get the next token
 * @return a token read
 */
Token Lexer::getNextToken() {
    while (this->currentChar != '\0') {
        // Handle whitespaces
        if (isWhitespace(this->currentChar) || isRedundent(currentChar)) {
            skip();
            continue;
        }

        // Handle numbers
        if (isdigit(this->currentChar)) {
            int i = 0;
            string token = readInteger();
            while (currentChar == '.') {
                i++;
                token += ".";
                advance();
                token += readInteger();
            }

            if (i == 0 || i == 1) {
                // Integer or double
                return Token(NUMBER, token);
            } else {
                // Probably ip
                return Token(STRING, token);
            }
        }

        // Handle variables and commands
        if (isVariableStart(this->currentChar)) {
            string token = readName();
            if (isCommand(token)) {
                return Token(COMMAND, token);
            } else {
                return Token(NAME, token);
            }
        }

        // Handle operators
        if (isStartOperator(this->currentChar) && lastToken.getType() != NUMBER && lastToken.getType() != NAME) {
            string token = readStartOperator();
            return Token(START_OPERATOR, token);
        }

        if (isBinaryOperator(this->currentChar)) {
            string token = readBinaryOperator();
            if (token == "=") {
                return Token(ASSIGNMENT_OPERATOR, token);
            } else {
                return Token(BINARY_OPERATOR, token);
            }
        }


        if (isEndOperator(this->currentChar)) {
            string token = readEndOperator();
            return Token(END_OPERATOR, token);
        }

        // Handle strings
        if (this->currentChar == '"') {
            string token = readString();
            return Token(STRING, token);
        }

        // Handle { }
        if (isStartOrEnd(this->currentChar)) {
            return readStartOrEnd();
        }

        throw LexerException(format("Unknown format given: %s", this->input));
    }

    return Token(END_OF_INPUT, "");
}

/**
 * Check if a token is a command
 * @param str the token
 * @return true if is a command, else false
 */
bool Lexer::isCommand(const string &str) {
    return commandTable->exists(str);
}