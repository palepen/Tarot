#ifndef DECLARATION_H
#define DECLARATION_H
#include <memory>
#include <iostream>

#include "Source.h"
#include "Type.h"
#include "Statement.h"
#include "Utils.h"

struct Block
{
  SourceLocation location;
  std::vector<std::unique_ptr<Statement>> statements;

  Block(SourceLocation location)
      : location(location) {}

  Block(SourceLocation location, std::vector<std::unique_ptr<Statement>> statements)
      : location(location), statements(std::move(statements)) {}

  void dump(size_t level = 0) const;
};

inline void Block::dump(size_t level) const
{
  std::cerr << indent(level) << "Block\n";
  for (auto &&stmt : statements)
  {
    stmt->dump(level + 1);
  }
}

struct Decl
{
  SourceLocation location;
  std::string identifier;

  Decl(SourceLocation location, std::string identifier) : location(location), identifier(std::move(identifier)) {}
  virtual ~Decl() = default;

  virtual void dump(size_t level = 0) const = 0;
};

struct ParameterDecl : public Decl
{
  Type type;
  ParameterDecl(SourceLocation location, std::string identifier, Type type) : Decl(location, std::move(identifier)), type(std::move(type)) {}

  void dump(size_t level = 0) const override
  {
    std::cerr << indent(level) << "ParamDecl: " << identifier << "\n";
  }
};

struct FunctionDecl : public Decl
{
  Type type;
  std::unique_ptr<Block> body;
  std::vector<std::unique_ptr<ParameterDecl>> params;

FunctionDecl(SourceLocation location, std::string identifier, Type type, std::unique_ptr<Block> body, std::unique_ptr<std::vector<std::unique_ptr<ParameterDecl>>> params) : Decl(location, identifier), type(std::move(type)), body(std::move(body)), params(std::move(*params)) {};

  void dump(size_t level) const override
  {
    std::cerr << indent(level) << "FunctionDecl: " << identifier << ":" << type.name << '\n';
    for (auto &&param : params)
    { 
        param->dump(level + 1);
    }

    body->dump(level + 1);
  };
};


#endif