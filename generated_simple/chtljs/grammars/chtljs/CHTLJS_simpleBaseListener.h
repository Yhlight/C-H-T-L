
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJS_simpleListener.h"


/**
 * This class provides an empty implementation of CHTLJS_simpleListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CHTLJS_simpleBaseListener : public CHTLJS_simpleListener {
public:

  virtual void enterChtlScriptBlock(CHTLJS_simpleParser::ChtlScriptBlockContext * /*ctx*/) override { }
  virtual void exitChtlScriptBlock(CHTLJS_simpleParser::ChtlScriptBlockContext * /*ctx*/) override { }

  virtual void enterChtlScriptContent(CHTLJS_simpleParser::ChtlScriptContentContext * /*ctx*/) override { }
  virtual void exitChtlScriptContent(CHTLJS_simpleParser::ChtlScriptContentContext * /*ctx*/) override { }

  virtual void enterChtlStatement(CHTLJS_simpleParser::ChtlStatementContext * /*ctx*/) override { }
  virtual void exitChtlStatement(CHTLJS_simpleParser::ChtlStatementContext * /*ctx*/) override { }

  virtual void enterChtlSelectorStatement(CHTLJS_simpleParser::ChtlSelectorStatementContext * /*ctx*/) override { }
  virtual void exitChtlSelectorStatement(CHTLJS_simpleParser::ChtlSelectorStatementContext * /*ctx*/) override { }

  virtual void enterChtlSelector(CHTLJS_simpleParser::ChtlSelectorContext * /*ctx*/) override { }
  virtual void exitChtlSelector(CHTLJS_simpleParser::ChtlSelectorContext * /*ctx*/) override { }

  virtual void enterSelectorContent(CHTLJS_simpleParser::SelectorContentContext * /*ctx*/) override { }
  virtual void exitSelectorContent(CHTLJS_simpleParser::SelectorContentContext * /*ctx*/) override { }

  virtual void enterChtlListenStatement(CHTLJS_simpleParser::ChtlListenStatementContext * /*ctx*/) override { }
  virtual void exitChtlListenStatement(CHTLJS_simpleParser::ChtlListenStatementContext * /*ctx*/) override { }

  virtual void enterChtlListenObject(CHTLJS_simpleParser::ChtlListenObjectContext * /*ctx*/) override { }
  virtual void exitChtlListenObject(CHTLJS_simpleParser::ChtlListenObjectContext * /*ctx*/) override { }

  virtual void enterChtlListenEvents(CHTLJS_simpleParser::ChtlListenEventsContext * /*ctx*/) override { }
  virtual void exitChtlListenEvents(CHTLJS_simpleParser::ChtlListenEventsContext * /*ctx*/) override { }

  virtual void enterChtlListenEvent(CHTLJS_simpleParser::ChtlListenEventContext * /*ctx*/) override { }
  virtual void exitChtlListenEvent(CHTLJS_simpleParser::ChtlListenEventContext * /*ctx*/) override { }

  virtual void enterEventType(CHTLJS_simpleParser::EventTypeContext * /*ctx*/) override { }
  virtual void exitEventType(CHTLJS_simpleParser::EventTypeContext * /*ctx*/) override { }

  virtual void enterEventHandler(CHTLJS_simpleParser::EventHandlerContext * /*ctx*/) override { }
  virtual void exitEventHandler(CHTLJS_simpleParser::EventHandlerContext * /*ctx*/) override { }

  virtual void enterChtlDelegateStatement(CHTLJS_simpleParser::ChtlDelegateStatementContext * /*ctx*/) override { }
  virtual void exitChtlDelegateStatement(CHTLJS_simpleParser::ChtlDelegateStatementContext * /*ctx*/) override { }

  virtual void enterChtlDelegateObject(CHTLJS_simpleParser::ChtlDelegateObjectContext * /*ctx*/) override { }
  virtual void exitChtlDelegateObject(CHTLJS_simpleParser::ChtlDelegateObjectContext * /*ctx*/) override { }

  virtual void enterChtlDelegateConfig(CHTLJS_simpleParser::ChtlDelegateConfigContext * /*ctx*/) override { }
  virtual void exitChtlDelegateConfig(CHTLJS_simpleParser::ChtlDelegateConfigContext * /*ctx*/) override { }

  virtual void enterChtlTargetConfig(CHTLJS_simpleParser::ChtlTargetConfigContext * /*ctx*/) override { }
  virtual void exitChtlTargetConfig(CHTLJS_simpleParser::ChtlTargetConfigContext * /*ctx*/) override { }

  virtual void enterChtlEventConfig(CHTLJS_simpleParser::ChtlEventConfigContext * /*ctx*/) override { }
  virtual void exitChtlEventConfig(CHTLJS_simpleParser::ChtlEventConfigContext * /*ctx*/) override { }

  virtual void enterChtlAnimateStatement(CHTLJS_simpleParser::ChtlAnimateStatementContext * /*ctx*/) override { }
  virtual void exitChtlAnimateStatement(CHTLJS_simpleParser::ChtlAnimateStatementContext * /*ctx*/) override { }

  virtual void enterChtlAnimateObject(CHTLJS_simpleParser::ChtlAnimateObjectContext * /*ctx*/) override { }
  virtual void exitChtlAnimateObject(CHTLJS_simpleParser::ChtlAnimateObjectContext * /*ctx*/) override { }

  virtual void enterChtlAnimateConfig(CHTLJS_simpleParser::ChtlAnimateConfigContext * /*ctx*/) override { }
  virtual void exitChtlAnimateConfig(CHTLJS_simpleParser::ChtlAnimateConfigContext * /*ctx*/) override { }

  virtual void enterChtlAnimateProperty(CHTLJS_simpleParser::ChtlAnimatePropertyContext * /*ctx*/) override { }
  virtual void exitChtlAnimateProperty(CHTLJS_simpleParser::ChtlAnimatePropertyContext * /*ctx*/) override { }

  virtual void enterChtlDuration(CHTLJS_simpleParser::ChtlDurationContext * /*ctx*/) override { }
  virtual void exitChtlDuration(CHTLJS_simpleParser::ChtlDurationContext * /*ctx*/) override { }

  virtual void enterChtlEasing(CHTLJS_simpleParser::ChtlEasingContext * /*ctx*/) override { }
  virtual void exitChtlEasing(CHTLJS_simpleParser::ChtlEasingContext * /*ctx*/) override { }

  virtual void enterEasingValue(CHTLJS_simpleParser::EasingValueContext * /*ctx*/) override { }
  virtual void exitEasingValue(CHTLJS_simpleParser::EasingValueContext * /*ctx*/) override { }

  virtual void enterChtlBegin(CHTLJS_simpleParser::ChtlBeginContext * /*ctx*/) override { }
  virtual void exitChtlBegin(CHTLJS_simpleParser::ChtlBeginContext * /*ctx*/) override { }

  virtual void enterChtlEnd(CHTLJS_simpleParser::ChtlEndContext * /*ctx*/) override { }
  virtual void exitChtlEnd(CHTLJS_simpleParser::ChtlEndContext * /*ctx*/) override { }

  virtual void enterChtlCssProperties(CHTLJS_simpleParser::ChtlCssPropertiesContext * /*ctx*/) override { }
  virtual void exitChtlCssProperties(CHTLJS_simpleParser::ChtlCssPropertiesContext * /*ctx*/) override { }

  virtual void enterChtlCssProperty(CHTLJS_simpleParser::ChtlCssPropertyContext * /*ctx*/) override { }
  virtual void exitChtlCssProperty(CHTLJS_simpleParser::ChtlCssPropertyContext * /*ctx*/) override { }

  virtual void enterPropertyName(CHTLJS_simpleParser::PropertyNameContext * /*ctx*/) override { }
  virtual void exitPropertyName(CHTLJS_simpleParser::PropertyNameContext * /*ctx*/) override { }

  virtual void enterPropertyValue(CHTLJS_simpleParser::PropertyValueContext * /*ctx*/) override { }
  virtual void exitPropertyValue(CHTLJS_simpleParser::PropertyValueContext * /*ctx*/) override { }

  virtual void enterMethodCall(CHTLJS_simpleParser::MethodCallContext * /*ctx*/) override { }
  virtual void exitMethodCall(CHTLJS_simpleParser::MethodCallContext * /*ctx*/) override { }

  virtual void enterArguments(CHTLJS_simpleParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(CHTLJS_simpleParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterArgumentList(CHTLJS_simpleParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(CHTLJS_simpleParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterBasicStatement(CHTLJS_simpleParser::BasicStatementContext * /*ctx*/) override { }
  virtual void exitBasicStatement(CHTLJS_simpleParser::BasicStatementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

