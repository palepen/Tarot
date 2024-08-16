#include <iostream>
#include <fstream>
#include "../includes/Parser.h"

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
    std::pair<std::vector<std::unique_ptr<FunctionalDecl>>, bool> AST = parse.parseSourceFile();

    for (auto &it : AST.first)
    {        
        std::cout << "Identifer: " << it->identifier << std::endl;
    }
}