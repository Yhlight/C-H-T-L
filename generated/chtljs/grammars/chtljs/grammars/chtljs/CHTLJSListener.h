
// Generated from grammars/chtljs/CHTLJS.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJSParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CHTLJSParser.
 */
class  CHTLJSListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(CHTLJSParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(CHTLJSParser::ProgramContext *ctx) = 0;

  virtual void enterSourceElement(CHTLJSParser::SourceElementContext *ctx) = 0;
  virtual void exitSourceElement(CHTLJSParser::SourceElementContext *ctx) = 0;

  virtual void enterStatement(CHTLJSParser::StatementContext *ctx) = 0;
  virtual void exitStatement(CHTLJSParser::StatementContext *ctx) = 0;

  virtual void enterBlock(CHTLJSParser::BlockContext *ctx) = 0;
  virtual void exitBlock(CHTLJSParser::BlockContext *ctx) = 0;

  virtual void enterStatementList(CHTLJSParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(CHTLJSParser::StatementListContext *ctx) = 0;

  virtual void enterVariableStatement(CHTLJSParser::VariableStatementContext *ctx) = 0;
  virtual void exitVariableStatement(CHTLJSParser::VariableStatementContext *ctx) = 0;

  virtual void enterVariableDeclarationList(CHTLJSParser::VariableDeclarationListContext *ctx) = 0;
  virtual void exitVariableDeclarationList(CHTLJSParser::VariableDeclarationListContext *ctx) = 0;

  virtual void enterVariableDeclaration(CHTLJSParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(CHTLJSParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterAssignmentExpression(CHTLJSParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(CHTLJSParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterAssignmentOperator(CHTLJSParser::AssignmentOperatorContext *ctx) = 0;
  virtual void exitAssignmentOperator(CHTLJSParser::AssignmentOperatorContext *ctx) = 0;

  virtual void enterEmptyStatement(CHTLJSParser::EmptyStatementContext *ctx) = 0;
  virtual void exitEmptyStatement(CHTLJSParser::EmptyStatementContext *ctx) = 0;

  virtual void enterExpressionStatement(CHTLJSParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(CHTLJSParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfStatement(CHTLJSParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(CHTLJSParser::IfStatementContext *ctx) = 0;

  virtual void enterIterationStatement(CHTLJSParser::IterationStatementContext *ctx) = 0;
  virtual void exitIterationStatement(CHTLJSParser::IterationStatementContext *ctx) = 0;

  virtual void enterContinueStatement(CHTLJSParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(CHTLJSParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(CHTLJSParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(CHTLJSParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(CHTLJSParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(CHTLJSParser::ReturnStatementContext *ctx) = 0;

  virtual void enterWithStatement(CHTLJSParser::WithStatementContext *ctx) = 0;
  virtual void exitWithStatement(CHTLJSParser::WithStatementContext *ctx) = 0;

  virtual void enterLabelledStatement(CHTLJSParser::LabelledStatementContext *ctx) = 0;
  virtual void exitLabelledStatement(CHTLJSParser::LabelledStatementContext *ctx) = 0;

  virtual void enterSwitchStatement(CHTLJSParser::SwitchStatementContext *ctx) = 0;
  virtual void exitSwitchStatement(CHTLJSParser::SwitchStatementContext *ctx) = 0;

  virtual void enterCaseBlock(CHTLJSParser::CaseBlockContext *ctx) = 0;
  virtual void exitCaseBlock(CHTLJSParser::CaseBlockContext *ctx) = 0;

  virtual void enterCaseClauses(CHTLJSParser::CaseClausesContext *ctx) = 0;
  virtual void exitCaseClauses(CHTLJSParser::CaseClausesContext *ctx) = 0;

  virtual void enterCaseClause(CHTLJSParser::CaseClauseContext *ctx) = 0;
  virtual void exitCaseClause(CHTLJSParser::CaseClauseContext *ctx) = 0;

  virtual void enterDefaultClause(CHTLJSParser::DefaultClauseContext *ctx) = 0;
  virtual void exitDefaultClause(CHTLJSParser::DefaultClauseContext *ctx) = 0;

  virtual void enterThrowStatement(CHTLJSParser::ThrowStatementContext *ctx) = 0;
  virtual void exitThrowStatement(CHTLJSParser::ThrowStatementContext *ctx) = 0;

  virtual void enterTryStatement(CHTLJSParser::TryStatementContext *ctx) = 0;
  virtual void exitTryStatement(CHTLJSParser::TryStatementContext *ctx) = 0;

  virtual void enterCatchBlock(CHTLJSParser::CatchBlockContext *ctx) = 0;
  virtual void exitCatchBlock(CHTLJSParser::CatchBlockContext *ctx) = 0;

  virtual void enterFinallyBlock(CHTLJSParser::FinallyBlockContext *ctx) = 0;
  virtual void exitFinallyBlock(CHTLJSParser::FinallyBlockContext *ctx) = 0;

  virtual void enterDebuggerStatement(CHTLJSParser::DebuggerStatementContext *ctx) = 0;
  virtual void exitDebuggerStatement(CHTLJSParser::DebuggerStatementContext *ctx) = 0;

  virtual void enterFunctionDeclaration(CHTLJSParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(CHTLJSParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterFormalParameterList(CHTLJSParser::FormalParameterListContext *ctx) = 0;
  virtual void exitFormalParameterList(CHTLJSParser::FormalParameterListContext *ctx) = 0;

  virtual void enterFunctionBody(CHTLJSParser::FunctionBodyContext *ctx) = 0;
  virtual void exitFunctionBody(CHTLJSParser::FunctionBodyContext *ctx) = 0;

  virtual void enterClassDeclaration(CHTLJSParser::ClassDeclarationContext *ctx) = 0;
  virtual void exitClassDeclaration(CHTLJSParser::ClassDeclarationContext *ctx) = 0;

  virtual void enterClassBody(CHTLJSParser::ClassBodyContext *ctx) = 0;
  virtual void exitClassBody(CHTLJSParser::ClassBodyContext *ctx) = 0;

  virtual void enterClassElement(CHTLJSParser::ClassElementContext *ctx) = 0;
  virtual void exitClassElement(CHTLJSParser::ClassElementContext *ctx) = 0;

  virtual void enterMethodDefinition(CHTLJSParser::MethodDefinitionContext *ctx) = 0;
  virtual void exitMethodDefinition(CHTLJSParser::MethodDefinitionContext *ctx) = 0;

  virtual void enterExpression(CHTLJSParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(CHTLJSParser::ExpressionContext *ctx) = 0;

  virtual void enterConditionalExpression(CHTLJSParser::ConditionalExpressionContext *ctx) = 0;
  virtual void exitConditionalExpression(CHTLJSParser::ConditionalExpressionContext *ctx) = 0;

  virtual void enterLogicalORExpression(CHTLJSParser::LogicalORExpressionContext *ctx) = 0;
  virtual void exitLogicalORExpression(CHTLJSParser::LogicalORExpressionContext *ctx) = 0;

  virtual void enterLogicalANDExpression(CHTLJSParser::LogicalANDExpressionContext *ctx) = 0;
  virtual void exitLogicalANDExpression(CHTLJSParser::LogicalANDExpressionContext *ctx) = 0;

  virtual void enterBitwiseORExpression(CHTLJSParser::BitwiseORExpressionContext *ctx) = 0;
  virtual void exitBitwiseORExpression(CHTLJSParser::BitwiseORExpressionContext *ctx) = 0;

  virtual void enterBitwiseXORExpression(CHTLJSParser::BitwiseXORExpressionContext *ctx) = 0;
  virtual void exitBitwiseXORExpression(CHTLJSParser::BitwiseXORExpressionContext *ctx) = 0;

  virtual void enterBitwiseANDExpression(CHTLJSParser::BitwiseANDExpressionContext *ctx) = 0;
  virtual void exitBitwiseANDExpression(CHTLJSParser::BitwiseANDExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(CHTLJSParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(CHTLJSParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(CHTLJSParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(CHTLJSParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(CHTLJSParser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(CHTLJSParser::ShiftExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(CHTLJSParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(CHTLJSParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(CHTLJSParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(CHTLJSParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(CHTLJSParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(CHTLJSParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterUnaryOperator(CHTLJSParser::UnaryOperatorContext *ctx) = 0;
  virtual void exitUnaryOperator(CHTLJSParser::UnaryOperatorContext *ctx) = 0;

  virtual void enterPostfixExpression(CHTLJSParser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(CHTLJSParser::PostfixExpressionContext *ctx) = 0;

  virtual void enterLeftHandSideExpression(CHTLJSParser::LeftHandSideExpressionContext *ctx) = 0;
  virtual void exitLeftHandSideExpression(CHTLJSParser::LeftHandSideExpressionContext *ctx) = 0;

  virtual void enterCallExpression(CHTLJSParser::CallExpressionContext *ctx) = 0;
  virtual void exitCallExpression(CHTLJSParser::CallExpressionContext *ctx) = 0;

  virtual void enterArguments(CHTLJSParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(CHTLJSParser::ArgumentsContext *ctx) = 0;

  virtual void enterArgumentList(CHTLJSParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(CHTLJSParser::ArgumentListContext *ctx) = 0;

  virtual void enterNewExpression(CHTLJSParser::NewExpressionContext *ctx) = 0;
  virtual void exitNewExpression(CHTLJSParser::NewExpressionContext *ctx) = 0;

  virtual void enterSuperProperty(CHTLJSParser::SuperPropertyContext *ctx) = 0;
  virtual void exitSuperProperty(CHTLJSParser::SuperPropertyContext *ctx) = 0;

  virtual void enterFunctionExpression(CHTLJSParser::FunctionExpressionContext *ctx) = 0;
  virtual void exitFunctionExpression(CHTLJSParser::FunctionExpressionContext *ctx) = 0;

  virtual void enterClassExpression(CHTLJSParser::ClassExpressionContext *ctx) = 0;
  virtual void exitClassExpression(CHTLJSParser::ClassExpressionContext *ctx) = 0;

  virtual void enterThisExpression(CHTLJSParser::ThisExpressionContext *ctx) = 0;
  virtual void exitThisExpression(CHTLJSParser::ThisExpressionContext *ctx) = 0;

  virtual void enterArrayLiteral(CHTLJSParser::ArrayLiteralContext *ctx) = 0;
  virtual void exitArrayLiteral(CHTLJSParser::ArrayLiteralContext *ctx) = 0;

  virtual void enterElementList(CHTLJSParser::ElementListContext *ctx) = 0;
  virtual void exitElementList(CHTLJSParser::ElementListContext *ctx) = 0;

  virtual void enterObjectLiteral(CHTLJSParser::ObjectLiteralContext *ctx) = 0;
  virtual void exitObjectLiteral(CHTLJSParser::ObjectLiteralContext *ctx) = 0;

  virtual void enterPropertyDefinition(CHTLJSParser::PropertyDefinitionContext *ctx) = 0;
  virtual void exitPropertyDefinition(CHTLJSParser::PropertyDefinitionContext *ctx) = 0;

  virtual void enterParenthesizedExpression(CHTLJSParser::ParenthesizedExpressionContext *ctx) = 0;
  virtual void exitParenthesizedExpression(CHTLJSParser::ParenthesizedExpressionContext *ctx) = 0;

  virtual void enterArrowFunction(CHTLJSParser::ArrowFunctionContext *ctx) = 0;
  virtual void exitArrowFunction(CHTLJSParser::ArrowFunctionContext *ctx) = 0;

  virtual void enterArrowParameters(CHTLJSParser::ArrowParametersContext *ctx) = 0;
  virtual void exitArrowParameters(CHTLJSParser::ArrowParametersContext *ctx) = 0;

  virtual void enterArrowFunctionBody(CHTLJSParser::ArrowFunctionBodyContext *ctx) = 0;
  virtual void exitArrowFunctionBody(CHTLJSParser::ArrowFunctionBodyContext *ctx) = 0;

  virtual void enterChtlStatement(CHTLJSParser::ChtlStatementContext *ctx) = 0;
  virtual void exitChtlStatement(CHTLJSParser::ChtlStatementContext *ctx) = 0;

  virtual void enterChtlSelectorStatement(CHTLJSParser::ChtlSelectorStatementContext *ctx) = 0;
  virtual void exitChtlSelectorStatement(CHTLJSParser::ChtlSelectorStatementContext *ctx) = 0;

  virtual void enterChtlSelector(CHTLJSParser::ChtlSelectorContext *ctx) = 0;
  virtual void exitChtlSelector(CHTLJSParser::ChtlSelectorContext *ctx) = 0;

  virtual void enterSelectorContent(CHTLJSParser::SelectorContentContext *ctx) = 0;
  virtual void exitSelectorContent(CHTLJSParser::SelectorContentContext *ctx) = 0;

  virtual void enterSelectorType(CHTLJSParser::SelectorTypeContext *ctx) = 0;
  virtual void exitSelectorType(CHTLJSParser::SelectorTypeContext *ctx) = 0;

  virtual void enterSelectorModifier(CHTLJSParser::SelectorModifierContext *ctx) = 0;
  virtual void exitSelectorModifier(CHTLJSParser::SelectorModifierContext *ctx) = 0;

  virtual void enterChtlListenStatement(CHTLJSParser::ChtlListenStatementContext *ctx) = 0;
  virtual void exitChtlListenStatement(CHTLJSParser::ChtlListenStatementContext *ctx) = 0;

  virtual void enterChtlListenObject(CHTLJSParser::ChtlListenObjectContext *ctx) = 0;
  virtual void exitChtlListenObject(CHTLJSParser::ChtlListenObjectContext *ctx) = 0;

  virtual void enterChtlListenEvents(CHTLJSParser::ChtlListenEventsContext *ctx) = 0;
  virtual void exitChtlListenEvents(CHTLJSParser::ChtlListenEventsContext *ctx) = 0;

  virtual void enterChtlListenEvent(CHTLJSParser::ChtlListenEventContext *ctx) = 0;
  virtual void exitChtlListenEvent(CHTLJSParser::ChtlListenEventContext *ctx) = 0;

  virtual void enterEventType(CHTLJSParser::EventTypeContext *ctx) = 0;
  virtual void exitEventType(CHTLJSParser::EventTypeContext *ctx) = 0;

  virtual void enterEventHandler(CHTLJSParser::EventHandlerContext *ctx) = 0;
  virtual void exitEventHandler(CHTLJSParser::EventHandlerContext *ctx) = 0;

  virtual void enterChtlDelegateStatement(CHTLJSParser::ChtlDelegateStatementContext *ctx) = 0;
  virtual void exitChtlDelegateStatement(CHTLJSParser::ChtlDelegateStatementContext *ctx) = 0;

  virtual void enterChtlDelegateObject(CHTLJSParser::ChtlDelegateObjectContext *ctx) = 0;
  virtual void exitChtlDelegateObject(CHTLJSParser::ChtlDelegateObjectContext *ctx) = 0;

  virtual void enterChtlDelegateConfig(CHTLJSParser::ChtlDelegateConfigContext *ctx) = 0;
  virtual void exitChtlDelegateConfig(CHTLJSParser::ChtlDelegateConfigContext *ctx) = 0;

  virtual void enterChtlTargetConfig(CHTLJSParser::ChtlTargetConfigContext *ctx) = 0;
  virtual void exitChtlTargetConfig(CHTLJSParser::ChtlTargetConfigContext *ctx) = 0;

  virtual void enterChtlSelectorArray(CHTLJSParser::ChtlSelectorArrayContext *ctx) = 0;
  virtual void exitChtlSelectorArray(CHTLJSParser::ChtlSelectorArrayContext *ctx) = 0;

  virtual void enterChtlEventConfig(CHTLJSParser::ChtlEventConfigContext *ctx) = 0;
  virtual void exitChtlEventConfig(CHTLJSParser::ChtlEventConfigContext *ctx) = 0;

  virtual void enterChtlAnimateStatement(CHTLJSParser::ChtlAnimateStatementContext *ctx) = 0;
  virtual void exitChtlAnimateStatement(CHTLJSParser::ChtlAnimateStatementContext *ctx) = 0;

  virtual void enterChtlAnimateObject(CHTLJSParser::ChtlAnimateObjectContext *ctx) = 0;
  virtual void exitChtlAnimateObject(CHTLJSParser::ChtlAnimateObjectContext *ctx) = 0;

  virtual void enterChtlAnimateConfig(CHTLJSParser::ChtlAnimateConfigContext *ctx) = 0;
  virtual void exitChtlAnimateConfig(CHTLJSParser::ChtlAnimateConfigContext *ctx) = 0;

  virtual void enterChtlAnimateProperty(CHTLJSParser::ChtlAnimatePropertyContext *ctx) = 0;
  virtual void exitChtlAnimateProperty(CHTLJSParser::ChtlAnimatePropertyContext *ctx) = 0;

  virtual void enterChtlDuration(CHTLJSParser::ChtlDurationContext *ctx) = 0;
  virtual void exitChtlDuration(CHTLJSParser::ChtlDurationContext *ctx) = 0;

  virtual void enterChtlEasing(CHTLJSParser::ChtlEasingContext *ctx) = 0;
  virtual void exitChtlEasing(CHTLJSParser::ChtlEasingContext *ctx) = 0;

  virtual void enterEasingValue(CHTLJSParser::EasingValueContext *ctx) = 0;
  virtual void exitEasingValue(CHTLJSParser::EasingValueContext *ctx) = 0;

  virtual void enterChtlBegin(CHTLJSParser::ChtlBeginContext *ctx) = 0;
  virtual void exitChtlBegin(CHTLJSParser::ChtlBeginContext *ctx) = 0;

  virtual void enterChtlWhen(CHTLJSParser::ChtlWhenContext *ctx) = 0;
  virtual void exitChtlWhen(CHTLJSParser::ChtlWhenContext *ctx) = 0;

  virtual void enterChtlWhenClause(CHTLJSParser::ChtlWhenClauseContext *ctx) = 0;
  virtual void exitChtlWhenClause(CHTLJSParser::ChtlWhenClauseContext *ctx) = 0;

  virtual void enterChtlAt(CHTLJSParser::ChtlAtContext *ctx) = 0;
  virtual void exitChtlAt(CHTLJSParser::ChtlAtContext *ctx) = 0;

  virtual void enterChtlEnd(CHTLJSParser::ChtlEndContext *ctx) = 0;
  virtual void exitChtlEnd(CHTLJSParser::ChtlEndContext *ctx) = 0;

  virtual void enterChtlLoop(CHTLJSParser::ChtlLoopContext *ctx) = 0;
  virtual void exitChtlLoop(CHTLJSParser::ChtlLoopContext *ctx) = 0;

  virtual void enterChtlDirection(CHTLJSParser::ChtlDirectionContext *ctx) = 0;
  virtual void exitChtlDirection(CHTLJSParser::ChtlDirectionContext *ctx) = 0;

  virtual void enterDirectionValue(CHTLJSParser::DirectionValueContext *ctx) = 0;
  virtual void exitDirectionValue(CHTLJSParser::DirectionValueContext *ctx) = 0;

  virtual void enterChtlDelay(CHTLJSParser::ChtlDelayContext *ctx) = 0;
  virtual void exitChtlDelay(CHTLJSParser::ChtlDelayContext *ctx) = 0;

  virtual void enterChtlCallback(CHTLJSParser::ChtlCallbackContext *ctx) = 0;
  virtual void exitChtlCallback(CHTLJSParser::ChtlCallbackContext *ctx) = 0;

  virtual void enterChtlCssProperties(CHTLJSParser::ChtlCssPropertiesContext *ctx) = 0;
  virtual void exitChtlCssProperties(CHTLJSParser::ChtlCssPropertiesContext *ctx) = 0;

  virtual void enterChtlCssProperty(CHTLJSParser::ChtlCssPropertyContext *ctx) = 0;
  virtual void exitChtlCssProperty(CHTLJSParser::ChtlCssPropertyContext *ctx) = 0;

  virtual void enterPropertyName(CHTLJSParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(CHTLJSParser::PropertyNameContext *ctx) = 0;

  virtual void enterPropertyValue(CHTLJSParser::PropertyValueContext *ctx) = 0;
  virtual void exitPropertyValue(CHTLJSParser::PropertyValueContext *ctx) = 0;

  virtual void enterMethodCall(CHTLJSParser::MethodCallContext *ctx) = 0;
  virtual void exitMethodCall(CHTLJSParser::MethodCallContext *ctx) = 0;

  virtual void enterFunctionCall(CHTLJSParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(CHTLJSParser::FunctionCallContext *ctx) = 0;

  virtual void enterFunctionArg(CHTLJSParser::FunctionArgContext *ctx) = 0;
  virtual void exitFunctionArg(CHTLJSParser::FunctionArgContext *ctx) = 0;

  virtual void enterValue(CHTLJSParser::ValueContext *ctx) = 0;
  virtual void exitValue(CHTLJSParser::ValueContext *ctx) = 0;

  virtual void enterSourceElements(CHTLJSParser::SourceElementsContext *ctx) = 0;
  virtual void exitSourceElements(CHTLJSParser::SourceElementsContext *ctx) = 0;


};

