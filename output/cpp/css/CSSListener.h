
// Generated from CSS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CSSParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CSSParser.
 */
class  CSSListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStylesheet(CSSParser::StylesheetContext *ctx) = 0;
  virtual void exitStylesheet(CSSParser::StylesheetContext *ctx) = 0;

  virtual void enterStatement(CSSParser::StatementContext *ctx) = 0;
  virtual void exitStatement(CSSParser::StatementContext *ctx) = 0;

  virtual void enterRuleset(CSSParser::RulesetContext *ctx) = 0;
  virtual void exitRuleset(CSSParser::RulesetContext *ctx) = 0;

  virtual void enterSelectorList(CSSParser::SelectorListContext *ctx) = 0;
  virtual void exitSelectorList(CSSParser::SelectorListContext *ctx) = 0;

  virtual void enterSelector(CSSParser::SelectorContext *ctx) = 0;
  virtual void exitSelector(CSSParser::SelectorContext *ctx) = 0;

  virtual void enterCombinator(CSSParser::CombinatorContext *ctx) = 0;
  virtual void exitCombinator(CSSParser::CombinatorContext *ctx) = 0;

  virtual void enterSimpleSelector(CSSParser::SimpleSelectorContext *ctx) = 0;
  virtual void exitSimpleSelector(CSSParser::SimpleSelectorContext *ctx) = 0;

  virtual void enterTypeSelector(CSSParser::TypeSelectorContext *ctx) = 0;
  virtual void exitTypeSelector(CSSParser::TypeSelectorContext *ctx) = 0;

  virtual void enterUniversalSelector(CSSParser::UniversalSelectorContext *ctx) = 0;
  virtual void exitUniversalSelector(CSSParser::UniversalSelectorContext *ctx) = 0;

  virtual void enterIdSelector(CSSParser::IdSelectorContext *ctx) = 0;
  virtual void exitIdSelector(CSSParser::IdSelectorContext *ctx) = 0;

  virtual void enterClassSelector(CSSParser::ClassSelectorContext *ctx) = 0;
  virtual void exitClassSelector(CSSParser::ClassSelectorContext *ctx) = 0;

  virtual void enterAttributeSelector(CSSParser::AttributeSelectorContext *ctx) = 0;
  virtual void exitAttributeSelector(CSSParser::AttributeSelectorContext *ctx) = 0;

  virtual void enterAttributeOperator(CSSParser::AttributeOperatorContext *ctx) = 0;
  virtual void exitAttributeOperator(CSSParser::AttributeOperatorContext *ctx) = 0;

  virtual void enterPseudoSelector(CSSParser::PseudoSelectorContext *ctx) = 0;
  virtual void exitPseudoSelector(CSSParser::PseudoSelectorContext *ctx) = 0;

  virtual void enterPseudoClass(CSSParser::PseudoClassContext *ctx) = 0;
  virtual void exitPseudoClass(CSSParser::PseudoClassContext *ctx) = 0;

  virtual void enterPseudoClassArgument(CSSParser::PseudoClassArgumentContext *ctx) = 0;
  virtual void exitPseudoClassArgument(CSSParser::PseudoClassArgumentContext *ctx) = 0;

  virtual void enterPseudoElement(CSSParser::PseudoElementContext *ctx) = 0;
  virtual void exitPseudoElement(CSSParser::PseudoElementContext *ctx) = 0;

  virtual void enterDeclaration(CSSParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(CSSParser::DeclarationContext *ctx) = 0;

  virtual void enterProperty(CSSParser::PropertyContext *ctx) = 0;
  virtual void exitProperty(CSSParser::PropertyContext *ctx) = 0;

  virtual void enterValue(CSSParser::ValueContext *ctx) = 0;
  virtual void exitValue(CSSParser::ValueContext *ctx) = 0;

  virtual void enterOperator(CSSParser::OperatorContext *ctx) = 0;
  virtual void exitOperator(CSSParser::OperatorContext *ctx) = 0;

  virtual void enterTerm(CSSParser::TermContext *ctx) = 0;
  virtual void exitTerm(CSSParser::TermContext *ctx) = 0;

  virtual void enterUnaryOperator(CSSParser::UnaryOperatorContext *ctx) = 0;
  virtual void exitUnaryOperator(CSSParser::UnaryOperatorContext *ctx) = 0;

  virtual void enterNumeric(CSSParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(CSSParser::NumericContext *ctx) = 0;

  virtual void enterPercentage(CSSParser::PercentageContext *ctx) = 0;
  virtual void exitPercentage(CSSParser::PercentageContext *ctx) = 0;

  virtual void enterLength(CSSParser::LengthContext *ctx) = 0;
  virtual void exitLength(CSSParser::LengthContext *ctx) = 0;

  virtual void enterAngle(CSSParser::AngleContext *ctx) = 0;
  virtual void exitAngle(CSSParser::AngleContext *ctx) = 0;

  virtual void enterTime(CSSParser::TimeContext *ctx) = 0;
  virtual void exitTime(CSSParser::TimeContext *ctx) = 0;

  virtual void enterFrequency(CSSParser::FrequencyContext *ctx) = 0;
  virtual void exitFrequency(CSSParser::FrequencyContext *ctx) = 0;

  virtual void enterResolution(CSSParser::ResolutionContext *ctx) = 0;
  virtual void exitResolution(CSSParser::ResolutionContext *ctx) = 0;

  virtual void enterHexcolor(CSSParser::HexcolorContext *ctx) = 0;
  virtual void exitHexcolor(CSSParser::HexcolorContext *ctx) = 0;

  virtual void enterFunction(CSSParser::FunctionContext *ctx) = 0;
  virtual void exitFunction(CSSParser::FunctionContext *ctx) = 0;

  virtual void enterFunctionArguments(CSSParser::FunctionArgumentsContext *ctx) = 0;
  virtual void exitFunctionArguments(CSSParser::FunctionArgumentsContext *ctx) = 0;

  virtual void enterFunctionArgument(CSSParser::FunctionArgumentContext *ctx) = 0;
  virtual void exitFunctionArgument(CSSParser::FunctionArgumentContext *ctx) = 0;

  virtual void enterCalc(CSSParser::CalcContext *ctx) = 0;
  virtual void exitCalc(CSSParser::CalcContext *ctx) = 0;

  virtual void enterCalcExpression(CSSParser::CalcExpressionContext *ctx) = 0;
  virtual void exitCalcExpression(CSSParser::CalcExpressionContext *ctx) = 0;

  virtual void enterCalcTerm(CSSParser::CalcTermContext *ctx) = 0;
  virtual void exitCalcTerm(CSSParser::CalcTermContext *ctx) = 0;

  virtual void enterCalcFactor(CSSParser::CalcFactorContext *ctx) = 0;
  virtual void exitCalcFactor(CSSParser::CalcFactorContext *ctx) = 0;

  virtual void enterAtRule(CSSParser::AtRuleContext *ctx) = 0;
  virtual void exitAtRule(CSSParser::AtRuleContext *ctx) = 0;

  virtual void enterAtImport(CSSParser::AtImportContext *ctx) = 0;
  virtual void exitAtImport(CSSParser::AtImportContext *ctx) = 0;

  virtual void enterAtMedia(CSSParser::AtMediaContext *ctx) = 0;
  virtual void exitAtMedia(CSSParser::AtMediaContext *ctx) = 0;

  virtual void enterMediaQueryList(CSSParser::MediaQueryListContext *ctx) = 0;
  virtual void exitMediaQueryList(CSSParser::MediaQueryListContext *ctx) = 0;

  virtual void enterMediaQuery(CSSParser::MediaQueryContext *ctx) = 0;
  virtual void exitMediaQuery(CSSParser::MediaQueryContext *ctx) = 0;

  virtual void enterMediaType(CSSParser::MediaTypeContext *ctx) = 0;
  virtual void exitMediaType(CSSParser::MediaTypeContext *ctx) = 0;

  virtual void enterMediaFeature(CSSParser::MediaFeatureContext *ctx) = 0;
  virtual void exitMediaFeature(CSSParser::MediaFeatureContext *ctx) = 0;

  virtual void enterAtKeyframes(CSSParser::AtKeyframesContext *ctx) = 0;
  virtual void exitAtKeyframes(CSSParser::AtKeyframesContext *ctx) = 0;

  virtual void enterKeyframeBlock(CSSParser::KeyframeBlockContext *ctx) = 0;
  virtual void exitKeyframeBlock(CSSParser::KeyframeBlockContext *ctx) = 0;

  virtual void enterKeyframeSelector(CSSParser::KeyframeSelectorContext *ctx) = 0;
  virtual void exitKeyframeSelector(CSSParser::KeyframeSelectorContext *ctx) = 0;

  virtual void enterAtFontFace(CSSParser::AtFontFaceContext *ctx) = 0;
  virtual void exitAtFontFace(CSSParser::AtFontFaceContext *ctx) = 0;

  virtual void enterAtSupports(CSSParser::AtSupportsContext *ctx) = 0;
  virtual void exitAtSupports(CSSParser::AtSupportsContext *ctx) = 0;

  virtual void enterSupportsCondition(CSSParser::SupportsConditionContext *ctx) = 0;
  virtual void exitSupportsCondition(CSSParser::SupportsConditionContext *ctx) = 0;

  virtual void enterSupportsNegation(CSSParser::SupportsNegationContext *ctx) = 0;
  virtual void exitSupportsNegation(CSSParser::SupportsNegationContext *ctx) = 0;

  virtual void enterSupportsConjunction(CSSParser::SupportsConjunctionContext *ctx) = 0;
  virtual void exitSupportsConjunction(CSSParser::SupportsConjunctionContext *ctx) = 0;

  virtual void enterSupportsDisjunction(CSSParser::SupportsDisjunctionContext *ctx) = 0;
  virtual void exitSupportsDisjunction(CSSParser::SupportsDisjunctionContext *ctx) = 0;

  virtual void enterSupportsInParens(CSSParser::SupportsInParensContext *ctx) = 0;
  virtual void exitSupportsInParens(CSSParser::SupportsInParensContext *ctx) = 0;

  virtual void enterSupportsFeature(CSSParser::SupportsFeatureContext *ctx) = 0;
  virtual void exitSupportsFeature(CSSParser::SupportsFeatureContext *ctx) = 0;

  virtual void enterAtPage(CSSParser::AtPageContext *ctx) = 0;
  virtual void exitAtPage(CSSParser::AtPageContext *ctx) = 0;

  virtual void enterPseudoPage(CSSParser::PseudoPageContext *ctx) = 0;
  virtual void exitPseudoPage(CSSParser::PseudoPageContext *ctx) = 0;

  virtual void enterAtNamespace(CSSParser::AtNamespaceContext *ctx) = 0;
  virtual void exitAtNamespace(CSSParser::AtNamespaceContext *ctx) = 0;

  virtual void enterAtCharset(CSSParser::AtCharsetContext *ctx) = 0;
  virtual void exitAtCharset(CSSParser::AtCharsetContext *ctx) = 0;

  virtual void enterAtViewport(CSSParser::AtViewportContext *ctx) = 0;
  virtual void exitAtViewport(CSSParser::AtViewportContext *ctx) = 0;

  virtual void enterAtCounterStyle(CSSParser::AtCounterStyleContext *ctx) = 0;
  virtual void exitAtCounterStyle(CSSParser::AtCounterStyleContext *ctx) = 0;

  virtual void enterAtFontFeatureValues(CSSParser::AtFontFeatureValuesContext *ctx) = 0;
  virtual void exitAtFontFeatureValues(CSSParser::AtFontFeatureValuesContext *ctx) = 0;

  virtual void enterFontFamilyName(CSSParser::FontFamilyNameContext *ctx) = 0;
  virtual void exitFontFamilyName(CSSParser::FontFamilyNameContext *ctx) = 0;

  virtual void enterFontFeatureValueBlock(CSSParser::FontFeatureValueBlockContext *ctx) = 0;
  virtual void exitFontFeatureValueBlock(CSSParser::FontFeatureValueBlockContext *ctx) = 0;

  virtual void enterAtProperty(CSSParser::AtPropertyContext *ctx) = 0;
  virtual void exitAtProperty(CSSParser::AtPropertyContext *ctx) = 0;

  virtual void enterExpression(CSSParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(CSSParser::ExpressionContext *ctx) = 0;

  virtual void enterComment(CSSParser::CommentContext *ctx) = 0;
  virtual void exitComment(CSSParser::CommentContext *ctx) = 0;


};

