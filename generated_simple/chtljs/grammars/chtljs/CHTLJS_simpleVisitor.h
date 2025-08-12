
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJS_simpleParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CHTLJS_simpleParser.
 */
class  CHTLJS_simpleVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CHTLJS_simpleParser.
   */
    virtual std::any visitChtlScriptBlock(CHTLJS_simpleParser::ChtlScriptBlockContext *context) = 0;

    virtual std::any visitChtlScriptContent(CHTLJS_simpleParser::ChtlScriptContentContext *context) = 0;

    virtual std::any visitChtlStatement(CHTLJS_simpleParser::ChtlStatementContext *context) = 0;

    virtual std::any visitChtlSelectorStatement(CHTLJS_simpleParser::ChtlSelectorStatementContext *context) = 0;

    virtual std::any visitChtlSelector(CHTLJS_simpleParser::ChtlSelectorContext *context) = 0;

    virtual std::any visitSelectorContent(CHTLJS_simpleParser::SelectorContentContext *context) = 0;

    virtual std::any visitChtlListenStatement(CHTLJS_simpleParser::ChtlListenStatementContext *context) = 0;

    virtual std::any visitChtlListenObject(CHTLJS_simpleParser::ChtlListenObjectContext *context) = 0;

    virtual std::any visitChtlListenEvents(CHTLJS_simpleParser::ChtlListenEventsContext *context) = 0;

    virtual std::any visitChtlListenEvent(CHTLJS_simpleParser::ChtlListenEventContext *context) = 0;

    virtual std::any visitEventType(CHTLJS_simpleParser::EventTypeContext *context) = 0;

    virtual std::any visitEventHandler(CHTLJS_simpleParser::EventHandlerContext *context) = 0;

    virtual std::any visitChtlDelegateStatement(CHTLJS_simpleParser::ChtlDelegateStatementContext *context) = 0;

    virtual std::any visitChtlDelegateObject(CHTLJS_simpleParser::ChtlDelegateObjectContext *context) = 0;

    virtual std::any visitChtlDelegateConfig(CHTLJS_simpleParser::ChtlDelegateConfigContext *context) = 0;

    virtual std::any visitChtlTargetConfig(CHTLJS_simpleParser::ChtlTargetConfigContext *context) = 0;

    virtual std::any visitChtlEventConfig(CHTLJS_simpleParser::ChtlEventConfigContext *context) = 0;

    virtual std::any visitChtlAnimateStatement(CHTLJS_simpleParser::ChtlAnimateStatementContext *context) = 0;

    virtual std::any visitChtlAnimateObject(CHTLJS_simpleParser::ChtlAnimateObjectContext *context) = 0;

    virtual std::any visitChtlAnimateConfig(CHTLJS_simpleParser::ChtlAnimateConfigContext *context) = 0;

    virtual std::any visitChtlAnimateProperty(CHTLJS_simpleParser::ChtlAnimatePropertyContext *context) = 0;

    virtual std::any visitChtlDuration(CHTLJS_simpleParser::ChtlDurationContext *context) = 0;

    virtual std::any visitChtlEasing(CHTLJS_simpleParser::ChtlEasingContext *context) = 0;

    virtual std::any visitEasingValue(CHTLJS_simpleParser::EasingValueContext *context) = 0;

    virtual std::any visitChtlBegin(CHTLJS_simpleParser::ChtlBeginContext *context) = 0;

    virtual std::any visitChtlEnd(CHTLJS_simpleParser::ChtlEndContext *context) = 0;

    virtual std::any visitChtlCssProperties(CHTLJS_simpleParser::ChtlCssPropertiesContext *context) = 0;

    virtual std::any visitChtlCssProperty(CHTLJS_simpleParser::ChtlCssPropertyContext *context) = 0;

    virtual std::any visitPropertyName(CHTLJS_simpleParser::PropertyNameContext *context) = 0;

    virtual std::any visitPropertyValue(CHTLJS_simpleParser::PropertyValueContext *context) = 0;

    virtual std::any visitMethodCall(CHTLJS_simpleParser::MethodCallContext *context) = 0;

    virtual std::any visitArguments(CHTLJS_simpleParser::ArgumentsContext *context) = 0;

    virtual std::any visitArgumentList(CHTLJS_simpleParser::ArgumentListContext *context) = 0;

    virtual std::any visitBasicStatement(CHTLJS_simpleParser::BasicStatementContext *context) = 0;


};

