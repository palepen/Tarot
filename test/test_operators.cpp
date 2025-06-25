#include <catch2/catch_test_macros.hpp>
#include <string>
#include <sstream>
#include <functional>
#include <iostream>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Source.h"
#include "test_helper.h"

// Utility to capture stderr output during a dump call
static std::string captureDump(const std::function<void()>& dumpFn) {
    std::ostringstream oss;
    auto* oldBuf = std::cerr.rdbuf(oss.rdbuf());
    dumpFn();
    std::cerr.rdbuf(oldBuf);
    return oss.str();
}

TEST_CASE("Parser: Simple addition", "[Parser]") {
    std::string path = "simple_add.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    bool ok     = parseRes.second;
    REQUIRE(ok);

    auto dumpOutput = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    REQUIRE(dumpOutput.find("BinaryOperator: '+'") != std::string::npos);
}

TEST_CASE("Parser: Multiplication and addition precedence", "[Parser]") {
    std::string path = "prec.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    bool ok     = parseRes.second;
    REQUIRE(ok);

    auto ast = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    REQUIRE(ast.find("BinaryOperator: '+'") < ast.find("BinaryOperator: '*'") );
}

TEST_CASE("Parser: Left-associativity of addition", "[Parser]") {
    std::string path = "assoc_left.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    bool ok     = parseRes.second;
    REQUIRE(ok);

    auto s = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    auto pos1 = s.find("BinaryOperator: '+'");
    auto pos2 = s.find("BinaryOperator: '+'", pos1 + 1);
    REQUIRE(pos1 != std::string::npos);
    REQUIRE(pos2 != std::string::npos);
}

TEST_CASE("Parser: Grouping overrides precedence", "[Parser]") {
    std::string path = "group.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    bool ok     = parseRes.second;
    REQUIRE(ok);

    auto ast = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    REQUIRE(ast.find("BinaryOperator: '*'") < ast.find("BinaryOperator: '+'"));
}

TEST_CASE("Parser: Unary negation", "[Parser]") {
    std::string path = "unary.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    bool ok     = parseRes.second;
    REQUIRE(ok);

    auto dumpOutput = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    REQUIRE(dumpOutput.find("UnaryOperator: '-'") != std::string::npos);
}

TEST_CASE("Parser: Nested prefix and binary", "[Parser]") {
    std::string path = "nested_ops.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    bool ok     = parseRes.second;
    REQUIRE(ok);

    auto ast = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    REQUIRE(ast.find("BinaryOperator: '*'") != std::string::npos);
    REQUIRE(ast.find("UnaryOperator: '-'") != std::string::npos);
}
