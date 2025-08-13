// Generated from CHTL.g4 by ANTLR 4.13.1
package chtl;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link CHTLParser}.
 */
public interface CHTLListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link CHTLParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(CHTLParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(CHTLParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#topLevelStatement}.
	 * @param ctx the parse tree
	 */
	void enterTopLevelStatement(CHTLParser.TopLevelStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#topLevelStatement}.
	 * @param ctx the parse tree
	 */
	void exitTopLevelStatement(CHTLParser.TopLevelStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#configurationBlock}.
	 * @param ctx the parse tree
	 */
	void enterConfigurationBlock(CHTLParser.ConfigurationBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#configurationBlock}.
	 * @param ctx the parse tree
	 */
	void exitConfigurationBlock(CHTLParser.ConfigurationBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#configurationItem}.
	 * @param ctx the parse tree
	 */
	void enterConfigurationItem(CHTLParser.ConfigurationItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#configurationItem}.
	 * @param ctx the parse tree
	 */
	void exitConfigurationItem(CHTLParser.ConfigurationItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#configKey}.
	 * @param ctx the parse tree
	 */
	void enterConfigKey(CHTLParser.ConfigKeyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#configKey}.
	 * @param ctx the parse tree
	 */
	void exitConfigKey(CHTLParser.ConfigKeyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#configValue}.
	 * @param ctx the parse tree
	 */
	void enterConfigValue(CHTLParser.ConfigValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#configValue}.
	 * @param ctx the parse tree
	 */
	void exitConfigValue(CHTLParser.ConfigValueContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#configValueArray}.
	 * @param ctx the parse tree
	 */
	void enterConfigValueArray(CHTLParser.ConfigValueArrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#configValueArray}.
	 * @param ctx the parse tree
	 */
	void exitConfigValueArray(CHTLParser.ConfigValueArrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#configArrayItem}.
	 * @param ctx the parse tree
	 */
	void enterConfigArrayItem(CHTLParser.ConfigArrayItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#configArrayItem}.
	 * @param ctx the parse tree
	 */
	void exitConfigArrayItem(CHTLParser.ConfigArrayItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#nameConfigItem}.
	 * @param ctx the parse tree
	 */
	void enterNameConfigItem(CHTLParser.NameConfigItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#nameConfigItem}.
	 * @param ctx the parse tree
	 */
	void exitNameConfigItem(CHTLParser.NameConfigItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#namespaceDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterNamespaceDeclaration(CHTLParser.NamespaceDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#namespaceDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitNamespaceDeclaration(CHTLParser.NamespaceDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#namespaceBody}.
	 * @param ctx the parse tree
	 */
	void enterNamespaceBody(CHTLParser.NamespaceBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#namespaceBody}.
	 * @param ctx the parse tree
	 */
	void exitNamespaceBody(CHTLParser.NamespaceBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#namespaceContent}.
	 * @param ctx the parse tree
	 */
	void enterNamespaceContent(CHTLParser.NamespaceContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#namespaceContent}.
	 * @param ctx the parse tree
	 */
	void exitNamespaceContent(CHTLParser.NamespaceContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void enterImportStatement(CHTLParser.ImportStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#importStatement}.
	 * @param ctx the parse tree
	 */
	void exitImportStatement(CHTLParser.ImportStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#importType}.
	 * @param ctx the parse tree
	 */
	void enterImportType(CHTLParser.ImportTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#importType}.
	 * @param ctx the parse tree
	 */
	void exitImportType(CHTLParser.ImportTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#importPath}.
	 * @param ctx the parse tree
	 */
	void enterImportPath(CHTLParser.ImportPathContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#importPath}.
	 * @param ctx the parse tree
	 */
	void exitImportPath(CHTLParser.ImportPathContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#dottedPath}.
	 * @param ctx the parse tree
	 */
	void enterDottedPath(CHTLParser.DottedPathContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#dottedPath}.
	 * @param ctx the parse tree
	 */
	void exitDottedPath(CHTLParser.DottedPathContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#templateDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterTemplateDeclaration(CHTLParser.TemplateDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#templateDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitTemplateDeclaration(CHTLParser.TemplateDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#templateType}.
	 * @param ctx the parse tree
	 */
	void enterTemplateType(CHTLParser.TemplateTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#templateType}.
	 * @param ctx the parse tree
	 */
	void exitTemplateType(CHTLParser.TemplateTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#templateBody}.
	 * @param ctx the parse tree
	 */
	void enterTemplateBody(CHTLParser.TemplateBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#templateBody}.
	 * @param ctx the parse tree
	 */
	void exitTemplateBody(CHTLParser.TemplateBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#templateContent}.
	 * @param ctx the parse tree
	 */
	void enterTemplateContent(CHTLParser.TemplateContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#templateContent}.
	 * @param ctx the parse tree
	 */
	void exitTemplateContent(CHTLParser.TemplateContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#templateInheritance}.
	 * @param ctx the parse tree
	 */
	void enterTemplateInheritance(CHTLParser.TemplateInheritanceContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#templateInheritance}.
	 * @param ctx the parse tree
	 */
	void exitTemplateInheritance(CHTLParser.TemplateInheritanceContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#customDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterCustomDeclaration(CHTLParser.CustomDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#customDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitCustomDeclaration(CHTLParser.CustomDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#customType}.
	 * @param ctx the parse tree
	 */
	void enterCustomType(CHTLParser.CustomTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#customType}.
	 * @param ctx the parse tree
	 */
	void exitCustomType(CHTLParser.CustomTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#customBody}.
	 * @param ctx the parse tree
	 */
	void enterCustomBody(CHTLParser.CustomBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#customBody}.
	 * @param ctx the parse tree
	 */
	void exitCustomBody(CHTLParser.CustomBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#customContent}.
	 * @param ctx the parse tree
	 */
	void enterCustomContent(CHTLParser.CustomContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#customContent}.
	 * @param ctx the parse tree
	 */
	void exitCustomContent(CHTLParser.CustomContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#customInheritance}.
	 * @param ctx the parse tree
	 */
	void enterCustomInheritance(CHTLParser.CustomInheritanceContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#customInheritance}.
	 * @param ctx the parse tree
	 */
	void exitCustomInheritance(CHTLParser.CustomInheritanceContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#customSpecialization}.
	 * @param ctx the parse tree
	 */
	void enterCustomSpecialization(CHTLParser.CustomSpecializationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#customSpecialization}.
	 * @param ctx the parse tree
	 */
	void exitCustomSpecialization(CHTLParser.CustomSpecializationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#specializationContent}.
	 * @param ctx the parse tree
	 */
	void enterSpecializationContent(CHTLParser.SpecializationContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#specializationContent}.
	 * @param ctx the parse tree
	 */
	void exitSpecializationContent(CHTLParser.SpecializationContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#deleteStatement}.
	 * @param ctx the parse tree
	 */
	void enterDeleteStatement(CHTLParser.DeleteStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#deleteStatement}.
	 * @param ctx the parse tree
	 */
	void exitDeleteStatement(CHTLParser.DeleteStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#deleteTarget}.
	 * @param ctx the parse tree
	 */
	void enterDeleteTarget(CHTLParser.DeleteTargetContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#deleteTarget}.
	 * @param ctx the parse tree
	 */
	void exitDeleteTarget(CHTLParser.DeleteTargetContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#insertStatement}.
	 * @param ctx the parse tree
	 */
	void enterInsertStatement(CHTLParser.InsertStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#insertStatement}.
	 * @param ctx the parse tree
	 */
	void exitInsertStatement(CHTLParser.InsertStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#insertPosition}.
	 * @param ctx the parse tree
	 */
	void enterInsertPosition(CHTLParser.InsertPositionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#insertPosition}.
	 * @param ctx the parse tree
	 */
	void exitInsertPosition(CHTLParser.InsertPositionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementSelector}.
	 * @param ctx the parse tree
	 */
	void enterElementSelector(CHTLParser.ElementSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementSelector}.
	 * @param ctx the parse tree
	 */
	void exitElementSelector(CHTLParser.ElementSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#insertContent}.
	 * @param ctx the parse tree
	 */
	void enterInsertContent(CHTLParser.InsertContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#insertContent}.
	 * @param ctx the parse tree
	 */
	void exitInsertContent(CHTLParser.InsertContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#originBlock}.
	 * @param ctx the parse tree
	 */
	void enterOriginBlock(CHTLParser.OriginBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#originBlock}.
	 * @param ctx the parse tree
	 */
	void exitOriginBlock(CHTLParser.OriginBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#originType}.
	 * @param ctx the parse tree
	 */
	void enterOriginType(CHTLParser.OriginTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#originType}.
	 * @param ctx the parse tree
	 */
	void exitOriginType(CHTLParser.OriginTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#originContent}.
	 * @param ctx the parse tree
	 */
	void enterOriginContent(CHTLParser.OriginContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#originContent}.
	 * @param ctx the parse tree
	 */
	void exitOriginContent(CHTLParser.OriginContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#htmlElement}.
	 * @param ctx the parse tree
	 */
	void enterHtmlElement(CHTLParser.HtmlElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#htmlElement}.
	 * @param ctx the parse tree
	 */
	void exitHtmlElement(CHTLParser.HtmlElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#globalStyleElement}.
	 * @param ctx the parse tree
	 */
	void enterGlobalStyleElement(CHTLParser.GlobalStyleElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#globalStyleElement}.
	 * @param ctx the parse tree
	 */
	void exitGlobalStyleElement(CHTLParser.GlobalStyleElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#globalStyleContent}.
	 * @param ctx the parse tree
	 */
	void enterGlobalStyleContent(CHTLParser.GlobalStyleContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#globalStyleContent}.
	 * @param ctx the parse tree
	 */
	void exitGlobalStyleContent(CHTLParser.GlobalStyleContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementName}.
	 * @param ctx the parse tree
	 */
	void enterElementName(CHTLParser.ElementNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementName}.
	 * @param ctx the parse tree
	 */
	void exitElementName(CHTLParser.ElementNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementIndexAccess}.
	 * @param ctx the parse tree
	 */
	void enterElementIndexAccess(CHTLParser.ElementIndexAccessContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementIndexAccess}.
	 * @param ctx the parse tree
	 */
	void exitElementIndexAccess(CHTLParser.ElementIndexAccessContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementBody}.
	 * @param ctx the parse tree
	 */
	void enterElementBody(CHTLParser.ElementBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementBody}.
	 * @param ctx the parse tree
	 */
	void exitElementBody(CHTLParser.ElementBodyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementContent}.
	 * @param ctx the parse tree
	 */
	void enterElementContent(CHTLParser.ElementContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementContent}.
	 * @param ctx the parse tree
	 */
	void exitElementContent(CHTLParser.ElementContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#attribute}.
	 * @param ctx the parse tree
	 */
	void enterAttribute(CHTLParser.AttributeContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#attribute}.
	 * @param ctx the parse tree
	 */
	void exitAttribute(CHTLParser.AttributeContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#attributeName}.
	 * @param ctx the parse tree
	 */
	void enterAttributeName(CHTLParser.AttributeNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#attributeName}.
	 * @param ctx the parse tree
	 */
	void exitAttributeName(CHTLParser.AttributeNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#attributeValue}.
	 * @param ctx the parse tree
	 */
	void enterAttributeValue(CHTLParser.AttributeValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#attributeValue}.
	 * @param ctx the parse tree
	 */
	void exitAttributeValue(CHTLParser.AttributeValueContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#textContent}.
	 * @param ctx the parse tree
	 */
	void enterTextContent(CHTLParser.TextContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#textContent}.
	 * @param ctx the parse tree
	 */
	void exitTextContent(CHTLParser.TextContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#styleBlock}.
	 * @param ctx the parse tree
	 */
	void enterStyleBlock(CHTLParser.StyleBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#styleBlock}.
	 * @param ctx the parse tree
	 */
	void exitStyleBlock(CHTLParser.StyleBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#styleContent}.
	 * @param ctx the parse tree
	 */
	void enterStyleContent(CHTLParser.StyleContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#styleContent}.
	 * @param ctx the parse tree
	 */
	void exitStyleContent(CHTLParser.StyleContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#styleProperty}.
	 * @param ctx the parse tree
	 */
	void enterStyleProperty(CHTLParser.StylePropertyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#styleProperty}.
	 * @param ctx the parse tree
	 */
	void exitStyleProperty(CHTLParser.StylePropertyContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#propertyName}.
	 * @param ctx the parse tree
	 */
	void enterPropertyName(CHTLParser.PropertyNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#propertyName}.
	 * @param ctx the parse tree
	 */
	void exitPropertyName(CHTLParser.PropertyNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#propertyValue}.
	 * @param ctx the parse tree
	 */
	void enterPropertyValue(CHTLParser.PropertyValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#propertyValue}.
	 * @param ctx the parse tree
	 */
	void exitPropertyValue(CHTLParser.PropertyValueContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#cssSelector}.
	 * @param ctx the parse tree
	 */
	void enterCssSelector(CHTLParser.CssSelectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#cssSelector}.
	 * @param ctx the parse tree
	 */
	void exitCssSelector(CHTLParser.CssSelectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#pseudoClass}.
	 * @param ctx the parse tree
	 */
	void enterPseudoClass(CHTLParser.PseudoClassContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#pseudoClass}.
	 * @param ctx the parse tree
	 */
	void exitPseudoClass(CHTLParser.PseudoClassContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#pseudoElement}.
	 * @param ctx the parse tree
	 */
	void enterPseudoElement(CHTLParser.PseudoElementContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#pseudoElement}.
	 * @param ctx the parse tree
	 */
	void exitPseudoElement(CHTLParser.PseudoElementContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#cssFunction}.
	 * @param ctx the parse tree
	 */
	void enterCssFunction(CHTLParser.CssFunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#cssFunction}.
	 * @param ctx the parse tree
	 */
	void exitCssFunction(CHTLParser.CssFunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#cssArguments}.
	 * @param ctx the parse tree
	 */
	void enterCssArguments(CHTLParser.CssArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#cssArguments}.
	 * @param ctx the parse tree
	 */
	void exitCssArguments(CHTLParser.CssArgumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#cssArgument}.
	 * @param ctx the parse tree
	 */
	void enterCssArgument(CHTLParser.CssArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#cssArgument}.
	 * @param ctx the parse tree
	 */
	void exitCssArgument(CHTLParser.CssArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#scriptBlock}.
	 * @param ctx the parse tree
	 */
	void enterScriptBlock(CHTLParser.ScriptBlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#scriptBlock}.
	 * @param ctx the parse tree
	 */
	void exitScriptBlock(CHTLParser.ScriptBlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#scriptContent}.
	 * @param ctx the parse tree
	 */
	void enterScriptContent(CHTLParser.ScriptContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#scriptContent}.
	 * @param ctx the parse tree
	 */
	void exitScriptContent(CHTLParser.ScriptContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementUsage}.
	 * @param ctx the parse tree
	 */
	void enterElementUsage(CHTLParser.ElementUsageContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementUsage}.
	 * @param ctx the parse tree
	 */
	void exitElementUsage(CHTLParser.ElementUsageContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementSpecialization}.
	 * @param ctx the parse tree
	 */
	void enterElementSpecialization(CHTLParser.ElementSpecializationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementSpecialization}.
	 * @param ctx the parse tree
	 */
	void exitElementSpecialization(CHTLParser.ElementSpecializationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#elementSpecializationContent}.
	 * @param ctx the parse tree
	 */
	void enterElementSpecializationContent(CHTLParser.ElementSpecializationContentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#elementSpecializationContent}.
	 * @param ctx the parse tree
	 */
	void exitElementSpecializationContent(CHTLParser.ElementSpecializationContentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#styleUsage}.
	 * @param ctx the parse tree
	 */
	void enterStyleUsage(CHTLParser.StyleUsageContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#styleUsage}.
	 * @param ctx the parse tree
	 */
	void exitStyleUsage(CHTLParser.StyleUsageContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#styleSpecialization}.
	 * @param ctx the parse tree
	 */
	void enterStyleSpecialization(CHTLParser.StyleSpecializationContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#styleSpecialization}.
	 * @param ctx the parse tree
	 */
	void exitStyleSpecialization(CHTLParser.StyleSpecializationContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#variableDefinition}.
	 * @param ctx the parse tree
	 */
	void enterVariableDefinition(CHTLParser.VariableDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#variableDefinition}.
	 * @param ctx the parse tree
	 */
	void exitVariableDefinition(CHTLParser.VariableDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#variableUsage}.
	 * @param ctx the parse tree
	 */
	void enterVariableUsage(CHTLParser.VariableUsageContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#variableUsage}.
	 * @param ctx the parse tree
	 */
	void exitVariableUsage(CHTLParser.VariableUsageContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#variableArguments}.
	 * @param ctx the parse tree
	 */
	void enterVariableArguments(CHTLParser.VariableArgumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#variableArguments}.
	 * @param ctx the parse tree
	 */
	void exitVariableArguments(CHTLParser.VariableArgumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#variableArgument}.
	 * @param ctx the parse tree
	 */
	void enterVariableArgument(CHTLParser.VariableArgumentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#variableArgument}.
	 * @param ctx the parse tree
	 */
	void exitVariableArgument(CHTLParser.VariableArgumentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#variableAssignment}.
	 * @param ctx the parse tree
	 */
	void enterVariableAssignment(CHTLParser.VariableAssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#variableAssignment}.
	 * @param ctx the parse tree
	 */
	void exitVariableAssignment(CHTLParser.VariableAssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#namespacePath}.
	 * @param ctx the parse tree
	 */
	void enterNamespacePath(CHTLParser.NamespacePathContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#namespacePath}.
	 * @param ctx the parse tree
	 */
	void exitNamespacePath(CHTLParser.NamespacePathContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#exceptConstraint}.
	 * @param ctx the parse tree
	 */
	void enterExceptConstraint(CHTLParser.ExceptConstraintContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#exceptConstraint}.
	 * @param ctx the parse tree
	 */
	void exitExceptConstraint(CHTLParser.ExceptConstraintContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#exceptTarget}.
	 * @param ctx the parse tree
	 */
	void enterExceptTarget(CHTLParser.ExceptTargetContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#exceptTarget}.
	 * @param ctx the parse tree
	 */
	void exitExceptTarget(CHTLParser.ExceptTargetContext ctx);
	/**
	 * Enter a parse tree produced by {@link CHTLParser#comment}.
	 * @param ctx the parse tree
	 */
	void enterComment(CHTLParser.CommentContext ctx);
	/**
	 * Exit a parse tree produced by {@link CHTLParser#comment}.
	 * @param ctx the parse tree
	 */
	void exitComment(CHTLParser.CommentContext ctx);
}