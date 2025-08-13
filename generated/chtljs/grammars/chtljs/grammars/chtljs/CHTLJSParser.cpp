
// Generated from grammars/chtljs/CHTLJS.g4 by ANTLR 4.9.2


#include "CHTLJSListener.h"

#include "CHTLJSParser.h"


using namespace antlrcpp;
using namespace antlr4;

CHTLJSParser::CHTLJSParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CHTLJSParser::~CHTLJSParser() {
  delete _interpreter;
}

std::string CHTLJSParser::getGrammarFileName() const {
  return "CHTLJS.g4";
}

const std::vector<std::string>& CHTLJSParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CHTLJSParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

CHTLJSParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ProgramContext::EOF() {
  return getToken(CHTLJSParser::EOF, 0);
}

std::vector<CHTLJSParser::SourceElementContext *> CHTLJSParser::ProgramContext::sourceElement() {
  return getRuleContexts<CHTLJSParser::SourceElementContext>();
}

CHTLJSParser::SourceElementContext* CHTLJSParser::ProgramContext::sourceElement(size_t i) {
  return getRuleContext<CHTLJSParser::SourceElementContext>(i);
}


size_t CHTLJSParser::ProgramContext::getRuleIndex() const {
  return CHTLJSParser::RuleProgram;
}

void CHTLJSParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void CHTLJSParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

CHTLJSParser::ProgramContext* CHTLJSParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CHTLJSParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::CHTL_ANIMATE)
      | (1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST)
      | (1ULL << CHTLJSParser::IF)
      | (1ULL << CHTLJSParser::FOR)
      | (1ULL << CHTLJSParser::WHILE)
      | (1ULL << CHTLJSParser::DO)
      | (1ULL << CHTLJSParser::SWITCH)
      | (1ULL << CHTLJSParser::BREAK)
      | (1ULL << CHTLJSParser::CONTINUE)
      | (1ULL << CHTLJSParser::RETURN)
      | (1ULL << CHTLJSParser::TRY)
      | (1ULL << CHTLJSParser::THROW)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID)
      | (1ULL << CHTLJSParser::WITH)
      | (1ULL << CHTLJSParser::DEBUGGER))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::SEMICOLON - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::CHTL_DOUBLE_BRACE - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(224);
      sourceElement();
      setState(229);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(230);
    match(CHTLJSParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceElementContext ------------------------------------------------------------------

CHTLJSParser::SourceElementContext::SourceElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::StatementContext* CHTLJSParser::SourceElementContext::statement() {
  return getRuleContext<CHTLJSParser::StatementContext>(0);
}

CHTLJSParser::FunctionDeclarationContext* CHTLJSParser::SourceElementContext::functionDeclaration() {
  return getRuleContext<CHTLJSParser::FunctionDeclarationContext>(0);
}

CHTLJSParser::ClassDeclarationContext* CHTLJSParser::SourceElementContext::classDeclaration() {
  return getRuleContext<CHTLJSParser::ClassDeclarationContext>(0);
}

CHTLJSParser::ChtlStatementContext* CHTLJSParser::SourceElementContext::chtlStatement() {
  return getRuleContext<CHTLJSParser::ChtlStatementContext>(0);
}


size_t CHTLJSParser::SourceElementContext::getRuleIndex() const {
  return CHTLJSParser::RuleSourceElement;
}

void CHTLJSParser::SourceElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceElement(this);
}

void CHTLJSParser::SourceElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceElement(this);
}

CHTLJSParser::SourceElementContext* CHTLJSParser::sourceElement() {
  SourceElementContext *_localctx = _tracker.createInstance<SourceElementContext>(_ctx, getState());
  enterRule(_localctx, 2, CHTLJSParser::RuleSourceElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(236);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(232);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(233);
      functionDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(234);
      classDeclaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(235);
      chtlStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CHTLJSParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::BlockContext* CHTLJSParser::StatementContext::block() {
  return getRuleContext<CHTLJSParser::BlockContext>(0);
}

CHTLJSParser::VariableStatementContext* CHTLJSParser::StatementContext::variableStatement() {
  return getRuleContext<CHTLJSParser::VariableStatementContext>(0);
}

CHTLJSParser::EmptyStatementContext* CHTLJSParser::StatementContext::emptyStatement() {
  return getRuleContext<CHTLJSParser::EmptyStatementContext>(0);
}

CHTLJSParser::ExpressionStatementContext* CHTLJSParser::StatementContext::expressionStatement() {
  return getRuleContext<CHTLJSParser::ExpressionStatementContext>(0);
}

CHTLJSParser::IfStatementContext* CHTLJSParser::StatementContext::ifStatement() {
  return getRuleContext<CHTLJSParser::IfStatementContext>(0);
}

CHTLJSParser::IterationStatementContext* CHTLJSParser::StatementContext::iterationStatement() {
  return getRuleContext<CHTLJSParser::IterationStatementContext>(0);
}

CHTLJSParser::ContinueStatementContext* CHTLJSParser::StatementContext::continueStatement() {
  return getRuleContext<CHTLJSParser::ContinueStatementContext>(0);
}

CHTLJSParser::BreakStatementContext* CHTLJSParser::StatementContext::breakStatement() {
  return getRuleContext<CHTLJSParser::BreakStatementContext>(0);
}

CHTLJSParser::ReturnStatementContext* CHTLJSParser::StatementContext::returnStatement() {
  return getRuleContext<CHTLJSParser::ReturnStatementContext>(0);
}

CHTLJSParser::WithStatementContext* CHTLJSParser::StatementContext::withStatement() {
  return getRuleContext<CHTLJSParser::WithStatementContext>(0);
}

CHTLJSParser::LabelledStatementContext* CHTLJSParser::StatementContext::labelledStatement() {
  return getRuleContext<CHTLJSParser::LabelledStatementContext>(0);
}

CHTLJSParser::SwitchStatementContext* CHTLJSParser::StatementContext::switchStatement() {
  return getRuleContext<CHTLJSParser::SwitchStatementContext>(0);
}

CHTLJSParser::ThrowStatementContext* CHTLJSParser::StatementContext::throwStatement() {
  return getRuleContext<CHTLJSParser::ThrowStatementContext>(0);
}

CHTLJSParser::TryStatementContext* CHTLJSParser::StatementContext::tryStatement() {
  return getRuleContext<CHTLJSParser::TryStatementContext>(0);
}

CHTLJSParser::DebuggerStatementContext* CHTLJSParser::StatementContext::debuggerStatement() {
  return getRuleContext<CHTLJSParser::DebuggerStatementContext>(0);
}


size_t CHTLJSParser::StatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleStatement;
}

void CHTLJSParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void CHTLJSParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

CHTLJSParser::StatementContext* CHTLJSParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, CHTLJSParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(253);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(238);
      block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(239);
      variableStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(240);
      emptyStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(241);
      expressionStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(242);
      ifStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(243);
      iterationStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(244);
      continueStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(245);
      breakStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(246);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(247);
      withStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(248);
      labelledStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(249);
      switchStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(250);
      throwStatement();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(251);
      tryStatement();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(252);
      debuggerStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

CHTLJSParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::BlockContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

tree::TerminalNode* CHTLJSParser::BlockContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

CHTLJSParser::StatementListContext* CHTLJSParser::BlockContext::statementList() {
  return getRuleContext<CHTLJSParser::StatementListContext>(0);
}


size_t CHTLJSParser::BlockContext::getRuleIndex() const {
  return CHTLJSParser::RuleBlock;
}

void CHTLJSParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void CHTLJSParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

CHTLJSParser::BlockContext* CHTLJSParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, CHTLJSParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(255);
    match(CHTLJSParser::LBRACE);
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST)
      | (1ULL << CHTLJSParser::IF)
      | (1ULL << CHTLJSParser::FOR)
      | (1ULL << CHTLJSParser::WHILE)
      | (1ULL << CHTLJSParser::DO)
      | (1ULL << CHTLJSParser::SWITCH)
      | (1ULL << CHTLJSParser::BREAK)
      | (1ULL << CHTLJSParser::CONTINUE)
      | (1ULL << CHTLJSParser::RETURN)
      | (1ULL << CHTLJSParser::TRY)
      | (1ULL << CHTLJSParser::THROW)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID)
      | (1ULL << CHTLJSParser::WITH)
      | (1ULL << CHTLJSParser::DEBUGGER))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::SEMICOLON - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(256);
      statementList();
    }
    setState(259);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

CHTLJSParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::StatementContext *> CHTLJSParser::StatementListContext::statement() {
  return getRuleContexts<CHTLJSParser::StatementContext>();
}

CHTLJSParser::StatementContext* CHTLJSParser::StatementListContext::statement(size_t i) {
  return getRuleContext<CHTLJSParser::StatementContext>(i);
}


size_t CHTLJSParser::StatementListContext::getRuleIndex() const {
  return CHTLJSParser::RuleStatementList;
}

void CHTLJSParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void CHTLJSParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}

CHTLJSParser::StatementListContext* CHTLJSParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 8, CHTLJSParser::RuleStatementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(261);
      statement();
      setState(264); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST)
      | (1ULL << CHTLJSParser::IF)
      | (1ULL << CHTLJSParser::FOR)
      | (1ULL << CHTLJSParser::WHILE)
      | (1ULL << CHTLJSParser::DO)
      | (1ULL << CHTLJSParser::SWITCH)
      | (1ULL << CHTLJSParser::BREAK)
      | (1ULL << CHTLJSParser::CONTINUE)
      | (1ULL << CHTLJSParser::RETURN)
      | (1ULL << CHTLJSParser::TRY)
      | (1ULL << CHTLJSParser::THROW)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID)
      | (1ULL << CHTLJSParser::WITH)
      | (1ULL << CHTLJSParser::DEBUGGER))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::SEMICOLON - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableStatementContext ------------------------------------------------------------------

CHTLJSParser::VariableStatementContext::VariableStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::VariableDeclarationListContext* CHTLJSParser::VariableStatementContext::variableDeclarationList() {
  return getRuleContext<CHTLJSParser::VariableDeclarationListContext>(0);
}

tree::TerminalNode* CHTLJSParser::VariableStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLJSParser::VariableStatementContext::VAR() {
  return getToken(CHTLJSParser::VAR, 0);
}

tree::TerminalNode* CHTLJSParser::VariableStatementContext::LET() {
  return getToken(CHTLJSParser::LET, 0);
}

tree::TerminalNode* CHTLJSParser::VariableStatementContext::CONST() {
  return getToken(CHTLJSParser::CONST, 0);
}


size_t CHTLJSParser::VariableStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleVariableStatement;
}

void CHTLJSParser::VariableStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableStatement(this);
}

void CHTLJSParser::VariableStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableStatement(this);
}

CHTLJSParser::VariableStatementContext* CHTLJSParser::variableStatement() {
  VariableStatementContext *_localctx = _tracker.createInstance<VariableStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, CHTLJSParser::RuleVariableStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(267);
    variableDeclarationList();
    setState(268);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationListContext ------------------------------------------------------------------

CHTLJSParser::VariableDeclarationListContext::VariableDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::VariableDeclarationContext *> CHTLJSParser::VariableDeclarationListContext::variableDeclaration() {
  return getRuleContexts<CHTLJSParser::VariableDeclarationContext>();
}

CHTLJSParser::VariableDeclarationContext* CHTLJSParser::VariableDeclarationListContext::variableDeclaration(size_t i) {
  return getRuleContext<CHTLJSParser::VariableDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::VariableDeclarationListContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::VariableDeclarationListContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::VariableDeclarationListContext::getRuleIndex() const {
  return CHTLJSParser::RuleVariableDeclarationList;
}

void CHTLJSParser::VariableDeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclarationList(this);
}

void CHTLJSParser::VariableDeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclarationList(this);
}

CHTLJSParser::VariableDeclarationListContext* CHTLJSParser::variableDeclarationList() {
  VariableDeclarationListContext *_localctx = _tracker.createInstance<VariableDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 12, CHTLJSParser::RuleVariableDeclarationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    variableDeclaration();
    setState(275);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(271);
      match(CHTLJSParser::COMMA);
      setState(272);
      variableDeclaration();
      setState(277);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

CHTLJSParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::VariableDeclarationContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::VariableDeclarationContext::ASSIGN() {
  return getToken(CHTLJSParser::ASSIGN, 0);
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::VariableDeclarationContext::assignmentExpression() {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(0);
}


size_t CHTLJSParser::VariableDeclarationContext::getRuleIndex() const {
  return CHTLJSParser::RuleVariableDeclaration;
}

void CHTLJSParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void CHTLJSParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}

CHTLJSParser::VariableDeclarationContext* CHTLJSParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, CHTLJSParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    match(CHTLJSParser::IDENTIFIER);
    setState(281);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::ASSIGN) {
      setState(279);
      match(CHTLJSParser::ASSIGN);
      setState(280);
      assignmentExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

CHTLJSParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ConditionalExpressionContext* CHTLJSParser::AssignmentExpressionContext::conditionalExpression() {
  return getRuleContext<CHTLJSParser::ConditionalExpressionContext>(0);
}

CHTLJSParser::AssignmentOperatorContext* CHTLJSParser::AssignmentExpressionContext::assignmentOperator() {
  return getRuleContext<CHTLJSParser::AssignmentOperatorContext>(0);
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::AssignmentExpressionContext::assignmentExpression() {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(0);
}


size_t CHTLJSParser::AssignmentExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleAssignmentExpression;
}

void CHTLJSParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void CHTLJSParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, CHTLJSParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(287);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLJSParser::FUNCTION:
      case CHTLJSParser::NEW:
      case CHTLJSParser::THIS:
      case CHTLJSParser::SUPER:
      case CHTLJSParser::CLASS:
      case CHTLJSParser::TYPEOF:
      case CHTLJSParser::DELETE:
      case CHTLJSParser::VOID:
      case CHTLJSParser::IDENTIFIER:
      case CHTLJSParser::LBRACE:
      case CHTLJSParser::LPAREN:
      case CHTLJSParser::LBRACKET:
      case CHTLJSParser::BANG:
      case CHTLJSParser::TILDE:
      case CHTLJSParser::INC:
      case CHTLJSParser::DEC:
      case CHTLJSParser::ADD:
      case CHTLJSParser::SUB: {
        enterOuterAlt(_localctx, 1);
        setState(283);
        conditionalExpression();
        break;
      }

      case CHTLJSParser::ASSIGN:
      case CHTLJSParser::ADD_ASSIGN:
      case CHTLJSParser::SUB_ASSIGN:
      case CHTLJSParser::MUL_ASSIGN:
      case CHTLJSParser::DIV_ASSIGN:
      case CHTLJSParser::MOD_ASSIGN:
      case CHTLJSParser::POWER_ASSIGN:
      case CHTLJSParser::LSHIFT_ASSIGN:
      case CHTLJSParser::RSHIFT_ASSIGN:
      case CHTLJSParser::URSHIFT_ASSIGN:
      case CHTLJSParser::AND_ASSIGN:
      case CHTLJSParser::OR_ASSIGN:
      case CHTLJSParser::XOR_ASSIGN: {
        enterOuterAlt(_localctx, 2);
        setState(284);
        assignmentOperator();
        setState(285);
        assignmentExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

CHTLJSParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::ASSIGN() {
  return getToken(CHTLJSParser::ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::ADD_ASSIGN() {
  return getToken(CHTLJSParser::ADD_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::SUB_ASSIGN() {
  return getToken(CHTLJSParser::SUB_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::MUL_ASSIGN() {
  return getToken(CHTLJSParser::MUL_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::DIV_ASSIGN() {
  return getToken(CHTLJSParser::DIV_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::MOD_ASSIGN() {
  return getToken(CHTLJSParser::MOD_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::POWER_ASSIGN() {
  return getToken(CHTLJSParser::POWER_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::LSHIFT_ASSIGN() {
  return getToken(CHTLJSParser::LSHIFT_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::RSHIFT_ASSIGN() {
  return getToken(CHTLJSParser::RSHIFT_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::URSHIFT_ASSIGN() {
  return getToken(CHTLJSParser::URSHIFT_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::AND_ASSIGN() {
  return getToken(CHTLJSParser::AND_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::OR_ASSIGN() {
  return getToken(CHTLJSParser::OR_ASSIGN, 0);
}

tree::TerminalNode* CHTLJSParser::AssignmentOperatorContext::XOR_ASSIGN() {
  return getToken(CHTLJSParser::XOR_ASSIGN, 0);
}


size_t CHTLJSParser::AssignmentOperatorContext::getRuleIndex() const {
  return CHTLJSParser::RuleAssignmentOperator;
}

void CHTLJSParser::AssignmentOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperator(this);
}

void CHTLJSParser::AssignmentOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperator(this);
}

CHTLJSParser::AssignmentOperatorContext* CHTLJSParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 18, CHTLJSParser::RuleAssignmentOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(289);
    _la = _input->LA(1);
    if (!(((((_la - 79) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 79)) & ((1ULL << (CHTLJSParser::ASSIGN - 79))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 79))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 79)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmptyStatementContext ------------------------------------------------------------------

CHTLJSParser::EmptyStatementContext::EmptyStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::EmptyStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}


size_t CHTLJSParser::EmptyStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleEmptyStatement;
}

void CHTLJSParser::EmptyStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmptyStatement(this);
}

void CHTLJSParser::EmptyStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmptyStatement(this);
}

CHTLJSParser::EmptyStatementContext* CHTLJSParser::emptyStatement() {
  EmptyStatementContext *_localctx = _tracker.createInstance<EmptyStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, CHTLJSParser::RuleEmptyStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

CHTLJSParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ExpressionContext* CHTLJSParser::ExpressionStatementContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::ExpressionStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}


size_t CHTLJSParser::ExpressionStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleExpressionStatement;
}

void CHTLJSParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void CHTLJSParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}

CHTLJSParser::ExpressionStatementContext* CHTLJSParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, CHTLJSParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    expression();
    setState(294);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

CHTLJSParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::IfStatementContext::IF() {
  return getToken(CHTLJSParser::IF, 0);
}

tree::TerminalNode* CHTLJSParser::IfStatementContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::IfStatementContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::IfStatementContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

std::vector<CHTLJSParser::StatementContext *> CHTLJSParser::IfStatementContext::statement() {
  return getRuleContexts<CHTLJSParser::StatementContext>();
}

CHTLJSParser::StatementContext* CHTLJSParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<CHTLJSParser::StatementContext>(i);
}

tree::TerminalNode* CHTLJSParser::IfStatementContext::ELSE() {
  return getToken(CHTLJSParser::ELSE, 0);
}


size_t CHTLJSParser::IfStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleIfStatement;
}

void CHTLJSParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void CHTLJSParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}

CHTLJSParser::IfStatementContext* CHTLJSParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, CHTLJSParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    match(CHTLJSParser::IF);
    setState(297);
    match(CHTLJSParser::LPAREN);
    setState(298);
    expression();
    setState(299);
    match(CHTLJSParser::RPAREN);
    setState(300);
    statement();
    setState(303);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(301);
      match(CHTLJSParser::ELSE);
      setState(302);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

CHTLJSParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::IterationStatementContext::DO() {
  return getToken(CHTLJSParser::DO, 0);
}

CHTLJSParser::StatementContext* CHTLJSParser::IterationStatementContext::statement() {
  return getRuleContext<CHTLJSParser::StatementContext>(0);
}

tree::TerminalNode* CHTLJSParser::IterationStatementContext::WHILE() {
  return getToken(CHTLJSParser::WHILE, 0);
}

tree::TerminalNode* CHTLJSParser::IterationStatementContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

std::vector<CHTLJSParser::ExpressionContext *> CHTLJSParser::IterationStatementContext::expression() {
  return getRuleContexts<CHTLJSParser::ExpressionContext>();
}

CHTLJSParser::ExpressionContext* CHTLJSParser::IterationStatementContext::expression(size_t i) {
  return getRuleContext<CHTLJSParser::ExpressionContext>(i);
}

tree::TerminalNode* CHTLJSParser::IterationStatementContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> CHTLJSParser::IterationStatementContext::SEMICOLON() {
  return getTokens(CHTLJSParser::SEMICOLON);
}

tree::TerminalNode* CHTLJSParser::IterationStatementContext::SEMICOLON(size_t i) {
  return getToken(CHTLJSParser::SEMICOLON, i);
}

tree::TerminalNode* CHTLJSParser::IterationStatementContext::FOR() {
  return getToken(CHTLJSParser::FOR, 0);
}

CHTLJSParser::VariableStatementContext* CHTLJSParser::IterationStatementContext::variableStatement() {
  return getRuleContext<CHTLJSParser::VariableStatementContext>(0);
}


size_t CHTLJSParser::IterationStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleIterationStatement;
}

void CHTLJSParser::IterationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIterationStatement(this);
}

void CHTLJSParser::IterationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIterationStatement(this);
}

CHTLJSParser::IterationStatementContext* CHTLJSParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, CHTLJSParser::RuleIterationStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(335);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLJSParser::DO: {
        enterOuterAlt(_localctx, 1);
        setState(305);
        match(CHTLJSParser::DO);
        setState(306);
        statement();
        setState(307);
        match(CHTLJSParser::WHILE);
        setState(308);
        match(CHTLJSParser::LPAREN);
        setState(309);
        expression();
        setState(310);
        match(CHTLJSParser::RPAREN);
        setState(311);
        match(CHTLJSParser::SEMICOLON);
        break;
      }

      case CHTLJSParser::WHILE: {
        enterOuterAlt(_localctx, 2);
        setState(313);
        match(CHTLJSParser::WHILE);
        setState(314);
        match(CHTLJSParser::LPAREN);
        setState(315);
        expression();
        setState(316);
        match(CHTLJSParser::RPAREN);
        setState(317);
        statement();
        break;
      }

      case CHTLJSParser::FOR: {
        enterOuterAlt(_localctx, 3);
        setState(319);
        match(CHTLJSParser::FOR);
        setState(320);
        match(CHTLJSParser::LPAREN);
        setState(323);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case CHTLJSParser::FUNCTION:
          case CHTLJSParser::NEW:
          case CHTLJSParser::THIS:
          case CHTLJSParser::SUPER:
          case CHTLJSParser::CLASS:
          case CHTLJSParser::TYPEOF:
          case CHTLJSParser::DELETE:
          case CHTLJSParser::VOID:
          case CHTLJSParser::IDENTIFIER:
          case CHTLJSParser::LBRACE:
          case CHTLJSParser::LPAREN:
          case CHTLJSParser::LBRACKET:
          case CHTLJSParser::ASSIGN:
          case CHTLJSParser::BANG:
          case CHTLJSParser::TILDE:
          case CHTLJSParser::INC:
          case CHTLJSParser::DEC:
          case CHTLJSParser::ADD_ASSIGN:
          case CHTLJSParser::SUB_ASSIGN:
          case CHTLJSParser::MUL_ASSIGN:
          case CHTLJSParser::DIV_ASSIGN:
          case CHTLJSParser::MOD_ASSIGN:
          case CHTLJSParser::POWER_ASSIGN:
          case CHTLJSParser::LSHIFT_ASSIGN:
          case CHTLJSParser::RSHIFT_ASSIGN:
          case CHTLJSParser::URSHIFT_ASSIGN:
          case CHTLJSParser::AND_ASSIGN:
          case CHTLJSParser::OR_ASSIGN:
          case CHTLJSParser::XOR_ASSIGN:
          case CHTLJSParser::ADD:
          case CHTLJSParser::SUB: {
            setState(321);
            expression();
            break;
          }

          case CHTLJSParser::VAR:
          case CHTLJSParser::LET:
          case CHTLJSParser::CONST: {
            setState(322);
            variableStatement();
            break;
          }

          case CHTLJSParser::SEMICOLON: {
            break;
          }

        default:
          break;
        }
        setState(325);
        match(CHTLJSParser::SEMICOLON);
        setState(327);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
          | (1ULL << CHTLJSParser::NEW)
          | (1ULL << CHTLJSParser::THIS)
          | (1ULL << CHTLJSParser::SUPER)
          | (1ULL << CHTLJSParser::CLASS)
          | (1ULL << CHTLJSParser::TYPEOF)
          | (1ULL << CHTLJSParser::DELETE)
          | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
          | (1ULL << (CHTLJSParser::LBRACE - 69))
          | (1ULL << (CHTLJSParser::LPAREN - 69))
          | (1ULL << (CHTLJSParser::LBRACKET - 69))
          | (1ULL << (CHTLJSParser::ASSIGN - 69))
          | (1ULL << (CHTLJSParser::BANG - 69))
          | (1ULL << (CHTLJSParser::TILDE - 69))
          | (1ULL << (CHTLJSParser::INC - 69))
          | (1ULL << (CHTLJSParser::DEC - 69))
          | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::ADD - 69))
          | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
          setState(326);
          expression();
        }
        setState(329);
        match(CHTLJSParser::SEMICOLON);
        setState(331);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
          | (1ULL << CHTLJSParser::NEW)
          | (1ULL << CHTLJSParser::THIS)
          | (1ULL << CHTLJSParser::SUPER)
          | (1ULL << CHTLJSParser::CLASS)
          | (1ULL << CHTLJSParser::TYPEOF)
          | (1ULL << CHTLJSParser::DELETE)
          | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
          | (1ULL << (CHTLJSParser::LBRACE - 69))
          | (1ULL << (CHTLJSParser::LPAREN - 69))
          | (1ULL << (CHTLJSParser::LBRACKET - 69))
          | (1ULL << (CHTLJSParser::ASSIGN - 69))
          | (1ULL << (CHTLJSParser::BANG - 69))
          | (1ULL << (CHTLJSParser::TILDE - 69))
          | (1ULL << (CHTLJSParser::INC - 69))
          | (1ULL << (CHTLJSParser::DEC - 69))
          | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
          | (1ULL << (CHTLJSParser::ADD - 69))
          | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
          setState(330);
          expression();
        }
        setState(333);
        match(CHTLJSParser::RPAREN);
        setState(334);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

CHTLJSParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ContinueStatementContext::CONTINUE() {
  return getToken(CHTLJSParser::CONTINUE, 0);
}

tree::TerminalNode* CHTLJSParser::ContinueStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLJSParser::ContinueStatementContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}


size_t CHTLJSParser::ContinueStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleContinueStatement;
}

void CHTLJSParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void CHTLJSParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}

CHTLJSParser::ContinueStatementContext* CHTLJSParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, CHTLJSParser::RuleContinueStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    match(CHTLJSParser::CONTINUE);
    setState(339);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::IDENTIFIER) {
      setState(338);
      match(CHTLJSParser::IDENTIFIER);
    }
    setState(341);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

CHTLJSParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::BreakStatementContext::BREAK() {
  return getToken(CHTLJSParser::BREAK, 0);
}

tree::TerminalNode* CHTLJSParser::BreakStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLJSParser::BreakStatementContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}


size_t CHTLJSParser::BreakStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleBreakStatement;
}

void CHTLJSParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void CHTLJSParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}

CHTLJSParser::BreakStatementContext* CHTLJSParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, CHTLJSParser::RuleBreakStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(343);
    match(CHTLJSParser::BREAK);
    setState(345);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::IDENTIFIER) {
      setState(344);
      match(CHTLJSParser::IDENTIFIER);
    }
    setState(347);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

CHTLJSParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ReturnStatementContext::RETURN() {
  return getToken(CHTLJSParser::RETURN, 0);
}

tree::TerminalNode* CHTLJSParser::ReturnStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::ReturnStatementContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}


size_t CHTLJSParser::ReturnStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleReturnStatement;
}

void CHTLJSParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void CHTLJSParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}

CHTLJSParser::ReturnStatementContext* CHTLJSParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, CHTLJSParser::RuleReturnStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    match(CHTLJSParser::RETURN);
    setState(351);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(350);
      expression();
    }
    setState(353);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithStatementContext ------------------------------------------------------------------

CHTLJSParser::WithStatementContext::WithStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::WithStatementContext::WITH() {
  return getToken(CHTLJSParser::WITH, 0);
}

tree::TerminalNode* CHTLJSParser::WithStatementContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::WithStatementContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::WithStatementContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

CHTLJSParser::StatementContext* CHTLJSParser::WithStatementContext::statement() {
  return getRuleContext<CHTLJSParser::StatementContext>(0);
}


size_t CHTLJSParser::WithStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleWithStatement;
}

void CHTLJSParser::WithStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWithStatement(this);
}

void CHTLJSParser::WithStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWithStatement(this);
}

CHTLJSParser::WithStatementContext* CHTLJSParser::withStatement() {
  WithStatementContext *_localctx = _tracker.createInstance<WithStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, CHTLJSParser::RuleWithStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(355);
    match(CHTLJSParser::WITH);
    setState(356);
    match(CHTLJSParser::LPAREN);
    setState(357);
    expression();
    setState(358);
    match(CHTLJSParser::RPAREN);
    setState(359);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelledStatementContext ------------------------------------------------------------------

CHTLJSParser::LabelledStatementContext::LabelledStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::LabelledStatementContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::LabelledStatementContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::StatementContext* CHTLJSParser::LabelledStatementContext::statement() {
  return getRuleContext<CHTLJSParser::StatementContext>(0);
}


size_t CHTLJSParser::LabelledStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleLabelledStatement;
}

void CHTLJSParser::LabelledStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabelledStatement(this);
}

void CHTLJSParser::LabelledStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabelledStatement(this);
}

CHTLJSParser::LabelledStatementContext* CHTLJSParser::labelledStatement() {
  LabelledStatementContext *_localctx = _tracker.createInstance<LabelledStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, CHTLJSParser::RuleLabelledStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(361);
    match(CHTLJSParser::IDENTIFIER);
    setState(362);
    match(CHTLJSParser::COLON);
    setState(363);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchStatementContext ------------------------------------------------------------------

CHTLJSParser::SwitchStatementContext::SwitchStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::SwitchStatementContext::SWITCH() {
  return getToken(CHTLJSParser::SWITCH, 0);
}

tree::TerminalNode* CHTLJSParser::SwitchStatementContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::SwitchStatementContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::SwitchStatementContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

CHTLJSParser::CaseBlockContext* CHTLJSParser::SwitchStatementContext::caseBlock() {
  return getRuleContext<CHTLJSParser::CaseBlockContext>(0);
}


size_t CHTLJSParser::SwitchStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleSwitchStatement;
}

void CHTLJSParser::SwitchStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSwitchStatement(this);
}

void CHTLJSParser::SwitchStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSwitchStatement(this);
}

CHTLJSParser::SwitchStatementContext* CHTLJSParser::switchStatement() {
  SwitchStatementContext *_localctx = _tracker.createInstance<SwitchStatementContext>(_ctx, getState());
  enterRule(_localctx, 38, CHTLJSParser::RuleSwitchStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(365);
    match(CHTLJSParser::SWITCH);
    setState(366);
    match(CHTLJSParser::LPAREN);
    setState(367);
    expression();
    setState(368);
    match(CHTLJSParser::RPAREN);
    setState(369);
    caseBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseBlockContext ------------------------------------------------------------------

CHTLJSParser::CaseBlockContext::CaseBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::CaseBlockContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

tree::TerminalNode* CHTLJSParser::CaseBlockContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

std::vector<CHTLJSParser::CaseClausesContext *> CHTLJSParser::CaseBlockContext::caseClauses() {
  return getRuleContexts<CHTLJSParser::CaseClausesContext>();
}

CHTLJSParser::CaseClausesContext* CHTLJSParser::CaseBlockContext::caseClauses(size_t i) {
  return getRuleContext<CHTLJSParser::CaseClausesContext>(i);
}

CHTLJSParser::DefaultClauseContext* CHTLJSParser::CaseBlockContext::defaultClause() {
  return getRuleContext<CHTLJSParser::DefaultClauseContext>(0);
}


size_t CHTLJSParser::CaseBlockContext::getRuleIndex() const {
  return CHTLJSParser::RuleCaseBlock;
}

void CHTLJSParser::CaseBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseBlock(this);
}

void CHTLJSParser::CaseBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseBlock(this);
}

CHTLJSParser::CaseBlockContext* CHTLJSParser::caseBlock() {
  CaseBlockContext *_localctx = _tracker.createInstance<CaseBlockContext>(_ctx, getState());
  enterRule(_localctx, 40, CHTLJSParser::RuleCaseBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(371);
    match(CHTLJSParser::LBRACE);
    setState(373);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::CASE) {
      setState(372);
      caseClauses();
    }
    setState(379);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::DEFAULT) {
      setState(375);
      defaultClause();
      setState(377);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::CASE) {
        setState(376);
        caseClauses();
      }
    }
    setState(381);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClausesContext ------------------------------------------------------------------

CHTLJSParser::CaseClausesContext::CaseClausesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::CaseClauseContext *> CHTLJSParser::CaseClausesContext::caseClause() {
  return getRuleContexts<CHTLJSParser::CaseClauseContext>();
}

CHTLJSParser::CaseClauseContext* CHTLJSParser::CaseClausesContext::caseClause(size_t i) {
  return getRuleContext<CHTLJSParser::CaseClauseContext>(i);
}


size_t CHTLJSParser::CaseClausesContext::getRuleIndex() const {
  return CHTLJSParser::RuleCaseClauses;
}

void CHTLJSParser::CaseClausesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseClauses(this);
}

void CHTLJSParser::CaseClausesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseClauses(this);
}

CHTLJSParser::CaseClausesContext* CHTLJSParser::caseClauses() {
  CaseClausesContext *_localctx = _tracker.createInstance<CaseClausesContext>(_ctx, getState());
  enterRule(_localctx, 42, CHTLJSParser::RuleCaseClauses);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(384); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(383);
      caseClause();
      setState(386); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CHTLJSParser::CASE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClauseContext ------------------------------------------------------------------

CHTLJSParser::CaseClauseContext::CaseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::CaseClauseContext::CASE() {
  return getToken(CHTLJSParser::CASE, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::CaseClauseContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::CaseClauseContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::StatementListContext* CHTLJSParser::CaseClauseContext::statementList() {
  return getRuleContext<CHTLJSParser::StatementListContext>(0);
}


size_t CHTLJSParser::CaseClauseContext::getRuleIndex() const {
  return CHTLJSParser::RuleCaseClause;
}

void CHTLJSParser::CaseClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseClause(this);
}

void CHTLJSParser::CaseClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseClause(this);
}

CHTLJSParser::CaseClauseContext* CHTLJSParser::caseClause() {
  CaseClauseContext *_localctx = _tracker.createInstance<CaseClauseContext>(_ctx, getState());
  enterRule(_localctx, 44, CHTLJSParser::RuleCaseClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(388);
    match(CHTLJSParser::CASE);
    setState(389);
    expression();
    setState(390);
    match(CHTLJSParser::COLON);
    setState(392);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST)
      | (1ULL << CHTLJSParser::IF)
      | (1ULL << CHTLJSParser::FOR)
      | (1ULL << CHTLJSParser::WHILE)
      | (1ULL << CHTLJSParser::DO)
      | (1ULL << CHTLJSParser::SWITCH)
      | (1ULL << CHTLJSParser::BREAK)
      | (1ULL << CHTLJSParser::CONTINUE)
      | (1ULL << CHTLJSParser::RETURN)
      | (1ULL << CHTLJSParser::TRY)
      | (1ULL << CHTLJSParser::THROW)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID)
      | (1ULL << CHTLJSParser::WITH)
      | (1ULL << CHTLJSParser::DEBUGGER))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::SEMICOLON - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(391);
      statementList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultClauseContext ------------------------------------------------------------------

CHTLJSParser::DefaultClauseContext::DefaultClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::DefaultClauseContext::DEFAULT() {
  return getToken(CHTLJSParser::DEFAULT, 0);
}

tree::TerminalNode* CHTLJSParser::DefaultClauseContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::StatementListContext* CHTLJSParser::DefaultClauseContext::statementList() {
  return getRuleContext<CHTLJSParser::StatementListContext>(0);
}


size_t CHTLJSParser::DefaultClauseContext::getRuleIndex() const {
  return CHTLJSParser::RuleDefaultClause;
}

void CHTLJSParser::DefaultClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultClause(this);
}

void CHTLJSParser::DefaultClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultClause(this);
}

CHTLJSParser::DefaultClauseContext* CHTLJSParser::defaultClause() {
  DefaultClauseContext *_localctx = _tracker.createInstance<DefaultClauseContext>(_ctx, getState());
  enterRule(_localctx, 46, CHTLJSParser::RuleDefaultClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(394);
    match(CHTLJSParser::DEFAULT);
    setState(395);
    match(CHTLJSParser::COLON);
    setState(397);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST)
      | (1ULL << CHTLJSParser::IF)
      | (1ULL << CHTLJSParser::FOR)
      | (1ULL << CHTLJSParser::WHILE)
      | (1ULL << CHTLJSParser::DO)
      | (1ULL << CHTLJSParser::SWITCH)
      | (1ULL << CHTLJSParser::BREAK)
      | (1ULL << CHTLJSParser::CONTINUE)
      | (1ULL << CHTLJSParser::RETURN)
      | (1ULL << CHTLJSParser::TRY)
      | (1ULL << CHTLJSParser::THROW)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID)
      | (1ULL << CHTLJSParser::WITH)
      | (1ULL << CHTLJSParser::DEBUGGER))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::SEMICOLON - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(396);
      statementList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThrowStatementContext ------------------------------------------------------------------

CHTLJSParser::ThrowStatementContext::ThrowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ThrowStatementContext::THROW() {
  return getToken(CHTLJSParser::THROW, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::ThrowStatementContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::ThrowStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}


size_t CHTLJSParser::ThrowStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleThrowStatement;
}

void CHTLJSParser::ThrowStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThrowStatement(this);
}

void CHTLJSParser::ThrowStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThrowStatement(this);
}

CHTLJSParser::ThrowStatementContext* CHTLJSParser::throwStatement() {
  ThrowStatementContext *_localctx = _tracker.createInstance<ThrowStatementContext>(_ctx, getState());
  enterRule(_localctx, 48, CHTLJSParser::RuleThrowStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(399);
    match(CHTLJSParser::THROW);
    setState(400);
    expression();
    setState(401);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TryStatementContext ------------------------------------------------------------------

CHTLJSParser::TryStatementContext::TryStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::TryStatementContext::TRY() {
  return getToken(CHTLJSParser::TRY, 0);
}

CHTLJSParser::BlockContext* CHTLJSParser::TryStatementContext::block() {
  return getRuleContext<CHTLJSParser::BlockContext>(0);
}

CHTLJSParser::CatchBlockContext* CHTLJSParser::TryStatementContext::catchBlock() {
  return getRuleContext<CHTLJSParser::CatchBlockContext>(0);
}

CHTLJSParser::FinallyBlockContext* CHTLJSParser::TryStatementContext::finallyBlock() {
  return getRuleContext<CHTLJSParser::FinallyBlockContext>(0);
}


size_t CHTLJSParser::TryStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleTryStatement;
}

void CHTLJSParser::TryStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTryStatement(this);
}

void CHTLJSParser::TryStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTryStatement(this);
}

CHTLJSParser::TryStatementContext* CHTLJSParser::tryStatement() {
  TryStatementContext *_localctx = _tracker.createInstance<TryStatementContext>(_ctx, getState());
  enterRule(_localctx, 50, CHTLJSParser::RuleTryStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(416);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(403);
      match(CHTLJSParser::TRY);
      setState(404);
      block();
      setState(406);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::CATCH) {
        setState(405);
        catchBlock();
      }
      setState(409);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::FINALLY) {
        setState(408);
        finallyBlock();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(411);
      match(CHTLJSParser::TRY);
      setState(412);
      block();
      setState(413);
      catchBlock();
      setState(414);
      finallyBlock();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CatchBlockContext ------------------------------------------------------------------

CHTLJSParser::CatchBlockContext::CatchBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::CatchBlockContext::CATCH() {
  return getToken(CHTLJSParser::CATCH, 0);
}

tree::TerminalNode* CHTLJSParser::CatchBlockContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::CatchBlockContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::CatchBlockContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

CHTLJSParser::BlockContext* CHTLJSParser::CatchBlockContext::block() {
  return getRuleContext<CHTLJSParser::BlockContext>(0);
}


size_t CHTLJSParser::CatchBlockContext::getRuleIndex() const {
  return CHTLJSParser::RuleCatchBlock;
}

void CHTLJSParser::CatchBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCatchBlock(this);
}

void CHTLJSParser::CatchBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCatchBlock(this);
}

CHTLJSParser::CatchBlockContext* CHTLJSParser::catchBlock() {
  CatchBlockContext *_localctx = _tracker.createInstance<CatchBlockContext>(_ctx, getState());
  enterRule(_localctx, 52, CHTLJSParser::RuleCatchBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(418);
    match(CHTLJSParser::CATCH);
    setState(419);
    match(CHTLJSParser::LPAREN);
    setState(420);
    match(CHTLJSParser::IDENTIFIER);
    setState(421);
    match(CHTLJSParser::RPAREN);
    setState(422);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FinallyBlockContext ------------------------------------------------------------------

CHTLJSParser::FinallyBlockContext::FinallyBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::FinallyBlockContext::FINALLY() {
  return getToken(CHTLJSParser::FINALLY, 0);
}

CHTLJSParser::BlockContext* CHTLJSParser::FinallyBlockContext::block() {
  return getRuleContext<CHTLJSParser::BlockContext>(0);
}


size_t CHTLJSParser::FinallyBlockContext::getRuleIndex() const {
  return CHTLJSParser::RuleFinallyBlock;
}

void CHTLJSParser::FinallyBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFinallyBlock(this);
}

void CHTLJSParser::FinallyBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFinallyBlock(this);
}

CHTLJSParser::FinallyBlockContext* CHTLJSParser::finallyBlock() {
  FinallyBlockContext *_localctx = _tracker.createInstance<FinallyBlockContext>(_ctx, getState());
  enterRule(_localctx, 54, CHTLJSParser::RuleFinallyBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(424);
    match(CHTLJSParser::FINALLY);
    setState(425);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DebuggerStatementContext ------------------------------------------------------------------

CHTLJSParser::DebuggerStatementContext::DebuggerStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::DebuggerStatementContext::DEBUGGER() {
  return getToken(CHTLJSParser::DEBUGGER, 0);
}

tree::TerminalNode* CHTLJSParser::DebuggerStatementContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}


size_t CHTLJSParser::DebuggerStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleDebuggerStatement;
}

void CHTLJSParser::DebuggerStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDebuggerStatement(this);
}

void CHTLJSParser::DebuggerStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDebuggerStatement(this);
}

CHTLJSParser::DebuggerStatementContext* CHTLJSParser::debuggerStatement() {
  DebuggerStatementContext *_localctx = _tracker.createInstance<DebuggerStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, CHTLJSParser::RuleDebuggerStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    match(CHTLJSParser::DEBUGGER);
    setState(428);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

CHTLJSParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::FunctionDeclarationContext::FUNCTION() {
  return getToken(CHTLJSParser::FUNCTION, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionDeclarationContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionDeclarationContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionDeclarationContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionDeclarationContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::FunctionBodyContext* CHTLJSParser::FunctionDeclarationContext::functionBody() {
  return getRuleContext<CHTLJSParser::FunctionBodyContext>(0);
}

tree::TerminalNode* CHTLJSParser::FunctionDeclarationContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

CHTLJSParser::FormalParameterListContext* CHTLJSParser::FunctionDeclarationContext::formalParameterList() {
  return getRuleContext<CHTLJSParser::FormalParameterListContext>(0);
}


size_t CHTLJSParser::FunctionDeclarationContext::getRuleIndex() const {
  return CHTLJSParser::RuleFunctionDeclaration;
}

void CHTLJSParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void CHTLJSParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}

CHTLJSParser::FunctionDeclarationContext* CHTLJSParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 58, CHTLJSParser::RuleFunctionDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(430);
    match(CHTLJSParser::FUNCTION);
    setState(431);
    match(CHTLJSParser::IDENTIFIER);
    setState(432);
    match(CHTLJSParser::LPAREN);
    setState(434);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::IDENTIFIER) {
      setState(433);
      formalParameterList();
    }
    setState(436);
    match(CHTLJSParser::RPAREN);
    setState(437);
    match(CHTLJSParser::LBRACE);
    setState(438);
    functionBody();
    setState(439);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormalParameterListContext ------------------------------------------------------------------

CHTLJSParser::FormalParameterListContext::FormalParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLJSParser::FormalParameterListContext::IDENTIFIER() {
  return getTokens(CHTLJSParser::IDENTIFIER);
}

tree::TerminalNode* CHTLJSParser::FormalParameterListContext::IDENTIFIER(size_t i) {
  return getToken(CHTLJSParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::FormalParameterListContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::FormalParameterListContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::FormalParameterListContext::getRuleIndex() const {
  return CHTLJSParser::RuleFormalParameterList;
}

void CHTLJSParser::FormalParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormalParameterList(this);
}

void CHTLJSParser::FormalParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormalParameterList(this);
}

CHTLJSParser::FormalParameterListContext* CHTLJSParser::formalParameterList() {
  FormalParameterListContext *_localctx = _tracker.createInstance<FormalParameterListContext>(_ctx, getState());
  enterRule(_localctx, 60, CHTLJSParser::RuleFormalParameterList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(441);
    match(CHTLJSParser::IDENTIFIER);
    setState(446);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(442);
      match(CHTLJSParser::COMMA);
      setState(443);
      match(CHTLJSParser::IDENTIFIER);
      setState(448);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionBodyContext ------------------------------------------------------------------

CHTLJSParser::FunctionBodyContext::FunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::SourceElementsContext* CHTLJSParser::FunctionBodyContext::sourceElements() {
  return getRuleContext<CHTLJSParser::SourceElementsContext>(0);
}


size_t CHTLJSParser::FunctionBodyContext::getRuleIndex() const {
  return CHTLJSParser::RuleFunctionBody;
}

void CHTLJSParser::FunctionBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionBody(this);
}

void CHTLJSParser::FunctionBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionBody(this);
}

CHTLJSParser::FunctionBodyContext* CHTLJSParser::functionBody() {
  FunctionBodyContext *_localctx = _tracker.createInstance<FunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 62, CHTLJSParser::RuleFunctionBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(450);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::CHTL_ANIMATE)
      | (1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST)
      | (1ULL << CHTLJSParser::IF)
      | (1ULL << CHTLJSParser::FOR)
      | (1ULL << CHTLJSParser::WHILE)
      | (1ULL << CHTLJSParser::DO)
      | (1ULL << CHTLJSParser::SWITCH)
      | (1ULL << CHTLJSParser::BREAK)
      | (1ULL << CHTLJSParser::CONTINUE)
      | (1ULL << CHTLJSParser::RETURN)
      | (1ULL << CHTLJSParser::TRY)
      | (1ULL << CHTLJSParser::THROW)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID)
      | (1ULL << CHTLJSParser::WITH)
      | (1ULL << CHTLJSParser::DEBUGGER))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::SEMICOLON - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::CHTL_DOUBLE_BRACE - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(449);
      sourceElements();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclarationContext ------------------------------------------------------------------

CHTLJSParser::ClassDeclarationContext::ClassDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ClassDeclarationContext::CLASS() {
  return getToken(CHTLJSParser::CLASS, 0);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ClassDeclarationContext::IDENTIFIER() {
  return getTokens(CHTLJSParser::IDENTIFIER);
}

tree::TerminalNode* CHTLJSParser::ClassDeclarationContext::IDENTIFIER(size_t i) {
  return getToken(CHTLJSParser::IDENTIFIER, i);
}

tree::TerminalNode* CHTLJSParser::ClassDeclarationContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

tree::TerminalNode* CHTLJSParser::ClassDeclarationContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

tree::TerminalNode* CHTLJSParser::ClassDeclarationContext::EXTENDS() {
  return getToken(CHTLJSParser::EXTENDS, 0);
}

CHTLJSParser::ClassBodyContext* CHTLJSParser::ClassDeclarationContext::classBody() {
  return getRuleContext<CHTLJSParser::ClassBodyContext>(0);
}


size_t CHTLJSParser::ClassDeclarationContext::getRuleIndex() const {
  return CHTLJSParser::RuleClassDeclaration;
}

void CHTLJSParser::ClassDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDeclaration(this);
}

void CHTLJSParser::ClassDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDeclaration(this);
}

CHTLJSParser::ClassDeclarationContext* CHTLJSParser::classDeclaration() {
  ClassDeclarationContext *_localctx = _tracker.createInstance<ClassDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 64, CHTLJSParser::RuleClassDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(452);
    match(CHTLJSParser::CLASS);
    setState(453);
    match(CHTLJSParser::IDENTIFIER);
    setState(456);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::EXTENDS) {
      setState(454);
      match(CHTLJSParser::EXTENDS);
      setState(455);
      match(CHTLJSParser::IDENTIFIER);
    }
    setState(458);
    match(CHTLJSParser::LBRACE);
    setState(460);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 47) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 47)) & ((1ULL << (CHTLJSParser::GET - 47))
      | (1ULL << (CHTLJSParser::SET - 47))
      | (1ULL << (CHTLJSParser::IDENTIFIER - 47)))) != 0)) {
      setState(459);
      classBody();
    }
    setState(462);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassBodyContext ------------------------------------------------------------------

CHTLJSParser::ClassBodyContext::ClassBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::ClassElementContext *> CHTLJSParser::ClassBodyContext::classElement() {
  return getRuleContexts<CHTLJSParser::ClassElementContext>();
}

CHTLJSParser::ClassElementContext* CHTLJSParser::ClassBodyContext::classElement(size_t i) {
  return getRuleContext<CHTLJSParser::ClassElementContext>(i);
}


size_t CHTLJSParser::ClassBodyContext::getRuleIndex() const {
  return CHTLJSParser::RuleClassBody;
}

void CHTLJSParser::ClassBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassBody(this);
}

void CHTLJSParser::ClassBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassBody(this);
}

CHTLJSParser::ClassBodyContext* CHTLJSParser::classBody() {
  ClassBodyContext *_localctx = _tracker.createInstance<ClassBodyContext>(_ctx, getState());
  enterRule(_localctx, 66, CHTLJSParser::RuleClassBody);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(465); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(464);
      classElement();
      setState(467); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 47) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 47)) & ((1ULL << (CHTLJSParser::GET - 47))
      | (1ULL << (CHTLJSParser::SET - 47))
      | (1ULL << (CHTLJSParser::IDENTIFIER - 47)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassElementContext ------------------------------------------------------------------

CHTLJSParser::ClassElementContext::ClassElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::MethodDefinitionContext* CHTLJSParser::ClassElementContext::methodDefinition() {
  return getRuleContext<CHTLJSParser::MethodDefinitionContext>(0);
}


size_t CHTLJSParser::ClassElementContext::getRuleIndex() const {
  return CHTLJSParser::RuleClassElement;
}

void CHTLJSParser::ClassElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassElement(this);
}

void CHTLJSParser::ClassElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassElement(this);
}

CHTLJSParser::ClassElementContext* CHTLJSParser::classElement() {
  ClassElementContext *_localctx = _tracker.createInstance<ClassElementContext>(_ctx, getState());
  enterRule(_localctx, 68, CHTLJSParser::RuleClassElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(469);
    methodDefinition();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodDefinitionContext ------------------------------------------------------------------

CHTLJSParser::MethodDefinitionContext::MethodDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::MethodDefinitionContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::MethodDefinitionContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::MethodDefinitionContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::MethodDefinitionContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::FunctionBodyContext* CHTLJSParser::MethodDefinitionContext::functionBody() {
  return getRuleContext<CHTLJSParser::FunctionBodyContext>(0);
}

tree::TerminalNode* CHTLJSParser::MethodDefinitionContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

CHTLJSParser::FormalParameterListContext* CHTLJSParser::MethodDefinitionContext::formalParameterList() {
  return getRuleContext<CHTLJSParser::FormalParameterListContext>(0);
}

tree::TerminalNode* CHTLJSParser::MethodDefinitionContext::GET() {
  return getToken(CHTLJSParser::GET, 0);
}

tree::TerminalNode* CHTLJSParser::MethodDefinitionContext::SET() {
  return getToken(CHTLJSParser::SET, 0);
}


size_t CHTLJSParser::MethodDefinitionContext::getRuleIndex() const {
  return CHTLJSParser::RuleMethodDefinition;
}

void CHTLJSParser::MethodDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodDefinition(this);
}

void CHTLJSParser::MethodDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodDefinition(this);
}

CHTLJSParser::MethodDefinitionContext* CHTLJSParser::methodDefinition() {
  MethodDefinitionContext *_localctx = _tracker.createInstance<MethodDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 70, CHTLJSParser::RuleMethodDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(472);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::GET

    || _la == CHTLJSParser::SET) {
      setState(471);
      _la = _input->LA(1);
      if (!(_la == CHTLJSParser::GET

      || _la == CHTLJSParser::SET)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(474);
    match(CHTLJSParser::IDENTIFIER);
    setState(475);
    match(CHTLJSParser::LPAREN);
    setState(477);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::IDENTIFIER) {
      setState(476);
      formalParameterList();
    }
    setState(479);
    match(CHTLJSParser::RPAREN);
    setState(480);
    match(CHTLJSParser::LBRACE);
    setState(481);
    functionBody();
    setState(482);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CHTLJSParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::AssignmentExpressionContext *> CHTLJSParser::ExpressionContext::assignmentExpression() {
  return getRuleContexts<CHTLJSParser::AssignmentExpressionContext>();
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::ExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ExpressionContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ExpressionContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleExpression;
}

void CHTLJSParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void CHTLJSParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 72, CHTLJSParser::RuleExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(484);
    assignmentExpression();
    setState(489);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(485);
      match(CHTLJSParser::COMMA);
      setState(486);
      assignmentExpression();
      setState(491);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

CHTLJSParser::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::LogicalORExpressionContext* CHTLJSParser::ConditionalExpressionContext::logicalORExpression() {
  return getRuleContext<CHTLJSParser::LogicalORExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::ConditionalExpressionContext::QUESTION() {
  return getToken(CHTLJSParser::QUESTION, 0);
}

std::vector<CHTLJSParser::AssignmentExpressionContext *> CHTLJSParser::ConditionalExpressionContext::assignmentExpression() {
  return getRuleContexts<CHTLJSParser::AssignmentExpressionContext>();
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::ConditionalExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(i);
}

tree::TerminalNode* CHTLJSParser::ConditionalExpressionContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}


size_t CHTLJSParser::ConditionalExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleConditionalExpression;
}

void CHTLJSParser::ConditionalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalExpression(this);
}

void CHTLJSParser::ConditionalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalExpression(this);
}

CHTLJSParser::ConditionalExpressionContext* CHTLJSParser::conditionalExpression() {
  ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 74, CHTLJSParser::RuleConditionalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(492);
    logicalORExpression();
    setState(498);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::QUESTION) {
      setState(493);
      match(CHTLJSParser::QUESTION);
      setState(494);
      assignmentExpression();
      setState(495);
      match(CHTLJSParser::COLON);
      setState(496);
      assignmentExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalORExpressionContext ------------------------------------------------------------------

CHTLJSParser::LogicalORExpressionContext::LogicalORExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::LogicalANDExpressionContext *> CHTLJSParser::LogicalORExpressionContext::logicalANDExpression() {
  return getRuleContexts<CHTLJSParser::LogicalANDExpressionContext>();
}

CHTLJSParser::LogicalANDExpressionContext* CHTLJSParser::LogicalORExpressionContext::logicalANDExpression(size_t i) {
  return getRuleContext<CHTLJSParser::LogicalANDExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::LogicalORExpressionContext::OR() {
  return getTokens(CHTLJSParser::OR);
}

tree::TerminalNode* CHTLJSParser::LogicalORExpressionContext::OR(size_t i) {
  return getToken(CHTLJSParser::OR, i);
}


size_t CHTLJSParser::LogicalORExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleLogicalORExpression;
}

void CHTLJSParser::LogicalORExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalORExpression(this);
}

void CHTLJSParser::LogicalORExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalORExpression(this);
}

CHTLJSParser::LogicalORExpressionContext* CHTLJSParser::logicalORExpression() {
  LogicalORExpressionContext *_localctx = _tracker.createInstance<LogicalORExpressionContext>(_ctx, getState());
  enterRule(_localctx, 76, CHTLJSParser::RuleLogicalORExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(500);
    logicalANDExpression();
    setState(505);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::OR) {
      setState(501);
      match(CHTLJSParser::OR);
      setState(502);
      logicalANDExpression();
      setState(507);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalANDExpressionContext ------------------------------------------------------------------

CHTLJSParser::LogicalANDExpressionContext::LogicalANDExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::BitwiseORExpressionContext *> CHTLJSParser::LogicalANDExpressionContext::bitwiseORExpression() {
  return getRuleContexts<CHTLJSParser::BitwiseORExpressionContext>();
}

CHTLJSParser::BitwiseORExpressionContext* CHTLJSParser::LogicalANDExpressionContext::bitwiseORExpression(size_t i) {
  return getRuleContext<CHTLJSParser::BitwiseORExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::LogicalANDExpressionContext::AND() {
  return getTokens(CHTLJSParser::AND);
}

tree::TerminalNode* CHTLJSParser::LogicalANDExpressionContext::AND(size_t i) {
  return getToken(CHTLJSParser::AND, i);
}


size_t CHTLJSParser::LogicalANDExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleLogicalANDExpression;
}

void CHTLJSParser::LogicalANDExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalANDExpression(this);
}

void CHTLJSParser::LogicalANDExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalANDExpression(this);
}

CHTLJSParser::LogicalANDExpressionContext* CHTLJSParser::logicalANDExpression() {
  LogicalANDExpressionContext *_localctx = _tracker.createInstance<LogicalANDExpressionContext>(_ctx, getState());
  enterRule(_localctx, 78, CHTLJSParser::RuleLogicalANDExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(508);
    bitwiseORExpression();
    setState(513);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::AND) {
      setState(509);
      match(CHTLJSParser::AND);
      setState(510);
      bitwiseORExpression();
      setState(515);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseORExpressionContext ------------------------------------------------------------------

CHTLJSParser::BitwiseORExpressionContext::BitwiseORExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::BitwiseXORExpressionContext *> CHTLJSParser::BitwiseORExpressionContext::bitwiseXORExpression() {
  return getRuleContexts<CHTLJSParser::BitwiseXORExpressionContext>();
}

CHTLJSParser::BitwiseXORExpressionContext* CHTLJSParser::BitwiseORExpressionContext::bitwiseXORExpression(size_t i) {
  return getRuleContext<CHTLJSParser::BitwiseXORExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::BitwiseORExpressionContext::BITOR() {
  return getTokens(CHTLJSParser::BITOR);
}

tree::TerminalNode* CHTLJSParser::BitwiseORExpressionContext::BITOR(size_t i) {
  return getToken(CHTLJSParser::BITOR, i);
}


size_t CHTLJSParser::BitwiseORExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleBitwiseORExpression;
}

void CHTLJSParser::BitwiseORExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseORExpression(this);
}

void CHTLJSParser::BitwiseORExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseORExpression(this);
}

CHTLJSParser::BitwiseORExpressionContext* CHTLJSParser::bitwiseORExpression() {
  BitwiseORExpressionContext *_localctx = _tracker.createInstance<BitwiseORExpressionContext>(_ctx, getState());
  enterRule(_localctx, 80, CHTLJSParser::RuleBitwiseORExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(516);
    bitwiseXORExpression();
    setState(521);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::BITOR) {
      setState(517);
      match(CHTLJSParser::BITOR);
      setState(518);
      bitwiseXORExpression();
      setState(523);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseXORExpressionContext ------------------------------------------------------------------

CHTLJSParser::BitwiseXORExpressionContext::BitwiseXORExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::BitwiseANDExpressionContext *> CHTLJSParser::BitwiseXORExpressionContext::bitwiseANDExpression() {
  return getRuleContexts<CHTLJSParser::BitwiseANDExpressionContext>();
}

CHTLJSParser::BitwiseANDExpressionContext* CHTLJSParser::BitwiseXORExpressionContext::bitwiseANDExpression(size_t i) {
  return getRuleContext<CHTLJSParser::BitwiseANDExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::BitwiseXORExpressionContext::CARET() {
  return getTokens(CHTLJSParser::CARET);
}

tree::TerminalNode* CHTLJSParser::BitwiseXORExpressionContext::CARET(size_t i) {
  return getToken(CHTLJSParser::CARET, i);
}


size_t CHTLJSParser::BitwiseXORExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleBitwiseXORExpression;
}

void CHTLJSParser::BitwiseXORExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseXORExpression(this);
}

void CHTLJSParser::BitwiseXORExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseXORExpression(this);
}

CHTLJSParser::BitwiseXORExpressionContext* CHTLJSParser::bitwiseXORExpression() {
  BitwiseXORExpressionContext *_localctx = _tracker.createInstance<BitwiseXORExpressionContext>(_ctx, getState());
  enterRule(_localctx, 82, CHTLJSParser::RuleBitwiseXORExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(524);
    bitwiseANDExpression();
    setState(529);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::CARET) {
      setState(525);
      match(CHTLJSParser::CARET);
      setState(526);
      bitwiseANDExpression();
      setState(531);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BitwiseANDExpressionContext ------------------------------------------------------------------

CHTLJSParser::BitwiseANDExpressionContext::BitwiseANDExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::EqualityExpressionContext *> CHTLJSParser::BitwiseANDExpressionContext::equalityExpression() {
  return getRuleContexts<CHTLJSParser::EqualityExpressionContext>();
}

CHTLJSParser::EqualityExpressionContext* CHTLJSParser::BitwiseANDExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<CHTLJSParser::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::BitwiseANDExpressionContext::BITAND() {
  return getTokens(CHTLJSParser::BITAND);
}

tree::TerminalNode* CHTLJSParser::BitwiseANDExpressionContext::BITAND(size_t i) {
  return getToken(CHTLJSParser::BITAND, i);
}


size_t CHTLJSParser::BitwiseANDExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleBitwiseANDExpression;
}

void CHTLJSParser::BitwiseANDExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitwiseANDExpression(this);
}

void CHTLJSParser::BitwiseANDExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitwiseANDExpression(this);
}

CHTLJSParser::BitwiseANDExpressionContext* CHTLJSParser::bitwiseANDExpression() {
  BitwiseANDExpressionContext *_localctx = _tracker.createInstance<BitwiseANDExpressionContext>(_ctx, getState());
  enterRule(_localctx, 84, CHTLJSParser::RuleBitwiseANDExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(532);
    equalityExpression();
    setState(537);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::BITAND) {
      setState(533);
      match(CHTLJSParser::BITAND);
      setState(534);
      equalityExpression();
      setState(539);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

CHTLJSParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::RelationalExpressionContext *> CHTLJSParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<CHTLJSParser::RelationalExpressionContext>();
}

CHTLJSParser::RelationalExpressionContext* CHTLJSParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<CHTLJSParser::RelationalExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::EqualityExpressionContext::EQUAL() {
  return getTokens(CHTLJSParser::EQUAL);
}

tree::TerminalNode* CHTLJSParser::EqualityExpressionContext::EQUAL(size_t i) {
  return getToken(CHTLJSParser::EQUAL, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::EqualityExpressionContext::NOTEQUAL() {
  return getTokens(CHTLJSParser::NOTEQUAL);
}

tree::TerminalNode* CHTLJSParser::EqualityExpressionContext::NOTEQUAL(size_t i) {
  return getToken(CHTLJSParser::NOTEQUAL, i);
}


size_t CHTLJSParser::EqualityExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleEqualityExpression;
}

void CHTLJSParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void CHTLJSParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}

CHTLJSParser::EqualityExpressionContext* CHTLJSParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 86, CHTLJSParser::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(540);
    relationalExpression();
    setState(545);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::EQUAL

    || _la == CHTLJSParser::NOTEQUAL) {
      setState(541);
      _la = _input->LA(1);
      if (!(_la == CHTLJSParser::EQUAL

      || _la == CHTLJSParser::NOTEQUAL)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(542);
      relationalExpression();
      setState(547);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

CHTLJSParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::ShiftExpressionContext *> CHTLJSParser::RelationalExpressionContext::shiftExpression() {
  return getRuleContexts<CHTLJSParser::ShiftExpressionContext>();
}

CHTLJSParser::ShiftExpressionContext* CHTLJSParser::RelationalExpressionContext::shiftExpression(size_t i) {
  return getRuleContext<CHTLJSParser::ShiftExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::RelationalExpressionContext::LT() {
  return getTokens(CHTLJSParser::LT);
}

tree::TerminalNode* CHTLJSParser::RelationalExpressionContext::LT(size_t i) {
  return getToken(CHTLJSParser::LT, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::RelationalExpressionContext::GT() {
  return getTokens(CHTLJSParser::GT);
}

tree::TerminalNode* CHTLJSParser::RelationalExpressionContext::GT(size_t i) {
  return getToken(CHTLJSParser::GT, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::RelationalExpressionContext::LE() {
  return getTokens(CHTLJSParser::LE);
}

tree::TerminalNode* CHTLJSParser::RelationalExpressionContext::LE(size_t i) {
  return getToken(CHTLJSParser::LE, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::RelationalExpressionContext::GE() {
  return getTokens(CHTLJSParser::GE);
}

tree::TerminalNode* CHTLJSParser::RelationalExpressionContext::GE(size_t i) {
  return getToken(CHTLJSParser::GE, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::RelationalExpressionContext::INSTANCEOF() {
  return getTokens(CHTLJSParser::INSTANCEOF);
}

tree::TerminalNode* CHTLJSParser::RelationalExpressionContext::INSTANCEOF(size_t i) {
  return getToken(CHTLJSParser::INSTANCEOF, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::RelationalExpressionContext::IN() {
  return getTokens(CHTLJSParser::IN);
}

tree::TerminalNode* CHTLJSParser::RelationalExpressionContext::IN(size_t i) {
  return getToken(CHTLJSParser::IN, i);
}


size_t CHTLJSParser::RelationalExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleRelationalExpression;
}

void CHTLJSParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void CHTLJSParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}

CHTLJSParser::RelationalExpressionContext* CHTLJSParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 88, CHTLJSParser::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(548);
    shiftExpression();
    setState(553);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 54) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 54)) & ((1ULL << (CHTLJSParser::IN - 54))
      | (1ULL << (CHTLJSParser::INSTANCEOF - 54))
      | (1ULL << (CHTLJSParser::GT - 54))
      | (1ULL << (CHTLJSParser::LT - 54))
      | (1ULL << (CHTLJSParser::GE - 54))
      | (1ULL << (CHTLJSParser::LE - 54)))) != 0)) {
      setState(549);
      _la = _input->LA(1);
      if (!(((((_la - 54) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 54)) & ((1ULL << (CHTLJSParser::IN - 54))
        | (1ULL << (CHTLJSParser::INSTANCEOF - 54))
        | (1ULL << (CHTLJSParser::GT - 54))
        | (1ULL << (CHTLJSParser::LT - 54))
        | (1ULL << (CHTLJSParser::GE - 54))
        | (1ULL << (CHTLJSParser::LE - 54)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(550);
      shiftExpression();
      setState(555);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftExpressionContext ------------------------------------------------------------------

CHTLJSParser::ShiftExpressionContext::ShiftExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::AdditiveExpressionContext *> CHTLJSParser::ShiftExpressionContext::additiveExpression() {
  return getRuleContexts<CHTLJSParser::AdditiveExpressionContext>();
}

CHTLJSParser::AdditiveExpressionContext* CHTLJSParser::ShiftExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<CHTLJSParser::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ShiftExpressionContext::LSHIFT() {
  return getTokens(CHTLJSParser::LSHIFT);
}

tree::TerminalNode* CHTLJSParser::ShiftExpressionContext::LSHIFT(size_t i) {
  return getToken(CHTLJSParser::LSHIFT, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ShiftExpressionContext::RSHIFT() {
  return getTokens(CHTLJSParser::RSHIFT);
}

tree::TerminalNode* CHTLJSParser::ShiftExpressionContext::RSHIFT(size_t i) {
  return getToken(CHTLJSParser::RSHIFT, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ShiftExpressionContext::URSHIFT() {
  return getTokens(CHTLJSParser::URSHIFT);
}

tree::TerminalNode* CHTLJSParser::ShiftExpressionContext::URSHIFT(size_t i) {
  return getToken(CHTLJSParser::URSHIFT, i);
}


size_t CHTLJSParser::ShiftExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleShiftExpression;
}

void CHTLJSParser::ShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpression(this);
}

void CHTLJSParser::ShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpression(this);
}

CHTLJSParser::ShiftExpressionContext* CHTLJSParser::shiftExpression() {
  ShiftExpressionContext *_localctx = _tracker.createInstance<ShiftExpressionContext>(_ctx, getState());
  enterRule(_localctx, 90, CHTLJSParser::RuleShiftExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(556);
    additiveExpression();
    setState(561);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 105) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 105)) & ((1ULL << (CHTLJSParser::LSHIFT - 105))
      | (1ULL << (CHTLJSParser::RSHIFT - 105))
      | (1ULL << (CHTLJSParser::URSHIFT - 105)))) != 0)) {
      setState(557);
      _la = _input->LA(1);
      if (!(((((_la - 105) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 105)) & ((1ULL << (CHTLJSParser::LSHIFT - 105))
        | (1ULL << (CHTLJSParser::RSHIFT - 105))
        | (1ULL << (CHTLJSParser::URSHIFT - 105)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(558);
      additiveExpression();
      setState(563);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

CHTLJSParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::MultiplicativeExpressionContext* CHTLJSParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContext<CHTLJSParser::MultiplicativeExpressionContext>(0);
}

std::vector<CHTLJSParser::AdditiveExpressionContext *> CHTLJSParser::AdditiveExpressionContext::additiveExpression() {
  return getRuleContexts<CHTLJSParser::AdditiveExpressionContext>();
}

CHTLJSParser::AdditiveExpressionContext* CHTLJSParser::AdditiveExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<CHTLJSParser::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::AdditiveExpressionContext::ADD() {
  return getTokens(CHTLJSParser::ADD);
}

tree::TerminalNode* CHTLJSParser::AdditiveExpressionContext::ADD(size_t i) {
  return getToken(CHTLJSParser::ADD, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::AdditiveExpressionContext::SUB() {
  return getTokens(CHTLJSParser::SUB);
}

tree::TerminalNode* CHTLJSParser::AdditiveExpressionContext::SUB(size_t i) {
  return getToken(CHTLJSParser::SUB, i);
}


size_t CHTLJSParser::AdditiveExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleAdditiveExpression;
}

void CHTLJSParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void CHTLJSParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}

CHTLJSParser::AdditiveExpressionContext* CHTLJSParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 92, CHTLJSParser::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(564);
    multiplicativeExpression();
    setState(569);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(565);
        _la = _input->LA(1);
        if (!(_la == CHTLJSParser::ADD

        || _la == CHTLJSParser::SUB)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(566);
        additiveExpression(); 
      }
      setState(571);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

CHTLJSParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::UnaryExpressionContext *> CHTLJSParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<CHTLJSParser::UnaryExpressionContext>();
}

CHTLJSParser::UnaryExpressionContext* CHTLJSParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<CHTLJSParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::MultiplicativeExpressionContext::MUL() {
  return getTokens(CHTLJSParser::MUL);
}

tree::TerminalNode* CHTLJSParser::MultiplicativeExpressionContext::MUL(size_t i) {
  return getToken(CHTLJSParser::MUL, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::MultiplicativeExpressionContext::DIV() {
  return getTokens(CHTLJSParser::DIV);
}

tree::TerminalNode* CHTLJSParser::MultiplicativeExpressionContext::DIV(size_t i) {
  return getToken(CHTLJSParser::DIV, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::MultiplicativeExpressionContext::MOD() {
  return getTokens(CHTLJSParser::MOD);
}

tree::TerminalNode* CHTLJSParser::MultiplicativeExpressionContext::MOD(size_t i) {
  return getToken(CHTLJSParser::MOD, i);
}


size_t CHTLJSParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleMultiplicativeExpression;
}

void CHTLJSParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void CHTLJSParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}

CHTLJSParser::MultiplicativeExpressionContext* CHTLJSParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 94, CHTLJSParser::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(572);
    unaryExpression();
    setState(577);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (CHTLJSParser::MUL - 82))
      | (1ULL << (CHTLJSParser::DIV - 82))
      | (1ULL << (CHTLJSParser::MOD - 82)))) != 0)) {
      setState(573);
      _la = _input->LA(1);
      if (!(((((_la - 82) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 82)) & ((1ULL << (CHTLJSParser::MUL - 82))
        | (1ULL << (CHTLJSParser::DIV - 82))
        | (1ULL << (CHTLJSParser::MOD - 82)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(574);
      unaryExpression();
      setState(579);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

CHTLJSParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::UnaryOperatorContext* CHTLJSParser::UnaryExpressionContext::unaryOperator() {
  return getRuleContext<CHTLJSParser::UnaryOperatorContext>(0);
}

CHTLJSParser::UnaryExpressionContext* CHTLJSParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<CHTLJSParser::UnaryExpressionContext>(0);
}

CHTLJSParser::PostfixExpressionContext* CHTLJSParser::UnaryExpressionContext::postfixExpression() {
  return getRuleContext<CHTLJSParser::PostfixExpressionContext>(0);
}


size_t CHTLJSParser::UnaryExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleUnaryExpression;
}

void CHTLJSParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void CHTLJSParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}

CHTLJSParser::UnaryExpressionContext* CHTLJSParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 96, CHTLJSParser::RuleUnaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(584);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLJSParser::TYPEOF:
      case CHTLJSParser::DELETE:
      case CHTLJSParser::VOID:
      case CHTLJSParser::BANG:
      case CHTLJSParser::TILDE:
      case CHTLJSParser::INC:
      case CHTLJSParser::DEC:
      case CHTLJSParser::ADD:
      case CHTLJSParser::SUB: {
        enterOuterAlt(_localctx, 1);
        setState(580);
        unaryOperator();
        setState(581);
        unaryExpression();
        break;
      }

      case CHTLJSParser::FUNCTION:
      case CHTLJSParser::NEW:
      case CHTLJSParser::THIS:
      case CHTLJSParser::SUPER:
      case CHTLJSParser::CLASS:
      case CHTLJSParser::IDENTIFIER:
      case CHTLJSParser::LBRACE:
      case CHTLJSParser::LPAREN:
      case CHTLJSParser::LBRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(583);
        postfixExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOperatorContext ------------------------------------------------------------------

CHTLJSParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::DELETE() {
  return getToken(CHTLJSParser::DELETE, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::VOID() {
  return getToken(CHTLJSParser::VOID, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::TYPEOF() {
  return getToken(CHTLJSParser::TYPEOF, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::INC() {
  return getToken(CHTLJSParser::INC, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::DEC() {
  return getToken(CHTLJSParser::DEC, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::ADD() {
  return getToken(CHTLJSParser::ADD, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::SUB() {
  return getToken(CHTLJSParser::SUB, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::BANG() {
  return getToken(CHTLJSParser::BANG, 0);
}

tree::TerminalNode* CHTLJSParser::UnaryOperatorContext::TILDE() {
  return getToken(CHTLJSParser::TILDE, 0);
}


size_t CHTLJSParser::UnaryOperatorContext::getRuleIndex() const {
  return CHTLJSParser::RuleUnaryOperator;
}

void CHTLJSParser::UnaryOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOperator(this);
}

void CHTLJSParser::UnaryOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOperator(this);
}

CHTLJSParser::UnaryOperatorContext* CHTLJSParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 98, CHTLJSParser::RuleUnaryOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(586);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 94) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 94)) & ((1ULL << (CHTLJSParser::BANG - 94))
      | (1ULL << (CHTLJSParser::TILDE - 94))
      | (1ULL << (CHTLJSParser::INC - 94))
      | (1ULL << (CHTLJSParser::DEC - 94))
      | (1ULL << (CHTLJSParser::ADD - 94))
      | (1ULL << (CHTLJSParser::SUB - 94)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExpressionContext ------------------------------------------------------------------

CHTLJSParser::PostfixExpressionContext::PostfixExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::LeftHandSideExpressionContext* CHTLJSParser::PostfixExpressionContext::leftHandSideExpression() {
  return getRuleContext<CHTLJSParser::LeftHandSideExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::PostfixExpressionContext::INC() {
  return getToken(CHTLJSParser::INC, 0);
}

tree::TerminalNode* CHTLJSParser::PostfixExpressionContext::DEC() {
  return getToken(CHTLJSParser::DEC, 0);
}


size_t CHTLJSParser::PostfixExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RulePostfixExpression;
}

void CHTLJSParser::PostfixExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostfixExpression(this);
}

void CHTLJSParser::PostfixExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostfixExpression(this);
}

CHTLJSParser::PostfixExpressionContext* CHTLJSParser::postfixExpression() {
  PostfixExpressionContext *_localctx = _tracker.createInstance<PostfixExpressionContext>(_ctx, getState());
  enterRule(_localctx, 100, CHTLJSParser::RulePostfixExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(588);
    leftHandSideExpression();
    setState(590);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::INC

    || _la == CHTLJSParser::DEC) {
      setState(589);
      _la = _input->LA(1);
      if (!(_la == CHTLJSParser::INC

      || _la == CHTLJSParser::DEC)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LeftHandSideExpressionContext ------------------------------------------------------------------

CHTLJSParser::LeftHandSideExpressionContext::LeftHandSideExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::CallExpressionContext* CHTLJSParser::LeftHandSideExpressionContext::callExpression() {
  return getRuleContext<CHTLJSParser::CallExpressionContext>(0);
}

CHTLJSParser::NewExpressionContext* CHTLJSParser::LeftHandSideExpressionContext::newExpression() {
  return getRuleContext<CHTLJSParser::NewExpressionContext>(0);
}


size_t CHTLJSParser::LeftHandSideExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleLeftHandSideExpression;
}

void CHTLJSParser::LeftHandSideExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLeftHandSideExpression(this);
}

void CHTLJSParser::LeftHandSideExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLeftHandSideExpression(this);
}

CHTLJSParser::LeftHandSideExpressionContext* CHTLJSParser::leftHandSideExpression() {
  LeftHandSideExpressionContext *_localctx = _tracker.createInstance<LeftHandSideExpressionContext>(_ctx, getState());
  enterRule(_localctx, 102, CHTLJSParser::RuleLeftHandSideExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(594);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(592);
      callExpression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(593);
      newExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallExpressionContext ------------------------------------------------------------------

CHTLJSParser::CallExpressionContext::CallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::SuperPropertyContext* CHTLJSParser::CallExpressionContext::superProperty() {
  return getRuleContext<CHTLJSParser::SuperPropertyContext>(0);
}

CHTLJSParser::FunctionExpressionContext* CHTLJSParser::CallExpressionContext::functionExpression() {
  return getRuleContext<CHTLJSParser::FunctionExpressionContext>(0);
}

CHTLJSParser::ClassExpressionContext* CHTLJSParser::CallExpressionContext::classExpression() {
  return getRuleContext<CHTLJSParser::ClassExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::CallExpressionContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

CHTLJSParser::ThisExpressionContext* CHTLJSParser::CallExpressionContext::thisExpression() {
  return getRuleContext<CHTLJSParser::ThisExpressionContext>(0);
}

CHTLJSParser::ArrayLiteralContext* CHTLJSParser::CallExpressionContext::arrayLiteral() {
  return getRuleContext<CHTLJSParser::ArrayLiteralContext>(0);
}

CHTLJSParser::ObjectLiteralContext* CHTLJSParser::CallExpressionContext::objectLiteral() {
  return getRuleContext<CHTLJSParser::ObjectLiteralContext>(0);
}

CHTLJSParser::ParenthesizedExpressionContext* CHTLJSParser::CallExpressionContext::parenthesizedExpression() {
  return getRuleContext<CHTLJSParser::ParenthesizedExpressionContext>(0);
}

CHTLJSParser::NewExpressionContext* CHTLJSParser::CallExpressionContext::newExpression() {
  return getRuleContext<CHTLJSParser::NewExpressionContext>(0);
}

CHTLJSParser::CallExpressionContext* CHTLJSParser::CallExpressionContext::callExpression() {
  return getRuleContext<CHTLJSParser::CallExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::CallExpressionContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::CallExpressionContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

CHTLJSParser::ArgumentsContext* CHTLJSParser::CallExpressionContext::arguments() {
  return getRuleContext<CHTLJSParser::ArgumentsContext>(0);
}

tree::TerminalNode* CHTLJSParser::CallExpressionContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::CallExpressionContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::CallExpressionContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}

tree::TerminalNode* CHTLJSParser::CallExpressionContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}


size_t CHTLJSParser::CallExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleCallExpression;
}

void CHTLJSParser::CallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallExpression(this);
}

void CHTLJSParser::CallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallExpression(this);
}


CHTLJSParser::CallExpressionContext* CHTLJSParser::callExpression() {
   return callExpression(0);
}

CHTLJSParser::CallExpressionContext* CHTLJSParser::callExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CHTLJSParser::CallExpressionContext *_localctx = _tracker.createInstance<CallExpressionContext>(_ctx, parentState);
  CHTLJSParser::CallExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 104;
  enterRecursionRule(_localctx, 104, CHTLJSParser::RuleCallExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(606);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      setState(597);
      superProperty();
      break;
    }

    case 2: {
      setState(598);
      functionExpression();
      break;
    }

    case 3: {
      setState(599);
      classExpression();
      break;
    }

    case 4: {
      setState(600);
      match(CHTLJSParser::IDENTIFIER);
      break;
    }

    case 5: {
      setState(601);
      thisExpression();
      break;
    }

    case 6: {
      setState(602);
      arrayLiteral();
      break;
    }

    case 7: {
      setState(603);
      objectLiteral();
      break;
    }

    case 8: {
      setState(604);
      parenthesizedExpression();
      break;
    }

    case 9: {
      setState(605);
      newExpression();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(624);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(622);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<CallExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCallExpression);
          setState(608);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(609);
          match(CHTLJSParser::LPAREN);
          setState(611);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
            | (1ULL << CHTLJSParser::NEW)
            | (1ULL << CHTLJSParser::THIS)
            | (1ULL << CHTLJSParser::SUPER)
            | (1ULL << CHTLJSParser::CLASS)
            | (1ULL << CHTLJSParser::TYPEOF)
            | (1ULL << CHTLJSParser::DELETE)
            | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
            | (1ULL << (CHTLJSParser::LBRACE - 69))
            | (1ULL << (CHTLJSParser::LPAREN - 69))
            | (1ULL << (CHTLJSParser::LBRACKET - 69))
            | (1ULL << (CHTLJSParser::ASSIGN - 69))
            | (1ULL << (CHTLJSParser::BANG - 69))
            | (1ULL << (CHTLJSParser::TILDE - 69))
            | (1ULL << (CHTLJSParser::INC - 69))
            | (1ULL << (CHTLJSParser::DEC - 69))
            | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::ADD - 69))
            | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
            setState(610);
            arguments();
          }
          setState(613);
          match(CHTLJSParser::RPAREN);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<CallExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCallExpression);
          setState(614);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(615);
          match(CHTLJSParser::LBRACKET);
          setState(616);
          expression();
          setState(617);
          match(CHTLJSParser::RBRACKET);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<CallExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCallExpression);
          setState(619);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(620);
          match(CHTLJSParser::DOT);
          setState(621);
          match(CHTLJSParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(626);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

CHTLJSParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ArgumentListContext* CHTLJSParser::ArgumentsContext::argumentList() {
  return getRuleContext<CHTLJSParser::ArgumentListContext>(0);
}


size_t CHTLJSParser::ArgumentsContext::getRuleIndex() const {
  return CHTLJSParser::RuleArguments;
}

void CHTLJSParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void CHTLJSParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}

CHTLJSParser::ArgumentsContext* CHTLJSParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 106, CHTLJSParser::RuleArguments);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(627);
    argumentList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

CHTLJSParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::AssignmentExpressionContext *> CHTLJSParser::ArgumentListContext::assignmentExpression() {
  return getRuleContexts<CHTLJSParser::AssignmentExpressionContext>();
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::ArgumentListContext::assignmentExpression(size_t i) {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ArgumentListContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ArgumentListContext::getRuleIndex() const {
  return CHTLJSParser::RuleArgumentList;
}

void CHTLJSParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void CHTLJSParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}

CHTLJSParser::ArgumentListContext* CHTLJSParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 108, CHTLJSParser::RuleArgumentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(629);
    assignmentExpression();
    setState(634);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(630);
      match(CHTLJSParser::COMMA);
      setState(631);
      assignmentExpression();
      setState(636);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NewExpressionContext ------------------------------------------------------------------

CHTLJSParser::NewExpressionContext::NewExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::NewExpressionContext::NEW() {
  return getToken(CHTLJSParser::NEW, 0);
}

CHTLJSParser::NewExpressionContext* CHTLJSParser::NewExpressionContext::newExpression() {
  return getRuleContext<CHTLJSParser::NewExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::NewExpressionContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::NewExpressionContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

CHTLJSParser::ArgumentsContext* CHTLJSParser::NewExpressionContext::arguments() {
  return getRuleContext<CHTLJSParser::ArgumentsContext>(0);
}

tree::TerminalNode* CHTLJSParser::NewExpressionContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::NewExpressionContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::NewExpressionContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}

tree::TerminalNode* CHTLJSParser::NewExpressionContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}

tree::TerminalNode* CHTLJSParser::NewExpressionContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

CHTLJSParser::SuperPropertyContext* CHTLJSParser::NewExpressionContext::superProperty() {
  return getRuleContext<CHTLJSParser::SuperPropertyContext>(0);
}

CHTLJSParser::FunctionExpressionContext* CHTLJSParser::NewExpressionContext::functionExpression() {
  return getRuleContext<CHTLJSParser::FunctionExpressionContext>(0);
}

CHTLJSParser::ClassExpressionContext* CHTLJSParser::NewExpressionContext::classExpression() {
  return getRuleContext<CHTLJSParser::ClassExpressionContext>(0);
}

CHTLJSParser::ThisExpressionContext* CHTLJSParser::NewExpressionContext::thisExpression() {
  return getRuleContext<CHTLJSParser::ThisExpressionContext>(0);
}

CHTLJSParser::ArrayLiteralContext* CHTLJSParser::NewExpressionContext::arrayLiteral() {
  return getRuleContext<CHTLJSParser::ArrayLiteralContext>(0);
}

CHTLJSParser::ObjectLiteralContext* CHTLJSParser::NewExpressionContext::objectLiteral() {
  return getRuleContext<CHTLJSParser::ObjectLiteralContext>(0);
}

CHTLJSParser::ParenthesizedExpressionContext* CHTLJSParser::NewExpressionContext::parenthesizedExpression() {
  return getRuleContext<CHTLJSParser::ParenthesizedExpressionContext>(0);
}


size_t CHTLJSParser::NewExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleNewExpression;
}

void CHTLJSParser::NewExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewExpression(this);
}

void CHTLJSParser::NewExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewExpression(this);
}

CHTLJSParser::NewExpressionContext* CHTLJSParser::newExpression() {
  NewExpressionContext *_localctx = _tracker.createInstance<NewExpressionContext>(_ctx, getState());
  enterRule(_localctx, 110, CHTLJSParser::RuleNewExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(666);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(637);
      match(CHTLJSParser::NEW);
      setState(638);
      newExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(639);
      match(CHTLJSParser::NEW);
      setState(640);
      newExpression();
      setState(641);
      match(CHTLJSParser::LPAREN);
      setState(643);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
        | (1ULL << CHTLJSParser::NEW)
        | (1ULL << CHTLJSParser::THIS)
        | (1ULL << CHTLJSParser::SUPER)
        | (1ULL << CHTLJSParser::CLASS)
        | (1ULL << CHTLJSParser::TYPEOF)
        | (1ULL << CHTLJSParser::DELETE)
        | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
        | (1ULL << (CHTLJSParser::LBRACE - 69))
        | (1ULL << (CHTLJSParser::LPAREN - 69))
        | (1ULL << (CHTLJSParser::LBRACKET - 69))
        | (1ULL << (CHTLJSParser::ASSIGN - 69))
        | (1ULL << (CHTLJSParser::BANG - 69))
        | (1ULL << (CHTLJSParser::TILDE - 69))
        | (1ULL << (CHTLJSParser::INC - 69))
        | (1ULL << (CHTLJSParser::DEC - 69))
        | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
        | (1ULL << (CHTLJSParser::ADD - 69))
        | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
        setState(642);
        arguments();
      }
      setState(645);
      match(CHTLJSParser::RPAREN);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(647);
      match(CHTLJSParser::NEW);
      setState(648);
      newExpression();
      setState(649);
      match(CHTLJSParser::LBRACKET);
      setState(650);
      expression();
      setState(651);
      match(CHTLJSParser::RBRACKET);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(653);
      match(CHTLJSParser::NEW);
      setState(654);
      newExpression();
      setState(655);
      match(CHTLJSParser::DOT);
      setState(656);
      match(CHTLJSParser::IDENTIFIER);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(658);
      superProperty();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(659);
      functionExpression();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(660);
      classExpression();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(661);
      match(CHTLJSParser::IDENTIFIER);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(662);
      thisExpression();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(663);
      arrayLiteral();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(664);
      objectLiteral();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(665);
      parenthesizedExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SuperPropertyContext ------------------------------------------------------------------

CHTLJSParser::SuperPropertyContext::SuperPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::SuperPropertyContext::SUPER() {
  return getToken(CHTLJSParser::SUPER, 0);
}

tree::TerminalNode* CHTLJSParser::SuperPropertyContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::SuperPropertyContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::SuperPropertyContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}

tree::TerminalNode* CHTLJSParser::SuperPropertyContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}

tree::TerminalNode* CHTLJSParser::SuperPropertyContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}


size_t CHTLJSParser::SuperPropertyContext::getRuleIndex() const {
  return CHTLJSParser::RuleSuperProperty;
}

void CHTLJSParser::SuperPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSuperProperty(this);
}

void CHTLJSParser::SuperPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSuperProperty(this);
}

CHTLJSParser::SuperPropertyContext* CHTLJSParser::superProperty() {
  SuperPropertyContext *_localctx = _tracker.createInstance<SuperPropertyContext>(_ctx, getState());
  enterRule(_localctx, 112, CHTLJSParser::RuleSuperProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(676);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(668);
      match(CHTLJSParser::SUPER);
      setState(669);
      match(CHTLJSParser::LBRACKET);
      setState(670);
      expression();
      setState(671);
      match(CHTLJSParser::RBRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(673);
      match(CHTLJSParser::SUPER);
      setState(674);
      match(CHTLJSParser::DOT);
      setState(675);
      match(CHTLJSParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionExpressionContext ------------------------------------------------------------------

CHTLJSParser::FunctionExpressionContext::FunctionExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::FunctionExpressionContext::FUNCTION() {
  return getToken(CHTLJSParser::FUNCTION, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionExpressionContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionExpressionContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionExpressionContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::FunctionBodyContext* CHTLJSParser::FunctionExpressionContext::functionBody() {
  return getRuleContext<CHTLJSParser::FunctionBodyContext>(0);
}

tree::TerminalNode* CHTLJSParser::FunctionExpressionContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionExpressionContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

CHTLJSParser::FormalParameterListContext* CHTLJSParser::FunctionExpressionContext::formalParameterList() {
  return getRuleContext<CHTLJSParser::FormalParameterListContext>(0);
}


size_t CHTLJSParser::FunctionExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleFunctionExpression;
}

void CHTLJSParser::FunctionExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionExpression(this);
}

void CHTLJSParser::FunctionExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionExpression(this);
}

CHTLJSParser::FunctionExpressionContext* CHTLJSParser::functionExpression() {
  FunctionExpressionContext *_localctx = _tracker.createInstance<FunctionExpressionContext>(_ctx, getState());
  enterRule(_localctx, 114, CHTLJSParser::RuleFunctionExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(678);
    match(CHTLJSParser::FUNCTION);
    setState(680);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::IDENTIFIER) {
      setState(679);
      match(CHTLJSParser::IDENTIFIER);
    }
    setState(682);
    match(CHTLJSParser::LPAREN);
    setState(684);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::IDENTIFIER) {
      setState(683);
      formalParameterList();
    }
    setState(686);
    match(CHTLJSParser::RPAREN);
    setState(687);
    match(CHTLJSParser::LBRACE);
    setState(688);
    functionBody();
    setState(689);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassExpressionContext ------------------------------------------------------------------

CHTLJSParser::ClassExpressionContext::ClassExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ClassExpressionContext::CLASS() {
  return getToken(CHTLJSParser::CLASS, 0);
}

tree::TerminalNode* CHTLJSParser::ClassExpressionContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

tree::TerminalNode* CHTLJSParser::ClassExpressionContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ClassExpressionContext::IDENTIFIER() {
  return getTokens(CHTLJSParser::IDENTIFIER);
}

tree::TerminalNode* CHTLJSParser::ClassExpressionContext::IDENTIFIER(size_t i) {
  return getToken(CHTLJSParser::IDENTIFIER, i);
}

tree::TerminalNode* CHTLJSParser::ClassExpressionContext::EXTENDS() {
  return getToken(CHTLJSParser::EXTENDS, 0);
}

CHTLJSParser::ClassBodyContext* CHTLJSParser::ClassExpressionContext::classBody() {
  return getRuleContext<CHTLJSParser::ClassBodyContext>(0);
}


size_t CHTLJSParser::ClassExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleClassExpression;
}

void CHTLJSParser::ClassExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassExpression(this);
}

void CHTLJSParser::ClassExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassExpression(this);
}

CHTLJSParser::ClassExpressionContext* CHTLJSParser::classExpression() {
  ClassExpressionContext *_localctx = _tracker.createInstance<ClassExpressionContext>(_ctx, getState());
  enterRule(_localctx, 116, CHTLJSParser::RuleClassExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(691);
    match(CHTLJSParser::CLASS);
    setState(693);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::IDENTIFIER) {
      setState(692);
      match(CHTLJSParser::IDENTIFIER);
    }
    setState(697);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::EXTENDS) {
      setState(695);
      match(CHTLJSParser::EXTENDS);
      setState(696);
      match(CHTLJSParser::IDENTIFIER);
    }
    setState(699);
    match(CHTLJSParser::LBRACE);
    setState(701);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 47) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 47)) & ((1ULL << (CHTLJSParser::GET - 47))
      | (1ULL << (CHTLJSParser::SET - 47))
      | (1ULL << (CHTLJSParser::IDENTIFIER - 47)))) != 0)) {
      setState(700);
      classBody();
    }
    setState(703);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ThisExpressionContext ------------------------------------------------------------------

CHTLJSParser::ThisExpressionContext::ThisExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ThisExpressionContext::THIS() {
  return getToken(CHTLJSParser::THIS, 0);
}


size_t CHTLJSParser::ThisExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleThisExpression;
}

void CHTLJSParser::ThisExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThisExpression(this);
}

void CHTLJSParser::ThisExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThisExpression(this);
}

CHTLJSParser::ThisExpressionContext* CHTLJSParser::thisExpression() {
  ThisExpressionContext *_localctx = _tracker.createInstance<ThisExpressionContext>(_ctx, getState());
  enterRule(_localctx, 118, CHTLJSParser::RuleThisExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(705);
    match(CHTLJSParser::THIS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLiteralContext ------------------------------------------------------------------

CHTLJSParser::ArrayLiteralContext::ArrayLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ArrayLiteralContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLJSParser::ArrayLiteralContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}

CHTLJSParser::ElementListContext* CHTLJSParser::ArrayLiteralContext::elementList() {
  return getRuleContext<CHTLJSParser::ElementListContext>(0);
}

tree::TerminalNode* CHTLJSParser::ArrayLiteralContext::COMMA() {
  return getToken(CHTLJSParser::COMMA, 0);
}


size_t CHTLJSParser::ArrayLiteralContext::getRuleIndex() const {
  return CHTLJSParser::RuleArrayLiteral;
}

void CHTLJSParser::ArrayLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayLiteral(this);
}

void CHTLJSParser::ArrayLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayLiteral(this);
}

CHTLJSParser::ArrayLiteralContext* CHTLJSParser::arrayLiteral() {
  ArrayLiteralContext *_localctx = _tracker.createInstance<ArrayLiteralContext>(_ctx, getState());
  enterRule(_localctx, 120, CHTLJSParser::RuleArrayLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(707);
    match(CHTLJSParser::LBRACKET);
    setState(712);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ELLIPSIS - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(708);
      elementList();
      setState(710);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::COMMA) {
        setState(709);
        match(CHTLJSParser::COMMA);
      }
    }
    setState(714);
    match(CHTLJSParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementListContext ------------------------------------------------------------------

CHTLJSParser::ElementListContext::ElementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::AssignmentExpressionContext *> CHTLJSParser::ElementListContext::assignmentExpression() {
  return getRuleContexts<CHTLJSParser::AssignmentExpressionContext>();
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::ElementListContext::assignmentExpression(size_t i) {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ElementListContext::ELLIPSIS() {
  return getTokens(CHTLJSParser::ELLIPSIS);
}

tree::TerminalNode* CHTLJSParser::ElementListContext::ELLIPSIS(size_t i) {
  return getToken(CHTLJSParser::ELLIPSIS, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ElementListContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ElementListContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ElementListContext::getRuleIndex() const {
  return CHTLJSParser::RuleElementList;
}

void CHTLJSParser::ElementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementList(this);
}

void CHTLJSParser::ElementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementList(this);
}

CHTLJSParser::ElementListContext* CHTLJSParser::elementList() {
  ElementListContext *_localctx = _tracker.createInstance<ElementListContext>(_ctx, getState());
  enterRule(_localctx, 122, CHTLJSParser::RuleElementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(717);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::ELLIPSIS) {
      setState(716);
      match(CHTLJSParser::ELLIPSIS);
    }
    setState(719);
    assignmentExpression();
    setState(727);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(720);
        match(CHTLJSParser::COMMA);
        setState(722);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CHTLJSParser::ELLIPSIS) {
          setState(721);
          match(CHTLJSParser::ELLIPSIS);
        }
        setState(724);
        assignmentExpression(); 
      }
      setState(729);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectLiteralContext ------------------------------------------------------------------

CHTLJSParser::ObjectLiteralContext::ObjectLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ObjectLiteralContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

tree::TerminalNode* CHTLJSParser::ObjectLiteralContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

std::vector<CHTLJSParser::PropertyDefinitionContext *> CHTLJSParser::ObjectLiteralContext::propertyDefinition() {
  return getRuleContexts<CHTLJSParser::PropertyDefinitionContext>();
}

CHTLJSParser::PropertyDefinitionContext* CHTLJSParser::ObjectLiteralContext::propertyDefinition(size_t i) {
  return getRuleContext<CHTLJSParser::PropertyDefinitionContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ObjectLiteralContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ObjectLiteralContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ObjectLiteralContext::getRuleIndex() const {
  return CHTLJSParser::RuleObjectLiteral;
}

void CHTLJSParser::ObjectLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectLiteral(this);
}

void CHTLJSParser::ObjectLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectLiteral(this);
}

CHTLJSParser::ObjectLiteralContext* CHTLJSParser::objectLiteral() {
  ObjectLiteralContext *_localctx = _tracker.createInstance<ObjectLiteralContext>(_ctx, getState());
  enterRule(_localctx, 124, CHTLJSParser::RuleObjectLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(730);
    match(CHTLJSParser::LBRACE);
    setState(739);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::GET)
      | (1ULL << CHTLJSParser::SET)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ELLIPSIS - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(731);
      propertyDefinition();
      setState(736);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CHTLJSParser::COMMA) {
        setState(732);
        match(CHTLJSParser::COMMA);
        setState(733);
        propertyDefinition();
        setState(738);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(741);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyDefinitionContext ------------------------------------------------------------------

CHTLJSParser::PropertyDefinitionContext::PropertyDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::PropertyDefinitionContext::assignmentExpression() {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::FunctionBodyContext* CHTLJSParser::PropertyDefinitionContext::functionBody() {
  return getRuleContext<CHTLJSParser::FunctionBodyContext>(0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}

CHTLJSParser::FormalParameterListContext* CHTLJSParser::PropertyDefinitionContext::formalParameterList() {
  return getRuleContext<CHTLJSParser::FormalParameterListContext>(0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::GET() {
  return getToken(CHTLJSParser::GET, 0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::SET() {
  return getToken(CHTLJSParser::SET, 0);
}

tree::TerminalNode* CHTLJSParser::PropertyDefinitionContext::ELLIPSIS() {
  return getToken(CHTLJSParser::ELLIPSIS, 0);
}


size_t CHTLJSParser::PropertyDefinitionContext::getRuleIndex() const {
  return CHTLJSParser::RulePropertyDefinition;
}

void CHTLJSParser::PropertyDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyDefinition(this);
}

void CHTLJSParser::PropertyDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyDefinition(this);
}

CHTLJSParser::PropertyDefinitionContext* CHTLJSParser::propertyDefinition() {
  PropertyDefinitionContext *_localctx = _tracker.createInstance<PropertyDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 126, CHTLJSParser::RulePropertyDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(763);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(743);
      match(CHTLJSParser::IDENTIFIER);
      setState(744);
      match(CHTLJSParser::COLON);
      setState(745);
      assignmentExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(747);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::GET

      || _la == CHTLJSParser::SET) {
        setState(746);
        _la = _input->LA(1);
        if (!(_la == CHTLJSParser::GET

        || _la == CHTLJSParser::SET)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(749);
      match(CHTLJSParser::IDENTIFIER);
      setState(750);
      match(CHTLJSParser::LPAREN);
      setState(752);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::IDENTIFIER) {
        setState(751);
        formalParameterList();
      }
      setState(754);
      match(CHTLJSParser::RPAREN);
      setState(755);
      match(CHTLJSParser::LBRACE);
      setState(756);
      functionBody();
      setState(757);
      match(CHTLJSParser::RBRACE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(760);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::ELLIPSIS) {
        setState(759);
        match(CHTLJSParser::ELLIPSIS);
      }
      setState(762);
      assignmentExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParenthesizedExpressionContext ------------------------------------------------------------------

CHTLJSParser::ParenthesizedExpressionContext::ParenthesizedExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ParenthesizedExpressionContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::ParenthesizedExpressionContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::ParenthesizedExpressionContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}


size_t CHTLJSParser::ParenthesizedExpressionContext::getRuleIndex() const {
  return CHTLJSParser::RuleParenthesizedExpression;
}

void CHTLJSParser::ParenthesizedExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesizedExpression(this);
}

void CHTLJSParser::ParenthesizedExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesizedExpression(this);
}

CHTLJSParser::ParenthesizedExpressionContext* CHTLJSParser::parenthesizedExpression() {
  ParenthesizedExpressionContext *_localctx = _tracker.createInstance<ParenthesizedExpressionContext>(_ctx, getState());
  enterRule(_localctx, 128, CHTLJSParser::RuleParenthesizedExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(765);
    match(CHTLJSParser::LPAREN);
    setState(766);
    expression();
    setState(767);
    match(CHTLJSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionContext ------------------------------------------------------------------

CHTLJSParser::ArrowFunctionContext::ArrowFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ArrowParametersContext* CHTLJSParser::ArrowFunctionContext::arrowParameters() {
  return getRuleContext<CHTLJSParser::ArrowParametersContext>(0);
}

tree::TerminalNode* CHTLJSParser::ArrowFunctionContext::ARROW() {
  return getToken(CHTLJSParser::ARROW, 0);
}

CHTLJSParser::ArrowFunctionBodyContext* CHTLJSParser::ArrowFunctionContext::arrowFunctionBody() {
  return getRuleContext<CHTLJSParser::ArrowFunctionBodyContext>(0);
}


size_t CHTLJSParser::ArrowFunctionContext::getRuleIndex() const {
  return CHTLJSParser::RuleArrowFunction;
}

void CHTLJSParser::ArrowFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunction(this);
}

void CHTLJSParser::ArrowFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunction(this);
}

CHTLJSParser::ArrowFunctionContext* CHTLJSParser::arrowFunction() {
  ArrowFunctionContext *_localctx = _tracker.createInstance<ArrowFunctionContext>(_ctx, getState());
  enterRule(_localctx, 130, CHTLJSParser::RuleArrowFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(769);
    arrowParameters();
    setState(770);
    match(CHTLJSParser::ARROW);
    setState(771);
    arrowFunctionBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowParametersContext ------------------------------------------------------------------

CHTLJSParser::ArrowParametersContext::ArrowParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ArrowParametersContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::ArrowParametersContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::ArrowParametersContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

CHTLJSParser::FormalParameterListContext* CHTLJSParser::ArrowParametersContext::formalParameterList() {
  return getRuleContext<CHTLJSParser::FormalParameterListContext>(0);
}


size_t CHTLJSParser::ArrowParametersContext::getRuleIndex() const {
  return CHTLJSParser::RuleArrowParameters;
}

void CHTLJSParser::ArrowParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowParameters(this);
}

void CHTLJSParser::ArrowParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowParameters(this);
}

CHTLJSParser::ArrowParametersContext* CHTLJSParser::arrowParameters() {
  ArrowParametersContext *_localctx = _tracker.createInstance<ArrowParametersContext>(_ctx, getState());
  enterRule(_localctx, 132, CHTLJSParser::RuleArrowParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(779);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLJSParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(773);
        match(CHTLJSParser::IDENTIFIER);
        break;
      }

      case CHTLJSParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(774);
        match(CHTLJSParser::LPAREN);
        setState(776);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CHTLJSParser::IDENTIFIER) {
          setState(775);
          formalParameterList();
        }
        setState(778);
        match(CHTLJSParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionBodyContext ------------------------------------------------------------------

CHTLJSParser::ArrowFunctionBodyContext::ArrowFunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::AssignmentExpressionContext* CHTLJSParser::ArrowFunctionBodyContext::assignmentExpression() {
  return getRuleContext<CHTLJSParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::ArrowFunctionBodyContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::FunctionBodyContext* CHTLJSParser::ArrowFunctionBodyContext::functionBody() {
  return getRuleContext<CHTLJSParser::FunctionBodyContext>(0);
}

tree::TerminalNode* CHTLJSParser::ArrowFunctionBodyContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}


size_t CHTLJSParser::ArrowFunctionBodyContext::getRuleIndex() const {
  return CHTLJSParser::RuleArrowFunctionBody;
}

void CHTLJSParser::ArrowFunctionBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunctionBody(this);
}

void CHTLJSParser::ArrowFunctionBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunctionBody(this);
}

CHTLJSParser::ArrowFunctionBodyContext* CHTLJSParser::arrowFunctionBody() {
  ArrowFunctionBodyContext *_localctx = _tracker.createInstance<ArrowFunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 134, CHTLJSParser::RuleArrowFunctionBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(786);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(781);
      assignmentExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(782);
      match(CHTLJSParser::LBRACE);
      setState(783);
      functionBody();
      setState(784);
      match(CHTLJSParser::RBRACE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlStatementContext ------------------------------------------------------------------

CHTLJSParser::ChtlStatementContext::ChtlStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ChtlSelectorStatementContext* CHTLJSParser::ChtlStatementContext::chtlSelectorStatement() {
  return getRuleContext<CHTLJSParser::ChtlSelectorStatementContext>(0);
}

CHTLJSParser::ChtlListenStatementContext* CHTLJSParser::ChtlStatementContext::chtlListenStatement() {
  return getRuleContext<CHTLJSParser::ChtlListenStatementContext>(0);
}

CHTLJSParser::ChtlDelegateStatementContext* CHTLJSParser::ChtlStatementContext::chtlDelegateStatement() {
  return getRuleContext<CHTLJSParser::ChtlDelegateStatementContext>(0);
}

CHTLJSParser::ChtlAnimateStatementContext* CHTLJSParser::ChtlStatementContext::chtlAnimateStatement() {
  return getRuleContext<CHTLJSParser::ChtlAnimateStatementContext>(0);
}


size_t CHTLJSParser::ChtlStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlStatement;
}

void CHTLJSParser::ChtlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlStatement(this);
}

void CHTLJSParser::ChtlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlStatement(this);
}

CHTLJSParser::ChtlStatementContext* CHTLJSParser::chtlStatement() {
  ChtlStatementContext *_localctx = _tracker.createInstance<ChtlStatementContext>(_ctx, getState());
  enterRule(_localctx, 136, CHTLJSParser::RuleChtlStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(792);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(788);
      chtlSelectorStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(789);
      chtlListenStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(790);
      chtlDelegateStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(791);
      chtlAnimateStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlSelectorStatementContext ------------------------------------------------------------------

CHTLJSParser::ChtlSelectorStatementContext::ChtlSelectorStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ChtlSelectorContext* CHTLJSParser::ChtlSelectorStatementContext::chtlSelector() {
  return getRuleContext<CHTLJSParser::ChtlSelectorContext>(0);
}

CHTLJSParser::MethodCallContext* CHTLJSParser::ChtlSelectorStatementContext::methodCall() {
  return getRuleContext<CHTLJSParser::MethodCallContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlSelectorStatementContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlSelectorStatementContext::CHTL_ARROW() {
  return getToken(CHTLJSParser::CHTL_ARROW, 0);
}


size_t CHTLJSParser::ChtlSelectorStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlSelectorStatement;
}

void CHTLJSParser::ChtlSelectorStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlSelectorStatement(this);
}

void CHTLJSParser::ChtlSelectorStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlSelectorStatement(this);
}

CHTLJSParser::ChtlSelectorStatementContext* CHTLJSParser::chtlSelectorStatement() {
  ChtlSelectorStatementContext *_localctx = _tracker.createInstance<ChtlSelectorStatementContext>(_ctx, getState());
  enterRule(_localctx, 138, CHTLJSParser::RuleChtlSelectorStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(794);
    chtlSelector();
    setState(795);
    _la = _input->LA(1);
    if (!(_la == CHTLJSParser::CHTL_ARROW

    || _la == CHTLJSParser::DOT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(796);
    methodCall(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlSelectorContext ------------------------------------------------------------------

CHTLJSParser::ChtlSelectorContext::ChtlSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlSelectorContext::CHTL_DOUBLE_BRACE() {
  return getToken(CHTLJSParser::CHTL_DOUBLE_BRACE, 0);
}

CHTLJSParser::SelectorContentContext* CHTLJSParser::ChtlSelectorContext::selectorContent() {
  return getRuleContext<CHTLJSParser::SelectorContentContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlSelectorContext::CHTL_DOUBLE_BRACE_CLOSE() {
  return getToken(CHTLJSParser::CHTL_DOUBLE_BRACE_CLOSE, 0);
}


size_t CHTLJSParser::ChtlSelectorContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlSelector;
}

void CHTLJSParser::ChtlSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlSelector(this);
}

void CHTLJSParser::ChtlSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlSelector(this);
}

CHTLJSParser::ChtlSelectorContext* CHTLJSParser::chtlSelector() {
  ChtlSelectorContext *_localctx = _tracker.createInstance<ChtlSelectorContext>(_ctx, getState());
  enterRule(_localctx, 140, CHTLJSParser::RuleChtlSelector);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(798);
    match(CHTLJSParser::CHTL_DOUBLE_BRACE);
    setState(799);
    selectorContent();
    setState(800);
    match(CHTLJSParser::CHTL_DOUBLE_BRACE_CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorContentContext ------------------------------------------------------------------

CHTLJSParser::SelectorContentContext::SelectorContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::SelectorContentContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

CHTLJSParser::SelectorTypeContext* CHTLJSParser::SelectorContentContext::selectorType() {
  return getRuleContext<CHTLJSParser::SelectorTypeContext>(0);
}

std::vector<CHTLJSParser::SelectorModifierContext *> CHTLJSParser::SelectorContentContext::selectorModifier() {
  return getRuleContexts<CHTLJSParser::SelectorModifierContext>();
}

CHTLJSParser::SelectorModifierContext* CHTLJSParser::SelectorContentContext::selectorModifier(size_t i) {
  return getRuleContext<CHTLJSParser::SelectorModifierContext>(i);
}


size_t CHTLJSParser::SelectorContentContext::getRuleIndex() const {
  return CHTLJSParser::RuleSelectorContent;
}

void CHTLJSParser::SelectorContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorContent(this);
}

void CHTLJSParser::SelectorContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorContent(this);
}

CHTLJSParser::SelectorContentContext* CHTLJSParser::selectorContent() {
  SelectorContentContext *_localctx = _tracker.createInstance<SelectorContentContext>(_ctx, getState());
  enterRule(_localctx, 142, CHTLJSParser::RuleSelectorContent);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(803);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLJSParser::HASH

    || _la == CHTLJSParser::DOT) {
      setState(802);
      selectorType();
    }
    setState(805);
    match(CHTLJSParser::IDENTIFIER);
    setState(807); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(806);
              selectorModifier();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(809); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorTypeContext ------------------------------------------------------------------

CHTLJSParser::SelectorTypeContext::SelectorTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::SelectorTypeContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}

tree::TerminalNode* CHTLJSParser::SelectorTypeContext::HASH() {
  return getToken(CHTLJSParser::HASH, 0);
}


size_t CHTLJSParser::SelectorTypeContext::getRuleIndex() const {
  return CHTLJSParser::RuleSelectorType;
}

void CHTLJSParser::SelectorTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorType(this);
}

void CHTLJSParser::SelectorTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorType(this);
}

CHTLJSParser::SelectorTypeContext* CHTLJSParser::selectorType() {
  SelectorTypeContext *_localctx = _tracker.createInstance<SelectorTypeContext>(_ctx, getState());
  enterRule(_localctx, 144, CHTLJSParser::RuleSelectorType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(811);
    _la = _input->LA(1);
    if (!(_la == CHTLJSParser::HASH

    || _la == CHTLJSParser::DOT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorModifierContext ------------------------------------------------------------------

CHTLJSParser::SelectorModifierContext::SelectorModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::SelectorModifierContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

tree::TerminalNode* CHTLJSParser::SelectorModifierContext::NUMBER() {
  return getToken(CHTLJSParser::NUMBER, 0);
}

tree::TerminalNode* CHTLJSParser::SelectorModifierContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}

std::vector<tree::TerminalNode *> CHTLJSParser::SelectorModifierContext::WS() {
  return getTokens(CHTLJSParser::WS);
}

tree::TerminalNode* CHTLJSParser::SelectorModifierContext::WS(size_t i) {
  return getToken(CHTLJSParser::WS, i);
}

std::vector<CHTLJSParser::SelectorContentContext *> CHTLJSParser::SelectorModifierContext::selectorContent() {
  return getRuleContexts<CHTLJSParser::SelectorContentContext>();
}

CHTLJSParser::SelectorContentContext* CHTLJSParser::SelectorModifierContext::selectorContent(size_t i) {
  return getRuleContext<CHTLJSParser::SelectorContentContext>(i);
}


size_t CHTLJSParser::SelectorModifierContext::getRuleIndex() const {
  return CHTLJSParser::RuleSelectorModifier;
}

void CHTLJSParser::SelectorModifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorModifier(this);
}

void CHTLJSParser::SelectorModifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorModifier(this);
}

CHTLJSParser::SelectorModifierContext* CHTLJSParser::selectorModifier() {
  SelectorModifierContext *_localctx = _tracker.createInstance<SelectorModifierContext>(_ctx, getState());
  enterRule(_localctx, 146, CHTLJSParser::RuleSelectorModifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(822);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLJSParser::LBRACKET: {
        enterOuterAlt(_localctx, 1);
        setState(813);
        match(CHTLJSParser::LBRACKET);
        setState(814);
        match(CHTLJSParser::NUMBER);
        setState(815);
        match(CHTLJSParser::RBRACKET);
        break;
      }

      case CHTLJSParser::WS: {
        enterOuterAlt(_localctx, 2);
        setState(818); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(816);
                  match(CHTLJSParser::WS);
                  setState(817);
                  selectorContent();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(820); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlListenStatementContext ------------------------------------------------------------------

CHTLJSParser::ChtlListenStatementContext::ChtlListenStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ChtlSelectorContext* CHTLJSParser::ChtlListenStatementContext::chtlSelector() {
  return getRuleContext<CHTLJSParser::ChtlSelectorContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlListenStatementContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlListenStatementContext::CHTL_LISTEN() {
  return getToken(CHTLJSParser::CHTL_LISTEN, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlListenStatementContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

CHTLJSParser::ChtlListenObjectContext* CHTLJSParser::ChtlListenStatementContext::chtlListenObject() {
  return getRuleContext<CHTLJSParser::ChtlListenObjectContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlListenStatementContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}


size_t CHTLJSParser::ChtlListenStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlListenStatement;
}

void CHTLJSParser::ChtlListenStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenStatement(this);
}

void CHTLJSParser::ChtlListenStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenStatement(this);
}

CHTLJSParser::ChtlListenStatementContext* CHTLJSParser::chtlListenStatement() {
  ChtlListenStatementContext *_localctx = _tracker.createInstance<ChtlListenStatementContext>(_ctx, getState());
  enterRule(_localctx, 148, CHTLJSParser::RuleChtlListenStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(824);
    chtlSelector();
    setState(825);
    match(CHTLJSParser::DOT);
    setState(826);
    match(CHTLJSParser::CHTL_LISTEN);
    setState(827);
    match(CHTLJSParser::LPAREN);
    setState(828);
    chtlListenObject();
    setState(829);
    match(CHTLJSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlListenObjectContext ------------------------------------------------------------------

CHTLJSParser::ChtlListenObjectContext::ChtlListenObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlListenObjectContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::ChtlListenEventsContext* CHTLJSParser::ChtlListenObjectContext::chtlListenEvents() {
  return getRuleContext<CHTLJSParser::ChtlListenEventsContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlListenObjectContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}


size_t CHTLJSParser::ChtlListenObjectContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlListenObject;
}

void CHTLJSParser::ChtlListenObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenObject(this);
}

void CHTLJSParser::ChtlListenObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenObject(this);
}

CHTLJSParser::ChtlListenObjectContext* CHTLJSParser::chtlListenObject() {
  ChtlListenObjectContext *_localctx = _tracker.createInstance<ChtlListenObjectContext>(_ctx, getState());
  enterRule(_localctx, 150, CHTLJSParser::RuleChtlListenObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(831);
    match(CHTLJSParser::LBRACE);
    setState(832);
    chtlListenEvents();
    setState(833);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlListenEventsContext ------------------------------------------------------------------

CHTLJSParser::ChtlListenEventsContext::ChtlListenEventsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::ChtlListenEventContext *> CHTLJSParser::ChtlListenEventsContext::chtlListenEvent() {
  return getRuleContexts<CHTLJSParser::ChtlListenEventContext>();
}

CHTLJSParser::ChtlListenEventContext* CHTLJSParser::ChtlListenEventsContext::chtlListenEvent(size_t i) {
  return getRuleContext<CHTLJSParser::ChtlListenEventContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ChtlListenEventsContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ChtlListenEventsContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ChtlListenEventsContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlListenEvents;
}

void CHTLJSParser::ChtlListenEventsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenEvents(this);
}

void CHTLJSParser::ChtlListenEventsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenEvents(this);
}

CHTLJSParser::ChtlListenEventsContext* CHTLJSParser::chtlListenEvents() {
  ChtlListenEventsContext *_localctx = _tracker.createInstance<ChtlListenEventsContext>(_ctx, getState());
  enterRule(_localctx, 152, CHTLJSParser::RuleChtlListenEvents);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(835);
    chtlListenEvent();
    setState(840);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(836);
      match(CHTLJSParser::COMMA);
      setState(837);
      chtlListenEvent();
      setState(842);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlListenEventContext ------------------------------------------------------------------

CHTLJSParser::ChtlListenEventContext::ChtlListenEventContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::EventTypeContext* CHTLJSParser::ChtlListenEventContext::eventType() {
  return getRuleContext<CHTLJSParser::EventTypeContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlListenEventContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::EventHandlerContext* CHTLJSParser::ChtlListenEventContext::eventHandler() {
  return getRuleContext<CHTLJSParser::EventHandlerContext>(0);
}


size_t CHTLJSParser::ChtlListenEventContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlListenEvent;
}

void CHTLJSParser::ChtlListenEventContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlListenEvent(this);
}

void CHTLJSParser::ChtlListenEventContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlListenEvent(this);
}

CHTLJSParser::ChtlListenEventContext* CHTLJSParser::chtlListenEvent() {
  ChtlListenEventContext *_localctx = _tracker.createInstance<ChtlListenEventContext>(_ctx, getState());
  enterRule(_localctx, 154, CHTLJSParser::RuleChtlListenEvent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(843);
    eventType();
    setState(844);
    match(CHTLJSParser::COLON);
    setState(845);
    eventHandler();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventTypeContext ------------------------------------------------------------------

CHTLJSParser::EventTypeContext::EventTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::EventTypeContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}


size_t CHTLJSParser::EventTypeContext::getRuleIndex() const {
  return CHTLJSParser::RuleEventType;
}

void CHTLJSParser::EventTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEventType(this);
}

void CHTLJSParser::EventTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEventType(this);
}

CHTLJSParser::EventTypeContext* CHTLJSParser::eventType() {
  EventTypeContext *_localctx = _tracker.createInstance<EventTypeContext>(_ctx, getState());
  enterRule(_localctx, 156, CHTLJSParser::RuleEventType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(847);
    match(CHTLJSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventHandlerContext ------------------------------------------------------------------

CHTLJSParser::EventHandlerContext::EventHandlerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::EventHandlerContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

CHTLJSParser::FunctionExpressionContext* CHTLJSParser::EventHandlerContext::functionExpression() {
  return getRuleContext<CHTLJSParser::FunctionExpressionContext>(0);
}

CHTLJSParser::ArrowFunctionContext* CHTLJSParser::EventHandlerContext::arrowFunction() {
  return getRuleContext<CHTLJSParser::ArrowFunctionContext>(0);
}


size_t CHTLJSParser::EventHandlerContext::getRuleIndex() const {
  return CHTLJSParser::RuleEventHandler;
}

void CHTLJSParser::EventHandlerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEventHandler(this);
}

void CHTLJSParser::EventHandlerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEventHandler(this);
}

CHTLJSParser::EventHandlerContext* CHTLJSParser::eventHandler() {
  EventHandlerContext *_localctx = _tracker.createInstance<EventHandlerContext>(_ctx, getState());
  enterRule(_localctx, 158, CHTLJSParser::RuleEventHandler);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(852);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(849);
      match(CHTLJSParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(850);
      functionExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(851);
      arrowFunction();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDelegateStatementContext ------------------------------------------------------------------

CHTLJSParser::ChtlDelegateStatementContext::ChtlDelegateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ChtlSelectorContext* CHTLJSParser::ChtlDelegateStatementContext::chtlSelector() {
  return getRuleContext<CHTLJSParser::ChtlSelectorContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelegateStatementContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelegateStatementContext::CHTL_DELEGATE() {
  return getToken(CHTLJSParser::CHTL_DELEGATE, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelegateStatementContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

CHTLJSParser::ChtlDelegateObjectContext* CHTLJSParser::ChtlDelegateStatementContext::chtlDelegateObject() {
  return getRuleContext<CHTLJSParser::ChtlDelegateObjectContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelegateStatementContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}


size_t CHTLJSParser::ChtlDelegateStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlDelegateStatement;
}

void CHTLJSParser::ChtlDelegateStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDelegateStatement(this);
}

void CHTLJSParser::ChtlDelegateStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDelegateStatement(this);
}

CHTLJSParser::ChtlDelegateStatementContext* CHTLJSParser::chtlDelegateStatement() {
  ChtlDelegateStatementContext *_localctx = _tracker.createInstance<ChtlDelegateStatementContext>(_ctx, getState());
  enterRule(_localctx, 160, CHTLJSParser::RuleChtlDelegateStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(854);
    chtlSelector();
    setState(855);
    match(CHTLJSParser::DOT);
    setState(856);
    match(CHTLJSParser::CHTL_DELEGATE);
    setState(857);
    match(CHTLJSParser::LPAREN);
    setState(858);
    chtlDelegateObject();
    setState(859);
    match(CHTLJSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDelegateObjectContext ------------------------------------------------------------------

CHTLJSParser::ChtlDelegateObjectContext::ChtlDelegateObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlDelegateObjectContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::ChtlDelegateConfigContext* CHTLJSParser::ChtlDelegateObjectContext::chtlDelegateConfig() {
  return getRuleContext<CHTLJSParser::ChtlDelegateConfigContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelegateObjectContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}


size_t CHTLJSParser::ChtlDelegateObjectContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlDelegateObject;
}

void CHTLJSParser::ChtlDelegateObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDelegateObject(this);
}

void CHTLJSParser::ChtlDelegateObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDelegateObject(this);
}

CHTLJSParser::ChtlDelegateObjectContext* CHTLJSParser::chtlDelegateObject() {
  ChtlDelegateObjectContext *_localctx = _tracker.createInstance<ChtlDelegateObjectContext>(_ctx, getState());
  enterRule(_localctx, 162, CHTLJSParser::RuleChtlDelegateObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(861);
    match(CHTLJSParser::LBRACE);
    setState(862);
    chtlDelegateConfig();
    setState(863);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDelegateConfigContext ------------------------------------------------------------------

CHTLJSParser::ChtlDelegateConfigContext::ChtlDelegateConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ChtlTargetConfigContext* CHTLJSParser::ChtlDelegateConfigContext::chtlTargetConfig() {
  return getRuleContext<CHTLJSParser::ChtlTargetConfigContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelegateConfigContext::COMMA() {
  return getToken(CHTLJSParser::COMMA, 0);
}

CHTLJSParser::ChtlEventConfigContext* CHTLJSParser::ChtlDelegateConfigContext::chtlEventConfig() {
  return getRuleContext<CHTLJSParser::ChtlEventConfigContext>(0);
}


size_t CHTLJSParser::ChtlDelegateConfigContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlDelegateConfig;
}

void CHTLJSParser::ChtlDelegateConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDelegateConfig(this);
}

void CHTLJSParser::ChtlDelegateConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDelegateConfig(this);
}

CHTLJSParser::ChtlDelegateConfigContext* CHTLJSParser::chtlDelegateConfig() {
  ChtlDelegateConfigContext *_localctx = _tracker.createInstance<ChtlDelegateConfigContext>(_ctx, getState());
  enterRule(_localctx, 164, CHTLJSParser::RuleChtlDelegateConfig);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(865);
    chtlTargetConfig();
    setState(866);
    match(CHTLJSParser::COMMA);
    setState(867);
    chtlEventConfig();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlTargetConfigContext ------------------------------------------------------------------

CHTLJSParser::ChtlTargetConfigContext::ChtlTargetConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlTargetConfigContext::CHTL_TARGET() {
  return getToken(CHTLJSParser::CHTL_TARGET, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlTargetConfigContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::ChtlSelectorContext* CHTLJSParser::ChtlTargetConfigContext::chtlSelector() {
  return getRuleContext<CHTLJSParser::ChtlSelectorContext>(0);
}

CHTLJSParser::ChtlSelectorArrayContext* CHTLJSParser::ChtlTargetConfigContext::chtlSelectorArray() {
  return getRuleContext<CHTLJSParser::ChtlSelectorArrayContext>(0);
}


size_t CHTLJSParser::ChtlTargetConfigContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlTargetConfig;
}

void CHTLJSParser::ChtlTargetConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlTargetConfig(this);
}

void CHTLJSParser::ChtlTargetConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlTargetConfig(this);
}

CHTLJSParser::ChtlTargetConfigContext* CHTLJSParser::chtlTargetConfig() {
  ChtlTargetConfigContext *_localctx = _tracker.createInstance<ChtlTargetConfigContext>(_ctx, getState());
  enterRule(_localctx, 166, CHTLJSParser::RuleChtlTargetConfig);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(869);
    match(CHTLJSParser::CHTL_TARGET);
    setState(870);
    match(CHTLJSParser::COLON);
    setState(873);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLJSParser::CHTL_DOUBLE_BRACE: {
        setState(871);
        chtlSelector();
        break;
      }

      case CHTLJSParser::LBRACKET: {
        setState(872);
        chtlSelectorArray();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlSelectorArrayContext ------------------------------------------------------------------

CHTLJSParser::ChtlSelectorArrayContext::ChtlSelectorArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlSelectorArrayContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

std::vector<CHTLJSParser::ChtlSelectorContext *> CHTLJSParser::ChtlSelectorArrayContext::chtlSelector() {
  return getRuleContexts<CHTLJSParser::ChtlSelectorContext>();
}

CHTLJSParser::ChtlSelectorContext* CHTLJSParser::ChtlSelectorArrayContext::chtlSelector(size_t i) {
  return getRuleContext<CHTLJSParser::ChtlSelectorContext>(i);
}

tree::TerminalNode* CHTLJSParser::ChtlSelectorArrayContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ChtlSelectorArrayContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ChtlSelectorArrayContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ChtlSelectorArrayContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlSelectorArray;
}

void CHTLJSParser::ChtlSelectorArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlSelectorArray(this);
}

void CHTLJSParser::ChtlSelectorArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlSelectorArray(this);
}

CHTLJSParser::ChtlSelectorArrayContext* CHTLJSParser::chtlSelectorArray() {
  ChtlSelectorArrayContext *_localctx = _tracker.createInstance<ChtlSelectorArrayContext>(_ctx, getState());
  enterRule(_localctx, 168, CHTLJSParser::RuleChtlSelectorArray);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(875);
    match(CHTLJSParser::LBRACKET);
    setState(876);
    chtlSelector();
    setState(881);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(877);
      match(CHTLJSParser::COMMA);
      setState(878);
      chtlSelector();
      setState(883);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(884);
    match(CHTLJSParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlEventConfigContext ------------------------------------------------------------------

CHTLJSParser::ChtlEventConfigContext::ChtlEventConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ChtlListenEventsContext* CHTLJSParser::ChtlEventConfigContext::chtlListenEvents() {
  return getRuleContext<CHTLJSParser::ChtlListenEventsContext>(0);
}


size_t CHTLJSParser::ChtlEventConfigContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlEventConfig;
}

void CHTLJSParser::ChtlEventConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlEventConfig(this);
}

void CHTLJSParser::ChtlEventConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlEventConfig(this);
}

CHTLJSParser::ChtlEventConfigContext* CHTLJSParser::chtlEventConfig() {
  ChtlEventConfigContext *_localctx = _tracker.createInstance<ChtlEventConfigContext>(_ctx, getState());
  enterRule(_localctx, 170, CHTLJSParser::RuleChtlEventConfig);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(886);
    chtlListenEvents();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAnimateStatementContext ------------------------------------------------------------------

CHTLJSParser::ChtlAnimateStatementContext::ChtlAnimateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlAnimateStatementContext::CHTL_ANIMATE() {
  return getToken(CHTLJSParser::CHTL_ANIMATE, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlAnimateStatementContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

CHTLJSParser::ChtlAnimateObjectContext* CHTLJSParser::ChtlAnimateStatementContext::chtlAnimateObject() {
  return getRuleContext<CHTLJSParser::ChtlAnimateObjectContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlAnimateStatementContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}


size_t CHTLJSParser::ChtlAnimateStatementContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlAnimateStatement;
}

void CHTLJSParser::ChtlAnimateStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateStatement(this);
}

void CHTLJSParser::ChtlAnimateStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateStatement(this);
}

CHTLJSParser::ChtlAnimateStatementContext* CHTLJSParser::chtlAnimateStatement() {
  ChtlAnimateStatementContext *_localctx = _tracker.createInstance<ChtlAnimateStatementContext>(_ctx, getState());
  enterRule(_localctx, 172, CHTLJSParser::RuleChtlAnimateStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(888);
    match(CHTLJSParser::CHTL_ANIMATE);
    setState(889);
    match(CHTLJSParser::LPAREN);
    setState(890);
    chtlAnimateObject();
    setState(891);
    match(CHTLJSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAnimateObjectContext ------------------------------------------------------------------

CHTLJSParser::ChtlAnimateObjectContext::ChtlAnimateObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlAnimateObjectContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::ChtlAnimateConfigContext* CHTLJSParser::ChtlAnimateObjectContext::chtlAnimateConfig() {
  return getRuleContext<CHTLJSParser::ChtlAnimateConfigContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlAnimateObjectContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}


size_t CHTLJSParser::ChtlAnimateObjectContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlAnimateObject;
}

void CHTLJSParser::ChtlAnimateObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateObject(this);
}

void CHTLJSParser::ChtlAnimateObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateObject(this);
}

CHTLJSParser::ChtlAnimateObjectContext* CHTLJSParser::chtlAnimateObject() {
  ChtlAnimateObjectContext *_localctx = _tracker.createInstance<ChtlAnimateObjectContext>(_ctx, getState());
  enterRule(_localctx, 174, CHTLJSParser::RuleChtlAnimateObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(893);
    match(CHTLJSParser::LBRACE);
    setState(894);
    chtlAnimateConfig();
    setState(895);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAnimateConfigContext ------------------------------------------------------------------

CHTLJSParser::ChtlAnimateConfigContext::ChtlAnimateConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::ChtlAnimatePropertyContext *> CHTLJSParser::ChtlAnimateConfigContext::chtlAnimateProperty() {
  return getRuleContexts<CHTLJSParser::ChtlAnimatePropertyContext>();
}

CHTLJSParser::ChtlAnimatePropertyContext* CHTLJSParser::ChtlAnimateConfigContext::chtlAnimateProperty(size_t i) {
  return getRuleContext<CHTLJSParser::ChtlAnimatePropertyContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ChtlAnimateConfigContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ChtlAnimateConfigContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ChtlAnimateConfigContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlAnimateConfig;
}

void CHTLJSParser::ChtlAnimateConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateConfig(this);
}

void CHTLJSParser::ChtlAnimateConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateConfig(this);
}

CHTLJSParser::ChtlAnimateConfigContext* CHTLJSParser::chtlAnimateConfig() {
  ChtlAnimateConfigContext *_localctx = _tracker.createInstance<ChtlAnimateConfigContext>(_ctx, getState());
  enterRule(_localctx, 176, CHTLJSParser::RuleChtlAnimateConfig);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(897);
    chtlAnimateProperty();
    setState(902);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(898);
      match(CHTLJSParser::COMMA);
      setState(899);
      chtlAnimateProperty();
      setState(904);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAnimatePropertyContext ------------------------------------------------------------------

CHTLJSParser::ChtlAnimatePropertyContext::ChtlAnimatePropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::ChtlDurationContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlDuration() {
  return getRuleContext<CHTLJSParser::ChtlDurationContext>(0);
}

CHTLJSParser::ChtlEasingContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlEasing() {
  return getRuleContext<CHTLJSParser::ChtlEasingContext>(0);
}

CHTLJSParser::ChtlBeginContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlBegin() {
  return getRuleContext<CHTLJSParser::ChtlBeginContext>(0);
}

CHTLJSParser::ChtlWhenContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlWhen() {
  return getRuleContext<CHTLJSParser::ChtlWhenContext>(0);
}

CHTLJSParser::ChtlEndContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlEnd() {
  return getRuleContext<CHTLJSParser::ChtlEndContext>(0);
}

CHTLJSParser::ChtlLoopContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlLoop() {
  return getRuleContext<CHTLJSParser::ChtlLoopContext>(0);
}

CHTLJSParser::ChtlDirectionContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlDirection() {
  return getRuleContext<CHTLJSParser::ChtlDirectionContext>(0);
}

CHTLJSParser::ChtlDelayContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlDelay() {
  return getRuleContext<CHTLJSParser::ChtlDelayContext>(0);
}

CHTLJSParser::ChtlCallbackContext* CHTLJSParser::ChtlAnimatePropertyContext::chtlCallback() {
  return getRuleContext<CHTLJSParser::ChtlCallbackContext>(0);
}


size_t CHTLJSParser::ChtlAnimatePropertyContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlAnimateProperty;
}

void CHTLJSParser::ChtlAnimatePropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAnimateProperty(this);
}

void CHTLJSParser::ChtlAnimatePropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAnimateProperty(this);
}

CHTLJSParser::ChtlAnimatePropertyContext* CHTLJSParser::chtlAnimateProperty() {
  ChtlAnimatePropertyContext *_localctx = _tracker.createInstance<ChtlAnimatePropertyContext>(_ctx, getState());
  enterRule(_localctx, 178, CHTLJSParser::RuleChtlAnimateProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(914);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CHTLJSParser::CHTL_DURATION: {
        enterOuterAlt(_localctx, 1);
        setState(905);
        chtlDuration();
        break;
      }

      case CHTLJSParser::CHTL_EASING: {
        enterOuterAlt(_localctx, 2);
        setState(906);
        chtlEasing();
        break;
      }

      case CHTLJSParser::CHTL_BEGIN: {
        enterOuterAlt(_localctx, 3);
        setState(907);
        chtlBegin();
        break;
      }

      case CHTLJSParser::CHTL_WHEN: {
        enterOuterAlt(_localctx, 4);
        setState(908);
        chtlWhen();
        break;
      }

      case CHTLJSParser::CHTL_END: {
        enterOuterAlt(_localctx, 5);
        setState(909);
        chtlEnd();
        break;
      }

      case CHTLJSParser::CHTL_LOOP: {
        enterOuterAlt(_localctx, 6);
        setState(910);
        chtlLoop();
        break;
      }

      case CHTLJSParser::CHTL_DIRECTION: {
        enterOuterAlt(_localctx, 7);
        setState(911);
        chtlDirection();
        break;
      }

      case CHTLJSParser::CHTL_DELAY: {
        enterOuterAlt(_localctx, 8);
        setState(912);
        chtlDelay();
        break;
      }

      case CHTLJSParser::CHTL_CALLBACK: {
        enterOuterAlt(_localctx, 9);
        setState(913);
        chtlCallback();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDurationContext ------------------------------------------------------------------

CHTLJSParser::ChtlDurationContext::ChtlDurationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlDurationContext::CHTL_DURATION() {
  return getToken(CHTLJSParser::CHTL_DURATION, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlDurationContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlDurationContext::NUMBER() {
  return getToken(CHTLJSParser::NUMBER, 0);
}


size_t CHTLJSParser::ChtlDurationContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlDuration;
}

void CHTLJSParser::ChtlDurationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDuration(this);
}

void CHTLJSParser::ChtlDurationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDuration(this);
}

CHTLJSParser::ChtlDurationContext* CHTLJSParser::chtlDuration() {
  ChtlDurationContext *_localctx = _tracker.createInstance<ChtlDurationContext>(_ctx, getState());
  enterRule(_localctx, 180, CHTLJSParser::RuleChtlDuration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(916);
    match(CHTLJSParser::CHTL_DURATION);
    setState(917);
    match(CHTLJSParser::COLON);
    setState(918);
    match(CHTLJSParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlEasingContext ------------------------------------------------------------------

CHTLJSParser::ChtlEasingContext::ChtlEasingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlEasingContext::CHTL_EASING() {
  return getToken(CHTLJSParser::CHTL_EASING, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlEasingContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::EasingValueContext* CHTLJSParser::ChtlEasingContext::easingValue() {
  return getRuleContext<CHTLJSParser::EasingValueContext>(0);
}


size_t CHTLJSParser::ChtlEasingContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlEasing;
}

void CHTLJSParser::ChtlEasingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlEasing(this);
}

void CHTLJSParser::ChtlEasingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlEasing(this);
}

CHTLJSParser::ChtlEasingContext* CHTLJSParser::chtlEasing() {
  ChtlEasingContext *_localctx = _tracker.createInstance<ChtlEasingContext>(_ctx, getState());
  enterRule(_localctx, 182, CHTLJSParser::RuleChtlEasing);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(920);
    match(CHTLJSParser::CHTL_EASING);
    setState(921);
    match(CHTLJSParser::COLON);
    setState(922);
    easingValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EasingValueContext ------------------------------------------------------------------

CHTLJSParser::EasingValueContext::EasingValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::EasingValueContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::EasingValueContext::STRING() {
  return getToken(CHTLJSParser::STRING, 0);
}


size_t CHTLJSParser::EasingValueContext::getRuleIndex() const {
  return CHTLJSParser::RuleEasingValue;
}

void CHTLJSParser::EasingValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEasingValue(this);
}

void CHTLJSParser::EasingValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEasingValue(this);
}

CHTLJSParser::EasingValueContext* CHTLJSParser::easingValue() {
  EasingValueContext *_localctx = _tracker.createInstance<EasingValueContext>(_ctx, getState());
  enterRule(_localctx, 184, CHTLJSParser::RuleEasingValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(924);
    _la = _input->LA(1);
    if (!(_la == CHTLJSParser::STRING

    || _la == CHTLJSParser::IDENTIFIER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlBeginContext ------------------------------------------------------------------

CHTLJSParser::ChtlBeginContext::ChtlBeginContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlBeginContext::CHTL_BEGIN() {
  return getToken(CHTLJSParser::CHTL_BEGIN, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlBeginContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlBeginContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::ChtlCssPropertiesContext* CHTLJSParser::ChtlBeginContext::chtlCssProperties() {
  return getRuleContext<CHTLJSParser::ChtlCssPropertiesContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlBeginContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}


size_t CHTLJSParser::ChtlBeginContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlBegin;
}

void CHTLJSParser::ChtlBeginContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlBegin(this);
}

void CHTLJSParser::ChtlBeginContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlBegin(this);
}

CHTLJSParser::ChtlBeginContext* CHTLJSParser::chtlBegin() {
  ChtlBeginContext *_localctx = _tracker.createInstance<ChtlBeginContext>(_ctx, getState());
  enterRule(_localctx, 186, CHTLJSParser::RuleChtlBegin);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(926);
    match(CHTLJSParser::CHTL_BEGIN);
    setState(927);
    match(CHTLJSParser::COLON);
    setState(928);
    match(CHTLJSParser::LBRACE);
    setState(929);
    chtlCssProperties();
    setState(930);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlWhenContext ------------------------------------------------------------------

CHTLJSParser::ChtlWhenContext::ChtlWhenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlWhenContext::CHTL_WHEN() {
  return getToken(CHTLJSParser::CHTL_WHEN, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlWhenContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlWhenContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

std::vector<CHTLJSParser::ChtlWhenClauseContext *> CHTLJSParser::ChtlWhenContext::chtlWhenClause() {
  return getRuleContexts<CHTLJSParser::ChtlWhenClauseContext>();
}

CHTLJSParser::ChtlWhenClauseContext* CHTLJSParser::ChtlWhenContext::chtlWhenClause(size_t i) {
  return getRuleContext<CHTLJSParser::ChtlWhenClauseContext>(i);
}

tree::TerminalNode* CHTLJSParser::ChtlWhenContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}

std::vector<tree::TerminalNode *> CHTLJSParser::ChtlWhenContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::ChtlWhenContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::ChtlWhenContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlWhen;
}

void CHTLJSParser::ChtlWhenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlWhen(this);
}

void CHTLJSParser::ChtlWhenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlWhen(this);
}

CHTLJSParser::ChtlWhenContext* CHTLJSParser::chtlWhen() {
  ChtlWhenContext *_localctx = _tracker.createInstance<ChtlWhenContext>(_ctx, getState());
  enterRule(_localctx, 188, CHTLJSParser::RuleChtlWhen);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(932);
    match(CHTLJSParser::CHTL_WHEN);
    setState(933);
    match(CHTLJSParser::COLON);
    setState(934);
    match(CHTLJSParser::LBRACKET);
    setState(935);
    chtlWhenClause();
    setState(940);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::COMMA) {
      setState(936);
      match(CHTLJSParser::COMMA);
      setState(937);
      chtlWhenClause();
      setState(942);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(943);
    match(CHTLJSParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlWhenClauseContext ------------------------------------------------------------------

CHTLJSParser::ChtlWhenClauseContext::ChtlWhenClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlWhenClauseContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::ChtlAtContext* CHTLJSParser::ChtlWhenClauseContext::chtlAt() {
  return getRuleContext<CHTLJSParser::ChtlAtContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlWhenClauseContext::COMMA() {
  return getToken(CHTLJSParser::COMMA, 0);
}

CHTLJSParser::ChtlCssPropertiesContext* CHTLJSParser::ChtlWhenClauseContext::chtlCssProperties() {
  return getRuleContext<CHTLJSParser::ChtlCssPropertiesContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlWhenClauseContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}


size_t CHTLJSParser::ChtlWhenClauseContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlWhenClause;
}

void CHTLJSParser::ChtlWhenClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlWhenClause(this);
}

void CHTLJSParser::ChtlWhenClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlWhenClause(this);
}

CHTLJSParser::ChtlWhenClauseContext* CHTLJSParser::chtlWhenClause() {
  ChtlWhenClauseContext *_localctx = _tracker.createInstance<ChtlWhenClauseContext>(_ctx, getState());
  enterRule(_localctx, 190, CHTLJSParser::RuleChtlWhenClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(945);
    match(CHTLJSParser::LBRACE);
    setState(946);
    chtlAt();
    setState(947);
    match(CHTLJSParser::COMMA);
    setState(948);
    chtlCssProperties();
    setState(949);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlAtContext ------------------------------------------------------------------

CHTLJSParser::ChtlAtContext::ChtlAtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlAtContext::CHTL_AT() {
  return getToken(CHTLJSParser::CHTL_AT, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlAtContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlAtContext::NUMBER() {
  return getToken(CHTLJSParser::NUMBER, 0);
}


size_t CHTLJSParser::ChtlAtContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlAt;
}

void CHTLJSParser::ChtlAtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAt(this);
}

void CHTLJSParser::ChtlAtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAt(this);
}

CHTLJSParser::ChtlAtContext* CHTLJSParser::chtlAt() {
  ChtlAtContext *_localctx = _tracker.createInstance<ChtlAtContext>(_ctx, getState());
  enterRule(_localctx, 192, CHTLJSParser::RuleChtlAt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(951);
    match(CHTLJSParser::CHTL_AT);
    setState(952);
    match(CHTLJSParser::COLON);
    setState(953);
    match(CHTLJSParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlEndContext ------------------------------------------------------------------

CHTLJSParser::ChtlEndContext::ChtlEndContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlEndContext::CHTL_END() {
  return getToken(CHTLJSParser::CHTL_END, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlEndContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlEndContext::LBRACE() {
  return getToken(CHTLJSParser::LBRACE, 0);
}

CHTLJSParser::ChtlCssPropertiesContext* CHTLJSParser::ChtlEndContext::chtlCssProperties() {
  return getRuleContext<CHTLJSParser::ChtlCssPropertiesContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlEndContext::RBRACE() {
  return getToken(CHTLJSParser::RBRACE, 0);
}


size_t CHTLJSParser::ChtlEndContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlEnd;
}

void CHTLJSParser::ChtlEndContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlEnd(this);
}

void CHTLJSParser::ChtlEndContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlEnd(this);
}

CHTLJSParser::ChtlEndContext* CHTLJSParser::chtlEnd() {
  ChtlEndContext *_localctx = _tracker.createInstance<ChtlEndContext>(_ctx, getState());
  enterRule(_localctx, 194, CHTLJSParser::RuleChtlEnd);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(955);
    match(CHTLJSParser::CHTL_END);
    setState(956);
    match(CHTLJSParser::COLON);
    setState(957);
    match(CHTLJSParser::LBRACE);
    setState(958);
    chtlCssProperties();
    setState(959);
    match(CHTLJSParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlLoopContext ------------------------------------------------------------------

CHTLJSParser::ChtlLoopContext::ChtlLoopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlLoopContext::CHTL_LOOP() {
  return getToken(CHTLJSParser::CHTL_LOOP, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlLoopContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlLoopContext::NUMBER() {
  return getToken(CHTLJSParser::NUMBER, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlLoopContext::MINUS() {
  return getToken(CHTLJSParser::MINUS, 0);
}


size_t CHTLJSParser::ChtlLoopContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlLoop;
}

void CHTLJSParser::ChtlLoopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlLoop(this);
}

void CHTLJSParser::ChtlLoopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlLoop(this);
}

CHTLJSParser::ChtlLoopContext* CHTLJSParser::chtlLoop() {
  ChtlLoopContext *_localctx = _tracker.createInstance<ChtlLoopContext>(_ctx, getState());
  enterRule(_localctx, 196, CHTLJSParser::RuleChtlLoop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(961);
    match(CHTLJSParser::CHTL_LOOP);
    setState(962);
    match(CHTLJSParser::COLON);
    setState(963);
    _la = _input->LA(1);
    if (!(_la == CHTLJSParser::NUMBER

    || _la == CHTLJSParser::MINUS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDirectionContext ------------------------------------------------------------------

CHTLJSParser::ChtlDirectionContext::ChtlDirectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlDirectionContext::CHTL_DIRECTION() {
  return getToken(CHTLJSParser::CHTL_DIRECTION, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlDirectionContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::DirectionValueContext* CHTLJSParser::ChtlDirectionContext::directionValue() {
  return getRuleContext<CHTLJSParser::DirectionValueContext>(0);
}


size_t CHTLJSParser::ChtlDirectionContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlDirection;
}

void CHTLJSParser::ChtlDirectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDirection(this);
}

void CHTLJSParser::ChtlDirectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDirection(this);
}

CHTLJSParser::ChtlDirectionContext* CHTLJSParser::chtlDirection() {
  ChtlDirectionContext *_localctx = _tracker.createInstance<ChtlDirectionContext>(_ctx, getState());
  enterRule(_localctx, 198, CHTLJSParser::RuleChtlDirection);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(965);
    match(CHTLJSParser::CHTL_DIRECTION);
    setState(966);
    match(CHTLJSParser::COLON);
    setState(967);
    directionValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectionValueContext ------------------------------------------------------------------

CHTLJSParser::DirectionValueContext::DirectionValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::DirectionValueContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::DirectionValueContext::STRING() {
  return getToken(CHTLJSParser::STRING, 0);
}


size_t CHTLJSParser::DirectionValueContext::getRuleIndex() const {
  return CHTLJSParser::RuleDirectionValue;
}

void CHTLJSParser::DirectionValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirectionValue(this);
}

void CHTLJSParser::DirectionValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirectionValue(this);
}

CHTLJSParser::DirectionValueContext* CHTLJSParser::directionValue() {
  DirectionValueContext *_localctx = _tracker.createInstance<DirectionValueContext>(_ctx, getState());
  enterRule(_localctx, 200, CHTLJSParser::RuleDirectionValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(969);
    _la = _input->LA(1);
    if (!(_la == CHTLJSParser::STRING

    || _la == CHTLJSParser::IDENTIFIER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDelayContext ------------------------------------------------------------------

CHTLJSParser::ChtlDelayContext::ChtlDelayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlDelayContext::CHTL_DELAY() {
  return getToken(CHTLJSParser::CHTL_DELAY, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelayContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlDelayContext::NUMBER() {
  return getToken(CHTLJSParser::NUMBER, 0);
}


size_t CHTLJSParser::ChtlDelayContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlDelay;
}

void CHTLJSParser::ChtlDelayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDelay(this);
}

void CHTLJSParser::ChtlDelayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDelay(this);
}

CHTLJSParser::ChtlDelayContext* CHTLJSParser::chtlDelay() {
  ChtlDelayContext *_localctx = _tracker.createInstance<ChtlDelayContext>(_ctx, getState());
  enterRule(_localctx, 202, CHTLJSParser::RuleChtlDelay);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(971);
    match(CHTLJSParser::CHTL_DELAY);
    setState(972);
    match(CHTLJSParser::COLON);
    setState(973);
    match(CHTLJSParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlCallbackContext ------------------------------------------------------------------

CHTLJSParser::ChtlCallbackContext::ChtlCallbackContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ChtlCallbackContext::CHTL_CALLBACK() {
  return getToken(CHTLJSParser::CHTL_CALLBACK, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlCallbackContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

tree::TerminalNode* CHTLJSParser::ChtlCallbackContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}


size_t CHTLJSParser::ChtlCallbackContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlCallback;
}

void CHTLJSParser::ChtlCallbackContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlCallback(this);
}

void CHTLJSParser::ChtlCallbackContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlCallback(this);
}

CHTLJSParser::ChtlCallbackContext* CHTLJSParser::chtlCallback() {
  ChtlCallbackContext *_localctx = _tracker.createInstance<ChtlCallbackContext>(_ctx, getState());
  enterRule(_localctx, 204, CHTLJSParser::RuleChtlCallback);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(975);
    match(CHTLJSParser::CHTL_CALLBACK);
    setState(976);
    match(CHTLJSParser::COLON);
    setState(977);
    match(CHTLJSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlCssPropertiesContext ------------------------------------------------------------------

CHTLJSParser::ChtlCssPropertiesContext::ChtlCssPropertiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::ChtlCssPropertyContext *> CHTLJSParser::ChtlCssPropertiesContext::chtlCssProperty() {
  return getRuleContexts<CHTLJSParser::ChtlCssPropertyContext>();
}

CHTLJSParser::ChtlCssPropertyContext* CHTLJSParser::ChtlCssPropertiesContext::chtlCssProperty(size_t i) {
  return getRuleContext<CHTLJSParser::ChtlCssPropertyContext>(i);
}


size_t CHTLJSParser::ChtlCssPropertiesContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlCssProperties;
}

void CHTLJSParser::ChtlCssPropertiesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlCssProperties(this);
}

void CHTLJSParser::ChtlCssPropertiesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlCssProperties(this);
}

CHTLJSParser::ChtlCssPropertiesContext* CHTLJSParser::chtlCssProperties() {
  ChtlCssPropertiesContext *_localctx = _tracker.createInstance<ChtlCssPropertiesContext>(_ctx, getState());
  enterRule(_localctx, 206, CHTLJSParser::RuleChtlCssProperties);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(982);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLJSParser::IDENTIFIER) {
      setState(979);
      chtlCssProperty();
      setState(984);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlCssPropertyContext ------------------------------------------------------------------

CHTLJSParser::ChtlCssPropertyContext::ChtlCssPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLJSParser::PropertyNameContext* CHTLJSParser::ChtlCssPropertyContext::propertyName() {
  return getRuleContext<CHTLJSParser::PropertyNameContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlCssPropertyContext::COLON() {
  return getToken(CHTLJSParser::COLON, 0);
}

CHTLJSParser::PropertyValueContext* CHTLJSParser::ChtlCssPropertyContext::propertyValue() {
  return getRuleContext<CHTLJSParser::PropertyValueContext>(0);
}

tree::TerminalNode* CHTLJSParser::ChtlCssPropertyContext::SEMICOLON() {
  return getToken(CHTLJSParser::SEMICOLON, 0);
}


size_t CHTLJSParser::ChtlCssPropertyContext::getRuleIndex() const {
  return CHTLJSParser::RuleChtlCssProperty;
}

void CHTLJSParser::ChtlCssPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlCssProperty(this);
}

void CHTLJSParser::ChtlCssPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlCssProperty(this);
}

CHTLJSParser::ChtlCssPropertyContext* CHTLJSParser::chtlCssProperty() {
  ChtlCssPropertyContext *_localctx = _tracker.createInstance<ChtlCssPropertyContext>(_ctx, getState());
  enterRule(_localctx, 208, CHTLJSParser::RuleChtlCssProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(985);
    propertyName();
    setState(986);
    match(CHTLJSParser::COLON);
    setState(987);
    propertyValue();
    setState(988);
    match(CHTLJSParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyNameContext ------------------------------------------------------------------

CHTLJSParser::PropertyNameContext::PropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::PropertyNameContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}


size_t CHTLJSParser::PropertyNameContext::getRuleIndex() const {
  return CHTLJSParser::RulePropertyName;
}

void CHTLJSParser::PropertyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyName(this);
}

void CHTLJSParser::PropertyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyName(this);
}

CHTLJSParser::PropertyNameContext* CHTLJSParser::propertyName() {
  PropertyNameContext *_localctx = _tracker.createInstance<PropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 210, CHTLJSParser::RulePropertyName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(990);
    match(CHTLJSParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyValueContext ------------------------------------------------------------------

CHTLJSParser::PropertyValueContext::PropertyValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLJSParser::PropertyValueContext::STRING() {
  return getTokens(CHTLJSParser::STRING);
}

tree::TerminalNode* CHTLJSParser::PropertyValueContext::STRING(size_t i) {
  return getToken(CHTLJSParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::PropertyValueContext::LITERAL() {
  return getTokens(CHTLJSParser::LITERAL);
}

tree::TerminalNode* CHTLJSParser::PropertyValueContext::LITERAL(size_t i) {
  return getToken(CHTLJSParser::LITERAL, i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::PropertyValueContext::IDENTIFIER() {
  return getTokens(CHTLJSParser::IDENTIFIER);
}

tree::TerminalNode* CHTLJSParser::PropertyValueContext::IDENTIFIER(size_t i) {
  return getToken(CHTLJSParser::IDENTIFIER, i);
}

std::vector<CHTLJSParser::FunctionCallContext *> CHTLJSParser::PropertyValueContext::functionCall() {
  return getRuleContexts<CHTLJSParser::FunctionCallContext>();
}

CHTLJSParser::FunctionCallContext* CHTLJSParser::PropertyValueContext::functionCall(size_t i) {
  return getRuleContext<CHTLJSParser::FunctionCallContext>(i);
}


size_t CHTLJSParser::PropertyValueContext::getRuleIndex() const {
  return CHTLJSParser::RulePropertyValue;
}

void CHTLJSParser::PropertyValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyValue(this);
}

void CHTLJSParser::PropertyValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyValue(this);
}

CHTLJSParser::PropertyValueContext* CHTLJSParser::propertyValue() {
  PropertyValueContext *_localctx = _tracker.createInstance<PropertyValueContext>(_ctx, getState());
  enterRule(_localctx, 212, CHTLJSParser::RulePropertyValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(998);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & ((1ULL << (CHTLJSParser::STRING - 65))
      | (1ULL << (CHTLJSParser::IDENTIFIER - 65))
      | (1ULL << (CHTLJSParser::LITERAL - 65)))) != 0)) {
      setState(996);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
      case 1: {
        setState(992);
        match(CHTLJSParser::STRING);
        break;
      }

      case 2: {
        setState(993);
        match(CHTLJSParser::LITERAL);
        break;
      }

      case 3: {
        setState(994);
        match(CHTLJSParser::IDENTIFIER);
        break;
      }

      case 4: {
        setState(995);
        functionCall();
        break;
      }

      default:
        break;
      }
      setState(1000);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodCallContext ------------------------------------------------------------------

CHTLJSParser::MethodCallContext::MethodCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::MethodCallContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::MethodCallContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::MethodCallContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

CHTLJSParser::ArgumentsContext* CHTLJSParser::MethodCallContext::arguments() {
  return getRuleContext<CHTLJSParser::ArgumentsContext>(0);
}

CHTLJSParser::MethodCallContext* CHTLJSParser::MethodCallContext::methodCall() {
  return getRuleContext<CHTLJSParser::MethodCallContext>(0);
}

tree::TerminalNode* CHTLJSParser::MethodCallContext::DOT() {
  return getToken(CHTLJSParser::DOT, 0);
}

tree::TerminalNode* CHTLJSParser::MethodCallContext::LBRACKET() {
  return getToken(CHTLJSParser::LBRACKET, 0);
}

CHTLJSParser::ExpressionContext* CHTLJSParser::MethodCallContext::expression() {
  return getRuleContext<CHTLJSParser::ExpressionContext>(0);
}

tree::TerminalNode* CHTLJSParser::MethodCallContext::RBRACKET() {
  return getToken(CHTLJSParser::RBRACKET, 0);
}


size_t CHTLJSParser::MethodCallContext::getRuleIndex() const {
  return CHTLJSParser::RuleMethodCall;
}

void CHTLJSParser::MethodCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodCall(this);
}

void CHTLJSParser::MethodCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodCall(this);
}


CHTLJSParser::MethodCallContext* CHTLJSParser::methodCall() {
   return methodCall(0);
}

CHTLJSParser::MethodCallContext* CHTLJSParser::methodCall(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CHTLJSParser::MethodCallContext *_localctx = _tracker.createInstance<MethodCallContext>(_ctx, parentState);
  CHTLJSParser::MethodCallContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 214;
  enterRecursionRule(_localctx, 214, CHTLJSParser::RuleMethodCall, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1002);
    match(CHTLJSParser::IDENTIFIER);
    setState(1003);
    match(CHTLJSParser::LPAREN);
    setState(1005);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
      setState(1004);
      arguments();
    }
    setState(1007);
    match(CHTLJSParser::RPAREN);
    _ctx->stop = _input->LT(-1);
    setState(1027);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(1025);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<MethodCallContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMethodCall);
          setState(1009);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(1010);
          match(CHTLJSParser::DOT);
          setState(1011);
          match(CHTLJSParser::IDENTIFIER);
          setState(1012);
          match(CHTLJSParser::LPAREN);
          setState(1014);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << CHTLJSParser::FUNCTION)
            | (1ULL << CHTLJSParser::NEW)
            | (1ULL << CHTLJSParser::THIS)
            | (1ULL << CHTLJSParser::SUPER)
            | (1ULL << CHTLJSParser::CLASS)
            | (1ULL << CHTLJSParser::TYPEOF)
            | (1ULL << CHTLJSParser::DELETE)
            | (1ULL << CHTLJSParser::VOID))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
            | (1ULL << (CHTLJSParser::LBRACE - 69))
            | (1ULL << (CHTLJSParser::LPAREN - 69))
            | (1ULL << (CHTLJSParser::LBRACKET - 69))
            | (1ULL << (CHTLJSParser::ASSIGN - 69))
            | (1ULL << (CHTLJSParser::BANG - 69))
            | (1ULL << (CHTLJSParser::TILDE - 69))
            | (1ULL << (CHTLJSParser::INC - 69))
            | (1ULL << (CHTLJSParser::DEC - 69))
            | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
            | (1ULL << (CHTLJSParser::ADD - 69))
            | (1ULL << (CHTLJSParser::SUB - 69)))) != 0)) {
            setState(1013);
            arguments();
          }
          setState(1016);
          match(CHTLJSParser::RPAREN);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<MethodCallContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMethodCall);
          setState(1017);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(1018);
          match(CHTLJSParser::LBRACKET);
          setState(1019);
          expression();
          setState(1020);
          match(CHTLJSParser::RBRACKET);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<MethodCallContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleMethodCall);
          setState(1022);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(1023);
          match(CHTLJSParser::DOT);
          setState(1024);
          match(CHTLJSParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(1029);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

CHTLJSParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::FunctionCallContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionCallContext::LPAREN() {
  return getToken(CHTLJSParser::LPAREN, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionCallContext::RPAREN() {
  return getToken(CHTLJSParser::RPAREN, 0);
}

std::vector<CHTLJSParser::FunctionArgContext *> CHTLJSParser::FunctionCallContext::functionArg() {
  return getRuleContexts<CHTLJSParser::FunctionArgContext>();
}

CHTLJSParser::FunctionArgContext* CHTLJSParser::FunctionCallContext::functionArg(size_t i) {
  return getRuleContext<CHTLJSParser::FunctionArgContext>(i);
}

std::vector<tree::TerminalNode *> CHTLJSParser::FunctionCallContext::COMMA() {
  return getTokens(CHTLJSParser::COMMA);
}

tree::TerminalNode* CHTLJSParser::FunctionCallContext::COMMA(size_t i) {
  return getToken(CHTLJSParser::COMMA, i);
}


size_t CHTLJSParser::FunctionCallContext::getRuleIndex() const {
  return CHTLJSParser::RuleFunctionCall;
}

void CHTLJSParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void CHTLJSParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

CHTLJSParser::FunctionCallContext* CHTLJSParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 216, CHTLJSParser::RuleFunctionCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1030);
    match(CHTLJSParser::IDENTIFIER);
    setState(1031);
    match(CHTLJSParser::LPAREN);
    setState(1040);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CHTLJSParser::NUMBER - 64))
      | (1ULL << (CHTLJSParser::STRING - 64))
      | (1ULL << (CHTLJSParser::IDENTIFIER - 64)))) != 0)) {
      setState(1032);
      functionArg();
      setState(1037);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CHTLJSParser::COMMA) {
        setState(1033);
        match(CHTLJSParser::COMMA);
        setState(1034);
        functionArg();
        setState(1039);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1042);
    match(CHTLJSParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgContext ------------------------------------------------------------------

CHTLJSParser::FunctionArgContext::FunctionArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::FunctionArgContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLJSParser::FunctionArgContext::ASSIGN() {
  return getToken(CHTLJSParser::ASSIGN, 0);
}

CHTLJSParser::ValueContext* CHTLJSParser::FunctionArgContext::value() {
  return getRuleContext<CHTLJSParser::ValueContext>(0);
}


size_t CHTLJSParser::FunctionArgContext::getRuleIndex() const {
  return CHTLJSParser::RuleFunctionArg;
}

void CHTLJSParser::FunctionArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArg(this);
}

void CHTLJSParser::FunctionArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArg(this);
}

CHTLJSParser::FunctionArgContext* CHTLJSParser::functionArg() {
  FunctionArgContext *_localctx = _tracker.createInstance<FunctionArgContext>(_ctx, getState());
  enterRule(_localctx, 218, CHTLJSParser::RuleFunctionArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1050);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1044);
      match(CHTLJSParser::IDENTIFIER);
      setState(1047);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CHTLJSParser::ASSIGN) {
        setState(1045);
        match(CHTLJSParser::ASSIGN);
        setState(1046);
        value();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1049);
      value();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

CHTLJSParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLJSParser::ValueContext::STRING() {
  return getToken(CHTLJSParser::STRING, 0);
}

tree::TerminalNode* CHTLJSParser::ValueContext::NUMBER() {
  return getToken(CHTLJSParser::NUMBER, 0);
}

tree::TerminalNode* CHTLJSParser::ValueContext::IDENTIFIER() {
  return getToken(CHTLJSParser::IDENTIFIER, 0);
}


size_t CHTLJSParser::ValueContext::getRuleIndex() const {
  return CHTLJSParser::RuleValue;
}

void CHTLJSParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void CHTLJSParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

CHTLJSParser::ValueContext* CHTLJSParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 220, CHTLJSParser::RuleValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1052);
    _la = _input->LA(1);
    if (!(((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CHTLJSParser::NUMBER - 64))
      | (1ULL << (CHTLJSParser::STRING - 64))
      | (1ULL << (CHTLJSParser::IDENTIFIER - 64)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceElementsContext ------------------------------------------------------------------

CHTLJSParser::SourceElementsContext::SourceElementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLJSParser::SourceElementContext *> CHTLJSParser::SourceElementsContext::sourceElement() {
  return getRuleContexts<CHTLJSParser::SourceElementContext>();
}

CHTLJSParser::SourceElementContext* CHTLJSParser::SourceElementsContext::sourceElement(size_t i) {
  return getRuleContext<CHTLJSParser::SourceElementContext>(i);
}


size_t CHTLJSParser::SourceElementsContext::getRuleIndex() const {
  return CHTLJSParser::RuleSourceElements;
}

void CHTLJSParser::SourceElementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceElements(this);
}

void CHTLJSParser::SourceElementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLJSListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceElements(this);
}

CHTLJSParser::SourceElementsContext* CHTLJSParser::sourceElements() {
  SourceElementsContext *_localctx = _tracker.createInstance<SourceElementsContext>(_ctx, getState());
  enterRule(_localctx, 222, CHTLJSParser::RuleSourceElements);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1055); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(1054);
      sourceElement();
      setState(1057); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLJSParser::CHTL_ANIMATE)
      | (1ULL << CHTLJSParser::FUNCTION)
      | (1ULL << CHTLJSParser::VAR)
      | (1ULL << CHTLJSParser::LET)
      | (1ULL << CHTLJSParser::CONST)
      | (1ULL << CHTLJSParser::IF)
      | (1ULL << CHTLJSParser::FOR)
      | (1ULL << CHTLJSParser::WHILE)
      | (1ULL << CHTLJSParser::DO)
      | (1ULL << CHTLJSParser::SWITCH)
      | (1ULL << CHTLJSParser::BREAK)
      | (1ULL << CHTLJSParser::CONTINUE)
      | (1ULL << CHTLJSParser::RETURN)
      | (1ULL << CHTLJSParser::TRY)
      | (1ULL << CHTLJSParser::THROW)
      | (1ULL << CHTLJSParser::NEW)
      | (1ULL << CHTLJSParser::THIS)
      | (1ULL << CHTLJSParser::SUPER)
      | (1ULL << CHTLJSParser::CLASS)
      | (1ULL << CHTLJSParser::TYPEOF)
      | (1ULL << CHTLJSParser::DELETE)
      | (1ULL << CHTLJSParser::VOID)
      | (1ULL << CHTLJSParser::WITH)
      | (1ULL << CHTLJSParser::DEBUGGER))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (CHTLJSParser::IDENTIFIER - 69))
      | (1ULL << (CHTLJSParser::LBRACE - 69))
      | (1ULL << (CHTLJSParser::LPAREN - 69))
      | (1ULL << (CHTLJSParser::LBRACKET - 69))
      | (1ULL << (CHTLJSParser::SEMICOLON - 69))
      | (1ULL << (CHTLJSParser::ASSIGN - 69))
      | (1ULL << (CHTLJSParser::BANG - 69))
      | (1ULL << (CHTLJSParser::TILDE - 69))
      | (1ULL << (CHTLJSParser::INC - 69))
      | (1ULL << (CHTLJSParser::DEC - 69))
      | (1ULL << (CHTLJSParser::ADD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::SUB_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MUL_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::DIV_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::MOD_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::POWER_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::LSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::RSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::URSHIFT_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::AND_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::OR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::XOR_ASSIGN - 69))
      | (1ULL << (CHTLJSParser::CHTL_DOUBLE_BRACE - 69))
      | (1ULL << (CHTLJSParser::ADD - 69))
      | (1ULL << (CHTLJSParser::SUB - 69)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CHTLJSParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 52: return callExpressionSempred(dynamic_cast<CallExpressionContext *>(context), predicateIndex);
    case 107: return methodCallSempred(dynamic_cast<MethodCallContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CHTLJSParser::callExpressionSempred(CallExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 12);
    case 1: return precpred(_ctx, 11);
    case 2: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

bool CHTLJSParser::methodCallSempred(MethodCallContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 3);
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CHTLJSParser::_decisionToDFA;
atn::PredictionContextCache CHTLJSParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CHTLJSParser::_atn;
std::vector<uint16_t> CHTLJSParser::_serializedATN;

std::vector<std::string> CHTLJSParser::_ruleNames = {
  "program", "sourceElement", "statement", "block", "statementList", "variableStatement", 
  "variableDeclarationList", "variableDeclaration", "assignmentExpression", 
  "assignmentOperator", "emptyStatement", "expressionStatement", "ifStatement", 
  "iterationStatement", "continueStatement", "breakStatement", "returnStatement", 
  "withStatement", "labelledStatement", "switchStatement", "caseBlock", 
  "caseClauses", "caseClause", "defaultClause", "throwStatement", "tryStatement", 
  "catchBlock", "finallyBlock", "debuggerStatement", "functionDeclaration", 
  "formalParameterList", "functionBody", "classDeclaration", "classBody", 
  "classElement", "methodDefinition", "expression", "conditionalExpression", 
  "logicalORExpression", "logicalANDExpression", "bitwiseORExpression", 
  "bitwiseXORExpression", "bitwiseANDExpression", "equalityExpression", 
  "relationalExpression", "shiftExpression", "additiveExpression", "multiplicativeExpression", 
  "unaryExpression", "unaryOperator", "postfixExpression", "leftHandSideExpression", 
  "callExpression", "arguments", "argumentList", "newExpression", "superProperty", 
  "functionExpression", "classExpression", "thisExpression", "arrayLiteral", 
  "elementList", "objectLiteral", "propertyDefinition", "parenthesizedExpression", 
  "arrowFunction", "arrowParameters", "arrowFunctionBody", "chtlStatement", 
  "chtlSelectorStatement", "chtlSelector", "selectorContent", "selectorType", 
  "selectorModifier", "chtlListenStatement", "chtlListenObject", "chtlListenEvents", 
  "chtlListenEvent", "eventType", "eventHandler", "chtlDelegateStatement", 
  "chtlDelegateObject", "chtlDelegateConfig", "chtlTargetConfig", "chtlSelectorArray", 
  "chtlEventConfig", "chtlAnimateStatement", "chtlAnimateObject", "chtlAnimateConfig", 
  "chtlAnimateProperty", "chtlDuration", "chtlEasing", "easingValue", "chtlBegin", 
  "chtlWhen", "chtlWhenClause", "chtlAt", "chtlEnd", "chtlLoop", "chtlDirection", 
  "directionValue", "chtlDelay", "chtlCallback", "chtlCssProperties", "chtlCssProperty", 
  "propertyName", "propertyValue", "methodCall", "functionCall", "functionArg", 
  "value", "sourceElements"
};

std::vector<std::string> CHTLJSParser::_literalNames = {
  "", "", "", "", "'script'", "'listen'", "'delegate'", "'animate'", "'at'", 
  "'when'", "'begin'", "'end'", "'loop'", "'direction'", "'delay'", "'callback'", 
  "'target'", "'easing'", "'duration'", "'function'", "'var'", "'let'", 
  "'const'", "'if'", "'else'", "'for'", "'while'", "'do'", "'switch'", "'case'", 
  "'default'", "'break'", "'continue'", "'return'", "'try'", "'catch'", 
  "'finally'", "'throw'", "'new'", "'this'", "'super'", "'class'", "'extends'", 
  "'static'", "'async'", "'await'", "'yield'", "'get'", "'set'", "'import'", 
  "'export'", "'from'", "'as'", "'of'", "'in'", "'instanceof'", "'typeof'", 
  "'delete'", "'void'", "'with'", "'debugger'", "'null'", "'true'", "'false'", 
  "", "", "", "", "", "", "'{'", "'}'", "'('", "')'", "'['", "']'", "';'", 
  "':'", "", "", "'-'", "'+'", "'*'", "'/'", "'%'", "'**'", "'>'", "'<'", 
  "'>='", "'<='", "'=='", "'!='", "'&&'", "'||'", "'!'", "'~'", "'\u003F'", 
  "'++'", "'--'", "'+='", "'-='", "'*='", "'/='", "'%='", "'**='", "'<<'", 
  "'>>'", "'>>>'", "'<<='", "'>>='", "'>>>='", "'&'", "'|'", "'^'", "'&='", 
  "'|='", "'^='", "'...'", "'=>'", "'{{'", "'}}'", "'->'", "", "'#'", "'.'", 
  "','"
};

std::vector<std::string> CHTLJSParser::_symbolicNames = {
  "", "WS", "COMMENT", "MULTILINE_COMMENT", "CHTL_SCRIPT", "CHTL_LISTEN", 
  "CHTL_DELEGATE", "CHTL_ANIMATE", "CHTL_AT", "CHTL_WHEN", "CHTL_BEGIN", 
  "CHTL_END", "CHTL_LOOP", "CHTL_DIRECTION", "CHTL_DELAY", "CHTL_CALLBACK", 
  "CHTL_TARGET", "CHTL_EASING", "CHTL_DURATION", "FUNCTION", "VAR", "LET", 
  "CONST", "IF", "ELSE", "FOR", "WHILE", "DO", "SWITCH", "CASE", "DEFAULT", 
  "BREAK", "CONTINUE", "RETURN", "TRY", "CATCH", "FINALLY", "THROW", "NEW", 
  "THIS", "SUPER", "CLASS", "EXTENDS", "STATIC", "ASYNC", "AWAIT", "YIELD", 
  "GET", "SET", "IMPORT", "EXPORT", "FROM", "AS", "OF", "IN", "INSTANCEOF", 
  "TYPEOF", "DELETE", "VOID", "WITH", "DEBUGGER", "NULL", "TRUE", "FALSE", 
  "NUMBER", "STRING", "REGEX", "REGEX_BODY", "REGEX_FLAGS", "IDENTIFIER", 
  "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "SEMICOLON", 
  "COLON", "EQUALS", "ASSIGN", "MINUS", "PLUS", "MUL", "DIV", "MOD", "POWER", 
  "GT", "LT", "GE", "LE", "EQUAL", "NOTEQUAL", "AND", "OR", "BANG", "TILDE", 
  "QUESTION", "INC", "DEC", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", 
  "MOD_ASSIGN", "POWER_ASSIGN", "LSHIFT", "RSHIFT", "URSHIFT", "LSHIFT_ASSIGN", 
  "RSHIFT_ASSIGN", "URSHIFT_ASSIGN", "BITAND", "BITOR", "CARET", "AND_ASSIGN", 
  "OR_ASSIGN", "XOR_ASSIGN", "ELLIPSIS", "ARROW", "CHTL_DOUBLE_BRACE", "CHTL_DOUBLE_BRACE_CLOSE", 
  "CHTL_ARROW", "LITERAL", "HASH", "DOT", "COMMA", "ADD", "SUB"
};

dfa::Vocabulary CHTLJSParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CHTLJSParser::_tokenNames;

CHTLJSParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		                std::string name = std::string(_vocabulary.getLiteralName(i));
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x81, 0x426, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 
       0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 
       0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 0x9, 0x1f, 0x4, 0x20, 
       0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 0x22, 0x4, 0x23, 
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 0x25, 0x4, 0x26, 
       0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 0x4, 0x29, 
       0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 0x2c, 
       0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
       0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 
       0x9, 0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 
       0x9, 0x35, 0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 
       0x9, 0x38, 0x4, 0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 
       0x9, 0x3b, 0x4, 0x3c, 0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 
       0x9, 0x3e, 0x4, 0x3f, 0x9, 0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 
       0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 
       0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 0x46, 0x9, 0x46, 0x4, 0x47, 
       0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 0x9, 0x49, 0x4, 0x4a, 
       0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 0x4c, 0x4, 0x4d, 
       0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 0x4, 0x50, 
       0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 0x53, 
       0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
       0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 
       0x9, 0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 
       0x9, 0x5c, 0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 
       0x9, 0x5f, 0x4, 0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 
       0x9, 0x62, 0x4, 0x63, 0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 
       0x9, 0x65, 0x4, 0x66, 0x9, 0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 
       0x9, 0x68, 0x4, 0x69, 0x9, 0x69, 0x4, 0x6a, 0x9, 0x6a, 0x4, 0x6b, 
       0x9, 0x6b, 0x4, 0x6c, 0x9, 0x6c, 0x4, 0x6d, 0x9, 0x6d, 0x4, 0x6e, 
       0x9, 0x6e, 0x4, 0x6f, 0x9, 0x6f, 0x4, 0x70, 0x9, 0x70, 0x4, 0x71, 
       0x9, 0x71, 0x3, 0x2, 0x7, 0x2, 0xe4, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 
       0xe7, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x5, 0x3, 0xef, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 
       0x100, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x104, 0xa, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x6, 0x6, 0x6, 0x109, 0xa, 0x6, 0xd, 0x6, 0xe, 
       0x6, 0x10a, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 
       0x8, 0x3, 0x8, 0x7, 0x8, 0x114, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x117, 
       0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x11c, 0xa, 0x9, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x122, 0xa, 0xa, 
       0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x5, 0xe, 0x132, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 
       0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
       0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 
       0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x146, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 
       0x5, 0xf, 0x14a, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x14e, 0xa, 
       0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x152, 0xa, 0xf, 0x3, 0x10, 0x3, 
       0x10, 0x5, 0x10, 0x156, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 
       0x3, 0x11, 0x5, 0x11, 0x15c, 0xa, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
       0x12, 0x3, 0x12, 0x5, 0x12, 0x162, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 
       0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
       0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 
       0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 
       0x5, 0x16, 0x178, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x17c, 
       0xa, 0x16, 0x5, 0x16, 0x17e, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 
       0x17, 0x6, 0x17, 0x183, 0xa, 0x17, 0xd, 0x17, 0xe, 0x17, 0x184, 0x3, 
       0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x18b, 0xa, 0x18, 
       0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x190, 0xa, 0x19, 0x3, 
       0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
       0x1b, 0x5, 0x1b, 0x199, 0xa, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x19c, 0xa, 
       0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 
       0x1b, 0x1a3, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
       0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 
       0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
       0x5, 0x1f, 0x1b5, 0xa, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
       0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x7, 0x20, 0x1bf, 
       0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 0x1c2, 0xb, 0x20, 0x3, 0x21, 0x5, 
       0x21, 0x1c5, 0xa, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 
       0x5, 0x22, 0x1cb, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x1cf, 
       0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x6, 0x23, 0x1d4, 0xa, 
       0x23, 0xd, 0x23, 0xe, 0x23, 0x1d5, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 
       0x5, 0x25, 0x1db, 0xa, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 
       0x25, 0x1e0, 0xa, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 
       0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x7, 0x26, 0x1ea, 0xa, 
       0x26, 0xc, 0x26, 0xe, 0x26, 0x1ed, 0xb, 0x26, 0x3, 0x27, 0x3, 0x27, 
       0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x1f5, 0xa, 
       0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x7, 0x28, 0x1fa, 0xa, 0x28, 
       0xc, 0x28, 0xe, 0x28, 0x1fd, 0xb, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 
       0x29, 0x7, 0x29, 0x202, 0xa, 0x29, 0xc, 0x29, 0xe, 0x29, 0x205, 0xb, 
       0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x7, 0x2a, 0x20a, 0xa, 0x2a, 
       0xc, 0x2a, 0xe, 0x2a, 0x20d, 0xb, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 
       0x2b, 0x7, 0x2b, 0x212, 0xa, 0x2b, 0xc, 0x2b, 0xe, 0x2b, 0x215, 0xb, 
       0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x7, 0x2c, 0x21a, 0xa, 0x2c, 
       0xc, 0x2c, 0xe, 0x2c, 0x21d, 0xb, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
       0x2d, 0x7, 0x2d, 0x222, 0xa, 0x2d, 0xc, 0x2d, 0xe, 0x2d, 0x225, 0xb, 
       0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x22a, 0xa, 0x2e, 
       0xc, 0x2e, 0xe, 0x2e, 0x22d, 0xb, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 
       0x2f, 0x7, 0x2f, 0x232, 0xa, 0x2f, 0xc, 0x2f, 0xe, 0x2f, 0x235, 0xb, 
       0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x7, 0x30, 0x23a, 0xa, 0x30, 
       0xc, 0x30, 0xe, 0x30, 0x23d, 0xb, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 
       0x31, 0x7, 0x31, 0x242, 0xa, 0x31, 0xc, 0x31, 0xe, 0x31, 0x245, 0xb, 
       0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x24b, 
       0xa, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 
       0x251, 0xa, 0x34, 0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 0x255, 0xa, 0x35, 
       0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x261, 0xa, 
       0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x266, 0xa, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x7, 0x36, 0x271, 0xa, 0x36, 0xc, 
       0x36, 0xe, 0x36, 0x274, 0xb, 0x36, 0x3, 0x37, 0x3, 0x37, 0x3, 0x38, 
       0x3, 0x38, 0x3, 0x38, 0x7, 0x38, 0x27b, 0xa, 0x38, 0xc, 0x38, 0xe, 
       0x38, 0x27e, 0xb, 0x38, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
       0x3, 0x39, 0x3, 0x39, 0x5, 0x39, 0x286, 0xa, 0x39, 0x3, 0x39, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
       0x39, 0x3, 0x39, 0x5, 0x39, 0x29d, 0xa, 0x39, 0x3, 0x3a, 0x3, 0x3a, 
       0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 
       0x5, 0x3a, 0x2a7, 0xa, 0x3a, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x2ab, 
       0xa, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x2af, 0xa, 0x3b, 0x3, 
       0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3c, 0x3, 
       0x3c, 0x5, 0x3c, 0x2b8, 0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 
       0x2bc, 0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x2c0, 0xa, 0x3c, 
       0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 
       0x3, 0x3e, 0x5, 0x3e, 0x2c9, 0xa, 0x3e, 0x5, 0x3e, 0x2cb, 0xa, 0x3e, 
       0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3f, 0x5, 0x3f, 0x2d0, 0xa, 0x3f, 0x3, 
       0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x2d5, 0xa, 0x3f, 0x3, 0x3f, 
       0x7, 0x3f, 0x2d8, 0xa, 0x3f, 0xc, 0x3f, 0xe, 0x3f, 0x2db, 0xb, 0x3f, 
       0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x2e1, 0xa, 
       0x40, 0xc, 0x40, 0xe, 0x40, 0x2e4, 0xb, 0x40, 0x5, 0x40, 0x2e6, 0xa, 
       0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 
       0x41, 0x5, 0x41, 0x2ee, 0xa, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 
       0x5, 0x41, 0x2f3, 0xa, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 
       0x41, 0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x2fb, 0xa, 0x41, 0x3, 0x41, 
       0x5, 0x41, 0x2fe, 0xa, 0x41, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 
       0x42, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x44, 0x3, 
       0x44, 0x3, 0x44, 0x5, 0x44, 0x30b, 0xa, 0x44, 0x3, 0x44, 0x5, 0x44, 
       0x30e, 0xa, 0x44, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 
       0x45, 0x5, 0x45, 0x315, 0xa, 0x45, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 
       0x3, 0x46, 0x5, 0x46, 0x31b, 0xa, 0x46, 0x3, 0x47, 0x3, 0x47, 0x3, 
       0x47, 0x3, 0x47, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 
       0x49, 0x5, 0x49, 0x326, 0xa, 0x49, 0x3, 0x49, 0x3, 0x49, 0x6, 0x49, 
       0x32a, 0xa, 0x49, 0xd, 0x49, 0xe, 0x49, 0x32b, 0x3, 0x4a, 0x3, 0x4a, 
       0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x6, 0x4b, 
       0x335, 0xa, 0x4b, 0xd, 0x4b, 0xe, 0x4b, 0x336, 0x5, 0x4b, 0x339, 
       0xa, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 
       0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x7, 0x4e, 0x349, 0xa, 0x4e, 0xc, 
       0x4e, 0xe, 0x4e, 0x34c, 0xb, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 
       0x3, 0x4f, 0x3, 0x50, 0x3, 0x50, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 
       0x5, 0x51, 0x357, 0xa, 0x51, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 
       0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 
       0x53, 0x3, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 
       0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x36c, 0xa, 0x55, 
       0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x7, 0x56, 0x372, 0xa, 
       0x56, 0xc, 0x56, 0xe, 0x56, 0x375, 0xb, 0x56, 0x3, 0x56, 0x3, 0x56, 
       0x3, 0x57, 0x3, 0x57, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 
       0x3, 0x58, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x3, 0x5a, 
       0x3, 0x5a, 0x3, 0x5a, 0x7, 0x5a, 0x387, 0xa, 0x5a, 0xc, 0x5a, 0xe, 
       0x5a, 0x38a, 0xb, 0x5a, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 
       0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x5, 0x5b, 
       0x395, 0xa, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 
       0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 0x3, 
       0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 
       0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x7, 
       0x60, 0x3ad, 0xa, 0x60, 0xc, 0x60, 0xe, 0x60, 0x3b0, 0xb, 0x60, 0x3, 
       0x60, 0x3, 0x60, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 
       0x61, 0x3, 0x61, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 
       0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 
       0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x65, 0x3, 0x65, 0x3, 
       0x65, 0x3, 0x65, 0x3, 0x66, 0x3, 0x66, 0x3, 0x67, 0x3, 0x67, 0x3, 
       0x67, 0x3, 0x67, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 
       0x69, 0x7, 0x69, 0x3d7, 0xa, 0x69, 0xc, 0x69, 0xe, 0x69, 0x3da, 0xb, 
       0x69, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 0x3, 
       0x6b, 0x3, 0x6b, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x7, 
       0x6c, 0x3e7, 0xa, 0x6c, 0xc, 0x6c, 0xe, 0x6c, 0x3ea, 0xb, 0x6c, 0x3, 
       0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x5, 0x6d, 0x3f0, 0xa, 0x6d, 
       0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 
       0x3, 0x6d, 0x5, 0x6d, 0x3f9, 0xa, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 
       0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 
       0x6d, 0x7, 0x6d, 0x404, 0xa, 0x6d, 0xc, 0x6d, 0xe, 0x6d, 0x407, 0xb, 
       0x6d, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x7, 
       0x6e, 0x40e, 0xa, 0x6e, 0xc, 0x6e, 0xe, 0x6e, 0x411, 0xb, 0x6e, 0x5, 
       0x6e, 0x413, 0xa, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6f, 0x3, 0x6f, 
       0x3, 0x6f, 0x5, 0x6f, 0x41a, 0xa, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x41d, 
       0xa, 0x6f, 0x3, 0x70, 0x3, 0x70, 0x3, 0x71, 0x6, 0x71, 0x422, 0xa, 
       0x71, 0xd, 0x71, 0xe, 0x71, 0x423, 0x3, 0x71, 0x2, 0x4, 0x6a, 0xd8, 
       0x72, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
       0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 
       0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 
       0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 
       0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 
       0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80, 0x82, 0x84, 
       0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 
       0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 0xb0, 
       0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 0xc0, 0xc2, 0xc4, 0xc6, 
       0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 
       0xde, 0xe0, 0x2, 0x11, 0x3, 0x2, 0x16, 0x18, 0x6, 0x2, 0x51, 0x51, 
       0x65, 0x6a, 0x6e, 0x70, 0x74, 0x76, 0x3, 0x2, 0x31, 0x32, 0x3, 0x2, 
       0x5c, 0x5d, 0x4, 0x2, 0x38, 0x39, 0x58, 0x5b, 0x3, 0x2, 0x6b, 0x6d, 
       0x3, 0x2, 0x80, 0x81, 0x3, 0x2, 0x54, 0x56, 0x6, 0x2, 0x3a, 0x3c, 
       0x60, 0x61, 0x63, 0x64, 0x80, 0x81, 0x3, 0x2, 0x63, 0x64, 0x4, 0x2, 
       0x7b, 0x7b, 0x7e, 0x7e, 0x3, 0x2, 0x7d, 0x7e, 0x4, 0x2, 0x43, 0x43, 
       0x47, 0x47, 0x4, 0x2, 0x42, 0x42, 0x52, 0x52, 0x4, 0x2, 0x42, 0x43, 
       0x47, 0x47, 0x2, 0x449, 0x2, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x4, 0xee, 
       0x3, 0x2, 0x2, 0x2, 0x6, 0xff, 0x3, 0x2, 0x2, 0x2, 0x8, 0x101, 0x3, 
       0x2, 0x2, 0x2, 0xa, 0x108, 0x3, 0x2, 0x2, 0x2, 0xc, 0x10c, 0x3, 0x2, 
       0x2, 0x2, 0xe, 0x110, 0x3, 0x2, 0x2, 0x2, 0x10, 0x118, 0x3, 0x2, 
       0x2, 0x2, 0x12, 0x121, 0x3, 0x2, 0x2, 0x2, 0x14, 0x123, 0x3, 0x2, 
       0x2, 0x2, 0x16, 0x125, 0x3, 0x2, 0x2, 0x2, 0x18, 0x127, 0x3, 0x2, 
       0x2, 0x2, 0x1a, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x151, 0x3, 0x2, 
       0x2, 0x2, 0x1e, 0x153, 0x3, 0x2, 0x2, 0x2, 0x20, 0x159, 0x3, 0x2, 
       0x2, 0x2, 0x22, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x24, 0x165, 0x3, 0x2, 
       0x2, 0x2, 0x26, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x28, 0x16f, 0x3, 0x2, 
       0x2, 0x2, 0x2a, 0x175, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x182, 0x3, 0x2, 
       0x2, 0x2, 0x2e, 0x186, 0x3, 0x2, 0x2, 0x2, 0x30, 0x18c, 0x3, 0x2, 
       0x2, 0x2, 0x32, 0x191, 0x3, 0x2, 0x2, 0x2, 0x34, 0x1a2, 0x3, 0x2, 
       0x2, 0x2, 0x36, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x38, 0x1aa, 0x3, 0x2, 
       0x2, 0x2, 0x3a, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x1b0, 0x3, 0x2, 
       0x2, 0x2, 0x3e, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x40, 0x1c4, 0x3, 0x2, 
       0x2, 0x2, 0x42, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1d3, 0x3, 0x2, 
       0x2, 0x2, 0x46, 0x1d7, 0x3, 0x2, 0x2, 0x2, 0x48, 0x1da, 0x3, 0x2, 
       0x2, 0x2, 0x4a, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x1ee, 0x3, 0x2, 
       0x2, 0x2, 0x4e, 0x1f6, 0x3, 0x2, 0x2, 0x2, 0x50, 0x1fe, 0x3, 0x2, 
       0x2, 0x2, 0x52, 0x206, 0x3, 0x2, 0x2, 0x2, 0x54, 0x20e, 0x3, 0x2, 
       0x2, 0x2, 0x56, 0x216, 0x3, 0x2, 0x2, 0x2, 0x58, 0x21e, 0x3, 0x2, 
       0x2, 0x2, 0x5a, 0x226, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x22e, 0x3, 0x2, 
       0x2, 0x2, 0x5e, 0x236, 0x3, 0x2, 0x2, 0x2, 0x60, 0x23e, 0x3, 0x2, 
       0x2, 0x2, 0x62, 0x24a, 0x3, 0x2, 0x2, 0x2, 0x64, 0x24c, 0x3, 0x2, 
       0x2, 0x2, 0x66, 0x24e, 0x3, 0x2, 0x2, 0x2, 0x68, 0x254, 0x3, 0x2, 
       0x2, 0x2, 0x6a, 0x260, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x275, 0x3, 0x2, 
       0x2, 0x2, 0x6e, 0x277, 0x3, 0x2, 0x2, 0x2, 0x70, 0x29c, 0x3, 0x2, 
       0x2, 0x2, 0x72, 0x2a6, 0x3, 0x2, 0x2, 0x2, 0x74, 0x2a8, 0x3, 0x2, 
       0x2, 0x2, 0x76, 0x2b5, 0x3, 0x2, 0x2, 0x2, 0x78, 0x2c3, 0x3, 0x2, 
       0x2, 0x2, 0x7a, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x2cf, 0x3, 0x2, 
       0x2, 0x2, 0x7e, 0x2dc, 0x3, 0x2, 0x2, 0x2, 0x80, 0x2fd, 0x3, 0x2, 
       0x2, 0x2, 0x82, 0x2ff, 0x3, 0x2, 0x2, 0x2, 0x84, 0x303, 0x3, 0x2, 
       0x2, 0x2, 0x86, 0x30d, 0x3, 0x2, 0x2, 0x2, 0x88, 0x314, 0x3, 0x2, 
       0x2, 0x2, 0x8a, 0x31a, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x31c, 0x3, 0x2, 
       0x2, 0x2, 0x8e, 0x320, 0x3, 0x2, 0x2, 0x2, 0x90, 0x325, 0x3, 0x2, 
       0x2, 0x2, 0x92, 0x32d, 0x3, 0x2, 0x2, 0x2, 0x94, 0x338, 0x3, 0x2, 
       0x2, 0x2, 0x96, 0x33a, 0x3, 0x2, 0x2, 0x2, 0x98, 0x341, 0x3, 0x2, 
       0x2, 0x2, 0x9a, 0x345, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x34d, 0x3, 0x2, 
       0x2, 0x2, 0x9e, 0x351, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x356, 0x3, 0x2, 
       0x2, 0x2, 0xa2, 0x358, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x35f, 0x3, 0x2, 
       0x2, 0x2, 0xa6, 0x363, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x367, 0x3, 0x2, 
       0x2, 0x2, 0xaa, 0x36d, 0x3, 0x2, 0x2, 0x2, 0xac, 0x378, 0x3, 0x2, 
       0x2, 0x2, 0xae, 0x37a, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x37f, 0x3, 0x2, 
       0x2, 0x2, 0xb2, 0x383, 0x3, 0x2, 0x2, 0x2, 0xb4, 0x394, 0x3, 0x2, 
       0x2, 0x2, 0xb6, 0x396, 0x3, 0x2, 0x2, 0x2, 0xb8, 0x39a, 0x3, 0x2, 
       0x2, 0x2, 0xba, 0x39e, 0x3, 0x2, 0x2, 0x2, 0xbc, 0x3a0, 0x3, 0x2, 
       0x2, 0x2, 0xbe, 0x3a6, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x3b3, 0x3, 0x2, 
       0x2, 0x2, 0xc2, 0x3b9, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x3bd, 0x3, 0x2, 
       0x2, 0x2, 0xc6, 0x3c3, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x3c7, 0x3, 0x2, 
       0x2, 0x2, 0xca, 0x3cb, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x3cd, 0x3, 0x2, 
       0x2, 0x2, 0xce, 0x3d1, 0x3, 0x2, 0x2, 0x2, 0xd0, 0x3d8, 0x3, 0x2, 
       0x2, 0x2, 0xd2, 0x3db, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x3e0, 0x3, 0x2, 
       0x2, 0x2, 0xd6, 0x3e8, 0x3, 0x2, 0x2, 0x2, 0xd8, 0x3eb, 0x3, 0x2, 
       0x2, 0x2, 0xda, 0x408, 0x3, 0x2, 0x2, 0x2, 0xdc, 0x41c, 0x3, 0x2, 
       0x2, 0x2, 0xde, 0x41e, 0x3, 0x2, 0x2, 0x2, 0xe0, 0x421, 0x3, 0x2, 
       0x2, 0x2, 0xe2, 0xe4, 0x5, 0x4, 0x3, 0x2, 0xe3, 0xe2, 0x3, 0x2, 0x2, 
       0x2, 0xe4, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe3, 0x3, 0x2, 0x2, 0x2, 
       0xe5, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe7, 
       0xe5, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x7, 0x2, 0x2, 0x3, 0xe9, 0x3, 
       0x3, 0x2, 0x2, 0x2, 0xea, 0xef, 0x5, 0x6, 0x4, 0x2, 0xeb, 0xef, 0x5, 
       0x3c, 0x1f, 0x2, 0xec, 0xef, 0x5, 0x42, 0x22, 0x2, 0xed, 0xef, 0x5, 
       0x8a, 0x46, 0x2, 0xee, 0xea, 0x3, 0x2, 0x2, 0x2, 0xee, 0xeb, 0x3, 
       0x2, 0x2, 0x2, 0xee, 0xec, 0x3, 0x2, 0x2, 0x2, 0xee, 0xed, 0x3, 0x2, 
       0x2, 0x2, 0xef, 0x5, 0x3, 0x2, 0x2, 0x2, 0xf0, 0x100, 0x5, 0x8, 0x5, 
       0x2, 0xf1, 0x100, 0x5, 0xc, 0x7, 0x2, 0xf2, 0x100, 0x5, 0x16, 0xc, 
       0x2, 0xf3, 0x100, 0x5, 0x18, 0xd, 0x2, 0xf4, 0x100, 0x5, 0x1a, 0xe, 
       0x2, 0xf5, 0x100, 0x5, 0x1c, 0xf, 0x2, 0xf6, 0x100, 0x5, 0x1e, 0x10, 
       0x2, 0xf7, 0x100, 0x5, 0x20, 0x11, 0x2, 0xf8, 0x100, 0x5, 0x22, 0x12, 
       0x2, 0xf9, 0x100, 0x5, 0x24, 0x13, 0x2, 0xfa, 0x100, 0x5, 0x26, 0x14, 
       0x2, 0xfb, 0x100, 0x5, 0x28, 0x15, 0x2, 0xfc, 0x100, 0x5, 0x32, 0x1a, 
       0x2, 0xfd, 0x100, 0x5, 0x34, 0x1b, 0x2, 0xfe, 0x100, 0x5, 0x3a, 0x1e, 
       0x2, 0xff, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xff, 0xf1, 0x3, 0x2, 0x2, 0x2, 
       0xff, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xff, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xff, 
       0xf4, 0x3, 0x2, 0x2, 0x2, 0xff, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xff, 0xf6, 
       0x3, 0x2, 0x2, 0x2, 0xff, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xff, 0xf8, 0x3, 
       0x2, 0x2, 0x2, 0xff, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfa, 0x3, 0x2, 
       0x2, 0x2, 0xff, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfc, 0x3, 0x2, 0x2, 
       0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfe, 0x3, 0x2, 0x2, 0x2, 
       0x100, 0x7, 0x3, 0x2, 0x2, 0x2, 0x101, 0x103, 0x7, 0x48, 0x2, 0x2, 
       0x102, 0x104, 0x5, 0xa, 0x6, 0x2, 0x103, 0x102, 0x3, 0x2, 0x2, 0x2, 
       0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 0x3, 0x2, 0x2, 0x2, 
       0x105, 0x106, 0x7, 0x49, 0x2, 0x2, 0x106, 0x9, 0x3, 0x2, 0x2, 0x2, 
       0x107, 0x109, 0x5, 0x6, 0x4, 0x2, 0x108, 0x107, 0x3, 0x2, 0x2, 0x2, 
       0x109, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x108, 0x3, 0x2, 0x2, 0x2, 
       0x10a, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10b, 0xb, 0x3, 0x2, 0x2, 0x2, 
       0x10c, 0x10d, 0x9, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x5, 0xe, 0x8, 0x2, 
       0x10e, 0x10f, 0x7, 0x4e, 0x2, 0x2, 0x10f, 0xd, 0x3, 0x2, 0x2, 0x2, 
       0x110, 0x115, 0x5, 0x10, 0x9, 0x2, 0x111, 0x112, 0x7, 0x7f, 0x2, 
       0x2, 0x112, 0x114, 0x5, 0x10, 0x9, 0x2, 0x113, 0x111, 0x3, 0x2, 0x2, 
       0x2, 0x114, 0x117, 0x3, 0x2, 0x2, 0x2, 0x115, 0x113, 0x3, 0x2, 0x2, 
       0x2, 0x115, 0x116, 0x3, 0x2, 0x2, 0x2, 0x116, 0xf, 0x3, 0x2, 0x2, 
       0x2, 0x117, 0x115, 0x3, 0x2, 0x2, 0x2, 0x118, 0x11b, 0x7, 0x47, 0x2, 
       0x2, 0x119, 0x11a, 0x7, 0x51, 0x2, 0x2, 0x11a, 0x11c, 0x5, 0x12, 
       0xa, 0x2, 0x11b, 0x119, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11c, 0x3, 0x2, 
       0x2, 0x2, 0x11c, 0x11, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x122, 0x5, 0x4c, 
       0x27, 0x2, 0x11e, 0x11f, 0x5, 0x14, 0xb, 0x2, 0x11f, 0x120, 0x5, 
       0x12, 0xa, 0x2, 0x120, 0x122, 0x3, 0x2, 0x2, 0x2, 0x121, 0x11d, 0x3, 
       0x2, 0x2, 0x2, 0x121, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x122, 0x13, 0x3, 
       0x2, 0x2, 0x2, 0x123, 0x124, 0x9, 0x3, 0x2, 0x2, 0x124, 0x15, 0x3, 
       0x2, 0x2, 0x2, 0x125, 0x126, 0x7, 0x4e, 0x2, 0x2, 0x126, 0x17, 0x3, 
       0x2, 0x2, 0x2, 0x127, 0x128, 0x5, 0x4a, 0x26, 0x2, 0x128, 0x129, 
       0x7, 0x4e, 0x2, 0x2, 0x129, 0x19, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 
       0x7, 0x19, 0x2, 0x2, 0x12b, 0x12c, 0x7, 0x4a, 0x2, 0x2, 0x12c, 0x12d, 
       0x5, 0x4a, 0x26, 0x2, 0x12d, 0x12e, 0x7, 0x4b, 0x2, 0x2, 0x12e, 0x131, 
       0x5, 0x6, 0x4, 0x2, 0x12f, 0x130, 0x7, 0x1a, 0x2, 0x2, 0x130, 0x132, 
       0x5, 0x6, 0x4, 0x2, 0x131, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x131, 0x132, 
       0x3, 0x2, 0x2, 0x2, 0x132, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x133, 0x134, 
       0x7, 0x1d, 0x2, 0x2, 0x134, 0x135, 0x5, 0x6, 0x4, 0x2, 0x135, 0x136, 
       0x7, 0x1c, 0x2, 0x2, 0x136, 0x137, 0x7, 0x4a, 0x2, 0x2, 0x137, 0x138, 
       0x5, 0x4a, 0x26, 0x2, 0x138, 0x139, 0x7, 0x4b, 0x2, 0x2, 0x139, 0x13a, 
       0x7, 0x4e, 0x2, 0x2, 0x13a, 0x152, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13c, 
       0x7, 0x1c, 0x2, 0x2, 0x13c, 0x13d, 0x7, 0x4a, 0x2, 0x2, 0x13d, 0x13e, 
       0x5, 0x4a, 0x26, 0x2, 0x13e, 0x13f, 0x7, 0x4b, 0x2, 0x2, 0x13f, 0x140, 
       0x5, 0x6, 0x4, 0x2, 0x140, 0x152, 0x3, 0x2, 0x2, 0x2, 0x141, 0x142, 
       0x7, 0x1b, 0x2, 0x2, 0x142, 0x145, 0x7, 0x4a, 0x2, 0x2, 0x143, 0x146, 
       0x5, 0x4a, 0x26, 0x2, 0x144, 0x146, 0x5, 0xc, 0x7, 0x2, 0x145, 0x143, 
       0x3, 0x2, 0x2, 0x2, 0x145, 0x144, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 
       0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 0x2, 0x147, 0x149, 
       0x7, 0x4e, 0x2, 0x2, 0x148, 0x14a, 0x5, 0x4a, 0x26, 0x2, 0x149, 0x148, 
       0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 
       0x3, 0x2, 0x2, 0x2, 0x14b, 0x14d, 0x7, 0x4e, 0x2, 0x2, 0x14c, 0x14e, 
       0x5, 0x4a, 0x26, 0x2, 0x14d, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14e, 
       0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x14f, 0x150, 
       0x7, 0x4b, 0x2, 0x2, 0x150, 0x152, 0x5, 0x6, 0x4, 0x2, 0x151, 0x133, 
       0x3, 0x2, 0x2, 0x2, 0x151, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x151, 0x141, 
       0x3, 0x2, 0x2, 0x2, 0x152, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x153, 0x155, 
       0x7, 0x22, 0x2, 0x2, 0x154, 0x156, 0x7, 0x47, 0x2, 0x2, 0x155, 0x154, 
       0x3, 0x2, 0x2, 0x2, 0x155, 0x156, 0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 
       0x3, 0x2, 0x2, 0x2, 0x157, 0x158, 0x7, 0x4e, 0x2, 0x2, 0x158, 0x1f, 
       0x3, 0x2, 0x2, 0x2, 0x159, 0x15b, 0x7, 0x21, 0x2, 0x2, 0x15a, 0x15c, 
       0x7, 0x47, 0x2, 0x2, 0x15b, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 
       0x3, 0x2, 0x2, 0x2, 0x15c, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x15e, 
       0x7, 0x4e, 0x2, 0x2, 0x15e, 0x21, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x161, 
       0x7, 0x23, 0x2, 0x2, 0x160, 0x162, 0x5, 0x4a, 0x26, 0x2, 0x161, 0x160, 
       0x3, 0x2, 0x2, 0x2, 0x161, 0x162, 0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 
       0x3, 0x2, 0x2, 0x2, 0x163, 0x164, 0x7, 0x4e, 0x2, 0x2, 0x164, 0x23, 
       0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 0x7, 0x3d, 0x2, 0x2, 0x166, 0x167, 
       0x7, 0x4a, 0x2, 0x2, 0x167, 0x168, 0x5, 0x4a, 0x26, 0x2, 0x168, 0x169, 
       0x7, 0x4b, 0x2, 0x2, 0x169, 0x16a, 0x5, 0x6, 0x4, 0x2, 0x16a, 0x25, 
       0x3, 0x2, 0x2, 0x2, 0x16b, 0x16c, 0x7, 0x47, 0x2, 0x2, 0x16c, 0x16d, 
       0x7, 0x4f, 0x2, 0x2, 0x16d, 0x16e, 0x5, 0x6, 0x4, 0x2, 0x16e, 0x27, 
       0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x7, 0x1e, 0x2, 0x2, 0x170, 0x171, 
       0x7, 0x4a, 0x2, 0x2, 0x171, 0x172, 0x5, 0x4a, 0x26, 0x2, 0x172, 0x173, 
       0x7, 0x4b, 0x2, 0x2, 0x173, 0x174, 0x5, 0x2a, 0x16, 0x2, 0x174, 0x29, 
       0x3, 0x2, 0x2, 0x2, 0x175, 0x177, 0x7, 0x48, 0x2, 0x2, 0x176, 0x178, 
       0x5, 0x2c, 0x17, 0x2, 0x177, 0x176, 0x3, 0x2, 0x2, 0x2, 0x177, 0x178, 
       0x3, 0x2, 0x2, 0x2, 0x178, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17b, 
       0x5, 0x30, 0x19, 0x2, 0x17a, 0x17c, 0x5, 0x2c, 0x17, 0x2, 0x17b, 
       0x17a, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x17c, 
       0x17e, 0x3, 0x2, 0x2, 0x2, 0x17d, 0x179, 0x3, 0x2, 0x2, 0x2, 0x17d, 
       0x17e, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x17f, 
       0x180, 0x7, 0x49, 0x2, 0x2, 0x180, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x181, 
       0x183, 0x5, 0x2e, 0x18, 0x2, 0x182, 0x181, 0x3, 0x2, 0x2, 0x2, 0x183, 
       0x184, 0x3, 0x2, 0x2, 0x2, 0x184, 0x182, 0x3, 0x2, 0x2, 0x2, 0x184, 
       0x185, 0x3, 0x2, 0x2, 0x2, 0x185, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x186, 
       0x187, 0x7, 0x1f, 0x2, 0x2, 0x187, 0x188, 0x5, 0x4a, 0x26, 0x2, 0x188, 
       0x18a, 0x7, 0x4f, 0x2, 0x2, 0x189, 0x18b, 0x5, 0xa, 0x6, 0x2, 0x18a, 
       0x189, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x18b, 
       0x2f, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x18d, 0x7, 0x20, 0x2, 0x2, 0x18d, 
       0x18f, 0x7, 0x4f, 0x2, 0x2, 0x18e, 0x190, 0x5, 0xa, 0x6, 0x2, 0x18f, 
       0x18e, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x190, 0x3, 0x2, 0x2, 0x2, 0x190, 
       0x31, 0x3, 0x2, 0x2, 0x2, 0x191, 0x192, 0x7, 0x27, 0x2, 0x2, 0x192, 
       0x193, 0x5, 0x4a, 0x26, 0x2, 0x193, 0x194, 0x7, 0x4e, 0x2, 0x2, 0x194, 
       0x33, 0x3, 0x2, 0x2, 0x2, 0x195, 0x196, 0x7, 0x24, 0x2, 0x2, 0x196, 
       0x198, 0x5, 0x8, 0x5, 0x2, 0x197, 0x199, 0x5, 0x36, 0x1c, 0x2, 0x198, 
       0x197, 0x3, 0x2, 0x2, 0x2, 0x198, 0x199, 0x3, 0x2, 0x2, 0x2, 0x199, 
       0x19b, 0x3, 0x2, 0x2, 0x2, 0x19a, 0x19c, 0x5, 0x38, 0x1d, 0x2, 0x19b, 
       0x19a, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x19c, 
       0x1a3, 0x3, 0x2, 0x2, 0x2, 0x19d, 0x19e, 0x7, 0x24, 0x2, 0x2, 0x19e, 
       0x19f, 0x5, 0x8, 0x5, 0x2, 0x19f, 0x1a0, 0x5, 0x36, 0x1c, 0x2, 0x1a0, 
       0x1a1, 0x5, 0x38, 0x1d, 0x2, 0x1a1, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a2, 
       0x195, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x1a3, 
       0x35, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 0x7, 0x25, 0x2, 0x2, 0x1a5, 
       0x1a6, 0x7, 0x4a, 0x2, 0x2, 0x1a6, 0x1a7, 0x7, 0x47, 0x2, 0x2, 0x1a7, 
       0x1a8, 0x7, 0x4b, 0x2, 0x2, 0x1a8, 0x1a9, 0x5, 0x8, 0x5, 0x2, 0x1a9, 
       0x37, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1ab, 0x7, 0x26, 0x2, 0x2, 0x1ab, 
       0x1ac, 0x5, 0x8, 0x5, 0x2, 0x1ac, 0x39, 0x3, 0x2, 0x2, 0x2, 0x1ad, 
       0x1ae, 0x7, 0x3e, 0x2, 0x2, 0x1ae, 0x1af, 0x7, 0x4e, 0x2, 0x2, 0x1af, 
       0x3b, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1b1, 0x7, 0x15, 0x2, 0x2, 0x1b1, 
       0x1b2, 0x7, 0x47, 0x2, 0x2, 0x1b2, 0x1b4, 0x7, 0x4a, 0x2, 0x2, 0x1b3, 
       0x1b5, 0x5, 0x3e, 0x20, 0x2, 0x1b4, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b4, 
       0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1b6, 
       0x1b7, 0x7, 0x4b, 0x2, 0x2, 0x1b7, 0x1b8, 0x7, 0x48, 0x2, 0x2, 0x1b8, 
       0x1b9, 0x5, 0x40, 0x21, 0x2, 0x1b9, 0x1ba, 0x7, 0x49, 0x2, 0x2, 0x1ba, 
       0x3d, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1c0, 0x7, 0x47, 0x2, 0x2, 0x1bc, 
       0x1bd, 0x7, 0x7f, 0x2, 0x2, 0x1bd, 0x1bf, 0x7, 0x47, 0x2, 0x2, 0x1be, 
       0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c0, 
       0x1be, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c1, 
       0x3f, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c3, 
       0x1c5, 0x5, 0xe0, 0x71, 0x2, 0x1c4, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x1c4, 
       0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x41, 0x3, 0x2, 0x2, 0x2, 0x1c6, 
       0x1c7, 0x7, 0x2b, 0x2, 0x2, 0x1c7, 0x1ca, 0x7, 0x47, 0x2, 0x2, 0x1c8, 
       0x1c9, 0x7, 0x2c, 0x2, 0x2, 0x1c9, 0x1cb, 0x7, 0x47, 0x2, 0x2, 0x1ca, 
       0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1cb, 
       0x1cc, 0x3, 0x2, 0x2, 0x2, 0x1cc, 0x1ce, 0x7, 0x48, 0x2, 0x2, 0x1cd, 
       0x1cf, 0x5, 0x44, 0x23, 0x2, 0x1ce, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1ce, 
       0x1cf, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d0, 
       0x1d1, 0x7, 0x49, 0x2, 0x2, 0x1d1, 0x43, 0x3, 0x2, 0x2, 0x2, 0x1d2, 
       0x1d4, 0x5, 0x46, 0x24, 0x2, 0x1d3, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d4, 
       0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d3, 0x3, 0x2, 0x2, 0x2, 0x1d5, 
       0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1d6, 0x45, 0x3, 0x2, 0x2, 0x2, 0x1d7, 
       0x1d8, 0x5, 0x48, 0x25, 0x2, 0x1d8, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1d9, 
       0x1db, 0x9, 0x4, 0x2, 0x2, 0x1da, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1da, 
       0x1db, 0x3, 0x2, 0x2, 0x2, 0x1db, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1dc, 
       0x1dd, 0x7, 0x47, 0x2, 0x2, 0x1dd, 0x1df, 0x7, 0x4a, 0x2, 0x2, 0x1de, 
       0x1e0, 0x5, 0x3e, 0x20, 0x2, 0x1df, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1df, 
       0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1e1, 
       0x1e2, 0x7, 0x4b, 0x2, 0x2, 0x1e2, 0x1e3, 0x7, 0x48, 0x2, 0x2, 0x1e3, 
       0x1e4, 0x5, 0x40, 0x21, 0x2, 0x1e4, 0x1e5, 0x7, 0x49, 0x2, 0x2, 0x1e5, 
       0x49, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1eb, 0x5, 0x12, 0xa, 0x2, 0x1e7, 
       0x1e8, 0x7, 0x7f, 0x2, 0x2, 0x1e8, 0x1ea, 0x5, 0x12, 0xa, 0x2, 0x1e9, 
       0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x1eb, 
       0x1e9, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x1ec, 
       0x4b, 0x3, 0x2, 0x2, 0x2, 0x1ed, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x1ee, 
       0x1f4, 0x5, 0x4e, 0x28, 0x2, 0x1ef, 0x1f0, 0x7, 0x62, 0x2, 0x2, 0x1f0, 
       0x1f1, 0x5, 0x12, 0xa, 0x2, 0x1f1, 0x1f2, 0x7, 0x4f, 0x2, 0x2, 0x1f2, 
       0x1f3, 0x5, 0x12, 0xa, 0x2, 0x1f3, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f4, 
       0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1f4, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f5, 
       0x4d, 0x3, 0x2, 0x2, 0x2, 0x1f6, 0x1fb, 0x5, 0x50, 0x29, 0x2, 0x1f7, 
       0x1f8, 0x7, 0x5f, 0x2, 0x2, 0x1f8, 0x1fa, 0x5, 0x50, 0x29, 0x2, 0x1f9, 
       0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1fb, 
       0x1f9, 0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fc, 
       0x4f, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fb, 0x3, 0x2, 0x2, 0x2, 0x1fe, 
       0x203, 0x5, 0x52, 0x2a, 0x2, 0x1ff, 0x200, 0x7, 0x5e, 0x2, 0x2, 0x200, 
       0x202, 0x5, 0x52, 0x2a, 0x2, 0x201, 0x1ff, 0x3, 0x2, 0x2, 0x2, 0x202, 
       0x205, 0x3, 0x2, 0x2, 0x2, 0x203, 0x201, 0x3, 0x2, 0x2, 0x2, 0x203, 
       0x204, 0x3, 0x2, 0x2, 0x2, 0x204, 0x51, 0x3, 0x2, 0x2, 0x2, 0x205, 
       0x203, 0x3, 0x2, 0x2, 0x2, 0x206, 0x20b, 0x5, 0x54, 0x2b, 0x2, 0x207, 
       0x208, 0x7, 0x72, 0x2, 0x2, 0x208, 0x20a, 0x5, 0x54, 0x2b, 0x2, 0x209, 
       0x207, 0x3, 0x2, 0x2, 0x2, 0x20a, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20b, 
       0x209, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x20c, 0x3, 0x2, 0x2, 0x2, 0x20c, 
       0x53, 0x3, 0x2, 0x2, 0x2, 0x20d, 0x20b, 0x3, 0x2, 0x2, 0x2, 0x20e, 
       0x213, 0x5, 0x56, 0x2c, 0x2, 0x20f, 0x210, 0x7, 0x73, 0x2, 0x2, 0x210, 
       0x212, 0x5, 0x56, 0x2c, 0x2, 0x211, 0x20f, 0x3, 0x2, 0x2, 0x2, 0x212, 
       0x215, 0x3, 0x2, 0x2, 0x2, 0x213, 0x211, 0x3, 0x2, 0x2, 0x2, 0x213, 
       0x214, 0x3, 0x2, 0x2, 0x2, 0x214, 0x55, 0x3, 0x2, 0x2, 0x2, 0x215, 
       0x213, 0x3, 0x2, 0x2, 0x2, 0x216, 0x21b, 0x5, 0x58, 0x2d, 0x2, 0x217, 
       0x218, 0x7, 0x71, 0x2, 0x2, 0x218, 0x21a, 0x5, 0x58, 0x2d, 0x2, 0x219, 
       0x217, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21b, 
       0x219, 0x3, 0x2, 0x2, 0x2, 0x21b, 0x21c, 0x3, 0x2, 0x2, 0x2, 0x21c, 
       0x57, 0x3, 0x2, 0x2, 0x2, 0x21d, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x21e, 
       0x223, 0x5, 0x5a, 0x2e, 0x2, 0x21f, 0x220, 0x9, 0x5, 0x2, 0x2, 0x220, 
       0x222, 0x5, 0x5a, 0x2e, 0x2, 0x221, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x222, 
       0x225, 0x3, 0x2, 0x2, 0x2, 0x223, 0x221, 0x3, 0x2, 0x2, 0x2, 0x223, 
       0x224, 0x3, 0x2, 0x2, 0x2, 0x224, 0x59, 0x3, 0x2, 0x2, 0x2, 0x225, 
       0x223, 0x3, 0x2, 0x2, 0x2, 0x226, 0x22b, 0x5, 0x5c, 0x2f, 0x2, 0x227, 
       0x228, 0x9, 0x6, 0x2, 0x2, 0x228, 0x22a, 0x5, 0x5c, 0x2f, 0x2, 0x229, 
       0x227, 0x3, 0x2, 0x2, 0x2, 0x22a, 0x22d, 0x3, 0x2, 0x2, 0x2, 0x22b, 
       0x229, 0x3, 0x2, 0x2, 0x2, 0x22b, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x22c, 
       0x5b, 0x3, 0x2, 0x2, 0x2, 0x22d, 0x22b, 0x3, 0x2, 0x2, 0x2, 0x22e, 
       0x233, 0x5, 0x5e, 0x30, 0x2, 0x22f, 0x230, 0x9, 0x7, 0x2, 0x2, 0x230, 
       0x232, 0x5, 0x5e, 0x30, 0x2, 0x231, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x232, 
       0x235, 0x3, 0x2, 0x2, 0x2, 0x233, 0x231, 0x3, 0x2, 0x2, 0x2, 0x233, 
       0x234, 0x3, 0x2, 0x2, 0x2, 0x234, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x235, 
       0x233, 0x3, 0x2, 0x2, 0x2, 0x236, 0x23b, 0x5, 0x60, 0x31, 0x2, 0x237, 
       0x238, 0x9, 0x8, 0x2, 0x2, 0x238, 0x23a, 0x5, 0x5e, 0x30, 0x2, 0x239, 
       0x237, 0x3, 0x2, 0x2, 0x2, 0x23a, 0x23d, 0x3, 0x2, 0x2, 0x2, 0x23b, 
       0x239, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x23c, 0x3, 0x2, 0x2, 0x2, 0x23c, 
       0x5f, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x23e, 
       0x243, 0x5, 0x62, 0x32, 0x2, 0x23f, 0x240, 0x9, 0x9, 0x2, 0x2, 0x240, 
       0x242, 0x5, 0x62, 0x32, 0x2, 0x241, 0x23f, 0x3, 0x2, 0x2, 0x2, 0x242, 
       0x245, 0x3, 0x2, 0x2, 0x2, 0x243, 0x241, 0x3, 0x2, 0x2, 0x2, 0x243, 
       0x244, 0x3, 0x2, 0x2, 0x2, 0x244, 0x61, 0x3, 0x2, 0x2, 0x2, 0x245, 
       0x243, 0x3, 0x2, 0x2, 0x2, 0x246, 0x247, 0x5, 0x64, 0x33, 0x2, 0x247, 
       0x248, 0x5, 0x62, 0x32, 0x2, 0x248, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x249, 
       0x24b, 0x5, 0x66, 0x34, 0x2, 0x24a, 0x246, 0x3, 0x2, 0x2, 0x2, 0x24a, 
       0x249, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x63, 0x3, 0x2, 0x2, 0x2, 0x24c, 
       0x24d, 0x9, 0xa, 0x2, 0x2, 0x24d, 0x65, 0x3, 0x2, 0x2, 0x2, 0x24e, 
       0x250, 0x5, 0x68, 0x35, 0x2, 0x24f, 0x251, 0x9, 0xb, 0x2, 0x2, 0x250, 
       0x24f, 0x3, 0x2, 0x2, 0x2, 0x250, 0x251, 0x3, 0x2, 0x2, 0x2, 0x251, 
       0x67, 0x3, 0x2, 0x2, 0x2, 0x252, 0x255, 0x5, 0x6a, 0x36, 0x2, 0x253, 
       0x255, 0x5, 0x70, 0x39, 0x2, 0x254, 0x252, 0x3, 0x2, 0x2, 0x2, 0x254, 
       0x253, 0x3, 0x2, 0x2, 0x2, 0x255, 0x69, 0x3, 0x2, 0x2, 0x2, 0x256, 
       0x257, 0x8, 0x36, 0x1, 0x2, 0x257, 0x261, 0x5, 0x72, 0x3a, 0x2, 0x258, 
       0x261, 0x5, 0x74, 0x3b, 0x2, 0x259, 0x261, 0x5, 0x76, 0x3c, 0x2, 
       0x25a, 0x261, 0x7, 0x47, 0x2, 0x2, 0x25b, 0x261, 0x5, 0x78, 0x3d, 
       0x2, 0x25c, 0x261, 0x5, 0x7a, 0x3e, 0x2, 0x25d, 0x261, 0x5, 0x7e, 
       0x40, 0x2, 0x25e, 0x261, 0x5, 0x82, 0x42, 0x2, 0x25f, 0x261, 0x5, 
       0x70, 0x39, 0x2, 0x260, 0x256, 0x3, 0x2, 0x2, 0x2, 0x260, 0x258, 
       0x3, 0x2, 0x2, 0x2, 0x260, 0x259, 0x3, 0x2, 0x2, 0x2, 0x260, 0x25a, 
       0x3, 0x2, 0x2, 0x2, 0x260, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x260, 0x25c, 
       0x3, 0x2, 0x2, 0x2, 0x260, 0x25d, 0x3, 0x2, 0x2, 0x2, 0x260, 0x25e, 
       0x3, 0x2, 0x2, 0x2, 0x260, 0x25f, 0x3, 0x2, 0x2, 0x2, 0x261, 0x272, 
       0x3, 0x2, 0x2, 0x2, 0x262, 0x263, 0xc, 0xe, 0x2, 0x2, 0x263, 0x265, 
       0x7, 0x4a, 0x2, 0x2, 0x264, 0x266, 0x5, 0x6c, 0x37, 0x2, 0x265, 0x264, 
       0x3, 0x2, 0x2, 0x2, 0x265, 0x266, 0x3, 0x2, 0x2, 0x2, 0x266, 0x267, 
       0x3, 0x2, 0x2, 0x2, 0x267, 0x271, 0x7, 0x4b, 0x2, 0x2, 0x268, 0x269, 
       0xc, 0xd, 0x2, 0x2, 0x269, 0x26a, 0x7, 0x4c, 0x2, 0x2, 0x26a, 0x26b, 
       0x5, 0x4a, 0x26, 0x2, 0x26b, 0x26c, 0x7, 0x4d, 0x2, 0x2, 0x26c, 0x271, 
       0x3, 0x2, 0x2, 0x2, 0x26d, 0x26e, 0xc, 0xc, 0x2, 0x2, 0x26e, 0x26f, 
       0x7, 0x7e, 0x2, 0x2, 0x26f, 0x271, 0x7, 0x47, 0x2, 0x2, 0x270, 0x262, 
       0x3, 0x2, 0x2, 0x2, 0x270, 0x268, 0x3, 0x2, 0x2, 0x2, 0x270, 0x26d, 
       0x3, 0x2, 0x2, 0x2, 0x271, 0x274, 0x3, 0x2, 0x2, 0x2, 0x272, 0x270, 
       0x3, 0x2, 0x2, 0x2, 0x272, 0x273, 0x3, 0x2, 0x2, 0x2, 0x273, 0x6b, 
       0x3, 0x2, 0x2, 0x2, 0x274, 0x272, 0x3, 0x2, 0x2, 0x2, 0x275, 0x276, 
       0x5, 0x6e, 0x38, 0x2, 0x276, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x277, 0x27c, 
       0x5, 0x12, 0xa, 0x2, 0x278, 0x279, 0x7, 0x7f, 0x2, 0x2, 0x279, 0x27b, 
       0x5, 0x12, 0xa, 0x2, 0x27a, 0x278, 0x3, 0x2, 0x2, 0x2, 0x27b, 0x27e, 
       0x3, 0x2, 0x2, 0x2, 0x27c, 0x27a, 0x3, 0x2, 0x2, 0x2, 0x27c, 0x27d, 
       0x3, 0x2, 0x2, 0x2, 0x27d, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x27c, 
       0x3, 0x2, 0x2, 0x2, 0x27f, 0x280, 0x7, 0x28, 0x2, 0x2, 0x280, 0x29d, 
       0x5, 0x70, 0x39, 0x2, 0x281, 0x282, 0x7, 0x28, 0x2, 0x2, 0x282, 0x283, 
       0x5, 0x70, 0x39, 0x2, 0x283, 0x285, 0x7, 0x4a, 0x2, 0x2, 0x284, 0x286, 
       0x5, 0x6c, 0x37, 0x2, 0x285, 0x284, 0x3, 0x2, 0x2, 0x2, 0x285, 0x286, 
       0x3, 0x2, 0x2, 0x2, 0x286, 0x287, 0x3, 0x2, 0x2, 0x2, 0x287, 0x288, 
       0x7, 0x4b, 0x2, 0x2, 0x288, 0x29d, 0x3, 0x2, 0x2, 0x2, 0x289, 0x28a, 
       0x7, 0x28, 0x2, 0x2, 0x28a, 0x28b, 0x5, 0x70, 0x39, 0x2, 0x28b, 0x28c, 
       0x7, 0x4c, 0x2, 0x2, 0x28c, 0x28d, 0x5, 0x4a, 0x26, 0x2, 0x28d, 0x28e, 
       0x7, 0x4d, 0x2, 0x2, 0x28e, 0x29d, 0x3, 0x2, 0x2, 0x2, 0x28f, 0x290, 
       0x7, 0x28, 0x2, 0x2, 0x290, 0x291, 0x5, 0x70, 0x39, 0x2, 0x291, 0x292, 
       0x7, 0x7e, 0x2, 0x2, 0x292, 0x293, 0x7, 0x47, 0x2, 0x2, 0x293, 0x29d, 
       0x3, 0x2, 0x2, 0x2, 0x294, 0x29d, 0x5, 0x72, 0x3a, 0x2, 0x295, 0x29d, 
       0x5, 0x74, 0x3b, 0x2, 0x296, 0x29d, 0x5, 0x76, 0x3c, 0x2, 0x297, 
       0x29d, 0x7, 0x47, 0x2, 0x2, 0x298, 0x29d, 0x5, 0x78, 0x3d, 0x2, 0x299, 
       0x29d, 0x5, 0x7a, 0x3e, 0x2, 0x29a, 0x29d, 0x5, 0x7e, 0x40, 0x2, 
       0x29b, 0x29d, 0x5, 0x82, 0x42, 0x2, 0x29c, 0x27f, 0x3, 0x2, 0x2, 
       0x2, 0x29c, 0x281, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x289, 0x3, 0x2, 0x2, 
       0x2, 0x29c, 0x28f, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x294, 0x3, 0x2, 0x2, 
       0x2, 0x29c, 0x295, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x296, 0x3, 0x2, 0x2, 
       0x2, 0x29c, 0x297, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x298, 0x3, 0x2, 0x2, 
       0x2, 0x29c, 0x299, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x29a, 0x3, 0x2, 0x2, 
       0x2, 0x29c, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x29d, 0x71, 0x3, 0x2, 0x2, 
       0x2, 0x29e, 0x29f, 0x7, 0x2a, 0x2, 0x2, 0x29f, 0x2a0, 0x7, 0x4c, 
       0x2, 0x2, 0x2a0, 0x2a1, 0x5, 0x4a, 0x26, 0x2, 0x2a1, 0x2a2, 0x7, 
       0x4d, 0x2, 0x2, 0x2a2, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2a3, 0x2a4, 0x7, 
       0x2a, 0x2, 0x2, 0x2a4, 0x2a5, 0x7, 0x7e, 0x2, 0x2, 0x2a5, 0x2a7, 
       0x7, 0x47, 0x2, 0x2, 0x2a6, 0x29e, 0x3, 0x2, 0x2, 0x2, 0x2a6, 0x2a3, 
       0x3, 0x2, 0x2, 0x2, 0x2a7, 0x73, 0x3, 0x2, 0x2, 0x2, 0x2a8, 0x2aa, 
       0x7, 0x15, 0x2, 0x2, 0x2a9, 0x2ab, 0x7, 0x47, 0x2, 0x2, 0x2aa, 0x2a9, 
       0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2ab, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2ac, 
       0x3, 0x2, 0x2, 0x2, 0x2ac, 0x2ae, 0x7, 0x4a, 0x2, 0x2, 0x2ad, 0x2af, 
       0x5, 0x3e, 0x20, 0x2, 0x2ae, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2af, 
       0x3, 0x2, 0x2, 0x2, 0x2af, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2b1, 
       0x7, 0x4b, 0x2, 0x2, 0x2b1, 0x2b2, 0x7, 0x48, 0x2, 0x2, 0x2b2, 0x2b3, 
       0x5, 0x40, 0x21, 0x2, 0x2b3, 0x2b4, 0x7, 0x49, 0x2, 0x2, 0x2b4, 0x75, 
       0x3, 0x2, 0x2, 0x2, 0x2b5, 0x2b7, 0x7, 0x2b, 0x2, 0x2, 0x2b6, 0x2b8, 
       0x7, 0x47, 0x2, 0x2, 0x2b7, 0x2b6, 0x3, 0x2, 0x2, 0x2, 0x2b7, 0x2b8, 
       0x3, 0x2, 0x2, 0x2, 0x2b8, 0x2bb, 0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2ba, 
       0x7, 0x2c, 0x2, 0x2, 0x2ba, 0x2bc, 0x7, 0x47, 0x2, 0x2, 0x2bb, 0x2b9, 
       0x3, 0x2, 0x2, 0x2, 0x2bb, 0x2bc, 0x3, 0x2, 0x2, 0x2, 0x2bc, 0x2bd, 
       0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2bf, 0x7, 0x48, 0x2, 0x2, 0x2be, 0x2c0, 
       0x5, 0x44, 0x23, 0x2, 0x2bf, 0x2be, 0x3, 0x2, 0x2, 0x2, 0x2bf, 0x2c0, 
       0x3, 0x2, 0x2, 0x2, 0x2c0, 0x2c1, 0x3, 0x2, 0x2, 0x2, 0x2c1, 0x2c2, 
       0x7, 0x49, 0x2, 0x2, 0x2c2, 0x77, 0x3, 0x2, 0x2, 0x2, 0x2c3, 0x2c4, 
       0x7, 0x29, 0x2, 0x2, 0x2c4, 0x79, 0x3, 0x2, 0x2, 0x2, 0x2c5, 0x2ca, 
       0x7, 0x4c, 0x2, 0x2, 0x2c6, 0x2c8, 0x5, 0x7c, 0x3f, 0x2, 0x2c7, 0x2c9, 
       0x7, 0x7f, 0x2, 0x2, 0x2c8, 0x2c7, 0x3, 0x2, 0x2, 0x2, 0x2c8, 0x2c9, 
       0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2cb, 0x3, 0x2, 0x2, 0x2, 0x2ca, 0x2c6, 
       0x3, 0x2, 0x2, 0x2, 0x2ca, 0x2cb, 0x3, 0x2, 0x2, 0x2, 0x2cb, 0x2cc, 
       0x3, 0x2, 0x2, 0x2, 0x2cc, 0x2cd, 0x7, 0x4d, 0x2, 0x2, 0x2cd, 0x7b, 
       0x3, 0x2, 0x2, 0x2, 0x2ce, 0x2d0, 0x7, 0x77, 0x2, 0x2, 0x2cf, 0x2ce, 
       0x3, 0x2, 0x2, 0x2, 0x2cf, 0x2d0, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2d1, 
       0x3, 0x2, 0x2, 0x2, 0x2d1, 0x2d9, 0x5, 0x12, 0xa, 0x2, 0x2d2, 0x2d4, 
       0x7, 0x7f, 0x2, 0x2, 0x2d3, 0x2d5, 0x7, 0x77, 0x2, 0x2, 0x2d4, 0x2d3, 
       0x3, 0x2, 0x2, 0x2, 0x2d4, 0x2d5, 0x3, 0x2, 0x2, 0x2, 0x2d5, 0x2d6, 
       0x3, 0x2, 0x2, 0x2, 0x2d6, 0x2d8, 0x5, 0x12, 0xa, 0x2, 0x2d7, 0x2d2, 
       0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2db, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x2d7, 
       0x3, 0x2, 0x2, 0x2, 0x2d9, 0x2da, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x7d, 
       0x3, 0x2, 0x2, 0x2, 0x2db, 0x2d9, 0x3, 0x2, 0x2, 0x2, 0x2dc, 0x2e5, 
       0x7, 0x48, 0x2, 0x2, 0x2dd, 0x2e2, 0x5, 0x80, 0x41, 0x2, 0x2de, 0x2df, 
       0x7, 0x7f, 0x2, 0x2, 0x2df, 0x2e1, 0x5, 0x80, 0x41, 0x2, 0x2e0, 0x2de, 
       0x3, 0x2, 0x2, 0x2, 0x2e1, 0x2e4, 0x3, 0x2, 0x2, 0x2, 0x2e2, 0x2e0, 
       0x3, 0x2, 0x2, 0x2, 0x2e2, 0x2e3, 0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e6, 
       0x3, 0x2, 0x2, 0x2, 0x2e4, 0x2e2, 0x3, 0x2, 0x2, 0x2, 0x2e5, 0x2dd, 
       0x3, 0x2, 0x2, 0x2, 0x2e5, 0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2e6, 0x2e7, 
       0x3, 0x2, 0x2, 0x2, 0x2e7, 0x2e8, 0x7, 0x49, 0x2, 0x2, 0x2e8, 0x7f, 
       0x3, 0x2, 0x2, 0x2, 0x2e9, 0x2ea, 0x7, 0x47, 0x2, 0x2, 0x2ea, 0x2eb, 
       0x7, 0x4f, 0x2, 0x2, 0x2eb, 0x2fe, 0x5, 0x12, 0xa, 0x2, 0x2ec, 0x2ee, 
       0x9, 0x4, 0x2, 0x2, 0x2ed, 0x2ec, 0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2ee, 
       0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2ef, 0x3, 0x2, 0x2, 0x2, 0x2ef, 0x2f0, 
       0x7, 0x47, 0x2, 0x2, 0x2f0, 0x2f2, 0x7, 0x4a, 0x2, 0x2, 0x2f1, 0x2f3, 
       0x5, 0x3e, 0x20, 0x2, 0x2f2, 0x2f1, 0x3, 0x2, 0x2, 0x2, 0x2f2, 0x2f3, 
       0x3, 0x2, 0x2, 0x2, 0x2f3, 0x2f4, 0x3, 0x2, 0x2, 0x2, 0x2f4, 0x2f5, 
       0x7, 0x4b, 0x2, 0x2, 0x2f5, 0x2f6, 0x7, 0x48, 0x2, 0x2, 0x2f6, 0x2f7, 
       0x5, 0x40, 0x21, 0x2, 0x2f7, 0x2f8, 0x7, 0x49, 0x2, 0x2, 0x2f8, 0x2fe, 
       0x3, 0x2, 0x2, 0x2, 0x2f9, 0x2fb, 0x7, 0x77, 0x2, 0x2, 0x2fa, 0x2f9, 
       0x3, 0x2, 0x2, 0x2, 0x2fa, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x2fb, 0x2fc, 
       0x3, 0x2, 0x2, 0x2, 0x2fc, 0x2fe, 0x5, 0x12, 0xa, 0x2, 0x2fd, 0x2e9, 
       0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2ed, 0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2fa, 
       0x3, 0x2, 0x2, 0x2, 0x2fe, 0x81, 0x3, 0x2, 0x2, 0x2, 0x2ff, 0x300, 
       0x7, 0x4a, 0x2, 0x2, 0x300, 0x301, 0x5, 0x4a, 0x26, 0x2, 0x301, 0x302, 
       0x7, 0x4b, 0x2, 0x2, 0x302, 0x83, 0x3, 0x2, 0x2, 0x2, 0x303, 0x304, 
       0x5, 0x86, 0x44, 0x2, 0x304, 0x305, 0x7, 0x78, 0x2, 0x2, 0x305, 0x306, 
       0x5, 0x88, 0x45, 0x2, 0x306, 0x85, 0x3, 0x2, 0x2, 0x2, 0x307, 0x30e, 
       0x7, 0x47, 0x2, 0x2, 0x308, 0x30a, 0x7, 0x4a, 0x2, 0x2, 0x309, 0x30b, 
       0x5, 0x3e, 0x20, 0x2, 0x30a, 0x309, 0x3, 0x2, 0x2, 0x2, 0x30a, 0x30b, 
       0x3, 0x2, 0x2, 0x2, 0x30b, 0x30c, 0x3, 0x2, 0x2, 0x2, 0x30c, 0x30e, 
       0x7, 0x4b, 0x2, 0x2, 0x30d, 0x307, 0x3, 0x2, 0x2, 0x2, 0x30d, 0x308, 
       0x3, 0x2, 0x2, 0x2, 0x30e, 0x87, 0x3, 0x2, 0x2, 0x2, 0x30f, 0x315, 
       0x5, 0x12, 0xa, 0x2, 0x310, 0x311, 0x7, 0x48, 0x2, 0x2, 0x311, 0x312, 
       0x5, 0x40, 0x21, 0x2, 0x312, 0x313, 0x7, 0x49, 0x2, 0x2, 0x313, 0x315, 
       0x3, 0x2, 0x2, 0x2, 0x314, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x314, 0x310, 
       0x3, 0x2, 0x2, 0x2, 0x315, 0x89, 0x3, 0x2, 0x2, 0x2, 0x316, 0x31b, 
       0x5, 0x8c, 0x47, 0x2, 0x317, 0x31b, 0x5, 0x96, 0x4c, 0x2, 0x318, 
       0x31b, 0x5, 0xa2, 0x52, 0x2, 0x319, 0x31b, 0x5, 0xae, 0x58, 0x2, 
       0x31a, 0x316, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x317, 0x3, 0x2, 0x2, 0x2, 
       0x31a, 0x318, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x319, 0x3, 0x2, 0x2, 0x2, 
       0x31b, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x31c, 0x31d, 0x5, 0x8e, 0x48, 0x2, 
       0x31d, 0x31e, 0x9, 0xc, 0x2, 0x2, 0x31e, 0x31f, 0x5, 0xd8, 0x6d, 
       0x2, 0x31f, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x320, 0x321, 0x7, 0x79, 0x2, 
       0x2, 0x321, 0x322, 0x5, 0x90, 0x49, 0x2, 0x322, 0x323, 0x7, 0x7a, 
       0x2, 0x2, 0x323, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x324, 0x326, 0x5, 0x92, 
       0x4a, 0x2, 0x325, 0x324, 0x3, 0x2, 0x2, 0x2, 0x325, 0x326, 0x3, 0x2, 
       0x2, 0x2, 0x326, 0x327, 0x3, 0x2, 0x2, 0x2, 0x327, 0x329, 0x7, 0x47, 
       0x2, 0x2, 0x328, 0x32a, 0x5, 0x94, 0x4b, 0x2, 0x329, 0x328, 0x3, 
       0x2, 0x2, 0x2, 0x32a, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x32b, 0x329, 0x3, 
       0x2, 0x2, 0x2, 0x32b, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x32c, 0x91, 0x3, 
       0x2, 0x2, 0x2, 0x32d, 0x32e, 0x9, 0xd, 0x2, 0x2, 0x32e, 0x93, 0x3, 
       0x2, 0x2, 0x2, 0x32f, 0x330, 0x7, 0x4c, 0x2, 0x2, 0x330, 0x331, 0x7, 
       0x42, 0x2, 0x2, 0x331, 0x339, 0x7, 0x4d, 0x2, 0x2, 0x332, 0x333, 
       0x7, 0x3, 0x2, 0x2, 0x333, 0x335, 0x5, 0x90, 0x49, 0x2, 0x334, 0x332, 
       0x3, 0x2, 0x2, 0x2, 0x335, 0x336, 0x3, 0x2, 0x2, 0x2, 0x336, 0x334, 
       0x3, 0x2, 0x2, 0x2, 0x336, 0x337, 0x3, 0x2, 0x2, 0x2, 0x337, 0x339, 
       0x3, 0x2, 0x2, 0x2, 0x338, 0x32f, 0x3, 0x2, 0x2, 0x2, 0x338, 0x334, 
       0x3, 0x2, 0x2, 0x2, 0x339, 0x95, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x33b, 
       0x5, 0x8e, 0x48, 0x2, 0x33b, 0x33c, 0x7, 0x7e, 0x2, 0x2, 0x33c, 0x33d, 
       0x7, 0x7, 0x2, 0x2, 0x33d, 0x33e, 0x7, 0x4a, 0x2, 0x2, 0x33e, 0x33f, 
       0x5, 0x98, 0x4d, 0x2, 0x33f, 0x340, 0x7, 0x4b, 0x2, 0x2, 0x340, 0x97, 
       0x3, 0x2, 0x2, 0x2, 0x341, 0x342, 0x7, 0x48, 0x2, 0x2, 0x342, 0x343, 
       0x5, 0x9a, 0x4e, 0x2, 0x343, 0x344, 0x7, 0x49, 0x2, 0x2, 0x344, 0x99, 
       0x3, 0x2, 0x2, 0x2, 0x345, 0x34a, 0x5, 0x9c, 0x4f, 0x2, 0x346, 0x347, 
       0x7, 0x7f, 0x2, 0x2, 0x347, 0x349, 0x5, 0x9c, 0x4f, 0x2, 0x348, 0x346, 
       0x3, 0x2, 0x2, 0x2, 0x349, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x34a, 0x348, 
       0x3, 0x2, 0x2, 0x2, 0x34a, 0x34b, 0x3, 0x2, 0x2, 0x2, 0x34b, 0x9b, 
       0x3, 0x2, 0x2, 0x2, 0x34c, 0x34a, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x34e, 
       0x5, 0x9e, 0x50, 0x2, 0x34e, 0x34f, 0x7, 0x4f, 0x2, 0x2, 0x34f, 0x350, 
       0x5, 0xa0, 0x51, 0x2, 0x350, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x351, 0x352, 
       0x7, 0x47, 0x2, 0x2, 0x352, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x353, 0x357, 
       0x7, 0x47, 0x2, 0x2, 0x354, 0x357, 0x5, 0x74, 0x3b, 0x2, 0x355, 0x357, 
       0x5, 0x84, 0x43, 0x2, 0x356, 0x353, 0x3, 0x2, 0x2, 0x2, 0x356, 0x354, 
       0x3, 0x2, 0x2, 0x2, 0x356, 0x355, 0x3, 0x2, 0x2, 0x2, 0x357, 0xa1, 
       0x3, 0x2, 0x2, 0x2, 0x358, 0x359, 0x5, 0x8e, 0x48, 0x2, 0x359, 0x35a, 
       0x7, 0x7e, 0x2, 0x2, 0x35a, 0x35b, 0x7, 0x8, 0x2, 0x2, 0x35b, 0x35c, 
       0x7, 0x4a, 0x2, 0x2, 0x35c, 0x35d, 0x5, 0xa4, 0x53, 0x2, 0x35d, 0x35e, 
       0x7, 0x4b, 0x2, 0x2, 0x35e, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x360, 
       0x7, 0x48, 0x2, 0x2, 0x360, 0x361, 0x5, 0xa6, 0x54, 0x2, 0x361, 0x362, 
       0x7, 0x49, 0x2, 0x2, 0x362, 0xa5, 0x3, 0x2, 0x2, 0x2, 0x363, 0x364, 
       0x5, 0xa8, 0x55, 0x2, 0x364, 0x365, 0x7, 0x7f, 0x2, 0x2, 0x365, 0x366, 
       0x5, 0xac, 0x57, 0x2, 0x366, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x367, 0x368, 
       0x7, 0x12, 0x2, 0x2, 0x368, 0x36b, 0x7, 0x4f, 0x2, 0x2, 0x369, 0x36c, 
       0x5, 0x8e, 0x48, 0x2, 0x36a, 0x36c, 0x5, 0xaa, 0x56, 0x2, 0x36b, 
       0x369, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x36a, 0x3, 0x2, 0x2, 0x2, 0x36c, 
       0xa9, 0x3, 0x2, 0x2, 0x2, 0x36d, 0x36e, 0x7, 0x4c, 0x2, 0x2, 0x36e, 
       0x373, 0x5, 0x8e, 0x48, 0x2, 0x36f, 0x370, 0x7, 0x7f, 0x2, 0x2, 0x370, 
       0x372, 0x5, 0x8e, 0x48, 0x2, 0x371, 0x36f, 0x3, 0x2, 0x2, 0x2, 0x372, 
       0x375, 0x3, 0x2, 0x2, 0x2, 0x373, 0x371, 0x3, 0x2, 0x2, 0x2, 0x373, 
       0x374, 0x3, 0x2, 0x2, 0x2, 0x374, 0x376, 0x3, 0x2, 0x2, 0x2, 0x375, 
       0x373, 0x3, 0x2, 0x2, 0x2, 0x376, 0x377, 0x7, 0x4d, 0x2, 0x2, 0x377, 
       0xab, 0x3, 0x2, 0x2, 0x2, 0x378, 0x379, 0x5, 0x9a, 0x4e, 0x2, 0x379, 
       0xad, 0x3, 0x2, 0x2, 0x2, 0x37a, 0x37b, 0x7, 0x9, 0x2, 0x2, 0x37b, 
       0x37c, 0x7, 0x4a, 0x2, 0x2, 0x37c, 0x37d, 0x5, 0xb0, 0x59, 0x2, 0x37d, 
       0x37e, 0x7, 0x4b, 0x2, 0x2, 0x37e, 0xaf, 0x3, 0x2, 0x2, 0x2, 0x37f, 
       0x380, 0x7, 0x48, 0x2, 0x2, 0x380, 0x381, 0x5, 0xb2, 0x5a, 0x2, 0x381, 
       0x382, 0x7, 0x49, 0x2, 0x2, 0x382, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x383, 
       0x388, 0x5, 0xb4, 0x5b, 0x2, 0x384, 0x385, 0x7, 0x7f, 0x2, 0x2, 0x385, 
       0x387, 0x5, 0xb4, 0x5b, 0x2, 0x386, 0x384, 0x3, 0x2, 0x2, 0x2, 0x387, 
       0x38a, 0x3, 0x2, 0x2, 0x2, 0x388, 0x386, 0x3, 0x2, 0x2, 0x2, 0x388, 
       0x389, 0x3, 0x2, 0x2, 0x2, 0x389, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x38a, 
       0x388, 0x3, 0x2, 0x2, 0x2, 0x38b, 0x395, 0x5, 0xb6, 0x5c, 0x2, 0x38c, 
       0x395, 0x5, 0xb8, 0x5d, 0x2, 0x38d, 0x395, 0x5, 0xbc, 0x5f, 0x2, 
       0x38e, 0x395, 0x5, 0xbe, 0x60, 0x2, 0x38f, 0x395, 0x5, 0xc4, 0x63, 
       0x2, 0x390, 0x395, 0x5, 0xc6, 0x64, 0x2, 0x391, 0x395, 0x5, 0xc8, 
       0x65, 0x2, 0x392, 0x395, 0x5, 0xcc, 0x67, 0x2, 0x393, 0x395, 0x5, 
       0xce, 0x68, 0x2, 0x394, 0x38b, 0x3, 0x2, 0x2, 0x2, 0x394, 0x38c, 
       0x3, 0x2, 0x2, 0x2, 0x394, 0x38d, 0x3, 0x2, 0x2, 0x2, 0x394, 0x38e, 
       0x3, 0x2, 0x2, 0x2, 0x394, 0x38f, 0x3, 0x2, 0x2, 0x2, 0x394, 0x390, 
       0x3, 0x2, 0x2, 0x2, 0x394, 0x391, 0x3, 0x2, 0x2, 0x2, 0x394, 0x392, 
       0x3, 0x2, 0x2, 0x2, 0x394, 0x393, 0x3, 0x2, 0x2, 0x2, 0x395, 0xb5, 
       0x3, 0x2, 0x2, 0x2, 0x396, 0x397, 0x7, 0x14, 0x2, 0x2, 0x397, 0x398, 
       0x7, 0x4f, 0x2, 0x2, 0x398, 0x399, 0x7, 0x42, 0x2, 0x2, 0x399, 0xb7, 
       0x3, 0x2, 0x2, 0x2, 0x39a, 0x39b, 0x7, 0x13, 0x2, 0x2, 0x39b, 0x39c, 
       0x7, 0x4f, 0x2, 0x2, 0x39c, 0x39d, 0x5, 0xba, 0x5e, 0x2, 0x39d, 0xb9, 
       0x3, 0x2, 0x2, 0x2, 0x39e, 0x39f, 0x9, 0xe, 0x2, 0x2, 0x39f, 0xbb, 
       0x3, 0x2, 0x2, 0x2, 0x3a0, 0x3a1, 0x7, 0xc, 0x2, 0x2, 0x3a1, 0x3a2, 
       0x7, 0x4f, 0x2, 0x2, 0x3a2, 0x3a3, 0x7, 0x48, 0x2, 0x2, 0x3a3, 0x3a4, 
       0x5, 0xd0, 0x69, 0x2, 0x3a4, 0x3a5, 0x7, 0x49, 0x2, 0x2, 0x3a5, 0xbd, 
       0x3, 0x2, 0x2, 0x2, 0x3a6, 0x3a7, 0x7, 0xb, 0x2, 0x2, 0x3a7, 0x3a8, 
       0x7, 0x4f, 0x2, 0x2, 0x3a8, 0x3a9, 0x7, 0x4c, 0x2, 0x2, 0x3a9, 0x3ae, 
       0x5, 0xc0, 0x61, 0x2, 0x3aa, 0x3ab, 0x7, 0x7f, 0x2, 0x2, 0x3ab, 0x3ad, 
       0x5, 0xc0, 0x61, 0x2, 0x3ac, 0x3aa, 0x3, 0x2, 0x2, 0x2, 0x3ad, 0x3b0, 
       0x3, 0x2, 0x2, 0x2, 0x3ae, 0x3ac, 0x3, 0x2, 0x2, 0x2, 0x3ae, 0x3af, 
       0x3, 0x2, 0x2, 0x2, 0x3af, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b0, 0x3ae, 
       0x3, 0x2, 0x2, 0x2, 0x3b1, 0x3b2, 0x7, 0x4d, 0x2, 0x2, 0x3b2, 0xbf, 
       0x3, 0x2, 0x2, 0x2, 0x3b3, 0x3b4, 0x7, 0x48, 0x2, 0x2, 0x3b4, 0x3b5, 
       0x5, 0xc2, 0x62, 0x2, 0x3b5, 0x3b6, 0x7, 0x7f, 0x2, 0x2, 0x3b6, 0x3b7, 
       0x5, 0xd0, 0x69, 0x2, 0x3b7, 0x3b8, 0x7, 0x49, 0x2, 0x2, 0x3b8, 0xc1, 
       0x3, 0x2, 0x2, 0x2, 0x3b9, 0x3ba, 0x7, 0xa, 0x2, 0x2, 0x3ba, 0x3bb, 
       0x7, 0x4f, 0x2, 0x2, 0x3bb, 0x3bc, 0x7, 0x42, 0x2, 0x2, 0x3bc, 0xc3, 
       0x3, 0x2, 0x2, 0x2, 0x3bd, 0x3be, 0x7, 0xd, 0x2, 0x2, 0x3be, 0x3bf, 
       0x7, 0x4f, 0x2, 0x2, 0x3bf, 0x3c0, 0x7, 0x48, 0x2, 0x2, 0x3c0, 0x3c1, 
       0x5, 0xd0, 0x69, 0x2, 0x3c1, 0x3c2, 0x7, 0x49, 0x2, 0x2, 0x3c2, 0xc5, 
       0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3c4, 0x7, 0xe, 0x2, 0x2, 0x3c4, 0x3c5, 
       0x7, 0x4f, 0x2, 0x2, 0x3c5, 0x3c6, 0x9, 0xf, 0x2, 0x2, 0x3c6, 0xc7, 
       0x3, 0x2, 0x2, 0x2, 0x3c7, 0x3c8, 0x7, 0xf, 0x2, 0x2, 0x3c8, 0x3c9, 
       0x7, 0x4f, 0x2, 0x2, 0x3c9, 0x3ca, 0x5, 0xca, 0x66, 0x2, 0x3ca, 0xc9, 
       0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3cc, 0x9, 0xe, 0x2, 0x2, 0x3cc, 0xcb, 
       0x3, 0x2, 0x2, 0x2, 0x3cd, 0x3ce, 0x7, 0x10, 0x2, 0x2, 0x3ce, 0x3cf, 
       0x7, 0x4f, 0x2, 0x2, 0x3cf, 0x3d0, 0x7, 0x42, 0x2, 0x2, 0x3d0, 0xcd, 
       0x3, 0x2, 0x2, 0x2, 0x3d1, 0x3d2, 0x7, 0x11, 0x2, 0x2, 0x3d2, 0x3d3, 
       0x7, 0x4f, 0x2, 0x2, 0x3d3, 0x3d4, 0x7, 0x47, 0x2, 0x2, 0x3d4, 0xcf, 
       0x3, 0x2, 0x2, 0x2, 0x3d5, 0x3d7, 0x5, 0xd2, 0x6a, 0x2, 0x3d6, 0x3d5, 
       0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3da, 0x3, 0x2, 0x2, 0x2, 0x3d8, 0x3d6, 
       0x3, 0x2, 0x2, 0x2, 0x3d8, 0x3d9, 0x3, 0x2, 0x2, 0x2, 0x3d9, 0xd1, 
       0x3, 0x2, 0x2, 0x2, 0x3da, 0x3d8, 0x3, 0x2, 0x2, 0x2, 0x3db, 0x3dc, 
       0x5, 0xd4, 0x6b, 0x2, 0x3dc, 0x3dd, 0x7, 0x4f, 0x2, 0x2, 0x3dd, 0x3de, 
       0x5, 0xd6, 0x6c, 0x2, 0x3de, 0x3df, 0x7, 0x4e, 0x2, 0x2, 0x3df, 0xd3, 
       0x3, 0x2, 0x2, 0x2, 0x3e0, 0x3e1, 0x7, 0x47, 0x2, 0x2, 0x3e1, 0xd5, 
       0x3, 0x2, 0x2, 0x2, 0x3e2, 0x3e7, 0x7, 0x43, 0x2, 0x2, 0x3e3, 0x3e7, 
       0x7, 0x7c, 0x2, 0x2, 0x3e4, 0x3e7, 0x7, 0x47, 0x2, 0x2, 0x3e5, 0x3e7, 
       0x5, 0xda, 0x6e, 0x2, 0x3e6, 0x3e2, 0x3, 0x2, 0x2, 0x2, 0x3e6, 0x3e3, 
       0x3, 0x2, 0x2, 0x2, 0x3e6, 0x3e4, 0x3, 0x2, 0x2, 0x2, 0x3e6, 0x3e5, 
       0x3, 0x2, 0x2, 0x2, 0x3e7, 0x3ea, 0x3, 0x2, 0x2, 0x2, 0x3e8, 0x3e6, 
       0x3, 0x2, 0x2, 0x2, 0x3e8, 0x3e9, 0x3, 0x2, 0x2, 0x2, 0x3e9, 0xd7, 
       0x3, 0x2, 0x2, 0x2, 0x3ea, 0x3e8, 0x3, 0x2, 0x2, 0x2, 0x3eb, 0x3ec, 
       0x8, 0x6d, 0x1, 0x2, 0x3ec, 0x3ed, 0x7, 0x47, 0x2, 0x2, 0x3ed, 0x3ef, 
       0x7, 0x4a, 0x2, 0x2, 0x3ee, 0x3f0, 0x5, 0x6c, 0x37, 0x2, 0x3ef, 0x3ee, 
       0x3, 0x2, 0x2, 0x2, 0x3ef, 0x3f0, 0x3, 0x2, 0x2, 0x2, 0x3f0, 0x3f1, 
       0x3, 0x2, 0x2, 0x2, 0x3f1, 0x3f2, 0x7, 0x4b, 0x2, 0x2, 0x3f2, 0x405, 
       0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3f4, 0xc, 0x5, 0x2, 0x2, 0x3f4, 0x3f5, 
       0x7, 0x7e, 0x2, 0x2, 0x3f5, 0x3f6, 0x7, 0x47, 0x2, 0x2, 0x3f6, 0x3f8, 
       0x7, 0x4a, 0x2, 0x2, 0x3f7, 0x3f9, 0x5, 0x6c, 0x37, 0x2, 0x3f8, 0x3f7, 
       0x3, 0x2, 0x2, 0x2, 0x3f8, 0x3f9, 0x3, 0x2, 0x2, 0x2, 0x3f9, 0x3fa, 
       0x3, 0x2, 0x2, 0x2, 0x3fa, 0x404, 0x7, 0x4b, 0x2, 0x2, 0x3fb, 0x3fc, 
       0xc, 0x4, 0x2, 0x2, 0x3fc, 0x3fd, 0x7, 0x4c, 0x2, 0x2, 0x3fd, 0x3fe, 
       0x5, 0x4a, 0x26, 0x2, 0x3fe, 0x3ff, 0x7, 0x4d, 0x2, 0x2, 0x3ff, 0x404, 
       0x3, 0x2, 0x2, 0x2, 0x400, 0x401, 0xc, 0x3, 0x2, 0x2, 0x401, 0x402, 
       0x7, 0x7e, 0x2, 0x2, 0x402, 0x404, 0x7, 0x47, 0x2, 0x2, 0x403, 0x3f3, 
       0x3, 0x2, 0x2, 0x2, 0x403, 0x3fb, 0x3, 0x2, 0x2, 0x2, 0x403, 0x400, 
       0x3, 0x2, 0x2, 0x2, 0x404, 0x407, 0x3, 0x2, 0x2, 0x2, 0x405, 0x403, 
       0x3, 0x2, 0x2, 0x2, 0x405, 0x406, 0x3, 0x2, 0x2, 0x2, 0x406, 0xd9, 
       0x3, 0x2, 0x2, 0x2, 0x407, 0x405, 0x3, 0x2, 0x2, 0x2, 0x408, 0x409, 
       0x7, 0x47, 0x2, 0x2, 0x409, 0x412, 0x7, 0x4a, 0x2, 0x2, 0x40a, 0x40f, 
       0x5, 0xdc, 0x6f, 0x2, 0x40b, 0x40c, 0x7, 0x7f, 0x2, 0x2, 0x40c, 0x40e, 
       0x5, 0xdc, 0x6f, 0x2, 0x40d, 0x40b, 0x3, 0x2, 0x2, 0x2, 0x40e, 0x411, 
       0x3, 0x2, 0x2, 0x2, 0x40f, 0x40d, 0x3, 0x2, 0x2, 0x2, 0x40f, 0x410, 
       0x3, 0x2, 0x2, 0x2, 0x410, 0x413, 0x3, 0x2, 0x2, 0x2, 0x411, 0x40f, 
       0x3, 0x2, 0x2, 0x2, 0x412, 0x40a, 0x3, 0x2, 0x2, 0x2, 0x412, 0x413, 
       0x3, 0x2, 0x2, 0x2, 0x413, 0x414, 0x3, 0x2, 0x2, 0x2, 0x414, 0x415, 
       0x7, 0x4b, 0x2, 0x2, 0x415, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x416, 0x419, 
       0x7, 0x47, 0x2, 0x2, 0x417, 0x418, 0x7, 0x51, 0x2, 0x2, 0x418, 0x41a, 
       0x5, 0xde, 0x70, 0x2, 0x419, 0x417, 0x3, 0x2, 0x2, 0x2, 0x419, 0x41a, 
       0x3, 0x2, 0x2, 0x2, 0x41a, 0x41d, 0x3, 0x2, 0x2, 0x2, 0x41b, 0x41d, 
       0x5, 0xde, 0x70, 0x2, 0x41c, 0x416, 0x3, 0x2, 0x2, 0x2, 0x41c, 0x41b, 
       0x3, 0x2, 0x2, 0x2, 0x41d, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x41e, 0x41f, 
       0x9, 0x10, 0x2, 0x2, 0x41f, 0xdf, 0x3, 0x2, 0x2, 0x2, 0x420, 0x422, 
       0x5, 0x4, 0x3, 0x2, 0x421, 0x420, 0x3, 0x2, 0x2, 0x2, 0x422, 0x423, 
       0x3, 0x2, 0x2, 0x2, 0x423, 0x421, 0x3, 0x2, 0x2, 0x2, 0x423, 0x424, 
       0x3, 0x2, 0x2, 0x2, 0x424, 0xe1, 0x3, 0x2, 0x2, 0x2, 0x65, 0xe5, 
       0xee, 0xff, 0x103, 0x10a, 0x115, 0x11b, 0x121, 0x131, 0x145, 0x149, 
       0x14d, 0x151, 0x155, 0x15b, 0x161, 0x177, 0x17b, 0x17d, 0x184, 0x18a, 
       0x18f, 0x198, 0x19b, 0x1a2, 0x1b4, 0x1c0, 0x1c4, 0x1ca, 0x1ce, 0x1d5, 
       0x1da, 0x1df, 0x1eb, 0x1f4, 0x1fb, 0x203, 0x20b, 0x213, 0x21b, 0x223, 
       0x22b, 0x233, 0x23b, 0x243, 0x24a, 0x250, 0x254, 0x260, 0x265, 0x270, 
       0x272, 0x27c, 0x285, 0x29c, 0x2a6, 0x2aa, 0x2ae, 0x2b7, 0x2bb, 0x2bf, 
       0x2c8, 0x2ca, 0x2cf, 0x2d4, 0x2d9, 0x2e2, 0x2e5, 0x2ed, 0x2f2, 0x2fa, 
       0x2fd, 0x30a, 0x30d, 0x314, 0x31a, 0x325, 0x32b, 0x336, 0x338, 0x34a, 
       0x356, 0x36b, 0x373, 0x388, 0x394, 0x3ae, 0x3d8, 0x3e6, 0x3e8, 0x3ef, 
       0x3f8, 0x403, 0x405, 0x40f, 0x412, 0x419, 0x41c, 0x423, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  auto atn_ptr = deserializer.deserialize(antlr4::atn::SerializedATNView(reinterpret_cast<const int32_t*>(_serializedATN.data()), _serializedATN.size()));
  // 手动复制ATN数据到静态成员
  _atn = *atn_ptr;

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CHTLJSParser::Initializer CHTLJSParser::_init;
