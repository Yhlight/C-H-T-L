
// Generated from grammars/chtl/CHTL_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTL_simpleParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CHTL_simpleParser.
 */
class  CHTL_simpleVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CHTL_simpleParser.
   */
    virtual std::any visitProgram(CHTL_simpleParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(CHTL_simpleParser::StatementContext *context) = 0;

    virtual std::any visitElementStatement(CHTL_simpleParser::ElementStatementContext *context) = 0;

    virtual std::any visitAttributes(CHTL_simpleParser::AttributesContext *context) = 0;

    virtual std::any visitAttribute(CHTL_simpleParser::AttributeContext *context) = 0;

    virtual std::any visitElementContent(CHTL_simpleParser::ElementContentContext *context) = 0;

    virtual std::any visitTextBlock(CHTL_simpleParser::TextBlockContext *context) = 0;

    virtual std::any visitStyleBlock(CHTL_simpleParser::StyleBlockContext *context) = 0;

    virtual std::any visitScriptBlock(CHTL_simpleParser::ScriptBlockContext *context) = 0;

    virtual std::any visitTemplateStatement(CHTL_simpleParser::TemplateStatementContext *context) = 0;

    virtual std::any visitCustomStatement(CHTL_simpleParser::CustomStatementContext *context) = 0;

    virtual std::any visitOriginStatement(CHTL_simpleParser::OriginStatementContext *context) = 0;


};

