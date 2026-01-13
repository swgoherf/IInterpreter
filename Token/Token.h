#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenList {
    NUMBER,     
    ID,         
    STRING,

    PLUS,       // +
    MINUS,      // -
    MUL,        // *
    DIV,        // /
    ASSIGN,     // =
    LPAREN,     // (
    RPAREN,     // )
    SEMI,       // ;
    LBRACE, RBRACE,   // { }
    EQ, LT, GT,       // ==, <, >
    
    IF, 
    ELSE, 
    WHILE, 
    FOR,
    PRINT,      // print()

    EOF_TOKEN   
};

struct Token {
    TokenList type;
    std::string value;
};

#endif