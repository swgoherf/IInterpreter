#include "Lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& input) : text(input), pos(0) {
    currentChar = text.empty() ? '\0' : text[0];
}

void Lexer::advance() {
    pos++;
    if (pos < text.length()) {
        currentChar = text[pos];
    } else {
        currentChar = '\0';
    }
}

void Lexer::skipSpace() {
    while (currentChar != '\0' && isspace(currentChar)) {
        advance();
    }
}

Token Lexer::number() {
    std::string result;
    while (currentChar != '\0' && isdigit(currentChar)) {
        result += currentChar;
        advance();
    }
    return {NUMBER, result};
}

Token Lexer::identifier() {
    std::string result;
    while (currentChar != '\0' && (isalnum(currentChar) || currentChar == '_')) {
        result += currentChar;
        advance();
    }

    if (result == "print") return {PRINT, result};
    return {ID, result};
}

Token Lexer::string() {
    std::string result;
    advance(); // пропускаем открывающую кавычку
    while (currentChar != '\0' && currentChar != '"') {
        result += currentChar;
        advance();
    }
    if (currentChar == '"') {
        advance(); // пропускаем закрывающую кавычку
        return {STRING, result};
    }
    throw std::runtime_error("Unterminated string");
}

Token Lexer::getNextToken() {
    while (currentChar != '\0') {
        if (isspace(currentChar)) {
            skipSpace();
            continue;
        }

        if (isdigit(currentChar)) return number();
        if (isalpha(currentChar)) return identifier();
        if (currentChar == '"') return string();

        if (currentChar == '+') { advance(); return {PLUS, "+"}; }
        if (currentChar == '-') { advance(); return {MINUS, "-"}; }
        if (currentChar == '*') { advance(); return {MUL, "*"}; }
        if (currentChar == '/') { advance(); return {DIV, "/"}; }
        if (currentChar == '(') { advance(); return {LPAREN, "("}; }
        if (currentChar == ')') { advance(); return {RPAREN, ")"}; }
        if (currentChar == '=') { advance(); return {ASSIGN, "="}; }
        if (currentChar == ';') { advance(); return {SEMI, ";"}; }

        throw std::runtime_error("Unknown character");
    }

    return {EOF_TOKEN, ""};
}