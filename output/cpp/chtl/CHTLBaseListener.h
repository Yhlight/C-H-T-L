
// Generated from CHTL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTLListener.h"


/**
 * This class provides an empty implementation of CHTLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CHTLBaseListener : public CHTLListener {
public:

  virtual void enterProgram(CHTLParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(CHTLParser::ProgramContext * /*ctx*/) override { }

  virtual void enterTopLevelStatement(CHTLParser::TopLevelStatementContext * /*ctx*/) override { }
  virtual void exitTopLevelStatement(CHTLParser::TopLevelStatementContext * /*ctx*/) override { }

  virtual void enterConfigurationBlock(CHTLParser::ConfigurationBlockContext * /*ctx*/) override { }
  virtual void exitConfigurationBlock(CHTLParser::ConfigurationBlockContext * /*ctx*/) override { }

  virtual void enterConfigurationItem(CHTLParser::ConfigurationItemContext * /*ctx*/) override { }
  virtual void exitConfigurationItem(CHTLParser::ConfigurationItemContext * /*ctx*/) override { }

  virtual void enterConfigKey(CHTLParser::ConfigKeyContext * /*ctx*/) override { }
  virtual void exitConfigKey(CHTLParser::ConfigKeyContext * /*ctx*/) override { }

  virtual void enterConfigValue(CHTLParser::ConfigValueContext * /*ctx*/) override { }
  virtual void exitConfigValue(CHTLParser::ConfigValueContext * /*ctx*/) override { }

  virtual void enterConfigValueArray(CHTLParser::ConfigValueArrayContext * /*ctx*/) override { }
  virtual void exitConfigValueArray(CHTLParser::ConfigValueArrayContext * /*ctx*/) override { }

  virtual void enterConfigArrayItem(CHTLParser::ConfigArrayItemContext * /*ctx*/) override { }
  virtual void exitConfigArrayItem(CHTLParser::ConfigArrayItemContext * /*ctx*/) override { }

  virtual void enterNameConfigItem(CHTLParser::NameConfigItemContext * /*ctx*/) override { }
  virtual void exitNameConfigItem(CHTLParser::NameConfigItemContext * /*ctx*/) override { }

  virtual void enterNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext * /*ctx*/) override { }
  virtual void exitNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext * /*ctx*/) override { }

  virtual void enterNamespaceBody(CHTLParser::NamespaceBodyContext * /*ctx*/) override { }
  virtual void exitNamespaceBody(CHTLParser::NamespaceBodyContext * /*ctx*/) override { }

  virtual void enterNamespaceContent(CHTLParser::NamespaceContentContext * /*ctx*/) override { }
  virtual void exitNamespaceContent(CHTLParser::NamespaceContentContext * /*ctx*/) override { }

  virtual void enterImportStatement(CHTLParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(CHTLParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterImportType(CHTLParser::ImportTypeContext * /*ctx*/) override { }
  virtual void exitImportType(CHTLParser::ImportTypeContext * /*ctx*/) override { }

  virtual void enterImportPath(CHTLParser::ImportPathContext * /*ctx*/) override { }
  virtual void exitImportPath(CHTLParser::ImportPathContext * /*ctx*/) override { }

  virtual void enterDottedPath(CHTLParser::DottedPathContext * /*ctx*/) override { }
  virtual void exitDottedPath(CHTLParser::DottedPathContext * /*ctx*/) override { }

  virtual void enterTemplateDeclaration(CHTLParser::TemplateDeclarationContext * /*ctx*/) override { }
  virtual void exitTemplateDeclaration(CHTLParser::TemplateDeclarationContext * /*ctx*/) override { }

  virtual void enterTemplateType(CHTLParser::TemplateTypeContext * /*ctx*/) override { }
  virtual void exitTemplateType(CHTLParser::TemplateTypeContext * /*ctx*/) override { }

  virtual void enterTemplateBody(CHTLParser::TemplateBodyContext * /*ctx*/) override { }
  virtual void exitTemplateBody(CHTLParser::TemplateBodyContext * /*ctx*/) override { }

  virtual void enterTemplateContent(CHTLParser::TemplateContentContext * /*ctx*/) override { }
  virtual void exitTemplateContent(CHTLParser::TemplateContentContext * /*ctx*/) override { }

  virtual void enterTemplateInheritance(CHTLParser::TemplateInheritanceContext * /*ctx*/) override { }
  virtual void exitTemplateInheritance(CHTLParser::TemplateInheritanceContext * /*ctx*/) override { }

  virtual void enterCustomDeclaration(CHTLParser::CustomDeclarationContext * /*ctx*/) override { }
  virtual void exitCustomDeclaration(CHTLParser::CustomDeclarationContext * /*ctx*/) override { }

  virtual void enterCustomType(CHTLParser::CustomTypeContext * /*ctx*/) override { }
  virtual void exitCustomType(CHTLParser::CustomTypeContext * /*ctx*/) override { }

  virtual void enterCustomBody(CHTLParser::CustomBodyContext * /*ctx*/) override { }
  virtual void exitCustomBody(CHTLParser::CustomBodyContext * /*ctx*/) override { }

  virtual void enterCustomContent(CHTLParser::CustomContentContext * /*ctx*/) override { }
  virtual void exitCustomContent(CHTLParser::CustomContentContext * /*ctx*/) override { }

  virtual void enterCustomInheritance(CHTLParser::CustomInheritanceContext * /*ctx*/) override { }
  virtual void exitCustomInheritance(CHTLParser::CustomInheritanceContext * /*ctx*/) override { }

  virtual void enterCustomSpecialization(CHTLParser::CustomSpecializationContext * /*ctx*/) override { }
  virtual void exitCustomSpecialization(CHTLParser::CustomSpecializationContext * /*ctx*/) override { }

  virtual void enterSpecializationContent(CHTLParser::SpecializationContentContext * /*ctx*/) override { }
  virtual void exitSpecializationContent(CHTLParser::SpecializationContentContext * /*ctx*/) override { }

  virtual void enterDeleteStatement(CHTLParser::DeleteStatementContext * /*ctx*/) override { }
  virtual void exitDeleteStatement(CHTLParser::DeleteStatementContext * /*ctx*/) override { }

  virtual void enterDeleteTarget(CHTLParser::DeleteTargetContext * /*ctx*/) override { }
  virtual void exitDeleteTarget(CHTLParser::DeleteTargetContext * /*ctx*/) override { }

  virtual void enterInsertStatement(CHTLParser::InsertStatementContext * /*ctx*/) override { }
  virtual void exitInsertStatement(CHTLParser::InsertStatementContext * /*ctx*/) override { }

  virtual void enterInsertPosition(CHTLParser::InsertPositionContext * /*ctx*/) override { }
  virtual void exitInsertPosition(CHTLParser::InsertPositionContext * /*ctx*/) override { }

  virtual void enterElementSelector(CHTLParser::ElementSelectorContext * /*ctx*/) override { }
  virtual void exitElementSelector(CHTLParser::ElementSelectorContext * /*ctx*/) override { }

  virtual void enterInsertContent(CHTLParser::InsertContentContext * /*ctx*/) override { }
  virtual void exitInsertContent(CHTLParser::InsertContentContext * /*ctx*/) override { }

  virtual void enterOriginBlock(CHTLParser::OriginBlockContext * /*ctx*/) override { }
  virtual void exitOriginBlock(CHTLParser::OriginBlockContext * /*ctx*/) override { }

  virtual void enterOriginType(CHTLParser::OriginTypeContext * /*ctx*/) override { }
  virtual void exitOriginType(CHTLParser::OriginTypeContext * /*ctx*/) override { }

  virtual void enterOriginContent(CHTLParser::OriginContentContext * /*ctx*/) override { }
  virtual void exitOriginContent(CHTLParser::OriginContentContext * /*ctx*/) override { }

  virtual void enterHtmlElement(CHTLParser::HtmlElementContext * /*ctx*/) override { }
  virtual void exitHtmlElement(CHTLParser::HtmlElementContext * /*ctx*/) override { }

  virtual void enterGlobalStyleElement(CHTLParser::GlobalStyleElementContext * /*ctx*/) override { }
  virtual void exitGlobalStyleElement(CHTLParser::GlobalStyleElementContext * /*ctx*/) override { }

  virtual void enterGlobalStyleContent(CHTLParser::GlobalStyleContentContext * /*ctx*/) override { }
  virtual void exitGlobalStyleContent(CHTLParser::GlobalStyleContentContext * /*ctx*/) override { }

  virtual void enterElementName(CHTLParser::ElementNameContext * /*ctx*/) override { }
  virtual void exitElementName(CHTLParser::ElementNameContext * /*ctx*/) override { }

  virtual void enterElementIndexAccess(CHTLParser::ElementIndexAccessContext * /*ctx*/) override { }
  virtual void exitElementIndexAccess(CHTLParser::ElementIndexAccessContext * /*ctx*/) override { }

  virtual void enterElementBody(CHTLParser::ElementBodyContext * /*ctx*/) override { }
  virtual void exitElementBody(CHTLParser::ElementBodyContext * /*ctx*/) override { }

  virtual void enterElementContent(CHTLParser::ElementContentContext * /*ctx*/) override { }
  virtual void exitElementContent(CHTLParser::ElementContentContext * /*ctx*/) override { }

  virtual void enterAttribute(CHTLParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(CHTLParser::AttributeContext * /*ctx*/) override { }

  virtual void enterAttributeName(CHTLParser::AttributeNameContext * /*ctx*/) override { }
  virtual void exitAttributeName(CHTLParser::AttributeNameContext * /*ctx*/) override { }

  virtual void enterAttributeValue(CHTLParser::AttributeValueContext * /*ctx*/) override { }
  virtual void exitAttributeValue(CHTLParser::AttributeValueContext * /*ctx*/) override { }

  virtual void enterTextContent(CHTLParser::TextContentContext * /*ctx*/) override { }
  virtual void exitTextContent(CHTLParser::TextContentContext * /*ctx*/) override { }

  virtual void enterStyleBlock(CHTLParser::StyleBlockContext * /*ctx*/) override { }
  virtual void exitStyleBlock(CHTLParser::StyleBlockContext * /*ctx*/) override { }

  virtual void enterStyleContent(CHTLParser::StyleContentContext * /*ctx*/) override { }
  virtual void exitStyleContent(CHTLParser::StyleContentContext * /*ctx*/) override { }

  virtual void enterStyleProperty(CHTLParser::StylePropertyContext * /*ctx*/) override { }
  virtual void exitStyleProperty(CHTLParser::StylePropertyContext * /*ctx*/) override { }

  virtual void enterPropertyName(CHTLParser::PropertyNameContext * /*ctx*/) override { }
  virtual void exitPropertyName(CHTLParser::PropertyNameContext * /*ctx*/) override { }

  virtual void enterPropertyValue(CHTLParser::PropertyValueContext * /*ctx*/) override { }
  virtual void exitPropertyValue(CHTLParser::PropertyValueContext * /*ctx*/) override { }

  virtual void enterCssSelector(CHTLParser::CssSelectorContext * /*ctx*/) override { }
  virtual void exitCssSelector(CHTLParser::CssSelectorContext * /*ctx*/) override { }

  virtual void enterPseudoClass(CHTLParser::PseudoClassContext * /*ctx*/) override { }
  virtual void exitPseudoClass(CHTLParser::PseudoClassContext * /*ctx*/) override { }

  virtual void enterPseudoElement(CHTLParser::PseudoElementContext * /*ctx*/) override { }
  virtual void exitPseudoElement(CHTLParser::PseudoElementContext * /*ctx*/) override { }

  virtual void enterCssFunction(CHTLParser::CssFunctionContext * /*ctx*/) override { }
  virtual void exitCssFunction(CHTLParser::CssFunctionContext * /*ctx*/) override { }

  virtual void enterCssArguments(CHTLParser::CssArgumentsContext * /*ctx*/) override { }
  virtual void exitCssArguments(CHTLParser::CssArgumentsContext * /*ctx*/) override { }

  virtual void enterCssArgument(CHTLParser::CssArgumentContext * /*ctx*/) override { }
  virtual void exitCssArgument(CHTLParser::CssArgumentContext * /*ctx*/) override { }

  virtual void enterScriptBlock(CHTLParser::ScriptBlockContext * /*ctx*/) override { }
  virtual void exitScriptBlock(CHTLParser::ScriptBlockContext * /*ctx*/) override { }

  virtual void enterScriptContent(CHTLParser::ScriptContentContext * /*ctx*/) override { }
  virtual void exitScriptContent(CHTLParser::ScriptContentContext * /*ctx*/) override { }

  virtual void enterElementUsage(CHTLParser::ElementUsageContext * /*ctx*/) override { }
  virtual void exitElementUsage(CHTLParser::ElementUsageContext * /*ctx*/) override { }

  virtual void enterElementSpecialization(CHTLParser::ElementSpecializationContext * /*ctx*/) override { }
  virtual void exitElementSpecialization(CHTLParser::ElementSpecializationContext * /*ctx*/) override { }

  virtual void enterElementSpecializationContent(CHTLParser::ElementSpecializationContentContext * /*ctx*/) override { }
  virtual void exitElementSpecializationContent(CHTLParser::ElementSpecializationContentContext * /*ctx*/) override { }

  virtual void enterStyleUsage(CHTLParser::StyleUsageContext * /*ctx*/) override { }
  virtual void exitStyleUsage(CHTLParser::StyleUsageContext * /*ctx*/) override { }

  virtual void enterStyleSpecialization(CHTLParser::StyleSpecializationContext * /*ctx*/) override { }
  virtual void exitStyleSpecialization(CHTLParser::StyleSpecializationContext * /*ctx*/) override { }

  virtual void enterVariableDefinition(CHTLParser::VariableDefinitionContext * /*ctx*/) override { }
  virtual void exitVariableDefinition(CHTLParser::VariableDefinitionContext * /*ctx*/) override { }

  virtual void enterVariableUsage(CHTLParser::VariableUsageContext * /*ctx*/) override { }
  virtual void exitVariableUsage(CHTLParser::VariableUsageContext * /*ctx*/) override { }

  virtual void enterVariableArguments(CHTLParser::VariableArgumentsContext * /*ctx*/) override { }
  virtual void exitVariableArguments(CHTLParser::VariableArgumentsContext * /*ctx*/) override { }

  virtual void enterVariableArgument(CHTLParser::VariableArgumentContext * /*ctx*/) override { }
  virtual void exitVariableArgument(CHTLParser::VariableArgumentContext * /*ctx*/) override { }

  virtual void enterVariableAssignment(CHTLParser::VariableAssignmentContext * /*ctx*/) override { }
  virtual void exitVariableAssignment(CHTLParser::VariableAssignmentContext * /*ctx*/) override { }

  virtual void enterNamespacePath(CHTLParser::NamespacePathContext * /*ctx*/) override { }
  virtual void exitNamespacePath(CHTLParser::NamespacePathContext * /*ctx*/) override { }

  virtual void enterExceptConstraint(CHTLParser::ExceptConstraintContext * /*ctx*/) override { }
  virtual void exitExceptConstraint(CHTLParser::ExceptConstraintContext * /*ctx*/) override { }

  virtual void enterExceptTarget(CHTLParser::ExceptTargetContext * /*ctx*/) override { }
  virtual void exitExceptTarget(CHTLParser::ExceptTargetContext * /*ctx*/) override { }

  virtual void enterComment(CHTLParser::CommentContext * /*ctx*/) override { }
  virtual void exitComment(CHTLParser::CommentContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

