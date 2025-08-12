
// Generated from grammars/css/CSS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CSS_simpleParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CSS_simpleParser.
 */
class  CSS_simpleListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStylesheet(CSS_simpleParser::StylesheetContext *ctx) = 0;
  virtual void exitStylesheet(CSS_simpleParser::StylesheetContext *ctx) = 0;

  virtual void enterRule(CSS_simpleParser::RuleContext *ctx) = 0;
  virtual void exitRule(CSS_simpleParser::RuleContext *ctx) = 0;

  virtual void enterSelector(CSS_simpleParser::SelectorContext *ctx) = 0;
  virtual void exitSelector(CSS_simpleParser::SelectorContext *ctx) = 0;

  virtual void enterDeclarationList(CSS_simpleParser::DeclarationListContext *ctx) = 0;
  virtual void exitDeclarationList(CSS_simpleParser::DeclarationListContext *ctx) = 0;

  virtual void enterDeclaration(CSS_simpleParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(CSS_simpleParser::DeclarationContext *ctx) = 0;

  virtual void enterProperty(CSS_simpleParser::PropertyContext *ctx) = 0;
  virtual void exitProperty(CSS_simpleParser::PropertyContext *ctx) = 0;

  virtual void enterValue(CSS_simpleParser::ValueContext *ctx) = 0;
  virtual void exitValue(CSS_simpleParser::ValueContext *ctx) = 0;


};

