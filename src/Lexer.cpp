#include "libtarot/Lexer.h"
#include <string>

bool isSpace(char c)
{
    return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}

Token Lexer::getNextToken()
{
    char currentChar = eatNextChar();
    while (isSpace(currentChar))
    {
        currentChar = eatNextChar();
    }

    SourceLocation tokenStartLocation{source->path, line, column};
    if (isalpha(currentChar) || currentChar == '_')
    {
        std::string val{currentChar};

        while (isalnum(peekNextChar()) || peekNextChar() == '_')
            val += eatNextChar();
        if (keywords.count(val))
        {
            return Token{tokenStartLocation, keywords.at(val), std::move(val)};
        }
        return Token{tokenStartLocation, TokenType::IDENTIFIER, std::move(val)};
    }

    if (isdigit(currentChar))
    {
        std::string value{currentChar};
        while (isdigit(peekNextChar()))
            value += eatNextChar();

        if (peekNextChar() != '.')
        {
            return Token{tokenStartLocation, TokenType::NUMBER, value};
        }

        value += eatNextChar();

        if (!isdigit(peekNextChar()))
            return Token{tokenStartLocation, TokenType::UNK, value};

        while (isdigit(peekNextChar()))
            value += eatNextChar();

        return Token{tokenStartLocation, TokenType::NUMBER, value};
    }

    if (currentChar == '/')
    {
        if (peekNextChar() != '/')
            return Token{tokenStartLocation, TokenType::SLASH};
        while (peekNextChar() != '\n' && peekNextChar() != '\0')
            eatNextChar();
        return getNextToken();
    }

    if (currentChar == '=' && peekNextChar() == '=')
    {
        eatNextChar();
        return Token{tokenStartLocation, TokenType::EQUALEQUAL};
    }

    if (currentChar == '&' && peekNextChar() == '&')
    {
        eatNextChar();
        return Token{tokenStartLocation, TokenType::AMPAMP};
    }

    if (currentChar == '|' && peekNextChar() == '|')
    {
        eatNextChar();
        return Token{tokenStartLocation, TokenType::PIPEPIPE};
    }

    return Token{tokenStartLocation, getTokenType(currentChar)};
}

TokenType Lexer::getTokenType(const char &currentChar)
{
    switch (currentChar)
    {
    case '(':
        return TokenType::LPAREN;
    case ')':
        return TokenType::RPAREN;
    case '{':
        return TokenType::LBRACE;
    case '}':
        return TokenType::RBRACE;
    case ':':
        return TokenType::COLON;
    case ';':
        return TokenType::SEMICOLON;
    case '\0':
        return TokenType::EOFTOK;
    case ',':
        return TokenType::COMMA;
    case '>':
        return TokenType::GT;
    case '<':
        return TokenType::LT;
    case '!':
        return TokenType::EXCL;
    default:
        return TokenType::UNK;
    }
}

char Lexer::peekNextChar() const
{
    return source->buffer[idx];
}

char Lexer::eatNextChar()
{
    ++column;

    if (source->buffer[idx] == '\n')
    {
        line++;
        column = 0;
    }
    return source->buffer[idx++];
}
