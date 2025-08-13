
// Generated from CHTL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CHTLParser.
 */
class  CHTLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(CHTLParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(CHTLParser::ProgramContext *ctx) = 0;

  virtual void enterTopLevelStatement(CHTLParser::TopLevelStatementContext *ctx) = 0;
  virtual void exitTopLevelStatement(CHTLParser::TopLevelStatementContext *ctx) = 0;

  virtual void enterConfigurationBlock(CHTLParser::ConfigurationBlockContext *ctx) = 0;
  virtual void exitConfigurationBlock(CHTLParser::ConfigurationBlockContext *ctx) = 0;

  virtual void enterConfigurationItem(CHTLParser::ConfigurationItemContext *ctx) = 0;
  virtual void exitConfigurationItem(CHTLParser::ConfigurationItemContext *ctx) = 0;

  virtual void enterConfigKey(CHTLParser::ConfigKeyContext *ctx) = 0;
  virtual void exitConfigKey(CHTLParser::ConfigKeyContext *ctx) = 0;

  virtual void enterConfigValue(CHTLParser::ConfigValueContext *ctx) = 0;
  virtual void exitConfigValue(CHTLParser::ConfigValueContext *ctx) = 0;

  virtual void enterConfigValueArray(CHTLParser::ConfigValueArrayContext *ctx) = 0;
  virtual void exitConfigValueArray(CHTLParser::ConfigValueArrayContext *ctx) = 0;

  virtual void enterConfigArrayItem(CHTLParser::ConfigArrayItemContext *ctx) = 0;
  virtual void exitConfigArrayItem(CHTLParser::ConfigArrayItemContext *ctx) = 0;

  virtual void enterNameConfigItem(CHTLParser::NameConfigItemContext *ctx) = 0;
  virtual void exitNameConfigItem(CHTLParser::NameConfigItemContext *ctx) = 0;

  virtual void enterNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext *ctx) = 0;
  virtual void exitNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext *ctx) = 0;

  virtual void enterNamespaceBody(CHTLParser::NamespaceBodyContext *ctx) = 0;
  virtual void exitNamespaceBody(CHTLParser::NamespaceBodyContext *ctx) = 0;

  virtual void enterNamespaceContent(CHTLParser::NamespaceContentContext *ctx) = 0;
  virtual void exitNamespaceContent(CHTLParser::NamespaceContentContext *ctx) = 0;

  virtual void enterImportStatement(CHTLParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(CHTLParser::ImportStatementContext *ctx) = 0;

  virtual void enterImportType(CHTLParser::ImportTypeContext *ctx) = 0;
  virtual void exitImportType(CHTLParser::ImportTypeContext *ctx) = 0;

  virtual void enterImportPath(CHTLParser::ImportPathContext *ctx) = 0;
  virtual void exitImportPath(CHTLParser::ImportPathContext *ctx) = 0;

  virtual void enterDottedPath(CHTLParser::DottedPathContext *ctx) = 0;
  virtual void exitDottedPath(CHTLParser::DottedPathContext *ctx) = 0;

  virtual void enterTemplateDeclaration(CHTLParser::TemplateDeclarationContext *ctx) = 0;
  virtual void exitTemplateDeclaration(CHTLParser::TemplateDeclarationContext *ctx) = 0;

  virtual void enterTemplateType(CHTLParser::TemplateTypeContext *ctx) = 0;
  virtual void exitTemplateType(CHTLParser::TemplateTypeContext *ctx) = 0;

  virtual void enterTemplateBody(CHTLParser::TemplateBodyContext *ctx) = 0;
  virtual void exitTemplateBody(CHTLParser::TemplateBodyContext *ctx) = 0;

  virtual void enterTemplateContent(CHTLParser::TemplateContentContext *ctx) = 0;
  virtual void exitTemplateContent(CHTLParser::TemplateContentContext *ctx) = 0;

  virtual void enterTemplateInheritance(CHTLParser::TemplateInheritanceContext *ctx) = 0;
  virtual void exitTemplateInheritance(CHTLParser::TemplateInheritanceContext *ctx) = 0;

  virtual void enterCustomDeclaration(CHTLParser::CustomDeclarationContext *ctx) = 0;
  virtual void exitCustomDeclaration(CHTLParser::CustomDeclarationContext *ctx) = 0;

  virtual void enterCustomType(CHTLParser::CustomTypeContext *ctx) = 0;
  virtual void exitCustomType(CHTLParser::CustomTypeContext *ctx) = 0;

  virtual void enterCustomBody(CHTLParser::CustomBodyContext *ctx) = 0;
  virtual void exitCustomBody(CHTLParser::CustomBodyContext *ctx) = 0;

  virtual void enterCustomContent(CHTLParser::CustomContentContext *ctx) = 0;
  virtual void exitCustomContent(CHTLParser::CustomContentContext *ctx) = 0;

  virtual void enterCustomInheritance(CHTLParser::CustomInheritanceContext *ctx) = 0;
  virtual void exitCustomInheritance(CHTLParser::CustomInheritanceContext *ctx) = 0;

  virtual void enterCustomSpecialization(CHTLParser::CustomSpecializationContext *ctx) = 0;
  virtual void exitCustomSpecialization(CHTLParser::CustomSpecializationContext *ctx) = 0;

  virtual void enterSpecializationContent(CHTLParser::SpecializationContentContext *ctx) = 0;
  virtual void exitSpecializationContent(CHTLParser::SpecializationContentContext *ctx) = 0;

  virtual void enterDeleteStatement(CHTLParser::DeleteStatementContext *ctx) = 0;
  virtual void exitDeleteStatement(CHTLParser::DeleteStatementContext *ctx) = 0;

  virtual void enterDeleteTarget(CHTLParser::DeleteTargetContext *ctx) = 0;
  virtual void exitDeleteTarget(CHTLParser::DeleteTargetContext *ctx) = 0;

  virtual void enterInsertStatement(CHTLParser::InsertStatementContext *ctx) = 0;
  virtual void exitInsertStatement(CHTLParser::InsertStatementContext *ctx) = 0;

  virtual void enterInsertPosition(CHTLParser::InsertPositionContext *ctx) = 0;
  virtual void exitInsertPosition(CHTLParser::InsertPositionContext *ctx) = 0;

  virtual void enterElementSelector(CHTLParser::ElementSelectorContext *ctx) = 0;
  virtual void exitElementSelector(CHTLParser::ElementSelectorContext *ctx) = 0;

  virtual void enterInsertContent(CHTLParser::InsertContentContext *ctx) = 0;
  virtual void exitInsertContent(CHTLParser::InsertContentContext *ctx) = 0;

  virtual void enterOriginBlock(CHTLParser::OriginBlockContext *ctx) = 0;
  virtual void exitOriginBlock(CHTLParser::OriginBlockContext *ctx) = 0;

  virtual void enterOriginType(CHTLParser::OriginTypeContext *ctx) = 0;
  virtual void exitOriginType(CHTLParser::OriginTypeContext *ctx) = 0;

  virtual void enterOriginContent(CHTLParser::OriginContentContext *ctx) = 0;
  virtual void exitOriginContent(CHTLParser::OriginContentContext *ctx) = 0;

  virtual void enterHtmlElement(CHTLParser::HtmlElementContext *ctx) = 0;
  virtual void exitHtmlElement(CHTLParser::HtmlElementContext *ctx) = 0;

  virtual void enterElementName(CHTLParser::ElementNameContext *ctx) = 0;
  virtual void exitElementName(CHTLParser::ElementNameContext *ctx) = 0;

  virtual void enterElementIndexAccess(CHTLParser::ElementIndexAccessContext *ctx) = 0;
  virtual void exitElementIndexAccess(CHTLParser::ElementIndexAccessContext *ctx) = 0;

  virtual void enterElementBody(CHTLParser::ElementBodyContext *ctx) = 0;
  virtual void exitElementBody(CHTLParser::ElementBodyContext *ctx) = 0;

  virtual void enterElementContent(CHTLParser::ElementContentContext *ctx) = 0;
  virtual void exitElementContent(CHTLParser::ElementContentContext *ctx) = 0;

  virtual void enterAttribute(CHTLParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(CHTLParser::AttributeContext *ctx) = 0;

  virtual void enterAttributeName(CHTLParser::AttributeNameContext *ctx) = 0;
  virtual void exitAttributeName(CHTLParser::AttributeNameContext *ctx) = 0;

  virtual void enterAttributeValue(CHTLParser::AttributeValueContext *ctx) = 0;
  virtual void exitAttributeValue(CHTLParser::AttributeValueContext *ctx) = 0;

  virtual void enterTextContent(CHTLParser::TextContentContext *ctx) = 0;
  virtual void exitTextContent(CHTLParser::TextContentContext *ctx) = 0;

  virtual void enterStyleBlock(CHTLParser::StyleBlockContext *ctx) = 0;
  virtual void exitStyleBlock(CHTLParser::StyleBlockContext *ctx) = 0;

  virtual void enterStyleContent(CHTLParser::StyleContentContext *ctx) = 0;
  virtual void exitStyleContent(CHTLParser::StyleContentContext *ctx) = 0;

  virtual void enterStyleProperty(CHTLParser::StylePropertyContext *ctx) = 0;
  virtual void exitStyleProperty(CHTLParser::StylePropertyContext *ctx) = 0;

  virtual void enterPropertyName(CHTLParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(CHTLParser::PropertyNameContext *ctx) = 0;

  virtual void enterPropertyValue(CHTLParser::PropertyValueContext *ctx) = 0;
  virtual void exitPropertyValue(CHTLParser::PropertyValueContext *ctx) = 0;

  virtual void enterCssSelector(CHTLParser::CssSelectorContext *ctx) = 0;
  virtual void exitCssSelector(CHTLParser::CssSelectorContext *ctx) = 0;

  virtual void enterPseudoClass(CHTLParser::PseudoClassContext *ctx) = 0;
  virtual void exitPseudoClass(CHTLParser::PseudoClassContext *ctx) = 0;

  virtual void enterPseudoElement(CHTLParser::PseudoElementContext *ctx) = 0;
  virtual void exitPseudoElement(CHTLParser::PseudoElementContext *ctx) = 0;

  virtual void enterCssFunction(CHTLParser::CssFunctionContext *ctx) = 0;
  virtual void exitCssFunction(CHTLParser::CssFunctionContext *ctx) = 0;

  virtual void enterCssArguments(CHTLParser::CssArgumentsContext *ctx) = 0;
  virtual void exitCssArguments(CHTLParser::CssArgumentsContext *ctx) = 0;

  virtual void enterCssArgument(CHTLParser::CssArgumentContext *ctx) = 0;
  virtual void exitCssArgument(CHTLParser::CssArgumentContext *ctx) = 0;

  virtual void enterScriptBlock(CHTLParser::ScriptBlockContext *ctx) = 0;
  virtual void exitScriptBlock(CHTLParser::ScriptBlockContext *ctx) = 0;

  virtual void enterScriptContent(CHTLParser::ScriptContentContext *ctx) = 0;
  virtual void exitScriptContent(CHTLParser::ScriptContentContext *ctx) = 0;

  virtual void enterElementUsage(CHTLParser::ElementUsageContext *ctx) = 0;
  virtual void exitElementUsage(CHTLParser::ElementUsageContext *ctx) = 0;

  virtual void enterElementSpecialization(CHTLParser::ElementSpecializationContext *ctx) = 0;
  virtual void exitElementSpecialization(CHTLParser::ElementSpecializationContext *ctx) = 0;

  virtual void enterElementSpecializationContent(CHTLParser::ElementSpecializationContentContext *ctx) = 0;
  virtual void exitElementSpecializationContent(CHTLParser::ElementSpecializationContentContext *ctx) = 0;

  virtual void enterStyleUsage(CHTLParser::StyleUsageContext *ctx) = 0;
  virtual void exitStyleUsage(CHTLParser::StyleUsageContext *ctx) = 0;

  virtual void enterStyleSpecialization(CHTLParser::StyleSpecializationContext *ctx) = 0;
  virtual void exitStyleSpecialization(CHTLParser::StyleSpecializationContext *ctx) = 0;

  virtual void enterVariableDefinition(CHTLParser::VariableDefinitionContext *ctx) = 0;
  virtual void exitVariableDefinition(CHTLParser::VariableDefinitionContext *ctx) = 0;

  virtual void enterVariableUsage(CHTLParser::VariableUsageContext *ctx) = 0;
  virtual void exitVariableUsage(CHTLParser::VariableUsageContext *ctx) = 0;

  virtual void enterVariableArguments(CHTLParser::VariableArgumentsContext *ctx) = 0;
  virtual void exitVariableArguments(CHTLParser::VariableArgumentsContext *ctx) = 0;

  virtual void enterVariableArgument(CHTLParser::VariableArgumentContext *ctx) = 0;
  virtual void exitVariableArgument(CHTLParser::VariableArgumentContext *ctx) = 0;

  virtual void enterVariableAssignment(CHTLParser::VariableAssignmentContext *ctx) = 0;
  virtual void exitVariableAssignment(CHTLParser::VariableAssignmentContext *ctx) = 0;

  virtual void enterNamespacePath(CHTLParser::NamespacePathContext *ctx) = 0;
  virtual void exitNamespacePath(CHTLParser::NamespacePathContext *ctx) = 0;

  virtual void enterExceptConstraint(CHTLParser::ExceptConstraintContext *ctx) = 0;
  virtual void exitExceptConstraint(CHTLParser::ExceptConstraintContext *ctx) = 0;

  virtual void enterExceptTarget(CHTLParser::ExceptTargetContext *ctx) = 0;
  virtual void exitExceptTarget(CHTLParser::ExceptTargetContext *ctx) = 0;

  virtual void enterComment(CHTLParser::CommentContext *ctx) = 0;
  virtual void exitComment(CHTLParser::CommentContext *ctx) = 0;


};

