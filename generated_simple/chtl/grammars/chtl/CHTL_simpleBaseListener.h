
// Generated from grammars/chtl/CHTL_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTL_simpleListener.h"


/**
 * This class provides an empty implementation of CHTL_simpleListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CHTL_simpleBaseListener : public CHTL_simpleListener {
public:

  virtual void enterProgram(CHTL_simpleParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(CHTL_simpleParser::ProgramContext * /*ctx*/) override { }

  virtual void enterStatement(CHTL_simpleParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(CHTL_simpleParser::StatementContext * /*ctx*/) override { }

  virtual void enterElementStatement(CHTL_simpleParser::ElementStatementContext * /*ctx*/) override { }
  virtual void exitElementStatement(CHTL_simpleParser::ElementStatementContext * /*ctx*/) override { }

  virtual void enterAttributes(CHTL_simpleParser::AttributesContext * /*ctx*/) override { }
  virtual void exitAttributes(CHTL_simpleParser::AttributesContext * /*ctx*/) override { }

  virtual void enterAttribute(CHTL_simpleParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(CHTL_simpleParser::AttributeContext * /*ctx*/) override { }

  virtual void enterElementContent(CHTL_simpleParser::ElementContentContext * /*ctx*/) override { }
  virtual void exitElementContent(CHTL_simpleParser::ElementContentContext * /*ctx*/) override { }

  virtual void enterTextBlock(CHTL_simpleParser::TextBlockContext * /*ctx*/) override { }
  virtual void exitTextBlock(CHTL_simpleParser::TextBlockContext * /*ctx*/) override { }

  virtual void enterStyleBlock(CHTL_simpleParser::StyleBlockContext * /*ctx*/) override { }
  virtual void exitStyleBlock(CHTL_simpleParser::StyleBlockContext * /*ctx*/) override { }

  virtual void enterScriptBlock(CHTL_simpleParser::ScriptBlockContext * /*ctx*/) override { }
  virtual void exitScriptBlock(CHTL_simpleParser::ScriptBlockContext * /*ctx*/) override { }

  virtual void enterTemplateStatement(CHTL_simpleParser::TemplateStatementContext * /*ctx*/) override { }
  virtual void exitTemplateStatement(CHTL_simpleParser::TemplateStatementContext * /*ctx*/) override { }

  virtual void enterCustomStatement(CHTL_simpleParser::CustomStatementContext * /*ctx*/) override { }
  virtual void exitCustomStatement(CHTL_simpleParser::CustomStatementContext * /*ctx*/) override { }

  virtual void enterOriginStatement(CHTL_simpleParser::OriginStatementContext * /*ctx*/) override { }
  virtual void exitOriginStatement(CHTL_simpleParser::OriginStatementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

