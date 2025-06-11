#ifndef TOKEN_H
#define TOKEN_H
#include <unordered_map>
#include <optional>
#include <values.h>
#include "TokenType.h"
#include "Source.h"

const std::unordered_map<std::string_view, TokenType>
    keywords = {
        {"fn", TokenType::FN},
        {"void", TokenType::VOID},
        {"return", TokenType::RETURN},
        {"number", TokenType::NUMBER},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE}
    };


struct Token
{
    SourceLocation source;
    TokenType type;
    std::optional<std::string> value = std::nullopt;
    std::string to_string()
    {

        switch (type)
        {
        case TokenType::FN:
            return "fn";
        case TokenType::VOID:
            return "void";
        case TokenType::RETURN:
            return "return";
        case TokenType::IDENTIFIER:
            return value.has_value() ? value.value() : "identifier";
        case TokenType::LBRACE:
            return "LBrace";
        case TokenType::RBRACE:
            return "RBrace";
        case TokenType::COLON:
            return "Colon";
        case TokenType::SEMICOLON:
            return "SemiColon";
        case TokenType::LPAREN:
            return "LParen";
        case TokenType::RPAREN:
            return "RParen";
        case TokenType::NUMBER:
            return "number";
        case TokenType::COMMA:
            return "comma";
        case TokenType::SLASH:
            return "slash";
        case TokenType::ASTERISK:
            return "asterisk";
        case TokenType::MINUS:
            return "minus";
        case TokenType::PLUS:
            return "plus";
        case TokenType::EOFTOK:
            return "EOF";
        default:
            return "single";
        }
    }
};


#endif