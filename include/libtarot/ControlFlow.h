#ifndef CONTROLFLOW_H
#define CONTROLFLOW_H

#include <set>
#include <vector>

#include "Resolved.h"
#include "Evaluate.h"

struct BasicBlock
{
    std::set<std::pair<int, bool>> predecessors;
    std::set<std::pair<int, bool>> successors;
    std::vector<const ResolvedStatement *> statements;
};

// cfg is the list of basic block

struct CFG
{
    std::vector<BasicBlock> basicBlocks;
    int entry = -1;
    int exit = -1;

    int insertNewBlock();
    int insertNewBlockBefore(int before, bool reachable);
    void insertEdge(int from, int to, bool reachable);
    void insertStmt(const ResolvedStatement *stmt, int block);
    void dump(size_t level = 0) const;
};

class CFGBuilder
{
    ConstantExpressionEvaluator cee;
    CFG cfg;

public:
    CFG build(const ResolvedFunctionDecl &fn);
    int insertBlock(const ResolvedBlock &block, int succ);
    int insertStmt(const ResolvedStatement &stmt, int block);
    int insertIfStatement(const ResolvedIfStatement &stmt, int block);
    int insertWhileStatement(const ResolvedWhileStatement &stmt, int block);
    int insertExpresssion(const ResolvedExpression &stmt, int block);
    int insertReturnStatement(const ResolvedReturnStmt &stmt, int block);
};

#endif