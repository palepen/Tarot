#include <iostream>
#include <fstream>
#include "../includes/Parser.h"
#include "../includes/Sema.h"

int main(int argc, char *argv[])
{
    std::ifstream inp(argv[1]);
    if (!inp)
    {
        std::cerr << "";
    }
    std::string buf;
    std::string line = "";
    while (std::getline(inp, buf))
    {
        if (line == "")
            line = buf;
        else
            line += "\n" + buf;
    }

    Lexer lex(argv[1], line);

    Parser parse(lex);

    std::pair<std::vector<std::unique_ptr<FunctionDecl>>, bool> AST = parse.parseSourceFile();
    for (auto &it : AST.first)
    {

        it->dump(0);
    }

    printf("SEMA BEGIN\n");
    Sema sema(AST.first);
    printf("SEMA END\n");

    printf("RESOLVE AST BEGIN\n");
    sema.resolveAST();
    printf("RESOLVE AST END\n");
    for (auto &it : sema.ast)
    {
        it->dump(0);
    }
}