
// Generated from grammars/css/CSS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CSS_simpleParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CSS_simpleParser.
 */
class  CSS_simpleVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CSS_simpleParser.
   */
    virtual std::any visitStylesheet(CSS_simpleParser::StylesheetContext *context) = 0;

    virtual std::any visitRule(CSS_simpleParser::RuleContext *context) = 0;

    virtual std::any visitSelector(CSS_simpleParser::SelectorContext *context) = 0;

    virtual std::any visitDeclarationList(CSS_simpleParser::DeclarationListContext *context) = 0;

    virtual std::any visitDeclaration(CSS_simpleParser::DeclarationContext *context) = 0;

    virtual std::any visitProperty(CSS_simpleParser::PropertyContext *context) = 0;

    virtual std::any visitValue(CSS_simpleParser::ValueContext *context) = 0;


};

