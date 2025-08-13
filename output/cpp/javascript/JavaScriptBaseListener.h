
// Generated from JavaScript.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "JavaScriptListener.h"


/**
 * This class provides an empty implementation of JavaScriptListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  JavaScriptBaseListener : public JavaScriptListener {
public:

  virtual void enterProgram(JavaScriptParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(JavaScriptParser::ProgramContext * /*ctx*/) override { }

  virtual void enterSourceElements(JavaScriptParser::SourceElementsContext * /*ctx*/) override { }
  virtual void exitSourceElements(JavaScriptParser::SourceElementsContext * /*ctx*/) override { }

  virtual void enterSourceElement(JavaScriptParser::SourceElementContext * /*ctx*/) override { }
  virtual void exitSourceElement(JavaScriptParser::SourceElementContext * /*ctx*/) override { }

  virtual void enterDeclaration(JavaScriptParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(JavaScriptParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterHoistableDeclaration(JavaScriptParser::HoistableDeclarationContext * /*ctx*/) override { }
  virtual void exitHoistableDeclaration(JavaScriptParser::HoistableDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterGeneratorDeclaration(JavaScriptParser::GeneratorDeclarationContext * /*ctx*/) override { }
  virtual void exitGeneratorDeclaration(JavaScriptParser::GeneratorDeclarationContext * /*ctx*/) override { }

  virtual void enterAsyncFunctionDeclaration(JavaScriptParser::AsyncFunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitAsyncFunctionDeclaration(JavaScriptParser::AsyncFunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterAsyncGeneratorDeclaration(JavaScriptParser::AsyncGeneratorDeclarationContext * /*ctx*/) override { }
  virtual void exitAsyncGeneratorDeclaration(JavaScriptParser::AsyncGeneratorDeclarationContext * /*ctx*/) override { }

  virtual void enterClassDeclaration(JavaScriptParser::ClassDeclarationContext * /*ctx*/) override { }
  virtual void exitClassDeclaration(JavaScriptParser::ClassDeclarationContext * /*ctx*/) override { }

  virtual void enterClassExtends(JavaScriptParser::ClassExtendsContext * /*ctx*/) override { }
  virtual void exitClassExtends(JavaScriptParser::ClassExtendsContext * /*ctx*/) override { }

  virtual void enterClassBody(JavaScriptParser::ClassBodyContext * /*ctx*/) override { }
  virtual void exitClassBody(JavaScriptParser::ClassBodyContext * /*ctx*/) override { }

  virtual void enterClassElement(JavaScriptParser::ClassElementContext * /*ctx*/) override { }
  virtual void exitClassElement(JavaScriptParser::ClassElementContext * /*ctx*/) override { }

  virtual void enterMethodDefinition(JavaScriptParser::MethodDefinitionContext * /*ctx*/) override { }
  virtual void exitMethodDefinition(JavaScriptParser::MethodDefinitionContext * /*ctx*/) override { }

  virtual void enterFieldDefinition(JavaScriptParser::FieldDefinitionContext * /*ctx*/) override { }
  virtual void exitFieldDefinition(JavaScriptParser::FieldDefinitionContext * /*ctx*/) override { }

  virtual void enterLexicalDeclaration(JavaScriptParser::LexicalDeclarationContext * /*ctx*/) override { }
  virtual void exitLexicalDeclaration(JavaScriptParser::LexicalDeclarationContext * /*ctx*/) override { }

  virtual void enterLetOrConst(JavaScriptParser::LetOrConstContext * /*ctx*/) override { }
  virtual void exitLetOrConst(JavaScriptParser::LetOrConstContext * /*ctx*/) override { }

  virtual void enterBindingList(JavaScriptParser::BindingListContext * /*ctx*/) override { }
  virtual void exitBindingList(JavaScriptParser::BindingListContext * /*ctx*/) override { }

  virtual void enterLexicalBinding(JavaScriptParser::LexicalBindingContext * /*ctx*/) override { }
  virtual void exitLexicalBinding(JavaScriptParser::LexicalBindingContext * /*ctx*/) override { }

  virtual void enterStatement(JavaScriptParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(JavaScriptParser::StatementContext * /*ctx*/) override { }

  virtual void enterBlockStatement(JavaScriptParser::BlockStatementContext * /*ctx*/) override { }
  virtual void exitBlockStatement(JavaScriptParser::BlockStatementContext * /*ctx*/) override { }

  virtual void enterStatementList(JavaScriptParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(JavaScriptParser::StatementListContext * /*ctx*/) override { }

  virtual void enterVariableStatement(JavaScriptParser::VariableStatementContext * /*ctx*/) override { }
  virtual void exitVariableStatement(JavaScriptParser::VariableStatementContext * /*ctx*/) override { }

  virtual void enterVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext * /*ctx*/) override { }
  virtual void exitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(JavaScriptParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(JavaScriptParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterEmptyStatement(JavaScriptParser::EmptyStatementContext * /*ctx*/) override { }
  virtual void exitEmptyStatement(JavaScriptParser::EmptyStatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(JavaScriptParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(JavaScriptParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterIfStatement(JavaScriptParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(JavaScriptParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterIterationStatement(JavaScriptParser::IterationStatementContext * /*ctx*/) override { }
  virtual void exitIterationStatement(JavaScriptParser::IterationStatementContext * /*ctx*/) override { }

  virtual void enterDoWhileStatement(JavaScriptParser::DoWhileStatementContext * /*ctx*/) override { }
  virtual void exitDoWhileStatement(JavaScriptParser::DoWhileStatementContext * /*ctx*/) override { }

  virtual void enterWhileStatement(JavaScriptParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(JavaScriptParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterForStatement(JavaScriptParser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(JavaScriptParser::ForStatementContext * /*ctx*/) override { }

  virtual void enterForInit(JavaScriptParser::ForInitContext * /*ctx*/) override { }
  virtual void exitForInit(JavaScriptParser::ForInitContext * /*ctx*/) override { }

  virtual void enterForInStatement(JavaScriptParser::ForInStatementContext * /*ctx*/) override { }
  virtual void exitForInStatement(JavaScriptParser::ForInStatementContext * /*ctx*/) override { }

  virtual void enterForOfStatement(JavaScriptParser::ForOfStatementContext * /*ctx*/) override { }
  virtual void exitForOfStatement(JavaScriptParser::ForOfStatementContext * /*ctx*/) override { }

  virtual void enterForInBinding(JavaScriptParser::ForInBindingContext * /*ctx*/) override { }
  virtual void exitForInBinding(JavaScriptParser::ForInBindingContext * /*ctx*/) override { }

  virtual void enterContinueStatement(JavaScriptParser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(JavaScriptParser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterBreakStatement(JavaScriptParser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(JavaScriptParser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(JavaScriptParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(JavaScriptParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterWithStatement(JavaScriptParser::WithStatementContext * /*ctx*/) override { }
  virtual void exitWithStatement(JavaScriptParser::WithStatementContext * /*ctx*/) override { }

  virtual void enterLabelledStatement(JavaScriptParser::LabelledStatementContext * /*ctx*/) override { }
  virtual void exitLabelledStatement(JavaScriptParser::LabelledStatementContext * /*ctx*/) override { }

  virtual void enterSwitchStatement(JavaScriptParser::SwitchStatementContext * /*ctx*/) override { }
  virtual void exitSwitchStatement(JavaScriptParser::SwitchStatementContext * /*ctx*/) override { }

  virtual void enterCaseClause(JavaScriptParser::CaseClauseContext * /*ctx*/) override { }
  virtual void exitCaseClause(JavaScriptParser::CaseClauseContext * /*ctx*/) override { }

  virtual void enterDefaultClause(JavaScriptParser::DefaultClauseContext * /*ctx*/) override { }
  virtual void exitDefaultClause(JavaScriptParser::DefaultClauseContext * /*ctx*/) override { }

  virtual void enterThrowStatement(JavaScriptParser::ThrowStatementContext * /*ctx*/) override { }
  virtual void exitThrowStatement(JavaScriptParser::ThrowStatementContext * /*ctx*/) override { }

  virtual void enterTryStatement(JavaScriptParser::TryStatementContext * /*ctx*/) override { }
  virtual void exitTryStatement(JavaScriptParser::TryStatementContext * /*ctx*/) override { }

  virtual void enterCatchClause(JavaScriptParser::CatchClauseContext * /*ctx*/) override { }
  virtual void exitCatchClause(JavaScriptParser::CatchClauseContext * /*ctx*/) override { }

  virtual void enterCatchParameter(JavaScriptParser::CatchParameterContext * /*ctx*/) override { }
  virtual void exitCatchParameter(JavaScriptParser::CatchParameterContext * /*ctx*/) override { }

  virtual void enterFinallyClause(JavaScriptParser::FinallyClauseContext * /*ctx*/) override { }
  virtual void exitFinallyClause(JavaScriptParser::FinallyClauseContext * /*ctx*/) override { }

  virtual void enterDebuggerStatement(JavaScriptParser::DebuggerStatementContext * /*ctx*/) override { }
  virtual void exitDebuggerStatement(JavaScriptParser::DebuggerStatementContext * /*ctx*/) override { }

  virtual void enterImportStatement(JavaScriptParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(JavaScriptParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterImportClause(JavaScriptParser::ImportClauseContext * /*ctx*/) override { }
  virtual void exitImportClause(JavaScriptParser::ImportClauseContext * /*ctx*/) override { }

  virtual void enterImportedDefaultBinding(JavaScriptParser::ImportedDefaultBindingContext * /*ctx*/) override { }
  virtual void exitImportedDefaultBinding(JavaScriptParser::ImportedDefaultBindingContext * /*ctx*/) override { }

  virtual void enterNamespaceImport(JavaScriptParser::NamespaceImportContext * /*ctx*/) override { }
  virtual void exitNamespaceImport(JavaScriptParser::NamespaceImportContext * /*ctx*/) override { }

  virtual void enterNamedImports(JavaScriptParser::NamedImportsContext * /*ctx*/) override { }
  virtual void exitNamedImports(JavaScriptParser::NamedImportsContext * /*ctx*/) override { }

  virtual void enterImportsList(JavaScriptParser::ImportsListContext * /*ctx*/) override { }
  virtual void exitImportsList(JavaScriptParser::ImportsListContext * /*ctx*/) override { }

  virtual void enterImportSpecifier(JavaScriptParser::ImportSpecifierContext * /*ctx*/) override { }
  virtual void exitImportSpecifier(JavaScriptParser::ImportSpecifierContext * /*ctx*/) override { }

  virtual void enterModuleSpecifier(JavaScriptParser::ModuleSpecifierContext * /*ctx*/) override { }
  virtual void exitModuleSpecifier(JavaScriptParser::ModuleSpecifierContext * /*ctx*/) override { }

  virtual void enterExportStatement(JavaScriptParser::ExportStatementContext * /*ctx*/) override { }
  virtual void exitExportStatement(JavaScriptParser::ExportStatementContext * /*ctx*/) override { }

  virtual void enterExportClause(JavaScriptParser::ExportClauseContext * /*ctx*/) override { }
  virtual void exitExportClause(JavaScriptParser::ExportClauseContext * /*ctx*/) override { }

  virtual void enterExportsList(JavaScriptParser::ExportsListContext * /*ctx*/) override { }
  virtual void exitExportsList(JavaScriptParser::ExportsListContext * /*ctx*/) override { }

  virtual void enterExportSpecifier(JavaScriptParser::ExportSpecifierContext * /*ctx*/) override { }
  virtual void exitExportSpecifier(JavaScriptParser::ExportSpecifierContext * /*ctx*/) override { }

  virtual void enterExpression(JavaScriptParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(JavaScriptParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(JavaScriptParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(JavaScriptParser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(JavaScriptParser::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(JavaScriptParser::ConditionalExpressionContext * /*ctx*/) override { }

  virtual void enterCoalesceExpression(JavaScriptParser::CoalesceExpressionContext * /*ctx*/) override { }
  virtual void exitCoalesceExpression(JavaScriptParser::CoalesceExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalORExpression(JavaScriptParser::LogicalORExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalORExpression(JavaScriptParser::LogicalORExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalANDExpression(JavaScriptParser::LogicalANDExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalANDExpression(JavaScriptParser::LogicalANDExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseORExpression(JavaScriptParser::BitwiseORExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseORExpression(JavaScriptParser::BitwiseORExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseXORExpression(JavaScriptParser::BitwiseXORExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseXORExpression(JavaScriptParser::BitwiseXORExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseANDExpression(JavaScriptParser::BitwiseANDExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseANDExpression(JavaScriptParser::BitwiseANDExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(JavaScriptParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(JavaScriptParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(JavaScriptParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(JavaScriptParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterShiftExpression(JavaScriptParser::ShiftExpressionContext * /*ctx*/) override { }
  virtual void exitShiftExpression(JavaScriptParser::ShiftExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(JavaScriptParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(JavaScriptParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterExponentiationExpression(JavaScriptParser::ExponentiationExpressionContext * /*ctx*/) override { }
  virtual void exitExponentiationExpression(JavaScriptParser::ExponentiationExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(JavaScriptParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(JavaScriptParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterUpdateExpression(JavaScriptParser::UpdateExpressionContext * /*ctx*/) override { }
  virtual void exitUpdateExpression(JavaScriptParser::UpdateExpressionContext * /*ctx*/) override { }

  virtual void enterLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext * /*ctx*/) override { }
  virtual void exitLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext * /*ctx*/) override { }

  virtual void enterNewExpression(JavaScriptParser::NewExpressionContext * /*ctx*/) override { }
  virtual void exitNewExpression(JavaScriptParser::NewExpressionContext * /*ctx*/) override { }

  virtual void enterCallExpression(JavaScriptParser::CallExpressionContext * /*ctx*/) override { }
  virtual void exitCallExpression(JavaScriptParser::CallExpressionContext * /*ctx*/) override { }

  virtual void enterSuperCall(JavaScriptParser::SuperCallContext * /*ctx*/) override { }
  virtual void exitSuperCall(JavaScriptParser::SuperCallContext * /*ctx*/) override { }

  virtual void enterImportCall(JavaScriptParser::ImportCallContext * /*ctx*/) override { }
  virtual void exitImportCall(JavaScriptParser::ImportCallContext * /*ctx*/) override { }

  virtual void enterArguments(JavaScriptParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(JavaScriptParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterArgumentList(JavaScriptParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(JavaScriptParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterArgument(JavaScriptParser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(JavaScriptParser::ArgumentContext * /*ctx*/) override { }

  virtual void enterMemberExpression(JavaScriptParser::MemberExpressionContext * /*ctx*/) override { }
  virtual void exitMemberExpression(JavaScriptParser::MemberExpressionContext * /*ctx*/) override { }

  virtual void enterMetaProperty(JavaScriptParser::MetaPropertyContext * /*ctx*/) override { }
  virtual void exitMetaProperty(JavaScriptParser::MetaPropertyContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(JavaScriptParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(JavaScriptParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext * /*ctx*/) override { }
  virtual void exitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext * /*ctx*/) override { }

  virtual void enterLiteral(JavaScriptParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(JavaScriptParser::LiteralContext * /*ctx*/) override { }

  virtual void enterNullLiteral(JavaScriptParser::NullLiteralContext * /*ctx*/) override { }
  virtual void exitNullLiteral(JavaScriptParser::NullLiteralContext * /*ctx*/) override { }

  virtual void enterBooleanLiteral(JavaScriptParser::BooleanLiteralContext * /*ctx*/) override { }
  virtual void exitBooleanLiteral(JavaScriptParser::BooleanLiteralContext * /*ctx*/) override { }

  virtual void enterNumericLiteral(JavaScriptParser::NumericLiteralContext * /*ctx*/) override { }
  virtual void exitNumericLiteral(JavaScriptParser::NumericLiteralContext * /*ctx*/) override { }

  virtual void enterStringLiteral(JavaScriptParser::StringLiteralContext * /*ctx*/) override { }
  virtual void exitStringLiteral(JavaScriptParser::StringLiteralContext * /*ctx*/) override { }

  virtual void enterArrayLiteral(JavaScriptParser::ArrayLiteralContext * /*ctx*/) override { }
  virtual void exitArrayLiteral(JavaScriptParser::ArrayLiteralContext * /*ctx*/) override { }

  virtual void enterElementList(JavaScriptParser::ElementListContext * /*ctx*/) override { }
  virtual void exitElementList(JavaScriptParser::ElementListContext * /*ctx*/) override { }

  virtual void enterArrayElement(JavaScriptParser::ArrayElementContext * /*ctx*/) override { }
  virtual void exitArrayElement(JavaScriptParser::ArrayElementContext * /*ctx*/) override { }

  virtual void enterObjectLiteral(JavaScriptParser::ObjectLiteralContext * /*ctx*/) override { }
  virtual void exitObjectLiteral(JavaScriptParser::ObjectLiteralContext * /*ctx*/) override { }

  virtual void enterPropertyDefinitionList(JavaScriptParser::PropertyDefinitionListContext * /*ctx*/) override { }
  virtual void exitPropertyDefinitionList(JavaScriptParser::PropertyDefinitionListContext * /*ctx*/) override { }

  virtual void enterPropertyDefinition(JavaScriptParser::PropertyDefinitionContext * /*ctx*/) override { }
  virtual void exitPropertyDefinition(JavaScriptParser::PropertyDefinitionContext * /*ctx*/) override { }

  virtual void enterPropertyName(JavaScriptParser::PropertyNameContext * /*ctx*/) override { }
  virtual void exitPropertyName(JavaScriptParser::PropertyNameContext * /*ctx*/) override { }

  virtual void enterFunctionExpression(JavaScriptParser::FunctionExpressionContext * /*ctx*/) override { }
  virtual void exitFunctionExpression(JavaScriptParser::FunctionExpressionContext * /*ctx*/) override { }

  virtual void enterGeneratorExpression(JavaScriptParser::GeneratorExpressionContext * /*ctx*/) override { }
  virtual void exitGeneratorExpression(JavaScriptParser::GeneratorExpressionContext * /*ctx*/) override { }

  virtual void enterAsyncFunctionExpression(JavaScriptParser::AsyncFunctionExpressionContext * /*ctx*/) override { }
  virtual void exitAsyncFunctionExpression(JavaScriptParser::AsyncFunctionExpressionContext * /*ctx*/) override { }

  virtual void enterAsyncGeneratorExpression(JavaScriptParser::AsyncGeneratorExpressionContext * /*ctx*/) override { }
  virtual void exitAsyncGeneratorExpression(JavaScriptParser::AsyncGeneratorExpressionContext * /*ctx*/) override { }

  virtual void enterClassExpression(JavaScriptParser::ClassExpressionContext * /*ctx*/) override { }
  virtual void exitClassExpression(JavaScriptParser::ClassExpressionContext * /*ctx*/) override { }

  virtual void enterArrowFunction(JavaScriptParser::ArrowFunctionContext * /*ctx*/) override { }
  virtual void exitArrowFunction(JavaScriptParser::ArrowFunctionContext * /*ctx*/) override { }

  virtual void enterAsyncArrowFunction(JavaScriptParser::AsyncArrowFunctionContext * /*ctx*/) override { }
  virtual void exitAsyncArrowFunction(JavaScriptParser::AsyncArrowFunctionContext * /*ctx*/) override { }

  virtual void enterArrowParameters(JavaScriptParser::ArrowParametersContext * /*ctx*/) override { }
  virtual void exitArrowParameters(JavaScriptParser::ArrowParametersContext * /*ctx*/) override { }

  virtual void enterArrowBody(JavaScriptParser::ArrowBodyContext * /*ctx*/) override { }
  virtual void exitArrowBody(JavaScriptParser::ArrowBodyContext * /*ctx*/) override { }

  virtual void enterYieldExpression(JavaScriptParser::YieldExpressionContext * /*ctx*/) override { }
  virtual void exitYieldExpression(JavaScriptParser::YieldExpressionContext * /*ctx*/) override { }

  virtual void enterTemplateLiteral(JavaScriptParser::TemplateLiteralContext * /*ctx*/) override { }
  virtual void exitTemplateLiteral(JavaScriptParser::TemplateLiteralContext * /*ctx*/) override { }

  virtual void enterTemplateSpans(JavaScriptParser::TemplateSpansContext * /*ctx*/) override { }
  virtual void exitTemplateSpans(JavaScriptParser::TemplateSpansContext * /*ctx*/) override { }

  virtual void enterTemplateSpan(JavaScriptParser::TemplateSpanContext * /*ctx*/) override { }
  virtual void exitTemplateSpan(JavaScriptParser::TemplateSpanContext * /*ctx*/) override { }

  virtual void enterTemplateMiddle(JavaScriptParser::TemplateMiddleContext * /*ctx*/) override { }
  virtual void exitTemplateMiddle(JavaScriptParser::TemplateMiddleContext * /*ctx*/) override { }

  virtual void enterRegularExpressionLiteral(JavaScriptParser::RegularExpressionLiteralContext * /*ctx*/) override { }
  virtual void exitRegularExpressionLiteral(JavaScriptParser::RegularExpressionLiteralContext * /*ctx*/) override { }

  virtual void enterFormalParameterList(JavaScriptParser::FormalParameterListContext * /*ctx*/) override { }
  virtual void exitFormalParameterList(JavaScriptParser::FormalParameterListContext * /*ctx*/) override { }

  virtual void enterFormalParameter(JavaScriptParser::FormalParameterContext * /*ctx*/) override { }
  virtual void exitFormalParameter(JavaScriptParser::FormalParameterContext * /*ctx*/) override { }

  virtual void enterRestParameter(JavaScriptParser::RestParameterContext * /*ctx*/) override { }
  virtual void exitRestParameter(JavaScriptParser::RestParameterContext * /*ctx*/) override { }

  virtual void enterBindingElement(JavaScriptParser::BindingElementContext * /*ctx*/) override { }
  virtual void exitBindingElement(JavaScriptParser::BindingElementContext * /*ctx*/) override { }

  virtual void enterBindingPattern(JavaScriptParser::BindingPatternContext * /*ctx*/) override { }
  virtual void exitBindingPattern(JavaScriptParser::BindingPatternContext * /*ctx*/) override { }

  virtual void enterObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext * /*ctx*/) override { }
  virtual void exitObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext * /*ctx*/) override { }

  virtual void enterBindingPropertyList(JavaScriptParser::BindingPropertyListContext * /*ctx*/) override { }
  virtual void exitBindingPropertyList(JavaScriptParser::BindingPropertyListContext * /*ctx*/) override { }

  virtual void enterBindingProperty(JavaScriptParser::BindingPropertyContext * /*ctx*/) override { }
  virtual void exitBindingProperty(JavaScriptParser::BindingPropertyContext * /*ctx*/) override { }

  virtual void enterArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext * /*ctx*/) override { }
  virtual void exitArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext * /*ctx*/) override { }

  virtual void enterBindingElementList(JavaScriptParser::BindingElementListContext * /*ctx*/) override { }
  virtual void exitBindingElementList(JavaScriptParser::BindingElementListContext * /*ctx*/) override { }

  virtual void enterBindingElision(JavaScriptParser::BindingElisionContext * /*ctx*/) override { }
  virtual void exitBindingElision(JavaScriptParser::BindingElisionContext * /*ctx*/) override { }

  virtual void enterFunctionBody(JavaScriptParser::FunctionBodyContext * /*ctx*/) override { }
  virtual void exitFunctionBody(JavaScriptParser::FunctionBodyContext * /*ctx*/) override { }

  virtual void enterInitializer(JavaScriptParser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(JavaScriptParser::InitializerContext * /*ctx*/) override { }

  virtual void enterBindingIdentifier(JavaScriptParser::BindingIdentifierContext * /*ctx*/) override { }
  virtual void exitBindingIdentifier(JavaScriptParser::BindingIdentifierContext * /*ctx*/) override { }

  virtual void enterIdentifier(JavaScriptParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(JavaScriptParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterIdentifierName(JavaScriptParser::IdentifierNameContext * /*ctx*/) override { }
  virtual void exitIdentifierName(JavaScriptParser::IdentifierNameContext * /*ctx*/) override { }

  virtual void enterReservedWord(JavaScriptParser::ReservedWordContext * /*ctx*/) override { }
  virtual void exitReservedWord(JavaScriptParser::ReservedWordContext * /*ctx*/) override { }

  virtual void enterKeyword(JavaScriptParser::KeywordContext * /*ctx*/) override { }
  virtual void exitKeyword(JavaScriptParser::KeywordContext * /*ctx*/) override { }

  virtual void enterFutureReservedWord(JavaScriptParser::FutureReservedWordContext * /*ctx*/) override { }
  virtual void exitFutureReservedWord(JavaScriptParser::FutureReservedWordContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

