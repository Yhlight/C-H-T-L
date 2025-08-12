
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJS_simpleParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CHTLJS_simpleParser.
 */
class  CHTLJS_simpleListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterChtlScriptBlock(CHTLJS_simpleParser::ChtlScriptBlockContext *ctx) = 0;
  virtual void exitChtlScriptBlock(CHTLJS_simpleParser::ChtlScriptBlockContext *ctx) = 0;

  virtual void enterChtlScriptContent(CHTLJS_simpleParser::ChtlScriptContentContext *ctx) = 0;
  virtual void exitChtlScriptContent(CHTLJS_simpleParser::ChtlScriptContentContext *ctx) = 0;

  virtual void enterChtlStatement(CHTLJS_simpleParser::ChtlStatementContext *ctx) = 0;
  virtual void exitChtlStatement(CHTLJS_simpleParser::ChtlStatementContext *ctx) = 0;

  virtual void enterChtlSelectorStatement(CHTLJS_simpleParser::ChtlSelectorStatementContext *ctx) = 0;
  virtual void exitChtlSelectorStatement(CHTLJS_simpleParser::ChtlSelectorStatementContext *ctx) = 0;

  virtual void enterChtlSelector(CHTLJS_simpleParser::ChtlSelectorContext *ctx) = 0;
  virtual void exitChtlSelector(CHTLJS_simpleParser::ChtlSelectorContext *ctx) = 0;

  virtual void enterSelectorContent(CHTLJS_simpleParser::SelectorContentContext *ctx) = 0;
  virtual void exitSelectorContent(CHTLJS_simpleParser::SelectorContentContext *ctx) = 0;

  virtual void enterChtlListenStatement(CHTLJS_simpleParser::ChtlListenStatementContext *ctx) = 0;
  virtual void exitChtlListenStatement(CHTLJS_simpleParser::ChtlListenStatementContext *ctx) = 0;

  virtual void enterChtlListenObject(CHTLJS_simpleParser::ChtlListenObjectContext *ctx) = 0;
  virtual void exitChtlListenObject(CHTLJS_simpleParser::ChtlListenObjectContext *ctx) = 0;

  virtual void enterChtlListenEvents(CHTLJS_simpleParser::ChtlListenEventsContext *ctx) = 0;
  virtual void exitChtlListenEvents(CHTLJS_simpleParser::ChtlListenEventsContext *ctx) = 0;

  virtual void enterChtlListenEvent(CHTLJS_simpleParser::ChtlListenEventContext *ctx) = 0;
  virtual void exitChtlListenEvent(CHTLJS_simpleParser::ChtlListenEventContext *ctx) = 0;

  virtual void enterEventType(CHTLJS_simpleParser::EventTypeContext *ctx) = 0;
  virtual void exitEventType(CHTLJS_simpleParser::EventTypeContext *ctx) = 0;

  virtual void enterEventHandler(CHTLJS_simpleParser::EventHandlerContext *ctx) = 0;
  virtual void exitEventHandler(CHTLJS_simpleParser::EventHandlerContext *ctx) = 0;

  virtual void enterChtlDelegateStatement(CHTLJS_simpleParser::ChtlDelegateStatementContext *ctx) = 0;
  virtual void exitChtlDelegateStatement(CHTLJS_simpleParser::ChtlDelegateStatementContext *ctx) = 0;

  virtual void enterChtlDelegateObject(CHTLJS_simpleParser::ChtlDelegateObjectContext *ctx) = 0;
  virtual void exitChtlDelegateObject(CHTLJS_simpleParser::ChtlDelegateObjectContext *ctx) = 0;

  virtual void enterChtlDelegateConfig(CHTLJS_simpleParser::ChtlDelegateConfigContext *ctx) = 0;
  virtual void exitChtlDelegateConfig(CHTLJS_simpleParser::ChtlDelegateConfigContext *ctx) = 0;

  virtual void enterChtlTargetConfig(CHTLJS_simpleParser::ChtlTargetConfigContext *ctx) = 0;
  virtual void exitChtlTargetConfig(CHTLJS_simpleParser::ChtlTargetConfigContext *ctx) = 0;

  virtual void enterChtlEventConfig(CHTLJS_simpleParser::ChtlEventConfigContext *ctx) = 0;
  virtual void exitChtlEventConfig(CHTLJS_simpleParser::ChtlEventConfigContext *ctx) = 0;

  virtual void enterChtlAnimateStatement(CHTLJS_simpleParser::ChtlAnimateStatementContext *ctx) = 0;
  virtual void exitChtlAnimateStatement(CHTLJS_simpleParser::ChtlAnimateStatementContext *ctx) = 0;

  virtual void enterChtlAnimateObject(CHTLJS_simpleParser::ChtlAnimateObjectContext *ctx) = 0;
  virtual void exitChtlAnimateObject(CHTLJS_simpleParser::ChtlAnimateObjectContext *ctx) = 0;

  virtual void enterChtlAnimateConfig(CHTLJS_simpleParser::ChtlAnimateConfigContext *ctx) = 0;
  virtual void exitChtlAnimateConfig(CHTLJS_simpleParser::ChtlAnimateConfigContext *ctx) = 0;

  virtual void enterChtlAnimateProperty(CHTLJS_simpleParser::ChtlAnimatePropertyContext *ctx) = 0;
  virtual void exitChtlAnimateProperty(CHTLJS_simpleParser::ChtlAnimatePropertyContext *ctx) = 0;

  virtual void enterChtlDuration(CHTLJS_simpleParser::ChtlDurationContext *ctx) = 0;
  virtual void exitChtlDuration(CHTLJS_simpleParser::ChtlDurationContext *ctx) = 0;

  virtual void enterChtlEasing(CHTLJS_simpleParser::ChtlEasingContext *ctx) = 0;
  virtual void exitChtlEasing(CHTLJS_simpleParser::ChtlEasingContext *ctx) = 0;

  virtual void enterEasingValue(CHTLJS_simpleParser::EasingValueContext *ctx) = 0;
  virtual void exitEasingValue(CHTLJS_simpleParser::EasingValueContext *ctx) = 0;

  virtual void enterChtlBegin(CHTLJS_simpleParser::ChtlBeginContext *ctx) = 0;
  virtual void exitChtlBegin(CHTLJS_simpleParser::ChtlBeginContext *ctx) = 0;

  virtual void enterChtlEnd(CHTLJS_simpleParser::ChtlEndContext *ctx) = 0;
  virtual void exitChtlEnd(CHTLJS_simpleParser::ChtlEndContext *ctx) = 0;

  virtual void enterChtlCssProperties(CHTLJS_simpleParser::ChtlCssPropertiesContext *ctx) = 0;
  virtual void exitChtlCssProperties(CHTLJS_simpleParser::ChtlCssPropertiesContext *ctx) = 0;

  virtual void enterChtlCssProperty(CHTLJS_simpleParser::ChtlCssPropertyContext *ctx) = 0;
  virtual void exitChtlCssProperty(CHTLJS_simpleParser::ChtlCssPropertyContext *ctx) = 0;

  virtual void enterPropertyName(CHTLJS_simpleParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(CHTLJS_simpleParser::PropertyNameContext *ctx) = 0;

  virtual void enterPropertyValue(CHTLJS_simpleParser::PropertyValueContext *ctx) = 0;
  virtual void exitPropertyValue(CHTLJS_simpleParser::PropertyValueContext *ctx) = 0;

  virtual void enterMethodCall(CHTLJS_simpleParser::MethodCallContext *ctx) = 0;
  virtual void exitMethodCall(CHTLJS_simpleParser::MethodCallContext *ctx) = 0;

  virtual void enterArguments(CHTLJS_simpleParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(CHTLJS_simpleParser::ArgumentsContext *ctx) = 0;

  virtual void enterArgumentList(CHTLJS_simpleParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(CHTLJS_simpleParser::ArgumentListContext *ctx) = 0;

  virtual void enterBasicStatement(CHTLJS_simpleParser::BasicStatementContext *ctx) = 0;
  virtual void exitBasicStatement(CHTLJS_simpleParser::BasicStatementContext *ctx) = 0;


};

