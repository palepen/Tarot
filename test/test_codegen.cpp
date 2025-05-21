#include <catch2/catch_test_macros.hpp>
#include <string>
#include <memory>
#include <llvm/IR/Verifier.h>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Sema.h"
#include "libtarot/Codegen.h"
#include "libtarot/Source.h"
#include "test_helper.h"

TEST_CASE("Codegen: Valid main function", "[Codegen]") {
    std::string path = "main_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
    REQUIRE(main->arg_size() == 0);

    auto *builtinMain = module->getFunction("__builtin_main");
    REQUIRE(builtinMain != nullptr);
    REQUIRE(builtinMain->getReturnType()->isVoidTy());
    REQUIRE(builtinMain->arg_size() == 0);
}

TEST_CASE("Codegen: Valid function call with definition", "[Codegen]") {
    std::string path = "valid_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, add, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    if (llvm::verifyModule(*module, &llvm::errs())) {
        module->print(llvm::errs(), nullptr);
        REQUIRE(false);
    }

    auto *add = module->getFunction("add");
    REQUIRE(add != nullptr);
    REQUIRE(add->getReturnType()->isDoubleTy());
    REQUIRE(add->arg_size() == 2);

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
    REQUIRE(main->arg_size() == 0);
}


TEST_CASE("Codegen: Valid number return statement", "[Codegen]") {
    std::string path = "return_literal.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);
    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, getFive, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *getFive = module->getFunction("getFive");
    REQUIRE(getFive != nullptr);
    REQUIRE(getFive->getReturnType()->isDoubleTy());
    REQUIRE(getFive->arg_size() == 0);
}

TEST_CASE("Codegen: Valid empty return in void function", "[Codegen]") {
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

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *noValue = module->getFunction("noValue");
    REQUIRE(noValue != nullptr);
    REQUIRE(noValue->getReturnType()->isVoidTy());
    REQUIRE(noValue->arg_size() == 0);
}

TEST_CASE("Codegen: Valid println call", "[Codegen]") {
    std::string path = "println_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *println = module->getFunction("println");
    REQUIRE(println != nullptr);
    REQUIRE(println->getReturnType()->isVoidTy());
    REQUIRE(println->arg_size() == 1);
    REQUIRE(println->getArg(0)->getType()->isDoubleTy());

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
}

TEST_CASE("Codegen: Multiple functions with call", "[Codegen]") {
    std::string path = "multiple_functions.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, helper, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *helper = module->getFunction("helper");
    REQUIRE(helper != nullptr);
    REQUIRE(helper->getReturnType()->isDoubleTy());
    REQUIRE(helper->arg_size() == 0);

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
}

TEST_CASE("Codegen: Unreachable code after return", "[Codegen]") {
    std::string path = "unreachable.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, foo

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *foo = module->getFunction("foo");
    REQUIRE(foo != nullptr);
    REQUIRE(foo->getReturnType()->isDoubleTy());
    REQUIRE(foo->arg_size() == 0);
}

TEST_CASE("Codegen: Multiple statements with valid calls", "[Codegen]") {
    std::string path = "valid_multiple_statements.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 4); // println, log, complex, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *complex = module->getFunction("complex");
    REQUIRE(complex != nullptr);
    REQUIRE(complex->getReturnType()->isDoubleTy());
    REQUIRE(complex->arg_size() == 0);
}