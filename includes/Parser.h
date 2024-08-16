#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Lexer.h"
#include "Declaration.h"
#define varOrReturn(var, init) \
    auto var = (init);         \
    if (!var)                  \
        return nullptr;        

#define matchOrReturn(tok, msg) \
    if (nextToken.type != tok)  \
        report(nextToken.source, msg); 

std::nullptr_t report(SourceLocation location, std::string_view message, bool isWarning = false);

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

    std::pair<std::vector<std::unique_ptr<FunctionalDecl>>, bool> parseSourceFile();
    std::unique_ptr<FunctionalDecl> parseFunctionDecl();
    std::optional<Type> parseType();
    std::unique_ptr<Block> parseBlock();
    void synchronizeOn(TokenType type);
    
};

#endif