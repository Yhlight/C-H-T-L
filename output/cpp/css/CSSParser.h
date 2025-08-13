
// Generated from CSS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CSSParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, COMMENT = 31, IMPORT = 32, 
    MEDIA = 33, KEYFRAMES = 34, FONT_FACE = 35, SUPPORTS = 36, PAGE = 37, 
    NAMESPACE = 38, CHARSET = 39, VIEWPORT = 40, COUNTER_STYLE = 41, FONT_FEATURE_VALUES = 42, 
    PROPERTY = 43, ONLY = 44, NOT = 45, AND = 46, OR = 47, FROM = 48, TO = 49, 
    IMPORTANT = 50, PX = 51, EM = 52, REM = 53, VH = 54, VW = 55, VMIN = 56, 
    VMAX = 57, CH = 58, EX = 59, CM = 60, MM = 61, IN = 62, PT = 63, PC = 64, 
    DEG = 65, RAD = 66, GRAD = 67, TURN = 68, S = 69, MS = 70, HZ = 71, 
    KHZ = 72, DPI = 73, DPCM = 74, DPPX = 75, VARIABLE = 76, NUMBER = 77, 
    STRING_LITERAL = 78, URI = 79, IDENTIFIER = 80, HEX_DIGIT = 81, WS = 82
  };

  enum {
    RuleStylesheet = 0, RuleStatement = 1, RuleRuleset = 2, RuleSelectorList = 3, 
    RuleSelector = 4, RuleCombinator = 5, RuleSimpleSelector = 6, RuleTypeSelector = 7, 
    RuleUniversalSelector = 8, RuleIdSelector = 9, RuleClassSelector = 10, 
    RuleAttributeSelector = 11, RuleAttributeOperator = 12, RulePseudoSelector = 13, 
    RulePseudoClass = 14, RulePseudoClassArgument = 15, RulePseudoElement = 16, 
    RuleDeclaration = 17, RuleProperty = 18, RuleValue = 19, RuleOperator = 20, 
    RuleTerm = 21, RuleUnaryOperator = 22, RuleNumeric = 23, RulePercentage = 24, 
    RuleLength = 25, RuleAngle = 26, RuleTime = 27, RuleFrequency = 28, 
    RuleResolution = 29, RuleHexcolor = 30, RuleFunction = 31, RuleFunctionArguments = 32, 
    RuleFunctionArgument = 33, RuleCalc = 34, RuleCalcExpression = 35, RuleCalcTerm = 36, 
    RuleCalcFactor = 37, RuleAtRule = 38, RuleAtImport = 39, RuleAtMedia = 40, 
    RuleMediaQueryList = 41, RuleMediaQuery = 42, RuleMediaType = 43, RuleMediaFeature = 44, 
    RuleAtKeyframes = 45, RuleKeyframeBlock = 46, RuleKeyframeSelector = 47, 
    RuleAtFontFace = 48, RuleAtSupports = 49, RuleSupportsCondition = 50, 
    RuleSupportsNegation = 51, RuleSupportsConjunction = 52, RuleSupportsDisjunction = 53, 
    RuleSupportsInParens = 54, RuleSupportsFeature = 55, RuleAtPage = 56, 
    RulePseudoPage = 57, RuleAtNamespace = 58, RuleAtCharset = 59, RuleAtViewport = 60, 
    RuleAtCounterStyle = 61, RuleAtFontFeatureValues = 62, RuleFontFamilyName = 63, 
    RuleFontFeatureValueBlock = 64, RuleAtProperty = 65, RuleExpression = 66, 
    RuleComment = 67
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
  class RulesetContext;
  class SelectorListContext;
  class SelectorContext;
  class CombinatorContext;
  class SimpleSelectorContext;
  class TypeSelectorContext;
  class UniversalSelectorContext;
  class IdSelectorContext;
  class ClassSelectorContext;
  class AttributeSelectorContext;
  class AttributeOperatorContext;
  class PseudoSelectorContext;
  class PseudoClassContext;
  class PseudoClassArgumentContext;
  class PseudoElementContext;
  class DeclarationContext;
  class PropertyContext;
  class ValueContext;
  class OperatorContext;
  class TermContext;
  class UnaryOperatorContext;
  class NumericContext;
  class PercentageContext;
  class LengthContext;
  class AngleContext;
  class TimeContext;
  class FrequencyContext;
  class ResolutionContext;
  class HexcolorContext;
  class FunctionContext;
  class FunctionArgumentsContext;
  class FunctionArgumentContext;
  class CalcContext;
  class CalcExpressionContext;
  class CalcTermContext;
  class CalcFactorContext;
  class AtRuleContext;
  class AtImportContext;
  class AtMediaContext;
  class MediaQueryListContext;
  class MediaQueryContext;
  class MediaTypeContext;
  class MediaFeatureContext;
  class AtKeyframesContext;
  class KeyframeBlockContext;
  class KeyframeSelectorContext;
  class AtFontFaceContext;
  class AtSupportsContext;
  class SupportsConditionContext;
  class SupportsNegationContext;
  class SupportsConjunctionContext;
  class SupportsDisjunctionContext;
  class SupportsInParensContext;
  class SupportsFeatureContext;
  class AtPageContext;
  class PseudoPageContext;
  class AtNamespaceContext;
  class AtCharsetContext;
  class AtViewportContext;
  class AtCounterStyleContext;
  class AtFontFeatureValuesContext;
  class FontFamilyNameContext;
  class FontFeatureValueBlockContext;
  class AtPropertyContext;
  class ExpressionContext;
  class CommentContext; 

  class  StylesheetContext : public antlr4::ParserRuleContext {
  public:
    StylesheetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StylesheetContext* stylesheet();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RulesetContext *ruleset();
    AtRuleContext *atRule();
    CommentContext *comment();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  RulesetContext : public antlr4::ParserRuleContext {
  public:
    RulesetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectorListContext *selectorList();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RulesetContext* ruleset();

  class  SelectorListContext : public antlr4::ParserRuleContext {
  public:
    SelectorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SelectorContext *> selector();
    SelectorContext* selector(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectorContext* selector();

  class  CombinatorContext : public antlr4::ParserRuleContext {
  public:
    CombinatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CombinatorContext* combinator();

  class  SimpleSelectorContext : public antlr4::ParserRuleContext {
  public:
    SimpleSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSelectorContext *typeSelector();
    UniversalSelectorContext *universalSelector();
    std::vector<IdSelectorContext *> idSelector();
    IdSelectorContext* idSelector(size_t i);
    std::vector<ClassSelectorContext *> classSelector();
    ClassSelectorContext* classSelector(size_t i);
    std::vector<AttributeSelectorContext *> attributeSelector();
    AttributeSelectorContext* attributeSelector(size_t i);
    std::vector<PseudoSelectorContext *> pseudoSelector();
    PseudoSelectorContext* pseudoSelector(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SimpleSelectorContext* simpleSelector();

  class  TypeSelectorContext : public antlr4::ParserRuleContext {
  public:
    TypeSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeSelectorContext* typeSelector();

  class  UniversalSelectorContext : public antlr4::ParserRuleContext {
  public:
    UniversalSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UniversalSelectorContext* universalSelector();

  class  IdSelectorContext : public antlr4::ParserRuleContext {
  public:
    IdSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdSelectorContext* idSelector();

  class  ClassSelectorContext : public antlr4::ParserRuleContext {
  public:
    ClassSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClassSelectorContext* classSelector();

  class  AttributeSelectorContext : public antlr4::ParserRuleContext {
  public:
    AttributeSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    AttributeOperatorContext *attributeOperator();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeSelectorContext* attributeSelector();

  class  AttributeOperatorContext : public antlr4::ParserRuleContext {
  public:
    AttributeOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AttributeOperatorContext* attributeOperator();

  class  PseudoSelectorContext : public antlr4::ParserRuleContext {
  public:
    PseudoSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PseudoClassContext *pseudoClass();
    PseudoElementContext *pseudoElement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoSelectorContext* pseudoSelector();

  class  PseudoClassContext : public antlr4::ParserRuleContext {
  public:
    PseudoClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    PseudoClassArgumentContext *pseudoClassArgument();
    antlr4::tree::TerminalNode *NOT();
    SelectorListContext *selectorList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoClassContext* pseudoClass();

  class  PseudoClassArgumentContext : public antlr4::ParserRuleContext {
  public:
    PseudoClassArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoClassArgumentContext* pseudoClassArgument();

  class  PseudoElementContext : public antlr4::ParserRuleContext {
  public:
    PseudoElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoElementContext* pseudoElement();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyContext *property();
    ValueContext *value();
    antlr4::tree::TerminalNode *IMPORTANT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclarationContext* declaration();

  class  PropertyContext : public antlr4::ParserRuleContext {
  public:
    PropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ValueContext* value();

  class  OperatorContext : public antlr4::ParserRuleContext {
  public:
    OperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OperatorContext* operator_();

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    PercentageContext *percentage();
    LengthContext *length();
    AngleContext *angle();
    TimeContext *time();
    FrequencyContext *frequency();
    ResolutionContext *resolution();
    UnaryOperatorContext *unaryOperator();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *URI();
    HexcolorContext *hexcolor();
    FunctionContext *function();
    antlr4::tree::TerminalNode *VARIABLE();
    CalcContext *calc();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TermContext* term();

  class  UnaryOperatorContext : public antlr4::ParserRuleContext {
  public:
    UnaryOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnaryOperatorContext* unaryOperator();

  class  NumericContext : public antlr4::ParserRuleContext {
  public:
    NumericContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericContext* numeric();

  class  PercentageContext : public antlr4::ParserRuleContext {
  public:
    PercentageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PercentageContext* percentage();

  class  LengthContext : public antlr4::ParserRuleContext {
  public:
    LengthContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *PX();
    antlr4::tree::TerminalNode *EM();
    antlr4::tree::TerminalNode *REM();
    antlr4::tree::TerminalNode *VH();
    antlr4::tree::TerminalNode *VW();
    antlr4::tree::TerminalNode *VMIN();
    antlr4::tree::TerminalNode *VMAX();
    antlr4::tree::TerminalNode *CH();
    antlr4::tree::TerminalNode *EX();
    antlr4::tree::TerminalNode *CM();
    antlr4::tree::TerminalNode *MM();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *PT();
    antlr4::tree::TerminalNode *PC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LengthContext* length();

  class  AngleContext : public antlr4::ParserRuleContext {
  public:
    AngleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *DEG();
    antlr4::tree::TerminalNode *RAD();
    antlr4::tree::TerminalNode *GRAD();
    antlr4::tree::TerminalNode *TURN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AngleContext* angle();

  class  TimeContext : public antlr4::ParserRuleContext {
  public:
    TimeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *S();
    antlr4::tree::TerminalNode *MS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TimeContext* time();

  class  FrequencyContext : public antlr4::ParserRuleContext {
  public:
    FrequencyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *HZ();
    antlr4::tree::TerminalNode *KHZ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FrequencyContext* frequency();

  class  ResolutionContext : public antlr4::ParserRuleContext {
  public:
    ResolutionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *DPI();
    antlr4::tree::TerminalNode *DPCM();
    antlr4::tree::TerminalNode *DPPX();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ResolutionContext* resolution();

  class  HexcolorContext : public antlr4::ParserRuleContext {
  public:
    HexcolorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> HEX_DIGIT();
    antlr4::tree::TerminalNode* HEX_DIGIT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HexcolorContext* hexcolor();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    FunctionArgumentsContext *functionArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionContext* function();

  class  FunctionArgumentsContext : public antlr4::ParserRuleContext {
  public:
    FunctionArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionArgumentContext *> functionArgument();
    FunctionArgumentContext* functionArgument(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionArgumentsContext* functionArguments();

  class  FunctionArgumentContext : public antlr4::ParserRuleContext {
  public:
    FunctionArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ValueContext *value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionArgumentContext* functionArgument();

  class  CalcContext : public antlr4::ParserRuleContext {
  public:
    CalcContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CalcExpressionContext *calcExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CalcContext* calc();

  class  CalcExpressionContext : public antlr4::ParserRuleContext {
  public:
    CalcExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CalcTermContext *> calcTerm();
    CalcTermContext* calcTerm(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CalcExpressionContext* calcExpression();

  class  CalcTermContext : public antlr4::ParserRuleContext {
  public:
    CalcTermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CalcFactorContext *> calcFactor();
    CalcFactorContext* calcFactor(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CalcTermContext* calcTerm();

  class  CalcFactorContext : public antlr4::ParserRuleContext {
  public:
    CalcFactorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    LengthContext *length();
    PercentageContext *percentage();
    CalcExpressionContext *calcExpression();
    CalcContext *calc();
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CalcFactorContext* calcFactor();

  class  AtRuleContext : public antlr4::ParserRuleContext {
  public:
    AtRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AtImportContext *atImport();
    AtMediaContext *atMedia();
    AtKeyframesContext *atKeyframes();
    AtFontFaceContext *atFontFace();
    AtSupportsContext *atSupports();
    AtPageContext *atPage();
    AtNamespaceContext *atNamespace();
    AtCharsetContext *atCharset();
    AtViewportContext *atViewport();
    AtCounterStyleContext *atCounterStyle();
    AtFontFeatureValuesContext *atFontFeatureValues();
    AtPropertyContext *atProperty();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtRuleContext* atRule();

  class  AtImportContext : public antlr4::ParserRuleContext {
  public:
    AtImportContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *URI();
    MediaQueryListContext *mediaQueryList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtImportContext* atImport();

  class  AtMediaContext : public antlr4::ParserRuleContext {
  public:
    AtMediaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MEDIA();
    MediaQueryListContext *mediaQueryList();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtMediaContext* atMedia();

  class  MediaQueryListContext : public antlr4::ParserRuleContext {
  public:
    MediaQueryListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MediaQueryContext *> mediaQuery();
    MediaQueryContext* mediaQuery(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MediaQueryListContext* mediaQueryList();

  class  MediaQueryContext : public antlr4::ParserRuleContext {
  public:
    MediaQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MediaTypeContext *mediaType();
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);
    std::vector<MediaFeatureContext *> mediaFeature();
    MediaFeatureContext* mediaFeature(size_t i);
    antlr4::tree::TerminalNode *ONLY();
    antlr4::tree::TerminalNode *NOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MediaQueryContext* mediaQuery();

  class  MediaTypeContext : public antlr4::ParserRuleContext {
  public:
    MediaTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MediaTypeContext* mediaType();

  class  MediaFeatureContext : public antlr4::ParserRuleContext {
  public:
    MediaFeatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ValueContext *value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MediaFeatureContext* mediaFeature();

  class  AtKeyframesContext : public antlr4::ParserRuleContext {
  public:
    AtKeyframesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *KEYFRAMES();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<KeyframeBlockContext *> keyframeBlock();
    KeyframeBlockContext* keyframeBlock(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtKeyframesContext* atKeyframes();

  class  KeyframeBlockContext : public antlr4::ParserRuleContext {
  public:
    KeyframeBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    KeyframeSelectorContext *keyframeSelector();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  KeyframeBlockContext* keyframeBlock();

  class  KeyframeSelectorContext : public antlr4::ParserRuleContext {
  public:
    KeyframeSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    antlr4::tree::TerminalNode *TO();
    PercentageContext *percentage();
    std::vector<KeyframeSelectorContext *> keyframeSelector();
    KeyframeSelectorContext* keyframeSelector(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  KeyframeSelectorContext* keyframeSelector();
  KeyframeSelectorContext* keyframeSelector(int precedence);
  class  AtFontFaceContext : public antlr4::ParserRuleContext {
  public:
    AtFontFaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FONT_FACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtFontFaceContext* atFontFace();

  class  AtSupportsContext : public antlr4::ParserRuleContext {
  public:
    AtSupportsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUPPORTS();
    SupportsConditionContext *supportsCondition();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtSupportsContext* atSupports();

  class  SupportsConditionContext : public antlr4::ParserRuleContext {
  public:
    SupportsConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SupportsNegationContext *supportsNegation();
    SupportsConjunctionContext *supportsConjunction();
    SupportsDisjunctionContext *supportsDisjunction();
    SupportsInParensContext *supportsInParens();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SupportsConditionContext* supportsCondition();

  class  SupportsNegationContext : public antlr4::ParserRuleContext {
  public:
    SupportsNegationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    SupportsInParensContext *supportsInParens();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SupportsNegationContext* supportsNegation();

  class  SupportsConjunctionContext : public antlr4::ParserRuleContext {
  public:
    SupportsConjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SupportsInParensContext *> supportsInParens();
    SupportsInParensContext* supportsInParens(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SupportsConjunctionContext* supportsConjunction();

  class  SupportsDisjunctionContext : public antlr4::ParserRuleContext {
  public:
    SupportsDisjunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SupportsInParensContext *> supportsInParens();
    SupportsInParensContext* supportsInParens(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SupportsDisjunctionContext* supportsDisjunction();

  class  SupportsInParensContext : public antlr4::ParserRuleContext {
  public:
    SupportsInParensContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SupportsConditionContext *supportsCondition();
    SupportsFeatureContext *supportsFeature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SupportsInParensContext* supportsInParens();

  class  SupportsFeatureContext : public antlr4::ParserRuleContext {
  public:
    SupportsFeatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationContext *declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SupportsFeatureContext* supportsFeature();

  class  AtPageContext : public antlr4::ParserRuleContext {
  public:
    AtPageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PAGE();
    PseudoPageContext *pseudoPage();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtPageContext* atPage();

  class  PseudoPageContext : public antlr4::ParserRuleContext {
  public:
    PseudoPageContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PseudoPageContext* pseudoPage();

  class  AtNamespaceContext : public antlr4::ParserRuleContext {
  public:
    AtNamespaceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMESPACE();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *URI();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtNamespaceContext* atNamespace();

  class  AtCharsetContext : public antlr4::ParserRuleContext {
  public:
    AtCharsetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHARSET();
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtCharsetContext* atCharset();

  class  AtViewportContext : public antlr4::ParserRuleContext {
  public:
    AtViewportContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VIEWPORT();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtViewportContext* atViewport();

  class  AtCounterStyleContext : public antlr4::ParserRuleContext {
  public:
    AtCounterStyleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COUNTER_STYLE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtCounterStyleContext* atCounterStyle();

  class  AtFontFeatureValuesContext : public antlr4::ParserRuleContext {
  public:
    AtFontFeatureValuesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FONT_FEATURE_VALUES();
    std::vector<FontFamilyNameContext *> fontFamilyName();
    FontFamilyNameContext* fontFamilyName(size_t i);
    std::vector<FontFeatureValueBlockContext *> fontFeatureValueBlock();
    FontFeatureValueBlockContext* fontFeatureValueBlock(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtFontFeatureValuesContext* atFontFeatureValues();

  class  FontFamilyNameContext : public antlr4::ParserRuleContext {
  public:
    FontFamilyNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FontFamilyNameContext* fontFamilyName();

  class  FontFeatureValueBlockContext : public antlr4::ParserRuleContext {
  public:
    FontFeatureValueBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FontFeatureValueBlockContext* fontFeatureValueBlock();

  class  AtPropertyContext : public antlr4::ParserRuleContext {
  public:
    AtPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PROPERTY();
    antlr4::tree::TerminalNode *VARIABLE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtPropertyContext* atProperty();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    std::vector<OperatorContext *> operator_();
    OperatorContext* operator_(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class  CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMMENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CommentContext* comment();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool keyframeSelectorSempred(KeyframeSelectorContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

