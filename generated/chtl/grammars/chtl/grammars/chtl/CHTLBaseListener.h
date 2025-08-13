
// Generated from grammars/chtl/CHTL.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "CHTLListener.h"


/**
 * This class provides an empty implementation of CHTLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CHTLBaseListener : public CHTLListener {
public:

  virtual void enterProgram(CHTLParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(CHTLParser::ProgramContext * /*ctx*/) override { }

  virtual void enterImportStatement(CHTLParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(CHTLParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterNamespaceStatement(CHTLParser::NamespaceStatementContext * /*ctx*/) override { }
  virtual void exitNamespaceStatement(CHTLParser::NamespaceStatementContext * /*ctx*/) override { }

  virtual void enterConfigurationStatement(CHTLParser::ConfigurationStatementContext * /*ctx*/) override { }
  virtual void exitConfigurationStatement(CHTLParser::ConfigurationStatementContext * /*ctx*/) override { }

  virtual void enterConfigurationContent(CHTLParser::ConfigurationContentContext * /*ctx*/) override { }
  virtual void exitConfigurationContent(CHTLParser::ConfigurationContentContext * /*ctx*/) override { }

  virtual void enterKeyValuePair(CHTLParser::KeyValuePairContext * /*ctx*/) override { }
  virtual void exitKeyValuePair(CHTLParser::KeyValuePairContext * /*ctx*/) override { }

  virtual void enterTemplateStatement(CHTLParser::TemplateStatementContext * /*ctx*/) override { }
  virtual void exitTemplateStatement(CHTLParser::TemplateStatementContext * /*ctx*/) override { }

  virtual void enterTemplateContent(CHTLParser::TemplateContentContext * /*ctx*/) override { }
  virtual void exitTemplateContent(CHTLParser::TemplateContentContext * /*ctx*/) override { }

  virtual void enterCustomStatement(CHTLParser::CustomStatementContext * /*ctx*/) override { }
  virtual void exitCustomStatement(CHTLParser::CustomStatementContext * /*ctx*/) override { }

  virtual void enterCustomContent(CHTLParser::CustomContentContext * /*ctx*/) override { }
  virtual void exitCustomContent(CHTLParser::CustomContentContext * /*ctx*/) override { }

  virtual void enterOriginStatement(CHTLParser::OriginStatementContext * /*ctx*/) override { }
  virtual void exitOriginStatement(CHTLParser::OriginStatementContext * /*ctx*/) override { }

  virtual void enterOriginType(CHTLParser::OriginTypeContext * /*ctx*/) override { }
  virtual void exitOriginType(CHTLParser::OriginTypeContext * /*ctx*/) override { }

  virtual void enterOriginContent(CHTLParser::OriginContentContext * /*ctx*/) override { }
  virtual void exitOriginContent(CHTLParser::OriginContentContext * /*ctx*/) override { }

  virtual void enterRawContent(CHTLParser::RawContentContext * /*ctx*/) override { }
  virtual void exitRawContent(CHTLParser::RawContentContext * /*ctx*/) override { }

  virtual void enterElementStatement(CHTLParser::ElementStatementContext * /*ctx*/) override { }
  virtual void exitElementStatement(CHTLParser::ElementStatementContext * /*ctx*/) override { }

  virtual void enterElementName(CHTLParser::ElementNameContext * /*ctx*/) override { }
  virtual void exitElementName(CHTLParser::ElementNameContext * /*ctx*/) override { }

  virtual void enterAttributes(CHTLParser::AttributesContext * /*ctx*/) override { }
  virtual void exitAttributes(CHTLParser::AttributesContext * /*ctx*/) override { }

  virtual void enterAttributeList(CHTLParser::AttributeListContext * /*ctx*/) override { }
  virtual void exitAttributeList(CHTLParser::AttributeListContext * /*ctx*/) override { }

  virtual void enterAttribute(CHTLParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(CHTLParser::AttributeContext * /*ctx*/) override { }

  virtual void enterElementContent(CHTLParser::ElementContentContext * /*ctx*/) override { }
  virtual void exitElementContent(CHTLParser::ElementContentContext * /*ctx*/) override { }

  virtual void enterTextBlock(CHTLParser::TextBlockContext * /*ctx*/) override { }
  virtual void exitTextBlock(CHTLParser::TextBlockContext * /*ctx*/) override { }

  virtual void enterTextContent(CHTLParser::TextContentContext * /*ctx*/) override { }
  virtual void exitTextContent(CHTLParser::TextContentContext * /*ctx*/) override { }

  virtual void enterStyleBlock(CHTLParser::StyleBlockContext * /*ctx*/) override { }
  virtual void exitStyleBlock(CHTLParser::StyleBlockContext * /*ctx*/) override { }

  virtual void enterStyleContent(CHTLParser::StyleContentContext * /*ctx*/) override { }
  virtual void exitStyleContent(CHTLParser::StyleContentContext * /*ctx*/) override { }

  virtual void enterScriptBlock(CHTLParser::ScriptBlockContext * /*ctx*/) override { }
  virtual void exitScriptBlock(CHTLParser::ScriptBlockContext * /*ctx*/) override { }

  virtual void enterScriptContent(CHTLParser::ScriptContentContext * /*ctx*/) override { }
  virtual void exitScriptContent(CHTLParser::ScriptContentContext * /*ctx*/) override { }

  virtual void enterCssRule(CHTLParser::CssRuleContext * /*ctx*/) override { }
  virtual void exitCssRule(CHTLParser::CssRuleContext * /*ctx*/) override { }

  virtual void enterSelector(CHTLParser::SelectorContext * /*ctx*/) override { }
  virtual void exitSelector(CHTLParser::SelectorContext * /*ctx*/) override { }

  virtual void enterSelectorWithContext(CHTLParser::SelectorWithContextContext * /*ctx*/) override { }
  virtual void exitSelectorWithContext(CHTLParser::SelectorWithContextContext * /*ctx*/) override { }

  virtual void enterContextSelector(CHTLParser::ContextSelectorContext * /*ctx*/) override { }
  virtual void exitContextSelector(CHTLParser::ContextSelectorContext * /*ctx*/) override { }

  virtual void enterCssProperties(CHTLParser::CssPropertiesContext * /*ctx*/) override { }
  virtual void exitCssProperties(CHTLParser::CssPropertiesContext * /*ctx*/) override { }

  virtual void enterCssProperty(CHTLParser::CssPropertyContext * /*ctx*/) override { }
  virtual void exitCssProperty(CHTLParser::CssPropertyContext * /*ctx*/) override { }

  virtual void enterFunctionCall(CHTLParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(CHTLParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterArgumentList(CHTLParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(CHTLParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterArgument(CHTLParser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(CHTLParser::ArgumentContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

