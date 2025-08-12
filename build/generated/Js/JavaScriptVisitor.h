
// Generated from /workspace/grammar/JavaScript.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "JavaScriptParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by JavaScriptParser.
 */
class  JavaScriptVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by JavaScriptParser.
   */
    virtual std::any visitProgram(JavaScriptParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(JavaScriptParser::StatementContext *context) = 0;

    virtual std::any visitBlock(JavaScriptParser::BlockContext *context) = 0;

    virtual std::any visitVariableStatement(JavaScriptParser::VariableStatementContext *context) = 0;

    virtual std::any visitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *context) = 0;

    virtual std::any visitVarModifier(JavaScriptParser::VarModifierContext *context) = 0;

    virtual std::any visitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitEmptyStatement(JavaScriptParser::EmptyStatementContext *context) = 0;

    virtual std::any visitExpressionStatement(JavaScriptParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitIfStatement(JavaScriptParser::IfStatementContext *context) = 0;

    virtual std::any visitIterationStatement(JavaScriptParser::IterationStatementContext *context) = 0;

    virtual std::any visitContinueStatement(JavaScriptParser::ContinueStatementContext *context) = 0;

    virtual std::any visitBreakStatement(JavaScriptParser::BreakStatementContext *context) = 0;

    virtual std::any visitReturnStatement(JavaScriptParser::ReturnStatementContext *context) = 0;

    virtual std::any visitWithStatement(JavaScriptParser::WithStatementContext *context) = 0;

    virtual std::any visitLabelledStatement(JavaScriptParser::LabelledStatementContext *context) = 0;

    virtual std::any visitSwitchStatement(JavaScriptParser::SwitchStatementContext *context) = 0;

    virtual std::any visitCaseBlock(JavaScriptParser::CaseBlockContext *context) = 0;

    virtual std::any visitCaseClauses(JavaScriptParser::CaseClausesContext *context) = 0;

    virtual std::any visitCaseClause(JavaScriptParser::CaseClauseContext *context) = 0;

    virtual std::any visitDefaultClause(JavaScriptParser::DefaultClauseContext *context) = 0;

    virtual std::any visitThrowStatement(JavaScriptParser::ThrowStatementContext *context) = 0;

    virtual std::any visitTryStatement(JavaScriptParser::TryStatementContext *context) = 0;

    virtual std::any visitCatchClause(JavaScriptParser::CatchClauseContext *context) = 0;

    virtual std::any visitFinallyClause(JavaScriptParser::FinallyClauseContext *context) = 0;

    virtual std::any visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *context) = 0;

    virtual std::any visitClassDeclaration(JavaScriptParser::ClassDeclarationContext *context) = 0;

    virtual std::any visitClassTail(JavaScriptParser::ClassTailContext *context) = 0;

    virtual std::any visitClassElement(JavaScriptParser::ClassElementContext *context) = 0;

    virtual std::any visitMethodDefinition(JavaScriptParser::MethodDefinitionContext *context) = 0;

    virtual std::any visitGetter(JavaScriptParser::GetterContext *context) = 0;

    virtual std::any visitSetter(JavaScriptParser::SetterContext *context) = 0;

    virtual std::any visitGeneratorMethod(JavaScriptParser::GeneratorMethodContext *context) = 0;

    virtual std::any visitAsyncMethod(JavaScriptParser::AsyncMethodContext *context) = 0;

    virtual std::any visitImportStatement(JavaScriptParser::ImportStatementContext *context) = 0;

    virtual std::any visitImportFromBlock(JavaScriptParser::ImportFromBlockContext *context) = 0;

    virtual std::any visitImportNamespace(JavaScriptParser::ImportNamespaceContext *context) = 0;

    virtual std::any visitImportSpecifier(JavaScriptParser::ImportSpecifierContext *context) = 0;

    virtual std::any visitModuleExportName(JavaScriptParser::ModuleExportNameContext *context) = 0;

    virtual std::any visitExportStatement(JavaScriptParser::ExportStatementContext *context) = 0;

    virtual std::any visitExportFromBlock(JavaScriptParser::ExportFromBlockContext *context) = 0;

    virtual std::any visitExportNamespace(JavaScriptParser::ExportNamespaceContext *context) = 0;

    virtual std::any visitExportSpecifier(JavaScriptParser::ExportSpecifierContext *context) = 0;

    virtual std::any visitDeclaration(JavaScriptParser::DeclarationContext *context) = 0;

    virtual std::any visitFormalParameterList(JavaScriptParser::FormalParameterListContext *context) = 0;

    virtual std::any visitFormalParameter(JavaScriptParser::FormalParameterContext *context) = 0;

    virtual std::any visitRestParameter(JavaScriptParser::RestParameterContext *context) = 0;

    virtual std::any visitAssignable(JavaScriptParser::AssignableContext *context) = 0;

    virtual std::any visitPropertyName(JavaScriptParser::PropertyNameContext *context) = 0;

    virtual std::any visitExpressionSequence(JavaScriptParser::ExpressionSequenceContext *context) = 0;

    virtual std::any visitSingleExpression(JavaScriptParser::SingleExpressionContext *context) = 0;

    virtual std::any visitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *context) = 0;

    virtual std::any visitLiteral(JavaScriptParser::LiteralContext *context) = 0;

    virtual std::any visitArrayLiteral(JavaScriptParser::ArrayLiteralContext *context) = 0;

    virtual std::any visitElementList(JavaScriptParser::ElementListContext *context) = 0;

    virtual std::any visitArrayElement(JavaScriptParser::ArrayElementContext *context) = 0;

    virtual std::any visitObjectLiteral(JavaScriptParser::ObjectLiteralContext *context) = 0;

    virtual std::any visitPropertyAssignment(JavaScriptParser::PropertyAssignmentContext *context) = 0;

    virtual std::any visitArguments(JavaScriptParser::ArgumentsContext *context) = 0;

    virtual std::any visitArgumentList(JavaScriptParser::ArgumentListContext *context) = 0;

    virtual std::any visitArgument(JavaScriptParser::ArgumentContext *context) = 0;

    virtual std::any visitAnonymousFunction(JavaScriptParser::AnonymousFunctionContext *context) = 0;

    virtual std::any visitArrowFunction(JavaScriptParser::ArrowFunctionContext *context) = 0;

    virtual std::any visitArrowFunctionParameters(JavaScriptParser::ArrowFunctionParametersContext *context) = 0;

    virtual std::any visitArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext *context) = 0;

    virtual std::any visitTypeofExpression(JavaScriptParser::TypeofExpressionContext *context) = 0;

    virtual std::any visitIdentifierName(JavaScriptParser::IdentifierNameContext *context) = 0;

    virtual std::any visitReservedWord(JavaScriptParser::ReservedWordContext *context) = 0;

    virtual std::any visitKeyword(JavaScriptParser::KeywordContext *context) = 0;


};

