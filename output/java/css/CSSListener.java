// Generated from CSS.g4 by ANTLR 4.13.1
package css;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link CSSParser}.
 */
public interface CSSListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link CSSParser#stylesheet}.
	 * @param ctx the parse tree
	 */
	void enterStylesheet(CSSParser.StylesheetContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#stylesheet}.
	 * @param ctx the parse tree
	 */
	void exitStylesheet(CSSParser.StylesheetContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(CSSParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(CSSParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#ruleset}.
	 * @param ctx the parse tree
	 */
	void enterRuleset(CSSParser.RulesetContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#ruleset}.
	 * @param ctx the parse tree
	 */
	void exitRuleset(CSSParser.RulesetContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#selectorList}.
	 * @param ctx the parse tree
	 */
	void enterSelectorList(CSSParser.SelectorListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#selectorList}.
	 * @param ctx the parse tree
	 */
	void exitSelectorList(CSSParser.SelectorListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#selector}.
	 * @param ctx the parse tree
	 */
	void enterSelector(CSSParser.SelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#selector}.
	 * @param ctx the parse tree
	 */
	void exitSelector(CSSParser.SelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#combinator}.
	 * @param ctx the parse tree
	 */
	void enterCombinator(CSSParser.CombinatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#combinator}.
	 * @param ctx the parse tree
	 */
	void exitCombinator(CSSParser.CombinatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#simpleSelector}.
	 * @param ctx the parse tree
	 */
	void enterSimpleSelector(CSSParser.SimpleSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#simpleSelector}.
	 * @param ctx the parse tree
	 */
	void exitSimpleSelector(CSSParser.SimpleSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#typeSelector}.
	 * @param ctx the parse tree
	 */
	void enterTypeSelector(CSSParser.TypeSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#typeSelector}.
	 * @param ctx the parse tree
	 */
	void exitTypeSelector(CSSParser.TypeSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#universalSelector}.
	 * @param ctx the parse tree
	 */
	void enterUniversalSelector(CSSParser.UniversalSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#universalSelector}.
	 * @param ctx the parse tree
	 */
	void exitUniversalSelector(CSSParser.UniversalSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#idSelector}.
	 * @param ctx the parse tree
	 */
	void enterIdSelector(CSSParser.IdSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#idSelector}.
	 * @param ctx the parse tree
	 */
	void exitIdSelector(CSSParser.IdSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#classSelector}.
	 * @param ctx the parse tree
	 */
	void enterClassSelector(CSSParser.ClassSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#classSelector}.
	 * @param ctx the parse tree
	 */
	void exitClassSelector(CSSParser.ClassSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#attributeSelector}.
	 * @param ctx the parse tree
	 */
	void enterAttributeSelector(CSSParser.AttributeSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#attributeSelector}.
	 * @param ctx the parse tree
	 */
	void exitAttributeSelector(CSSParser.AttributeSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#attributeOperator}.
	 * @param ctx the parse tree
	 */
	void enterAttributeOperator(CSSParser.AttributeOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#attributeOperator}.
	 * @param ctx the parse tree
	 */
	void exitAttributeOperator(CSSParser.AttributeOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#pseudoSelector}.
	 * @param ctx the parse tree
	 */
	void enterPseudoSelector(CSSParser.PseudoSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#pseudoSelector}.
	 * @param ctx the parse tree
	 */
	void exitPseudoSelector(CSSParser.PseudoSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#pseudoClass}.
	 * @param ctx the parse tree
	 */
	void enterPseudoClass(CSSParser.PseudoClassContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#pseudoClass}.
	 * @param ctx the parse tree
	 */
	void exitPseudoClass(CSSParser.PseudoClassContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#pseudoClassArgument}.
	 * @param ctx the parse tree
	 */
	void enterPseudoClassArgument(CSSParser.PseudoClassArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#pseudoClassArgument}.
	 * @param ctx the parse tree
	 */
	void exitPseudoClassArgument(CSSParser.PseudoClassArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#pseudoElement}.
	 * @param ctx the parse tree
	 */
	void enterPseudoElement(CSSParser.PseudoElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#pseudoElement}.
	 * @param ctx the parse tree
	 */
	void exitPseudoElement(CSSParser.PseudoElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(CSSParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(CSSParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#property}.
	 * @param ctx the parse tree
	 */
	void enterProperty(CSSParser.PropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#property}.
	 * @param ctx the parse tree
	 */
	void exitProperty(CSSParser.PropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#value}.
	 * @param ctx the parse tree
	 */
	void enterValue(CSSParser.ValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#value}.
	 * @param ctx the parse tree
	 */
	void exitValue(CSSParser.ValueContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#operator}.
	 * @param ctx the parse tree
	 */
	void enterOperator(CSSParser.OperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#operator}.
	 * @param ctx the parse tree
	 */
	void exitOperator(CSSParser.OperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(CSSParser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(CSSParser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#unaryOperator}.
	 * @param ctx the parse tree
	 */
	void enterUnaryOperator(CSSParser.UnaryOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#unaryOperator}.
	 * @param ctx the parse tree
	 */
	void exitUnaryOperator(CSSParser.UnaryOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#numeric}.
	 * @param ctx the parse tree
	 */
	void enterNumeric(CSSParser.NumericContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#numeric}.
	 * @param ctx the parse tree
	 */
	void exitNumeric(CSSParser.NumericContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#percentage}.
	 * @param ctx the parse tree
	 */
	void enterPercentage(CSSParser.PercentageContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#percentage}.
	 * @param ctx the parse tree
	 */
	void exitPercentage(CSSParser.PercentageContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#length}.
	 * @param ctx the parse tree
	 */
	void enterLength(CSSParser.LengthContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#length}.
	 * @param ctx the parse tree
	 */
	void exitLength(CSSParser.LengthContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#angle}.
	 * @param ctx the parse tree
	 */
	void enterAngle(CSSParser.AngleContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#angle}.
	 * @param ctx the parse tree
	 */
	void exitAngle(CSSParser.AngleContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#time}.
	 * @param ctx the parse tree
	 */
	void enterTime(CSSParser.TimeContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#time}.
	 * @param ctx the parse tree
	 */
	void exitTime(CSSParser.TimeContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#frequency}.
	 * @param ctx the parse tree
	 */
	void enterFrequency(CSSParser.FrequencyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#frequency}.
	 * @param ctx the parse tree
	 */
	void exitFrequency(CSSParser.FrequencyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#resolution}.
	 * @param ctx the parse tree
	 */
	void enterResolution(CSSParser.ResolutionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#resolution}.
	 * @param ctx the parse tree
	 */
	void exitResolution(CSSParser.ResolutionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#hexcolor}.
	 * @param ctx the parse tree
	 */
	void enterHexcolor(CSSParser.HexcolorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#hexcolor}.
	 * @param ctx the parse tree
	 */
	void exitHexcolor(CSSParser.HexcolorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(CSSParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(CSSParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#functionArguments}.
	 * @param ctx the parse tree
	 */
	void enterFunctionArguments(CSSParser.FunctionArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#functionArguments}.
	 * @param ctx the parse tree
	 */
	void exitFunctionArguments(CSSParser.FunctionArgumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#functionArgument}.
	 * @param ctx the parse tree
	 */
	void enterFunctionArgument(CSSParser.FunctionArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#functionArgument}.
	 * @param ctx the parse tree
	 */
	void exitFunctionArgument(CSSParser.FunctionArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#calc}.
	 * @param ctx the parse tree
	 */
	void enterCalc(CSSParser.CalcContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#calc}.
	 * @param ctx the parse tree
	 */
	void exitCalc(CSSParser.CalcContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#calcExpression}.
	 * @param ctx the parse tree
	 */
	void enterCalcExpression(CSSParser.CalcExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#calcExpression}.
	 * @param ctx the parse tree
	 */
	void exitCalcExpression(CSSParser.CalcExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#calcTerm}.
	 * @param ctx the parse tree
	 */
	void enterCalcTerm(CSSParser.CalcTermContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#calcTerm}.
	 * @param ctx the parse tree
	 */
	void exitCalcTerm(CSSParser.CalcTermContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#calcFactor}.
	 * @param ctx the parse tree
	 */
	void enterCalcFactor(CSSParser.CalcFactorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#calcFactor}.
	 * @param ctx the parse tree
	 */
	void exitCalcFactor(CSSParser.CalcFactorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atRule}.
	 * @param ctx the parse tree
	 */
	void enterAtRule(CSSParser.AtRuleContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atRule}.
	 * @param ctx the parse tree
	 */
	void exitAtRule(CSSParser.AtRuleContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atImport}.
	 * @param ctx the parse tree
	 */
	void enterAtImport(CSSParser.AtImportContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atImport}.
	 * @param ctx the parse tree
	 */
	void exitAtImport(CSSParser.AtImportContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atMedia}.
	 * @param ctx the parse tree
	 */
	void enterAtMedia(CSSParser.AtMediaContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atMedia}.
	 * @param ctx the parse tree
	 */
	void exitAtMedia(CSSParser.AtMediaContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#mediaQueryList}.
	 * @param ctx the parse tree
	 */
	void enterMediaQueryList(CSSParser.MediaQueryListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#mediaQueryList}.
	 * @param ctx the parse tree
	 */
	void exitMediaQueryList(CSSParser.MediaQueryListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#mediaQuery}.
	 * @param ctx the parse tree
	 */
	void enterMediaQuery(CSSParser.MediaQueryContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#mediaQuery}.
	 * @param ctx the parse tree
	 */
	void exitMediaQuery(CSSParser.MediaQueryContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#mediaType}.
	 * @param ctx the parse tree
	 */
	void enterMediaType(CSSParser.MediaTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#mediaType}.
	 * @param ctx the parse tree
	 */
	void exitMediaType(CSSParser.MediaTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#mediaFeature}.
	 * @param ctx the parse tree
	 */
	void enterMediaFeature(CSSParser.MediaFeatureContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#mediaFeature}.
	 * @param ctx the parse tree
	 */
	void exitMediaFeature(CSSParser.MediaFeatureContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atKeyframes}.
	 * @param ctx the parse tree
	 */
	void enterAtKeyframes(CSSParser.AtKeyframesContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atKeyframes}.
	 * @param ctx the parse tree
	 */
	void exitAtKeyframes(CSSParser.AtKeyframesContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#keyframeBlock}.
	 * @param ctx the parse tree
	 */
	void enterKeyframeBlock(CSSParser.KeyframeBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#keyframeBlock}.
	 * @param ctx the parse tree
	 */
	void exitKeyframeBlock(CSSParser.KeyframeBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#keyframeSelector}.
	 * @param ctx the parse tree
	 */
	void enterKeyframeSelector(CSSParser.KeyframeSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#keyframeSelector}.
	 * @param ctx the parse tree
	 */
	void exitKeyframeSelector(CSSParser.KeyframeSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atFontFace}.
	 * @param ctx the parse tree
	 */
	void enterAtFontFace(CSSParser.AtFontFaceContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atFontFace}.
	 * @param ctx the parse tree
	 */
	void exitAtFontFace(CSSParser.AtFontFaceContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atSupports}.
	 * @param ctx the parse tree
	 */
	void enterAtSupports(CSSParser.AtSupportsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atSupports}.
	 * @param ctx the parse tree
	 */
	void exitAtSupports(CSSParser.AtSupportsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#supportsCondition}.
	 * @param ctx the parse tree
	 */
	void enterSupportsCondition(CSSParser.SupportsConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#supportsCondition}.
	 * @param ctx the parse tree
	 */
	void exitSupportsCondition(CSSParser.SupportsConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#supportsNegation}.
	 * @param ctx the parse tree
	 */
	void enterSupportsNegation(CSSParser.SupportsNegationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#supportsNegation}.
	 * @param ctx the parse tree
	 */
	void exitSupportsNegation(CSSParser.SupportsNegationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#supportsConjunction}.
	 * @param ctx the parse tree
	 */
	void enterSupportsConjunction(CSSParser.SupportsConjunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#supportsConjunction}.
	 * @param ctx the parse tree
	 */
	void exitSupportsConjunction(CSSParser.SupportsConjunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#supportsDisjunction}.
	 * @param ctx the parse tree
	 */
	void enterSupportsDisjunction(CSSParser.SupportsDisjunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#supportsDisjunction}.
	 * @param ctx the parse tree
	 */
	void exitSupportsDisjunction(CSSParser.SupportsDisjunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#supportsInParens}.
	 * @param ctx the parse tree
	 */
	void enterSupportsInParens(CSSParser.SupportsInParensContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#supportsInParens}.
	 * @param ctx the parse tree
	 */
	void exitSupportsInParens(CSSParser.SupportsInParensContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#supportsFeature}.
	 * @param ctx the parse tree
	 */
	void enterSupportsFeature(CSSParser.SupportsFeatureContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#supportsFeature}.
	 * @param ctx the parse tree
	 */
	void exitSupportsFeature(CSSParser.SupportsFeatureContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atPage}.
	 * @param ctx the parse tree
	 */
	void enterAtPage(CSSParser.AtPageContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atPage}.
	 * @param ctx the parse tree
	 */
	void exitAtPage(CSSParser.AtPageContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#pseudoPage}.
	 * @param ctx the parse tree
	 */
	void enterPseudoPage(CSSParser.PseudoPageContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#pseudoPage}.
	 * @param ctx the parse tree
	 */
	void exitPseudoPage(CSSParser.PseudoPageContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atNamespace}.
	 * @param ctx the parse tree
	 */
	void enterAtNamespace(CSSParser.AtNamespaceContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atNamespace}.
	 * @param ctx the parse tree
	 */
	void exitAtNamespace(CSSParser.AtNamespaceContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atCharset}.
	 * @param ctx the parse tree
	 */
	void enterAtCharset(CSSParser.AtCharsetContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atCharset}.
	 * @param ctx the parse tree
	 */
	void exitAtCharset(CSSParser.AtCharsetContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atViewport}.
	 * @param ctx the parse tree
	 */
	void enterAtViewport(CSSParser.AtViewportContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atViewport}.
	 * @param ctx the parse tree
	 */
	void exitAtViewport(CSSParser.AtViewportContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atCounterStyle}.
	 * @param ctx the parse tree
	 */
	void enterAtCounterStyle(CSSParser.AtCounterStyleContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atCounterStyle}.
	 * @param ctx the parse tree
	 */
	void exitAtCounterStyle(CSSParser.AtCounterStyleContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atFontFeatureValues}.
	 * @param ctx the parse tree
	 */
	void enterAtFontFeatureValues(CSSParser.AtFontFeatureValuesContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atFontFeatureValues}.
	 * @param ctx the parse tree
	 */
	void exitAtFontFeatureValues(CSSParser.AtFontFeatureValuesContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#fontFamilyName}.
	 * @param ctx the parse tree
	 */
	void enterFontFamilyName(CSSParser.FontFamilyNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#fontFamilyName}.
	 * @param ctx the parse tree
	 */
	void exitFontFamilyName(CSSParser.FontFamilyNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#fontFeatureValueBlock}.
	 * @param ctx the parse tree
	 */
	void enterFontFeatureValueBlock(CSSParser.FontFeatureValueBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#fontFeatureValueBlock}.
	 * @param ctx the parse tree
	 */
	void exitFontFeatureValueBlock(CSSParser.FontFeatureValueBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#atProperty}.
	 * @param ctx the parse tree
	 */
	void enterAtProperty(CSSParser.AtPropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#atProperty}.
	 * @param ctx the parse tree
	 */
	void exitAtProperty(CSSParser.AtPropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(CSSParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(CSSParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CSSParser#comment}.
	 * @param ctx the parse tree
	 */
	void enterComment(CSSParser.CommentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CSSParser#comment}.
	 * @param ctx the parse tree
	 */
	void exitComment(CSSParser.CommentContext ctx);
}