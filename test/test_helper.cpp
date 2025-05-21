#include "include/test_helper.h"
#include <fstream>
#include <sstream>
#include <filesystem>

SourceFile createSourceFile(const std::string &path, const std::string &content)
{
    return SourceFile(path, content);
}

// Helper function to collect all tokens from a lexer
std::vector<Token> collectTokens(Lexer &lexer)
{
    std::vector<Token> tokens;
    Token token;
    do
    {
        token = lexer.getNextToken();
        tokens.push_back(token);
    } while (token.type != TokenType::EOFTOK);
    return tokens;
}




std::string readFile(const std::string& path) {
    std::string full_path = path;
#ifdef EXAMPLE_DIR
    if (path.find('/') == std::string::npos) {
        full_path = std::string(EXAMPLE_DIR) + "/" + path;
    }
#endif
    
    std::ifstream file(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + full_path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

