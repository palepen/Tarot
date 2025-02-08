#include "libtrt/Resolved.h"

void ResolvedNumberLiteral::dump(size_t level) const {
  std::cerr << indent(level) << "ResolvedNumberLiteral: '" << value << "'\n";
}


void ResolvedDeclarationRefExpr::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedDeclRefExpr: @(" << decl->identifier << "\n";
}

void ResolvedCallExpr::dump(size_t level) const 
{
    std::cerr << indent(level) << "ResolvedCallExpr: @(" << &callee << ")" << callee->identifier << "\n";
    for(auto &&arg : arguments){
        arg->dump(level + 1);
    } 
}


void ResolvedBlock::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedBlock\n";

    for(auto &&stmt : statements) 
    {
        if(stmt)
            stmt->dump(level + 1);
    }
}


void ResolvedParamDecl::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedParamDecl: @(" << this << ")" << identifier << ":" << "\n";
};


void ResolvedFunctionDecl::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedFunctionDecl: @(" << this << ")" << identifier << ":" << "\n";

    for (auto &&params : params){
        params->dump(level + 1);
    }

    if(body)
        body->dump(level + 1);
}


void ResolvedReturnStmt::dump(size_t level) const {
  std::cerr << indent(level) << "ResolvedReturnStmt\n";

  if (expr)
    expr->dump(level + 1);
}
