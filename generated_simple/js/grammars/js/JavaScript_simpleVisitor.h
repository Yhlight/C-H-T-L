
// Generated from grammars/js/JavaScript_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "JavaScript_simpleParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by JavaScript_simpleParser.
 */
class  JavaScript_simpleVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by JavaScript_simpleParser.
   */
    virtual std::any visitProgram(JavaScript_simpleParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(JavaScript_simpleParser::StatementContext *context) = 0;

    virtual std::any visitExpressionStatement(JavaScript_simpleParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitExpression(JavaScript_simpleParser::ExpressionContext *context) = 0;

    virtual std::any visitAssignmentExpression(JavaScript_simpleParser::AssignmentExpressionContext *context) = 0;

    virtual std::any visitFunctionCall(JavaScript_simpleParser::FunctionCallContext *context) = 0;

    virtual std::any visitArgumentList(JavaScript_simpleParser::ArgumentListContext *context) = 0;

    virtual std::any visitIdentifier(JavaScript_simpleParser::IdentifierContext *context) = 0;

    virtual std::any visitLiteral(JavaScript_simpleParser::LiteralContext *context) = 0;

    virtual std::any visitVariableDeclaration(JavaScript_simpleParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitFunctionDeclaration(JavaScript_simpleParser::FunctionDeclarationContext *context) = 0;

    virtual std::any visitParameterList(JavaScript_simpleParser::ParameterListContext *context) = 0;

    virtual std::any visitIfStatement(JavaScript_simpleParser::IfStatementContext *context) = 0;

    virtual std::any visitForStatement(JavaScript_simpleParser::ForStatementContext *context) = 0;

    virtual std::any visitForInitializer(JavaScript_simpleParser::ForInitializerContext *context) = 0;

    virtual std::any visitWhileStatement(JavaScript_simpleParser::WhileStatementContext *context) = 0;

    virtual std::any visitReturnStatement(JavaScript_simpleParser::ReturnStatementContext *context) = 0;

    virtual std::any visitBlockStatement(JavaScript_simpleParser::BlockStatementContext *context) = 0;


};

