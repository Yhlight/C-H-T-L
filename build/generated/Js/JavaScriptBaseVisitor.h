
// Generated from /workspace/grammar/JavaScript.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "JavaScriptVisitor.h"


/**
 * This class provides an empty implementation of JavaScriptVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  JavaScriptBaseVisitor : public JavaScriptVisitor {
public:

  virtual std::any visitProgram(JavaScriptParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(JavaScriptParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(JavaScriptParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableStatement(JavaScriptParser::VariableStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarModifier(JavaScriptParser::VarModifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyStatement(JavaScriptParser::EmptyStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(JavaScriptParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(JavaScriptParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterationStatement(JavaScriptParser::IterationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(JavaScriptParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWithStatement(JavaScriptParser::WithStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLabelledStatement(JavaScriptParser::LabelledStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaseBlock(JavaScriptParser::CaseBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaseClauses(JavaScriptParser::CaseClausesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaseClause(JavaScriptParser::CaseClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultClause(JavaScriptParser::DefaultClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTryStatement(JavaScriptParser::TryStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCatchClause(JavaScriptParser::CatchClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFinallyClause(JavaScriptParser::FinallyClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassTail(JavaScriptParser::ClassTailContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassElement(JavaScriptParser::ClassElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMethodDefinition(JavaScriptParser::MethodDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGetter(JavaScriptParser::GetterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetter(JavaScriptParser::SetterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGeneratorMethod(JavaScriptParser::GeneratorMethodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAsyncMethod(JavaScriptParser::AsyncMethodContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportStatement(JavaScriptParser::ImportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportFromBlock(JavaScriptParser::ImportFromBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportNamespace(JavaScriptParser::ImportNamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportSpecifier(JavaScriptParser::ImportSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModuleExportName(JavaScriptParser::ModuleExportNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportStatement(JavaScriptParser::ExportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportFromBlock(JavaScriptParser::ExportFromBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportNamespace(JavaScriptParser::ExportNamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportSpecifier(JavaScriptParser::ExportSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(JavaScriptParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormalParameter(JavaScriptParser::FormalParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRestParameter(JavaScriptParser::RestParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignable(JavaScriptParser::AssignableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyName(JavaScriptParser::PropertyNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionSequence(JavaScriptParser::ExpressionSequenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleExpression(JavaScriptParser::SingleExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(JavaScriptParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementList(JavaScriptParser::ElementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayElement(JavaScriptParser::ArrayElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyAssignment(JavaScriptParser::PropertyAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(JavaScriptParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(JavaScriptParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(JavaScriptParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnonymousFunction(JavaScriptParser::AnonymousFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrowFunctionParameters(JavaScriptParser::ArrowFunctionParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeofExpression(JavaScriptParser::TypeofExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReservedWord(JavaScriptParser::ReservedWordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyword(JavaScriptParser::KeywordContext *ctx) override {
    return visitChildren(ctx);
  }


};

