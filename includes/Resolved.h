#ifndef RESOLVED_H
#define RESOLVED_H
#include "Source.h"
#include "Type.h"

struct ResolvedStatement
{
    SourceLocation source;
    ResolvedStatement(SourceLocation source) : source(source) {}

    virtual ~ResolvedStatement() = default;

    virtual void dump(size_t dump = 0) const = 0;

};

struct ResolvedExpression : public ResolvedStatement 
{
    Type type;

    ResolvedExpression(SourceLocation source, Type type) 
    : ResolvedStatement(source), type(type) {}
};

struct ResolvedDecl
{
    SourceLocation source;
    std::string  identifier;
    Type type;

    ResolvedDecl(SourceLocation source, std::string identifier, Type type): source(source), identifier(identifier), type(type) {}

    virtual ~ResolvedDecl() = default;

    virtual void dump(size_t level = 0) const = 0;
};


#endif