#include "../includes/Parser.h"

std::nullptr_t report(SourceLocation location, std::string_view message, bool isWarning)
{
    const auto &[file, line, col] = location;
    std::cerr << file << ":" << line << ":" << col << ":" << (isWarning ? "warning: " : "error: ") << message << "\n";
    return nullptr;
}

std::unique_ptr<FunctionalDecl> Parser::parseFunctionDecl()
{
    SourceLocation location = nextToken.source;
    eatNextToken();

    matchOrReturn(TokenType::IDENTIFIER, "expected identifier");

    std::string functionIdentifier = *nextToken.value;
    eatNextToken();

    matchOrReturn(TokenType::LPAREN, "Expected '('");
    eatNextToken();

    matchOrReturn(TokenType::RPAREN, "Expected ')'");
    eatNextToken();

    matchOrReturn(TokenType::COLON, "Expected ':'");
    eatNextToken();

    varOrReturn(type, parseType());

    matchOrReturn(TokenType::LBRACE, "Expected function Body");
    varOrReturn(block, parseBlock());

    return std::make_unique<FunctionalDecl>(location, type ? functionIdentifier : "No Valid Name", *type, std::move(block));
}

std::optional<Type> Parser::parseType()
{
    TokenType type = nextToken.type;

    switch (type)
    {
    case TokenType::VOID:
    {
        eatNextToken();
        return Type::builtInVoid();
        break;
    }
    case TokenType::IDENTIFIER:
    {
        auto t = Type::builtInCustom(*nextToken.value);
        eatNextToken();
        return t;
    }
    default:
    {
        report(nextToken.source, "Expected Type Specifier");
        return std::nullopt;
    }
    }
}

std::unique_ptr<Block> Parser::parseBlock()
{
    SourceLocation location = nextToken.source;
    eatNextToken();

    matchOrReturn(TokenType::RBRACE, "Expected '}'");
    eatNextToken();

    return std::make_unique<Block>(location);
}

void Parser::synchronizeOn(TokenType type)
{
    incompleteAST = true;
    while (nextToken.type != type && nextToken.type != TokenType::EOFTOK)
    {
        eatNextToken();
    }
};

std::pair<std::vector<std::unique_ptr<FunctionalDecl>>, bool> Parser::parseSourceFile()
{
    bool hasMainFunction = false;
    std::vector<std::unique_ptr<FunctionalDecl>> functions;
    while (nextToken.type != TokenType::EOFTOK)
    {
        if (nextToken.type != TokenType::FN)
        {
            report(nextToken.source, "Only Function Declarations are Allowed");
            synchronizeOn(TokenType::FN);
            continue;
        }
        auto fn = parseFunctionDecl();

        if (fn)
            functions.emplace_back(std::move(fn));
    }

    for (auto &&fn : functions)
    {
        hasMainFunction |= fn->identifier == "main";
    }

    if (!hasMainFunction && !incompleteAST)
    {
        report(nextToken.source, "Main Function Not Found");
    }

    return {std::move(functions), !incompleteAST && hasMainFunction};
}
