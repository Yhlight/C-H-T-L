
// Generated from CHTLJavaScript.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJavaScriptParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CHTLJavaScriptParser.
 */
class  CHTLJavaScriptListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterPrimaryExpression(CHTLJavaScriptParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(CHTLJavaScriptParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterChtlSelector(CHTLJavaScriptParser::ChtlSelectorContext *ctx) = 0;
  virtual void exitChtlSelector(CHTLJavaScriptParser::ChtlSelectorContext *ctx) = 0;

  virtual void enterSelectorExpression(CHTLJavaScriptParser::SelectorExpressionContext *ctx) = 0;
  virtual void exitSelectorExpression(CHTLJavaScriptParser::SelectorExpressionContext *ctx) = 0;

  virtual void enterSelectorIdentifier(CHTLJavaScriptParser::SelectorIdentifierContext *ctx) = 0;
  virtual void exitSelectorIdentifier(CHTLJavaScriptParser::SelectorIdentifierContext *ctx) = 0;

  virtual void enterSelectorIndex(CHTLJavaScriptParser::SelectorIndexContext *ctx) = 0;
  virtual void exitSelectorIndex(CHTLJavaScriptParser::SelectorIndexContext *ctx) = 0;

  virtual void enterComplexSelector(CHTLJavaScriptParser::ComplexSelectorContext *ctx) = 0;
  virtual void exitComplexSelector(CHTLJavaScriptParser::ComplexSelectorContext *ctx) = 0;

  virtual void enterSelectorPart(CHTLJavaScriptParser::SelectorPartContext *ctx) = 0;
  virtual void exitSelectorPart(CHTLJavaScriptParser::SelectorPartContext *ctx) = 0;

  virtual void enterMemberExpression(CHTLJavaScriptParser::MemberExpressionContext *ctx) = 0;
  virtual void exitMemberExpression(CHTLJavaScriptParser::MemberExpressionContext *ctx) = 0;

  virtual void enterCallExpression(CHTLJavaScriptParser::CallExpressionContext *ctx) = 0;
  virtual void exitCallExpression(CHTLJavaScriptParser::CallExpressionContext *ctx) = 0;

  virtual void enterAnimateCall(CHTLJavaScriptParser::AnimateCallContext *ctx) = 0;
  virtual void exitAnimateCall(CHTLJavaScriptParser::AnimateCallContext *ctx) = 0;

  virtual void enterListenConfig(CHTLJavaScriptParser::ListenConfigContext *ctx) = 0;
  virtual void exitListenConfig(CHTLJavaScriptParser::ListenConfigContext *ctx) = 0;

  virtual void enterEventHandlerList(CHTLJavaScriptParser::EventHandlerListContext *ctx) = 0;
  virtual void exitEventHandlerList(CHTLJavaScriptParser::EventHandlerListContext *ctx) = 0;

  virtual void enterEventHandler(CHTLJavaScriptParser::EventHandlerContext *ctx) = 0;
  virtual void exitEventHandler(CHTLJavaScriptParser::EventHandlerContext *ctx) = 0;

  virtual void enterDelegateConfig(CHTLJavaScriptParser::DelegateConfigContext *ctx) = 0;
  virtual void exitDelegateConfig(CHTLJavaScriptParser::DelegateConfigContext *ctx) = 0;

  virtual void enterDelegateProperty(CHTLJavaScriptParser::DelegatePropertyContext *ctx) = 0;
  virtual void exitDelegateProperty(CHTLJavaScriptParser::DelegatePropertyContext *ctx) = 0;

  virtual void enterSelectorArray(CHTLJavaScriptParser::SelectorArrayContext *ctx) = 0;
  virtual void exitSelectorArray(CHTLJavaScriptParser::SelectorArrayContext *ctx) = 0;

  virtual void enterAnimateConfig(CHTLJavaScriptParser::AnimateConfigContext *ctx) = 0;
  virtual void exitAnimateConfig(CHTLJavaScriptParser::AnimateConfigContext *ctx) = 0;

  virtual void enterAnimateProperty(CHTLJavaScriptParser::AnimatePropertyContext *ctx) = 0;
  virtual void exitAnimateProperty(CHTLJavaScriptParser::AnimatePropertyContext *ctx) = 0;

  virtual void enterCssBlock(CHTLJavaScriptParser::CssBlockContext *ctx) = 0;
  virtual void exitCssBlock(CHTLJavaScriptParser::CssBlockContext *ctx) = 0;

  virtual void enterCssProperty(CHTLJavaScriptParser::CssPropertyContext *ctx) = 0;
  virtual void exitCssProperty(CHTLJavaScriptParser::CssPropertyContext *ctx) = 0;

  virtual void enterPropertyName(CHTLJavaScriptParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(CHTLJavaScriptParser::PropertyNameContext *ctx) = 0;

  virtual void enterPropertyValue(CHTLJavaScriptParser::PropertyValueContext *ctx) = 0;
  virtual void exitPropertyValue(CHTLJavaScriptParser::PropertyValueContext *ctx) = 0;

  virtual void enterCssFunction(CHTLJavaScriptParser::CssFunctionContext *ctx) = 0;
  virtual void exitCssFunction(CHTLJavaScriptParser::CssFunctionContext *ctx) = 0;

  virtual void enterCssFunctionArguments(CHTLJavaScriptParser::CssFunctionArgumentsContext *ctx) = 0;
  virtual void exitCssFunctionArguments(CHTLJavaScriptParser::CssFunctionArgumentsContext *ctx) = 0;

  virtual void enterWhenArray(CHTLJavaScriptParser::WhenArrayContext *ctx) = 0;
  virtual void exitWhenArray(CHTLJavaScriptParser::WhenArrayContext *ctx) = 0;

  virtual void enterWhenItem(CHTLJavaScriptParser::WhenItemContext *ctx) = 0;
  virtual void exitWhenItem(CHTLJavaScriptParser::WhenItemContext *ctx) = 0;

  virtual void enterWhenProperty(CHTLJavaScriptParser::WhenPropertyContext *ctx) = 0;
  virtual void exitWhenProperty(CHTLJavaScriptParser::WhenPropertyContext *ctx) = 0;

  virtual void enterLiteral(CHTLJavaScriptParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(CHTLJavaScriptParser::LiteralContext *ctx) = 0;

  virtual void enterProgram(CHTLJavaScriptParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(CHTLJavaScriptParser::ProgramContext *ctx) = 0;

  virtual void enterSourceElements(CHTLJavaScriptParser::SourceElementsContext *ctx) = 0;
  virtual void exitSourceElements(CHTLJavaScriptParser::SourceElementsContext *ctx) = 0;

  virtual void enterSourceElement(CHTLJavaScriptParser::SourceElementContext *ctx) = 0;
  virtual void exitSourceElement(CHTLJavaScriptParser::SourceElementContext *ctx) = 0;

  virtual void enterDeclaration(CHTLJavaScriptParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(CHTLJavaScriptParser::DeclarationContext *ctx) = 0;

  virtual void enterHoistableDeclaration(CHTLJavaScriptParser::HoistableDeclarationContext *ctx) = 0;
  virtual void exitHoistableDeclaration(CHTLJavaScriptParser::HoistableDeclarationContext *ctx) = 0;

  virtual void enterFunctionDeclaration(CHTLJavaScriptParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(CHTLJavaScriptParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterGeneratorDeclaration(CHTLJavaScriptParser::GeneratorDeclarationContext *ctx) = 0;
  virtual void exitGeneratorDeclaration(CHTLJavaScriptParser::GeneratorDeclarationContext *ctx) = 0;

  virtual void enterAsyncFunctionDeclaration(CHTLJavaScriptParser::AsyncFunctionDeclarationContext *ctx) = 0;
  virtual void exitAsyncFunctionDeclaration(CHTLJavaScriptParser::AsyncFunctionDeclarationContext *ctx) = 0;

  virtual void enterAsyncGeneratorDeclaration(CHTLJavaScriptParser::AsyncGeneratorDeclarationContext *ctx) = 0;
  virtual void exitAsyncGeneratorDeclaration(CHTLJavaScriptParser::AsyncGeneratorDeclarationContext *ctx) = 0;

  virtual void enterClassDeclaration(CHTLJavaScriptParser::ClassDeclarationContext *ctx) = 0;
  virtual void exitClassDeclaration(CHTLJavaScriptParser::ClassDeclarationContext *ctx) = 0;

  virtual void enterClassExtends(CHTLJavaScriptParser::ClassExtendsContext *ctx) = 0;
  virtual void exitClassExtends(CHTLJavaScriptParser::ClassExtendsContext *ctx) = 0;

  virtual void enterClassBody(CHTLJavaScriptParser::ClassBodyContext *ctx) = 0;
  virtual void exitClassBody(CHTLJavaScriptParser::ClassBodyContext *ctx) = 0;

  virtual void enterClassElement(CHTLJavaScriptParser::ClassElementContext *ctx) = 0;
  virtual void exitClassElement(CHTLJavaScriptParser::ClassElementContext *ctx) = 0;

  virtual void enterMethodDefinition(CHTLJavaScriptParser::MethodDefinitionContext *ctx) = 0;
  virtual void exitMethodDefinition(CHTLJavaScriptParser::MethodDefinitionContext *ctx) = 0;

  virtual void enterFieldDefinition(CHTLJavaScriptParser::FieldDefinitionContext *ctx) = 0;
  virtual void exitFieldDefinition(CHTLJavaScriptParser::FieldDefinitionContext *ctx) = 0;

  virtual void enterLexicalDeclaration(CHTLJavaScriptParser::LexicalDeclarationContext *ctx) = 0;
  virtual void exitLexicalDeclaration(CHTLJavaScriptParser::LexicalDeclarationContext *ctx) = 0;

  virtual void enterLetOrConst(CHTLJavaScriptParser::LetOrConstContext *ctx) = 0;
  virtual void exitLetOrConst(CHTLJavaScriptParser::LetOrConstContext *ctx) = 0;

  virtual void enterBindingList(CHTLJavaScriptParser::BindingListContext *ctx) = 0;
  virtual void exitBindingList(CHTLJavaScriptParser::BindingListContext *ctx) = 0;

  virtual void enterLexicalBinding(CHTLJavaScriptParser::LexicalBindingContext *ctx) = 0;
  virtual void exitLexicalBinding(CHTLJavaScriptParser::LexicalBindingContext *ctx) = 0;

  virtual void enterStatement(CHTLJavaScriptParser::StatementContext *ctx) = 0;
  virtual void exitStatement(CHTLJavaScriptParser::StatementContext *ctx) = 0;

  virtual void enterBlockStatement(CHTLJavaScriptParser::BlockStatementContext *ctx) = 0;
  virtual void exitBlockStatement(CHTLJavaScriptParser::BlockStatementContext *ctx) = 0;

  virtual void enterStatementList(CHTLJavaScriptParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(CHTLJavaScriptParser::StatementListContext *ctx) = 0;

  virtual void enterVariableStatement(CHTLJavaScriptParser::VariableStatementContext *ctx) = 0;
  virtual void exitVariableStatement(CHTLJavaScriptParser::VariableStatementContext *ctx) = 0;

  virtual void enterVariableDeclarationList(CHTLJavaScriptParser::VariableDeclarationListContext *ctx) = 0;
  virtual void exitVariableDeclarationList(CHTLJavaScriptParser::VariableDeclarationListContext *ctx) = 0;

  virtual void enterVariableDeclaration(CHTLJavaScriptParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(CHTLJavaScriptParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterEmptyStatement(CHTLJavaScriptParser::EmptyStatementContext *ctx) = 0;
  virtual void exitEmptyStatement(CHTLJavaScriptParser::EmptyStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(CHTLJavaScriptParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(CHTLJavaScriptParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfStatement(CHTLJavaScriptParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(CHTLJavaScriptParser::IfStatementContext *ctx) = 0;

  virtual void enterIterationStatement(CHTLJavaScriptParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(CHTLJavaScriptParser::IterationStatementContext *ctx) = 0;

  virtual void enterDoWhileStatement(CHTLJavaScriptParser::DoWhileStatementContext *ctx) = 0;
  virtual void exitDoWhileStatement(CHTLJavaScriptParser::DoWhileStatementContext *ctx) = 0;

  virtual void enterWhileStatement(CHTLJavaScriptParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(CHTLJavaScriptParser::WhileStatementContext *ctx) = 0;

  virtual void enterForStatement(CHTLJavaScriptParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(CHTLJavaScriptParser::ForStatementContext *ctx) = 0;

  virtual void enterForInit(CHTLJavaScriptParser::ForInitContext *ctx) = 0;
  virtual void exitForInit(CHTLJavaScriptParser::ForInitContext *ctx) = 0;

  virtual void enterForInStatement(CHTLJavaScriptParser::ForInStatementContext *ctx) = 0;
  virtual void exitForInStatement(CHTLJavaScriptParser::ForInStatementContext *ctx) = 0;

  virtual void enterForOfStatement(CHTLJavaScriptParser::ForOfStatementContext *ctx) = 0;
  virtual void exitForOfStatement(CHTLJavaScriptParser::ForOfStatementContext *ctx) = 0;

  virtual void enterForInBinding(CHTLJavaScriptParser::ForInBindingContext *ctx) = 0;
  virtual void exitForInBinding(CHTLJavaScriptParser::ForInBindingContext *ctx) = 0;

  virtual void enterContinueStatement(CHTLJavaScriptParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(CHTLJavaScriptParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(CHTLJavaScriptParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(CHTLJavaScriptParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(CHTLJavaScriptParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(CHTLJavaScriptParser::ReturnStatementContext *ctx) = 0;

  virtual void enterWithStatement(CHTLJavaScriptParser::WithStatementContext *ctx) = 0;
  virtual void exitWithStatement(CHTLJavaScriptParser::WithStatementContext *ctx) = 0;

  virtual void enterLabelledStatement(CHTLJavaScriptParser::LabelledStatementContext *ctx) = 0;
  virtual void exitLabelledStatement(CHTLJavaScriptParser::LabelledStatementContext *ctx) = 0;

  virtual void enterSwitchStatement(CHTLJavaScriptParser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(CHTLJavaScriptParser::SwitchStatementContext *ctx) = 0;

  virtual void enterCaseClause(CHTLJavaScriptParser::CaseClauseContext *ctx) = 0;
  virtual void exitCaseClause(CHTLJavaScriptParser::CaseClauseContext *ctx) = 0;

  virtual void enterDefaultClause(CHTLJavaScriptParser::DefaultClauseContext *ctx) = 0;
  virtual void exitDefaultClause(CHTLJavaScriptParser::DefaultClauseContext *ctx) = 0;

  virtual void enterThrowStatement(CHTLJavaScriptParser::ThrowStatementContext *ctx) = 0;
  virtual void exitThrowStatement(CHTLJavaScriptParser::ThrowStatementContext *ctx) = 0;

  virtual void enterTryStatement(CHTLJavaScriptParser::TryStatementContext *ctx) = 0;
  virtual void exitTryStatement(CHTLJavaScriptParser::TryStatementContext *ctx) = 0;

  virtual void enterCatchClause(CHTLJavaScriptParser::CatchClauseContext *ctx) = 0;
  virtual void exitCatchClause(CHTLJavaScriptParser::CatchClauseContext *ctx) = 0;

  virtual void enterCatchParameter(CHTLJavaScriptParser::CatchParameterContext *ctx) = 0;
  virtual void exitCatchParameter(CHTLJavaScriptParser::CatchParameterContext *ctx) = 0;

  virtual void enterFinallyClause(CHTLJavaScriptParser::FinallyClauseContext *ctx) = 0;
  virtual void exitFinallyClause(CHTLJavaScriptParser::FinallyClauseContext *ctx) = 0;

  virtual void enterDebuggerStatement(CHTLJavaScriptParser::DebuggerStatementContext *ctx) = 0;
  virtual void exitDebuggerStatement(CHTLJavaScriptParser::DebuggerStatementContext *ctx) = 0;

  virtual void enterImportStatement(CHTLJavaScriptParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(CHTLJavaScriptParser::ImportStatementContext *ctx) = 0;

  virtual void enterImportClause(CHTLJavaScriptParser::ImportClauseContext *ctx) = 0;
  virtual void exitImportClause(CHTLJavaScriptParser::ImportClauseContext *ctx) = 0;

  virtual void enterImportedDefaultBinding(CHTLJavaScriptParser::ImportedDefaultBindingContext *ctx) = 0;
  virtual void exitImportedDefaultBinding(CHTLJavaScriptParser::ImportedDefaultBindingContext *ctx) = 0;

  virtual void enterNamespaceImport(CHTLJavaScriptParser::NamespaceImportContext *ctx) = 0;
  virtual void exitNamespaceImport(CHTLJavaScriptParser::NamespaceImportContext *ctx) = 0;

  virtual void enterNamedImports(CHTLJavaScriptParser::NamedImportsContext *ctx) = 0;
  virtual void exitNamedImports(CHTLJavaScriptParser::NamedImportsContext *ctx) = 0;

  virtual void enterImportsList(CHTLJavaScriptParser::ImportsListContext *ctx) = 0;
  virtual void exitImportsList(CHTLJavaScriptParser::ImportsListContext *ctx) = 0;

  virtual void enterImportSpecifier(CHTLJavaScriptParser::ImportSpecifierContext *ctx) = 0;
  virtual void exitImportSpecifier(CHTLJavaScriptParser::ImportSpecifierContext *ctx) = 0;

  virtual void enterModuleSpecifier(CHTLJavaScriptParser::ModuleSpecifierContext *ctx) = 0;
  virtual void exitModuleSpecifier(CHTLJavaScriptParser::ModuleSpecifierContext *ctx) = 0;

  virtual void enterExportStatement(CHTLJavaScriptParser::ExportStatementContext *ctx) = 0;
  virtual void exitExportStatement(CHTLJavaScriptParser::ExportStatementContext *ctx) = 0;

  virtual void enterExportClause(CHTLJavaScriptParser::ExportClauseContext *ctx) = 0;
  virtual void exitExportClause(CHTLJavaScriptParser::ExportClauseContext *ctx) = 0;

  virtual void enterExportsList(CHTLJavaScriptParser::ExportsListContext *ctx) = 0;
  virtual void exitExportsList(CHTLJavaScriptParser::ExportsListContext *ctx) = 0;

  virtual void enterExportSpecifier(CHTLJavaScriptParser::ExportSpecifierContext *ctx) = 0;
  virtual void exitExportSpecifier(CHTLJavaScriptParser::ExportSpecifierContext *ctx) = 0;

  virtual void enterExpression(CHTLJavaScriptParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(CHTLJavaScriptParser::ExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(CHTLJavaScriptParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(CHTLJavaScriptParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(CHTLJavaScriptParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(CHTLJavaScriptParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterConditionalExpression(CHTLJavaScriptParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(CHTLJavaScriptParser::ConditionalExpressionContext *ctx) = 0;

  virtual void enterCoalesceExpression(CHTLJavaScriptParser::CoalesceExpressionContext *ctx) = 0;
  virtual void exitCoalesceExpression(CHTLJavaScriptParser::CoalesceExpressionContext *ctx) = 0;

  virtual void enterLogicalORExpression(CHTLJavaScriptParser::LogicalORExpressionContext *ctx) = 0;
  virtual void exitLogicalORExpression(CHTLJavaScriptParser::LogicalORExpressionContext *ctx) = 0;

  virtual void enterLogicalANDExpression(CHTLJavaScriptParser::LogicalANDExpressionContext *ctx) = 0;
  virtual void exitLogicalANDExpression(CHTLJavaScriptParser::LogicalANDExpressionContext *ctx) = 0;

  virtual void enterBitwiseORExpression(CHTLJavaScriptParser::BitwiseORExpressionContext *ctx) = 0;
  virtual void exitBitwiseORExpression(CHTLJavaScriptParser::BitwiseORExpressionContext *ctx) = 0;

  virtual void enterBitwiseXORExpression(CHTLJavaScriptParser::BitwiseXORExpressionContext *ctx) = 0;
  virtual void exitBitwiseXORExpression(CHTLJavaScriptParser::BitwiseXORExpressionContext *ctx) = 0;

  virtual void enterBitwiseANDExpression(CHTLJavaScriptParser::BitwiseANDExpressionContext *ctx) = 0;
  virtual void exitBitwiseANDExpression(CHTLJavaScriptParser::BitwiseANDExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(CHTLJavaScriptParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(CHTLJavaScriptParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(CHTLJavaScriptParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(CHTLJavaScriptParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(CHTLJavaScriptParser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(CHTLJavaScriptParser::ShiftExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(CHTLJavaScriptParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(CHTLJavaScriptParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(CHTLJavaScriptParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(CHTLJavaScriptParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterExponentiationExpression(CHTLJavaScriptParser::ExponentiationExpressionContext *ctx) = 0;
  virtual void exitExponentiationExpression(CHTLJavaScriptParser::ExponentiationExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(CHTLJavaScriptParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(CHTLJavaScriptParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterUpdateExpression(CHTLJavaScriptParser::UpdateExpressionContext *ctx) = 0;
  virtual void exitUpdateExpression(CHTLJavaScriptParser::UpdateExpressionContext *ctx) = 0;

  virtual void enterLeftHandSideExpression(CHTLJavaScriptParser::LeftHandSideExpressionContext *ctx) = 0;
  virtual void exitLeftHandSideExpression(CHTLJavaScriptParser::LeftHandSideExpressionContext *ctx) = 0;

  virtual void enterNewExpression(CHTLJavaScriptParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(CHTLJavaScriptParser::NewExpressionContext *ctx) = 0;

  virtual void enterSuperCall(CHTLJavaScriptParser::SuperCallContext *ctx) = 0;
  virtual void exitSuperCall(CHTLJavaScriptParser::SuperCallContext *ctx) = 0;

  virtual void enterImportCall(CHTLJavaScriptParser::ImportCallContext *ctx) = 0;
  virtual void exitImportCall(CHTLJavaScriptParser::ImportCallContext *ctx) = 0;

  virtual void enterArguments(CHTLJavaScriptParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(CHTLJavaScriptParser::ArgumentsContext *ctx) = 0;

  virtual void enterArgumentList(CHTLJavaScriptParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(CHTLJavaScriptParser::ArgumentListContext *ctx) = 0;

  virtual void enterArgument(CHTLJavaScriptParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(CHTLJavaScriptParser::ArgumentContext *ctx) = 0;

  virtual void enterMetaProperty(CHTLJavaScriptParser::MetaPropertyContext *ctx) = 0;
  virtual void exitMetaProperty(CHTLJavaScriptParser::MetaPropertyContext *ctx) = 0;

  virtual void enterParenthesizedExpression(CHTLJavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;
  virtual void exitParenthesizedExpression(CHTLJavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;

  virtual void enterNullLiteral(CHTLJavaScriptParser::NullLiteralContext *ctx) = 0;
  virtual void exitNullLiteral(CHTLJavaScriptParser::NullLiteralContext *ctx) = 0;

  virtual void enterBooleanLiteral(CHTLJavaScriptParser::BooleanLiteralContext *ctx) = 0;
  virtual void exitBooleanLiteral(CHTLJavaScriptParser::BooleanLiteralContext *ctx) = 0;

  virtual void enterNumericLiteral(CHTLJavaScriptParser::NumericLiteralContext *ctx) = 0;
  virtual void exitNumericLiteral(CHTLJavaScriptParser::NumericLiteralContext *ctx) = 0;

  virtual void enterStringLiteral(CHTLJavaScriptParser::StringLiteralContext *ctx) = 0;
  virtual void exitStringLiteral(CHTLJavaScriptParser::StringLiteralContext *ctx) = 0;

  virtual void enterArrayLiteral(CHTLJavaScriptParser::ArrayLiteralContext *ctx) = 0;
  virtual void exitArrayLiteral(CHTLJavaScriptParser::ArrayLiteralContext *ctx) = 0;

  virtual void enterElementList(CHTLJavaScriptParser::ElementListContext *ctx) = 0;
  virtual void exitElementList(CHTLJavaScriptParser::ElementListContext *ctx) = 0;

  virtual void enterArrayElement(CHTLJavaScriptParser::ArrayElementContext *ctx) = 0;
  virtual void exitArrayElement(CHTLJavaScriptParser::ArrayElementContext *ctx) = 0;

  virtual void enterObjectLiteral(CHTLJavaScriptParser::ObjectLiteralContext *ctx) = 0;
  virtual void exitObjectLiteral(CHTLJavaScriptParser::ObjectLiteralContext *ctx) = 0;

  virtual void enterPropertyDefinitionList(CHTLJavaScriptParser::PropertyDefinitionListContext *ctx) = 0;
  virtual void exitPropertyDefinitionList(CHTLJavaScriptParser::PropertyDefinitionListContext *ctx) = 0;

  virtual void enterPropertyDefinition(CHTLJavaScriptParser::PropertyDefinitionContext *ctx) = 0;
  virtual void exitPropertyDefinition(CHTLJavaScriptParser::PropertyDefinitionContext *ctx) = 0;

  virtual void enterFunctionExpression(CHTLJavaScriptParser::FunctionExpressionContext *ctx) = 0;
  virtual void exitFunctionExpression(CHTLJavaScriptParser::FunctionExpressionContext *ctx) = 0;

  virtual void enterGeneratorExpression(CHTLJavaScriptParser::GeneratorExpressionContext *ctx) = 0;
  virtual void exitGeneratorExpression(CHTLJavaScriptParser::GeneratorExpressionContext *ctx) = 0;

  virtual void enterAsyncFunctionExpression(CHTLJavaScriptParser::AsyncFunctionExpressionContext *ctx) = 0;
  virtual void exitAsyncFunctionExpression(CHTLJavaScriptParser::AsyncFunctionExpressionContext *ctx) = 0;

  virtual void enterAsyncGeneratorExpression(CHTLJavaScriptParser::AsyncGeneratorExpressionContext *ctx) = 0;
  virtual void exitAsyncGeneratorExpression(CHTLJavaScriptParser::AsyncGeneratorExpressionContext *ctx) = 0;

  virtual void enterClassExpression(CHTLJavaScriptParser::ClassExpressionContext *ctx) = 0;
  virtual void exitClassExpression(CHTLJavaScriptParser::ClassExpressionContext *ctx) = 0;

  virtual void enterArrowFunction(CHTLJavaScriptParser::ArrowFunctionContext *ctx) = 0;
  virtual void exitArrowFunction(CHTLJavaScriptParser::ArrowFunctionContext *ctx) = 0;

  virtual void enterAsyncArrowFunction(CHTLJavaScriptParser::AsyncArrowFunctionContext *ctx) = 0;
  virtual void exitAsyncArrowFunction(CHTLJavaScriptParser::AsyncArrowFunctionContext *ctx) = 0;

  virtual void enterArrowParameters(CHTLJavaScriptParser::ArrowParametersContext *ctx) = 0;
  virtual void exitArrowParameters(CHTLJavaScriptParser::ArrowParametersContext *ctx) = 0;

  virtual void enterArrowBody(CHTLJavaScriptParser::ArrowBodyContext *ctx) = 0;
  virtual void exitArrowBody(CHTLJavaScriptParser::ArrowBodyContext *ctx) = 0;

  virtual void enterYieldExpression(CHTLJavaScriptParser::YieldExpressionContext *ctx) = 0;
  virtual void exitYieldExpression(CHTLJavaScriptParser::YieldExpressionContext *ctx) = 0;

  virtual void enterTemplateLiteral(CHTLJavaScriptParser::TemplateLiteralContext *ctx) = 0;
  virtual void exitTemplateLiteral(CHTLJavaScriptParser::TemplateLiteralContext *ctx) = 0;

  virtual void enterTemplateSpans(CHTLJavaScriptParser::TemplateSpansContext *ctx) = 0;
  virtual void exitTemplateSpans(CHTLJavaScriptParser::TemplateSpansContext *ctx) = 0;

  virtual void enterTemplateSpan(CHTLJavaScriptParser::TemplateSpanContext *ctx) = 0;
  virtual void exitTemplateSpan(CHTLJavaScriptParser::TemplateSpanContext *ctx) = 0;

  virtual void enterTemplateMiddle(CHTLJavaScriptParser::TemplateMiddleContext *ctx) = 0;
  virtual void exitTemplateMiddle(CHTLJavaScriptParser::TemplateMiddleContext *ctx) = 0;

  virtual void enterRegularExpressionLiteral(CHTLJavaScriptParser::RegularExpressionLiteralContext *ctx) = 0;
  virtual void exitRegularExpressionLiteral(CHTLJavaScriptParser::RegularExpressionLiteralContext *ctx) = 0;

  virtual void enterFormalParameterList(CHTLJavaScriptParser::FormalParameterListContext *ctx) = 0;
  virtual void exitFormalParameterList(CHTLJavaScriptParser::FormalParameterListContext *ctx) = 0;

  virtual void enterFormalParameter(CHTLJavaScriptParser::FormalParameterContext *ctx) = 0;
  virtual void exitFormalParameter(CHTLJavaScriptParser::FormalParameterContext *ctx) = 0;

  virtual void enterRestParameter(CHTLJavaScriptParser::RestParameterContext *ctx) = 0;
  virtual void exitRestParameter(CHTLJavaScriptParser::RestParameterContext *ctx) = 0;

  virtual void enterBindingElement(CHTLJavaScriptParser::BindingElementContext *ctx) = 0;
  virtual void exitBindingElement(CHTLJavaScriptParser::BindingElementContext *ctx) = 0;

  virtual void enterBindingPattern(CHTLJavaScriptParser::BindingPatternContext *ctx) = 0;
  virtual void exitBindingPattern(CHTLJavaScriptParser::BindingPatternContext *ctx) = 0;

  virtual void enterObjectBindingPattern(CHTLJavaScriptParser::ObjectBindingPatternContext *ctx) = 0;
  virtual void exitObjectBindingPattern(CHTLJavaScriptParser::ObjectBindingPatternContext *ctx) = 0;

  virtual void enterBindingPropertyList(CHTLJavaScriptParser::BindingPropertyListContext *ctx) = 0;
  virtual void exitBindingPropertyList(CHTLJavaScriptParser::BindingPropertyListContext *ctx) = 0;

  virtual void enterBindingProperty(CHTLJavaScriptParser::BindingPropertyContext *ctx) = 0;
  virtual void exitBindingProperty(CHTLJavaScriptParser::BindingPropertyContext *ctx) = 0;

  virtual void enterArrayBindingPattern(CHTLJavaScriptParser::ArrayBindingPatternContext *ctx) = 0;
  virtual void exitArrayBindingPattern(CHTLJavaScriptParser::ArrayBindingPatternContext *ctx) = 0;

  virtual void enterBindingElementList(CHTLJavaScriptParser::BindingElementListContext *ctx) = 0;
  virtual void exitBindingElementList(CHTLJavaScriptParser::BindingElementListContext *ctx) = 0;

  virtual void enterBindingElision(CHTLJavaScriptParser::BindingElisionContext *ctx) = 0;
  virtual void exitBindingElision(CHTLJavaScriptParser::BindingElisionContext *ctx) = 0;

  virtual void enterFunctionBody(CHTLJavaScriptParser::FunctionBodyContext *ctx) = 0;
  virtual void exitFunctionBody(CHTLJavaScriptParser::FunctionBodyContext *ctx) = 0;

  virtual void enterInitializer(CHTLJavaScriptParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(CHTLJavaScriptParser::InitializerContext *ctx) = 0;

  virtual void enterBindingIdentifier(CHTLJavaScriptParser::BindingIdentifierContext *ctx) = 0;
  virtual void exitBindingIdentifier(CHTLJavaScriptParser::BindingIdentifierContext *ctx) = 0;

  virtual void enterIdentifier(CHTLJavaScriptParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(CHTLJavaScriptParser::IdentifierContext *ctx) = 0;

  virtual void enterIdentifierName(CHTLJavaScriptParser::IdentifierNameContext *ctx) = 0;
  virtual void exitIdentifierName(CHTLJavaScriptParser::IdentifierNameContext *ctx) = 0;

  virtual void enterReservedWord(CHTLJavaScriptParser::ReservedWordContext *ctx) = 0;
  virtual void exitReservedWord(CHTLJavaScriptParser::ReservedWordContext *ctx) = 0;

  virtual void enterKeyword(CHTLJavaScriptParser::KeywordContext *ctx) = 0;
  virtual void exitKeyword(CHTLJavaScriptParser::KeywordContext *ctx) = 0;

  virtual void enterFutureReservedWord(CHTLJavaScriptParser::FutureReservedWordContext *ctx) = 0;
  virtual void exitFutureReservedWord(CHTLJavaScriptParser::FutureReservedWordContext *ctx) = 0;


};

