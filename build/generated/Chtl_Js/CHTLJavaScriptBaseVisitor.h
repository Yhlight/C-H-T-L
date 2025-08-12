
// Generated from /workspace/grammar/CHTLJavaScript.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJavaScriptVisitor.h"


/**
 * This class provides an empty implementation of CHTLJavaScriptVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CHTLJavaScriptBaseVisitor : public CHTLJavaScriptVisitor {
public:

  virtual std::any visitSingleExpression(CHTLJavaScriptParser::SingleExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlSelectorList(CHTLJavaScriptParser::ChtlSelectorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlSelector(CHTLJavaScriptParser::ChtlSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChtlSelectorContent(CHTLJavaScriptParser::ChtlSelectorContentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssSelector(CHTLJavaScriptParser::CssSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssSelectorPart(CHTLJavaScriptParser::CssSelectorPartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitListenObject(CHTLJavaScriptParser::ListenObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEventBinding(CHTLJavaScriptParser::EventBindingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDelegateObject(CHTLJavaScriptParser::DelegateObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDelegateProperty(CHTLJavaScriptParser::DelegatePropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectorArray(CHTLJavaScriptParser::SelectorArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnimateCall(CHTLJavaScriptParser::AnimateCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnimateObject(CHTLJavaScriptParser::AnimateObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnimateProperty(CHTLJavaScriptParser::AnimatePropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssObject(CHTLJavaScriptParser::CssObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCssProperty(CHTLJavaScriptParser::CssPropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhenArray(CHTLJavaScriptParser::WhenArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhenObject(CHTLJavaScriptParser::WhenObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhenProperty(CHTLJavaScriptParser::WhenPropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(CHTLJavaScriptParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgram(CHTLJavaScriptParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(CHTLJavaScriptParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(CHTLJavaScriptParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableStatement(CHTLJavaScriptParser::VariableStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclarationList(CHTLJavaScriptParser::VariableDeclarationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarModifier(CHTLJavaScriptParser::VarModifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(CHTLJavaScriptParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyStatement(CHTLJavaScriptParser::EmptyStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(CHTLJavaScriptParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(CHTLJavaScriptParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterationStatement(CHTLJavaScriptParser::IterationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(CHTLJavaScriptParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(CHTLJavaScriptParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(CHTLJavaScriptParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWithStatement(CHTLJavaScriptParser::WithStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabelledStatement(CHTLJavaScriptParser::LabelledStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchStatement(CHTLJavaScriptParser::SwitchStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaseBlock(CHTLJavaScriptParser::CaseBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaseClauses(CHTLJavaScriptParser::CaseClausesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaseClause(CHTLJavaScriptParser::CaseClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultClause(CHTLJavaScriptParser::DefaultClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThrowStatement(CHTLJavaScriptParser::ThrowStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTryStatement(CHTLJavaScriptParser::TryStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCatchClause(CHTLJavaScriptParser::CatchClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFinallyClause(CHTLJavaScriptParser::FinallyClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDeclaration(CHTLJavaScriptParser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDeclaration(CHTLJavaScriptParser::ClassDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassTail(CHTLJavaScriptParser::ClassTailContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassElement(CHTLJavaScriptParser::ClassElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodDefinition(CHTLJavaScriptParser::MethodDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGetter(CHTLJavaScriptParser::GetterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetter(CHTLJavaScriptParser::SetterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGeneratorMethod(CHTLJavaScriptParser::GeneratorMethodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAsyncMethod(CHTLJavaScriptParser::AsyncMethodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportStatement(CHTLJavaScriptParser::ImportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportFromBlock(CHTLJavaScriptParser::ImportFromBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportNamespace(CHTLJavaScriptParser::ImportNamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportSpecifier(CHTLJavaScriptParser::ImportSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModuleExportName(CHTLJavaScriptParser::ModuleExportNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportStatement(CHTLJavaScriptParser::ExportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportFromBlock(CHTLJavaScriptParser::ExportFromBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportNamespace(CHTLJavaScriptParser::ExportNamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportSpecifier(CHTLJavaScriptParser::ExportSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(CHTLJavaScriptParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormalParameterList(CHTLJavaScriptParser::FormalParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormalParameter(CHTLJavaScriptParser::FormalParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRestParameter(CHTLJavaScriptParser::RestParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignable(CHTLJavaScriptParser::AssignableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyName(CHTLJavaScriptParser::PropertyNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionSequence(CHTLJavaScriptParser::ExpressionSequenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOperator(CHTLJavaScriptParser::AssignmentOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayLiteral(CHTLJavaScriptParser::ArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementList(CHTLJavaScriptParser::ElementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayElement(CHTLJavaScriptParser::ArrayElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectLiteral(CHTLJavaScriptParser::ObjectLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyAssignment(CHTLJavaScriptParser::PropertyAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(CHTLJavaScriptParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(CHTLJavaScriptParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(CHTLJavaScriptParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnonymousFunction(CHTLJavaScriptParser::AnonymousFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrowFunction(CHTLJavaScriptParser::ArrowFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrowFunctionParameters(CHTLJavaScriptParser::ArrowFunctionParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrowFunctionBody(CHTLJavaScriptParser::ArrowFunctionBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeofExpression(CHTLJavaScriptParser::TypeofExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierName(CHTLJavaScriptParser::IdentifierNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReservedWord(CHTLJavaScriptParser::ReservedWordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyword(CHTLJavaScriptParser::KeywordContext *ctx) override {
    return visitChildren(ctx);
  }


};

