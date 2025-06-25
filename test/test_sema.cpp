#include <catch2/catch_test_macros.hpp>
#include <string>
#include <memory>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Sema.h"
#include "libtarot/Source.h"
#include "test_helper.h"

TEST_CASE("Sema: Valid multiple functions with call", "[Sema]")
{
    std::string path = "multiple_functions.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions, false);

    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, helper, main
    REQUIRE(resolved[0]->identifier == "println");
    REQUIRE(resolved[1]->identifier == "helper");
    REQUIRE(resolved[2]->identifier == "main");
    REQUIRE(resolved[2]->body->statements.size() == 1);
}

TEST_CASE("Sema: Valid function call with definition", "[Sema]")
{
    std::string path = "valid_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions, false);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, add, main
    REQUIRE(resolved[1]->identifier == "add");
    REQUIRE(resolved[2]->identifier == "main");
    REQUIRE(resolved[2]->body->statements.size() == 1);
}

TEST_CASE("Sema: Undefined function call", "[Sema]")
{
    std::string path = "function_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to undefined 'add'
}

TEST_CASE("Sema: Custom type failure", "[Sema]")
{
    std::string path = "custom_type.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to custom type 'Point'
}

TEST_CASE("Sema: Valid main function", "[Sema]")
{
    std::string path = "main_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main
    REQUIRE(resolved[1]->identifier == "main");
    REQUIRE(resolved[1]->type.kind == Type::Kind::Void);
    REQUIRE(resolved[1]->params.empty());
}

TEST_CASE("Sema: Invalid main with parameters", "[Sema]")
{
    std::string path = "invalid_main.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to main with parameters
}

TEST_CASE("Sema: Invalid main with non-void return", "[Sema]")
{
    std::string path = "invalid_main_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to main returning number
}

TEST_CASE("Sema: Valid number return statement", "[Sema]")
{
    std::string path = "return_literal.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions,false);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, getFive, main
    REQUIRE(resolved[1]->identifier == "getFive");
    REQUIRE(resolved[1]->type.kind == Type::Kind::Number);
    REQUIRE(resolved[1]->body->statements.size() == 1);
}

TEST_CASE("Sema: Valid empty return in void function", "[Sema]")
{
    std::string path = "empty_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, noValue, main
    REQUIRE(resolved[1]->identifier == "noValue");
    REQUIRE(resolved[1]->type.kind == Type::Kind::Void);
}

TEST_CASE("Sema: Invalid return value in void function", "[Sema]")
{
    std::string path = "invalid_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to void function returning value
}

TEST_CASE("Sema: Missing return value in non-void function", "[Sema]")
{
    std::string path = "missing_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions, /*bailOnError=*/false);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty() == false); // Fails due to missing return value
}

TEST_CASE("Sema: Function redeclaration", "[Sema]")
{
    std::string path = "redeclare.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to redeclaration of 'foo'
}

TEST_CASE("Sema: Valid println call with number", "[Sema]")
{
    std::string path = "println_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main
    REQUIRE(resolved[1]->identifier == "main");
    REQUIRE(resolved[1]->body->statements.size() == 1);
}

TEST_CASE("Sema: Invalid println with wrong argument count", "[Sema]")
{
    std::string path = "invalid_println.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);
    Sema sema(functions, /*bailOnError=*/false);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty() == false); // Fails due to no arguments to println
}

TEST_CASE("Sema: Parameter type validation", "[Sema]")
{
    std::string path = "invalid_param.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to void parameter type
}

TEST_CASE("Sema: Unreachable code after return", "[Sema]")
{
    std::string path = "unreachable.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions, false);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, foo, main (warning for unreachable)
    REQUIRE(resolved[1]->body->statements.size() == 2);
}

TEST_CASE("Sema: Valid nested function call", "[Sema]")
{
    std::string path = "nested_calls.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to undefined 'outer' and 'inner'
}

TEST_CASE("Sema: Multiple statements with valid calls", "[Sema]")
{
    std::string path = "multiple_statements.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to undefined 'log'
}
