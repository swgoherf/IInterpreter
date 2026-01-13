#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {
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

    PRINT,      // print()

    EOF_TOKEN   
};

struct Token {
    TokenType type;
    std::string value;
};

#endif