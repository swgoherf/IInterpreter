#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "../Token/Token.h" 

class Lexer {
private:
    std::string text;
    size_t pos;
    char currentChar;

    void advance();
    void skipSpace();
    Token number();
    Token identifier(); 
    Token string();

public:
    Lexer(const std::string& input);
    Token getNextToken();
};

#endif