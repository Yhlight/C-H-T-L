
// Generated from /workspace/grammar/CHTL.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "CHTLVisitor.h"


/**
 * This class provides an empty implementation of CHTLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CHTLBaseVisitor : public CHTLVisitor {
public:

  virtual std::any visitProgram(CHTLParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(CHTLParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComment(CHTLParser::CommentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTextNode(CHTLParser::TextNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteral(CHTLParser::StringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(CHTLParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementName(CHTLParser::ElementNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementBody(CHTLParser::ElementBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementContent(CHTLParser::ElementContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttribute(CHTLParser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeName(CHTLParser::AttributeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttributeValue(CHTLParser::AttributeValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStyleBlock(CHTLParser::StyleBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStyleContent(CHTLParser::StyleContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssProperty(CHTLParser::CssPropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssPropertyName(CHTLParser::CssPropertyNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssPropertyValue(CHTLParser::CssPropertyValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssValue(CHTLParser::CssValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssSelector(CHTLParser::CssSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectorPattern(CHTLParser::SelectorPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassSelector(CHTLParser::ClassSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdSelector(CHTLParser::IdSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAmpersandSelector(CHTLParser::AmpersandSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPseudoSelector(CHTLParser::PseudoSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScriptBlock(CHTLParser::ScriptBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJsCode(CHTLParser::JsCodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateDeclaration(CHTLParser::TemplateDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateType(CHTLParser::TemplateTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateName(CHTLParser::TemplateNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateBody(CHTLParser::TemplateBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateContent(CHTLParser::TemplateContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclaration(CHTLParser::VarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomDeclaration(CHTLParser::CustomDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomType(CHTLParser::CustomTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomName(CHTLParser::CustomNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomBody(CHTLParser::CustomBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomContent(CHTLParser::CustomContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssPropertyWithoutValue(CHTLParser::CssPropertyWithoutValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateUsage(CHTLParser::TemplateUsageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTemplateSpecialization(CHTLParser::TemplateSpecializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecializationContent(CHTLParser::SpecializationContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarAssignment(CHTLParser::VarAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomUsage(CHTLParser::CustomUsageContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomSpecialization(CHTLParser::CustomSpecializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInheritStatement(CHTLParser::InheritStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeleteStatement(CHTLParser::DeleteStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeleteTarget(CHTLParser::DeleteTargetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementIndex(CHTLParser::ElementIndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertStatement(CHTLParser::InsertStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertPosition(CHTLParser::InsertPositionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertTarget(CHTLParser::InsertTargetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInsertContent(CHTLParser::InsertContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExceptStatement(CHTLParser::ExceptStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExceptTarget(CHTLParser::ExceptTargetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOriginBlock(CHTLParser::OriginBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOriginType(CHTLParser::OriginTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOriginName(CHTLParser::OriginNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOriginBody(CHTLParser::OriginBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRawContent(CHTLParser::RawContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportStatement(CHTLParser::ImportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportContent(CHTLParser::ImportContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportHtml(CHTLParser::ImportHtmlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportCss(CHTLParser::ImportCssContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportJs(CHTLParser::ImportJsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportChtl(CHTLParser::ImportChtlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportCustom(CHTLParser::ImportCustomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportTemplate(CHTLParser::ImportTemplateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilePath(CHTLParser::FilePathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceName(CHTLParser::NamespaceNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceBody(CHTLParser::NamespaceBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamespaceContent(CHTLParser::NamespaceContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConfigurationBlock(CHTLParser::ConfigurationBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConfigContent(CHTLParser::ConfigContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConfigAssignment(CHTLParser::ConfigAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConfigValue(CHTLParser::ConfigValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNameBlock(CHTLParser::NameBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNameAssignment(CHTLParser::NameAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }


};

