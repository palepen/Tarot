#include <catch2/catch_test_macros.hpp>
#include <string>
#include <sstream>
#include <functional>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Source.h"
#include "test_helper.h"

static std::string captureDump(const std::function<void()> &dumpFn)
{
    std::ostringstream oss;
    auto *oldBuf = std::cerr.rdbuf(oss.rdbuf());
    dumpFn();
    std::cerr.rdbuf(oldBuf);
    return oss.str();
}

TEST_CASE("Parser: Simple if statement", "[Parser][control-flow]")
{
    std::string path = "simple_if.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    // Check that the function has an if statement
    auto output = captureDump([&]
                              { fns[0]->body->statements[0]->dump(0); });
    REQUIRE(output.find("IfStatement") != std::string::npos);
}

TEST_CASE("Parser: If-else statement", "[Parser][control-flow]")
{
    std::string path = "if_else.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    // Should contain IfStatement and two blocks
    auto output = captureDump([&]
                              { fns[0]->body->statements[0]->dump(0); });
    REQUIRE(output.find("IfStatement") != std::string::npos);
    REQUIRE(output.find("Block") != std::string::npos);
}

TEST_CASE("Parser: Else if chain", "[Parser][control-flow]")
{
    std::string path = "else_if_chain.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    // Should show nested IfStatements
    auto output = captureDump([&]
                              { fns[0]->body->statements[0]->dump(0); });
    REQUIRE(output.find("IfStatement") != std::string::npos);
}

TEST_CASE("Parser: While loop", "[Parser][control-flow]")
{
    std::string path = "while.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    auto output = captureDump([&]
                              { fns[0]->body->statements[1]->dump(0); });
    REQUIRE(output.find("WhileStatement") != std::string::npos);
}

TEST_CASE("Parser: Nested control flow", "[Parser][control-flow]")
{
    std::string path = "nested.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    auto output = captureDump([&] { fns[0]->body->statements[1]->dump(0); });
    REQUIRE(output.find("IfStatement") != std::string::npos);
    REQUIRE(output.find("WhileStatement") != std::string::npos);
}
