#ifndef CODEGEN_H
#define CODEGEN_H
#include <map>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
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
    std::map<const ResolvedDecl *, llvm::Value *> declarations;

public:
    Codegen(std::vector<std::unique_ptr<ResolvedFunctionDecl>> &resolvedTree, std::string_view sourcePath);
    llvm::Module *generateIR();
    llvm::Type *generateType(Type type);
    llvm::AllocaInst *allocateStackVariable(llvm::Function *function, const std::string_view identifier);
    llvm::Value *generateStatement(const ResolvedStatement &stmt);
    llvm::Value *generateReturnStatement(const ResolvedReturnStmt &stmt);
    llvm::Value *generateExpression(const ResolvedExpression &expr);
    llvm::Value *generateCallExpr(const ResolvedCallExpr &call);
    llvm::Value *generateUnaryOperator(const ResolvedUnaryOperator &unary);
    llvm::Value *generateBinaryOperator(const ResolvedBinaryOperator &binOp);
    llvm::Value *doubleToBool(llvm::Value *v);
    llvm::Value *boolToDouble(llvm::Value *v);
    llvm::Function *getCurrentFunction();
    llvm::Value *generateIfStatement(const ResolvedIfStatement &stmt);
    
    void generateBuiltinPrintBody(const ResolvedFunctionDecl &println);
    void generateFunctionDecl(const ResolvedFunctionDecl &functionDecl);
    void generateFunctionBody(const ResolvedFunctionDecl &functionDecl);
    void generateBlock(const ResolvedBlock &block);
    void generateMainWrapper();
    void generateConditionalOperator(const ResolvedExpression &op, llvm::BasicBlock *trueBB, llvm::BasicBlock *falseBB);
};

#endif