
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLJS_simpleParser : public antlr4::Parser {
public:
  enum {
    WS = 1, COMMENT = 2, CHTL_SCRIPT = 3, CHTL_LISTEN = 4, CHTL_DELEGATE = 5, 
    CHTL_ANIMATE = 6, CHTL_DOUBLE_BRACE = 7, CHTL_DOUBLE_BRACE_CLOSE = 8, 
    CHTL_ARROW = 9, IDENTIFIER = 10, NUMBER = 11, STRING = 12, LBRACE = 13, 
    RBRACE = 14, LPAREN = 15, RPAREN = 16, SEMICOLON = 17, COLON = 18, COMMA = 19, 
    DOT = 20, HASH = 21
  };

  enum {
    RuleChtlScriptBlock = 0, RuleChtlScriptContent = 1, RuleChtlStatement = 2, 
    RuleChtlSelectorStatement = 3, RuleChtlSelector = 4, RuleSelectorContent = 5, 
    RuleChtlListenStatement = 6, RuleChtlListenObject = 7, RuleChtlListenEvents = 8, 
    RuleChtlListenEvent = 9, RuleEventType = 10, RuleEventHandler = 11, 
    RuleChtlDelegateStatement = 12, RuleChtlDelegateObject = 13, RuleChtlDelegateConfig = 14, 
    RuleChtlTargetConfig = 15, RuleChtlEventConfig = 16, RuleChtlAnimateStatement = 17, 
    RuleChtlAnimateObject = 18, RuleChtlAnimateConfig = 19, RuleChtlAnimateProperty = 20, 
    RuleChtlDuration = 21, RuleChtlEasing = 22, RuleEasingValue = 23, RuleChtlBegin = 24, 
    RuleChtlEnd = 25, RuleChtlCssProperties = 26, RuleChtlCssProperty = 27, 
    RulePropertyName = 28, RulePropertyValue = 29, RuleMethodCall = 30, 
    RuleArguments = 31, RuleArgumentList = 32, RuleBasicStatement = 33
  };

  explicit CHTLJS_simpleParser(antlr4::TokenStream *input);

  CHTLJS_simpleParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CHTLJS_simpleParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ChtlScriptBlockContext;
  class ChtlScriptContentContext;
  class ChtlStatementContext;
  class ChtlSelectorStatementContext;
  class ChtlSelectorContext;
  class SelectorContentContext;
  class ChtlListenStatementContext;
  class ChtlListenObjectContext;
  class ChtlListenEventsContext;
  class ChtlListenEventContext;
  class EventTypeContext;
  class EventHandlerContext;
  class ChtlDelegateStatementContext;
  class ChtlDelegateObjectContext;
  class ChtlDelegateConfigContext;
  class ChtlTargetConfigContext;
  class ChtlEventConfigContext;
  class ChtlAnimateStatementContext;
  class ChtlAnimateObjectContext;
  class ChtlAnimateConfigContext;
  class ChtlAnimatePropertyContext;
  class ChtlDurationContext;
  class ChtlEasingContext;
  class EasingValueContext;
  class ChtlBeginContext;
  class ChtlEndContext;
  class ChtlCssPropertiesContext;
  class ChtlCssPropertyContext;
  class PropertyNameContext;
  class PropertyValueContext;
  class MethodCallContext;
  class ArgumentsContext;
  class ArgumentListContext;
  class BasicStatementContext; 

  class  ChtlScriptBlockContext : public antlr4::ParserRuleContext {
  public:
    ChtlScriptBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHTL_SCRIPT();
    antlr4::tree::TerminalNode *LBRACE();
    ChtlScriptContentContext *chtlScriptContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlScriptBlockContext* chtlScriptBlock();

  class  ChtlScriptContentContext : public antlr4::ParserRuleContext {
  public:
    ChtlScriptContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ChtlStatementContext *> chtlStatement();
    ChtlStatementContext* chtlStatement(size_t i);
    std::vector<BasicStatementContext *> basicStatement();
    BasicStatementContext* basicStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlScriptContentContext* chtlScriptContent();

  class  ChtlStatementContext : public antlr4::ParserRuleContext {
  public:
    ChtlStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlSelectorStatementContext *chtlSelectorStatement();
    ChtlListenStatementContext *chtlListenStatement();
    ChtlDelegateStatementContext *chtlDelegateStatement();
    ChtlAnimateStatementContext *chtlAnimateStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlStatementContext* chtlStatement();

  class  ChtlSelectorStatementContext : public antlr4::ParserRuleContext {
  public:
    ChtlSelectorStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlSelectorContext *chtlSelector();
    antlr4::tree::TerminalNode *DOT();
    MethodCallContext *methodCall();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlSelectorStatementContext* chtlSelectorStatement();

  class  ChtlSelectorContext : public antlr4::ParserRuleContext {
  public:
    ChtlSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHTL_DOUBLE_BRACE();
    SelectorContentContext *selectorContent();
    antlr4::tree::TerminalNode *CHTL_DOUBLE_BRACE_CLOSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlSelectorContext* chtlSelector();

  class  SelectorContentContext : public antlr4::ParserRuleContext {
  public:
    SelectorContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *HASH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectorContentContext* selectorContent();

  class  ChtlListenStatementContext : public antlr4::ParserRuleContext {
  public:
    ChtlListenStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlSelectorContext *chtlSelector();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *CHTL_LISTEN();
    antlr4::tree::TerminalNode *LPAREN();
    ChtlListenObjectContext *chtlListenObject();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlListenStatementContext* chtlListenStatement();

  class  ChtlListenObjectContext : public antlr4::ParserRuleContext {
  public:
    ChtlListenObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    ChtlListenEventsContext *chtlListenEvents();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlListenObjectContext* chtlListenObject();

  class  ChtlListenEventsContext : public antlr4::ParserRuleContext {
  public:
    ChtlListenEventsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ChtlListenEventContext *> chtlListenEvent();
    ChtlListenEventContext* chtlListenEvent(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlListenEventsContext* chtlListenEvents();

  class  ChtlListenEventContext : public antlr4::ParserRuleContext {
  public:
    ChtlListenEventContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EventTypeContext *eventType();
    antlr4::tree::TerminalNode *COLON();
    EventHandlerContext *eventHandler();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlListenEventContext* chtlListenEvent();

  class  EventTypeContext : public antlr4::ParserRuleContext {
  public:
    EventTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EventTypeContext* eventType();

  class  EventHandlerContext : public antlr4::ParserRuleContext {
  public:
    EventHandlerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EventHandlerContext* eventHandler();

  class  ChtlDelegateStatementContext : public antlr4::ParserRuleContext {
  public:
    ChtlDelegateStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlSelectorContext *chtlSelector();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *CHTL_DELEGATE();
    antlr4::tree::TerminalNode *LPAREN();
    ChtlDelegateObjectContext *chtlDelegateObject();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlDelegateStatementContext* chtlDelegateStatement();

  class  ChtlDelegateObjectContext : public antlr4::ParserRuleContext {
  public:
    ChtlDelegateObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    ChtlDelegateConfigContext *chtlDelegateConfig();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlDelegateObjectContext* chtlDelegateObject();

  class  ChtlDelegateConfigContext : public antlr4::ParserRuleContext {
  public:
    ChtlDelegateConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlTargetConfigContext *chtlTargetConfig();
    antlr4::tree::TerminalNode *COMMA();
    ChtlEventConfigContext *chtlEventConfig();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlDelegateConfigContext* chtlDelegateConfig();

  class  ChtlTargetConfigContext : public antlr4::ParserRuleContext {
  public:
    ChtlTargetConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    ChtlSelectorContext *chtlSelector();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlTargetConfigContext* chtlTargetConfig();

  class  ChtlEventConfigContext : public antlr4::ParserRuleContext {
  public:
    ChtlEventConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlListenEventsContext *chtlListenEvents();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlEventConfigContext* chtlEventConfig();

  class  ChtlAnimateStatementContext : public antlr4::ParserRuleContext {
  public:
    ChtlAnimateStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHTL_ANIMATE();
    antlr4::tree::TerminalNode *LPAREN();
    ChtlAnimateObjectContext *chtlAnimateObject();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlAnimateStatementContext* chtlAnimateStatement();

  class  ChtlAnimateObjectContext : public antlr4::ParserRuleContext {
  public:
    ChtlAnimateObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    ChtlAnimateConfigContext *chtlAnimateConfig();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlAnimateObjectContext* chtlAnimateObject();

  class  ChtlAnimateConfigContext : public antlr4::ParserRuleContext {
  public:
    ChtlAnimateConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ChtlAnimatePropertyContext *> chtlAnimateProperty();
    ChtlAnimatePropertyContext* chtlAnimateProperty(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlAnimateConfigContext* chtlAnimateConfig();

  class  ChtlAnimatePropertyContext : public antlr4::ParserRuleContext {
  public:
    ChtlAnimatePropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlDurationContext *chtlDuration();
    ChtlEasingContext *chtlEasing();
    ChtlBeginContext *chtlBegin();
    ChtlEndContext *chtlEnd();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlAnimatePropertyContext* chtlAnimateProperty();

  class  ChtlDurationContext : public antlr4::ParserRuleContext {
  public:
    ChtlDurationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlDurationContext* chtlDuration();

  class  ChtlEasingContext : public antlr4::ParserRuleContext {
  public:
    ChtlEasingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    EasingValueContext *easingValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlEasingContext* chtlEasing();

  class  EasingValueContext : public antlr4::ParserRuleContext {
  public:
    EasingValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EasingValueContext* easingValue();

  class  ChtlBeginContext : public antlr4::ParserRuleContext {
  public:
    ChtlBeginContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *LBRACE();
    ChtlCssPropertiesContext *chtlCssProperties();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlBeginContext* chtlBegin();

  class  ChtlEndContext : public antlr4::ParserRuleContext {
  public:
    ChtlEndContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *LBRACE();
    ChtlCssPropertiesContext *chtlCssProperties();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlEndContext* chtlEnd();

  class  ChtlCssPropertiesContext : public antlr4::ParserRuleContext {
  public:
    ChtlCssPropertiesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ChtlCssPropertyContext *> chtlCssProperty();
    ChtlCssPropertyContext* chtlCssProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlCssPropertiesContext* chtlCssProperties();

  class  ChtlCssPropertyContext : public antlr4::ParserRuleContext {
  public:
    ChtlCssPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *COLON();
    PropertyValueContext *propertyValue();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChtlCssPropertyContext* chtlCssProperty();

  class  PropertyNameContext : public antlr4::ParserRuleContext {
  public:
    PropertyNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyNameContext* propertyName();

  class  PropertyValueContext : public antlr4::ParserRuleContext {
  public:
    PropertyValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyValueContext* propertyValue();

  class  MethodCallContext : public antlr4::ParserRuleContext {
  public:
    MethodCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentsContext *arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MethodCallContext* methodCall();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgumentListContext *argumentList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();

  class  BasicStatementContext : public antlr4::ParserRuleContext {
  public:
    BasicStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicStatementContext* basicStatement();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

