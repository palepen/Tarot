#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Lexer.h"
#include "Declaration.h"
#include "Report.h"

#define varOrReturn(var, init) \
    auto var = (init);         \
    if (!var)                  \
        return nullptr;

#define matchOrReturn(tok, msg) \
    if (nextToken.type != tok)  \
        report(nextToken.source, msg);

class Parser
{
private:
    Lexer *lexer;
    Token nextToken;

public:
    bool incompleteAST = false;
    explicit Parser(Lexer &lexer)
        : lexer(&lexer), nextToken(lexer.getNextToken())
    {
    }
    void eatNextToken()
    {
        nextToken = lexer->getNextToken();
    }

    std::pair<std::vector<std::unique_ptr<FunctionDecl>>, bool> parseSourceFile(bool isTestingWithoutMain);
    std::unique_ptr<FunctionDecl> parseFunctionDecl();
    std::optional<Type> parseType();
    std::unique_ptr<Block> parseBlock();
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<ReturnStatement> parseReturnStatement();
    std::unique_ptr<Expression> parsePrimary();
    std::unique_ptr<Expression> parsePostFixExpression();
    std::unique_ptr<std::vector<std::unique_ptr<Expression>>> parseArgumentList();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<ParameterDecl> parseParamDecl();
    std::unique_ptr<std::vector<std::unique_ptr<ParameterDecl>>> parseParameterList();
    std::unique_ptr<Expression> parseExpressionRHS(std::unique_ptr<Expression> lhs, int precedence);
    std::unique_ptr<Expression> parsePrefixExpression();
    void synchronizeOn(TokenType type);
    void synchronize();
};

#endif