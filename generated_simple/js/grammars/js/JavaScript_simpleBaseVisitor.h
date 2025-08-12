
// Generated from grammars/js/JavaScript_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "JavaScript_simpleVisitor.h"


/**
 * This class provides an empty implementation of JavaScript_simpleVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  JavaScript_simpleBaseVisitor : public JavaScript_simpleVisitor {
public:

  virtual std::any visitProgram(JavaScript_simpleParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(JavaScript_simpleParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(JavaScript_simpleParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(JavaScript_simpleParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentExpression(JavaScript_simpleParser::AssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(JavaScript_simpleParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(JavaScript_simpleParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(JavaScript_simpleParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(JavaScript_simpleParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(JavaScript_simpleParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDeclaration(JavaScript_simpleParser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(JavaScript_simpleParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(JavaScript_simpleParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(JavaScript_simpleParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForInitializer(JavaScript_simpleParser::ForInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(JavaScript_simpleParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(JavaScript_simpleParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(JavaScript_simpleParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }


};

