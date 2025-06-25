#ifndef DECLARATION_H
#define DECLARATION_H
#include <memory>
#include <iostream>
#include <optional>

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

struct VarDecl : public Decl
{
  std::optional<Type> type;
  std::unique_ptr<Expression> initializer;
  bool isMutable;

  VarDecl(SourceLocation location, std::string identifier, std::optional<Type> type, bool isMutable, std::unique_ptr<Expression> initializer = nullptr) : Decl(location, std::move(identifier)), type(std::move(type)), initializer(std::move(initializer)), isMutable(isMutable) {}

  void dump(size_t level = 0) const override;
};

struct DeclStatement : public Statement
{
    std::unique_ptr<VarDecl> varDecl;

    DeclStatement(SourceLocation location, std::unique_ptr<VarDecl> varDecl)
        : Statement(location),
          varDecl(std::move(varDecl)) {}

    void dump(size_t level = 0) const override;
};

struct Assignment : public Statement
{
    std::unique_ptr<DeclRefExpression> variable;
    std::unique_ptr<Expression> expr;

    Assignment(SourceLocation location, std::unique_ptr<DeclRefExpression> variable, std::unique_ptr<Expression> expr)
        : Statement(location),
          variable(std::move(variable)),
          expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};


#endif