#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <cstddef> 
#include "../Token/Token.h" 

struct LexerState { 
    size_t pos; 
    char currentChar; 
};

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

    LexerState getState() { 
        return {pos, currentChar}; 
    }
    
    void setState(LexerState state) { 
        pos = state.pos; 
        currentChar = state.currentChar; 
    }
};

#endif