#ifndef DECLARATION_H
#define DECLARATION_H
#include <memory>
#include <iostream>

#include "Source.h"
#include "Type.h"
#include "Statement.h"
#include "Utils.h"

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

  void dump(size_t level = 0) const override;
};

struct FunctionDecl : public Decl
{
  Type type;
  std::unique_ptr<Block> body;
  std::vector<std::unique_ptr<ParameterDecl>> params;

FunctionDecl(SourceLocation location, std::string identifier, Type type, std::unique_ptr<Block> body, std::unique_ptr<std::vector<std::unique_ptr<ParameterDecl>>> params) : Decl(location, identifier), type(std::move(type)), body(std::move(body)), params(std::move(*params)) {};

  void dump(size_t level = 0) const override;
};


#endif