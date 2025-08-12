
// Generated from /workspace/grammar/CHTL.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "CHTLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CHTLParser.
 */
class  CHTLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CHTLParser.
   */
    virtual std::any visitProgram(CHTLParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(CHTLParser::StatementContext *context) = 0;

    virtual std::any visitComment(CHTLParser::CommentContext *context) = 0;

    virtual std::any visitTextNode(CHTLParser::TextNodeContext *context) = 0;

    virtual std::any visitStringLiteral(CHTLParser::StringLiteralContext *context) = 0;

    virtual std::any visitElement(CHTLParser::ElementContext *context) = 0;

    virtual std::any visitElementName(CHTLParser::ElementNameContext *context) = 0;

    virtual std::any visitElementBody(CHTLParser::ElementBodyContext *context) = 0;

    virtual std::any visitElementContent(CHTLParser::ElementContentContext *context) = 0;

    virtual std::any visitAttribute(CHTLParser::AttributeContext *context) = 0;

    virtual std::any visitAttributeName(CHTLParser::AttributeNameContext *context) = 0;

    virtual std::any visitAttributeValue(CHTLParser::AttributeValueContext *context) = 0;

    virtual std::any visitStyleBlock(CHTLParser::StyleBlockContext *context) = 0;

    virtual std::any visitStyleContent(CHTLParser::StyleContentContext *context) = 0;

    virtual std::any visitCssProperty(CHTLParser::CssPropertyContext *context) = 0;

    virtual std::any visitCssPropertyName(CHTLParser::CssPropertyNameContext *context) = 0;

    virtual std::any visitCssPropertyValue(CHTLParser::CssPropertyValueContext *context) = 0;

    virtual std::any visitCssValue(CHTLParser::CssValueContext *context) = 0;

    virtual std::any visitCssSelector(CHTLParser::CssSelectorContext *context) = 0;

    virtual std::any visitSelectorPattern(CHTLParser::SelectorPatternContext *context) = 0;

    virtual std::any visitClassSelector(CHTLParser::ClassSelectorContext *context) = 0;

    virtual std::any visitIdSelector(CHTLParser::IdSelectorContext *context) = 0;

    virtual std::any visitAmpersandSelector(CHTLParser::AmpersandSelectorContext *context) = 0;

    virtual std::any visitPseudoSelector(CHTLParser::PseudoSelectorContext *context) = 0;

    virtual std::any visitScriptBlock(CHTLParser::ScriptBlockContext *context) = 0;

    virtual std::any visitJsCode(CHTLParser::JsCodeContext *context) = 0;

    virtual std::any visitTemplateDeclaration(CHTLParser::TemplateDeclarationContext *context) = 0;

    virtual std::any visitTemplateType(CHTLParser::TemplateTypeContext *context) = 0;

    virtual std::any visitTemplateName(CHTLParser::TemplateNameContext *context) = 0;

    virtual std::any visitTemplateBody(CHTLParser::TemplateBodyContext *context) = 0;

    virtual std::any visitTemplateContent(CHTLParser::TemplateContentContext *context) = 0;

    virtual std::any visitVarDeclaration(CHTLParser::VarDeclarationContext *context) = 0;

    virtual std::any visitCustomDeclaration(CHTLParser::CustomDeclarationContext *context) = 0;

    virtual std::any visitCustomType(CHTLParser::CustomTypeContext *context) = 0;

    virtual std::any visitCustomName(CHTLParser::CustomNameContext *context) = 0;

    virtual std::any visitCustomBody(CHTLParser::CustomBodyContext *context) = 0;

    virtual std::any visitCustomContent(CHTLParser::CustomContentContext *context) = 0;

    virtual std::any visitCssPropertyWithoutValue(CHTLParser::CssPropertyWithoutValueContext *context) = 0;

    virtual std::any visitTemplateUsage(CHTLParser::TemplateUsageContext *context) = 0;

    virtual std::any visitTemplateSpecialization(CHTLParser::TemplateSpecializationContext *context) = 0;

    virtual std::any visitSpecializationContent(CHTLParser::SpecializationContentContext *context) = 0;

    virtual std::any visitVarAssignment(CHTLParser::VarAssignmentContext *context) = 0;

    virtual std::any visitCustomUsage(CHTLParser::CustomUsageContext *context) = 0;

    virtual std::any visitCustomSpecialization(CHTLParser::CustomSpecializationContext *context) = 0;

    virtual std::any visitInheritStatement(CHTLParser::InheritStatementContext *context) = 0;

    virtual std::any visitDeleteStatement(CHTLParser::DeleteStatementContext *context) = 0;

    virtual std::any visitDeleteTarget(CHTLParser::DeleteTargetContext *context) = 0;

    virtual std::any visitElementIndex(CHTLParser::ElementIndexContext *context) = 0;

    virtual std::any visitInsertStatement(CHTLParser::InsertStatementContext *context) = 0;

    virtual std::any visitInsertPosition(CHTLParser::InsertPositionContext *context) = 0;

    virtual std::any visitInsertTarget(CHTLParser::InsertTargetContext *context) = 0;

    virtual std::any visitInsertContent(CHTLParser::InsertContentContext *context) = 0;

    virtual std::any visitExceptStatement(CHTLParser::ExceptStatementContext *context) = 0;

    virtual std::any visitExceptTarget(CHTLParser::ExceptTargetContext *context) = 0;

    virtual std::any visitOriginBlock(CHTLParser::OriginBlockContext *context) = 0;

    virtual std::any visitOriginType(CHTLParser::OriginTypeContext *context) = 0;

    virtual std::any visitOriginName(CHTLParser::OriginNameContext *context) = 0;

    virtual std::any visitOriginBody(CHTLParser::OriginBodyContext *context) = 0;

    virtual std::any visitRawContent(CHTLParser::RawContentContext *context) = 0;

    virtual std::any visitImportStatement(CHTLParser::ImportStatementContext *context) = 0;

    virtual std::any visitImportContent(CHTLParser::ImportContentContext *context) = 0;

    virtual std::any visitImportHtml(CHTLParser::ImportHtmlContext *context) = 0;

    virtual std::any visitImportCss(CHTLParser::ImportCssContext *context) = 0;

    virtual std::any visitImportJs(CHTLParser::ImportJsContext *context) = 0;

    virtual std::any visitImportChtl(CHTLParser::ImportChtlContext *context) = 0;

    virtual std::any visitImportCustom(CHTLParser::ImportCustomContext *context) = 0;

    virtual std::any visitImportTemplate(CHTLParser::ImportTemplateContext *context) = 0;

    virtual std::any visitFilePath(CHTLParser::FilePathContext *context) = 0;

    virtual std::any visitNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext *context) = 0;

    virtual std::any visitNamespaceName(CHTLParser::NamespaceNameContext *context) = 0;

    virtual std::any visitNamespaceBody(CHTLParser::NamespaceBodyContext *context) = 0;

    virtual std::any visitNamespaceContent(CHTLParser::NamespaceContentContext *context) = 0;

    virtual std::any visitConfigurationBlock(CHTLParser::ConfigurationBlockContext *context) = 0;

    virtual std::any visitConfigContent(CHTLParser::ConfigContentContext *context) = 0;

    virtual std::any visitConfigAssignment(CHTLParser::ConfigAssignmentContext *context) = 0;

    virtual std::any visitConfigValue(CHTLParser::ConfigValueContext *context) = 0;

    virtual std::any visitNameBlock(CHTLParser::NameBlockContext *context) = 0;

    virtual std::any visitNameAssignment(CHTLParser::NameAssignmentContext *context) = 0;


};

