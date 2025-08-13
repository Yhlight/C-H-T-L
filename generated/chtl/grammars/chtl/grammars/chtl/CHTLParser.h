
// Generated from grammars/chtl/CHTL.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  CHTLParser : public antlr4::Parser {
public:
  enum {
    WS = 1, COMMENT = 2, MULTILINE_COMMENT = 3, GENERATOR_COMMENT = 4, TEMPLATE = 5, 
    CUSTOM = 6, ORIGIN = 7, CONFIGURATION = 8, IMPORT = 9, NAMESPACE = 10, 
    INFO = 11, EXPORT = 12, STYLE = 13, ELEMENT = 14, VAR = 15, HTML = 16, 
    CSS = 17, JAVASCRIPT = 18, CHTL = 19, INHERIT = 20, DELETE = 21, INSERT = 22, 
    AFTER = 23, BEFORE = 24, REPLACE = 25, AT_TOP = 26, AT_BOTTOM = 27, 
    FROM = 28, AS = 29, EXCEPT = 30, TEXT = 31, STYLE_BLOCK = 32, SCRIPT = 33, 
    LBRACE = 34, RBRACE = 35, LBRACKET = 36, RBRACKET = 37, LPAREN = 38, 
    RPAREN = 39, SEMICOLON = 40, COLON = 41, EQUALS = 42, COMMA = 43, DOT = 44, 
    HASH = 45, PERIOD = 46, IDENTIFIER = 47, NUMBER = 48, STRING = 49, LITERAL = 50
  };

  enum {
    RuleProgram = 0, RuleImportStatement = 1, RuleNamespaceStatement = 2, 
    RuleConfigurationStatement = 3, RuleConfigurationContent = 4, RuleKeyValuePair = 5, 
    RuleTemplateStatement = 6, RuleTemplateContent = 7, RuleCustomStatement = 8, 
    RuleCustomContent = 9, RuleOriginStatement = 10, RuleOriginType = 11, 
    RuleOriginContent = 12, RuleRawContent = 13, RuleElementStatement = 14, 
    RuleElementName = 15, RuleAttributes = 16, RuleAttributeList = 17, RuleAttribute = 18, 
    RuleElementContent = 19, RuleTextBlock = 20, RuleTextContent = 21, RuleStyleBlock = 22, 
    RuleStyleContent = 23, RuleScriptBlock = 24, RuleScriptContent = 25, 
    RuleCssRule = 26, RuleSelector = 27, RuleSelectorWithContext = 28, RuleContextSelector = 29, 
    RuleCssProperties = 30, RuleCssProperty = 31, RuleFunctionCall = 32, 
    RuleArgumentList = 33, RuleArgument = 34
  };

  explicit CHTLParser(antlr4::TokenStream *input);
  ~CHTLParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class ImportStatementContext;
  class NamespaceStatementContext;
  class ConfigurationStatementContext;
  class ConfigurationContentContext;
  class KeyValuePairContext;
  class TemplateStatementContext;
  class TemplateContentContext;
  class CustomStatementContext;
  class CustomContentContext;
  class OriginStatementContext;
  class OriginTypeContext;
  class OriginContentContext;
  class RawContentContext;
  class ElementStatementContext;
  class ElementNameContext;
  class AttributesContext;
  class AttributeListContext;
  class AttributeContext;
  class ElementContentContext;
  class TextBlockContext;
  class TextContentContext;
  class StyleBlockContext;
  class StyleContentContext;
  class ScriptBlockContext;
  class ScriptContentContext;
  class CssRuleContext;
  class SelectorContext;
  class SelectorWithContextContext;
  class ContextSelectorContext;
  class CssPropertiesContext;
  class CssPropertyContext;
  class FunctionCallContext;
  class ArgumentListContext;
  class ArgumentContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ImportStatementContext *> importStatement();
    ImportStatementContext* importStatement(size_t i);
    std::vector<NamespaceStatementContext *> namespaceStatement();
    NamespaceStatementContext* namespaceStatement(size_t i);
    std::vector<ConfigurationStatementContext *> configurationStatement();
    ConfigurationStatementContext* configurationStatement(size_t i);
    std::vector<TemplateStatementContext *> templateStatement();
    TemplateStatementContext* templateStatement(size_t i);
    std::vector<CustomStatementContext *> customStatement();
    CustomStatementContext* customStatement(size_t i);
    std::vector<OriginStatementContext *> originStatement();
    OriginStatementContext* originStatement(size_t i);
    std::vector<ElementStatementContext *> elementStatement();
    ElementStatementContext* elementStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportStatementContext* importStatement();

  class  NamespaceStatementContext : public antlr4::ParserRuleContext {
  public:
    NamespaceStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMESPACE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamespaceStatementContext* namespaceStatement();

  class  ConfigurationStatementContext : public antlr4::ParserRuleContext {
  public:
    ConfigurationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONFIGURATION();
    antlr4::tree::TerminalNode *LBRACE();
    ConfigurationContentContext *configurationContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigurationStatementContext* configurationStatement();

  class  ConfigurationContentContext : public antlr4::ParserRuleContext {
  public:
    ConfigurationContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<KeyValuePairContext *> keyValuePair();
    KeyValuePairContext* keyValuePair(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigurationContentContext* configurationContent();

  class  KeyValuePairContext : public antlr4::ParserRuleContext {
  public:
    KeyValuePairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  KeyValuePairContext* keyValuePair();

  class  TemplateStatementContext : public antlr4::ParserRuleContext {
  public:
    TemplateStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEMPLATE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    TemplateContentContext *templateContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateStatementContext* templateStatement();

  class  TemplateContentContext : public antlr4::ParserRuleContext {
  public:
    TemplateContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementStatementContext *> elementStatement();
    ElementStatementContext* elementStatement(size_t i);
    std::vector<StyleBlockContext *> styleBlock();
    StyleBlockContext* styleBlock(size_t i);
    std::vector<ScriptBlockContext *> scriptBlock();
    ScriptBlockContext* scriptBlock(size_t i);
    std::vector<RawContentContext *> rawContent();
    RawContentContext* rawContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemplateContentContext* templateContent();

  class  CustomStatementContext : public antlr4::ParserRuleContext {
  public:
    CustomStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CUSTOM();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    CustomContentContext *customContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomStatementContext* customStatement();

  class  CustomContentContext : public antlr4::ParserRuleContext {
  public:
    CustomContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementStatementContext *> elementStatement();
    ElementStatementContext* elementStatement(size_t i);
    std::vector<StyleBlockContext *> styleBlock();
    StyleBlockContext* styleBlock(size_t i);
    std::vector<ScriptBlockContext *> scriptBlock();
    ScriptBlockContext* scriptBlock(size_t i);
    std::vector<RawContentContext *> rawContent();
    RawContentContext* rawContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CustomContentContext* customContent();

  class  OriginStatementContext : public antlr4::ParserRuleContext {
  public:
    OriginStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ORIGIN();
    OriginTypeContext *originType();
    antlr4::tree::TerminalNode *LBRACE();
    OriginContentContext *originContent();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginStatementContext* originStatement();

  class  OriginTypeContext : public antlr4::ParserRuleContext {
  public:
    OriginTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HTML();
    antlr4::tree::TerminalNode *CSS();
    antlr4::tree::TerminalNode *JAVASCRIPT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginTypeContext* originType();

  class  OriginContentContext : public antlr4::ParserRuleContext {
  public:
    OriginContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementStatementContext *> elementStatement();
    ElementStatementContext* elementStatement(size_t i);
    std::vector<StyleBlockContext *> styleBlock();
    StyleBlockContext* styleBlock(size_t i);
    std::vector<ScriptBlockContext *> scriptBlock();
    ScriptBlockContext* scriptBlock(size_t i);
    std::vector<RawContentContext *> rawContent();
    RawContentContext* rawContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OriginContentContext* originContent();

  class  RawContentContext : public antlr4::ParserRuleContext {
  public:
    RawContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LITERAL();
    antlr4::tree::TerminalNode* LITERAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RawContentContext* rawContent();

  class  ElementStatementContext : public antlr4::ParserRuleContext {
  public:
    ElementStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementNameContext *elementName();
    AttributesContext *attributes();
    antlr4::tree::TerminalNode *LBRACE();
    ElementContentContext *elementContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementStatementContext* elementStatement();

  class  ElementNameContext : public antlr4::ParserRuleContext {
  public:
    ElementNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementNameContext* elementName();

  class  AttributesContext : public antlr4::ParserRuleContext {
  public:
    AttributesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    AttributeListContext *attributeList();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributesContext* attributes();

  class  AttributeListContext : public antlr4::ParserRuleContext {
  public:
    AttributeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AttributeContext *> attribute();
    AttributeContext* attribute(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeListContext* attributeList();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeContext* attribute();

  class  ElementContentContext : public antlr4::ParserRuleContext {
  public:
    ElementContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementStatementContext *> elementStatement();
    ElementStatementContext* elementStatement(size_t i);
    std::vector<TextBlockContext *> textBlock();
    TextBlockContext* textBlock(size_t i);
    std::vector<StyleBlockContext *> styleBlock();
    StyleBlockContext* styleBlock(size_t i);
    std::vector<ScriptBlockContext *> scriptBlock();
    ScriptBlockContext* scriptBlock(size_t i);
    std::vector<RawContentContext *> rawContent();
    RawContentContext* rawContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementContentContext* elementContent();

  class  TextBlockContext : public antlr4::ParserRuleContext {
  public:
    TextBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEXT();
    antlr4::tree::TerminalNode *LBRACE();
    TextContentContext *textContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextBlockContext* textBlock();

  class  TextContentContext : public antlr4::ParserRuleContext {
  public:
    TextContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LITERAL();
    antlr4::tree::TerminalNode* LITERAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextContentContext* textContent();

  class  StyleBlockContext : public antlr4::ParserRuleContext {
  public:
    StyleBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STYLE();
    antlr4::tree::TerminalNode *LBRACE();
    StyleContentContext *styleContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StyleBlockContext* styleBlock();

  class  StyleContentContext : public antlr4::ParserRuleContext {
  public:
    StyleContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CssRuleContext *> cssRule();
    CssRuleContext* cssRule(size_t i);
    std::vector<RawContentContext *> rawContent();
    RawContentContext* rawContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StyleContentContext* styleContent();

  class  ScriptBlockContext : public antlr4::ParserRuleContext {
  public:
    ScriptBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *LBRACE();
    ScriptContentContext *scriptContent();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptBlockContext* scriptBlock();

  class  ScriptContentContext : public antlr4::ParserRuleContext {
  public:
    ScriptContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementStatementContext *> elementStatement();
    ElementStatementContext* elementStatement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LITERAL();
    antlr4::tree::TerminalNode* LITERAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<FunctionCallContext *> functionCall();
    FunctionCallContext* functionCall(size_t i);
    std::vector<RawContentContext *> rawContent();
    RawContentContext* rawContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptContentContext* scriptContent();

  class  CssRuleContext : public antlr4::ParserRuleContext {
  public:
    CssRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorContext *selector();
    antlr4::tree::TerminalNode *LBRACE();
    CssPropertiesContext *cssProperties();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssRuleContext* cssRule();

  class  SelectorContext : public antlr4::ParserRuleContext {
  public:
    SelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> HASH();
    antlr4::tree::TerminalNode* HASH(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    std::vector<SelectorWithContextContext *> selectorWithContext();
    SelectorWithContextContext* selectorWithContext(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorContext* selector();

  class  SelectorWithContextContext : public antlr4::ParserRuleContext {
  public:
    SelectorWithContextContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    ContextSelectorContext *contextSelector();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorWithContextContext* selectorWithContext();

  class  ContextSelectorContext : public antlr4::ParserRuleContext {
  public:
    ContextSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContextSelectorContext* contextSelector();

  class  CssPropertiesContext : public antlr4::ParserRuleContext {
  public:
    CssPropertiesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CssPropertyContext *> cssProperty();
    CssPropertyContext* cssProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssPropertiesContext* cssProperties();

  class  CssPropertyContext : public antlr4::ParserRuleContext {
  public:
    CssPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CssPropertyContext* cssProperty();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentListContext *argumentList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallContext* functionCall();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentListContext* argumentList();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgumentContext* argument();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

