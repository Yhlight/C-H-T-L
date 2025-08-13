
// Generated from JavaScript.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "JavaScriptParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by JavaScriptParser.
 */
class  JavaScriptListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(JavaScriptParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(JavaScriptParser::ProgramContext *ctx) = 0;

  virtual void enterSourceElements(JavaScriptParser::SourceElementsContext *ctx) = 0;
  virtual void exitSourceElements(JavaScriptParser::SourceElementsContext *ctx) = 0;

  virtual void enterSourceElement(JavaScriptParser::SourceElementContext *ctx) = 0;
  virtual void exitSourceElement(JavaScriptParser::SourceElementContext *ctx) = 0;

  virtual void enterDeclaration(JavaScriptParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(JavaScriptParser::DeclarationContext *ctx) = 0;

  virtual void enterHoistableDeclaration(JavaScriptParser::HoistableDeclarationContext *ctx) = 0;
  virtual void exitHoistableDeclaration(JavaScriptParser::HoistableDeclarationContext *ctx) = 0;

  virtual void enterFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterGeneratorDeclaration(JavaScriptParser::GeneratorDeclarationContext *ctx) = 0;
  virtual void exitGeneratorDeclaration(JavaScriptParser::GeneratorDeclarationContext *ctx) = 0;

  virtual void enterAsyncFunctionDeclaration(JavaScriptParser::AsyncFunctionDeclarationContext *ctx) = 0;
  virtual void exitAsyncFunctionDeclaration(JavaScriptParser::AsyncFunctionDeclarationContext *ctx) = 0;

  virtual void enterAsyncGeneratorDeclaration(JavaScriptParser::AsyncGeneratorDeclarationContext *ctx) = 0;
  virtual void exitAsyncGeneratorDeclaration(JavaScriptParser::AsyncGeneratorDeclarationContext *ctx) = 0;

  virtual void enterClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) = 0;
  virtual void exitClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) = 0;

  virtual void enterClassExtends(JavaScriptParser::ClassExtendsContext *ctx) = 0;
  virtual void exitClassExtends(JavaScriptParser::ClassExtendsContext *ctx) = 0;

  virtual void enterClassBody(JavaScriptParser::ClassBodyContext *ctx) = 0;
  virtual void exitClassBody(JavaScriptParser::ClassBodyContext *ctx) = 0;

  virtual void enterClassElement(JavaScriptParser::ClassElementContext *ctx) = 0;
  virtual void exitClassElement(JavaScriptParser::ClassElementContext *ctx) = 0;

  virtual void enterMethodDefinition(JavaScriptParser::MethodDefinitionContext *ctx) = 0;
  virtual void exitMethodDefinition(JavaScriptParser::MethodDefinitionContext *ctx) = 0;

  virtual void enterFieldDefinition(JavaScriptParser::FieldDefinitionContext *ctx) = 0;
  virtual void exitFieldDefinition(JavaScriptParser::FieldDefinitionContext *ctx) = 0;

  virtual void enterLexicalDeclaration(JavaScriptParser::LexicalDeclarationContext *ctx) = 0;
  virtual void exitLexicalDeclaration(JavaScriptParser::LexicalDeclarationContext *ctx) = 0;

  virtual void enterLetOrConst(JavaScriptParser::LetOrConstContext *ctx) = 0;
  virtual void exitLetOrConst(JavaScriptParser::LetOrConstContext *ctx) = 0;

  virtual void enterBindingList(JavaScriptParser::BindingListContext *ctx) = 0;
  virtual void exitBindingList(JavaScriptParser::BindingListContext *ctx) = 0;

  virtual void enterLexicalBinding(JavaScriptParser::LexicalBindingContext *ctx) = 0;
  virtual void exitLexicalBinding(JavaScriptParser::LexicalBindingContext *ctx) = 0;

  virtual void enterStatement(JavaScriptParser::StatementContext *ctx) = 0;
  virtual void exitStatement(JavaScriptParser::StatementContext *ctx) = 0;

  virtual void enterBlockStatement(JavaScriptParser::BlockStatementContext *ctx) = 0;
  virtual void exitBlockStatement(JavaScriptParser::BlockStatementContext *ctx) = 0;

  virtual void enterStatementList(JavaScriptParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(JavaScriptParser::StatementListContext *ctx) = 0;

  virtual void enterVariableStatement(JavaScriptParser::VariableStatementContext *ctx) = 0;
  virtual void exitVariableStatement(JavaScriptParser::VariableStatementContext *ctx) = 0;

  virtual void enterVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) = 0;
  virtual void exitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) = 0;

  virtual void enterVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterEmptyStatement(JavaScriptParser::EmptyStatementContext *ctx) = 0;
  virtual void exitEmptyStatement(JavaScriptParser::EmptyStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(JavaScriptParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(JavaScriptParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfStatement(JavaScriptParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(JavaScriptParser::IfStatementContext *ctx) = 0;

  virtual void enterIterationStatement(JavaScriptParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(JavaScriptParser::IterationStatementContext *ctx) = 0;

  virtual void enterDoWhileStatement(JavaScriptParser::DoWhileStatementContext *ctx) = 0;
  virtual void exitDoWhileStatement(JavaScriptParser::DoWhileStatementContext *ctx) = 0;

  virtual void enterWhileStatement(JavaScriptParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(JavaScriptParser::WhileStatementContext *ctx) = 0;

  virtual void enterForStatement(JavaScriptParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(JavaScriptParser::ForStatementContext *ctx) = 0;

  virtual void enterForInit(JavaScriptParser::ForInitContext *ctx) = 0;
  virtual void exitForInit(JavaScriptParser::ForInitContext *ctx) = 0;

  virtual void enterForInStatement(JavaScriptParser::ForInStatementContext *ctx) = 0;
  virtual void exitForInStatement(JavaScriptParser::ForInStatementContext *ctx) = 0;

  virtual void enterForOfStatement(JavaScriptParser::ForOfStatementContext *ctx) = 0;
  virtual void exitForOfStatement(JavaScriptParser::ForOfStatementContext *ctx) = 0;

  virtual void enterForInBinding(JavaScriptParser::ForInBindingContext *ctx) = 0;
  virtual void exitForInBinding(JavaScriptParser::ForInBindingContext *ctx) = 0;

  virtual void enterContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(JavaScriptParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(JavaScriptParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) = 0;

  virtual void enterWithStatement(JavaScriptParser::WithStatementContext *ctx) = 0;
  virtual void exitWithStatement(JavaScriptParser::WithStatementContext *ctx) = 0;

  virtual void enterLabelledStatement(JavaScriptParser::LabelledStatementContext *ctx) = 0;
  virtual void exitLabelledStatement(JavaScriptParser::LabelledStatementContext *ctx) = 0;

  virtual void enterSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) = 0;

  virtual void enterCaseClause(JavaScriptParser::CaseClauseContext *ctx) = 0;
  virtual void exitCaseClause(JavaScriptParser::CaseClauseContext *ctx) = 0;

  virtual void enterDefaultClause(JavaScriptParser::DefaultClauseContext *ctx) = 0;
  virtual void exitDefaultClause(JavaScriptParser::DefaultClauseContext *ctx) = 0;

  virtual void enterThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) = 0;
  virtual void exitThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) = 0;

  virtual void enterTryStatement(JavaScriptParser::TryStatementContext *ctx) = 0;
  virtual void exitTryStatement(JavaScriptParser::TryStatementContext *ctx) = 0;

  virtual void enterCatchClause(JavaScriptParser::CatchClauseContext *ctx) = 0;
  virtual void exitCatchClause(JavaScriptParser::CatchClauseContext *ctx) = 0;

  virtual void enterCatchParameter(JavaScriptParser::CatchParameterContext *ctx) = 0;
  virtual void exitCatchParameter(JavaScriptParser::CatchParameterContext *ctx) = 0;

  virtual void enterFinallyClause(JavaScriptParser::FinallyClauseContext *ctx) = 0;
  virtual void exitFinallyClause(JavaScriptParser::FinallyClauseContext *ctx) = 0;

  virtual void enterDebuggerStatement(JavaScriptParser::DebuggerStatementContext *ctx) = 0;
  virtual void exitDebuggerStatement(JavaScriptParser::DebuggerStatementContext *ctx) = 0;

  virtual void enterImportStatement(JavaScriptParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(JavaScriptParser::ImportStatementContext *ctx) = 0;

  virtual void enterImportClause(JavaScriptParser::ImportClauseContext *ctx) = 0;
  virtual void exitImportClause(JavaScriptParser::ImportClauseContext *ctx) = 0;

  virtual void enterImportedDefaultBinding(JavaScriptParser::ImportedDefaultBindingContext *ctx) = 0;
  virtual void exitImportedDefaultBinding(JavaScriptParser::ImportedDefaultBindingContext *ctx) = 0;

  virtual void enterNamespaceImport(JavaScriptParser::NamespaceImportContext *ctx) = 0;
  virtual void exitNamespaceImport(JavaScriptParser::NamespaceImportContext *ctx) = 0;

  virtual void enterNamedImports(JavaScriptParser::NamedImportsContext *ctx) = 0;
  virtual void exitNamedImports(JavaScriptParser::NamedImportsContext *ctx) = 0;

  virtual void enterImportsList(JavaScriptParser::ImportsListContext *ctx) = 0;
  virtual void exitImportsList(JavaScriptParser::ImportsListContext *ctx) = 0;

  virtual void enterImportSpecifier(JavaScriptParser::ImportSpecifierContext *ctx) = 0;
  virtual void exitImportSpecifier(JavaScriptParser::ImportSpecifierContext *ctx) = 0;

  virtual void enterModuleSpecifier(JavaScriptParser::ModuleSpecifierContext *ctx) = 0;
  virtual void exitModuleSpecifier(JavaScriptParser::ModuleSpecifierContext *ctx) = 0;

  virtual void enterExportStatement(JavaScriptParser::ExportStatementContext *ctx) = 0;
  virtual void exitExportStatement(JavaScriptParser::ExportStatementContext *ctx) = 0;

  virtual void enterExportClause(JavaScriptParser::ExportClauseContext *ctx) = 0;
  virtual void exitExportClause(JavaScriptParser::ExportClauseContext *ctx) = 0;

  virtual void enterExportsList(JavaScriptParser::ExportsListContext *ctx) = 0;
  virtual void exitExportsList(JavaScriptParser::ExportsListContext *ctx) = 0;

  virtual void enterExportSpecifier(JavaScriptParser::ExportSpecifierContext *ctx) = 0;
  virtual void exitExportSpecifier(JavaScriptParser::ExportSpecifierContext *ctx) = 0;

  virtual void enterExpression(JavaScriptParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(JavaScriptParser::ExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterConditionalExpression(JavaScriptParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(JavaScriptParser::ConditionalExpressionContext *ctx) = 0;

  virtual void enterCoalesceExpression(JavaScriptParser::CoalesceExpressionContext *ctx) = 0;
  virtual void exitCoalesceExpression(JavaScriptParser::CoalesceExpressionContext *ctx) = 0;

  virtual void enterLogicalORExpression(JavaScriptParser::LogicalORExpressionContext *ctx) = 0;
  virtual void exitLogicalORExpression(JavaScriptParser::LogicalORExpressionContext *ctx) = 0;

  virtual void enterLogicalANDExpression(JavaScriptParser::LogicalANDExpressionContext *ctx) = 0;
  virtual void exitLogicalANDExpression(JavaScriptParser::LogicalANDExpressionContext *ctx) = 0;

  virtual void enterBitwiseORExpression(JavaScriptParser::BitwiseORExpressionContext *ctx) = 0;
  virtual void exitBitwiseORExpression(JavaScriptParser::BitwiseORExpressionContext *ctx) = 0;

  virtual void enterBitwiseXORExpression(JavaScriptParser::BitwiseXORExpressionContext *ctx) = 0;
  virtual void exitBitwiseXORExpression(JavaScriptParser::BitwiseXORExpressionContext *ctx) = 0;

  virtual void enterBitwiseANDExpression(JavaScriptParser::BitwiseANDExpressionContext *ctx) = 0;
  virtual void exitBitwiseANDExpression(JavaScriptParser::BitwiseANDExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(JavaScriptParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(JavaScriptParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(JavaScriptParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(JavaScriptParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(JavaScriptParser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(JavaScriptParser::ShiftExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterExponentiationExpression(JavaScriptParser::ExponentiationExpressionContext *ctx) = 0;
  virtual void exitExponentiationExpression(JavaScriptParser::ExponentiationExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(JavaScriptParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(JavaScriptParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterUpdateExpression(JavaScriptParser::UpdateExpressionContext *ctx) = 0;
  virtual void exitUpdateExpression(JavaScriptParser::UpdateExpressionContext *ctx) = 0;

  virtual void enterLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext *ctx) = 0;
  virtual void exitLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext *ctx) = 0;

  virtual void enterNewExpression(JavaScriptParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(JavaScriptParser::NewExpressionContext *ctx) = 0;

  virtual void enterCallExpression(JavaScriptParser::CallExpressionContext *ctx) = 0;
  virtual void exitCallExpression(JavaScriptParser::CallExpressionContext *ctx) = 0;

  virtual void enterSuperCall(JavaScriptParser::SuperCallContext *ctx) = 0;
  virtual void exitSuperCall(JavaScriptParser::SuperCallContext *ctx) = 0;

  virtual void enterImportCall(JavaScriptParser::ImportCallContext *ctx) = 0;
  virtual void exitImportCall(JavaScriptParser::ImportCallContext *ctx) = 0;

  virtual void enterArguments(JavaScriptParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(JavaScriptParser::ArgumentsContext *ctx) = 0;

  virtual void enterArgumentList(JavaScriptParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(JavaScriptParser::ArgumentListContext *ctx) = 0;

  virtual void enterArgument(JavaScriptParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(JavaScriptParser::ArgumentContext *ctx) = 0;

  virtual void enterMemberExpression(JavaScriptParser::MemberExpressionContext *ctx) = 0;
  virtual void exitMemberExpression(JavaScriptParser::MemberExpressionContext *ctx) = 0;

  virtual void enterMetaProperty(JavaScriptParser::MetaPropertyContext *ctx) = 0;
  virtual void exitMetaProperty(JavaScriptParser::MetaPropertyContext *ctx) = 0;

  virtual void enterPrimaryExpression(JavaScriptParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(JavaScriptParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;
  virtual void exitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;

  virtual void enterLiteral(JavaScriptParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(JavaScriptParser::LiteralContext *ctx) = 0;

  virtual void enterNullLiteral(JavaScriptParser::NullLiteralContext *ctx) = 0;
  virtual void exitNullLiteral(JavaScriptParser::NullLiteralContext *ctx) = 0;

  virtual void enterBooleanLiteral(JavaScriptParser::BooleanLiteralContext *ctx) = 0;
  virtual void exitBooleanLiteral(JavaScriptParser::BooleanLiteralContext *ctx) = 0;

  virtual void enterNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) = 0;
  virtual void exitNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) = 0;

  virtual void enterStringLiteral(JavaScriptParser::StringLiteralContext *ctx) = 0;
  virtual void exitStringLiteral(JavaScriptParser::StringLiteralContext *ctx) = 0;

  virtual void enterArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) = 0;
  virtual void exitArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) = 0;

  virtual void enterElementList(JavaScriptParser::ElementListContext *ctx) = 0;
  virtual void exitElementList(JavaScriptParser::ElementListContext *ctx) = 0;

  virtual void enterArrayElement(JavaScriptParser::ArrayElementContext *ctx) = 0;
  virtual void exitArrayElement(JavaScriptParser::ArrayElementContext *ctx) = 0;

  virtual void enterObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) = 0;
  virtual void exitObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) = 0;

  virtual void enterPropertyDefinitionList(JavaScriptParser::PropertyDefinitionListContext *ctx) = 0;
  virtual void exitPropertyDefinitionList(JavaScriptParser::PropertyDefinitionListContext *ctx) = 0;

  virtual void enterPropertyDefinition(JavaScriptParser::PropertyDefinitionContext *ctx) = 0;
  virtual void exitPropertyDefinition(JavaScriptParser::PropertyDefinitionContext *ctx) = 0;

  virtual void enterPropertyName(JavaScriptParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(JavaScriptParser::PropertyNameContext *ctx) = 0;

  virtual void enterFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx) = 0;
  virtual void exitFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx) = 0;

  virtual void enterGeneratorExpression(JavaScriptParser::GeneratorExpressionContext *ctx) = 0;
  virtual void exitGeneratorExpression(JavaScriptParser::GeneratorExpressionContext *ctx) = 0;

  virtual void enterAsyncFunctionExpression(JavaScriptParser::AsyncFunctionExpressionContext *ctx) = 0;
  virtual void exitAsyncFunctionExpression(JavaScriptParser::AsyncFunctionExpressionContext *ctx) = 0;

  virtual void enterAsyncGeneratorExpression(JavaScriptParser::AsyncGeneratorExpressionContext *ctx) = 0;
  virtual void exitAsyncGeneratorExpression(JavaScriptParser::AsyncGeneratorExpressionContext *ctx) = 0;

  virtual void enterClassExpression(JavaScriptParser::ClassExpressionContext *ctx) = 0;
  virtual void exitClassExpression(JavaScriptParser::ClassExpressionContext *ctx) = 0;

  virtual void enterArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) = 0;
  virtual void exitArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) = 0;

  virtual void enterAsyncArrowFunction(JavaScriptParser::AsyncArrowFunctionContext *ctx) = 0;
  virtual void exitAsyncArrowFunction(JavaScriptParser::AsyncArrowFunctionContext *ctx) = 0;

  virtual void enterArrowParameters(JavaScriptParser::ArrowParametersContext *ctx) = 0;
  virtual void exitArrowParameters(JavaScriptParser::ArrowParametersContext *ctx) = 0;

  virtual void enterArrowBody(JavaScriptParser::ArrowBodyContext *ctx) = 0;
  virtual void exitArrowBody(JavaScriptParser::ArrowBodyContext *ctx) = 0;

  virtual void enterYieldExpression(JavaScriptParser::YieldExpressionContext *ctx) = 0;
  virtual void exitYieldExpression(JavaScriptParser::YieldExpressionContext *ctx) = 0;

  virtual void enterTemplateLiteral(JavaScriptParser::TemplateLiteralContext *ctx) = 0;
  virtual void exitTemplateLiteral(JavaScriptParser::TemplateLiteralContext *ctx) = 0;

  virtual void enterTemplateSpans(JavaScriptParser::TemplateSpansContext *ctx) = 0;
  virtual void exitTemplateSpans(JavaScriptParser::TemplateSpansContext *ctx) = 0;

  virtual void enterTemplateSpan(JavaScriptParser::TemplateSpanContext *ctx) = 0;
  virtual void exitTemplateSpan(JavaScriptParser::TemplateSpanContext *ctx) = 0;

  virtual void enterTemplateMiddle(JavaScriptParser::TemplateMiddleContext *ctx) = 0;
  virtual void exitTemplateMiddle(JavaScriptParser::TemplateMiddleContext *ctx) = 0;

  virtual void enterRegularExpressionLiteral(JavaScriptParser::RegularExpressionLiteralContext *ctx) = 0;
  virtual void exitRegularExpressionLiteral(JavaScriptParser::RegularExpressionLiteralContext *ctx) = 0;

  virtual void enterFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) = 0;
  virtual void exitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) = 0;

  virtual void enterFormalParameter(JavaScriptParser::FormalParameterContext *ctx) = 0;
  virtual void exitFormalParameter(JavaScriptParser::FormalParameterContext *ctx) = 0;

  virtual void enterRestParameter(JavaScriptParser::RestParameterContext *ctx) = 0;
  virtual void exitRestParameter(JavaScriptParser::RestParameterContext *ctx) = 0;

  virtual void enterBindingElement(JavaScriptParser::BindingElementContext *ctx) = 0;
  virtual void exitBindingElement(JavaScriptParser::BindingElementContext *ctx) = 0;

  virtual void enterBindingPattern(JavaScriptParser::BindingPatternContext *ctx) = 0;
  virtual void exitBindingPattern(JavaScriptParser::BindingPatternContext *ctx) = 0;

  virtual void enterObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext *ctx) = 0;
  virtual void exitObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext *ctx) = 0;

  virtual void enterBindingPropertyList(JavaScriptParser::BindingPropertyListContext *ctx) = 0;
  virtual void exitBindingPropertyList(JavaScriptParser::BindingPropertyListContext *ctx) = 0;

  virtual void enterBindingProperty(JavaScriptParser::BindingPropertyContext *ctx) = 0;
  virtual void exitBindingProperty(JavaScriptParser::BindingPropertyContext *ctx) = 0;

  virtual void enterArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext *ctx) = 0;
  virtual void exitArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext *ctx) = 0;

  virtual void enterBindingElementList(JavaScriptParser::BindingElementListContext *ctx) = 0;
  virtual void exitBindingElementList(JavaScriptParser::BindingElementListContext *ctx) = 0;

  virtual void enterBindingElision(JavaScriptParser::BindingElisionContext *ctx) = 0;
  virtual void exitBindingElision(JavaScriptParser::BindingElisionContext *ctx) = 0;

  virtual void enterFunctionBody(JavaScriptParser::FunctionBodyContext *ctx) = 0;
  virtual void exitFunctionBody(JavaScriptParser::FunctionBodyContext *ctx) = 0;

  virtual void enterInitializer(JavaScriptParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(JavaScriptParser::InitializerContext *ctx) = 0;

  virtual void enterBindingIdentifier(JavaScriptParser::BindingIdentifierContext *ctx) = 0;
  virtual void exitBindingIdentifier(JavaScriptParser::BindingIdentifierContext *ctx) = 0;

  virtual void enterIdentifier(JavaScriptParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(JavaScriptParser::IdentifierContext *ctx) = 0;

  virtual void enterIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) = 0;
  virtual void exitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) = 0;

  virtual void enterReservedWord(JavaScriptParser::ReservedWordContext *ctx) = 0;
  virtual void exitReservedWord(JavaScriptParser::ReservedWordContext *ctx) = 0;

  virtual void enterKeyword(JavaScriptParser::KeywordContext *ctx) = 0;
  virtual void exitKeyword(JavaScriptParser::KeywordContext *ctx) = 0;

  virtual void enterFutureReservedWord(JavaScriptParser::FutureReservedWordContext *ctx) = 0;
  virtual void exitFutureReservedWord(JavaScriptParser::FutureReservedWordContext *ctx) = 0;


};

