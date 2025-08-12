
// Generated from /workspace/grammar/CSS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CSSVisitor.h"


/**
 * This class provides an empty implementation of CSSVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CSSBaseVisitor : public CSSVisitor {
public:

  virtual std::any visitStylesheet(CSSParser::StylesheetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(CSSParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCharsetRule(CSSParser::CharsetRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportRule(CSSParser::ImportRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceRule(CSSParser::NamespaceRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMedia(CSSParser::MediaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMediaQueryList(CSSParser::MediaQueryListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMediaQuery(CSSParser::MediaQueryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMediaType(CSSParser::MediaTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMediaExpression(CSSParser::MediaExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMediaFeature(CSSParser::MediaFeatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPage(CSSParser::PageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPseudoPage(CSSParser::PseudoPageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFontFace(CSSParser::FontFaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyframes(CSSParser::KeyframesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyframeRule(CSSParser::KeyframeRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyframeSelector(CSSParser::KeyframeSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSupports(CSSParser::SupportsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSupportsCondition(CSSParser::SupportsConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSupportsNegation(CSSParser::SupportsNegationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSupportsConjunction(CSSParser::SupportsConjunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSupportsDisjunction(CSSParser::SupportsDisjunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSupportsConditionInParens(CSSParser::SupportsConditionInParensContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSupportsDeclarationCondition(CSSParser::SupportsDeclarationConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGeneralEnclosed(CSSParser::GeneralEnclosedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRuleset(CSSParser::RulesetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectorList(CSSParser::SelectorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelector(CSSParser::SelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCombinator(CSSParser::CombinatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleSelector(CSSParser::SimpleSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSelector(CSSParser::TypeSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeNamespacePrefix(CSSParser::TypeNamespacePrefixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementName(CSSParser::ElementNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUniversal(CSSParser::UniversalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdSelector(CSSParser::IdSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassSelector(CSSParser::ClassSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeSelector(CSSParser::AttributeSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeOperator(CSSParser::AttributeOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPseudoClass(CSSParser::PseudoClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionalPseudoClass(CSSParser::FunctionalPseudoClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPseudoElement(CSSParser::PseudoElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(CSSParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty(CSSParser::PropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue(CSSParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerm(CSSParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction(CSSParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHexcolor(CSSParser::HexcolorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUrl(CSSParser::UrlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperator(CSSParser::OperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportant(CSSParser::ImportantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNestedStatement(CSSParser::NestedStatementContext *ctx) override {
    return visitChildren(ctx);
  }


};

