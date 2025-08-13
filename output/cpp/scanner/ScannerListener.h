
// Generated from Scanner.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "ScannerParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ScannerParser.
 */
class  ScannerListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterDocument(ScannerParser::DocumentContext *ctx) = 0;
  virtual void exitDocument(ScannerParser::DocumentContext *ctx) = 0;

  virtual void enterCodeBlock(ScannerParser::CodeBlockContext *ctx) = 0;
  virtual void exitCodeBlock(ScannerParser::CodeBlockContext *ctx) = 0;

  virtual void enterChtlBlock(ScannerParser::ChtlBlockContext *ctx) = 0;
  virtual void exitChtlBlock(ScannerParser::ChtlBlockContext *ctx) = 0;

  virtual void enterChtlElement(ScannerParser::ChtlElementContext *ctx) = 0;
  virtual void exitChtlElement(ScannerParser::ChtlElementContext *ctx) = 0;

  virtual void enterElementStart(ScannerParser::ElementStartContext *ctx) = 0;
  virtual void exitElementStart(ScannerParser::ElementStartContext *ctx) = 0;

  virtual void enterElementEnd(ScannerParser::ElementEndContext *ctx) = 0;
  virtual void exitElementEnd(ScannerParser::ElementEndContext *ctx) = 0;

  virtual void enterElementContent(ScannerParser::ElementContentContext *ctx) = 0;
  virtual void exitElementContent(ScannerParser::ElementContentContext *ctx) = 0;

  virtual void enterChtlAttribute(ScannerParser::ChtlAttributeContext *ctx) = 0;
  virtual void exitChtlAttribute(ScannerParser::ChtlAttributeContext *ctx) = 0;

  virtual void enterChtlDeclaration(ScannerParser::ChtlDeclarationContext *ctx) = 0;
  virtual void exitChtlDeclaration(ScannerParser::ChtlDeclarationContext *ctx) = 0;

  virtual void enterChtlStatement(ScannerParser::ChtlStatementContext *ctx) = 0;
  virtual void exitChtlStatement(ScannerParser::ChtlStatementContext *ctx) = 0;

  virtual void enterTextBlock(ScannerParser::TextBlockContext *ctx) = 0;
  virtual void exitTextBlock(ScannerParser::TextBlockContext *ctx) = 0;

  virtual void enterTextContent(ScannerParser::TextContentContext *ctx) = 0;
  virtual void exitTextContent(ScannerParser::TextContentContext *ctx) = 0;


};

