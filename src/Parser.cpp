#include "../includes/Parser.h"

std::pair<std::vector<std::unique_ptr<FunctionDecl>>, bool> Parser::parseSourceFile()
{
    bool hasMainFunction = false;
    std::vector<std::unique_ptr<FunctionDecl>> functions;
    while (nextToken.type != TokenType::EOFTOK)
    {
        if (nextToken.type != TokenType::FN)
        {
            report(nextToken.source, "Unexpected Token: " + nextToken.to_string());
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

std::unique_ptr<FunctionDecl> Parser::parseFunctionDecl()
{
    SourceLocation location = nextToken.source;
    eatNextToken(); // fn

    std::string functionIdentifier = *nextToken.value;

    matchOrReturn(TokenType::IDENTIFIER, "expected identifier");
    eatNextToken();

    
    varOrReturn(parameterList, parseParameterList());
    eatNextToken();


    matchOrReturn(TokenType::COLON, "Expected ':'");
    eatNextToken();

    varOrReturn(type, parseType());

    matchOrReturn(TokenType::LBRACE, "Expected function Body");
    varOrReturn(block, parseBlock());

    return std::make_unique<FunctionDecl>(location, functionIdentifier, *type, std::move(block), std::move(parameterList));
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
    case TokenType::NUMBER:
    {
        eatNextToken();
        return Type::builtInNumber();
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
    eatNextToken(); // {

    std::vector<std::unique_ptr<Statement>> statements;

    while (true)
    {
        if (nextToken.type == TokenType::RBRACE)
            break;
        varOrReturn(stmt, parseStatement());
        if (!stmt)
        {
            synchronize();
            continue;
        }
        if (nextToken.type == TokenType::EOFTOK || nextToken.type == TokenType::FN)
            return report(nextToken.source, "Expected '} at the end of block");

        statements.emplace_back(std::move(stmt));
    }

    matchOrReturn(TokenType::RBRACE, "Expected '}'");
    eatNextToken(); // }

    matchOrReturn(TokenType::SEMICOLON, "Expected ';'");
    eatNextToken(); // ;

    return std::make_unique<Block>(location, std::move(statements));
}

void Parser::synchronizeOn(TokenType type)
{
    incompleteAST = true;
    while (nextToken.type != type && nextToken.type != TokenType::EOFTOK)
    {
        eatNextToken();
    }
};

std::unique_ptr<Statement> Parser::parseStatement()
{
    
    if (nextToken.type == TokenType::RETURN)
        return parseReturnStatement();

    varOrReturn(expr, parseExpression());
    matchOrReturn(TokenType::SEMICOLON, "Expected ';' at the end of expression")
        eatNextToken();

    return expr;
}

std::unique_ptr<ReturnStatement> Parser::parseReturnStatement()
{
    SourceLocation location = nextToken.source;
    eatNextToken(); // return

    std::unique_ptr<Expression> expr;
    if (nextToken.type != TokenType::SEMICOLON)
    {
        expr = parseExpression();
        if (!expr)
        {
            return nullptr;
        }
    }

    matchOrReturn(TokenType::SEMICOLON, "Expected ';' at the end of the return statement")
        eatNextToken(); // ;

    return std::make_unique<ReturnStatement>(location, std::move(expr));
}

std::unique_ptr<Expression> Parser::parsePrimary()
{
    SourceLocation location = nextToken.source;
    if (nextToken.type == TokenType::NUMBER)
    {
        auto literal = std::make_unique<NumberLiteral>(location, *nextToken.value);
        eatNextToken();
        return literal;
    }

    if (nextToken.type == TokenType::IDENTIFIER)
    {
        auto declRefExpr = std::make_unique<DeclRefExpression>(location, *nextToken.value);
        eatNextToken();
        return declRefExpr;
    }

    return report(location, "Expected Expression");
}

std::unique_ptr<Expression> Parser::parsePostFixExpression()
{
    varOrReturn(expr, parsePrimary());

    if (nextToken.type != TokenType::LPAREN)
        return expr;

    SourceLocation location = nextToken.source;
    varOrReturn(argumentList, parseArgumentList());

    return std::make_unique<CallExpression>(location, std::move(expr), std::move(*argumentList));
}

std::unique_ptr<std::vector<std::unique_ptr<Expression>>> Parser::parseArgumentList()
{
    matchOrReturn(TokenType::LPAREN, "expected '('");
    eatNextToken(); // (

    std::vector<std::unique_ptr<Expression>> argumentList;

    while (true)
    {
        if (nextToken.type == TokenType::RPAREN)
            break;

        varOrReturn(expr, parseExpression());

        argumentList.emplace_back(std::move(expr));

        if (nextToken.type != TokenType::COMMA)
            break;
        eatNextToken(); // ,
    }

    matchOrReturn(TokenType::RPAREN, "expected ')'");
    eatNextToken(); // )

    return std::make_unique<std::vector<std::unique_ptr<Expression>>>(std::move(argumentList));
}

std::unique_ptr<Expression> Parser::parseExpression()
{
    return parsePostFixExpression();
}

std::unique_ptr<ParameterDecl> Parser::parseParamDecl()
{
    SourceLocation location = nextToken.source;

    std::string identifier = *nextToken.value;
    eatNextToken();


    matchOrReturn(TokenType::COLON, "Expected ':'");
    eatNextToken();

    varOrReturn(type, parseType());
    return std::make_unique<ParameterDecl>(location, std::move(identifier), std::move(*type));
}

std::unique_ptr<std::vector<std::unique_ptr<ParameterDecl>>> Parser::parseParameterList()
{
    matchOrReturn(TokenType::LPAREN, "Expected '('");
    eatNextToken();

    std::vector<std::unique_ptr<ParameterDecl>> parameterlist;

    while (true)
    {
        if (nextToken.type == TokenType::RPAREN)
            break;
        matchOrReturn(TokenType::IDENTIFIER, "Expected parameter Declaration");

        varOrReturn(parameterDecl, parseParamDecl());
        parameterlist.emplace_back(std::move(parameterDecl));
        
        std::cout << nextToken.to_string() << std::endl;
        if (nextToken.type != TokenType::COMMA)
            break;
        eatNextToken();
    }

    return std::make_unique<std::vector<std::unique_ptr<ParameterDecl>>>(std::move(parameterlist));
};

void Parser::synchronize()
{
    incompleteAST = true;
    int braces = 0;
    while (true)
    {
        TokenType type = nextToken.type;

        if (type == TokenType::LBRACE)
        {
            ++braces;
        }
        else if (type == TokenType::RBRACE)
        {
            if (braces == 0)
                break;

            if (braces == 1)
            {
                eatNextToken();
                break;
            }
            --braces;
        }
        else if (type == TokenType::SEMICOLON && braces == 0)
        {
            eatNextToken();
            break;
        }
        else if (type == TokenType::FN || type == TokenType::EOFTOK)
        {
            break;
        }
        eatNextToken();
    }
}