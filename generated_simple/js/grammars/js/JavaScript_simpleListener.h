
// Generated from grammars/js/JavaScript_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "JavaScript_simpleParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by JavaScript_simpleParser.
 */
class  JavaScript_simpleListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(JavaScript_simpleParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(JavaScript_simpleParser::ProgramContext *ctx) = 0;

  virtual void enterStatement(JavaScript_simpleParser::StatementContext *ctx) = 0;
  virtual void exitStatement(JavaScript_simpleParser::StatementContext *ctx) = 0;

  virtual void enterExpressionStatement(JavaScript_simpleParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(JavaScript_simpleParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterExpression(JavaScript_simpleParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(JavaScript_simpleParser::ExpressionContext *ctx) = 0;

  virtual void enterAssignmentExpression(JavaScript_simpleParser::AssignmentExpressionContext *ctx) = 0;
  virtual void exitAssignmentExpression(JavaScript_simpleParser::AssignmentExpressionContext *ctx) = 0;

  virtual void enterFunctionCall(JavaScript_simpleParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(JavaScript_simpleParser::FunctionCallContext *ctx) = 0;

  virtual void enterArgumentList(JavaScript_simpleParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(JavaScript_simpleParser::ArgumentListContext *ctx) = 0;

  virtual void enterIdentifier(JavaScript_simpleParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(JavaScript_simpleParser::IdentifierContext *ctx) = 0;

  virtual void enterLiteral(JavaScript_simpleParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(JavaScript_simpleParser::LiteralContext *ctx) = 0;

  virtual void enterVariableDeclaration(JavaScript_simpleParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(JavaScript_simpleParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterFunctionDeclaration(JavaScript_simpleParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(JavaScript_simpleParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterParameterList(JavaScript_simpleParser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(JavaScript_simpleParser::ParameterListContext *ctx) = 0;

  virtual void enterIfStatement(JavaScript_simpleParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(JavaScript_simpleParser::IfStatementContext *ctx) = 0;

  virtual void enterForStatement(JavaScript_simpleParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(JavaScript_simpleParser::ForStatementContext *ctx) = 0;

  virtual void enterForInitializer(JavaScript_simpleParser::ForInitializerContext *ctx) = 0;
  virtual void exitForInitializer(JavaScript_simpleParser::ForInitializerContext *ctx) = 0;

  virtual void enterWhileStatement(JavaScript_simpleParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(JavaScript_simpleParser::WhileStatementContext *ctx) = 0;

  virtual void enterReturnStatement(JavaScript_simpleParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(JavaScript_simpleParser::ReturnStatementContext *ctx) = 0;

  virtual void enterBlockStatement(JavaScript_simpleParser::BlockStatementContext *ctx) = 0;
  virtual void exitBlockStatement(JavaScript_simpleParser::BlockStatementContext *ctx) = 0;


};

