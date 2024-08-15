#ifndef DECLARATION_H
#define DECLARATION_H
#include <memory>
#include <iostream>

#include "Source.h"
#include "Type.h"

struct Block
{
  SourceLocation location;

  Block(SourceLocation location)
      : location(location) {}

  void dump(size_t level = 0) const;
};

inline std::string indent(size_t level) { return std::string(level * 2, ' '); }

inline void Block::dump(size_t level) const
{
  std::cerr << indent(level) << "Block\n";
}

struct Decl
{
  SourceLocation location;
  std::string identifier;

  Decl(SourceLocation location, std::string identifier) : location(location), identifier(std::move(identifier)) {}
  virtual ~Decl() = default;

  virtual void dump(size_t level = 0) const = 0;
};

struct FunctionalDecl : public Decl
{
  Type type;
  std::unique_ptr<Block> body;

  FunctionalDecl(SourceLocation location, std::string identifier, Type type, std::unique_ptr<Block> body) : Decl(location, identifier), type(std::move(type)), body(std::move(body)) {};

  void dump(size_t level) const override
  {
    std::cerr << indent(level) << "FunctionDecl: " << identifier << ":" << type.name << '\n';
  };
};

#endif