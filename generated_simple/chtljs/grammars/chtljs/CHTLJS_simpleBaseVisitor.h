
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJS_simpleVisitor.h"


/**
 * This class provides an empty implementation of CHTLJS_simpleVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CHTLJS_simpleBaseVisitor : public CHTLJS_simpleVisitor {
public:

  virtual std::any visitChtlScriptBlock(CHTLJS_simpleParser::ChtlScriptBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlScriptContent(CHTLJS_simpleParser::ChtlScriptContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlStatement(CHTLJS_simpleParser::ChtlStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlSelectorStatement(CHTLJS_simpleParser::ChtlSelectorStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlSelector(CHTLJS_simpleParser::ChtlSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectorContent(CHTLJS_simpleParser::SelectorContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlListenStatement(CHTLJS_simpleParser::ChtlListenStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlListenObject(CHTLJS_simpleParser::ChtlListenObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlListenEvents(CHTLJS_simpleParser::ChtlListenEventsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlListenEvent(CHTLJS_simpleParser::ChtlListenEventContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEventType(CHTLJS_simpleParser::EventTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEventHandler(CHTLJS_simpleParser::EventHandlerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlDelegateStatement(CHTLJS_simpleParser::ChtlDelegateStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlDelegateObject(CHTLJS_simpleParser::ChtlDelegateObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlDelegateConfig(CHTLJS_simpleParser::ChtlDelegateConfigContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlTargetConfig(CHTLJS_simpleParser::ChtlTargetConfigContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlEventConfig(CHTLJS_simpleParser::ChtlEventConfigContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlAnimateStatement(CHTLJS_simpleParser::ChtlAnimateStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlAnimateObject(CHTLJS_simpleParser::ChtlAnimateObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlAnimateConfig(CHTLJS_simpleParser::ChtlAnimateConfigContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlAnimateProperty(CHTLJS_simpleParser::ChtlAnimatePropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlDuration(CHTLJS_simpleParser::ChtlDurationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlEasing(CHTLJS_simpleParser::ChtlEasingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEasingValue(CHTLJS_simpleParser::EasingValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlBegin(CHTLJS_simpleParser::ChtlBeginContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlEnd(CHTLJS_simpleParser::ChtlEndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlCssProperties(CHTLJS_simpleParser::ChtlCssPropertiesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlCssProperty(CHTLJS_simpleParser::ChtlCssPropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyName(CHTLJS_simpleParser::PropertyNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyValue(CHTLJS_simpleParser::PropertyValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodCall(CHTLJS_simpleParser::MethodCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(CHTLJS_simpleParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(CHTLJS_simpleParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicStatement(CHTLJS_simpleParser::BasicStatementContext *ctx) override {
    return visitChildren(ctx);
  }


};

