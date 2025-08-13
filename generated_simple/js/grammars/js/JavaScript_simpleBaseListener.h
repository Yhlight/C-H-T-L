
// Generated from grammars/js/JavaScript_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "JavaScript_simpleListener.h"


/**
 * This class provides an empty implementation of JavaScript_simpleListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  JavaScript_simpleBaseListener : public JavaScript_simpleListener {
public:

  virtual void enterProgram(JavaScript_simpleParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(JavaScript_simpleParser::ProgramContext * /*ctx*/) override { }

  virtual void enterStatement(JavaScript_simpleParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(JavaScript_simpleParser::StatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(JavaScript_simpleParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(JavaScript_simpleParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterExpression(JavaScript_simpleParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(JavaScript_simpleParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterAssignmentExpression(JavaScript_simpleParser::AssignmentExpressionContext * /*ctx*/) override { }
  virtual void exitAssignmentExpression(JavaScript_simpleParser::AssignmentExpressionContext * /*ctx*/) override { }

  virtual void enterFunctionCall(JavaScript_simpleParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(JavaScript_simpleParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterArgumentList(JavaScript_simpleParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(JavaScript_simpleParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterIdentifier(JavaScript_simpleParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(JavaScript_simpleParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterLiteral(JavaScript_simpleParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(JavaScript_simpleParser::LiteralContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(JavaScript_simpleParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(JavaScript_simpleParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(JavaScript_simpleParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(JavaScript_simpleParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterParameterList(JavaScript_simpleParser::ParameterListContext * /*ctx*/) override { }
  virtual void exitParameterList(JavaScript_simpleParser::ParameterListContext * /*ctx*/) override { }

  virtual void enterIfStatement(JavaScript_simpleParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(JavaScript_simpleParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterForStatement(JavaScript_simpleParser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(JavaScript_simpleParser::ForStatementContext * /*ctx*/) override { }

  virtual void enterForInitializer(JavaScript_simpleParser::ForInitializerContext * /*ctx*/) override { }
  virtual void exitForInitializer(JavaScript_simpleParser::ForInitializerContext * /*ctx*/) override { }

  virtual void enterWhileStatement(JavaScript_simpleParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(JavaScript_simpleParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(JavaScript_simpleParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(JavaScript_simpleParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterBlockStatement(JavaScript_simpleParser::BlockStatementContext * /*ctx*/) override { }
  virtual void exitBlockStatement(JavaScript_simpleParser::BlockStatementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

