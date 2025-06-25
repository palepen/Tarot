#include <catch2/catch_test_macros.hpp>
#include <string>
#include <sstream>
#include <functional>
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

TEST_CASE("Parser: Simple variable declaration", "[Parser][variables]") {
    std::string path = "simple_var.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto [functions, ok] = parser.parseSourceFile(false);
    REQUIRE(ok);
    REQUIRE(functions.size() == 2); // foo, main

    // foo function
    auto &foo = functions[0];
    REQUIRE(foo->body->statements.size() == 2);
    // 1st statement: let x = 5;
    auto declStmtDump = captureDump([&]{ foo->body->statements[0]->dump(0); });
    REQUIRE(declStmtDump.find("DeclStmt:") != std::string::npos);
    REQUIRE(declStmtDump.find("VarDecl: x") != std::string::npos);
    REQUIRE(declStmtDump.find("NumberLiteral: '5'") != std::string::npos);
}

TEST_CASE("Parser: Variable reassignment", "[Parser][variables]") {
    std::string path = "reassign.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto [functions, ok] = parser.parseSourceFile(false);
    REQUIRE(ok);

    auto &bar = functions[0];
    REQUIRE(bar->body->statements.size() == 3);
    // 2nd statement: y = y + 2;
    auto assignDump = captureDump([&]{ bar->body->statements[1]->dump(0); });
    REQUIRE(assignDump.find("Assignment:") != std::string::npos);
    REQUIRE(assignDump.find("Identifier: 'y'") != std::string::npos);
    REQUIRE(assignDump.find("BinaryOperator: '+'") != std::string::npos);
}

TEST_CASE("Parser: Multiple variable declarations", "[Parser][variables]") {
    std::string path = "multiple_vars.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);

    Lexer lexer(&sf);
    Parser parser(lexer);
    auto [functions, ok] = parser.parseSourceFile(false);
    REQUIRE(ok);

    auto &baz = functions[0];
    REQUIRE(baz->body->statements.size() == 3);
    auto decl1 = captureDump([&]{ baz->body->statements[0]->dump(0); });
    auto decl2 = captureDump([&]{ baz->body->statements[1]->dump(0); });
    REQUIRE(decl1.find("VarDecl: a") != std::string::npos);
    REQUIRE(decl2.find("VarDecl: b") != std::string::npos);
}

TEST_CASE("Parser: Variable initialized with expression", "[Parser][variables]") {
    std::string path = "expr_var.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto [functions, ok] = parser.parseSourceFile(false);
    REQUIRE(ok);

    auto &qux = functions[0];
    REQUIRE(qux->body->statements.size() == 2);
    auto initDump = captureDump([&]{ qux->body->statements[0]->dump(0); });
    REQUIRE(initDump.find("BinaryOperator: '*'") != std::string::npos);
    REQUIRE(initDump.find("BinaryOperator: '+'") != std::string::npos);
}
