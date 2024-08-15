#ifndef TOKENTYPE_H
#define TOKENTYPE_H
constexpr char singleCharTokens[] = {
    '\0', '(', ')', '{', '}', ':', ';'};

enum class TokenType : char
{
    IDENTIFIER,
    FN,
    VOID,
    EOFTOK = singleCharTokens[0],
    LPAREN = singleCharTokens[1],
    RPAREN = singleCharTokens[2],
    LBRACE = singleCharTokens[3],
    RBRACE = singleCharTokens[4],
    COLON = singleCharTokens[5],
    SEMICOLON = singleCharTokens[6],
    UNK = -128,
};
#endif