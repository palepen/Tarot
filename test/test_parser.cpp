#include <catch2/catch_test_macros.hpp>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Source.h"
#include "include/test_helper.h"

TEST_CASE("Parser: Simple main function", "[Parser]")
{
    std::string path = "main_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(true);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "main");
    REQUIRE(fn->type == Type::builtInVoid());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.empty());
}

TEST_CASE("Parser: Function with parameters", "[Parser]")
{
    std::string path = "params_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "add");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.size() == 2);
    REQUIRE(fn->params[0]->identifier == "a");
    REQUIRE(fn->params[0]->type == Type::builtInNumber());
    REQUIRE(fn->params[1]->identifier == "b");
    REQUIRE(fn->params[1]->type == Type::builtInNumber());
    REQUIRE(fn->body->statements.empty());
}

TEST_CASE("Parser: Return statement with literal", "[Parser]")
{
    std::string path = "return_literal.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 2);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "getFive");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto &stmt = fn->body->statements[0];
    auto returnStmt = dynamic_cast<ReturnStatement *>(stmt.get());
    REQUIRE(returnStmt != nullptr);
    REQUIRE(returnStmt->expr != nullptr);
    auto numberLiteral = dynamic_cast<NumberLiteral *>(returnStmt->expr.get());
    REQUIRE(numberLiteral != nullptr);
    REQUIRE(numberLiteral->value == "5");
}

TEST_CASE("Parser: Function call expression", "[Parser]")
{
    std::string path = "function_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 2);
    auto &fn0 = functions[0];
    REQUIRE(fn0->identifier == "add");
    REQUIRE(fn0->type == Type::builtInNumber());
    REQUIRE(fn0->params.size() == 2);
    REQUIRE(fn0->body->statements.size() == 1);
    auto &fn = functions[1];
    REQUIRE(fn->identifier == "compute");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
}

TEST_CASE("Parser: Nested function calls", "[Parser]")
{
    std::string path = "nested_calls.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "nested");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto &stmt = fn->body->statements[0];
    auto outerCall = dynamic_cast<CallExpression *>(stmt.get());
    REQUIRE(outerCall != nullptr);
    auto outerCallee = dynamic_cast<DeclRefExpression *>(outerCall->callee.get());
    REQUIRE(outerCallee != nullptr);
    REQUIRE(outerCallee->identifier == "outer");
    REQUIRE(outerCall->arguments.size() == 1);
    auto innerCall = dynamic_cast<CallExpression *>(outerCall->arguments[0].get());
    REQUIRE(innerCall != nullptr);
    auto innerCallee = dynamic_cast<DeclRefExpression *>(innerCall->callee.get());
    REQUIRE(innerCallee != nullptr);
    REQUIRE(innerCallee->identifier == "inner");
    REQUIRE(innerCall->arguments.size() == 1);
    auto arg = dynamic_cast<NumberLiteral *>(innerCall->arguments[0].get());
    REQUIRE(arg != nullptr);
    REQUIRE(arg->value == "3");
}

TEST_CASE("Parser: Multiple statements", "[Parser]")
{
    std::string path = "multiple_statements.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "complex");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 2);
    auto callStmt = dynamic_cast<CallExpression *>(fn->body->statements[0].get());
    REQUIRE(callStmt != nullptr);
    auto callee = dynamic_cast<DeclRefExpression *>(callStmt->callee.get());
    REQUIRE(callee != nullptr);
    REQUIRE(callee->identifier == "log");
    REQUIRE(callStmt->arguments.size() == 1);
    auto arg = dynamic_cast<NumberLiteral *>(callStmt->arguments[0].get());
    REQUIRE(arg != nullptr);
    REQUIRE(arg->value == "1");
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn->body->statements[1].get());
    REQUIRE(returnStmt != nullptr);
    auto retVal = dynamic_cast<NumberLiteral *>(returnStmt->expr.get());
    REQUIRE(retVal != nullptr);
    REQUIRE(retVal->value == "42");
}

TEST_CASE("Parser: Custom type", "[Parser]")
{
    std::string path = "custom_type.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "getPoint");
    REQUIRE(fn->type == Type::builtInCustom("Point"));
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn->body->statements[0].get());
    REQUIRE(returnStmt != nullptr);
    auto callExpr = dynamic_cast<CallExpression *>(returnStmt->expr.get());
    REQUIRE(callExpr != nullptr);
    auto callee = dynamic_cast<DeclRefExpression *>(callExpr->callee.get());
    REQUIRE(callee != nullptr);
    REQUIRE(callee->identifier == "origin");
    REQUIRE(callExpr->arguments.empty());
}

TEST_CASE("Parser: Invalid syntax", "[Parser]")
{
    std::string path = "invalid_syntax.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(true);

    REQUIRE(success == false);
    REQUIRE(functions.empty());
}

TEST_CASE("Parser: Empty return", "[Parser]")
{
    std::string path = "empty_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 2);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "noValue");
    REQUIRE(fn->type == Type::builtInVoid());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn->body->statements[0].get());
    REQUIRE(returnStmt != nullptr);
    REQUIRE(returnStmt->expr == nullptr);
}

TEST_CASE("Parser: Multiple functions", "[Parser]")
{
    std::string path = "multiple_functions.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(true);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 2);
    auto &fn1 = functions[0];
    REQUIRE(fn1->identifier == "helper");
    REQUIRE(fn1->type == Type::builtInNumber());
    REQUIRE(fn1->params.empty());
    REQUIRE(fn1->body->statements.size() == 1);
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn1->body->statements[0].get());
    REQUIRE(returnStmt != nullptr);
    auto retVal = dynamic_cast<NumberLiteral *>(returnStmt->expr.get());
    REQUIRE(retVal != nullptr);
    REQUIRE(retVal->value == "10");
    auto &fn2 = functions[1];
    REQUIRE(fn2->identifier == "main");
    REQUIRE(fn2->type == Type::builtInVoid());
    REQUIRE(fn2->params.empty());
    REQUIRE(fn2->body->statements.size() == 1);
    auto callStmt = dynamic_cast<CallExpression *>(fn2->body->statements[0].get());
    REQUIRE(callStmt != nullptr);
    auto callee = dynamic_cast<DeclRefExpression *>(callStmt->callee.get());
    REQUIRE(callee != nullptr);
    REQUIRE(callee->identifier == "helper");
    REQUIRE(callStmt->arguments.empty());
}