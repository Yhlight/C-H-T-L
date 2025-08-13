
// Generated from grammars/chtl/CHTL.g4 by ANTLR 4.9.2


#include "CHTLListener.h"

#include "CHTLParser.h"


using namespace antlrcpp;
using namespace antlr4;

CHTLParser::CHTLParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CHTLParser::~CHTLParser() {
  delete _interpreter;
}

std::string CHTLParser::getGrammarFileName() const {
  return "CHTL.g4";
}

const std::vector<std::string>& CHTLParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CHTLParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

CHTLParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ImportStatementContext *> CHTLParser::ProgramContext::importStatement() {
  return getRuleContexts<CHTLParser::ImportStatementContext>();
}

CHTLParser::ImportStatementContext* CHTLParser::ProgramContext::importStatement(size_t i) {
  return getRuleContext<CHTLParser::ImportStatementContext>(i);
}

std::vector<CHTLParser::NamespaceStatementContext *> CHTLParser::ProgramContext::namespaceStatement() {
  return getRuleContexts<CHTLParser::NamespaceStatementContext>();
}

CHTLParser::NamespaceStatementContext* CHTLParser::ProgramContext::namespaceStatement(size_t i) {
  return getRuleContext<CHTLParser::NamespaceStatementContext>(i);
}

std::vector<CHTLParser::ConfigurationStatementContext *> CHTLParser::ProgramContext::configurationStatement() {
  return getRuleContexts<CHTLParser::ConfigurationStatementContext>();
}

CHTLParser::ConfigurationStatementContext* CHTLParser::ProgramContext::configurationStatement(size_t i) {
  return getRuleContext<CHTLParser::ConfigurationStatementContext>(i);
}

std::vector<CHTLParser::TemplateStatementContext *> CHTLParser::ProgramContext::templateStatement() {
  return getRuleContexts<CHTLParser::TemplateStatementContext>();
}

CHTLParser::TemplateStatementContext* CHTLParser::ProgramContext::templateStatement(size_t i) {
  return getRuleContext<CHTLParser::TemplateStatementContext>(i);
}

std::vector<CHTLParser::CustomStatementContext *> CHTLParser::ProgramContext::customStatement() {
  return getRuleContexts<CHTLParser::CustomStatementContext>();
}

CHTLParser::CustomStatementContext* CHTLParser::ProgramContext::customStatement(size_t i) {
  return getRuleContext<CHTLParser::CustomStatementContext>(i);
}

std::vector<CHTLParser::OriginStatementContext *> CHTLParser::ProgramContext::originStatement() {
  return getRuleContexts<CHTLParser::OriginStatementContext>();
}

CHTLParser::OriginStatementContext* CHTLParser::ProgramContext::originStatement(size_t i) {
  return getRuleContext<CHTLParser::OriginStatementContext>(i);
}

std::vector<CHTLParser::ElementStatementContext *> CHTLParser::ProgramContext::elementStatement() {
  return getRuleContexts<CHTLParser::ElementStatementContext>();
}

CHTLParser::ElementStatementContext* CHTLParser::ProgramContext::elementStatement(size_t i) {
  return getRuleContext<CHTLParser::ElementStatementContext>(i);
}


size_t CHTLParser::ProgramContext::getRuleIndex() const {
  return CHTLParser::RuleProgram;
}

void CHTLParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void CHTLParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

CHTLParser::ProgramContext* CHTLParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CHTLParser::RuleProgram);
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
    setState(79);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::TEMPLATE)
      | (1ULL << CHTLParser::CUSTOM)
      | (1ULL << CHTLParser::ORIGIN)
      | (1ULL << CHTLParser::CONFIGURATION)
      | (1ULL << CHTLParser::IMPORT)
      | (1ULL << CHTLParser::NAMESPACE)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(77);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CHTLParser::IMPORT: {
          setState(70);
          importStatement();
          break;
        }

        case CHTLParser::NAMESPACE: {
          setState(71);
          namespaceStatement();
          break;
        }

        case CHTLParser::CONFIGURATION: {
          setState(72);
          configurationStatement();
          break;
        }

        case CHTLParser::TEMPLATE: {
          setState(73);
          templateStatement();
          break;
        }

        case CHTLParser::CUSTOM: {
          setState(74);
          customStatement();
          break;
        }

        case CHTLParser::ORIGIN: {
          setState(75);
          originStatement();
          break;
        }

        case CHTLParser::IDENTIFIER: {
          setState(76);
          elementStatement();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(81);
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

//----------------- ImportStatementContext ------------------------------------------------------------------

CHTLParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ImportStatementContext::IMPORT() {
  return getToken(CHTLParser::IMPORT, 0);
}

tree::TerminalNode* CHTLParser::ImportStatementContext::STRING() {
  return getToken(CHTLParser::STRING, 0);
}

tree::TerminalNode* CHTLParser::ImportStatementContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}


size_t CHTLParser::ImportStatementContext::getRuleIndex() const {
  return CHTLParser::RuleImportStatement;
}

void CHTLParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void CHTLParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}

CHTLParser::ImportStatementContext* CHTLParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CHTLParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(CHTLParser::IMPORT);
    setState(83);
    match(CHTLParser::STRING);
    setState(84);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespaceStatementContext ------------------------------------------------------------------

CHTLParser::NamespaceStatementContext::NamespaceStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::NamespaceStatementContext::NAMESPACE() {
  return getToken(CHTLParser::NAMESPACE, 0);
}

tree::TerminalNode* CHTLParser::NamespaceStatementContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::NamespaceStatementContext::EQUALS() {
  return getToken(CHTLParser::EQUALS, 0);
}

tree::TerminalNode* CHTLParser::NamespaceStatementContext::STRING() {
  return getToken(CHTLParser::STRING, 0);
}

tree::TerminalNode* CHTLParser::NamespaceStatementContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}


size_t CHTLParser::NamespaceStatementContext::getRuleIndex() const {
  return CHTLParser::RuleNamespaceStatement;
}

void CHTLParser::NamespaceStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamespaceStatement(this);
}

void CHTLParser::NamespaceStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamespaceStatement(this);
}

CHTLParser::NamespaceStatementContext* CHTLParser::namespaceStatement() {
  NamespaceStatementContext *_localctx = _tracker.createInstance<NamespaceStatementContext>(_ctx, getState());
  enterRule(_localctx, 4, CHTLParser::RuleNamespaceStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(CHTLParser::NAMESPACE);
    setState(87);
    match(CHTLParser::IDENTIFIER);
    setState(88);
    match(CHTLParser::EQUALS);
    setState(89);
    match(CHTLParser::STRING);
    setState(90);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigurationStatementContext ------------------------------------------------------------------

CHTLParser::ConfigurationStatementContext::ConfigurationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ConfigurationStatementContext::CONFIGURATION() {
  return getToken(CHTLParser::CONFIGURATION, 0);
}

tree::TerminalNode* CHTLParser::ConfigurationStatementContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::ConfigurationContentContext* CHTLParser::ConfigurationStatementContext::configurationContent() {
  return getRuleContext<CHTLParser::ConfigurationContentContext>(0);
}

tree::TerminalNode* CHTLParser::ConfigurationStatementContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::ConfigurationStatementContext::getRuleIndex() const {
  return CHTLParser::RuleConfigurationStatement;
}

void CHTLParser::ConfigurationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigurationStatement(this);
}

void CHTLParser::ConfigurationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigurationStatement(this);
}

CHTLParser::ConfigurationStatementContext* CHTLParser::configurationStatement() {
  ConfigurationStatementContext *_localctx = _tracker.createInstance<ConfigurationStatementContext>(_ctx, getState());
  enterRule(_localctx, 6, CHTLParser::RuleConfigurationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(CHTLParser::CONFIGURATION);
    setState(93);
    match(CHTLParser::LBRACE);
    setState(94);
    configurationContent();
    setState(95);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigurationContentContext ------------------------------------------------------------------

CHTLParser::ConfigurationContentContext::ConfigurationContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::KeyValuePairContext *> CHTLParser::ConfigurationContentContext::keyValuePair() {
  return getRuleContexts<CHTLParser::KeyValuePairContext>();
}

CHTLParser::KeyValuePairContext* CHTLParser::ConfigurationContentContext::keyValuePair(size_t i) {
  return getRuleContext<CHTLParser::KeyValuePairContext>(i);
}


size_t CHTLParser::ConfigurationContentContext::getRuleIndex() const {
  return CHTLParser::RuleConfigurationContent;
}

void CHTLParser::ConfigurationContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigurationContent(this);
}

void CHTLParser::ConfigurationContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigurationContent(this);
}

CHTLParser::ConfigurationContentContext* CHTLParser::configurationContent() {
  ConfigurationContentContext *_localctx = _tracker.createInstance<ConfigurationContentContext>(_ctx, getState());
  enterRule(_localctx, 8, CHTLParser::RuleConfigurationContent);
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
    setState(100);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::IDENTIFIER) {
      setState(97);
      keyValuePair();
      setState(102);
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

//----------------- KeyValuePairContext ------------------------------------------------------------------

CHTLParser::KeyValuePairContext::KeyValuePairContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::KeyValuePairContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::KeyValuePairContext::EQUALS() {
  return getToken(CHTLParser::EQUALS, 0);
}

tree::TerminalNode* CHTLParser::KeyValuePairContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::KeyValuePairContext::STRING() {
  return getToken(CHTLParser::STRING, 0);
}

tree::TerminalNode* CHTLParser::KeyValuePairContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}


size_t CHTLParser::KeyValuePairContext::getRuleIndex() const {
  return CHTLParser::RuleKeyValuePair;
}

void CHTLParser::KeyValuePairContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyValuePair(this);
}

void CHTLParser::KeyValuePairContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyValuePair(this);
}

CHTLParser::KeyValuePairContext* CHTLParser::keyValuePair() {
  KeyValuePairContext *_localctx = _tracker.createInstance<KeyValuePairContext>(_ctx, getState());
  enterRule(_localctx, 10, CHTLParser::RuleKeyValuePair);
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
    setState(103);
    match(CHTLParser::IDENTIFIER);
    setState(104);
    match(CHTLParser::EQUALS);
    setState(105);
    _la = _input->LA(1);
    if (!(_la == CHTLParser::NUMBER

    || _la == CHTLParser::STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(106);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateStatementContext ------------------------------------------------------------------

CHTLParser::TemplateStatementContext::TemplateStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TemplateStatementContext::TEMPLATE() {
  return getToken(CHTLParser::TEMPLATE, 0);
}

tree::TerminalNode* CHTLParser::TemplateStatementContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::TemplateStatementContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::TemplateContentContext* CHTLParser::TemplateStatementContext::templateContent() {
  return getRuleContext<CHTLParser::TemplateContentContext>(0);
}

tree::TerminalNode* CHTLParser::TemplateStatementContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::TemplateStatementContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateStatement;
}

void CHTLParser::TemplateStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateStatement(this);
}

void CHTLParser::TemplateStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateStatement(this);
}

CHTLParser::TemplateStatementContext* CHTLParser::templateStatement() {
  TemplateStatementContext *_localctx = _tracker.createInstance<TemplateStatementContext>(_ctx, getState());
  enterRule(_localctx, 12, CHTLParser::RuleTemplateStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    match(CHTLParser::TEMPLATE);
    setState(109);
    match(CHTLParser::IDENTIFIER);
    setState(110);
    match(CHTLParser::LBRACE);
    setState(111);
    templateContent();
    setState(112);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateContentContext ------------------------------------------------------------------

CHTLParser::TemplateContentContext::TemplateContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ElementStatementContext *> CHTLParser::TemplateContentContext::elementStatement() {
  return getRuleContexts<CHTLParser::ElementStatementContext>();
}

CHTLParser::ElementStatementContext* CHTLParser::TemplateContentContext::elementStatement(size_t i) {
  return getRuleContext<CHTLParser::ElementStatementContext>(i);
}

std::vector<CHTLParser::StyleBlockContext *> CHTLParser::TemplateContentContext::styleBlock() {
  return getRuleContexts<CHTLParser::StyleBlockContext>();
}

CHTLParser::StyleBlockContext* CHTLParser::TemplateContentContext::styleBlock(size_t i) {
  return getRuleContext<CHTLParser::StyleBlockContext>(i);
}

std::vector<CHTLParser::ScriptBlockContext *> CHTLParser::TemplateContentContext::scriptBlock() {
  return getRuleContexts<CHTLParser::ScriptBlockContext>();
}

CHTLParser::ScriptBlockContext* CHTLParser::TemplateContentContext::scriptBlock(size_t i) {
  return getRuleContext<CHTLParser::ScriptBlockContext>(i);
}

std::vector<CHTLParser::RawContentContext *> CHTLParser::TemplateContentContext::rawContent() {
  return getRuleContexts<CHTLParser::RawContentContext>();
}

CHTLParser::RawContentContext* CHTLParser::TemplateContentContext::rawContent(size_t i) {
  return getRuleContext<CHTLParser::RawContentContext>(i);
}


size_t CHTLParser::TemplateContentContext::getRuleIndex() const {
  return CHTLParser::RuleTemplateContent;
}

void CHTLParser::TemplateContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateContent(this);
}

void CHTLParser::TemplateContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateContent(this);
}

CHTLParser::TemplateContentContext* CHTLParser::templateContent() {
  TemplateContentContext *_localctx = _tracker.createInstance<TemplateContentContext>(_ctx, getState());
  enterRule(_localctx, 14, CHTLParser::RuleTemplateContent);
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
    setState(118); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(118);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(114);
        elementStatement();
        break;
      }

      case 2: {
        setState(115);
        styleBlock();
        break;
      }

      case 3: {
        setState(116);
        scriptBlock();
        break;
      }

      case 4: {
        setState(117);
        rawContent();
        break;
      }

      default:
        break;
      }
      setState(120); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING)
      | (1ULL << CHTLParser::LITERAL))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomStatementContext ------------------------------------------------------------------

CHTLParser::CustomStatementContext::CustomStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::CustomStatementContext::CUSTOM() {
  return getToken(CHTLParser::CUSTOM, 0);
}

tree::TerminalNode* CHTLParser::CustomStatementContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::CustomStatementContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::CustomContentContext* CHTLParser::CustomStatementContext::customContent() {
  return getRuleContext<CHTLParser::CustomContentContext>(0);
}

tree::TerminalNode* CHTLParser::CustomStatementContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::CustomStatementContext::getRuleIndex() const {
  return CHTLParser::RuleCustomStatement;
}

void CHTLParser::CustomStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomStatement(this);
}

void CHTLParser::CustomStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomStatement(this);
}

CHTLParser::CustomStatementContext* CHTLParser::customStatement() {
  CustomStatementContext *_localctx = _tracker.createInstance<CustomStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, CHTLParser::RuleCustomStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(CHTLParser::CUSTOM);
    setState(123);
    match(CHTLParser::IDENTIFIER);
    setState(124);
    match(CHTLParser::LBRACE);
    setState(125);
    customContent();
    setState(126);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomContentContext ------------------------------------------------------------------

CHTLParser::CustomContentContext::CustomContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ElementStatementContext *> CHTLParser::CustomContentContext::elementStatement() {
  return getRuleContexts<CHTLParser::ElementStatementContext>();
}

CHTLParser::ElementStatementContext* CHTLParser::CustomContentContext::elementStatement(size_t i) {
  return getRuleContext<CHTLParser::ElementStatementContext>(i);
}

std::vector<CHTLParser::StyleBlockContext *> CHTLParser::CustomContentContext::styleBlock() {
  return getRuleContexts<CHTLParser::StyleBlockContext>();
}

CHTLParser::StyleBlockContext* CHTLParser::CustomContentContext::styleBlock(size_t i) {
  return getRuleContext<CHTLParser::StyleBlockContext>(i);
}

std::vector<CHTLParser::ScriptBlockContext *> CHTLParser::CustomContentContext::scriptBlock() {
  return getRuleContexts<CHTLParser::ScriptBlockContext>();
}

CHTLParser::ScriptBlockContext* CHTLParser::CustomContentContext::scriptBlock(size_t i) {
  return getRuleContext<CHTLParser::ScriptBlockContext>(i);
}

std::vector<CHTLParser::RawContentContext *> CHTLParser::CustomContentContext::rawContent() {
  return getRuleContexts<CHTLParser::RawContentContext>();
}

CHTLParser::RawContentContext* CHTLParser::CustomContentContext::rawContent(size_t i) {
  return getRuleContext<CHTLParser::RawContentContext>(i);
}


size_t CHTLParser::CustomContentContext::getRuleIndex() const {
  return CHTLParser::RuleCustomContent;
}

void CHTLParser::CustomContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomContent(this);
}

void CHTLParser::CustomContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomContent(this);
}

CHTLParser::CustomContentContext* CHTLParser::customContent() {
  CustomContentContext *_localctx = _tracker.createInstance<CustomContentContext>(_ctx, getState());
  enterRule(_localctx, 18, CHTLParser::RuleCustomContent);
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
    setState(132); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(132);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(128);
        elementStatement();
        break;
      }

      case 2: {
        setState(129);
        styleBlock();
        break;
      }

      case 3: {
        setState(130);
        scriptBlock();
        break;
      }

      case 4: {
        setState(131);
        rawContent();
        break;
      }

      default:
        break;
      }
      setState(134); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING)
      | (1ULL << CHTLParser::LITERAL))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OriginStatementContext ------------------------------------------------------------------

CHTLParser::OriginStatementContext::OriginStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::OriginStatementContext::ORIGIN() {
  return getToken(CHTLParser::ORIGIN, 0);
}

CHTLParser::OriginTypeContext* CHTLParser::OriginStatementContext::originType() {
  return getRuleContext<CHTLParser::OriginTypeContext>(0);
}

tree::TerminalNode* CHTLParser::OriginStatementContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::OriginContentContext* CHTLParser::OriginStatementContext::originContent() {
  return getRuleContext<CHTLParser::OriginContentContext>(0);
}

tree::TerminalNode* CHTLParser::OriginStatementContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}

tree::TerminalNode* CHTLParser::OriginStatementContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::OriginStatementContext::getRuleIndex() const {
  return CHTLParser::RuleOriginStatement;
}

void CHTLParser::OriginStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginStatement(this);
}

void CHTLParser::OriginStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginStatement(this);
}

CHTLParser::OriginStatementContext* CHTLParser::originStatement() {
  OriginStatementContext *_localctx = _tracker.createInstance<OriginStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, CHTLParser::RuleOriginStatement);
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
    setState(136);
    match(CHTLParser::ORIGIN);
    setState(137);
    originType();
    setState(139);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::IDENTIFIER) {
      setState(138);
      match(CHTLParser::IDENTIFIER);
    }
    setState(141);
    match(CHTLParser::LBRACE);
    setState(142);
    originContent();
    setState(143);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OriginTypeContext ------------------------------------------------------------------

CHTLParser::OriginTypeContext::OriginTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::OriginTypeContext::HTML() {
  return getToken(CHTLParser::HTML, 0);
}

tree::TerminalNode* CHTLParser::OriginTypeContext::CSS() {
  return getToken(CHTLParser::CSS, 0);
}

tree::TerminalNode* CHTLParser::OriginTypeContext::JAVASCRIPT() {
  return getToken(CHTLParser::JAVASCRIPT, 0);
}


size_t CHTLParser::OriginTypeContext::getRuleIndex() const {
  return CHTLParser::RuleOriginType;
}

void CHTLParser::OriginTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginType(this);
}

void CHTLParser::OriginTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginType(this);
}

CHTLParser::OriginTypeContext* CHTLParser::originType() {
  OriginTypeContext *_localctx = _tracker.createInstance<OriginTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, CHTLParser::RuleOriginType);
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
    setState(145);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::HTML)
      | (1ULL << CHTLParser::CSS)
      | (1ULL << CHTLParser::JAVASCRIPT))) != 0))) {
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

//----------------- OriginContentContext ------------------------------------------------------------------

CHTLParser::OriginContentContext::OriginContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ElementStatementContext *> CHTLParser::OriginContentContext::elementStatement() {
  return getRuleContexts<CHTLParser::ElementStatementContext>();
}

CHTLParser::ElementStatementContext* CHTLParser::OriginContentContext::elementStatement(size_t i) {
  return getRuleContext<CHTLParser::ElementStatementContext>(i);
}

std::vector<CHTLParser::StyleBlockContext *> CHTLParser::OriginContentContext::styleBlock() {
  return getRuleContexts<CHTLParser::StyleBlockContext>();
}

CHTLParser::StyleBlockContext* CHTLParser::OriginContentContext::styleBlock(size_t i) {
  return getRuleContext<CHTLParser::StyleBlockContext>(i);
}

std::vector<CHTLParser::ScriptBlockContext *> CHTLParser::OriginContentContext::scriptBlock() {
  return getRuleContexts<CHTLParser::ScriptBlockContext>();
}

CHTLParser::ScriptBlockContext* CHTLParser::OriginContentContext::scriptBlock(size_t i) {
  return getRuleContext<CHTLParser::ScriptBlockContext>(i);
}

std::vector<CHTLParser::RawContentContext *> CHTLParser::OriginContentContext::rawContent() {
  return getRuleContexts<CHTLParser::RawContentContext>();
}

CHTLParser::RawContentContext* CHTLParser::OriginContentContext::rawContent(size_t i) {
  return getRuleContext<CHTLParser::RawContentContext>(i);
}


size_t CHTLParser::OriginContentContext::getRuleIndex() const {
  return CHTLParser::RuleOriginContent;
}

void CHTLParser::OriginContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOriginContent(this);
}

void CHTLParser::OriginContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOriginContent(this);
}

CHTLParser::OriginContentContext* CHTLParser::originContent() {
  OriginContentContext *_localctx = _tracker.createInstance<OriginContentContext>(_ctx, getState());
  enterRule(_localctx, 24, CHTLParser::RuleOriginContent);
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
    setState(151); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(151);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
      case 1: {
        setState(147);
        elementStatement();
        break;
      }

      case 2: {
        setState(148);
        styleBlock();
        break;
      }

      case 3: {
        setState(149);
        scriptBlock();
        break;
      }

      case 4: {
        setState(150);
        rawContent();
        break;
      }

      default:
        break;
      }
      setState(153); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING)
      | (1ULL << CHTLParser::LITERAL))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RawContentContext ------------------------------------------------------------------

CHTLParser::RawContentContext::RawContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::RawContentContext::STRING() {
  return getTokens(CHTLParser::STRING);
}

tree::TerminalNode* CHTLParser::RawContentContext::STRING(size_t i) {
  return getToken(CHTLParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTLParser::RawContentContext::LITERAL() {
  return getTokens(CHTLParser::LITERAL);
}

tree::TerminalNode* CHTLParser::RawContentContext::LITERAL(size_t i) {
  return getToken(CHTLParser::LITERAL, i);
}

std::vector<tree::TerminalNode *> CHTLParser::RawContentContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::RawContentContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CHTLParser::RawContentContext::NUMBER() {
  return getTokens(CHTLParser::NUMBER);
}

tree::TerminalNode* CHTLParser::RawContentContext::NUMBER(size_t i) {
  return getToken(CHTLParser::NUMBER, i);
}


size_t CHTLParser::RawContentContext::getRuleIndex() const {
  return CHTLParser::RuleRawContent;
}

void CHTLParser::RawContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRawContent(this);
}

void CHTLParser::RawContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRawContent(this);
}

CHTLParser::RawContentContext* CHTLParser::rawContent() {
  RawContentContext *_localctx = _tracker.createInstance<RawContentContext>(_ctx, getState());
  enterRule(_localctx, 26, CHTLParser::RuleRawContent);
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
    setState(156); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(155);
              _la = _input->LA(1);
              if (!((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
                | (1ULL << CHTLParser::NUMBER)
                | (1ULL << CHTLParser::STRING)
                | (1ULL << CHTLParser::LITERAL))) != 0))) {
              _errHandler->recoverInline(this);
              }
              else {
                _errHandler->reportMatch(this);
                consume();
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(158); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementStatementContext ------------------------------------------------------------------

CHTLParser::ElementStatementContext::ElementStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::ElementNameContext* CHTLParser::ElementStatementContext::elementName() {
  return getRuleContext<CHTLParser::ElementNameContext>(0);
}

CHTLParser::AttributesContext* CHTLParser::ElementStatementContext::attributes() {
  return getRuleContext<CHTLParser::AttributesContext>(0);
}

tree::TerminalNode* CHTLParser::ElementStatementContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::ElementContentContext* CHTLParser::ElementStatementContext::elementContent() {
  return getRuleContext<CHTLParser::ElementContentContext>(0);
}

tree::TerminalNode* CHTLParser::ElementStatementContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::ElementStatementContext::getRuleIndex() const {
  return CHTLParser::RuleElementStatement;
}

void CHTLParser::ElementStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementStatement(this);
}

void CHTLParser::ElementStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementStatement(this);
}

CHTLParser::ElementStatementContext* CHTLParser::elementStatement() {
  ElementStatementContext *_localctx = _tracker.createInstance<ElementStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, CHTLParser::RuleElementStatement);
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
    setState(160);
    elementName();
    setState(162);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACKET) {
      setState(161);
      attributes();
    }
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CHTLParser::LBRACE) {
      setState(164);
      match(CHTLParser::LBRACE);
      setState(165);
      elementContent();
      setState(166);
      match(CHTLParser::RBRACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementNameContext ------------------------------------------------------------------

CHTLParser::ElementNameContext::ElementNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ElementNameContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ElementNameContext::getRuleIndex() const {
  return CHTLParser::RuleElementName;
}

void CHTLParser::ElementNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementName(this);
}

void CHTLParser::ElementNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementName(this);
}

CHTLParser::ElementNameContext* CHTLParser::elementName() {
  ElementNameContext *_localctx = _tracker.createInstance<ElementNameContext>(_ctx, getState());
  enterRule(_localctx, 30, CHTLParser::RuleElementName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(CHTLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributesContext ------------------------------------------------------------------

CHTLParser::AttributesContext::AttributesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::AttributesContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

CHTLParser::AttributeListContext* CHTLParser::AttributesContext::attributeList() {
  return getRuleContext<CHTLParser::AttributeListContext>(0);
}

tree::TerminalNode* CHTLParser::AttributesContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}


size_t CHTLParser::AttributesContext::getRuleIndex() const {
  return CHTLParser::RuleAttributes;
}

void CHTLParser::AttributesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributes(this);
}

void CHTLParser::AttributesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributes(this);
}

CHTLParser::AttributesContext* CHTLParser::attributes() {
  AttributesContext *_localctx = _tracker.createInstance<AttributesContext>(_ctx, getState());
  enterRule(_localctx, 32, CHTLParser::RuleAttributes);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    match(CHTLParser::LBRACKET);
    setState(173);
    attributeList();
    setState(174);
    match(CHTLParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeListContext ------------------------------------------------------------------

CHTLParser::AttributeListContext::AttributeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::AttributeContext *> CHTLParser::AttributeListContext::attribute() {
  return getRuleContexts<CHTLParser::AttributeContext>();
}

CHTLParser::AttributeContext* CHTLParser::AttributeListContext::attribute(size_t i) {
  return getRuleContext<CHTLParser::AttributeContext>(i);
}

std::vector<tree::TerminalNode *> CHTLParser::AttributeListContext::COMMA() {
  return getTokens(CHTLParser::COMMA);
}

tree::TerminalNode* CHTLParser::AttributeListContext::COMMA(size_t i) {
  return getToken(CHTLParser::COMMA, i);
}


size_t CHTLParser::AttributeListContext::getRuleIndex() const {
  return CHTLParser::RuleAttributeList;
}

void CHTLParser::AttributeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttributeList(this);
}

void CHTLParser::AttributeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttributeList(this);
}

CHTLParser::AttributeListContext* CHTLParser::attributeList() {
  AttributeListContext *_localctx = _tracker.createInstance<AttributeListContext>(_ctx, getState());
  enterRule(_localctx, 34, CHTLParser::RuleAttributeList);
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
    setState(176);
    attribute();
    setState(181);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::COMMA) {
      setState(177);
      match(CHTLParser::COMMA);
      setState(178);
      attribute();
      setState(183);
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

//----------------- AttributeContext ------------------------------------------------------------------

CHTLParser::AttributeContext::AttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::AttributeContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::AttributeContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

tree::TerminalNode* CHTLParser::AttributeContext::EQUALS() {
  return getToken(CHTLParser::EQUALS, 0);
}

tree::TerminalNode* CHTLParser::AttributeContext::STRING() {
  return getToken(CHTLParser::STRING, 0);
}

tree::TerminalNode* CHTLParser::AttributeContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}


size_t CHTLParser::AttributeContext::getRuleIndex() const {
  return CHTLParser::RuleAttribute;
}

void CHTLParser::AttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttribute(this);
}

void CHTLParser::AttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttribute(this);
}

CHTLParser::AttributeContext* CHTLParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 36, CHTLParser::RuleAttribute);
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
    setState(184);
    match(CHTLParser::IDENTIFIER);
    setState(185);
    match(CHTLParser::EQUALS);
    setState(186);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING))) != 0))) {
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

//----------------- ElementContentContext ------------------------------------------------------------------

CHTLParser::ElementContentContext::ElementContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ElementStatementContext *> CHTLParser::ElementContentContext::elementStatement() {
  return getRuleContexts<CHTLParser::ElementStatementContext>();
}

CHTLParser::ElementStatementContext* CHTLParser::ElementContentContext::elementStatement(size_t i) {
  return getRuleContext<CHTLParser::ElementStatementContext>(i);
}

std::vector<CHTLParser::TextBlockContext *> CHTLParser::ElementContentContext::textBlock() {
  return getRuleContexts<CHTLParser::TextBlockContext>();
}

CHTLParser::TextBlockContext* CHTLParser::ElementContentContext::textBlock(size_t i) {
  return getRuleContext<CHTLParser::TextBlockContext>(i);
}

std::vector<CHTLParser::StyleBlockContext *> CHTLParser::ElementContentContext::styleBlock() {
  return getRuleContexts<CHTLParser::StyleBlockContext>();
}

CHTLParser::StyleBlockContext* CHTLParser::ElementContentContext::styleBlock(size_t i) {
  return getRuleContext<CHTLParser::StyleBlockContext>(i);
}

std::vector<CHTLParser::ScriptBlockContext *> CHTLParser::ElementContentContext::scriptBlock() {
  return getRuleContexts<CHTLParser::ScriptBlockContext>();
}

CHTLParser::ScriptBlockContext* CHTLParser::ElementContentContext::scriptBlock(size_t i) {
  return getRuleContext<CHTLParser::ScriptBlockContext>(i);
}

std::vector<CHTLParser::RawContentContext *> CHTLParser::ElementContentContext::rawContent() {
  return getRuleContexts<CHTLParser::RawContentContext>();
}

CHTLParser::RawContentContext* CHTLParser::ElementContentContext::rawContent(size_t i) {
  return getRuleContext<CHTLParser::RawContentContext>(i);
}


size_t CHTLParser::ElementContentContext::getRuleIndex() const {
  return CHTLParser::RuleElementContent;
}

void CHTLParser::ElementContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementContent(this);
}

void CHTLParser::ElementContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementContent(this);
}

CHTLParser::ElementContentContext* CHTLParser::elementContent() {
  ElementContentContext *_localctx = _tracker.createInstance<ElementContentContext>(_ctx, getState());
  enterRule(_localctx, 38, CHTLParser::RuleElementContent);
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
    setState(193); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(193);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(188);
        elementStatement();
        break;
      }

      case 2: {
        setState(189);
        textBlock();
        break;
      }

      case 3: {
        setState(190);
        styleBlock();
        break;
      }

      case 4: {
        setState(191);
        scriptBlock();
        break;
      }

      case 5: {
        setState(192);
        rawContent();
        break;
      }

      default:
        break;
      }
      setState(195); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::STYLE)
      | (1ULL << CHTLParser::TEXT)
      | (1ULL << CHTLParser::SCRIPT)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING)
      | (1ULL << CHTLParser::LITERAL))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TextBlockContext ------------------------------------------------------------------

CHTLParser::TextBlockContext::TextBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::TextBlockContext::TEXT() {
  return getToken(CHTLParser::TEXT, 0);
}

tree::TerminalNode* CHTLParser::TextBlockContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::TextContentContext* CHTLParser::TextBlockContext::textContent() {
  return getRuleContext<CHTLParser::TextContentContext>(0);
}

tree::TerminalNode* CHTLParser::TextBlockContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::TextBlockContext::getRuleIndex() const {
  return CHTLParser::RuleTextBlock;
}

void CHTLParser::TextBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextBlock(this);
}

void CHTLParser::TextBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextBlock(this);
}

CHTLParser::TextBlockContext* CHTLParser::textBlock() {
  TextBlockContext *_localctx = _tracker.createInstance<TextBlockContext>(_ctx, getState());
  enterRule(_localctx, 40, CHTLParser::RuleTextBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    match(CHTLParser::TEXT);
    setState(198);
    match(CHTLParser::LBRACE);
    setState(199);
    textContent();
    setState(200);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TextContentContext ------------------------------------------------------------------

CHTLParser::TextContentContext::TextContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::TextContentContext::STRING() {
  return getTokens(CHTLParser::STRING);
}

tree::TerminalNode* CHTLParser::TextContentContext::STRING(size_t i) {
  return getToken(CHTLParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTLParser::TextContentContext::LITERAL() {
  return getTokens(CHTLParser::LITERAL);
}

tree::TerminalNode* CHTLParser::TextContentContext::LITERAL(size_t i) {
  return getToken(CHTLParser::LITERAL, i);
}

std::vector<tree::TerminalNode *> CHTLParser::TextContentContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::TextContentContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}


size_t CHTLParser::TextContentContext::getRuleIndex() const {
  return CHTLParser::RuleTextContent;
}

void CHTLParser::TextContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextContent(this);
}

void CHTLParser::TextContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextContent(this);
}

CHTLParser::TextContentContext* CHTLParser::textContent() {
  TextContentContext *_localctx = _tracker.createInstance<TextContentContext>(_ctx, getState());
  enterRule(_localctx, 42, CHTLParser::RuleTextContent);
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
    setState(203); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(202);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
        | (1ULL << CHTLParser::STRING)
        | (1ULL << CHTLParser::LITERAL))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(205); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::STRING)
      | (1ULL << CHTLParser::LITERAL))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StyleBlockContext ------------------------------------------------------------------

CHTLParser::StyleBlockContext::StyleBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::StyleBlockContext::STYLE() {
  return getToken(CHTLParser::STYLE, 0);
}

tree::TerminalNode* CHTLParser::StyleBlockContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::StyleContentContext* CHTLParser::StyleBlockContext::styleContent() {
  return getRuleContext<CHTLParser::StyleContentContext>(0);
}

tree::TerminalNode* CHTLParser::StyleBlockContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::StyleBlockContext::getRuleIndex() const {
  return CHTLParser::RuleStyleBlock;
}

void CHTLParser::StyleBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleBlock(this);
}

void CHTLParser::StyleBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleBlock(this);
}

CHTLParser::StyleBlockContext* CHTLParser::styleBlock() {
  StyleBlockContext *_localctx = _tracker.createInstance<StyleBlockContext>(_ctx, getState());
  enterRule(_localctx, 44, CHTLParser::RuleStyleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    match(CHTLParser::STYLE);
    setState(208);
    match(CHTLParser::LBRACE);
    setState(209);
    styleContent();
    setState(210);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StyleContentContext ------------------------------------------------------------------

CHTLParser::StyleContentContext::StyleContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::CssRuleContext *> CHTLParser::StyleContentContext::cssRule() {
  return getRuleContexts<CHTLParser::CssRuleContext>();
}

CHTLParser::CssRuleContext* CHTLParser::StyleContentContext::cssRule(size_t i) {
  return getRuleContext<CHTLParser::CssRuleContext>(i);
}

std::vector<CHTLParser::RawContentContext *> CHTLParser::StyleContentContext::rawContent() {
  return getRuleContexts<CHTLParser::RawContentContext>();
}

CHTLParser::RawContentContext* CHTLParser::StyleContentContext::rawContent(size_t i) {
  return getRuleContext<CHTLParser::RawContentContext>(i);
}


size_t CHTLParser::StyleContentContext::getRuleIndex() const {
  return CHTLParser::RuleStyleContent;
}

void CHTLParser::StyleContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStyleContent(this);
}

void CHTLParser::StyleContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStyleContent(this);
}

CHTLParser::StyleContentContext* CHTLParser::styleContent() {
  StyleContentContext *_localctx = _tracker.createInstance<StyleContentContext>(_ctx, getState());
  enterRule(_localctx, 46, CHTLParser::RuleStyleContent);
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
    setState(214); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(214);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
      case 1: {
        setState(212);
        cssRule();
        break;
      }

      case 2: {
        setState(213);
        rawContent();
        break;
      }

      default:
        break;
      }
      setState(216); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::LBRACE)
      | (1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::DOT)
      | (1ULL << CHTLParser::HASH)
      | (1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING)
      | (1ULL << CHTLParser::LITERAL))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptBlockContext ------------------------------------------------------------------

CHTLParser::ScriptBlockContext::ScriptBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ScriptBlockContext::SCRIPT() {
  return getToken(CHTLParser::SCRIPT, 0);
}

tree::TerminalNode* CHTLParser::ScriptBlockContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::ScriptContentContext* CHTLParser::ScriptBlockContext::scriptContent() {
  return getRuleContext<CHTLParser::ScriptContentContext>(0);
}

tree::TerminalNode* CHTLParser::ScriptBlockContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::ScriptBlockContext::getRuleIndex() const {
  return CHTLParser::RuleScriptBlock;
}

void CHTLParser::ScriptBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScriptBlock(this);
}

void CHTLParser::ScriptBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScriptBlock(this);
}

CHTLParser::ScriptBlockContext* CHTLParser::scriptBlock() {
  ScriptBlockContext *_localctx = _tracker.createInstance<ScriptBlockContext>(_ctx, getState());
  enterRule(_localctx, 48, CHTLParser::RuleScriptBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(CHTLParser::SCRIPT);
    setState(219);
    match(CHTLParser::LBRACE);
    setState(220);
    scriptContent();
    setState(221);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptContentContext ------------------------------------------------------------------

CHTLParser::ScriptContentContext::ScriptContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ElementStatementContext *> CHTLParser::ScriptContentContext::elementStatement() {
  return getRuleContexts<CHTLParser::ElementStatementContext>();
}

CHTLParser::ElementStatementContext* CHTLParser::ScriptContentContext::elementStatement(size_t i) {
  return getRuleContext<CHTLParser::ElementStatementContext>(i);
}

std::vector<tree::TerminalNode *> CHTLParser::ScriptContentContext::STRING() {
  return getTokens(CHTLParser::STRING);
}

tree::TerminalNode* CHTLParser::ScriptContentContext::STRING(size_t i) {
  return getToken(CHTLParser::STRING, i);
}

std::vector<tree::TerminalNode *> CHTLParser::ScriptContentContext::LITERAL() {
  return getTokens(CHTLParser::LITERAL);
}

tree::TerminalNode* CHTLParser::ScriptContentContext::LITERAL(size_t i) {
  return getToken(CHTLParser::LITERAL, i);
}

std::vector<tree::TerminalNode *> CHTLParser::ScriptContentContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::ScriptContentContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

std::vector<CHTLParser::FunctionCallContext *> CHTLParser::ScriptContentContext::functionCall() {
  return getRuleContexts<CHTLParser::FunctionCallContext>();
}

CHTLParser::FunctionCallContext* CHTLParser::ScriptContentContext::functionCall(size_t i) {
  return getRuleContext<CHTLParser::FunctionCallContext>(i);
}

std::vector<CHTLParser::RawContentContext *> CHTLParser::ScriptContentContext::rawContent() {
  return getRuleContexts<CHTLParser::RawContentContext>();
}

CHTLParser::RawContentContext* CHTLParser::ScriptContentContext::rawContent(size_t i) {
  return getRuleContext<CHTLParser::RawContentContext>(i);
}


size_t CHTLParser::ScriptContentContext::getRuleIndex() const {
  return CHTLParser::RuleScriptContent;
}

void CHTLParser::ScriptContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScriptContent(this);
}

void CHTLParser::ScriptContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScriptContent(this);
}

CHTLParser::ScriptContentContext* CHTLParser::scriptContent() {
  ScriptContentContext *_localctx = _tracker.createInstance<ScriptContentContext>(_ctx, getState());
  enterRule(_localctx, 50, CHTLParser::RuleScriptContent);
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
    setState(229); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(229);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
      case 1: {
        setState(223);
        elementStatement();
        break;
      }

      case 2: {
        setState(224);
        match(CHTLParser::STRING);
        break;
      }

      case 3: {
        setState(225);
        match(CHTLParser::LITERAL);
        break;
      }

      case 4: {
        setState(226);
        match(CHTLParser::IDENTIFIER);
        break;
      }

      case 5: {
        setState(227);
        functionCall();
        break;
      }

      case 6: {
        setState(228);
        rawContent();
        break;
      }

      default:
        break;
      }
      setState(231); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING)
      | (1ULL << CHTLParser::LITERAL))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CssRuleContext ------------------------------------------------------------------

CHTLParser::CssRuleContext::CssRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CHTLParser::SelectorContext* CHTLParser::CssRuleContext::selector() {
  return getRuleContext<CHTLParser::SelectorContext>(0);
}

tree::TerminalNode* CHTLParser::CssRuleContext::LBRACE() {
  return getToken(CHTLParser::LBRACE, 0);
}

CHTLParser::CssPropertiesContext* CHTLParser::CssRuleContext::cssProperties() {
  return getRuleContext<CHTLParser::CssPropertiesContext>(0);
}

tree::TerminalNode* CHTLParser::CssRuleContext::RBRACE() {
  return getToken(CHTLParser::RBRACE, 0);
}


size_t CHTLParser::CssRuleContext::getRuleIndex() const {
  return CHTLParser::RuleCssRule;
}

void CHTLParser::CssRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCssRule(this);
}

void CHTLParser::CssRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCssRule(this);
}

CHTLParser::CssRuleContext* CHTLParser::cssRule() {
  CssRuleContext *_localctx = _tracker.createInstance<CssRuleContext>(_ctx, getState());
  enterRule(_localctx, 52, CHTLParser::RuleCssRule);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(233);
    selector();
    setState(234);
    match(CHTLParser::LBRACE);
    setState(235);
    cssProperties();
    setState(236);
    match(CHTLParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorContext ------------------------------------------------------------------

CHTLParser::SelectorContext::SelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::SelectorContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::SelectorContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CHTLParser::SelectorContext::HASH() {
  return getTokens(CHTLParser::HASH);
}

tree::TerminalNode* CHTLParser::SelectorContext::HASH(size_t i) {
  return getToken(CHTLParser::HASH, i);
}

std::vector<tree::TerminalNode *> CHTLParser::SelectorContext::DOT() {
  return getTokens(CHTLParser::DOT);
}

tree::TerminalNode* CHTLParser::SelectorContext::DOT(size_t i) {
  return getToken(CHTLParser::DOT, i);
}

std::vector<CHTLParser::SelectorWithContextContext *> CHTLParser::SelectorContext::selectorWithContext() {
  return getRuleContexts<CHTLParser::SelectorWithContextContext>();
}

CHTLParser::SelectorWithContextContext* CHTLParser::SelectorContext::selectorWithContext(size_t i) {
  return getRuleContext<CHTLParser::SelectorWithContextContext>(i);
}


size_t CHTLParser::SelectorContext::getRuleIndex() const {
  return CHTLParser::RuleSelector;
}

void CHTLParser::SelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelector(this);
}

void CHTLParser::SelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelector(this);
}

CHTLParser::SelectorContext* CHTLParser::selector() {
  SelectorContext *_localctx = _tracker.createInstance<SelectorContext>(_ctx, getState());
  enterRule(_localctx, 54, CHTLParser::RuleSelector);
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
    setState(245);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::LBRACKET)
      | (1ULL << CHTLParser::DOT)
      | (1ULL << CHTLParser::HASH)
      | (1ULL << CHTLParser::IDENTIFIER))) != 0)) {
      setState(243);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CHTLParser::IDENTIFIER: {
          setState(238);
          match(CHTLParser::IDENTIFIER);
          break;
        }

        case CHTLParser::HASH: {
          setState(239);
          match(CHTLParser::HASH);
          break;
        }

        case CHTLParser::DOT: {
          setState(240);
          match(CHTLParser::DOT);
          setState(241);
          match(CHTLParser::IDENTIFIER);
          break;
        }

        case CHTLParser::LBRACKET: {
          setState(242);
          selectorWithContext();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(247);
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

//----------------- SelectorWithContextContext ------------------------------------------------------------------

CHTLParser::SelectorWithContextContext::SelectorWithContextContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::SelectorWithContextContext::LBRACKET() {
  return getToken(CHTLParser::LBRACKET, 0);
}

CHTLParser::ContextSelectorContext* CHTLParser::SelectorWithContextContext::contextSelector() {
  return getRuleContext<CHTLParser::ContextSelectorContext>(0);
}

tree::TerminalNode* CHTLParser::SelectorWithContextContext::RBRACKET() {
  return getToken(CHTLParser::RBRACKET, 0);
}


size_t CHTLParser::SelectorWithContextContext::getRuleIndex() const {
  return CHTLParser::RuleSelectorWithContext;
}

void CHTLParser::SelectorWithContextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectorWithContext(this);
}

void CHTLParser::SelectorWithContextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectorWithContext(this);
}

CHTLParser::SelectorWithContextContext* CHTLParser::selectorWithContext() {
  SelectorWithContextContext *_localctx = _tracker.createInstance<SelectorWithContextContext>(_ctx, getState());
  enterRule(_localctx, 56, CHTLParser::RuleSelectorWithContext);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(248);
    match(CHTLParser::LBRACKET);
    setState(249);
    contextSelector();
    setState(250);
    match(CHTLParser::RBRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContextSelectorContext ------------------------------------------------------------------

CHTLParser::ContextSelectorContext::ContextSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::ContextSelectorContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::ContextSelectorContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CHTLParser::ContextSelectorContext::COMMA() {
  return getTokens(CHTLParser::COMMA);
}

tree::TerminalNode* CHTLParser::ContextSelectorContext::COMMA(size_t i) {
  return getToken(CHTLParser::COMMA, i);
}


size_t CHTLParser::ContextSelectorContext::getRuleIndex() const {
  return CHTLParser::RuleContextSelector;
}

void CHTLParser::ContextSelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContextSelector(this);
}

void CHTLParser::ContextSelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContextSelector(this);
}

CHTLParser::ContextSelectorContext* CHTLParser::contextSelector() {
  ContextSelectorContext *_localctx = _tracker.createInstance<ContextSelectorContext>(_ctx, getState());
  enterRule(_localctx, 58, CHTLParser::RuleContextSelector);
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
    setState(252);
    match(CHTLParser::IDENTIFIER);
    setState(257);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::COMMA) {
      setState(253);
      match(CHTLParser::COMMA);
      setState(254);
      match(CHTLParser::IDENTIFIER);
      setState(259);
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

//----------------- CssPropertiesContext ------------------------------------------------------------------

CHTLParser::CssPropertiesContext::CssPropertiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::CssPropertyContext *> CHTLParser::CssPropertiesContext::cssProperty() {
  return getRuleContexts<CHTLParser::CssPropertyContext>();
}

CHTLParser::CssPropertyContext* CHTLParser::CssPropertiesContext::cssProperty(size_t i) {
  return getRuleContext<CHTLParser::CssPropertyContext>(i);
}


size_t CHTLParser::CssPropertiesContext::getRuleIndex() const {
  return CHTLParser::RuleCssProperties;
}

void CHTLParser::CssPropertiesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCssProperties(this);
}

void CHTLParser::CssPropertiesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCssProperties(this);
}

CHTLParser::CssPropertiesContext* CHTLParser::cssProperties() {
  CssPropertiesContext *_localctx = _tracker.createInstance<CssPropertiesContext>(_ctx, getState());
  enterRule(_localctx, 60, CHTLParser::RuleCssProperties);
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
    setState(263);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::IDENTIFIER) {
      setState(260);
      cssProperty();
      setState(265);
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

//----------------- CssPropertyContext ------------------------------------------------------------------

CHTLParser::CssPropertyContext::CssPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CHTLParser::CssPropertyContext::IDENTIFIER() {
  return getTokens(CHTLParser::IDENTIFIER);
}

tree::TerminalNode* CHTLParser::CssPropertyContext::IDENTIFIER(size_t i) {
  return getToken(CHTLParser::IDENTIFIER, i);
}

tree::TerminalNode* CHTLParser::CssPropertyContext::COLON() {
  return getToken(CHTLParser::COLON, 0);
}

tree::TerminalNode* CHTLParser::CssPropertyContext::SEMICOLON() {
  return getToken(CHTLParser::SEMICOLON, 0);
}

tree::TerminalNode* CHTLParser::CssPropertyContext::STRING() {
  return getToken(CHTLParser::STRING, 0);
}

tree::TerminalNode* CHTLParser::CssPropertyContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}


size_t CHTLParser::CssPropertyContext::getRuleIndex() const {
  return CHTLParser::RuleCssProperty;
}

void CHTLParser::CssPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCssProperty(this);
}

void CHTLParser::CssPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCssProperty(this);
}

CHTLParser::CssPropertyContext* CHTLParser::cssProperty() {
  CssPropertyContext *_localctx = _tracker.createInstance<CssPropertyContext>(_ctx, getState());
  enterRule(_localctx, 62, CHTLParser::RuleCssProperty);
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
    match(CHTLParser::IDENTIFIER);
    setState(267);
    match(CHTLParser::COLON);
    setState(268);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(269);
    match(CHTLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

CHTLParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::FunctionCallContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}

tree::TerminalNode* CHTLParser::FunctionCallContext::LPAREN() {
  return getToken(CHTLParser::LPAREN, 0);
}

tree::TerminalNode* CHTLParser::FunctionCallContext::RPAREN() {
  return getToken(CHTLParser::RPAREN, 0);
}

CHTLParser::ArgumentListContext* CHTLParser::FunctionCallContext::argumentList() {
  return getRuleContext<CHTLParser::ArgumentListContext>(0);
}


size_t CHTLParser::FunctionCallContext::getRuleIndex() const {
  return CHTLParser::RuleFunctionCall;
}

void CHTLParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void CHTLParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

CHTLParser::FunctionCallContext* CHTLParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 64, CHTLParser::RuleFunctionCall);
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
    setState(271);
    match(CHTLParser::IDENTIFIER);
    setState(272);
    match(CHTLParser::LPAREN);
    setState(274);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING))) != 0)) {
      setState(273);
      argumentList();
    }
    setState(276);
    match(CHTLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

CHTLParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CHTLParser::ArgumentContext *> CHTLParser::ArgumentListContext::argument() {
  return getRuleContexts<CHTLParser::ArgumentContext>();
}

CHTLParser::ArgumentContext* CHTLParser::ArgumentListContext::argument(size_t i) {
  return getRuleContext<CHTLParser::ArgumentContext>(i);
}

std::vector<tree::TerminalNode *> CHTLParser::ArgumentListContext::COMMA() {
  return getTokens(CHTLParser::COMMA);
}

tree::TerminalNode* CHTLParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(CHTLParser::COMMA, i);
}


size_t CHTLParser::ArgumentListContext::getRuleIndex() const {
  return CHTLParser::RuleArgumentList;
}

void CHTLParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void CHTLParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}

CHTLParser::ArgumentListContext* CHTLParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 66, CHTLParser::RuleArgumentList);
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
    argument();
    setState(283);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CHTLParser::COMMA) {
      setState(279);
      match(CHTLParser::COMMA);
      setState(280);
      argument();
      setState(285);
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

//----------------- ArgumentContext ------------------------------------------------------------------

CHTLParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CHTLParser::ArgumentContext::STRING() {
  return getToken(CHTLParser::STRING, 0);
}

tree::TerminalNode* CHTLParser::ArgumentContext::NUMBER() {
  return getToken(CHTLParser::NUMBER, 0);
}

tree::TerminalNode* CHTLParser::ArgumentContext::IDENTIFIER() {
  return getToken(CHTLParser::IDENTIFIER, 0);
}


size_t CHTLParser::ArgumentContext::getRuleIndex() const {
  return CHTLParser::RuleArgument;
}

void CHTLParser::ArgumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgument(this);
}

void CHTLParser::ArgumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CHTLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgument(this);
}

CHTLParser::ArgumentContext* CHTLParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 68, CHTLParser::RuleArgument);
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
    setState(286);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CHTLParser::IDENTIFIER)
      | (1ULL << CHTLParser::NUMBER)
      | (1ULL << CHTLParser::STRING))) != 0))) {
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

// Static vars and initialization.
std::vector<dfa::DFA> CHTLParser::_decisionToDFA;
atn::PredictionContextCache CHTLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CHTLParser::_atn;
std::vector<uint16_t> CHTLParser::_serializedATN;

std::vector<std::string> CHTLParser::_ruleNames = {
  "program", "importStatement", "namespaceStatement", "configurationStatement", 
  "configurationContent", "keyValuePair", "templateStatement", "templateContent", 
  "customStatement", "customContent", "originStatement", "originType", "originContent", 
  "rawContent", "elementStatement", "elementName", "attributes", "attributeList", 
  "attribute", "elementContent", "textBlock", "textContent", "styleBlock", 
  "styleContent", "scriptBlock", "scriptContent", "cssRule", "selector", 
  "selectorWithContext", "contextSelector", "cssProperties", "cssProperty", 
  "functionCall", "argumentList", "argument"
};

std::vector<std::string> CHTLParser::_literalNames = {
  "", "", "", "", "", "'[Template]'", "'[Custom]'", "'[Origin]'", "'[Configuration]'", 
  "'[Import]'", "'[Namespace]'", "'[Info]'", "'[Export]'", "'[Style]'", 
  "'[Element]'", "'[Var]'", "'[HTML]'", "'[CSS]'", "'[JavaScript]'", "'[CHTL]'", 
  "'[Inherit]'", "'[Delete]'", "'[Insert]'", "'[After]'", "'[Before]'", 
  "'[Replace]'", "'[AtTop]'", "'[AtBottom]'", "'[From]'", "'[As]'", "'[Except]'", 
  "'[Text]'", "'[StyleBlock]'", "'[Script]'", "'{'", "'}'", "'['", "']'", 
  "'('", "')'", "';'", "':'", "'='", "','", "", "'#'"
};

std::vector<std::string> CHTLParser::_symbolicNames = {
  "", "WS", "COMMENT", "MULTILINE_COMMENT", "GENERATOR_COMMENT", "TEMPLATE", 
  "CUSTOM", "ORIGIN", "CONFIGURATION", "IMPORT", "NAMESPACE", "INFO", "EXPORT", 
  "STYLE", "ELEMENT", "VAR", "HTML", "CSS", "JAVASCRIPT", "CHTL", "INHERIT", 
  "DELETE", "INSERT", "AFTER", "BEFORE", "REPLACE", "AT_TOP", "AT_BOTTOM", 
  "FROM", "AS", "EXCEPT", "TEXT", "STYLE_BLOCK", "SCRIPT", "LBRACE", "RBRACE", 
  "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "SEMICOLON", "COLON", "EQUALS", 
  "COMMA", "DOT", "HASH", "PERIOD", "IDENTIFIER", "NUMBER", "STRING", "LITERAL"
};

dfa::Vocabulary CHTLParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CHTLParser::_tokenNames;

CHTLParser::Initializer::Initializer() {
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
       0x3, 0x34, 0x123, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x50, 0xa, 0x2, 0xc, 
       0x2, 0xe, 0x2, 0x53, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x7, 
       0x6, 0x65, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x68, 0xb, 0x6, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 
       0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
       0x3, 0x9, 0x6, 0x9, 0x79, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 0x7a, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 
       0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x6, 0xb, 0x87, 0xa, 0xb, 0xd, 0xb, 
       0xe, 0xb, 0x88, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x8e, 0xa, 
       0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x6, 0xe, 0x9a, 0xa, 0xe, 
       0xd, 0xe, 0xe, 0xe, 0x9b, 0x3, 0xf, 0x6, 0xf, 0x9f, 0xa, 0xf, 0xd, 
       0xf, 0xe, 0xf, 0xa0, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xa5, 0xa, 
       0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xab, 
       0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
       0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xb6, 0xa, 
       0x13, 0xc, 0x13, 0xe, 0x13, 0xb9, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 
       0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
       0x3, 0x15, 0x6, 0x15, 0xc4, 0xa, 0x15, 0xd, 0x15, 0xe, 0x15, 0xc5, 
       0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
       0x6, 0x17, 0xce, 0xa, 0x17, 0xd, 0x17, 0xe, 0x17, 0xcf, 0x3, 0x18, 
       0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 
       0x6, 0x19, 0xd9, 0xa, 0x19, 0xd, 0x19, 0xe, 0x19, 0xda, 0x3, 0x1a, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 
       0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x6, 0x1b, 0xe8, 0xa, 
       0x1b, 0xd, 0x1b, 0xe, 0x1b, 0xe9, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
       0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
       0x3, 0x1d, 0x7, 0x1d, 0xf6, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0xf9, 
       0xb, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 
       0x3, 0x1f, 0x3, 0x1f, 0x7, 0x1f, 0x102, 0xa, 0x1f, 0xc, 0x1f, 0xe, 
       0x1f, 0x105, 0xb, 0x1f, 0x3, 0x20, 0x7, 0x20, 0x108, 0xa, 0x20, 0xc, 
       0x20, 0xe, 0x20, 0x10b, 0xb, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
       0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 
       0x115, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 
       0x23, 0x7, 0x23, 0x11c, 0xa, 0x23, 0xc, 0x23, 0xe, 0x23, 0x11f, 0xb, 
       0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x2, 0x2, 0x25, 0x2, 0x4, 
       0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
       0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 
       0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x2, 
       0x7, 0x3, 0x2, 0x32, 0x33, 0x3, 0x2, 0x12, 0x14, 0x3, 0x2, 0x31, 
       0x34, 0x3, 0x2, 0x31, 0x33, 0x4, 0x2, 0x31, 0x31, 0x33, 0x34, 0x2, 
       0x12e, 0x2, 0x51, 0x3, 0x2, 0x2, 0x2, 0x4, 0x54, 0x3, 0x2, 0x2, 0x2, 
       0x6, 0x58, 0x3, 0x2, 0x2, 0x2, 0x8, 0x5e, 0x3, 0x2, 0x2, 0x2, 0xa, 
       0x66, 0x3, 0x2, 0x2, 0x2, 0xc, 0x69, 0x3, 0x2, 0x2, 0x2, 0xe, 0x6e, 
       0x3, 0x2, 0x2, 0x2, 0x10, 0x78, 0x3, 0x2, 0x2, 0x2, 0x12, 0x7c, 0x3, 
       0x2, 0x2, 0x2, 0x14, 0x86, 0x3, 0x2, 0x2, 0x2, 0x16, 0x8a, 0x3, 0x2, 
       0x2, 0x2, 0x18, 0x93, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x99, 0x3, 0x2, 0x2, 
       0x2, 0x1c, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xa2, 0x3, 0x2, 0x2, 0x2, 
       0x20, 0xac, 0x3, 0x2, 0x2, 0x2, 0x22, 0xae, 0x3, 0x2, 0x2, 0x2, 0x24, 
       0xb2, 0x3, 0x2, 0x2, 0x2, 0x26, 0xba, 0x3, 0x2, 0x2, 0x2, 0x28, 0xc3, 
       0x3, 0x2, 0x2, 0x2, 0x2a, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xcd, 0x3, 
       0x2, 0x2, 0x2, 0x2e, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x30, 0xd8, 0x3, 0x2, 
       0x2, 0x2, 0x32, 0xdc, 0x3, 0x2, 0x2, 0x2, 0x34, 0xe7, 0x3, 0x2, 0x2, 
       0x2, 0x36, 0xeb, 0x3, 0x2, 0x2, 0x2, 0x38, 0xf7, 0x3, 0x2, 0x2, 0x2, 
       0x3a, 0xfa, 0x3, 0x2, 0x2, 0x2, 0x3c, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x3e, 
       0x109, 0x3, 0x2, 0x2, 0x2, 0x40, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x42, 
       0x111, 0x3, 0x2, 0x2, 0x2, 0x44, 0x118, 0x3, 0x2, 0x2, 0x2, 0x46, 
       0x120, 0x3, 0x2, 0x2, 0x2, 0x48, 0x50, 0x5, 0x4, 0x3, 0x2, 0x49, 
       0x50, 0x5, 0x6, 0x4, 0x2, 0x4a, 0x50, 0x5, 0x8, 0x5, 0x2, 0x4b, 0x50, 
       0x5, 0xe, 0x8, 0x2, 0x4c, 0x50, 0x5, 0x12, 0xa, 0x2, 0x4d, 0x50, 
       0x5, 0x16, 0xc, 0x2, 0x4e, 0x50, 0x5, 0x1e, 0x10, 0x2, 0x4f, 0x48, 
       0x3, 0x2, 0x2, 0x2, 0x4f, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4a, 0x3, 
       0x2, 0x2, 0x2, 0x4f, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4c, 0x3, 0x2, 
       0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 
       0x2, 0x50, 0x53, 0x3, 0x2, 0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 
       0x51, 0x52, 0x3, 0x2, 0x2, 0x2, 0x52, 0x3, 0x3, 0x2, 0x2, 0x2, 0x53, 
       0x51, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x7, 0xb, 0x2, 0x2, 0x55, 0x56, 
       0x7, 0x33, 0x2, 0x2, 0x56, 0x57, 0x7, 0x2a, 0x2, 0x2, 0x57, 0x5, 
       0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x7, 0xc, 0x2, 0x2, 0x59, 0x5a, 0x7, 
       0x31, 0x2, 0x2, 0x5a, 0x5b, 0x7, 0x2c, 0x2, 0x2, 0x5b, 0x5c, 0x7, 
       0x33, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x2a, 0x2, 0x2, 0x5d, 0x7, 0x3, 
       0x2, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0xa, 0x2, 0x2, 0x5f, 0x60, 0x7, 0x24, 
       0x2, 0x2, 0x60, 0x61, 0x5, 0xa, 0x6, 0x2, 0x61, 0x62, 0x7, 0x25, 
       0x2, 0x2, 0x62, 0x9, 0x3, 0x2, 0x2, 0x2, 0x63, 0x65, 0x5, 0xc, 0x7, 
       0x2, 0x64, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 0x68, 0x3, 0x2, 0x2, 0x2, 
       0x66, 0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x3, 0x2, 0x2, 0x2, 0x67, 
       0xb, 0x3, 0x2, 0x2, 0x2, 0x68, 0x66, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 
       0x7, 0x31, 0x2, 0x2, 0x6a, 0x6b, 0x7, 0x2c, 0x2, 0x2, 0x6b, 0x6c, 
       0x9, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x7, 0x2a, 0x2, 0x2, 0x6d, 0xd, 0x3, 
       0x2, 0x2, 0x2, 0x6e, 0x6f, 0x7, 0x7, 0x2, 0x2, 0x6f, 0x70, 0x7, 0x31, 
       0x2, 0x2, 0x70, 0x71, 0x7, 0x24, 0x2, 0x2, 0x71, 0x72, 0x5, 0x10, 
       0x9, 0x2, 0x72, 0x73, 0x7, 0x25, 0x2, 0x2, 0x73, 0xf, 0x3, 0x2, 0x2, 
       0x2, 0x74, 0x79, 0x5, 0x1e, 0x10, 0x2, 0x75, 0x79, 0x5, 0x2e, 0x18, 
       0x2, 0x76, 0x79, 0x5, 0x32, 0x1a, 0x2, 0x77, 0x79, 0x5, 0x1c, 0xf, 
       0x2, 0x78, 0x74, 0x3, 0x2, 0x2, 0x2, 0x78, 0x75, 0x3, 0x2, 0x2, 0x2, 
       0x78, 0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x77, 0x3, 0x2, 0x2, 0x2, 0x79, 
       0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x78, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 
       0x3, 0x2, 0x2, 0x2, 0x7b, 0x11, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x7, 
       0x8, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x31, 0x2, 0x2, 0x7e, 0x7f, 0x7, 
       0x24, 0x2, 0x2, 0x7f, 0x80, 0x5, 0x14, 0xb, 0x2, 0x80, 0x81, 0x7, 
       0x25, 0x2, 0x2, 0x81, 0x13, 0x3, 0x2, 0x2, 0x2, 0x82, 0x87, 0x5, 
       0x1e, 0x10, 0x2, 0x83, 0x87, 0x5, 0x2e, 0x18, 0x2, 0x84, 0x87, 0x5, 
       0x32, 0x1a, 0x2, 0x85, 0x87, 0x5, 0x1c, 0xf, 0x2, 0x86, 0x82, 0x3, 
       0x2, 0x2, 0x2, 0x86, 0x83, 0x3, 0x2, 0x2, 0x2, 0x86, 0x84, 0x3, 0x2, 
       0x2, 0x2, 0x86, 0x85, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 0x3, 0x2, 0x2, 
       0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x3, 0x2, 0x2, 0x2, 
       0x89, 0x15, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0x9, 0x2, 0x2, 0x8b, 
       0x8d, 0x5, 0x18, 0xd, 0x2, 0x8c, 0x8e, 0x7, 0x31, 0x2, 0x2, 0x8d, 
       0x8c, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 
       0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 0x7, 0x24, 0x2, 0x2, 0x90, 0x91, 
       0x5, 0x1a, 0xe, 0x2, 0x91, 0x92, 0x7, 0x25, 0x2, 0x2, 0x92, 0x17, 
       0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x9, 0x3, 0x2, 0x2, 0x94, 0x19, 0x3, 
       0x2, 0x2, 0x2, 0x95, 0x9a, 0x5, 0x1e, 0x10, 0x2, 0x96, 0x9a, 0x5, 
       0x2e, 0x18, 0x2, 0x97, 0x9a, 0x5, 0x32, 0x1a, 0x2, 0x98, 0x9a, 0x5, 
       0x1c, 0xf, 0x2, 0x99, 0x95, 0x3, 0x2, 0x2, 0x2, 0x99, 0x96, 0x3, 
       0x2, 0x2, 0x2, 0x99, 0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x98, 0x3, 0x2, 
       0x2, 0x2, 0x9a, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x99, 0x3, 0x2, 0x2, 
       0x2, 0x9b, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x1b, 0x3, 0x2, 0x2, 0x2, 
       0x9d, 0x9f, 0x9, 0x4, 0x2, 0x2, 0x9e, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9f, 
       0xa0, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 
       0x3, 0x2, 0x2, 0x2, 0xa1, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa4, 0x5, 
       0x20, 0x11, 0x2, 0xa3, 0xa5, 0x5, 0x22, 0x12, 0x2, 0xa4, 0xa3, 0x3, 
       0x2, 0x2, 0x2, 0xa4, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xaa, 0x3, 0x2, 
       0x2, 0x2, 0xa6, 0xa7, 0x7, 0x24, 0x2, 0x2, 0xa7, 0xa8, 0x5, 0x28, 
       0x15, 0x2, 0xa8, 0xa9, 0x7, 0x25, 0x2, 0x2, 0xa9, 0xab, 0x3, 0x2, 
       0x2, 0x2, 0xaa, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x3, 0x2, 0x2, 
       0x2, 0xab, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x7, 0x31, 0x2, 
       0x2, 0xad, 0x21, 0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x7, 0x26, 0x2, 
       0x2, 0xaf, 0xb0, 0x5, 0x24, 0x13, 0x2, 0xb0, 0xb1, 0x7, 0x27, 0x2, 
       0x2, 0xb1, 0x23, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb7, 0x5, 0x26, 0x14, 
       0x2, 0xb3, 0xb4, 0x7, 0x2d, 0x2, 0x2, 0xb4, 0xb6, 0x5, 0x26, 0x14, 
       0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb9, 0x3, 0x2, 0x2, 0x2, 
       0xb7, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb8, 
       0x25, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 
       0x7, 0x31, 0x2, 0x2, 0xbb, 0xbc, 0x7, 0x2c, 0x2, 0x2, 0xbc, 0xbd, 
       0x9, 0x5, 0x2, 0x2, 0xbd, 0x27, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xc4, 0x5, 
       0x1e, 0x10, 0x2, 0xbf, 0xc4, 0x5, 0x2a, 0x16, 0x2, 0xc0, 0xc4, 0x5, 
       0x2e, 0x18, 0x2, 0xc1, 0xc4, 0x5, 0x32, 0x1a, 0x2, 0xc2, 0xc4, 0x5, 
       0x1c, 0xf, 0x2, 0xc3, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xbf, 0x3, 
       0x2, 0x2, 0x2, 0xc3, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc1, 0x3, 0x2, 
       0x2, 0x2, 0xc3, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x3, 0x2, 0x2, 
       0x2, 0xc5, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 
       0xc6, 0x29, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x7, 0x21, 0x2, 0x2, 
       0xc8, 0xc9, 0x7, 0x24, 0x2, 0x2, 0xc9, 0xca, 0x5, 0x2c, 0x17, 0x2, 
       0xca, 0xcb, 0x7, 0x25, 0x2, 0x2, 0xcb, 0x2b, 0x3, 0x2, 0x2, 0x2, 
       0xcc, 0xce, 0x9, 0x6, 0x2, 0x2, 0xcd, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xce, 
       0xcf, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xd0, 
       0x3, 0x2, 0x2, 0x2, 0xd0, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x7, 
       0xf, 0x2, 0x2, 0xd2, 0xd3, 0x7, 0x24, 0x2, 0x2, 0xd3, 0xd4, 0x5, 
       0x30, 0x19, 0x2, 0xd4, 0xd5, 0x7, 0x25, 0x2, 0x2, 0xd5, 0x2f, 0x3, 
       0x2, 0x2, 0x2, 0xd6, 0xd9, 0x5, 0x36, 0x1c, 0x2, 0xd7, 0xd9, 0x5, 
       0x1c, 0xf, 0x2, 0xd8, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd7, 0x3, 
       0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 0x2, 0x2, 0x2, 0xda, 0xd8, 0x3, 0x2, 
       0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdb, 0x31, 0x3, 0x2, 0x2, 
       0x2, 0xdc, 0xdd, 0x7, 0x23, 0x2, 0x2, 0xdd, 0xde, 0x7, 0x24, 0x2, 
       0x2, 0xde, 0xdf, 0x5, 0x34, 0x1b, 0x2, 0xdf, 0xe0, 0x7, 0x25, 0x2, 
       0x2, 0xe0, 0x33, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe8, 0x5, 0x1e, 0x10, 
       0x2, 0xe2, 0xe8, 0x7, 0x33, 0x2, 0x2, 0xe3, 0xe8, 0x7, 0x34, 0x2, 
       0x2, 0xe4, 0xe8, 0x7, 0x31, 0x2, 0x2, 0xe5, 0xe8, 0x5, 0x42, 0x22, 
       0x2, 0xe6, 0xe8, 0x5, 0x1c, 0xf, 0x2, 0xe7, 0xe1, 0x3, 0x2, 0x2, 
       0x2, 0xe7, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe3, 0x3, 0x2, 0x2, 0x2, 
       0xe7, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe7, 
       0xe6, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xe7, 
       0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x3, 0x2, 0x2, 0x2, 0xea, 0x35, 0x3, 
       0x2, 0x2, 0x2, 0xeb, 0xec, 0x5, 0x38, 0x1d, 0x2, 0xec, 0xed, 0x7, 
       0x24, 0x2, 0x2, 0xed, 0xee, 0x5, 0x3e, 0x20, 0x2, 0xee, 0xef, 0x7, 
       0x25, 0x2, 0x2, 0xef, 0x37, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf6, 0x7, 
       0x31, 0x2, 0x2, 0xf1, 0xf6, 0x7, 0x2f, 0x2, 0x2, 0xf2, 0xf3, 0x7, 
       0x2e, 0x2, 0x2, 0xf3, 0xf6, 0x7, 0x31, 0x2, 0x2, 0xf4, 0xf6, 0x5, 
       0x3a, 0x1e, 0x2, 0xf5, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf1, 0x3, 
       0x2, 0x2, 0x2, 0xf5, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf4, 0x3, 0x2, 
       0x2, 0x2, 0xf6, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf5, 0x3, 0x2, 0x2, 
       0x2, 0xf7, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf8, 0x39, 0x3, 0x2, 0x2, 0x2, 
       0xf9, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 0x7, 0x26, 0x2, 0x2, 
       0xfb, 0xfc, 0x5, 0x3c, 0x1f, 0x2, 0xfc, 0xfd, 0x7, 0x27, 0x2, 0x2, 
       0xfd, 0x3b, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x103, 0x7, 0x31, 0x2, 0x2, 
       0xff, 0x100, 0x7, 0x2d, 0x2, 0x2, 0x100, 0x102, 0x7, 0x31, 0x2, 0x2, 
       0x101, 0xff, 0x3, 0x2, 0x2, 0x2, 0x102, 0x105, 0x3, 0x2, 0x2, 0x2, 
       0x103, 0x101, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 
       0x104, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x105, 0x103, 0x3, 0x2, 0x2, 0x2, 
       0x106, 0x108, 0x5, 0x40, 0x21, 0x2, 0x107, 0x106, 0x3, 0x2, 0x2, 
       0x2, 0x108, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x109, 0x107, 0x3, 0x2, 0x2, 
       0x2, 0x109, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x3f, 0x3, 0x2, 0x2, 
       0x2, 0x10b, 0x109, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10d, 0x7, 0x31, 0x2, 
       0x2, 0x10d, 0x10e, 0x7, 0x2b, 0x2, 0x2, 0x10e, 0x10f, 0x9, 0x5, 0x2, 
       0x2, 0x10f, 0x110, 0x7, 0x2a, 0x2, 0x2, 0x110, 0x41, 0x3, 0x2, 0x2, 
       0x2, 0x111, 0x112, 0x7, 0x31, 0x2, 0x2, 0x112, 0x114, 0x7, 0x28, 
       0x2, 0x2, 0x113, 0x115, 0x5, 0x44, 0x23, 0x2, 0x114, 0x113, 0x3, 
       0x2, 0x2, 0x2, 0x114, 0x115, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0x3, 
       0x2, 0x2, 0x2, 0x116, 0x117, 0x7, 0x29, 0x2, 0x2, 0x117, 0x43, 0x3, 
       0x2, 0x2, 0x2, 0x118, 0x11d, 0x5, 0x46, 0x24, 0x2, 0x119, 0x11a, 
       0x7, 0x2d, 0x2, 0x2, 0x11a, 0x11c, 0x5, 0x46, 0x24, 0x2, 0x11b, 0x119, 
       0x3, 0x2, 0x2, 0x2, 0x11c, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11b, 
       0x3, 0x2, 0x2, 0x2, 0x11d, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x45, 
       0x3, 0x2, 0x2, 0x2, 0x11f, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x120, 0x121, 
       0x9, 0x5, 0x2, 0x2, 0x121, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x4f, 
       0x51, 0x66, 0x78, 0x7a, 0x86, 0x88, 0x8d, 0x99, 0x9b, 0xa0, 0xa4, 
       0xaa, 0xb7, 0xc3, 0xc5, 0xcf, 0xd8, 0xda, 0xe7, 0xe9, 0xf5, 0xf7, 
       0x103, 0x109, 0x114, 0x11d, 
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

CHTLParser::Initializer CHTLParser::_init;
