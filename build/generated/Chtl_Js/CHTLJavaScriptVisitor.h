
// Generated from /workspace/grammar/CHTLJavaScript.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJavaScriptParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CHTLJavaScriptParser.
 */
class  CHTLJavaScriptVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CHTLJavaScriptParser.
   */
    virtual std::any visitSingleExpression(CHTLJavaScriptParser::SingleExpressionContext *context) = 0;

    virtual std::any visitChtlSelectorList(CHTLJavaScriptParser::ChtlSelectorListContext *context) = 0;

    virtual std::any visitChtlSelector(CHTLJavaScriptParser::ChtlSelectorContext *context) = 0;

    virtual std::any visitChtlSelectorContent(CHTLJavaScriptParser::ChtlSelectorContentContext *context) = 0;

    virtual std::any visitCssSelector(CHTLJavaScriptParser::CssSelectorContext *context) = 0;

    virtual std::any visitCssSelectorPart(CHTLJavaScriptParser::CssSelectorPartContext *context) = 0;

    virtual std::any visitListenObject(CHTLJavaScriptParser::ListenObjectContext *context) = 0;

    virtual std::any visitEventBinding(CHTLJavaScriptParser::EventBindingContext *context) = 0;

    virtual std::any visitDelegateObject(CHTLJavaScriptParser::DelegateObjectContext *context) = 0;

    virtual std::any visitDelegateProperty(CHTLJavaScriptParser::DelegatePropertyContext *context) = 0;

    virtual std::any visitSelectorArray(CHTLJavaScriptParser::SelectorArrayContext *context) = 0;

    virtual std::any visitAnimateCall(CHTLJavaScriptParser::AnimateCallContext *context) = 0;

    virtual std::any visitAnimateObject(CHTLJavaScriptParser::AnimateObjectContext *context) = 0;

    virtual std::any visitAnimateProperty(CHTLJavaScriptParser::AnimatePropertyContext *context) = 0;

    virtual std::any visitCssObject(CHTLJavaScriptParser::CssObjectContext *context) = 0;

    virtual std::any visitCssProperty(CHTLJavaScriptParser::CssPropertyContext *context) = 0;

    virtual std::any visitWhenArray(CHTLJavaScriptParser::WhenArrayContext *context) = 0;

    virtual std::any visitWhenObject(CHTLJavaScriptParser::WhenObjectContext *context) = 0;

    virtual std::any visitWhenProperty(CHTLJavaScriptParser::WhenPropertyContext *context) = 0;

    virtual std::any visitLiteral(CHTLJavaScriptParser::LiteralContext *context) = 0;

    virtual std::any visitProgram(CHTLJavaScriptParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(CHTLJavaScriptParser::StatementContext *context) = 0;

    virtual std::any visitBlock(CHTLJavaScriptParser::BlockContext *context) = 0;

    virtual std::any visitVariableStatement(CHTLJavaScriptParser::VariableStatementContext *context) = 0;

    virtual std::any visitVariableDeclarationList(CHTLJavaScriptParser::VariableDeclarationListContext *context) = 0;

    virtual std::any visitVarModifier(CHTLJavaScriptParser::VarModifierContext *context) = 0;

    virtual std::any visitVariableDeclaration(CHTLJavaScriptParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitEmptyStatement(CHTLJavaScriptParser::EmptyStatementContext *context) = 0;

    virtual std::any visitExpressionStatement(CHTLJavaScriptParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitIfStatement(CHTLJavaScriptParser::IfStatementContext *context) = 0;

    virtual std::any visitIterationStatement(CHTLJavaScriptParser::IterationStatementContext *context) = 0;

    virtual std::any visitContinueStatement(CHTLJavaScriptParser::ContinueStatementContext *context) = 0;

    virtual std::any visitBreakStatement(CHTLJavaScriptParser::BreakStatementContext *context) = 0;

    virtual std::any visitReturnStatement(CHTLJavaScriptParser::ReturnStatementContext *context) = 0;

    virtual std::any visitWithStatement(CHTLJavaScriptParser::WithStatementContext *context) = 0;

    virtual std::any visitLabelledStatement(CHTLJavaScriptParser::LabelledStatementContext *context) = 0;

    virtual std::any visitSwitchStatement(CHTLJavaScriptParser::SwitchStatementContext *context) = 0;

    virtual std::any visitCaseBlock(CHTLJavaScriptParser::CaseBlockContext *context) = 0;

    virtual std::any visitCaseClauses(CHTLJavaScriptParser::CaseClausesContext *context) = 0;

    virtual std::any visitCaseClause(CHTLJavaScriptParser::CaseClauseContext *context) = 0;

    virtual std::any visitDefaultClause(CHTLJavaScriptParser::DefaultClauseContext *context) = 0;

    virtual std::any visitThrowStatement(CHTLJavaScriptParser::ThrowStatementContext *context) = 0;

    virtual std::any visitTryStatement(CHTLJavaScriptParser::TryStatementContext *context) = 0;

    virtual std::any visitCatchClause(CHTLJavaScriptParser::CatchClauseContext *context) = 0;

    virtual std::any visitFinallyClause(CHTLJavaScriptParser::FinallyClauseContext *context) = 0;

    virtual std::any visitFunctionDeclaration(CHTLJavaScriptParser::FunctionDeclarationContext *context) = 0;

    virtual std::any visitClassDeclaration(CHTLJavaScriptParser::ClassDeclarationContext *context) = 0;

    virtual std::any visitClassTail(CHTLJavaScriptParser::ClassTailContext *context) = 0;

    virtual std::any visitClassElement(CHTLJavaScriptParser::ClassElementContext *context) = 0;

    virtual std::any visitMethodDefinition(CHTLJavaScriptParser::MethodDefinitionContext *context) = 0;

    virtual std::any visitGetter(CHTLJavaScriptParser::GetterContext *context) = 0;

    virtual std::any visitSetter(CHTLJavaScriptParser::SetterContext *context) = 0;

    virtual std::any visitGeneratorMethod(CHTLJavaScriptParser::GeneratorMethodContext *context) = 0;

    virtual std::any visitAsyncMethod(CHTLJavaScriptParser::AsyncMethodContext *context) = 0;

    virtual std::any visitImportStatement(CHTLJavaScriptParser::ImportStatementContext *context) = 0;

    virtual std::any visitImportFromBlock(CHTLJavaScriptParser::ImportFromBlockContext *context) = 0;

    virtual std::any visitImportNamespace(CHTLJavaScriptParser::ImportNamespaceContext *context) = 0;

    virtual std::any visitImportSpecifier(CHTLJavaScriptParser::ImportSpecifierContext *context) = 0;

    virtual std::any visitModuleExportName(CHTLJavaScriptParser::ModuleExportNameContext *context) = 0;

    virtual std::any visitExportStatement(CHTLJavaScriptParser::ExportStatementContext *context) = 0;

    virtual std::any visitExportFromBlock(CHTLJavaScriptParser::ExportFromBlockContext *context) = 0;

    virtual std::any visitExportNamespace(CHTLJavaScriptParser::ExportNamespaceContext *context) = 0;

    virtual std::any visitExportSpecifier(CHTLJavaScriptParser::ExportSpecifierContext *context) = 0;

    virtual std::any visitDeclaration(CHTLJavaScriptParser::DeclarationContext *context) = 0;

    virtual std::any visitFormalParameterList(CHTLJavaScriptParser::FormalParameterListContext *context) = 0;

    virtual std::any visitFormalParameter(CHTLJavaScriptParser::FormalParameterContext *context) = 0;

    virtual std::any visitRestParameter(CHTLJavaScriptParser::RestParameterContext *context) = 0;

    virtual std::any visitAssignable(CHTLJavaScriptParser::AssignableContext *context) = 0;

    virtual std::any visitPropertyName(CHTLJavaScriptParser::PropertyNameContext *context) = 0;

    virtual std::any visitExpressionSequence(CHTLJavaScriptParser::ExpressionSequenceContext *context) = 0;

    virtual std::any visitAssignmentOperator(CHTLJavaScriptParser::AssignmentOperatorContext *context) = 0;

    virtual std::any visitArrayLiteral(CHTLJavaScriptParser::ArrayLiteralContext *context) = 0;

    virtual std::any visitElementList(CHTLJavaScriptParser::ElementListContext *context) = 0;

    virtual std::any visitArrayElement(CHTLJavaScriptParser::ArrayElementContext *context) = 0;

    virtual std::any visitObjectLiteral(CHTLJavaScriptParser::ObjectLiteralContext *context) = 0;

    virtual std::any visitPropertyAssignment(CHTLJavaScriptParser::PropertyAssignmentContext *context) = 0;

    virtual std::any visitArguments(CHTLJavaScriptParser::ArgumentsContext *context) = 0;

    virtual std::any visitArgumentList(CHTLJavaScriptParser::ArgumentListContext *context) = 0;

    virtual std::any visitArgument(CHTLJavaScriptParser::ArgumentContext *context) = 0;

    virtual std::any visitAnonymousFunction(CHTLJavaScriptParser::AnonymousFunctionContext *context) = 0;

    virtual std::any visitArrowFunction(CHTLJavaScriptParser::ArrowFunctionContext *context) = 0;

    virtual std::any visitArrowFunctionParameters(CHTLJavaScriptParser::ArrowFunctionParametersContext *context) = 0;

    virtual std::any visitArrowFunctionBody(CHTLJavaScriptParser::ArrowFunctionBodyContext *context) = 0;

    virtual std::any visitTypeofExpression(CHTLJavaScriptParser::TypeofExpressionContext *context) = 0;

    virtual std::any visitIdentifierName(CHTLJavaScriptParser::IdentifierNameContext *context) = 0;

    virtual std::any visitReservedWord(CHTLJavaScriptParser::ReservedWordContext *context) = 0;

    virtual std::any visitKeyword(CHTLJavaScriptParser::KeywordContext *context) = 0;


};

