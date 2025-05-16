#ifndef LEXER_H
#define LEXER_H
#include "Token.h"

bool isSpace(char c);
class Lexer
{

    int line = 1;
    int column = 0;
    const SourceFile *source;

public:
    size_t idx = 0;
    explicit Lexer(const std::string &path, const std::string &buffer)
    {
        this->source = new SourceFile(path, buffer);
    };
    Token getNextToken();

    TokenType getTokenType(const char &currentChar);
    
    char peekNextChar() const;
    char eatNextChar();
};
#endif