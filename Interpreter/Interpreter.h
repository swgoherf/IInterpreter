#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../Lexer/Lexer.h"
#include <map>
#include <string>
#include <variant>

class Interpreter {
private:
    Lexer lexer;
    Token currentToken;
    std::map<std::string, std::variant<int, std::string>> variables;

    void eat(TokenType type);
    
    std::variant<int, std::string> factor();
    std::variant<int, std::string> term();
    std::variant<int, std::string> expression();
    
    void assignment();
    void statement();

    std::variant<int, std::string> addValues(const std::variant<int, std::string>& a, const std::variant<int, std::string>& b);

public:
    Interpreter(const std::string& input);
    void interpret();
};

#endif