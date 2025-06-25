#include <llvm/Support/ErrorHandling.h>
#include "libtarot/ControlFlow.h"
#include <iostream>

int CFG::insertNewBlock()
{
    basicBlocks.emplace_back();
    return basicBlocks.size() - 1;
}

int CFG::insertNewBlockBefore(int before, bool reachable)
{
    int b = insertNewBlock();
    insertEdge(b, before, reachable);
    return b;
}

void CFG::insertEdge(int from, int to, bool reachable)
{
    basicBlocks[from].successors.emplace(std::make_pair(to, reachable));
    basicBlocks[to].predecessors.emplace(std::make_pair(from, reachable));
}

void CFG::insertStmt(const ResolvedStatement *stmt, int block)
{
    basicBlocks[block].statements.emplace_back(stmt);
}

CFG CFGBuilder::build(const ResolvedFunctionDecl &fn)
{
    cfg = {};
    cfg.exit = cfg.insertNewBlock();
    int body = insertBlock(*fn.body, cfg.exit);

    cfg.entry = cfg.insertNewBlockBefore(body, true);

    return cfg;
}

bool isTerminator(const ResolvedStatement &stmt)
{
    return dynamic_cast<const ResolvedIfStatement *>(&stmt) ||
           dynamic_cast<const ResolvedWhileStatement *>(&stmt) ||
           dynamic_cast<const ResolvedReturnStmt *>(&stmt);
}

int CFGBuilder::insertBlock(const ResolvedBlock &block, int succ)
{
    const auto &stmts = block.statements;

    bool insertNewBlock = true;
    for (auto it = stmts.rbegin(); it != stmts.rend(); it++)
    {

        if (insertNewBlock && !isTerminator(**it))
            succ = cfg.insertNewBlockBefore(succ, true);

        insertNewBlock = dynamic_cast<const ResolvedWhileStatement *>(it->get());
        succ = insertStmt(**it, succ);
    }

    return succ;
}

int CFGBuilder::insertStmt(const ResolvedStatement &stmt, int block)
{
    if (auto *ifStmt = dynamic_cast<const ResolvedIfStatement *>(&stmt))
        return insertIfStatement(*ifStmt, block);

    if (auto *whileStmt = dynamic_cast<const ResolvedWhileStatement *>(&stmt))
        return insertWhileStatement(*whileStmt, block);

    if (auto *expr = dynamic_cast<const ResolvedExpression *>(&stmt))
        return insertExpression(*expr, block);

    if (auto *returnStmt = dynamic_cast<const ResolvedReturnStmt *>(&stmt))
        return insertReturnStatement(*returnStmt, block);

    if (auto *declStmt = dynamic_cast<const ResolvedDeclStatement *>(&stmt))
        return insertDeclStmt(*declStmt, block);

    if (auto *assignment = dynamic_cast<const ResolvedAssignment *>(&stmt))
        return insertAssignment(*assignment, block);

    llvm_unreachable("unexpected Expression");
}

int CFGBuilder::insertReturnStatement(const ResolvedReturnStmt &stmt, int block)
{
    block = cfg.insertNewBlockBefore(cfg.exit, true);
    cfg.insertStmt(&stmt, block);

    if (stmt.expr)
        return insertExpression(*stmt.expr, block);

    return block;
}

int CFGBuilder::insertExpression(const ResolvedExpression &expr, int block)
{
    cfg.insertStmt(&expr, block);

    if (const auto *call = dynamic_cast<const ResolvedCallExpr *>(&expr))
    {
        for (auto it = call->arguments.rbegin(); it != call->arguments.rend(); ++it)
            insertExpression(**it, block);
        return block;
    }

    if (const auto *grouping = dynamic_cast<const ResolvedGroupingExpression *>(&expr))
        return insertExpression(*grouping->expr, block);

    if (const auto *binop = dynamic_cast<const ResolvedBinaryOperator *>(&expr))
        return insertExpression(*binop->rhs, block), insertExpression(*binop->lhs, block);

    if (const auto *unop = dynamic_cast<const ResolvedUnaryOperator *>(&expr))
        return insertExpression(*unop->operand, block);

    return block;
}

int CFGBuilder::insertIfStatement(const ResolvedIfStatement &stmt, int exit)
{
    int falseBlock = exit;
    if (stmt.falseBlock)
        falseBlock = insertBlock(*stmt.falseBlock, exit);

    int trueBlock = insertBlock(*stmt.trueBlock, exit);

    int entry = cfg.insertNewBlock();

    std::optional<double> val = cee.evaluate(*stmt.condition, true);
    cfg.insertEdge(entry, trueBlock, val != 0);
    cfg.insertEdge(entry, falseBlock, val.value_or(0) == 0);

    cfg.insertStmt(&stmt, entry);
    return insertExpression(*stmt.condition, entry);
}

int CFGBuilder::insertWhileStatement(const ResolvedWhileStatement &stmt, int exit)
{
    int latch = cfg.insertNewBlock();
    int body = insertBlock(*stmt.body, latch);

    int header = cfg.insertNewBlock();
    cfg.insertEdge(latch, header, true);
    std::optional<double> val = cee.evaluate(*stmt.condition, true);
    cfg.insertEdge(header, body, val != 0);
    cfg.insertEdge(header, exit, val.value_or(0) == 0);

    cfg.insertStmt(&stmt, header);
    insertExpression(*stmt.condition, header);

    return header;
}

void CFG::dump(size_t level) const
{
    for (int i = basicBlocks.size() - 1; i >= 0; --i)
    {
        std::cerr << '[' << i;
        if (i == entry)
            std::cerr << " (entry)";
        else if (i == exit)
            std::cerr << " (exit)";
        std::cerr << ']' << '\n';

        std::cerr << "  preds: ";
        for (auto &&[id, reachable] : basicBlocks[i].predecessors)
            std::cerr << id << ((reachable) ? " " : "(U) ");
        std::cerr << '\n';

        std::cerr << "  succs: ";
        for (auto &&[id, reachable] : basicBlocks[i].successors)
            std::cerr << id << ((reachable) ? " " : "(U) ");
        std::cerr << '\n';

        const auto &statements = basicBlocks[i].statements;
        for (auto it = statements.rbegin(); it != statements.rend(); ++it)
            (*it)->dump(1);
        std::cerr << '\n';
    }
}

int CFGBuilder::insertDeclStmt(const ResolvedDeclStatement &stmt, int block)
{
    cfg.insertStmt(&stmt, block);

    if (const auto &init = stmt.varDecl->initializer)
        return insertExpression(*init, block);

    return block;
}

int CFGBuilder::insertAssignment(const ResolvedAssignment &stmt, int block)
{
    cfg.insertStmt(&stmt, block);
    return insertExpression(*stmt.expr, block);
}
