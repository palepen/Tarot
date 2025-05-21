#include <catch2/catch_test_macros.hpp>
#include "include/test_helper.h"

TEST_CASE("Lexer: Single-character tokens", "[Lexer]")
{
    std::string source = "(){}:;,";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 8); // 7 tokens + EOF
    REQUIRE(tokens[0].type == TokenType::LPAREN);
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::RPAREN);
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 2);
    REQUIRE(tokens[2].type == TokenType::LBRACE);
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 3);
    REQUIRE(tokens[3].type == TokenType::RBRACE);
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 4);
    REQUIRE(tokens[4].type == TokenType::COLON);
    REQUIRE(tokens[4].source.line == 1);
    REQUIRE(tokens[4].source.col == 5);
    REQUIRE(tokens[5].type == TokenType::SEMICOLON);
    REQUIRE(tokens[5].source.line == 1);
    REQUIRE(tokens[5].source.col == 6);
    REQUIRE(tokens[6].type == TokenType::COMMA);
    REQUIRE(tokens[6].source.line == 1);
    REQUIRE(tokens[6].source.col == 7);
    REQUIRE(tokens[7].type == TokenType::EOFTOK);
    REQUIRE(tokens[7].source.line == 1);
    REQUIRE(tokens[7].source.col == 8);
}

TEST_CASE("Lexer: Keywords", "[Lexer]")
{
    std::string source = "fn void return number";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // 4 keywords + EOF
    REQUIRE(tokens[0].type == TokenType::FN);
    REQUIRE(tokens[0].value == "fn");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::VOID);
    REQUIRE(tokens[1].value == "void");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 4);
    REQUIRE(tokens[2].type == TokenType::RETURN);
    REQUIRE(tokens[2].value == "return");
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 9);
    REQUIRE(tokens[3].type == TokenType::NUMBER);
    REQUIRE(tokens[3].value == "number");
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 16);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Identifiers", "[Lexer]")
{
    std::string source = "main myFunc x123 _var";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // 4 identifiers + EOF
    REQUIRE(tokens[0].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[0].value == "main");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[1].value == "myFunc");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 6);
    REQUIRE(tokens[2].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[2].value == "x123");
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 13);
    REQUIRE(tokens[3].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[3].value == "_var");
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 18);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Numbers (integers and floats)", "[Lexer]")
{
    std::string source = "42 3.14 0.0 123.456";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // 4 numbers + EOF
    REQUIRE(tokens[0].type == TokenType::NUMBER);
    REQUIRE(tokens[0].value == "42");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::NUMBER);
    REQUIRE(tokens[1].value == "3.14");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 4);
    REQUIRE(tokens[2].type == TokenType::NUMBER);
    REQUIRE(tokens[2].value == "0.0");
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 9);
    REQUIRE(tokens[3].type == TokenType::NUMBER);
    REQUIRE(tokens[3].value == "123.456");
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 13);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Invalid number (dot without digits)", "[Lexer]")
{
    std::string source = "42.";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 2); // 1 unknown + EOF
    REQUIRE(tokens[0].type == TokenType::UNK);
    REQUIRE(tokens[0].value == "42.");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Comments", "[Lexer]") {
    std::string source = "fn main // This is a comment\nreturn;";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // fn, main, return, semicolon, EOF
    REQUIRE(tokens[0].type == TokenType::FN);
    REQUIRE(tokens[0].value == "fn");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[1].value == "main");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 4);
    REQUIRE(tokens[2].type == TokenType::RETURN);
    REQUIRE(tokens[2].value == "return");
    REQUIRE(tokens[2].source.line == 2);
    REQUIRE(tokens[2].source.col == 1);
    REQUIRE(tokens[3].type == TokenType::SEMICOLON);
    REQUIRE(tokens[3].source.line == 2);
    REQUIRE(tokens[3].source.col == 7);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Whitespace and newlines", "[Lexer]")
{
    std::string source = "fn\n\t main \r\n  return";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 4); // fn, main, return, EOF
    REQUIRE(tokens[0].type == TokenType::FN);
    REQUIRE(tokens[0].value == "fn");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[1].value == "main");
    REQUIRE(tokens[1].source.line == 2);
    REQUIRE(tokens[1].source.col == 3);
    REQUIRE(tokens[2].type == TokenType::RETURN);
    REQUIRE(tokens[2].value == "return");
    REQUIRE(tokens[2].source.line == 3);
    REQUIRE(tokens[2].source.col == 3);
    REQUIRE(tokens[3].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Unknown tokens", "[Lexer]")
{
    std::string source = "@#$";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 4); // 3 unknown + EOF
    REQUIRE(tokens[0].type == TokenType::UNK);
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::UNK);
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 2);
    REQUIRE(tokens[2].type == TokenType::UNK);
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 3);
    REQUIRE(tokens[3].type == TokenType::EOFTOK);
}