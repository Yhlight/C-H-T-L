
// Generated from grammars/css/CSS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CSS_simpleListener.h"


/**
 * This class provides an empty implementation of CSS_simpleListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CSS_simpleBaseListener : public CSS_simpleListener {
public:

  virtual void enterStylesheet(CSS_simpleParser::StylesheetContext * /*ctx*/) override { }
  virtual void exitStylesheet(CSS_simpleParser::StylesheetContext * /*ctx*/) override { }

  virtual void enterRule(CSS_simpleParser::RuleContext * /*ctx*/) override { }
  virtual void exitRule(CSS_simpleParser::RuleContext * /*ctx*/) override { }

  virtual void enterSelector(CSS_simpleParser::SelectorContext * /*ctx*/) override { }
  virtual void exitSelector(CSS_simpleParser::SelectorContext * /*ctx*/) override { }

  virtual void enterDeclarationList(CSS_simpleParser::DeclarationListContext * /*ctx*/) override { }
  virtual void exitDeclarationList(CSS_simpleParser::DeclarationListContext * /*ctx*/) override { }

  virtual void enterDeclaration(CSS_simpleParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(CSS_simpleParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterProperty(CSS_simpleParser::PropertyContext * /*ctx*/) override { }
  virtual void exitProperty(CSS_simpleParser::PropertyContext * /*ctx*/) override { }

  virtual void enterValue(CSS_simpleParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(CSS_simpleParser::ValueContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

