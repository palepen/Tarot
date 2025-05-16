#include <iostream>
#include <fstream>
#include "libtarot/Parser.h"
#include "libtarot/Sema.h"
#include "libtarot/Codegen.h"

int main(int argc, char *argv[])
{

    if(argc == 1)
    {
        std::cout << "Invalid arguments\n";
        std::cout << "Usage:\n\ttarot <executable>\n";
        return 1;
    }
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
    Sema sema(AST.first);

    auto resolvedAst = sema.resolveAST();
    Codegen codegen(resolvedAst, argv[1]);
    
    llvm::Module *module = codegen.generateIR();

    module->print(llvm::errs(), nullptr);
    return 0;
}