#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <unordered_map>
#include <optional>
#include <string_view>
#include <values.h>
#include "TokenType.h"
#include "Source.h"

const std::unordered_map<std::string_view, TokenType>
    keywords = {
        {"fn", TokenType::FN},
        {"void", TokenType::VOID}};


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
        case TokenType::IDENTIFIER:
            return value.has_value() ? value.value() : "identifier";
        case TokenType::LBRACE:
            return "{";
        case TokenType::RBRACE:
            return "}";
        default:
            return "single";
        }
    }
};

#endif