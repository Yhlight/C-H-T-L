
// Generated from /workspace/grammar/CSS.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "CSSParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CSSParser.
 */
class  CSSVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CSSParser.
   */
    virtual std::any visitStylesheet(CSSParser::StylesheetContext *context) = 0;

    virtual std::any visitStatement(CSSParser::StatementContext *context) = 0;

    virtual std::any visitCharsetRule(CSSParser::CharsetRuleContext *context) = 0;

    virtual std::any visitImportRule(CSSParser::ImportRuleContext *context) = 0;

    virtual std::any visitNamespaceRule(CSSParser::NamespaceRuleContext *context) = 0;

    virtual std::any visitMedia(CSSParser::MediaContext *context) = 0;

    virtual std::any visitMediaQueryList(CSSParser::MediaQueryListContext *context) = 0;

    virtual std::any visitMediaQuery(CSSParser::MediaQueryContext *context) = 0;

    virtual std::any visitMediaType(CSSParser::MediaTypeContext *context) = 0;

    virtual std::any visitMediaExpression(CSSParser::MediaExpressionContext *context) = 0;

    virtual std::any visitMediaFeature(CSSParser::MediaFeatureContext *context) = 0;

    virtual std::any visitPage(CSSParser::PageContext *context) = 0;

    virtual std::any visitPseudoPage(CSSParser::PseudoPageContext *context) = 0;

    virtual std::any visitFontFace(CSSParser::FontFaceContext *context) = 0;

    virtual std::any visitKeyframes(CSSParser::KeyframesContext *context) = 0;

    virtual std::any visitKeyframeRule(CSSParser::KeyframeRuleContext *context) = 0;

    virtual std::any visitKeyframeSelector(CSSParser::KeyframeSelectorContext *context) = 0;

    virtual std::any visitSupports(CSSParser::SupportsContext *context) = 0;

    virtual std::any visitSupportsCondition(CSSParser::SupportsConditionContext *context) = 0;

    virtual std::any visitSupportsNegation(CSSParser::SupportsNegationContext *context) = 0;

    virtual std::any visitSupportsConjunction(CSSParser::SupportsConjunctionContext *context) = 0;

    virtual std::any visitSupportsDisjunction(CSSParser::SupportsDisjunctionContext *context) = 0;

    virtual std::any visitSupportsConditionInParens(CSSParser::SupportsConditionInParensContext *context) = 0;

    virtual std::any visitSupportsDeclarationCondition(CSSParser::SupportsDeclarationConditionContext *context) = 0;

    virtual std::any visitGeneralEnclosed(CSSParser::GeneralEnclosedContext *context) = 0;

    virtual std::any visitRuleset(CSSParser::RulesetContext *context) = 0;

    virtual std::any visitSelectorList(CSSParser::SelectorListContext *context) = 0;

    virtual std::any visitSelector(CSSParser::SelectorContext *context) = 0;

    virtual std::any visitCombinator(CSSParser::CombinatorContext *context) = 0;

    virtual std::any visitSimpleSelector(CSSParser::SimpleSelectorContext *context) = 0;

    virtual std::any visitTypeSelector(CSSParser::TypeSelectorContext *context) = 0;

    virtual std::any visitTypeNamespacePrefix(CSSParser::TypeNamespacePrefixContext *context) = 0;

    virtual std::any visitElementName(CSSParser::ElementNameContext *context) = 0;

    virtual std::any visitUniversal(CSSParser::UniversalContext *context) = 0;

    virtual std::any visitIdSelector(CSSParser::IdSelectorContext *context) = 0;

    virtual std::any visitClassSelector(CSSParser::ClassSelectorContext *context) = 0;

    virtual std::any visitAttributeSelector(CSSParser::AttributeSelectorContext *context) = 0;

    virtual std::any visitAttributeOperator(CSSParser::AttributeOperatorContext *context) = 0;

    virtual std::any visitPseudoClass(CSSParser::PseudoClassContext *context) = 0;

    virtual std::any visitFunctionalPseudoClass(CSSParser::FunctionalPseudoClassContext *context) = 0;

    virtual std::any visitPseudoElement(CSSParser::PseudoElementContext *context) = 0;

    virtual std::any visitDeclaration(CSSParser::DeclarationContext *context) = 0;

    virtual std::any visitProperty(CSSParser::PropertyContext *context) = 0;

    virtual std::any visitValue(CSSParser::ValueContext *context) = 0;

    virtual std::any visitTerm(CSSParser::TermContext *context) = 0;

    virtual std::any visitFunction(CSSParser::FunctionContext *context) = 0;

    virtual std::any visitHexcolor(CSSParser::HexcolorContext *context) = 0;

    virtual std::any visitUrl(CSSParser::UrlContext *context) = 0;

    virtual std::any visitOperator(CSSParser::OperatorContext *context) = 0;

    virtual std::any visitImportant(CSSParser::ImportantContext *context) = 0;

    virtual std::any visitNestedStatement(CSSParser::NestedStatementContext *context) = 0;


};

