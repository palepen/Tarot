#include <iostream>
#include <fstream>
#include "libtrt/Parser.h"
#include "libtrt/Sema.h"

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


    // std::cout << "hello\n"; 
    // for (auto &it : AST.first)
    // {
    //     it->dump(0);
    // }
    Sema sema(AST.first);


    sema.resolveAST();
}