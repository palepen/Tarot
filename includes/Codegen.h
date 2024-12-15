#ifndef CODEGEN_H
#define CODEGEN_H
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Host.h"
#include "Resolved.h"

class Codegen{
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree;
    
    public:
        Codegen(std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree, std::string_view sourcePath);
        llvm::Module *generateIR();
};

#endif