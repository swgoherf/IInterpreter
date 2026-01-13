#include "Interpreter.h"
#include <iostream>
#include <stdexcept>
#include <variant>

Interpreter::Interpreter(const std::string& input) : lexer(input) {
    currentToken = lexer.getNextToken();
}

void Interpreter::eat(TokenType type) {
    if (currentToken.type == type) {
        currentToken = lexer.getNextToken();
    } else {
        throw std::runtime_error("Syntax error: Unexpected token " + currentToken.value);
    }
}

std::variant<int, std::string> Interpreter::addValues(const std::variant<int, std::string>& a, const std::variant<int, std::string>& b) {
    if (std::holds_alternative<int>(a) && std::holds_alternative<int>(b)) {
        return std::get<int>(a) + std::get<int>(b);
    }
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b)) {
        return std::get<std::string>(a) + std::get<std::string>(b);
    }
    else if (std::holds_alternative<int>(a) && std::holds_alternative<std::string>(b)) {
        return std::to_string(std::get<int>(a)) + std::get<std::string>(b);
    }
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<int>(b)) {
        return std::get<std::string>(a) + std::to_string(std::get<int>(b));
    }
    throw std::runtime_error("Type error in addition");
}

std::variant<int, std::string> Interpreter::factor() {
    Token token = currentToken;
    if (token.type == NUMBER) {
        eat(NUMBER);
        return std::stoi(token.value);
    } else if (token.type == STRING) {
        eat(STRING);
        return token.value;
    } else if (token.type == ID) {
        eat(ID);
        if (variables.find(token.value) == variables.end()) {
            throw std::runtime_error("Undefined variable: " + token.value);
        }
        return variables[token.value];
    } else if (token.type == LPAREN) {
        eat(LPAREN);
        auto result = expression();
        eat(RPAREN);
        return result;
    }
    throw std::runtime_error("Syntax error in factor");
}

std::variant<int, std::string> Interpreter::term() {
    auto result = factor();
    while (currentToken.type == MUL || currentToken.type == DIV) {
        if (!std::holds_alternative<int>(result)) {
            throw std::runtime_error("Multiplication/division only for numbers");
        }
        
        int left = std::get<int>(result);
        if (currentToken.type == MUL) {
            eat(MUL);
            auto right = factor();
            if (!std::holds_alternative<int>(right)) {
                throw std::runtime_error("Multiplication only for numbers");
            }
            result = left * std::get<int>(right);
        } else {
            eat(DIV);
            auto right = factor();
            if (!std::holds_alternative<int>(right)) {
                throw std::runtime_error("Division only for numbers");
            }
            result = left / std::get<int>(right);
        }
    }
    return result;
}

std::variant<int, std::string> Interpreter::expression() {
    auto result = term();
    while (currentToken.type == PLUS || currentToken.type == MINUS) {
        if (currentToken.type == PLUS) {
            eat(PLUS);
            auto right = term();
            result = addValues(result, right);
        } else {
            eat(MINUS);
            auto right = term();
            if (!std::holds_alternative<int>(result) || !std::holds_alternative<int>(right)) {
                throw std::runtime_error("Subtraction only for numbers");
            }
            result = std::get<int>(result) - std::get<int>(right);
        }
    }
    return result;
}

void Interpreter::assignment() {
    std::string varName = currentToken.value;
    eat(ID);
    eat(ASSIGN);
    auto value = expression();
    eat(SEMI);
    
    variables[varName] = value;
}

void Interpreter::statement() {
    if (currentToken.type == PRINT) {
        eat(PRINT);
        eat(LPAREN);
        auto result = expression();
        eat(RPAREN);
        eat(SEMI);
        
        std::visit([](auto&& arg) {
            std::cout << arg;
        }, result);
        std::cout << std::endl;
    } else if (currentToken.type == ID) {
        assignment();
    } else {
        throw std::runtime_error("Unknown statement");
    }
}

void Interpreter::interpret() {
    while (currentToken.type != EOF_TOKEN) {
        statement();
    }
}