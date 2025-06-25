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

TEST_CASE("Parser: Constexpr simple math", "[Parser][constexpr]") {
    std::string path = "simple_constexpr.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    // Should see a BinaryOperator: '+' and '*'
    auto output = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    REQUIRE(output.find("BinaryOperator: '+'") != std::string::npos);
    REQUIRE(output.find("BinaryOperator: '*'") != std::string::npos);
}

TEST_CASE("Parser: Constexpr used in main expression", "[Parser][constexpr]") {
    std::string path = "constexpr_in_expr.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    // Should see a BinaryOperator: '*'
    auto output = captureDump([&]{ fns[0]->body->statements[0]->dump(0); });
    REQUIRE(output.find("BinaryOperator: '*'") != std::string::npos);
}

TEST_CASE("Parser: Constexpr call chain", "[Parser][constexpr]") {
    std::string path = "const_call_chain.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    // Should see a function call expression in getFive
    auto output = captureDump([&]{ fns[1]->body->statements[0]->dump(0); });
    REQUIRE(output.find("Call Expr") != std::string::npos);
}

TEST_CASE("Parser: Constexpr in condition", "[Parser][constexpr]") {
    std::string path = "const_in_cond.t";
    std::string src = readFile(path);
    SourceFile sf = createSourceFile(path, src);
    Lexer lexer(&sf);
    Parser parser(lexer);
    auto parseRes = parser.parseSourceFile(false);
    auto &fns = parseRes.first;
    REQUIRE(parseRes.second);

    // Should see an IfStatement and a CallExpression for isZero()
    auto output = captureDump([&]{ fns[1]->body->statements[0]->dump(0); });
    REQUIRE(output.find("IfStatement") != std::string::npos);
    REQUIRE(output.find("Call Expr") != std::string::npos);
}
