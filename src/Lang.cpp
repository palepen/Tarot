#include <iostream>
#include <fstream>
#include "../includes/Lexer.h"

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

    while (lex.idx < line.length())
    {
        std::cout << lex.getNextToken().to_string() << std::endl;
    }
}