#ifndef CODEGEN_H
#define CODEGEN_H
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Host.h"
#include "Resolved.h"

class Codegen
{
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
    llvm::Instruction *allocaInsertPoint;
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree;
    llvm::Value *retVal = nullptr;
    llvm::BasicBlock *retBB = nullptr;
    
public:
    Codegen(std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree, std::string_view sourcePath);
    llvm::Module *generateIR();
    llvm::Type *generateType(Type type);
    llvm::AllocaInst *allocateStackVariable(llvm::Function *function, const std::string_view identifier);
    llvm::Value generateStatement(const ResolvedStatement  &stmt);
    void generateFunctionDecl(const ResolvedFunctionDecl &functionDecl);
    void generateFunctionBody(const ResolvedFunctionDecl &functionDecl);
    void generateBlock(const ResolvedBlock &block);

};

#endif