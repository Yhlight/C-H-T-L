
// Generated from CSS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CSSListener.h"


/**
 * This class provides an empty implementation of CSSListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CSSBaseListener : public CSSListener {
public:

  virtual void enterStylesheet(CSSParser::StylesheetContext * /*ctx*/) override { }
  virtual void exitStylesheet(CSSParser::StylesheetContext * /*ctx*/) override { }

  virtual void enterStatement(CSSParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(CSSParser::StatementContext * /*ctx*/) override { }

  virtual void enterRuleset(CSSParser::RulesetContext * /*ctx*/) override { }
  virtual void exitRuleset(CSSParser::RulesetContext * /*ctx*/) override { }

  virtual void enterSelectorList(CSSParser::SelectorListContext * /*ctx*/) override { }
  virtual void exitSelectorList(CSSParser::SelectorListContext * /*ctx*/) override { }

  virtual void enterSelector(CSSParser::SelectorContext * /*ctx*/) override { }
  virtual void exitSelector(CSSParser::SelectorContext * /*ctx*/) override { }

  virtual void enterCombinator(CSSParser::CombinatorContext * /*ctx*/) override { }
  virtual void exitCombinator(CSSParser::CombinatorContext * /*ctx*/) override { }

  virtual void enterSimpleSelector(CSSParser::SimpleSelectorContext * /*ctx*/) override { }
  virtual void exitSimpleSelector(CSSParser::SimpleSelectorContext * /*ctx*/) override { }

  virtual void enterTypeSelector(CSSParser::TypeSelectorContext * /*ctx*/) override { }
  virtual void exitTypeSelector(CSSParser::TypeSelectorContext * /*ctx*/) override { }

  virtual void enterUniversalSelector(CSSParser::UniversalSelectorContext * /*ctx*/) override { }
  virtual void exitUniversalSelector(CSSParser::UniversalSelectorContext * /*ctx*/) override { }

  virtual void enterIdSelector(CSSParser::IdSelectorContext * /*ctx*/) override { }
  virtual void exitIdSelector(CSSParser::IdSelectorContext * /*ctx*/) override { }

  virtual void enterClassSelector(CSSParser::ClassSelectorContext * /*ctx*/) override { }
  virtual void exitClassSelector(CSSParser::ClassSelectorContext * /*ctx*/) override { }

  virtual void enterAttributeSelector(CSSParser::AttributeSelectorContext * /*ctx*/) override { }
  virtual void exitAttributeSelector(CSSParser::AttributeSelectorContext * /*ctx*/) override { }

  virtual void enterAttributeOperator(CSSParser::AttributeOperatorContext * /*ctx*/) override { }
  virtual void exitAttributeOperator(CSSParser::AttributeOperatorContext * /*ctx*/) override { }

  virtual void enterPseudoSelector(CSSParser::PseudoSelectorContext * /*ctx*/) override { }
  virtual void exitPseudoSelector(CSSParser::PseudoSelectorContext * /*ctx*/) override { }

  virtual void enterPseudoClass(CSSParser::PseudoClassContext * /*ctx*/) override { }
  virtual void exitPseudoClass(CSSParser::PseudoClassContext * /*ctx*/) override { }

  virtual void enterPseudoClassArgument(CSSParser::PseudoClassArgumentContext * /*ctx*/) override { }
  virtual void exitPseudoClassArgument(CSSParser::PseudoClassArgumentContext * /*ctx*/) override { }

  virtual void enterPseudoElement(CSSParser::PseudoElementContext * /*ctx*/) override { }
  virtual void exitPseudoElement(CSSParser::PseudoElementContext * /*ctx*/) override { }

  virtual void enterDeclaration(CSSParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(CSSParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterProperty(CSSParser::PropertyContext * /*ctx*/) override { }
  virtual void exitProperty(CSSParser::PropertyContext * /*ctx*/) override { }

  virtual void enterValue(CSSParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(CSSParser::ValueContext * /*ctx*/) override { }

  virtual void enterOperator(CSSParser::OperatorContext * /*ctx*/) override { }
  virtual void exitOperator(CSSParser::OperatorContext * /*ctx*/) override { }

  virtual void enterTerm(CSSParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(CSSParser::TermContext * /*ctx*/) override { }

  virtual void enterUnaryOperator(CSSParser::UnaryOperatorContext * /*ctx*/) override { }
  virtual void exitUnaryOperator(CSSParser::UnaryOperatorContext * /*ctx*/) override { }

  virtual void enterNumeric(CSSParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(CSSParser::NumericContext * /*ctx*/) override { }

  virtual void enterPercentage(CSSParser::PercentageContext * /*ctx*/) override { }
  virtual void exitPercentage(CSSParser::PercentageContext * /*ctx*/) override { }

  virtual void enterLength(CSSParser::LengthContext * /*ctx*/) override { }
  virtual void exitLength(CSSParser::LengthContext * /*ctx*/) override { }

  virtual void enterAngle(CSSParser::AngleContext * /*ctx*/) override { }
  virtual void exitAngle(CSSParser::AngleContext * /*ctx*/) override { }

  virtual void enterTime(CSSParser::TimeContext * /*ctx*/) override { }
  virtual void exitTime(CSSParser::TimeContext * /*ctx*/) override { }

  virtual void enterFrequency(CSSParser::FrequencyContext * /*ctx*/) override { }
  virtual void exitFrequency(CSSParser::FrequencyContext * /*ctx*/) override { }

  virtual void enterResolution(CSSParser::ResolutionContext * /*ctx*/) override { }
  virtual void exitResolution(CSSParser::ResolutionContext * /*ctx*/) override { }

  virtual void enterHexcolor(CSSParser::HexcolorContext * /*ctx*/) override { }
  virtual void exitHexcolor(CSSParser::HexcolorContext * /*ctx*/) override { }

  virtual void enterFunction(CSSParser::FunctionContext * /*ctx*/) override { }
  virtual void exitFunction(CSSParser::FunctionContext * /*ctx*/) override { }

  virtual void enterFunctionArguments(CSSParser::FunctionArgumentsContext * /*ctx*/) override { }
  virtual void exitFunctionArguments(CSSParser::FunctionArgumentsContext * /*ctx*/) override { }

  virtual void enterFunctionArgument(CSSParser::FunctionArgumentContext * /*ctx*/) override { }
  virtual void exitFunctionArgument(CSSParser::FunctionArgumentContext * /*ctx*/) override { }

  virtual void enterCalc(CSSParser::CalcContext * /*ctx*/) override { }
  virtual void exitCalc(CSSParser::CalcContext * /*ctx*/) override { }

  virtual void enterCalcExpression(CSSParser::CalcExpressionContext * /*ctx*/) override { }
  virtual void exitCalcExpression(CSSParser::CalcExpressionContext * /*ctx*/) override { }

  virtual void enterCalcTerm(CSSParser::CalcTermContext * /*ctx*/) override { }
  virtual void exitCalcTerm(CSSParser::CalcTermContext * /*ctx*/) override { }

  virtual void enterCalcFactor(CSSParser::CalcFactorContext * /*ctx*/) override { }
  virtual void exitCalcFactor(CSSParser::CalcFactorContext * /*ctx*/) override { }

  virtual void enterAtRule(CSSParser::AtRuleContext * /*ctx*/) override { }
  virtual void exitAtRule(CSSParser::AtRuleContext * /*ctx*/) override { }

  virtual void enterAtImport(CSSParser::AtImportContext * /*ctx*/) override { }
  virtual void exitAtImport(CSSParser::AtImportContext * /*ctx*/) override { }

  virtual void enterAtMedia(CSSParser::AtMediaContext * /*ctx*/) override { }
  virtual void exitAtMedia(CSSParser::AtMediaContext * /*ctx*/) override { }

  virtual void enterMediaQueryList(CSSParser::MediaQueryListContext * /*ctx*/) override { }
  virtual void exitMediaQueryList(CSSParser::MediaQueryListContext * /*ctx*/) override { }

  virtual void enterMediaQuery(CSSParser::MediaQueryContext * /*ctx*/) override { }
  virtual void exitMediaQuery(CSSParser::MediaQueryContext * /*ctx*/) override { }

  virtual void enterMediaType(CSSParser::MediaTypeContext * /*ctx*/) override { }
  virtual void exitMediaType(CSSParser::MediaTypeContext * /*ctx*/) override { }

  virtual void enterMediaFeature(CSSParser::MediaFeatureContext * /*ctx*/) override { }
  virtual void exitMediaFeature(CSSParser::MediaFeatureContext * /*ctx*/) override { }

  virtual void enterAtKeyframes(CSSParser::AtKeyframesContext * /*ctx*/) override { }
  virtual void exitAtKeyframes(CSSParser::AtKeyframesContext * /*ctx*/) override { }

  virtual void enterKeyframeBlock(CSSParser::KeyframeBlockContext * /*ctx*/) override { }
  virtual void exitKeyframeBlock(CSSParser::KeyframeBlockContext * /*ctx*/) override { }

  virtual void enterKeyframeSelector(CSSParser::KeyframeSelectorContext * /*ctx*/) override { }
  virtual void exitKeyframeSelector(CSSParser::KeyframeSelectorContext * /*ctx*/) override { }

  virtual void enterAtFontFace(CSSParser::AtFontFaceContext * /*ctx*/) override { }
  virtual void exitAtFontFace(CSSParser::AtFontFaceContext * /*ctx*/) override { }

  virtual void enterAtSupports(CSSParser::AtSupportsContext * /*ctx*/) override { }
  virtual void exitAtSupports(CSSParser::AtSupportsContext * /*ctx*/) override { }

  virtual void enterSupportsCondition(CSSParser::SupportsConditionContext * /*ctx*/) override { }
  virtual void exitSupportsCondition(CSSParser::SupportsConditionContext * /*ctx*/) override { }

  virtual void enterSupportsNegation(CSSParser::SupportsNegationContext * /*ctx*/) override { }
  virtual void exitSupportsNegation(CSSParser::SupportsNegationContext * /*ctx*/) override { }

  virtual void enterSupportsConjunction(CSSParser::SupportsConjunctionContext * /*ctx*/) override { }
  virtual void exitSupportsConjunction(CSSParser::SupportsConjunctionContext * /*ctx*/) override { }

  virtual void enterSupportsDisjunction(CSSParser::SupportsDisjunctionContext * /*ctx*/) override { }
  virtual void exitSupportsDisjunction(CSSParser::SupportsDisjunctionContext * /*ctx*/) override { }

  virtual void enterSupportsInParens(CSSParser::SupportsInParensContext * /*ctx*/) override { }
  virtual void exitSupportsInParens(CSSParser::SupportsInParensContext * /*ctx*/) override { }

  virtual void enterSupportsFeature(CSSParser::SupportsFeatureContext * /*ctx*/) override { }
  virtual void exitSupportsFeature(CSSParser::SupportsFeatureContext * /*ctx*/) override { }

  virtual void enterAtPage(CSSParser::AtPageContext * /*ctx*/) override { }
  virtual void exitAtPage(CSSParser::AtPageContext * /*ctx*/) override { }

  virtual void enterPseudoPage(CSSParser::PseudoPageContext * /*ctx*/) override { }
  virtual void exitPseudoPage(CSSParser::PseudoPageContext * /*ctx*/) override { }

  virtual void enterAtNamespace(CSSParser::AtNamespaceContext * /*ctx*/) override { }
  virtual void exitAtNamespace(CSSParser::AtNamespaceContext * /*ctx*/) override { }

  virtual void enterAtCharset(CSSParser::AtCharsetContext * /*ctx*/) override { }
  virtual void exitAtCharset(CSSParser::AtCharsetContext * /*ctx*/) override { }

  virtual void enterAtViewport(CSSParser::AtViewportContext * /*ctx*/) override { }
  virtual void exitAtViewport(CSSParser::AtViewportContext * /*ctx*/) override { }

  virtual void enterAtCounterStyle(CSSParser::AtCounterStyleContext * /*ctx*/) override { }
  virtual void exitAtCounterStyle(CSSParser::AtCounterStyleContext * /*ctx*/) override { }

  virtual void enterAtFontFeatureValues(CSSParser::AtFontFeatureValuesContext * /*ctx*/) override { }
  virtual void exitAtFontFeatureValues(CSSParser::AtFontFeatureValuesContext * /*ctx*/) override { }

  virtual void enterFontFamilyName(CSSParser::FontFamilyNameContext * /*ctx*/) override { }
  virtual void exitFontFamilyName(CSSParser::FontFamilyNameContext * /*ctx*/) override { }

  virtual void enterFontFeatureValueBlock(CSSParser::FontFeatureValueBlockContext * /*ctx*/) override { }
  virtual void exitFontFeatureValueBlock(CSSParser::FontFeatureValueBlockContext * /*ctx*/) override { }

  virtual void enterAtProperty(CSSParser::AtPropertyContext * /*ctx*/) override { }
  virtual void exitAtProperty(CSSParser::AtPropertyContext * /*ctx*/) override { }

  virtual void enterExpression(CSSParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(CSSParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterComment(CSSParser::CommentContext * /*ctx*/) override { }
  virtual void exitComment(CSSParser::CommentContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

