
// Generated from grammars/chtl/CHTL.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "CHTLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CHTLParser.
 */
class  CHTLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(CHTLParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(CHTLParser::ProgramContext *ctx) = 0;

  virtual void enterImportStatement(CHTLParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(CHTLParser::ImportStatementContext *ctx) = 0;

  virtual void enterNamespaceStatement(CHTLParser::NamespaceStatementContext *ctx) = 0;
  virtual void exitNamespaceStatement(CHTLParser::NamespaceStatementContext *ctx) = 0;

  virtual void enterConfigurationStatement(CHTLParser::ConfigurationStatementContext *ctx) = 0;
  virtual void exitConfigurationStatement(CHTLParser::ConfigurationStatementContext *ctx) = 0;

  virtual void enterConfigurationContent(CHTLParser::ConfigurationContentContext *ctx) = 0;
  virtual void exitConfigurationContent(CHTLParser::ConfigurationContentContext *ctx) = 0;

  virtual void enterKeyValuePair(CHTLParser::KeyValuePairContext *ctx) = 0;
  virtual void exitKeyValuePair(CHTLParser::KeyValuePairContext *ctx) = 0;

  virtual void enterTemplateStatement(CHTLParser::TemplateStatementContext *ctx) = 0;
  virtual void exitTemplateStatement(CHTLParser::TemplateStatementContext *ctx) = 0;

  virtual void enterTemplateContent(CHTLParser::TemplateContentContext *ctx) = 0;
  virtual void exitTemplateContent(CHTLParser::TemplateContentContext *ctx) = 0;

  virtual void enterCustomStatement(CHTLParser::CustomStatementContext *ctx) = 0;
  virtual void exitCustomStatement(CHTLParser::CustomStatementContext *ctx) = 0;

  virtual void enterCustomContent(CHTLParser::CustomContentContext *ctx) = 0;
  virtual void exitCustomContent(CHTLParser::CustomContentContext *ctx) = 0;

  virtual void enterOriginStatement(CHTLParser::OriginStatementContext *ctx) = 0;
  virtual void exitOriginStatement(CHTLParser::OriginStatementContext *ctx) = 0;

  virtual void enterOriginType(CHTLParser::OriginTypeContext *ctx) = 0;
  virtual void exitOriginType(CHTLParser::OriginTypeContext *ctx) = 0;

  virtual void enterOriginContent(CHTLParser::OriginContentContext *ctx) = 0;
  virtual void exitOriginContent(CHTLParser::OriginContentContext *ctx) = 0;

  virtual void enterRawContent(CHTLParser::RawContentContext *ctx) = 0;
  virtual void exitRawContent(CHTLParser::RawContentContext *ctx) = 0;

  virtual void enterElementStatement(CHTLParser::ElementStatementContext *ctx) = 0;
  virtual void exitElementStatement(CHTLParser::ElementStatementContext *ctx) = 0;

  virtual void enterElementName(CHTLParser::ElementNameContext *ctx) = 0;
  virtual void exitElementName(CHTLParser::ElementNameContext *ctx) = 0;

  virtual void enterAttributes(CHTLParser::AttributesContext *ctx) = 0;
  virtual void exitAttributes(CHTLParser::AttributesContext *ctx) = 0;

  virtual void enterAttributeList(CHTLParser::AttributeListContext *ctx) = 0;
  virtual void exitAttributeList(CHTLParser::AttributeListContext *ctx) = 0;

  virtual void enterAttribute(CHTLParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(CHTLParser::AttributeContext *ctx) = 0;

  virtual void enterElementContent(CHTLParser::ElementContentContext *ctx) = 0;
  virtual void exitElementContent(CHTLParser::ElementContentContext *ctx) = 0;

  virtual void enterTextBlock(CHTLParser::TextBlockContext *ctx) = 0;
  virtual void exitTextBlock(CHTLParser::TextBlockContext *ctx) = 0;

  virtual void enterTextContent(CHTLParser::TextContentContext *ctx) = 0;
  virtual void exitTextContent(CHTLParser::TextContentContext *ctx) = 0;

  virtual void enterStyleBlock(CHTLParser::StyleBlockContext *ctx) = 0;
  virtual void exitStyleBlock(CHTLParser::StyleBlockContext *ctx) = 0;

  virtual void enterStyleContent(CHTLParser::StyleContentContext *ctx) = 0;
  virtual void exitStyleContent(CHTLParser::StyleContentContext *ctx) = 0;

  virtual void enterScriptBlock(CHTLParser::ScriptBlockContext *ctx) = 0;
  virtual void exitScriptBlock(CHTLParser::ScriptBlockContext *ctx) = 0;

  virtual void enterScriptContent(CHTLParser::ScriptContentContext *ctx) = 0;
  virtual void exitScriptContent(CHTLParser::ScriptContentContext *ctx) = 0;

  virtual void enterCssRule(CHTLParser::CssRuleContext *ctx) = 0;
  virtual void exitCssRule(CHTLParser::CssRuleContext *ctx) = 0;

  virtual void enterSelector(CHTLParser::SelectorContext *ctx) = 0;
  virtual void exitSelector(CHTLParser::SelectorContext *ctx) = 0;

  virtual void enterSelectorWithContext(CHTLParser::SelectorWithContextContext *ctx) = 0;
  virtual void exitSelectorWithContext(CHTLParser::SelectorWithContextContext *ctx) = 0;

  virtual void enterContextSelector(CHTLParser::ContextSelectorContext *ctx) = 0;
  virtual void exitContextSelector(CHTLParser::ContextSelectorContext *ctx) = 0;

  virtual void enterCssProperties(CHTLParser::CssPropertiesContext *ctx) = 0;
  virtual void exitCssProperties(CHTLParser::CssPropertiesContext *ctx) = 0;

  virtual void enterCssProperty(CHTLParser::CssPropertyContext *ctx) = 0;
  virtual void exitCssProperty(CHTLParser::CssPropertyContext *ctx) = 0;

  virtual void enterFunctionCall(CHTLParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(CHTLParser::FunctionCallContext *ctx) = 0;

  virtual void enterArgumentList(CHTLParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(CHTLParser::ArgumentListContext *ctx) = 0;

  virtual void enterArgument(CHTLParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(CHTLParser::ArgumentContext *ctx) = 0;


};

