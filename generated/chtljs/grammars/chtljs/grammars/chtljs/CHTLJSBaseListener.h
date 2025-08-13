
// Generated from grammars/chtljs/CHTLJS.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "CHTLJSListener.h"


/**
 * This class provides an empty implementation of CHTLJSListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CHTLJSBaseListener : public CHTLJSListener {
public:

  virtual void enterProgram(CHTLJSParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(CHTLJSParser::ProgramContext * /*ctx*/) override { }

  virtual void enterSourceElement(CHTLJSParser::SourceElementContext * /*ctx*/) override { }
  virtual void exitSourceElement(CHTLJSParser::SourceElementContext * /*ctx*/) override { }

  virtual void enterStatement(CHTLJSParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(CHTLJSParser::StatementContext * /*ctx*/) override { }

  virtual void enterBlock(CHTLJSParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(CHTLJSParser::BlockContext * /*ctx*/) override { }

  virtual void enterStatementList(CHTLJSParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(CHTLJSParser::StatementListContext * /*ctx*/) override { }

  virtual void enterVariableStatement(CHTLJSParser::VariableStatementContext * /*ctx*/) override { }
  virtual void exitVariableStatement(CHTLJSParser::VariableStatementContext * /*ctx*/) override { }

  virtual void enterVariableDeclarationList(CHTLJSParser::VariableDeclarationListContext * /*ctx*/) override { }
  virtual void exitVariableDeclarationList(CHTLJSParser::VariableDeclarationListContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(CHTLJSParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(CHTLJSParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(CHTLJSParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(CHTLJSParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentOperator(CHTLJSParser::AssignmentOperatorContext * /*ctx*/) override { }
  virtual void exitAssignmentOperator(CHTLJSParser::AssignmentOperatorContext * /*ctx*/) override { }

  virtual void enterEmptyStatement(CHTLJSParser::EmptyStatementContext * /*ctx*/) override { }
  virtual void exitEmptyStatement(CHTLJSParser::EmptyStatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(CHTLJSParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(CHTLJSParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterIfStatement(CHTLJSParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(CHTLJSParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterIterationStatement(CHTLJSParser::IterationStatementContext * /*ctx*/) override { }
  virtual void exitIterationStatement(CHTLJSParser::IterationStatementContext * /*ctx*/) override { }

  virtual void enterContinueStatement(CHTLJSParser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(CHTLJSParser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterBreakStatement(CHTLJSParser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(CHTLJSParser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(CHTLJSParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(CHTLJSParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterWithStatement(CHTLJSParser::WithStatementContext * /*ctx*/) override { }
  virtual void exitWithStatement(CHTLJSParser::WithStatementContext * /*ctx*/) override { }

  virtual void enterLabelledStatement(CHTLJSParser::LabelledStatementContext * /*ctx*/) override { }
  virtual void exitLabelledStatement(CHTLJSParser::LabelledStatementContext * /*ctx*/) override { }

  virtual void enterSwitchStatement(CHTLJSParser::SwitchStatementContext * /*ctx*/) override { }
  virtual void exitSwitchStatement(CHTLJSParser::SwitchStatementContext * /*ctx*/) override { }

  virtual void enterCaseBlock(CHTLJSParser::CaseBlockContext * /*ctx*/) override { }
  virtual void exitCaseBlock(CHTLJSParser::CaseBlockContext * /*ctx*/) override { }

  virtual void enterCaseClauses(CHTLJSParser::CaseClausesContext * /*ctx*/) override { }
  virtual void exitCaseClauses(CHTLJSParser::CaseClausesContext * /*ctx*/) override { }

  virtual void enterCaseClause(CHTLJSParser::CaseClauseContext * /*ctx*/) override { }
  virtual void exitCaseClause(CHTLJSParser::CaseClauseContext * /*ctx*/) override { }

  virtual void enterDefaultClause(CHTLJSParser::DefaultClauseContext * /*ctx*/) override { }
  virtual void exitDefaultClause(CHTLJSParser::DefaultClauseContext * /*ctx*/) override { }

  virtual void enterThrowStatement(CHTLJSParser::ThrowStatementContext * /*ctx*/) override { }
  virtual void exitThrowStatement(CHTLJSParser::ThrowStatementContext * /*ctx*/) override { }

  virtual void enterTryStatement(CHTLJSParser::TryStatementContext * /*ctx*/) override { }
  virtual void exitTryStatement(CHTLJSParser::TryStatementContext * /*ctx*/) override { }

  virtual void enterCatchBlock(CHTLJSParser::CatchBlockContext * /*ctx*/) override { }
  virtual void exitCatchBlock(CHTLJSParser::CatchBlockContext * /*ctx*/) override { }

  virtual void enterFinallyBlock(CHTLJSParser::FinallyBlockContext * /*ctx*/) override { }
  virtual void exitFinallyBlock(CHTLJSParser::FinallyBlockContext * /*ctx*/) override { }

  virtual void enterDebuggerStatement(CHTLJSParser::DebuggerStatementContext * /*ctx*/) override { }
  virtual void exitDebuggerStatement(CHTLJSParser::DebuggerStatementContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(CHTLJSParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(CHTLJSParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterFormalParameterList(CHTLJSParser::FormalParameterListContext * /*ctx*/) override { }
  virtual void exitFormalParameterList(CHTLJSParser::FormalParameterListContext * /*ctx*/) override { }

  virtual void enterFunctionBody(CHTLJSParser::FunctionBodyContext * /*ctx*/) override { }
  virtual void exitFunctionBody(CHTLJSParser::FunctionBodyContext * /*ctx*/) override { }

  virtual void enterClassDeclaration(CHTLJSParser::ClassDeclarationContext * /*ctx*/) override { }
  virtual void exitClassDeclaration(CHTLJSParser::ClassDeclarationContext * /*ctx*/) override { }

  virtual void enterClassBody(CHTLJSParser::ClassBodyContext * /*ctx*/) override { }
  virtual void exitClassBody(CHTLJSParser::ClassBodyContext * /*ctx*/) override { }

  virtual void enterClassElement(CHTLJSParser::ClassElementContext * /*ctx*/) override { }
  virtual void exitClassElement(CHTLJSParser::ClassElementContext * /*ctx*/) override { }

  virtual void enterMethodDefinition(CHTLJSParser::MethodDefinitionContext * /*ctx*/) override { }
  virtual void exitMethodDefinition(CHTLJSParser::MethodDefinitionContext * /*ctx*/) override { }

  virtual void enterExpression(CHTLJSParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(CHTLJSParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterConditionalExpression(CHTLJSParser::ConditionalExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalExpression(CHTLJSParser::ConditionalExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalORExpression(CHTLJSParser::LogicalORExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalORExpression(CHTLJSParser::LogicalORExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalANDExpression(CHTLJSParser::LogicalANDExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalANDExpression(CHTLJSParser::LogicalANDExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseORExpression(CHTLJSParser::BitwiseORExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseORExpression(CHTLJSParser::BitwiseORExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseXORExpression(CHTLJSParser::BitwiseXORExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseXORExpression(CHTLJSParser::BitwiseXORExpressionContext * /*ctx*/) override { }

  virtual void enterBitwiseANDExpression(CHTLJSParser::BitwiseANDExpressionContext * /*ctx*/) override { }
  virtual void exitBitwiseANDExpression(CHTLJSParser::BitwiseANDExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(CHTLJSParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(CHTLJSParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(CHTLJSParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(CHTLJSParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterShiftExpression(CHTLJSParser::ShiftExpressionContext * /*ctx*/) override { }
  virtual void exitShiftExpression(CHTLJSParser::ShiftExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(CHTLJSParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(CHTLJSParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(CHTLJSParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(CHTLJSParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(CHTLJSParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(CHTLJSParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryOperator(CHTLJSParser::UnaryOperatorContext * /*ctx*/) override { }
  virtual void exitUnaryOperator(CHTLJSParser::UnaryOperatorContext * /*ctx*/) override { }

  virtual void enterPostfixExpression(CHTLJSParser::PostfixExpressionContext * /*ctx*/) override { }
  virtual void exitPostfixExpression(CHTLJSParser::PostfixExpressionContext * /*ctx*/) override { }

  virtual void enterLeftHandSideExpression(CHTLJSParser::LeftHandSideExpressionContext * /*ctx*/) override { }
  virtual void exitLeftHandSideExpression(CHTLJSParser::LeftHandSideExpressionContext * /*ctx*/) override { }

  virtual void enterCallExpression(CHTLJSParser::CallExpressionContext * /*ctx*/) override { }
  virtual void exitCallExpression(CHTLJSParser::CallExpressionContext * /*ctx*/) override { }

  virtual void enterArguments(CHTLJSParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(CHTLJSParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterArgumentList(CHTLJSParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(CHTLJSParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterNewExpression(CHTLJSParser::NewExpressionContext * /*ctx*/) override { }
  virtual void exitNewExpression(CHTLJSParser::NewExpressionContext * /*ctx*/) override { }

  virtual void enterSuperProperty(CHTLJSParser::SuperPropertyContext * /*ctx*/) override { }
  virtual void exitSuperProperty(CHTLJSParser::SuperPropertyContext * /*ctx*/) override { }

  virtual void enterFunctionExpression(CHTLJSParser::FunctionExpressionContext * /*ctx*/) override { }
  virtual void exitFunctionExpression(CHTLJSParser::FunctionExpressionContext * /*ctx*/) override { }

  virtual void enterClassExpression(CHTLJSParser::ClassExpressionContext * /*ctx*/) override { }
  virtual void exitClassExpression(CHTLJSParser::ClassExpressionContext * /*ctx*/) override { }

  virtual void enterThisExpression(CHTLJSParser::ThisExpressionContext * /*ctx*/) override { }
  virtual void exitThisExpression(CHTLJSParser::ThisExpressionContext * /*ctx*/) override { }

  virtual void enterArrayLiteral(CHTLJSParser::ArrayLiteralContext * /*ctx*/) override { }
  virtual void exitArrayLiteral(CHTLJSParser::ArrayLiteralContext * /*ctx*/) override { }

  virtual void enterElementList(CHTLJSParser::ElementListContext * /*ctx*/) override { }
  virtual void exitElementList(CHTLJSParser::ElementListContext * /*ctx*/) override { }

  virtual void enterObjectLiteral(CHTLJSParser::ObjectLiteralContext * /*ctx*/) override { }
  virtual void exitObjectLiteral(CHTLJSParser::ObjectLiteralContext * /*ctx*/) override { }

  virtual void enterPropertyDefinition(CHTLJSParser::PropertyDefinitionContext * /*ctx*/) override { }
  virtual void exitPropertyDefinition(CHTLJSParser::PropertyDefinitionContext * /*ctx*/) override { }

  virtual void enterParenthesizedExpression(CHTLJSParser::ParenthesizedExpressionContext * /*ctx*/) override { }
  virtual void exitParenthesizedExpression(CHTLJSParser::ParenthesizedExpressionContext * /*ctx*/) override { }

  virtual void enterArrowFunction(CHTLJSParser::ArrowFunctionContext * /*ctx*/) override { }
  virtual void exitArrowFunction(CHTLJSParser::ArrowFunctionContext * /*ctx*/) override { }

  virtual void enterArrowParameters(CHTLJSParser::ArrowParametersContext * /*ctx*/) override { }
  virtual void exitArrowParameters(CHTLJSParser::ArrowParametersContext * /*ctx*/) override { }

  virtual void enterArrowFunctionBody(CHTLJSParser::ArrowFunctionBodyContext * /*ctx*/) override { }
  virtual void exitArrowFunctionBody(CHTLJSParser::ArrowFunctionBodyContext * /*ctx*/) override { }

  virtual void enterChtlStatement(CHTLJSParser::ChtlStatementContext * /*ctx*/) override { }
  virtual void exitChtlStatement(CHTLJSParser::ChtlStatementContext * /*ctx*/) override { }

  virtual void enterChtlSelectorStatement(CHTLJSParser::ChtlSelectorStatementContext * /*ctx*/) override { }
  virtual void exitChtlSelectorStatement(CHTLJSParser::ChtlSelectorStatementContext * /*ctx*/) override { }

  virtual void enterChtlSelector(CHTLJSParser::ChtlSelectorContext * /*ctx*/) override { }
  virtual void exitChtlSelector(CHTLJSParser::ChtlSelectorContext * /*ctx*/) override { }

  virtual void enterSelectorContent(CHTLJSParser::SelectorContentContext * /*ctx*/) override { }
  virtual void exitSelectorContent(CHTLJSParser::SelectorContentContext * /*ctx*/) override { }

  virtual void enterSelectorType(CHTLJSParser::SelectorTypeContext * /*ctx*/) override { }
  virtual void exitSelectorType(CHTLJSParser::SelectorTypeContext * /*ctx*/) override { }

  virtual void enterSelectorModifier(CHTLJSParser::SelectorModifierContext * /*ctx*/) override { }
  virtual void exitSelectorModifier(CHTLJSParser::SelectorModifierContext * /*ctx*/) override { }

  virtual void enterChtlListenStatement(CHTLJSParser::ChtlListenStatementContext * /*ctx*/) override { }
  virtual void exitChtlListenStatement(CHTLJSParser::ChtlListenStatementContext * /*ctx*/) override { }

  virtual void enterChtlListenObject(CHTLJSParser::ChtlListenObjectContext * /*ctx*/) override { }
  virtual void exitChtlListenObject(CHTLJSParser::ChtlListenObjectContext * /*ctx*/) override { }

  virtual void enterChtlListenEvents(CHTLJSParser::ChtlListenEventsContext * /*ctx*/) override { }
  virtual void exitChtlListenEvents(CHTLJSParser::ChtlListenEventsContext * /*ctx*/) override { }

  virtual void enterChtlListenEvent(CHTLJSParser::ChtlListenEventContext * /*ctx*/) override { }
  virtual void exitChtlListenEvent(CHTLJSParser::ChtlListenEventContext * /*ctx*/) override { }

  virtual void enterEventType(CHTLJSParser::EventTypeContext * /*ctx*/) override { }
  virtual void exitEventType(CHTLJSParser::EventTypeContext * /*ctx*/) override { }

  virtual void enterEventHandler(CHTLJSParser::EventHandlerContext * /*ctx*/) override { }
  virtual void exitEventHandler(CHTLJSParser::EventHandlerContext * /*ctx*/) override { }

  virtual void enterChtlDelegateStatement(CHTLJSParser::ChtlDelegateStatementContext * /*ctx*/) override { }
  virtual void exitChtlDelegateStatement(CHTLJSParser::ChtlDelegateStatementContext * /*ctx*/) override { }

  virtual void enterChtlDelegateObject(CHTLJSParser::ChtlDelegateObjectContext * /*ctx*/) override { }
  virtual void exitChtlDelegateObject(CHTLJSParser::ChtlDelegateObjectContext * /*ctx*/) override { }

  virtual void enterChtlDelegateConfig(CHTLJSParser::ChtlDelegateConfigContext * /*ctx*/) override { }
  virtual void exitChtlDelegateConfig(CHTLJSParser::ChtlDelegateConfigContext * /*ctx*/) override { }

  virtual void enterChtlTargetConfig(CHTLJSParser::ChtlTargetConfigContext * /*ctx*/) override { }
  virtual void exitChtlTargetConfig(CHTLJSParser::ChtlTargetConfigContext * /*ctx*/) override { }

  virtual void enterChtlSelectorArray(CHTLJSParser::ChtlSelectorArrayContext * /*ctx*/) override { }
  virtual void exitChtlSelectorArray(CHTLJSParser::ChtlSelectorArrayContext * /*ctx*/) override { }

  virtual void enterChtlEventConfig(CHTLJSParser::ChtlEventConfigContext * /*ctx*/) override { }
  virtual void exitChtlEventConfig(CHTLJSParser::ChtlEventConfigContext * /*ctx*/) override { }

  virtual void enterChtlAnimateStatement(CHTLJSParser::ChtlAnimateStatementContext * /*ctx*/) override { }
  virtual void exitChtlAnimateStatement(CHTLJSParser::ChtlAnimateStatementContext * /*ctx*/) override { }

  virtual void enterChtlAnimateObject(CHTLJSParser::ChtlAnimateObjectContext * /*ctx*/) override { }
  virtual void exitChtlAnimateObject(CHTLJSParser::ChtlAnimateObjectContext * /*ctx*/) override { }

  virtual void enterChtlAnimateConfig(CHTLJSParser::ChtlAnimateConfigContext * /*ctx*/) override { }
  virtual void exitChtlAnimateConfig(CHTLJSParser::ChtlAnimateConfigContext * /*ctx*/) override { }

  virtual void enterChtlAnimateProperty(CHTLJSParser::ChtlAnimatePropertyContext * /*ctx*/) override { }
  virtual void exitChtlAnimateProperty(CHTLJSParser::ChtlAnimatePropertyContext * /*ctx*/) override { }

  virtual void enterChtlDuration(CHTLJSParser::ChtlDurationContext * /*ctx*/) override { }
  virtual void exitChtlDuration(CHTLJSParser::ChtlDurationContext * /*ctx*/) override { }

  virtual void enterChtlEasing(CHTLJSParser::ChtlEasingContext * /*ctx*/) override { }
  virtual void exitChtlEasing(CHTLJSParser::ChtlEasingContext * /*ctx*/) override { }

  virtual void enterEasingValue(CHTLJSParser::EasingValueContext * /*ctx*/) override { }
  virtual void exitEasingValue(CHTLJSParser::EasingValueContext * /*ctx*/) override { }

  virtual void enterChtlBegin(CHTLJSParser::ChtlBeginContext * /*ctx*/) override { }
  virtual void exitChtlBegin(CHTLJSParser::ChtlBeginContext * /*ctx*/) override { }

  virtual void enterChtlWhen(CHTLJSParser::ChtlWhenContext * /*ctx*/) override { }
  virtual void exitChtlWhen(CHTLJSParser::ChtlWhenContext * /*ctx*/) override { }

  virtual void enterChtlWhenClause(CHTLJSParser::ChtlWhenClauseContext * /*ctx*/) override { }
  virtual void exitChtlWhenClause(CHTLJSParser::ChtlWhenClauseContext * /*ctx*/) override { }

  virtual void enterChtlAt(CHTLJSParser::ChtlAtContext * /*ctx*/) override { }
  virtual void exitChtlAt(CHTLJSParser::ChtlAtContext * /*ctx*/) override { }

  virtual void enterChtlEnd(CHTLJSParser::ChtlEndContext * /*ctx*/) override { }
  virtual void exitChtlEnd(CHTLJSParser::ChtlEndContext * /*ctx*/) override { }

  virtual void enterChtlLoop(CHTLJSParser::ChtlLoopContext * /*ctx*/) override { }
  virtual void exitChtlLoop(CHTLJSParser::ChtlLoopContext * /*ctx*/) override { }

  virtual void enterChtlDirection(CHTLJSParser::ChtlDirectionContext * /*ctx*/) override { }
  virtual void exitChtlDirection(CHTLJSParser::ChtlDirectionContext * /*ctx*/) override { }

  virtual void enterDirectionValue(CHTLJSParser::DirectionValueContext * /*ctx*/) override { }
  virtual void exitDirectionValue(CHTLJSParser::DirectionValueContext * /*ctx*/) override { }

  virtual void enterChtlDelay(CHTLJSParser::ChtlDelayContext * /*ctx*/) override { }
  virtual void exitChtlDelay(CHTLJSParser::ChtlDelayContext * /*ctx*/) override { }

  virtual void enterChtlCallback(CHTLJSParser::ChtlCallbackContext * /*ctx*/) override { }
  virtual void exitChtlCallback(CHTLJSParser::ChtlCallbackContext * /*ctx*/) override { }

  virtual void enterChtlCssProperties(CHTLJSParser::ChtlCssPropertiesContext * /*ctx*/) override { }
  virtual void exitChtlCssProperties(CHTLJSParser::ChtlCssPropertiesContext * /*ctx*/) override { }

  virtual void enterChtlCssProperty(CHTLJSParser::ChtlCssPropertyContext * /*ctx*/) override { }
  virtual void exitChtlCssProperty(CHTLJSParser::ChtlCssPropertyContext * /*ctx*/) override { }

  virtual void enterPropertyName(CHTLJSParser::PropertyNameContext * /*ctx*/) override { }
  virtual void exitPropertyName(CHTLJSParser::PropertyNameContext * /*ctx*/) override { }

  virtual void enterPropertyValue(CHTLJSParser::PropertyValueContext * /*ctx*/) override { }
  virtual void exitPropertyValue(CHTLJSParser::PropertyValueContext * /*ctx*/) override { }

  virtual void enterMethodCall(CHTLJSParser::MethodCallContext * /*ctx*/) override { }
  virtual void exitMethodCall(CHTLJSParser::MethodCallContext * /*ctx*/) override { }

  virtual void enterFunctionCall(CHTLJSParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(CHTLJSParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterFunctionArg(CHTLJSParser::FunctionArgContext * /*ctx*/) override { }
  virtual void exitFunctionArg(CHTLJSParser::FunctionArgContext * /*ctx*/) override { }

  virtual void enterValue(CHTLJSParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(CHTLJSParser::ValueContext * /*ctx*/) override { }

  virtual void enterSourceElements(CHTLJSParser::SourceElementsContext * /*ctx*/) override { }
  virtual void exitSourceElements(CHTLJSParser::SourceElementsContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

