
// Generated from grammars/js/JavaScript.g4 by ANTLR 4.9.2

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

  virtual void enterSourceElement(JavaScriptParser::SourceElementContext * /*ctx*/) override { }
  virtual void exitSourceElement(JavaScriptParser::SourceElementContext * /*ctx*/) override { }

  virtual void enterStatement(JavaScriptParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(JavaScriptParser::StatementContext * /*ctx*/) override { }

  virtual void enterBlock(JavaScriptParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(JavaScriptParser::BlockContext * /*ctx*/) override { }

  virtual void enterStatementList(JavaScriptParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(JavaScriptParser::StatementListContext * /*ctx*/) override { }

  virtual void enterVariableStatement(JavaScriptParser::VariableStatementContext * /*ctx*/) override { }
  virtual void exitVariableStatement(JavaScriptParser::VariableStatementContext * /*ctx*/) override { }

  virtual void enterVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext * /*ctx*/) override { }
  virtual void exitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(JavaScriptParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(JavaScriptParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterBindingPattern(JavaScriptParser::BindingPatternContext * /*ctx*/) override { }
  virtual void exitBindingPattern(JavaScriptParser::BindingPatternContext * /*ctx*/) override { }

  virtual void enterObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext * /*ctx*/) override { }
  virtual void exitObjectBindingPattern(JavaScriptParser::ObjectBindingPatternContext * /*ctx*/) override { }

  virtual void enterBindingProperty(JavaScriptParser::BindingPropertyContext * /*ctx*/) override { }
  virtual void exitBindingProperty(JavaScriptParser::BindingPropertyContext * /*ctx*/) override { }

  virtual void enterBindingElement(JavaScriptParser::BindingElementContext * /*ctx*/) override { }
  virtual void exitBindingElement(JavaScriptParser::BindingElementContext * /*ctx*/) override { }

  virtual void enterArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext * /*ctx*/) override { }
  virtual void exitArrayBindingPattern(JavaScriptParser::ArrayBindingPatternContext * /*ctx*/) override { }

  virtual void enterPropertyName(JavaScriptParser::PropertyNameContext * /*ctx*/) override { }
  virtual void exitPropertyName(JavaScriptParser::PropertyNameContext * /*ctx*/) override { }

  virtual void enterIdentifierName(JavaScriptParser::IdentifierNameContext * /*ctx*/) override { }
  virtual void exitIdentifierName(JavaScriptParser::IdentifierNameContext * /*ctx*/) override { }

  virtual void enterReservedWord(JavaScriptParser::ReservedWordContext * /*ctx*/) override { }
  virtual void exitReservedWord(JavaScriptParser::ReservedWordContext * /*ctx*/) override { }

  virtual void enterKeyword(JavaScriptParser::KeywordContext * /*ctx*/) override { }
  virtual void exitKeyword(JavaScriptParser::KeywordContext * /*ctx*/) override { }

  virtual void enterFutureReservedWord(JavaScriptParser::FutureReservedWordContext * /*ctx*/) override { }
  virtual void exitFutureReservedWord(JavaScriptParser::FutureReservedWordContext * /*ctx*/) override { }

  virtual void enterStringLiteral(JavaScriptParser::StringLiteralContext * /*ctx*/) override { }
  virtual void exitStringLiteral(JavaScriptParser::StringLiteralContext * /*ctx*/) override { }

  virtual void enterNumericLiteral(JavaScriptParser::NumericLiteralContext * /*ctx*/) override { }
  virtual void exitNumericLiteral(JavaScriptParser::NumericLiteralContext * /*ctx*/) override { }

  virtual void enterInitializer(JavaScriptParser::InitializerContext * /*ctx*/) override { }
  virtual void exitInitializer(JavaScriptParser::InitializerContext * /*ctx*/) override { }

  virtual void enterEmptyStatement(JavaScriptParser::EmptyStatementContext * /*ctx*/) override { }
  virtual void exitEmptyStatement(JavaScriptParser::EmptyStatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(JavaScriptParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(JavaScriptParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterIfStatement(JavaScriptParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(JavaScriptParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterIterationStatement(JavaScriptParser::IterationStatementContext * /*ctx*/) override { }
  virtual void exitIterationStatement(JavaScriptParser::IterationStatementContext * /*ctx*/) override { }

  virtual void enterContinueStatement(JavaScriptParser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(JavaScriptParser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterBreakStatement(JavaScriptParser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(JavaScriptParser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(JavaScriptParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(JavaScriptParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterYieldStatement(JavaScriptParser::YieldStatementContext * /*ctx*/) override { }
  virtual void exitYieldStatement(JavaScriptParser::YieldStatementContext * /*ctx*/) override { }

  virtual void enterWithStatement(JavaScriptParser::WithStatementContext * /*ctx*/) override { }
  virtual void exitWithStatement(JavaScriptParser::WithStatementContext * /*ctx*/) override { }

  virtual void enterLabelledStatement(JavaScriptParser::LabelledStatementContext * /*ctx*/) override { }
  virtual void exitLabelledStatement(JavaScriptParser::LabelledStatementContext * /*ctx*/) override { }

  virtual void enterSwitchStatement(JavaScriptParser::SwitchStatementContext * /*ctx*/) override { }
  virtual void exitSwitchStatement(JavaScriptParser::SwitchStatementContext * /*ctx*/) override { }

  virtual void enterCaseBlock(JavaScriptParser::CaseBlockContext * /*ctx*/) override { }
  virtual void exitCaseBlock(JavaScriptParser::CaseBlockContext * /*ctx*/) override { }

  virtual void enterCaseClauses(JavaScriptParser::CaseClausesContext * /*ctx*/) override { }
  virtual void exitCaseClauses(JavaScriptParser::CaseClausesContext * /*ctx*/) override { }

  virtual void enterCaseClause(JavaScriptParser::CaseClauseContext * /*ctx*/) override { }
  virtual void exitCaseClause(JavaScriptParser::CaseClauseContext * /*ctx*/) override { }

  virtual void enterDefaultClause(JavaScriptParser::DefaultClauseContext * /*ctx*/) override { }
  virtual void exitDefaultClause(JavaScriptParser::DefaultClauseContext * /*ctx*/) override { }

  virtual void enterThrowStatement(JavaScriptParser::ThrowStatementContext * /*ctx*/) override { }
  virtual void exitThrowStatement(JavaScriptParser::ThrowStatementContext * /*ctx*/) override { }

  virtual void enterTryStatement(JavaScriptParser::TryStatementContext * /*ctx*/) override { }
  virtual void exitTryStatement(JavaScriptParser::TryStatementContext * /*ctx*/) override { }

  virtual void enterCatchBlock(JavaScriptParser::CatchBlockContext * /*ctx*/) override { }
  virtual void exitCatchBlock(JavaScriptParser::CatchBlockContext * /*ctx*/) override { }

  virtual void enterFinallyBlock(JavaScriptParser::FinallyBlockContext * /*ctx*/) override { }
  virtual void exitFinallyBlock(JavaScriptParser::FinallyBlockContext * /*ctx*/) override { }

  virtual void enterDebuggerStatement(JavaScriptParser::DebuggerStatementContext * /*ctx*/) override { }
  virtual void exitDebuggerStatement(JavaScriptParser::DebuggerStatementContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterFormalParameterList(JavaScriptParser::FormalParameterListContext * /*ctx*/) override { }
  virtual void exitFormalParameterList(JavaScriptParser::FormalParameterListContext * /*ctx*/) override { }

  virtual void enterFormalParameterArg(JavaScriptParser::FormalParameterArgContext * /*ctx*/) override { }
  virtual void exitFormalParameterArg(JavaScriptParser::FormalParameterArgContext * /*ctx*/) override { }

  virtual void enterFunctionBody(JavaScriptParser::FunctionBodyContext * /*ctx*/) override { }
  virtual void exitFunctionBody(JavaScriptParser::FunctionBodyContext * /*ctx*/) override { }

  virtual void enterClassDeclaration(JavaScriptParser::ClassDeclarationContext * /*ctx*/) override { }
  virtual void exitClassDeclaration(JavaScriptParser::ClassDeclarationContext * /*ctx*/) override { }

  virtual void enterClassBody(JavaScriptParser::ClassBodyContext * /*ctx*/) override { }
  virtual void exitClassBody(JavaScriptParser::ClassBodyContext * /*ctx*/) override { }

  virtual void enterClassElement(JavaScriptParser::ClassElementContext * /*ctx*/) override { }
  virtual void exitClassElement(JavaScriptParser::ClassElementContext * /*ctx*/) override { }

  virtual void enterMethodDefinition(JavaScriptParser::MethodDefinitionContext * /*ctx*/) override { }
  virtual void exitMethodDefinition(JavaScriptParser::MethodDefinitionContext * /*ctx*/) override { }

  virtual void enterImportStatement(JavaScriptParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(JavaScriptParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterImportClause(JavaScriptParser::ImportClauseContext * /*ctx*/) override { }
  virtual void exitImportClause(JavaScriptParser::ImportClauseContext * /*ctx*/) override { }

  virtual void enterDefaultImport(JavaScriptParser::DefaultImportContext * /*ctx*/) override { }
  virtual void exitDefaultImport(JavaScriptParser::DefaultImportContext * /*ctx*/) override { }

  virtual void enterNameSpaceImport(JavaScriptParser::NameSpaceImportContext * /*ctx*/) override { }
  virtual void exitNameSpaceImport(JavaScriptParser::NameSpaceImportContext * /*ctx*/) override { }

  virtual void enterNamedImports(JavaScriptParser::NamedImportsContext * /*ctx*/) override { }
  virtual void exitNamedImports(JavaScriptParser::NamedImportsContext * /*ctx*/) override { }

  virtual void enterImportSpecifier(JavaScriptParser::ImportSpecifierContext * /*ctx*/) override { }
  virtual void exitImportSpecifier(JavaScriptParser::ImportSpecifierContext * /*ctx*/) override { }

  virtual void enterFromClause(JavaScriptParser::FromClauseContext * /*ctx*/) override { }
  virtual void exitFromClause(JavaScriptParser::FromClauseContext * /*ctx*/) override { }

  virtual void enterModuleSpecifier(JavaScriptParser::ModuleSpecifierContext * /*ctx*/) override { }
  virtual void exitModuleSpecifier(JavaScriptParser::ModuleSpecifierContext * /*ctx*/) override { }

  virtual void enterExportStatement(JavaScriptParser::ExportStatementContext * /*ctx*/) override { }
  virtual void exitExportStatement(JavaScriptParser::ExportStatementContext * /*ctx*/) override { }

  virtual void enterExportClause(JavaScriptParser::ExportClauseContext * /*ctx*/) override { }
  virtual void exitExportClause(JavaScriptParser::ExportClauseContext * /*ctx*/) override { }

  virtual void enterNamedExports(JavaScriptParser::NamedExportsContext * /*ctx*/) override { }
  virtual void exitNamedExports(JavaScriptParser::NamedExportsContext * /*ctx*/) override { }

  virtual void enterExportSpecifier(JavaScriptParser::ExportSpecifierContext * /*ctx*/) override { }
  virtual void exitExportSpecifier(JavaScriptParser::ExportSpecifierContext * /*ctx*/) override { }

  virtual void enterDefaultExport(JavaScriptParser::DefaultExportContext * /*ctx*/) override { }
  virtual void exitDefaultExport(JavaScriptParser::DefaultExportContext * /*ctx*/) override { }

  virtual void enterExpression(JavaScriptParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(JavaScriptParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(JavaScriptParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(JavaScriptParser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(JavaScriptParser::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(JavaScriptParser::ConditionalExpressionContext * /*ctx*/) override { }

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

  virtual void enterUnaryExpression(JavaScriptParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(JavaScriptParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryOperator(JavaScriptParser::UnaryOperatorContext * /*ctx*/) override { }
  virtual void exitUnaryOperator(JavaScriptParser::UnaryOperatorContext * /*ctx*/) override { }

  virtual void enterPostfixExpression(JavaScriptParser::PostfixExpressionContext * /*ctx*/) override { }
  virtual void exitPostfixExpression(JavaScriptParser::PostfixExpressionContext * /*ctx*/) override { }

  virtual void enterLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext * /*ctx*/) override { }
  virtual void exitLeftHandSideExpression(JavaScriptParser::LeftHandSideExpressionContext * /*ctx*/) override { }

  virtual void enterCallExpression(JavaScriptParser::CallExpressionContext * /*ctx*/) override { }
  virtual void exitCallExpression(JavaScriptParser::CallExpressionContext * /*ctx*/) override { }

  virtual void enterArguments(JavaScriptParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(JavaScriptParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterArgumentList(JavaScriptParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(JavaScriptParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterNewExpression(JavaScriptParser::NewExpressionContext * /*ctx*/) override { }
  virtual void exitNewExpression(JavaScriptParser::NewExpressionContext * /*ctx*/) override { }

  virtual void enterSuperProperty(JavaScriptParser::SuperPropertyContext * /*ctx*/) override { }
  virtual void exitSuperProperty(JavaScriptParser::SuperPropertyContext * /*ctx*/) override { }

  virtual void enterFunctionExpression(JavaScriptParser::FunctionExpressionContext * /*ctx*/) override { }
  virtual void exitFunctionExpression(JavaScriptParser::FunctionExpressionContext * /*ctx*/) override { }

  virtual void enterClassExpression(JavaScriptParser::ClassExpressionContext * /*ctx*/) override { }
  virtual void exitClassExpression(JavaScriptParser::ClassExpressionContext * /*ctx*/) override { }

  virtual void enterIdentifier(JavaScriptParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(JavaScriptParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterThisExpression(JavaScriptParser::ThisExpressionContext * /*ctx*/) override { }
  virtual void exitThisExpression(JavaScriptParser::ThisExpressionContext * /*ctx*/) override { }

  virtual void enterArrayLiteral(JavaScriptParser::ArrayLiteralContext * /*ctx*/) override { }
  virtual void exitArrayLiteral(JavaScriptParser::ArrayLiteralContext * /*ctx*/) override { }

  virtual void enterElementList(JavaScriptParser::ElementListContext * /*ctx*/) override { }
  virtual void exitElementList(JavaScriptParser::ElementListContext * /*ctx*/) override { }

  virtual void enterObjectLiteral(JavaScriptParser::ObjectLiteralContext * /*ctx*/) override { }
  virtual void exitObjectLiteral(JavaScriptParser::ObjectLiteralContext * /*ctx*/) override { }

  virtual void enterPropertyDefinition(JavaScriptParser::PropertyDefinitionContext * /*ctx*/) override { }
  virtual void exitPropertyDefinition(JavaScriptParser::PropertyDefinitionContext * /*ctx*/) override { }

  virtual void enterParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext * /*ctx*/) override { }
  virtual void exitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext * /*ctx*/) override { }

  virtual void enterTemplateLiteral(JavaScriptParser::TemplateLiteralContext * /*ctx*/) override { }
  virtual void exitTemplateLiteral(JavaScriptParser::TemplateLiteralContext * /*ctx*/) override { }

  virtual void enterTemplateElement(JavaScriptParser::TemplateElementContext * /*ctx*/) override { }
  virtual void exitTemplateElement(JavaScriptParser::TemplateElementContext * /*ctx*/) override { }

  virtual void enterTemplateCharacters(JavaScriptParser::TemplateCharactersContext * /*ctx*/) override { }
  virtual void exitTemplateCharacters(JavaScriptParser::TemplateCharactersContext * /*ctx*/) override { }

  virtual void enterTemplateSubstitution(JavaScriptParser::TemplateSubstitutionContext * /*ctx*/) override { }
  virtual void exitTemplateSubstitution(JavaScriptParser::TemplateSubstitutionContext * /*ctx*/) override { }

  virtual void enterYieldExpression(JavaScriptParser::YieldExpressionContext * /*ctx*/) override { }
  virtual void exitYieldExpression(JavaScriptParser::YieldExpressionContext * /*ctx*/) override { }

  virtual void enterArrowFunction(JavaScriptParser::ArrowFunctionContext * /*ctx*/) override { }
  virtual void exitArrowFunction(JavaScriptParser::ArrowFunctionContext * /*ctx*/) override { }

  virtual void enterArrowParameters(JavaScriptParser::ArrowParametersContext * /*ctx*/) override { }
  virtual void exitArrowParameters(JavaScriptParser::ArrowParametersContext * /*ctx*/) override { }

  virtual void enterArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext * /*ctx*/) override { }
  virtual void exitArrowFunctionBody(JavaScriptParser::ArrowFunctionBodyContext * /*ctx*/) override { }

  virtual void enterExpressionNoIn(JavaScriptParser::ExpressionNoInContext * /*ctx*/) override { }
  virtual void exitExpressionNoIn(JavaScriptParser::ExpressionNoInContext * /*ctx*/) override { }

  virtual void enterAssignmentExpressionNoIn(JavaScriptParser::AssignmentExpressionNoInContext * /*ctx*/) override { }
  virtual void exitAssignmentExpressionNoIn(JavaScriptParser::AssignmentExpressionNoInContext * /*ctx*/) override { }

  virtual void enterConditionalExpressionNoIn(JavaScriptParser::ConditionalExpressionNoInContext * /*ctx*/) override { }
  virtual void exitConditionalExpressionNoIn(JavaScriptParser::ConditionalExpressionNoInContext * /*ctx*/) override { }

  virtual void enterLogicalORExpressionNoIn(JavaScriptParser::LogicalORExpressionNoInContext * /*ctx*/) override { }
  virtual void exitLogicalORExpressionNoIn(JavaScriptParser::LogicalORExpressionNoInContext * /*ctx*/) override { }

  virtual void enterLogicalANDExpressionNoIn(JavaScriptParser::LogicalANDExpressionNoInContext * /*ctx*/) override { }
  virtual void exitLogicalANDExpressionNoIn(JavaScriptParser::LogicalANDExpressionNoInContext * /*ctx*/) override { }

  virtual void enterBitwiseORExpressionNoIn(JavaScriptParser::BitwiseORExpressionNoInContext * /*ctx*/) override { }
  virtual void exitBitwiseORExpressionNoIn(JavaScriptParser::BitwiseORExpressionNoInContext * /*ctx*/) override { }

  virtual void enterBitwiseXORExpressionNoIn(JavaScriptParser::BitwiseXORExpressionNoInContext * /*ctx*/) override { }
  virtual void exitBitwiseXORExpressionNoIn(JavaScriptParser::BitwiseXORExpressionNoInContext * /*ctx*/) override { }

  virtual void enterBitwiseANDExpressionNoIn(JavaScriptParser::BitwiseANDExpressionNoInContext * /*ctx*/) override { }
  virtual void exitBitwiseANDExpressionNoIn(JavaScriptParser::BitwiseANDExpressionNoInContext * /*ctx*/) override { }

  virtual void enterEqualityExpressionNoIn(JavaScriptParser::EqualityExpressionNoInContext * /*ctx*/) override { }
  virtual void exitEqualityExpressionNoIn(JavaScriptParser::EqualityExpressionNoInContext * /*ctx*/) override { }

  virtual void enterRelationalExpressionNoIn(JavaScriptParser::RelationalExpressionNoInContext * /*ctx*/) override { }
  virtual void exitRelationalExpressionNoIn(JavaScriptParser::RelationalExpressionNoInContext * /*ctx*/) override { }

  virtual void enterShiftExpressionNoIn(JavaScriptParser::ShiftExpressionNoInContext * /*ctx*/) override { }
  virtual void exitShiftExpressionNoIn(JavaScriptParser::ShiftExpressionNoInContext * /*ctx*/) override { }

  virtual void enterAdditiveExpressionNoIn(JavaScriptParser::AdditiveExpressionNoInContext * /*ctx*/) override { }
  virtual void exitAdditiveExpressionNoIn(JavaScriptParser::AdditiveExpressionNoInContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpressionNoIn(JavaScriptParser::MultiplicativeExpressionNoInContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpressionNoIn(JavaScriptParser::MultiplicativeExpressionNoInContext * /*ctx*/) override { }

  virtual void enterUnaryExpressionNoIn(JavaScriptParser::UnaryExpressionNoInContext * /*ctx*/) override { }
  virtual void exitUnaryExpressionNoIn(JavaScriptParser::UnaryExpressionNoInContext * /*ctx*/) override { }

  virtual void enterSourceElements(JavaScriptParser::SourceElementsContext * /*ctx*/) override { }
  virtual void exitSourceElements(JavaScriptParser::SourceElementsContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

