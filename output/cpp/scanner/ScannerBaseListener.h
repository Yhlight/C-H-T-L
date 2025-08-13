
// Generated from Scanner.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "ScannerListener.h"


/**
 * This class provides an empty implementation of ScannerListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ScannerBaseListener : public ScannerListener {
public:

  virtual void enterDocument(ScannerParser::DocumentContext * /*ctx*/) override { }
  virtual void exitDocument(ScannerParser::DocumentContext * /*ctx*/) override { }

  virtual void enterCodeBlock(ScannerParser::CodeBlockContext * /*ctx*/) override { }
  virtual void exitCodeBlock(ScannerParser::CodeBlockContext * /*ctx*/) override { }

  virtual void enterChtlBlock(ScannerParser::ChtlBlockContext * /*ctx*/) override { }
  virtual void exitChtlBlock(ScannerParser::ChtlBlockContext * /*ctx*/) override { }

  virtual void enterChtlElement(ScannerParser::ChtlElementContext * /*ctx*/) override { }
  virtual void exitChtlElement(ScannerParser::ChtlElementContext * /*ctx*/) override { }

  virtual void enterElementStart(ScannerParser::ElementStartContext * /*ctx*/) override { }
  virtual void exitElementStart(ScannerParser::ElementStartContext * /*ctx*/) override { }

  virtual void enterElementEnd(ScannerParser::ElementEndContext * /*ctx*/) override { }
  virtual void exitElementEnd(ScannerParser::ElementEndContext * /*ctx*/) override { }

  virtual void enterElementContent(ScannerParser::ElementContentContext * /*ctx*/) override { }
  virtual void exitElementContent(ScannerParser::ElementContentContext * /*ctx*/) override { }

  virtual void enterChtlAttribute(ScannerParser::ChtlAttributeContext * /*ctx*/) override { }
  virtual void exitChtlAttribute(ScannerParser::ChtlAttributeContext * /*ctx*/) override { }

  virtual void enterChtlDeclaration(ScannerParser::ChtlDeclarationContext * /*ctx*/) override { }
  virtual void exitChtlDeclaration(ScannerParser::ChtlDeclarationContext * /*ctx*/) override { }

  virtual void enterChtlStatement(ScannerParser::ChtlStatementContext * /*ctx*/) override { }
  virtual void exitChtlStatement(ScannerParser::ChtlStatementContext * /*ctx*/) override { }

  virtual void enterTextBlock(ScannerParser::TextBlockContext * /*ctx*/) override { }
  virtual void exitTextBlock(ScannerParser::TextBlockContext * /*ctx*/) override { }

  virtual void enterTextContent(ScannerParser::TextContentContext * /*ctx*/) override { }
  virtual void exitTextContent(ScannerParser::TextContentContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

