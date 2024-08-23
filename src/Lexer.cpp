#include "../includes/Lexer.h"
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
    if (isalpha(currentChar))
    {
        std::string val{currentChar};

        while (isalnum(peekNextChar()))
            val += eatNextChar();
        if (keywords.count(val)){
            return Token{tokenStartLocation, keywords.at(val), std::move(val)};
        }
        return Token{tokenStartLocation, TokenType::IDENTIFIER, std::move(val)};
    }
    
    if(isdigit(currentChar)){
        std::string value{currentChar};
        while(isdigit(peekNextChar()))
            value += eatNextChar();
        
        if(peekNextChar() != '.'){
            return Token{tokenStartLocation, TokenType::NUMBER, value};
        }    

        value += eatNextChar();

        if(!isdigit(peekNextChar())) 
            return Token{tokenStartLocation, TokenType::UNK};

        while(isdigit(peekNextChar())) value += eatNextChar();

        return Token{tokenStartLocation, TokenType::NUMBER, value};
    }

    if (currentChar == '/' && peekNextChar() == '/')
    {
        while (peekNextChar() != '\n' && peekNextChar() != '\0')
            eatNextChar();
        return getNextToken();
    }

    return Token{tokenStartLocation, getTokenType(currentChar)};
}

TokenType Lexer::getTokenType(const char &currentChar)
{
    switch (currentChar)
    {
    case '(':
        return TokenType::LPAREN;
        break;
    case ')':
        return TokenType::RPAREN;
        break;
    case '{':
        return TokenType::LBRACE;
        break;
    case '}':
        return TokenType::RBRACE;
        break;
    case ':':
        return TokenType::COLON;
        break;
    case ';':
        return TokenType::SEMICOLON;
        break;
    case '\0':
        return TokenType::EOFTOK;
        break;
    default:
        return TokenType::UNK;
        break;
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
