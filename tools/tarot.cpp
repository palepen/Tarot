#include <iostream>
#include <filesystem>
#include <fstream>
#include "libtarot/Parser.h"
#include "libtarot/Sema.h"
#include "libtarot/Codegen.h"
#include "libtarot/ControlFlow.h"
void displayHelp()
{
    std::cout << "Usage:\n"
              << "    tarot [options] <source_file>\n\n"
              << "Options:\n"
              << "    -h          help\n"
              << "    -o <file>   write executable to <file>\n"
              << "    -ast-dump   print the abstract syntax tree\n"
              << "    -res-dump   print the resolved syntax tree\n"
              << "    -llvm-dump  print the llvm module\n"
              << "    -cfg-dump    print the control flow graph\n";
}

struct CompilerOptions
{
    std::filesystem::path source;
    std::filesystem::path output;
    bool displayHelp = false;
    bool astDump = false;
    bool resDump = false;
    bool cfgDump = false;
    bool llvmDump = false;
};

[[noreturn]] void error(std::string_view msg)
{
    std::cerr << "error: " << msg << '\n';
    std::exit(1);
}

CompilerOptions parseArguments(int argc, const char **argv)
{
    CompilerOptions options;

    int idx = 1;
    while (idx < argc)
    {
        std::string_view arg = argv[idx];

        if (arg[0] != '-')
        {
            if (!options.source.empty())
            {
                error("unexpected argument '" + std::string(arg) + '\'');
            }

            options.source = arg;
        }
        else
        {
            if (arg == "-h")
                options.displayHelp = true;
            else if (arg == "-o")
                options.output = ++idx >= argc ? "" : argv[idx];
            else if (arg == "-ast-dump")
                options.astDump = true;
            else if (arg == "-res-dump")
                options.resDump = true;
            else if (arg == "-llvm-dump")
                options.llvmDump = true;
            else if (arg == "-cfg-dump")
                options.cfgDump = true;

            else
                error("unexpected option '" + std::string(arg) + "\'");
        }
        ++idx;
    }
    return options;
}

int main(int argc, const char **argv)
{

    CompilerOptions options = parseArguments(argc, argv);

    if (options.displayHelp)
    {
        displayHelp();
        return 0;
    }

    if (options.source.empty())
    {
        error("no source file specified");
    }

    std::ifstream file(options.source);

    if (!file)
    {
        error("failed to open '" + options.source.string() + "\'");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    SourceFile sourceFile = {options.source.c_str(), buffer.str()};

    Lexer lexer(&sourceFile);
    Parser parser(lexer);

    auto [ast, success] = parser.parseSourceFile(true);

    if (options.astDump)
    {
        for (auto &it : ast)
        {
            it->dump(0);
        }
        return 0;
    }

    if (!success)
        return 1;

    Sema sema(ast);
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree = sema.resolveAST();

    if (options.resDump)
    {
        for (auto &&fn : resolvedTree)
            fn->dump();

        return 0;
    }

    if (options.cfgDump)
    {
        for (auto &&fn : resolvedTree)
        {
            std::cerr << fn->identifier << ':' << '\n';
            CFGBuilder().build(*fn).dump();
        }
        return 0;
    }

    if (resolvedTree.empty())
        return 1;

    Codegen codegen(resolvedTree, options.source.string());

    llvm::Module *llvmIR = codegen.generateIR();

    if (options.llvmDump)
    {
        llvmIR->print(llvm::outs(), nullptr);
        ;
        return 0;
    }

    std::stringstream path;
    path << "tmp-" << std::filesystem::hash_value(options.source) << ".ll";
    const std::string &llvmIRPath = path.str();
    std::error_code errorCode;

    llvm::raw_fd_ostream f(llvmIRPath, errorCode);
    llvmIR->print(f, nullptr);

    std::stringstream command;
    command << "clang " << llvmIRPath;

    if (!options.output.empty())
    {
        command << " -o " << options.output.c_str();
    }

    std::cout << command.str() << std::endl;
    int ret = std::system(command.str().c_str());
    std::filesystem::remove(llvmIRPath);
    return ret;
}