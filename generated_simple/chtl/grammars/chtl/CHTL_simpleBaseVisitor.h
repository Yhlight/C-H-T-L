
// Generated from grammars/chtl/CHTL_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTL_simpleVisitor.h"


/**
 * This class provides an empty implementation of CHTL_simpleVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CHTL_simpleBaseVisitor : public CHTL_simpleVisitor {
public:

  virtual std::any visitProgram(CHTL_simpleParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(CHTL_simpleParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementStatement(CHTL_simpleParser::ElementStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributes(CHTL_simpleParser::AttributesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute(CHTL_simpleParser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementContent(CHTL_simpleParser::ElementContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTextBlock(CHTL_simpleParser::TextBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStyleBlock(CHTL_simpleParser::StyleBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScriptBlock(CHTL_simpleParser::ScriptBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateStatement(CHTL_simpleParser::TemplateStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomStatement(CHTL_simpleParser::CustomStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOriginStatement(CHTL_simpleParser::OriginStatementContext *ctx) override {
    return visitChildren(ctx);
  }


};

