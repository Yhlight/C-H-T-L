
// Generated from grammars/css/CSS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CSS_simpleVisitor.h"


/**
 * This class provides an empty implementation of CSS_simpleVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CSS_simpleBaseVisitor : public CSS_simpleVisitor {
public:

  virtual std::any visitStylesheet(CSS_simpleParser::StylesheetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRule(CSS_simpleParser::RuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelector(CSS_simpleParser::SelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarationList(CSS_simpleParser::DeclarationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(CSS_simpleParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty(CSS_simpleParser::PropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue(CSS_simpleParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }


};

