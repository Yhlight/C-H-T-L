
// Generated from grammars/chtl/CHTL_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTL_simpleParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CHTL_simpleParser.
 */
class  CHTL_simpleListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(CHTL_simpleParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(CHTL_simpleParser::ProgramContext *ctx) = 0;

  virtual void enterStatement(CHTL_simpleParser::StatementContext *ctx) = 0;
  virtual void exitStatement(CHTL_simpleParser::StatementContext *ctx) = 0;

  virtual void enterElementStatement(CHTL_simpleParser::ElementStatementContext *ctx) = 0;
  virtual void exitElementStatement(CHTL_simpleParser::ElementStatementContext *ctx) = 0;

  virtual void enterAttributes(CHTL_simpleParser::AttributesContext *ctx) = 0;
  virtual void exitAttributes(CHTL_simpleParser::AttributesContext *ctx) = 0;

  virtual void enterAttribute(CHTL_simpleParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(CHTL_simpleParser::AttributeContext *ctx) = 0;

  virtual void enterElementContent(CHTL_simpleParser::ElementContentContext *ctx) = 0;
  virtual void exitElementContent(CHTL_simpleParser::ElementContentContext *ctx) = 0;

  virtual void enterTextBlock(CHTL_simpleParser::TextBlockContext *ctx) = 0;
  virtual void exitTextBlock(CHTL_simpleParser::TextBlockContext *ctx) = 0;

  virtual void enterStyleBlock(CHTL_simpleParser::StyleBlockContext *ctx) = 0;
  virtual void exitStyleBlock(CHTL_simpleParser::StyleBlockContext *ctx) = 0;

  virtual void enterScriptBlock(CHTL_simpleParser::ScriptBlockContext *ctx) = 0;
  virtual void exitScriptBlock(CHTL_simpleParser::ScriptBlockContext *ctx) = 0;

  virtual void enterTemplateStatement(CHTL_simpleParser::TemplateStatementContext *ctx) = 0;
  virtual void exitTemplateStatement(CHTL_simpleParser::TemplateStatementContext *ctx) = 0;

  virtual void enterCustomStatement(CHTL_simpleParser::CustomStatementContext *ctx) = 0;
  virtual void exitCustomStatement(CHTL_simpleParser::CustomStatementContext *ctx) = 0;

  virtual void enterOriginStatement(CHTL_simpleParser::OriginStatementContext *ctx) = 0;
  virtual void exitOriginStatement(CHTL_simpleParser::OriginStatementContext *ctx) = 0;


};

