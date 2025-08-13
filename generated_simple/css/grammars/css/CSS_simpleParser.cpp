
// Generated from grammars/css/CSS_simple.g4 by ANTLR 4.13.1


#include "CSS_simpleListener.h"
#include "CSS_simpleVisitor.h"

#include "CSS_simpleParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CSS_simpleParserStaticData final {
  CSS_simpleParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CSS_simpleParserStaticData(const CSS_simpleParserStaticData&) = delete;
  CSS_simpleParserStaticData(CSS_simpleParserStaticData&&) = delete;
  CSS_simpleParserStaticData& operator=(const CSS_simpleParserStaticData&) = delete;
  CSS_simpleParserStaticData& operator=(CSS_simpleParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag css_simpleParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CSS_simpleParserStaticData *css_simpleParserStaticData = nullptr;

void css_simpleParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (css_simpleParserStaticData != nullptr) {
    return;
  }
#else
  assert(css_simpleParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CSS_simpleParserStaticData>(
    std::vector<std::string>{
      "stylesheet", "rule", "selector", "declarationList", "declaration", 
      "property", "value"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "'{'", "'}'", "'('", "')'", "';'", "':'", 
      "','", "'.'", "'#'"
    },
    std::vector<std::string>{
      "", "WS", "COMMENT", "SELECTOR", "IDENTIFIER", "NUMBER", "STRING", 
      "LBRACE", "RBRACE", "LPAREN", "RPAREN", "SEMICOLON", "COLON", "COMMA", 
      "DOT", "HASH"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,15,50,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,1,0,
  	5,0,16,8,0,10,0,12,0,19,9,0,1,1,1,1,1,1,1,1,1,1,1,2,3,2,27,8,2,1,2,1,
  	2,1,3,5,3,32,8,3,10,3,12,3,35,9,3,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,6,5,6,
  	45,8,6,10,6,12,6,48,9,6,1,6,0,0,7,0,2,4,6,8,10,12,0,2,1,0,14,15,1,0,4,
  	6,46,0,17,1,0,0,0,2,20,1,0,0,0,4,26,1,0,0,0,6,33,1,0,0,0,8,36,1,0,0,0,
  	10,41,1,0,0,0,12,46,1,0,0,0,14,16,3,2,1,0,15,14,1,0,0,0,16,19,1,0,0,0,
  	17,15,1,0,0,0,17,18,1,0,0,0,18,1,1,0,0,0,19,17,1,0,0,0,20,21,3,4,2,0,
  	21,22,5,7,0,0,22,23,3,6,3,0,23,24,5,8,0,0,24,3,1,0,0,0,25,27,7,0,0,0,
  	26,25,1,0,0,0,26,27,1,0,0,0,27,28,1,0,0,0,28,29,5,4,0,0,29,5,1,0,0,0,
  	30,32,3,8,4,0,31,30,1,0,0,0,32,35,1,0,0,0,33,31,1,0,0,0,33,34,1,0,0,0,
  	34,7,1,0,0,0,35,33,1,0,0,0,36,37,3,10,5,0,37,38,5,12,0,0,38,39,3,12,6,
  	0,39,40,5,11,0,0,40,9,1,0,0,0,41,42,5,4,0,0,42,11,1,0,0,0,43,45,7,1,0,
  	0,44,43,1,0,0,0,45,48,1,0,0,0,46,44,1,0,0,0,46,47,1,0,0,0,47,13,1,0,0,
  	0,48,46,1,0,0,0,4,17,26,33,46
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  css_simpleParserStaticData = staticData.release();
}

}

CSS_simpleParser::CSS_simpleParser(TokenStream *input) : CSS_simpleParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CSS_simpleParser::CSS_simpleParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CSS_simpleParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *css_simpleParserStaticData->atn, css_simpleParserStaticData->decisionToDFA, css_simpleParserStaticData->sharedContextCache, options);
}

CSS_simpleParser::~CSS_simpleParser() {
  delete _interpreter;
}

const atn::ATN& CSS_simpleParser::getATN() const {
  return *css_simpleParserStaticData->atn;
}

std::string CSS_simpleParser::getGrammarFileName() const {
  return "CSS_simple.g4";
}

const std::vector<std::string>& CSS_simpleParser::getRuleNames() const {
  return css_simpleParserStaticData->ruleNames;
}

const dfa::Vocabulary& CSS_simpleParser::getVocabulary() const {
  return css_simpleParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CSS_simpleParser::getSerializedATN() const {
  return css_simpleParserStaticData->serializedATN;
}


//----------------- StylesheetContext ------------------------------------------------------------------

CSS_simpleParser::StylesheetContext::StylesheetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSS_simpleParser::RuleContext *> CSS_simpleParser::StylesheetContext::rule_() {
  return getRuleContexts<CSS_simpleParser::RuleContext>();
}

CSS_simpleParser::RuleContext* CSS_simpleParser::StylesheetContext::rule_(size_t i) {
  return getRuleContext<CSS_simpleParser::RuleContext>(i);
}


size_t CSS_simpleParser::StylesheetContext::getRuleIndex() const {
  return CSS_simpleParser::RuleStylesheet;
}

void CSS_simpleParser::StylesheetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStylesheet(this);
}

void CSS_simpleParser::StylesheetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStylesheet(this);
}


std::any CSS_simpleParser::StylesheetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSS_simpleVisitor*>(visitor))
    return parserVisitor->visitStylesheet(this);
  else
    return visitor->visitChildren(this);
}

CSS_simpleParser::StylesheetContext* CSS_simpleParser::stylesheet() {
  StylesheetContext *_localctx = _tracker.createInstance<StylesheetContext>(_ctx, getState());
  enterRule(_localctx, 0, CSS_simpleParser::RuleStylesheet);
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
    setState(17);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 49168) != 0)) {
      setState(14);
      rule_();
      setState(19);
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

//----------------- RuleContext ------------------------------------------------------------------

CSS_simpleParser::RuleContext::RuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSS_simpleParser::SelectorContext* CSS_simpleParser::RuleContext::selector() {
  return getRuleContext<CSS_simpleParser::SelectorContext>(0);
}

tree::TerminalNode* CSS_simpleParser::RuleContext::LBRACE() {
  return getToken(CSS_simpleParser::LBRACE, 0);
}

CSS_simpleParser::DeclarationListContext* CSS_simpleParser::RuleContext::declarationList() {
  return getRuleContext<CSS_simpleParser::DeclarationListContext>(0);
}

tree::TerminalNode* CSS_simpleParser::RuleContext::RBRACE() {
  return getToken(CSS_simpleParser::RBRACE, 0);
}


size_t CSS_simpleParser::RuleContext::getRuleIndex() const {
  return CSS_simpleParser::RuleRule;
}

void CSS_simpleParser::RuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRule(this);
}

void CSS_simpleParser::RuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRule(this);
}


std::any CSS_simpleParser::RuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSS_simpleVisitor*>(visitor))
    return parserVisitor->visitRule(this);
  else
    return visitor->visitChildren(this);
}

CSS_simpleParser::RuleContext* CSS_simpleParser::rule_() {
  RuleContext *_localctx = _tracker.createInstance<RuleContext>(_ctx, getState());
  enterRule(_localctx, 2, CSS_simpleParser::RuleRule);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    selector();
    setState(21);
    match(CSS_simpleParser::LBRACE);
    setState(22);
    declarationList();
    setState(23);
    match(CSS_simpleParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectorContext ------------------------------------------------------------------

CSS_simpleParser::SelectorContext::SelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSS_simpleParser::SelectorContext::IDENTIFIER() {
  return getToken(CSS_simpleParser::IDENTIFIER, 0);
}

tree::TerminalNode* CSS_simpleParser::SelectorContext::DOT() {
  return getToken(CSS_simpleParser::DOT, 0);
}

tree::TerminalNode* CSS_simpleParser::SelectorContext::HASH() {
  return getToken(CSS_simpleParser::HASH, 0);
}


size_t CSS_simpleParser::SelectorContext::getRuleIndex() const {
  return CSS_simpleParser::RuleSelector;
}

void CSS_simpleParser::SelectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelector(this);
}

void CSS_simpleParser::SelectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelector(this);
}


std::any CSS_simpleParser::SelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSS_simpleVisitor*>(visitor))
    return parserVisitor->visitSelector(this);
  else
    return visitor->visitChildren(this);
}

CSS_simpleParser::SelectorContext* CSS_simpleParser::selector() {
  SelectorContext *_localctx = _tracker.createInstance<SelectorContext>(_ctx, getState());
  enterRule(_localctx, 4, CSS_simpleParser::RuleSelector);
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
    setState(26);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CSS_simpleParser::DOT

    || _la == CSS_simpleParser::HASH) {
      setState(25);
      _la = _input->LA(1);
      if (!(_la == CSS_simpleParser::DOT

      || _la == CSS_simpleParser::HASH)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(28);
    match(CSS_simpleParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationListContext ------------------------------------------------------------------

CSS_simpleParser::DeclarationListContext::DeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CSS_simpleParser::DeclarationContext *> CSS_simpleParser::DeclarationListContext::declaration() {
  return getRuleContexts<CSS_simpleParser::DeclarationContext>();
}

CSS_simpleParser::DeclarationContext* CSS_simpleParser::DeclarationListContext::declaration(size_t i) {
  return getRuleContext<CSS_simpleParser::DeclarationContext>(i);
}


size_t CSS_simpleParser::DeclarationListContext::getRuleIndex() const {
  return CSS_simpleParser::RuleDeclarationList;
}

void CSS_simpleParser::DeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationList(this);
}

void CSS_simpleParser::DeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationList(this);
}


std::any CSS_simpleParser::DeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSS_simpleVisitor*>(visitor))
    return parserVisitor->visitDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

CSS_simpleParser::DeclarationListContext* CSS_simpleParser::declarationList() {
  DeclarationListContext *_localctx = _tracker.createInstance<DeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 6, CSS_simpleParser::RuleDeclarationList);
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
    setState(33);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CSS_simpleParser::IDENTIFIER) {
      setState(30);
      declaration();
      setState(35);
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

//----------------- DeclarationContext ------------------------------------------------------------------

CSS_simpleParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CSS_simpleParser::PropertyContext* CSS_simpleParser::DeclarationContext::property() {
  return getRuleContext<CSS_simpleParser::PropertyContext>(0);
}

tree::TerminalNode* CSS_simpleParser::DeclarationContext::COLON() {
  return getToken(CSS_simpleParser::COLON, 0);
}

CSS_simpleParser::ValueContext* CSS_simpleParser::DeclarationContext::value() {
  return getRuleContext<CSS_simpleParser::ValueContext>(0);
}

tree::TerminalNode* CSS_simpleParser::DeclarationContext::SEMICOLON() {
  return getToken(CSS_simpleParser::SEMICOLON, 0);
}


size_t CSS_simpleParser::DeclarationContext::getRuleIndex() const {
  return CSS_simpleParser::RuleDeclaration;
}

void CSS_simpleParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void CSS_simpleParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any CSS_simpleParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSS_simpleVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CSS_simpleParser::DeclarationContext* CSS_simpleParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 8, CSS_simpleParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    property();
    setState(37);
    match(CSS_simpleParser::COLON);
    setState(38);
    value();
    setState(39);
    match(CSS_simpleParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyContext ------------------------------------------------------------------

CSS_simpleParser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CSS_simpleParser::PropertyContext::IDENTIFIER() {
  return getToken(CSS_simpleParser::IDENTIFIER, 0);
}


size_t CSS_simpleParser::PropertyContext::getRuleIndex() const {
  return CSS_simpleParser::RuleProperty;
}

void CSS_simpleParser::PropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty(this);
}

void CSS_simpleParser::PropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty(this);
}


std::any CSS_simpleParser::PropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSS_simpleVisitor*>(visitor))
    return parserVisitor->visitProperty(this);
  else
    return visitor->visitChildren(this);
}

CSS_simpleParser::PropertyContext* CSS_simpleParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 10, CSS_simpleParser::RuleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(41);
    match(CSS_simpleParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

CSS_simpleParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CSS_simpleParser::ValueContext::STRING() {
  return getTokens(CSS_simpleParser::STRING);
}

tree::TerminalNode* CSS_simpleParser::ValueContext::STRING(size_t i) {
  return getToken(CSS_simpleParser::STRING, i);
}

std::vector<tree::TerminalNode *> CSS_simpleParser::ValueContext::NUMBER() {
  return getTokens(CSS_simpleParser::NUMBER);
}

tree::TerminalNode* CSS_simpleParser::ValueContext::NUMBER(size_t i) {
  return getToken(CSS_simpleParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> CSS_simpleParser::ValueContext::IDENTIFIER() {
  return getTokens(CSS_simpleParser::IDENTIFIER);
}

tree::TerminalNode* CSS_simpleParser::ValueContext::IDENTIFIER(size_t i) {
  return getToken(CSS_simpleParser::IDENTIFIER, i);
}


size_t CSS_simpleParser::ValueContext::getRuleIndex() const {
  return CSS_simpleParser::RuleValue;
}

void CSS_simpleParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void CSS_simpleParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CSS_simpleListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}


std::any CSS_simpleParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CSS_simpleVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

CSS_simpleParser::ValueContext* CSS_simpleParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 12, CSS_simpleParser::RuleValue);
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
    setState(46);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 112) != 0)) {
      setState(43);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 112) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(48);
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

void CSS_simpleParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  css_simpleParserInitialize();
#else
  ::antlr4::internal::call_once(css_simpleParserOnceFlag, css_simpleParserInitialize);
#endif
}
