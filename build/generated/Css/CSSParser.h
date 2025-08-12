
// Generated from /workspace/grammar/CSS.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"




class  CSSParser : public antlr4::Parser {
public:
  enum {
    CHARSET = 1, IMPORT = 2, NAMESPACE = 3, MEDIA = 4, PAGE = 5, FONT_FACE = 6, 
    KEYFRAMES = 7, SUPPORTS = 8, ONLY = 9, NOT = 10, AND = 11, OR = 12, 
    FROM = 13, TO = 14, IMPORTANT = 15, LPAREN = 16, RPAREN = 17, LBRACE = 18, 
    RBRACE = 19, LBRACKET = 20, RBRACKET = 21, COLON = 22, SEMICOLON = 23, 
    COMMA = 24, DOT = 25, HASH = 26, PLUS = 27, MINUS = 28, GREATER = 29, 
    TILDE = 30, STAR = 31, PIPE = 32, SLASH = 33, EQUALS = 34, INCLUDES = 35, 
    DASHMATCH = 36, PREFIXMATCH = 37, SUFFIXMATCH = 38, SUBSTRINGMATCH = 39, 
    LENGTH = 40, EMS = 41, EXS = 42, ANGLE = 43, TIME = 44, FREQ = 45, PERCENTAGE = 46, 
    FUNCTION = 47, URL = 48, NUMBER = 49, STRING = 50, IDENT = 51, HEXDIGIT = 52, 
    COMMENT = 53, SPACE = 54, ANY = 55
  };

  enum {
    RuleStylesheet = 0, RuleStatement = 1, RuleCharsetRule = 2, RuleImportRule = 3, 
    RuleNamespaceRule = 4, RuleMedia = 5, RuleMediaQueryList = 6, RuleMediaQuery = 7, 
    RuleMediaType = 8, RuleMediaExpression = 9, RuleMediaFeature = 10, RulePage = 11, 
    RulePseudoPage = 12, RuleFontFace = 13, RuleKeyframes = 14, RuleKeyframeRule = 15, 
    RuleKeyframeSelector = 16, RuleSupports = 17, RuleSupportsCondition = 18, 
    RuleSupportsNegation = 19, RuleSupportsConjunction = 20, RuleSupportsDisjunction = 21, 
    RuleSupportsConditionInParens = 22, RuleSupportsDeclarationCondition = 23, 
    RuleGeneralEnclosed = 24, RuleRuleset = 25, RuleSelectorList = 26, RuleSelector = 27, 
    RuleCombinator = 28, RuleSimpleSelector = 29, RuleTypeSelector = 30, 
    RuleTypeNamespacePrefix = 31, RuleElementName = 32, RuleUniversal = 33, 
    RuleIdSelector = 34, RuleClassSelector = 35, RuleAttributeSelector = 36, 
    RuleAttributeOperator = 37, RulePseudoClass = 38, RuleFunctionalPseudoClass = 39, 
    RulePseudoElement = 40, RuleDeclaration = 41, RuleProperty = 42, RuleValue = 43, 
    RuleTerm = 44, RuleFunction = 45, RuleHexcolor = 46, RuleUrl = 47, RuleOperator = 48, 
    RuleImportant = 49, RuleNestedStatement = 50
  };

  explicit CSSParser(antlr4::TokenStream *input);

  CSSParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CSSParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class StylesheetContext;
  class StatementContext;
  class CharsetRuleContext;
  class ImportRuleContext;
  class NamespaceRuleContext;
  class MediaContext;
  class MediaQueryListContext;
  class MediaQueryContext;
  class MediaTypeContext;
  class MediaExpressionContext;
  class MediaFeatureContext;
  class PageContext;
  class PseudoPageContext;
  class FontFaceContext;
  class KeyframesContext;
  class KeyframeRuleContext;
  class KeyframeSelectorContext;
  class SupportsContext;
  class SupportsConditionContext;
  class SupportsNegationContext;
  class SupportsConjunctionContext;
  class SupportsDisjunctionContext;
  class SupportsConditionInParensContext;
  class SupportsDeclarationConditionContext;
  class GeneralEnclosedContext;
  class RulesetContext;
  class SelectorListContext;
  class SelectorContext;
  class CombinatorContext;
  class SimpleSelectorContext;
  class TypeSelectorContext;
  class TypeNamespacePrefixContext;
  class ElementNameContext;
  class UniversalContext;
  class IdSelectorContext;
  class ClassSelectorContext;
  class AttributeSelectorContext;
  class AttributeOperatorContext;
  class PseudoClassContext;
  class FunctionalPseudoClassContext;
  class PseudoElementContext;
  class DeclarationContext;
  class PropertyContext;
  class ValueContext;
  class TermContext;
  class FunctionContext;
  class HexcolorContext;
  class UrlContext;
  class OperatorContext;
  class ImportantContext;
  class NestedStatementContext; 

  class  StylesheetContext : public antlr4::ParserRuleContext {
  public:
    StylesheetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StylesheetContext* stylesheet();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RulesetContext *ruleset();
    MediaContext *media();
    PageContext *page();
    FontFaceContext *fontFace();
    KeyframesContext *keyframes();
    SupportsContext *supports();
    ImportRuleContext *importRule();
    NamespaceRuleContext *namespaceRule();
    CharsetRuleContext *charsetRule();
    NestedStatementContext *nestedStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  CharsetRuleContext : public antlr4::ParserRuleContext {
  public:
    CharsetRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHARSET();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CharsetRuleContext* charsetRule();

  class  ImportRuleContext : public antlr4::ParserRuleContext {
  public:
    ImportRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *STRING();
    UrlContext *url();
    MediaQueryListContext *mediaQueryList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportRuleContext* importRule();

  class  NamespaceRuleContext : public antlr4::ParserRuleContext {
  public:
    NamespaceRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMESPACE();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *STRING();
    UrlContext *url();
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceRuleContext* namespaceRule();

  class  MediaContext : public antlr4::ParserRuleContext {
  public:
    MediaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MEDIA();
    MediaQueryListContext *mediaQueryList();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<RulesetContext *> ruleset();
    RulesetContext* ruleset(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MediaContext* media();

  class  MediaQueryListContext : public antlr4::ParserRuleContext {
  public:
    MediaQueryListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MediaQueryContext *> mediaQuery();
    MediaQueryContext* mediaQuery(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MediaQueryListContext* mediaQueryList();

  class  MediaQueryContext : public antlr4::ParserRuleContext {
  public:
    MediaQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MediaTypeContext *mediaType();
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);
    std::vector<MediaExpressionContext *> mediaExpression();
    MediaExpressionContext* mediaExpression(size_t i);
    antlr4::tree::TerminalNode *ONLY();
    antlr4::tree::TerminalNode *NOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MediaQueryContext* mediaQuery();

  class  MediaTypeContext : public antlr4::ParserRuleContext {
  public:
    MediaTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MediaTypeContext* mediaType();

  class  MediaExpressionContext : public antlr4::ParserRuleContext {
  public:
    MediaExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    MediaFeatureContext *mediaFeature();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *COLON();
    ValueContext *value();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MediaExpressionContext* mediaExpression();

  class  MediaFeatureContext : public antlr4::ParserRuleContext {
  public:
    MediaFeatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MediaFeatureContext* mediaFeature();

  class  PageContext : public antlr4::ParserRuleContext {
  public:
    PageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PAGE();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    PseudoPageContext *pseudoPage();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PageContext* page();

  class  PseudoPageContext : public antlr4::ParserRuleContext {
  public:
    PseudoPageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PseudoPageContext* pseudoPage();

  class  FontFaceContext : public antlr4::ParserRuleContext {
  public:
    FontFaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FONT_FACE();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FontFaceContext* fontFace();

  class  KeyframesContext : public antlr4::ParserRuleContext {
  public:
    KeyframesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYFRAMES();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<KeyframeRuleContext *> keyframeRule();
    KeyframeRuleContext* keyframeRule(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyframesContext* keyframes();

  class  KeyframeRuleContext : public antlr4::ParserRuleContext {
  public:
    KeyframeRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    KeyframeSelectorContext *keyframeSelector();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyframeRuleContext* keyframeRule();

  class  KeyframeSelectorContext : public antlr4::ParserRuleContext {
  public:
    KeyframeSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> FROM();
    antlr4::tree::TerminalNode* FROM(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TO();
    antlr4::tree::TerminalNode* TO(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PERCENTAGE();
    antlr4::tree::TerminalNode* PERCENTAGE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyframeSelectorContext* keyframeSelector();

  class  SupportsContext : public antlr4::ParserRuleContext {
  public:
    SupportsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUPPORTS();
    SupportsConditionContext *supportsCondition();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<RulesetContext *> ruleset();
    RulesetContext* ruleset(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupportsContext* supports();

  class  SupportsConditionContext : public antlr4::ParserRuleContext {
  public:
    SupportsConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SupportsNegationContext *supportsNegation();
    SupportsConjunctionContext *supportsConjunction();
    SupportsDisjunctionContext *supportsDisjunction();
    SupportsConditionInParensContext *supportsConditionInParens();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupportsConditionContext* supportsCondition();

  class  SupportsNegationContext : public antlr4::ParserRuleContext {
  public:
    SupportsNegationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *SPACE();
    SupportsConditionInParensContext *supportsConditionInParens();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupportsNegationContext* supportsNegation();

  class  SupportsConjunctionContext : public antlr4::ParserRuleContext {
  public:
    SupportsConjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SupportsConditionInParensContext *> supportsConditionInParens();
    SupportsConditionInParensContext* supportsConditionInParens(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupportsConjunctionContext* supportsConjunction();

  class  SupportsDisjunctionContext : public antlr4::ParserRuleContext {
  public:
    SupportsDisjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SupportsConditionInParensContext *> supportsConditionInParens();
    SupportsConditionInParensContext* supportsConditionInParens(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SPACE();
    antlr4::tree::TerminalNode* SPACE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupportsDisjunctionContext* supportsDisjunction();

  class  SupportsConditionInParensContext : public antlr4::ParserRuleContext {
  public:
    SupportsConditionInParensContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    SupportsConditionContext *supportsCondition();
    antlr4::tree::TerminalNode *RPAREN();
    SupportsDeclarationConditionContext *supportsDeclarationCondition();
    GeneralEnclosedContext *generalEnclosed();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupportsConditionInParensContext* supportsConditionInParens();

  class  SupportsDeclarationConditionContext : public antlr4::ParserRuleContext {
  public:
    SupportsDeclarationConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupportsDeclarationConditionContext* supportsDeclarationCondition();

  class  GeneralEnclosedContext : public antlr4::ParserRuleContext {
  public:
    GeneralEnclosedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> RPAREN();
    antlr4::tree::TerminalNode* RPAREN(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GeneralEnclosedContext* generalEnclosed();

  class  RulesetContext : public antlr4::ParserRuleContext {
  public:
    RulesetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorListContext *selectorList();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RulesetContext* ruleset();

  class  SelectorListContext : public antlr4::ParserRuleContext {
  public:
    SelectorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SelectorContext *> selector();
    SelectorContext* selector(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectorListContext* selectorList();

  class  SelectorContext : public antlr4::ParserRuleContext {
  public:
    SelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimpleSelectorContext *> simpleSelector();
    SimpleSelectorContext* simpleSelector(size_t i);
    std::vector<CombinatorContext *> combinator();
    CombinatorContext* combinator(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectorContext* selector();

  class  CombinatorContext : public antlr4::ParserRuleContext {
  public:
    CombinatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *TILDE();
    antlr4::tree::TerminalNode *SPACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CombinatorContext* combinator();

  class  SimpleSelectorContext : public antlr4::ParserRuleContext {
  public:
    SimpleSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSelectorContext *typeSelector();
    UniversalContext *universal();
    std::vector<IdSelectorContext *> idSelector();
    IdSelectorContext* idSelector(size_t i);
    std::vector<ClassSelectorContext *> classSelector();
    ClassSelectorContext* classSelector(size_t i);
    std::vector<AttributeSelectorContext *> attributeSelector();
    AttributeSelectorContext* attributeSelector(size_t i);
    std::vector<PseudoClassContext *> pseudoClass();
    PseudoClassContext* pseudoClass(size_t i);
    std::vector<PseudoElementContext *> pseudoElement();
    PseudoElementContext* pseudoElement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleSelectorContext* simpleSelector();

  class  TypeSelectorContext : public antlr4::ParserRuleContext {
  public:
    TypeSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementNameContext *elementName();
    TypeNamespacePrefixContext *typeNamespacePrefix();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeSelectorContext* typeSelector();

  class  TypeNamespacePrefixContext : public antlr4::ParserRuleContext {
  public:
    TypeNamespacePrefixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PIPE();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *STAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNamespacePrefixContext* typeNamespacePrefix();

  class  ElementNameContext : public antlr4::ParserRuleContext {
  public:
    ElementNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementNameContext* elementName();

  class  UniversalContext : public antlr4::ParserRuleContext {
  public:
    UniversalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    TypeNamespacePrefixContext *typeNamespacePrefix();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UniversalContext* universal();

  class  IdSelectorContext : public antlr4::ParserRuleContext {
  public:
    IdSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HASH();
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdSelectorContext* idSelector();

  class  ClassSelectorContext : public antlr4::ParserRuleContext {
  public:
    ClassSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassSelectorContext* classSelector();

  class  AttributeSelectorContext : public antlr4::ParserRuleContext {
  public:
    AttributeSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    std::vector<antlr4::tree::TerminalNode *> IDENT();
    antlr4::tree::TerminalNode* IDENT(size_t i);
    antlr4::tree::TerminalNode *RBRACKET();
    AttributeOperatorContext *attributeOperator();
    antlr4::tree::TerminalNode *STRING();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeSelectorContext* attributeSelector();

  class  AttributeOperatorContext : public antlr4::ParserRuleContext {
  public:
    AttributeOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *INCLUDES();
    antlr4::tree::TerminalNode *DASHMATCH();
    antlr4::tree::TerminalNode *PREFIXMATCH();
    antlr4::tree::TerminalNode *SUFFIXMATCH();
    antlr4::tree::TerminalNode *SUBSTRINGMATCH();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeOperatorContext* attributeOperator();

  class  PseudoClassContext : public antlr4::ParserRuleContext {
  public:
    PseudoClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    antlr4::tree::TerminalNode *IDENT();
    FunctionalPseudoClassContext *functionalPseudoClass();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PseudoClassContext* pseudoClass();

  class  FunctionalPseudoClassContext : public antlr4::ParserRuleContext {
  public:
    FunctionalPseudoClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *RPAREN();
    SelectorListContext *selectorList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionalPseudoClassContext* functionalPseudoClass();

  class  PseudoElementContext : public antlr4::ParserRuleContext {
  public:
    PseudoElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    antlr4::tree::TerminalNode *IDENT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PseudoElementContext* pseudoElement();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyContext *property();
    antlr4::tree::TerminalNode *COLON();
    ValueContext *value();
    antlr4::tree::TerminalNode *IMPORTANT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  PropertyContext : public antlr4::ParserRuleContext {
  public:
    PropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENT();
    antlr4::tree::TerminalNode* IDENT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyContext* property();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    std::vector<OperatorContext *> operator_();
    OperatorContext* operator_(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueContext* value();

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *PERCENTAGE();
    antlr4::tree::TerminalNode *LENGTH();
    antlr4::tree::TerminalNode *EMS();
    antlr4::tree::TerminalNode *EXS();
    antlr4::tree::TerminalNode *ANGLE();
    antlr4::tree::TerminalNode *TIME();
    antlr4::tree::TerminalNode *FREQ();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *IDENT();
    UrlContext *url();
    HexcolorContext *hexcolor();
    FunctionContext *function();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TermContext* term();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionContext* function();

  class  HexcolorContext : public antlr4::ParserRuleContext {
  public:
    HexcolorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HASH();
    std::vector<antlr4::tree::TerminalNode *> HEXDIGIT();
    antlr4::tree::TerminalNode* HEXDIGIT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HexcolorContext* hexcolor();

  class  UrlContext : public antlr4::ParserRuleContext {
  public:
    UrlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *URL();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UrlContext* url();

  class  OperatorContext : public antlr4::ParserRuleContext {
  public:
    OperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *SPACE();
    antlr4::tree::TerminalNode *SLASH();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperatorContext* operator_();

  class  ImportantContext : public antlr4::ParserRuleContext {
  public:
    ImportantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORTANT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportantContext* important();

  class  NestedStatementContext : public antlr4::ParserRuleContext {
  public:
    NestedStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NestedStatementContext* nestedStatement();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

