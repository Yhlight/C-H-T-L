
// Generated from Scanner.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  ScannerParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, TEXT = 4, STYLE = 5, SCRIPT = 6, TEMPLATE_START = 7, 
    CUSTOM_START = 8, CONFIG_START = 9, NAMESPACE_START = 10, IMPORT_START = 11, 
    ORIGIN_START = 12, COLON_OR_EQUAL = 13, IDENTIFIER = 14, STRING_LITERAL = 15, 
    UNQUOTED_LITERAL = 16, ATTR_VALUE = 17, ANY_CONTENT = 18, WS = 19, COMMENT = 20, 
    MULTI_COMMENT = 21
  };

  enum {
    RuleDocument = 0, RuleCodeBlock = 1, RuleChtlBlock = 2, RuleChtlElement = 3, 
    RuleElementStart = 4, RuleElementEnd = 5, RuleElementContent = 6, RuleChtlAttribute = 7, 
    RuleChtlDeclaration = 8, RuleChtlStatement = 9, RuleTextBlock = 10, 
    RuleTextContent = 11
  };

  explicit ScannerParser(antlr4::TokenStream *input);

  ScannerParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~ScannerParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class DocumentContext;
  class CodeBlockContext;
  class ChtlBlockContext;
  class ChtlElementContext;
  class ElementStartContext;
  class ElementEndContext;
  class ElementContentContext;
  class ChtlAttributeContext;
  class ChtlDeclarationContext;
  class ChtlStatementContext;
  class TextBlockContext;
  class TextContentContext; 

  class  DocumentContext : public antlr4::ParserRuleContext {
  public:
    DocumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<CodeBlockContext *> codeBlock();
    CodeBlockContext* codeBlock(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DocumentContext* document();

  class  CodeBlockContext : public antlr4::ParserRuleContext {
  public:
    CodeBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlBlockContext *chtlBlock();
    TextBlockContext *textBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CodeBlockContext* codeBlock();

  class  ChtlBlockContext : public antlr4::ParserRuleContext {
  public:
    ChtlBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlElementContext *chtlElement();
    ChtlDeclarationContext *chtlDeclaration();
    ChtlStatementContext *chtlStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChtlBlockContext* chtlBlock();

  class  ChtlElementContext : public antlr4::ParserRuleContext {
  public:
    ChtlElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementStartContext *elementStart();
    ElementEndContext *elementEnd();
    std::vector<ElementContentContext *> elementContent();
    ElementContentContext* elementContent(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChtlElementContext* chtlElement();

  class  ElementStartContext : public antlr4::ParserRuleContext {
  public:
    ElementStartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *TEXT();
    antlr4::tree::TerminalNode *STYLE();
    antlr4::tree::TerminalNode *SCRIPT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementStartContext* elementStart();

  class  ElementEndContext : public antlr4::ParserRuleContext {
  public:
    ElementEndContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementEndContext* elementEnd();

  class  ElementContentContext : public antlr4::ParserRuleContext {
  public:
    ElementContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChtlAttributeContext *chtlAttribute();
    ChtlElementContext *chtlElement();
    TextContentContext *textContent();
    antlr4::tree::TerminalNode *ANY_CONTENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementContentContext* elementContent();

  class  ChtlAttributeContext : public antlr4::ParserRuleContext {
  public:
    ChtlAttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *COLON_OR_EQUAL();
    antlr4::tree::TerminalNode *ATTR_VALUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChtlAttributeContext* chtlAttribute();

  class  ChtlDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ChtlDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEMPLATE_START();
    std::vector<antlr4::tree::TerminalNode *> ANY_CONTENT();
    antlr4::tree::TerminalNode* ANY_CONTENT(size_t i);
    antlr4::tree::TerminalNode *CUSTOM_START();
    antlr4::tree::TerminalNode *CONFIG_START();
    antlr4::tree::TerminalNode *NAMESPACE_START();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChtlDeclarationContext* chtlDeclaration();

  class  ChtlStatementContext : public antlr4::ParserRuleContext {
  public:
    ChtlStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT_START();
    std::vector<antlr4::tree::TerminalNode *> ANY_CONTENT();
    antlr4::tree::TerminalNode* ANY_CONTENT(size_t i);
    antlr4::tree::TerminalNode *ORIGIN_START();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChtlStatementContext* chtlStatement();

  class  TextBlockContext : public antlr4::ParserRuleContext {
  public:
    TextBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TextContentContext *textContent();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextBlockContext* textBlock();

  class  TextContentContext : public antlr4::ParserRuleContext {
  public:
    TextContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *UNQUOTED_LITERAL();
    antlr4::tree::TerminalNode *ANY_CONTENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TextContentContext* textContent();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

