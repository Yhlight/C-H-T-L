
// Generated from grammars/js/JavaScript.g4 by ANTLR 4.9.2

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

  virtual void enterSourceElement(JavaScriptParser::SourceElementContext *ctx) = 0;
  virtual void exitSourceElement(JavaScriptParser::SourceElementContext *ctx) = 0;

  virtual void enterStatement(JavaScriptParser::StatementContext *ctx) = 0;
  virtual void exitStatement(JavaScriptParser::StatementContext *ctx) = 0;

  virtual void enterBlock(JavaScriptParser::BlockContext *ctx) = 0;
  virtual void exitBlock(JavaScriptParser::BlockContext *ctx) = 0;

  virtual void enterStatementList(JavaScriptParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(JavaScriptParser::StatementListContext *ctx) = 0;

  virtual void enterVariableStatement(JavaScriptParser::VariableStatementContext *ctx) = 0;
  virtual void exitVariableStatement(JavaScriptParser::VariableStatementContext *ctx) = 0;

  virtual void enterVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) = 0;
  virtual void exitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) = 0;

  virtual void enterVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(JavaScriptParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterBindingPattern(JavaScriptParser::BindingPatternContext *ctx) = 0;
  virtual void exitBindingPattern(JavaScriptParser::BindingPatternContext *ctx) = 0;

  virtual void enterObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext *ctx) = 0;
  virtual void exitObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext *ctx) = 0;

  virtual void enterBindingProperty(JavaScriptParser::BindingPropertyContext *ctx) = 0;
  virtual void exitBindingProperty(JavaScriptParser::BindingPropertyContext *ctx) = 0;

  virtual void enterBindingElement(JavaScriptParser::BindingElementContext *ctx) = 0;
  virtual void exitBindingElement(JavaScriptParser::BindingElementContext *ctx) = 0;

  virtual void enterArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext *ctx) = 0;
  virtual void exitArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext *ctx) = 0;

  virtual void enterPropertyName(JavaScriptParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(JavaScriptParser::PropertyNameContext *ctx) = 0;

  virtual void enterIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) = 0;
  virtual void exitIdentifierName(JavaScriptParser::IdentifierNameContext *ctx) = 0;

  virtual void enterReservedWord(JavaScriptParser::ReservedWordContext *ctx) = 0;
  virtual void exitReservedWord(JavaScriptParser::ReservedWordContext *ctx) = 0;

  virtual void enterKeyword(JavaScriptParser::KeywordContext *ctx) = 0;
  virtual void exitKeyword(JavaScriptParser::KeywordContext *ctx) = 0;

  virtual void enterFutureReservedWord(JavaScriptParser::FutureReservedWordContext *ctx) = 0;
  virtual void exitFutureReservedWord(JavaScriptParser::FutureReservedWordContext *ctx) = 0;

  virtual void enterStringLiteral(JavaScriptParser::StringLiteralContext *ctx) = 0;
  virtual void exitStringLiteral(JavaScriptParser::StringLiteralContext *ctx) = 0;

  virtual void enterNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) = 0;
  virtual void exitNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) = 0;

  virtual void enterInitializer(JavaScriptParser::InitializerContext *ctx) = 0;
  virtual void exitInitializer(JavaScriptParser::InitializerContext *ctx) = 0;

  virtual void enterEmptyStatement(JavaScriptParser::EmptyStatementContext *ctx) = 0;
  virtual void exitEmptyStatement(JavaScriptParser::EmptyStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(JavaScriptParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(JavaScriptParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfStatement(JavaScriptParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(JavaScriptParser::IfStatementContext *ctx) = 0;

  virtual void enterIterationStatement(JavaScriptParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(JavaScriptParser::IterationStatementContext *ctx) = 0;

  virtual void enterContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(JavaScriptParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(JavaScriptParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) = 0;

  virtual void enterYieldStatement(JavaScriptParser::YieldStatementContext *ctx) = 0;
  virtual void exitYieldStatement(JavaScriptParser::YieldStatementContext *ctx) = 0;

  virtual void enterWithStatement(JavaScriptParser::WithStatementContext *ctx) = 0;
  virtual void exitWithStatement(JavaScriptParser::WithStatementContext *ctx) = 0;

  virtual void enterLabelledStatement(JavaScriptParser::LabelledStatementContext *ctx) = 0;
  virtual void exitLabelledStatement(JavaScriptParser::LabelledStatementContext *ctx) = 0;

  virtual void enterSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) = 0;

  virtual void enterCaseBlock(JavaScriptParser::CaseBlockContext *ctx) = 0;
  virtual void exitCaseBlock(JavaScriptParser::CaseBlockContext *ctx) = 0;

  virtual void enterCaseClauses(JavaScriptParser::CaseClausesContext *ctx) = 0;
  virtual void exitCaseClauses(JavaScriptParser::CaseClausesContext *ctx) = 0;

  virtual void enterCaseClause(JavaScriptParser::CaseClauseContext *ctx) = 0;
  virtual void exitCaseClause(JavaScriptParser::CaseClauseContext *ctx) = 0;

  virtual void enterDefaultClause(JavaScriptParser::DefaultClauseContext *ctx) = 0;
  virtual void exitDefaultClause(JavaScriptParser::DefaultClauseContext *ctx) = 0;

  virtual void enterThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) = 0;
  virtual void exitThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) = 0;

  virtual void enterTryStatement(JavaScriptParser::TryStatementContext *ctx) = 0;
  virtual void exitTryStatement(JavaScriptParser::TryStatementContext *ctx) = 0;

  virtual void enterCatchBlock(JavaScriptParser::CatchBlockContext *ctx) = 0;
  virtual void exitCatchBlock(JavaScriptParser::CatchBlockContext *ctx) = 0;

  virtual void enterFinallyBlock(JavaScriptParser::FinallyBlockContext *ctx) = 0;
  virtual void exitFinallyBlock(JavaScriptParser::FinallyBlockContext *ctx) = 0;

  virtual void enterDebuggerStatement(JavaScriptParser::DebuggerStatementContext *ctx) = 0;
  virtual void exitDebuggerStatement(JavaScriptParser::DebuggerStatementContext *ctx) = 0;

  virtual void enterFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) = 0;
  virtual void exitFormalParameterList(JavaScriptParser::FormalParameterListContext *ctx) = 0;

  virtual void enterFormalParameterArg(JavaScriptParser::FormalParameterArgContext *ctx) = 0;
  virtual void exitFormalParameterArg(JavaScriptParser::FormalParameterArgContext *ctx) = 0;

  virtual void enterFunctionBody(JavaScriptParser::FunctionBodyContext *ctx) = 0;
  virtual void exitFunctionBody(JavaScriptParser::FunctionBodyContext *ctx) = 0;

  virtual void enterClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) = 0;
  virtual void exitClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) = 0;

  virtual void enterClassBody(JavaScriptParser::ClassBodyContext *ctx) = 0;
  virtual void exitClassBody(JavaScriptParser::ClassBodyContext *ctx) = 0;

  virtual void enterClassElement(JavaScriptParser::ClassElementContext *ctx) = 0;
  virtual void exitClassElement(JavaScriptParser::ClassElementContext *ctx) = 0;

  virtual void enterMethodDefinition(JavaScriptParser::MethodDefinitionContext *ctx) = 0;
  virtual void exitMethodDefinition(JavaScriptParser::MethodDefinitionContext *ctx) = 0;

  virtual void enterImportStatement(JavaScriptParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(JavaScriptParser::ImportStatementContext *ctx) = 0;

  virtual void enterImportClause(JavaScriptParser::ImportClauseContext *ctx) = 0;
  virtual void exitImportClause(JavaScriptParser::ImportClauseContext *ctx) = 0;

  virtual void enterDefaultImport(JavaScriptParser::DefaultImportContext *ctx) = 0;
  virtual void exitDefaultImport(JavaScriptParser::DefaultImportContext *ctx) = 0;

  virtual void enterNameSpaceImport(JavaScriptParser::NameSpaceImportContext *ctx) = 0;
  virtual void exitNameSpaceImport(JavaScriptParser::NameSpaceImportContext *ctx) = 0;

  virtual void enterNamedImports(JavaScriptParser::NamedImportsContext *ctx) = 0;
  virtual void exitNamedImports(JavaScriptParser::NamedImportsContext *ctx) = 0;

  virtual void enterImportSpecifier(JavaScriptParser::ImportSpecifierContext *ctx) = 0;
  virtual void exitImportSpecifier(JavaScriptParser::ImportSpecifierContext *ctx) = 0;

  virtual void enterFromClause(JavaScriptParser::FromClauseContext *ctx) = 0;
  virtual void exitFromClause(JavaScriptParser::FromClauseContext *ctx) = 0;

  virtual void enterModuleSpecifier(JavaScriptParser::ModuleSpecifierContext *ctx) = 0;
  virtual void exitModuleSpecifier(JavaScriptParser::ModuleSpecifierContext *ctx) = 0;

  virtual void enterExportStatement(JavaScriptParser::ExportStatementContext *ctx) = 0;
  virtual void exitExportStatement(JavaScriptParser::ExportStatementContext *ctx) = 0;

  virtual void enterExportClause(JavaScriptParser::ExportClauseContext *ctx) = 0;
  virtual void exitExportClause(JavaScriptParser::ExportClauseContext *ctx) = 0;

  virtual void enterNamedExports(JavaScriptParser::NamedExportsContext *ctx) = 0;
  virtual void exitNamedExports(JavaScriptParser::NamedExportsContext *ctx) = 0;

  virtual void enterExportSpecifier(JavaScriptParser::ExportSpecifierContext *ctx) = 0;
  virtual void exitExportSpecifier(JavaScriptParser::ExportSpecifierContext *ctx) = 0;

  virtual void enterDefaultExport(JavaScriptParser::DefaultExportContext *ctx) = 0;
  virtual void exitDefaultExport(JavaScriptParser::DefaultExportContext *ctx) = 0;

  virtual void enterExpression(JavaScriptParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(JavaScriptParser::ExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterConditionalExpression(JavaScriptParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(JavaScriptParser::ConditionalExpressionContext *ctx) = 0;

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

  virtual void enterUnaryExpression(JavaScriptParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(JavaScriptParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterUnaryOperator(JavaScriptParser::UnaryOperatorContext *ctx) = 0;
  virtual void exitUnaryOperator(JavaScriptParser::UnaryOperatorContext *ctx) = 0;

  virtual void enterPostfixExpression(JavaScriptParser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(JavaScriptParser::PostfixExpressionContext *ctx) = 0;

  virtual void enterLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext *ctx) = 0;
  virtual void exitLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext *ctx) = 0;

  virtual void enterCallExpression(JavaScriptParser::CallExpressionContext *ctx) = 0;
  virtual void exitCallExpression(JavaScriptParser::CallExpressionContext *ctx) = 0;

  virtual void enterArguments(JavaScriptParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(JavaScriptParser::ArgumentsContext *ctx) = 0;

  virtual void enterArgumentList(JavaScriptParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(JavaScriptParser::ArgumentListContext *ctx) = 0;

  virtual void enterNewExpression(JavaScriptParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(JavaScriptParser::NewExpressionContext *ctx) = 0;

  virtual void enterSuperProperty(JavaScriptParser::SuperPropertyContext *ctx) = 0;
  virtual void exitSuperProperty(JavaScriptParser::SuperPropertyContext *ctx) = 0;

  virtual void enterFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx) = 0;
  virtual void exitFunctionExpression(JavaScriptParser::FunctionExpressionContext *ctx) = 0;

  virtual void enterClassExpression(JavaScriptParser::ClassExpressionContext *ctx) = 0;
  virtual void exitClassExpression(JavaScriptParser::ClassExpressionContext *ctx) = 0;

  virtual void enterIdentifier(JavaScriptParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(JavaScriptParser::IdentifierContext *ctx) = 0;

  virtual void enterThisExpression(JavaScriptParser::ThisExpressionContext *ctx) = 0;
  virtual void exitThisExpression(JavaScriptParser::ThisExpressionContext *ctx) = 0;

  virtual void enterArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) = 0;
  virtual void exitArrayLiteral(JavaScriptParser::ArrayLiteralContext *ctx) = 0;

  virtual void enterElementList(JavaScriptParser::ElementListContext *ctx) = 0;
  virtual void exitElementList(JavaScriptParser::ElementListContext *ctx) = 0;

  virtual void enterObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) = 0;
  virtual void exitObjectLiteral(JavaScriptParser::ObjectLiteralContext *ctx) = 0;

  virtual void enterPropertyDefinition(JavaScriptParser::PropertyDefinitionContext *ctx) = 0;
  virtual void exitPropertyDefinition(JavaScriptParser::PropertyDefinitionContext *ctx) = 0;

  virtual void enterParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;
  virtual void exitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) = 0;

  virtual void enterTemplateLiteral(JavaScriptParser::TemplateLiteralContext *ctx) = 0;
  virtual void exitTemplateLiteral(JavaScriptParser::TemplateLiteralContext *ctx) = 0;

  virtual void enterTemplateElement(JavaScriptParser::TemplateElementContext *ctx) = 0;
  virtual void exitTemplateElement(JavaScriptParser::TemplateElementContext *ctx) = 0;

  virtual void enterTemplateCharacters(JavaScriptParser::TemplateCharactersContext *ctx) = 0;
  virtual void exitTemplateCharacters(JavaScriptParser::TemplateCharactersContext *ctx) = 0;

  virtual void enterTemplateSubstitution(JavaScriptParser::TemplateSubstitutionContext *ctx) = 0;
  virtual void exitTemplateSubstitution(JavaScriptParser::TemplateSubstitutionContext *ctx) = 0;

  virtual void enterYieldExpression(JavaScriptParser::YieldExpressionContext *ctx) = 0;
  virtual void exitYieldExpression(JavaScriptParser::YieldExpressionContext *ctx) = 0;

  virtual void enterArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) = 0;
  virtual void exitArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) = 0;

  virtual void enterArrowParameters(JavaScriptParser::ArrowParametersContext *ctx) = 0;
  virtual void exitArrowParameters(JavaScriptParser::ArrowParametersContext *ctx) = 0;

  virtual void enterArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext *ctx) = 0;
  virtual void exitArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext *ctx) = 0;

  virtual void enterExpressionNoIn(JavaScriptParser::ExpressionNoInContext *ctx) = 0;
  virtual void exitExpressionNoIn(JavaScriptParser::ExpressionNoInContext *ctx) = 0;

  virtual void enterAssignmentExpressionNoIn(JavaScriptParser::AssignmentExpressionNoInContext *ctx) = 0;
  virtual void exitAssignmentExpressionNoIn(JavaScriptParser::AssignmentExpressionNoInContext *ctx) = 0;

  virtual void enterConditionalExpressionNoIn(JavaScriptParser::ConditionalExpressionNoInContext *ctx) = 0;
  virtual void exitConditionalExpressionNoIn(JavaScriptParser::ConditionalExpressionNoInContext *ctx) = 0;

  virtual void enterLogicalORExpressionNoIn(JavaScriptParser::LogicalORExpressionNoInContext *ctx) = 0;
  virtual void exitLogicalORExpressionNoIn(JavaScriptParser::LogicalORExpressionNoInContext *ctx) = 0;

  virtual void enterLogicalANDExpressionNoIn(JavaScriptParser::LogicalANDExpressionNoInContext *ctx) = 0;
  virtual void exitLogicalANDExpressionNoIn(JavaScriptParser::LogicalANDExpressionNoInContext *ctx) = 0;

  virtual void enterBitwiseORExpressionNoIn(JavaScriptParser::BitwiseORExpressionNoInContext *ctx) = 0;
  virtual void exitBitwiseORExpressionNoIn(JavaScriptParser::BitwiseORExpressionNoInContext *ctx) = 0;

  virtual void enterBitwiseXORExpressionNoIn(JavaScriptParser::BitwiseXORExpressionNoInContext *ctx) = 0;
  virtual void exitBitwiseXORExpressionNoIn(JavaScriptParser::BitwiseXORExpressionNoInContext *ctx) = 0;

  virtual void enterBitwiseANDExpressionNoIn(JavaScriptParser::BitwiseANDExpressionNoInContext *ctx) = 0;
  virtual void exitBitwiseANDExpressionNoIn(JavaScriptParser::BitwiseANDExpressionNoInContext *ctx) = 0;

  virtual void enterEqualityExpressionNoIn(JavaScriptParser::EqualityExpressionNoInContext *ctx) = 0;
  virtual void exitEqualityExpressionNoIn(JavaScriptParser::EqualityExpressionNoInContext *ctx) = 0;

  virtual void enterRelationalExpressionNoIn(JavaScriptParser::RelationalExpressionNoInContext *ctx) = 0;
  virtual void exitRelationalExpressionNoIn(JavaScriptParser::RelationalExpressionNoInContext *ctx) = 0;

  virtual void enterShiftExpressionNoIn(JavaScriptParser::ShiftExpressionNoInContext *ctx) = 0;
  virtual void exitShiftExpressionNoIn(JavaScriptParser::ShiftExpressionNoInContext *ctx) = 0;

  virtual void enterAdditiveExpressionNoIn(JavaScriptParser::AdditiveExpressionNoInContext *ctx) = 0;
  virtual void exitAdditiveExpressionNoIn(JavaScriptParser::AdditiveExpressionNoInContext *ctx) = 0;

  virtual void enterMultiplicativeExpressionNoIn(JavaScriptParser::MultiplicativeExpressionNoInContext *ctx) = 0;
  virtual void exitMultiplicativeExpressionNoIn(JavaScriptParser::MultiplicativeExpressionNoInContext *ctx) = 0;

  virtual void enterUnaryExpressionNoIn(JavaScriptParser::UnaryExpressionNoInContext *ctx) = 0;
  virtual void exitUnaryExpressionNoIn(JavaScriptParser::UnaryExpressionNoInContext *ctx) = 0;

  virtual void enterSourceElements(JavaScriptParser::SourceElementsContext *ctx) = 0;
  virtual void exitSourceElements(JavaScriptParser::SourceElementsContext *ctx) = 0;


};

