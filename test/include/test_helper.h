#ifndef TEST_HELPER_H
#define TEST_HELPER_H
#include <string>
#include <vector>
#include <string>
#include <memory>
#include "libtarot/Parser.h"
#include "libtarot/Lexer.h"
#include "libtarot/Token.h"
#include "libtarot/TokenType.h"
#include "libtarot/Source.h"

SourceFile createSourceFile(const std::string &path, const std::string &content);

std::vector<Token> collectTokens(Lexer &lexer);
std::string readFile(const std::string& path);

#endif