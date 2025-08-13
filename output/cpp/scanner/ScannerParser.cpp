
// Generated from Scanner.g4 by ANTLR 4.13.1


#include "ScannerListener.h"

#include "ScannerParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ScannerParserStaticData final {
  ScannerParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ScannerParserStaticData(const ScannerParserStaticData&) = delete;
  ScannerParserStaticData(ScannerParserStaticData&&) = delete;
  ScannerParserStaticData& operator=(const ScannerParserStaticData&) = delete;
  ScannerParserStaticData& operator=(ScannerParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag scannerParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ScannerParserStaticData *scannerParserStaticData = nullptr;

void scannerParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (scannerParserStaticData != nullptr) {
    return;
  }
#else
  assert(scannerParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ScannerParserStaticData>(
    std::vector<std::string>{
      "document", "codeBlock", "chtlBlock", "chtlElement", "elementStart", 
      "elementEnd", "elementContent", "chtlAttribute", "chtlDeclaration", 
      "chtlStatement", "textBlock", "textContent"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "';'", "'text'", "'style'", "'script'", "'[Template]'", 
      "'[Custom]'", "'[Configuration]'", "'[Namespace]'", "'[Import]'", 
      "'[Origin]'"
    },
    std::vector<std::string>{
      "", "", "", "", "TEXT", "STYLE", "SCRIPT", "TEMPLATE_START", "CUSTOM_START", 
      "CONFIG_START", "NAMESPACE_START", "IMPORT_START", "ORIGIN_START", 
      "COLON_OR_EQUAL", "IDENTIFIER", "STRING_LITERAL", "UNQUOTED_LITERAL", 
      "ATTR_VALUE", "ANY_CONTENT", "WS", "COMMENT", "MULTI_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,21,132,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,1,0,5,0,26,8,0,10,0,12,0,29,
  	9,0,1,0,1,0,1,1,1,1,3,1,35,8,1,1,2,1,2,1,2,3,2,40,8,2,1,3,1,3,5,3,44,
  	8,3,10,3,12,3,47,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,59,8,
  	4,1,5,1,5,1,6,1,6,1,6,1,6,3,6,67,8,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,5,8,
  	76,8,8,10,8,12,8,79,9,8,1,8,1,8,1,8,5,8,84,8,8,10,8,12,8,87,9,8,1,8,1,
  	8,1,8,5,8,92,8,8,10,8,12,8,95,9,8,1,8,1,8,1,8,5,8,100,8,8,10,8,12,8,103,
  	9,8,1,8,3,8,106,8,8,1,9,1,9,5,9,110,8,9,10,9,12,9,113,9,9,1,9,3,9,116,
  	8,9,1,9,1,9,5,9,120,8,9,10,9,12,9,123,9,9,1,9,3,9,126,8,9,1,10,1,10,1,
  	11,1,11,1,11,0,0,12,0,2,4,6,8,10,12,14,16,18,20,22,0,1,2,0,15,16,18,18,
  	141,0,27,1,0,0,0,2,34,1,0,0,0,4,39,1,0,0,0,6,41,1,0,0,0,8,58,1,0,0,0,
  	10,60,1,0,0,0,12,66,1,0,0,0,14,68,1,0,0,0,16,105,1,0,0,0,18,125,1,0,0,
  	0,20,127,1,0,0,0,22,129,1,0,0,0,24,26,3,2,1,0,25,24,1,0,0,0,26,29,1,0,
  	0,0,27,25,1,0,0,0,27,28,1,0,0,0,28,30,1,0,0,0,29,27,1,0,0,0,30,31,5,0,
  	0,1,31,1,1,0,0,0,32,35,3,4,2,0,33,35,3,20,10,0,34,32,1,0,0,0,34,33,1,
  	0,0,0,35,3,1,0,0,0,36,40,3,6,3,0,37,40,3,16,8,0,38,40,3,18,9,0,39,36,
  	1,0,0,0,39,37,1,0,0,0,39,38,1,0,0,0,40,5,1,0,0,0,41,45,3,8,4,0,42,44,
  	3,12,6,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,0,0,45,46,1,0,0,0,46,48,
  	1,0,0,0,47,45,1,0,0,0,48,49,3,10,5,0,49,7,1,0,0,0,50,51,5,14,0,0,51,59,
  	5,1,0,0,52,53,5,4,0,0,53,59,5,1,0,0,54,55,5,5,0,0,55,59,5,1,0,0,56,57,
  	5,6,0,0,57,59,5,1,0,0,58,50,1,0,0,0,58,52,1,0,0,0,58,54,1,0,0,0,58,56,
  	1,0,0,0,59,9,1,0,0,0,60,61,5,2,0,0,61,11,1,0,0,0,62,67,3,14,7,0,63,67,
  	3,6,3,0,64,67,3,22,11,0,65,67,5,18,0,0,66,62,1,0,0,0,66,63,1,0,0,0,66,
  	64,1,0,0,0,66,65,1,0,0,0,67,13,1,0,0,0,68,69,5,14,0,0,69,70,5,13,0,0,
  	70,71,5,17,0,0,71,72,5,3,0,0,72,15,1,0,0,0,73,77,5,7,0,0,74,76,5,18,0,
  	0,75,74,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,77,78,1,0,0,0,78,80,1,0,0,
  	0,79,77,1,0,0,0,80,106,5,2,0,0,81,85,5,8,0,0,82,84,5,18,0,0,83,82,1,0,
  	0,0,84,87,1,0,0,0,85,83,1,0,0,0,85,86,1,0,0,0,86,88,1,0,0,0,87,85,1,0,
  	0,0,88,106,5,2,0,0,89,93,5,9,0,0,90,92,5,18,0,0,91,90,1,0,0,0,92,95,1,
  	0,0,0,93,91,1,0,0,0,93,94,1,0,0,0,94,96,1,0,0,0,95,93,1,0,0,0,96,106,
  	5,2,0,0,97,101,5,10,0,0,98,100,5,18,0,0,99,98,1,0,0,0,100,103,1,0,0,0,
  	101,99,1,0,0,0,101,102,1,0,0,0,102,104,1,0,0,0,103,101,1,0,0,0,104,106,
  	5,2,0,0,105,73,1,0,0,0,105,81,1,0,0,0,105,89,1,0,0,0,105,97,1,0,0,0,106,
  	17,1,0,0,0,107,111,5,11,0,0,108,110,5,18,0,0,109,108,1,0,0,0,110,113,
  	1,0,0,0,111,109,1,0,0,0,111,112,1,0,0,0,112,115,1,0,0,0,113,111,1,0,0,
  	0,114,116,5,3,0,0,115,114,1,0,0,0,115,116,1,0,0,0,116,126,1,0,0,0,117,
  	121,5,12,0,0,118,120,5,18,0,0,119,118,1,0,0,0,120,123,1,0,0,0,121,119,
  	1,0,0,0,121,122,1,0,0,0,122,124,1,0,0,0,123,121,1,0,0,0,124,126,5,2,0,
  	0,125,107,1,0,0,0,125,117,1,0,0,0,126,19,1,0,0,0,127,128,3,22,11,0,128,
  	21,1,0,0,0,129,130,7,0,0,0,130,23,1,0,0,0,15,27,34,39,45,58,66,77,85,
  	93,101,105,111,115,121,125
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  scannerParserStaticData = staticData.release();
}

}

ScannerParser::ScannerParser(TokenStream *input) : ScannerParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ScannerParser::ScannerParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ScannerParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *scannerParserStaticData->atn, scannerParserStaticData->decisionToDFA, scannerParserStaticData->sharedContextCache, options);
}

ScannerParser::~ScannerParser() {
  delete _interpreter;
}

const atn::ATN& ScannerParser::getATN() const {
  return *scannerParserStaticData->atn;
}

std::string ScannerParser::getGrammarFileName() const {
  return "Scanner.g4";
}

const std::vector<std::string>& ScannerParser::getRuleNames() const {
  return scannerParserStaticData->ruleNames;
}

const dfa::Vocabulary& ScannerParser::getVocabulary() const {
  return scannerParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ScannerParser::getSerializedATN() const {
  return scannerParserStaticData->serializedATN;
}


//----------------- DocumentContext ------------------------------------------------------------------

ScannerParser::DocumentContext::DocumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScannerParser::DocumentContext::EOF() {
  return getToken(ScannerParser::EOF, 0);
}

std::vector<ScannerParser::CodeBlockContext *> ScannerParser::DocumentContext::codeBlock() {
  return getRuleContexts<ScannerParser::CodeBlockContext>();
}

ScannerParser::CodeBlockContext* ScannerParser::DocumentContext::codeBlock(size_t i) {
  return getRuleContext<ScannerParser::CodeBlockContext>(i);
}


size_t ScannerParser::DocumentContext::getRuleIndex() const {
  return ScannerParser::RuleDocument;
}

void ScannerParser::DocumentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDocument(this);
}

void ScannerParser::DocumentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDocument(this);
}

ScannerParser::DocumentContext* ScannerParser::document() {
  DocumentContext *_localctx = _tracker.createInstance<DocumentContext>(_ctx, getState());
  enterRule(_localctx, 0, ScannerParser::RuleDocument);
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
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 385008) != 0)) {
      setState(24);
      codeBlock();
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(30);
    match(ScannerParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CodeBlockContext ------------------------------------------------------------------

ScannerParser::CodeBlockContext::CodeBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ScannerParser::ChtlBlockContext* ScannerParser::CodeBlockContext::chtlBlock() {
  return getRuleContext<ScannerParser::ChtlBlockContext>(0);
}

ScannerParser::TextBlockContext* ScannerParser::CodeBlockContext::textBlock() {
  return getRuleContext<ScannerParser::TextBlockContext>(0);
}


size_t ScannerParser::CodeBlockContext::getRuleIndex() const {
  return ScannerParser::RuleCodeBlock;
}

void ScannerParser::CodeBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCodeBlock(this);
}

void ScannerParser::CodeBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCodeBlock(this);
}

ScannerParser::CodeBlockContext* ScannerParser::codeBlock() {
  CodeBlockContext *_localctx = _tracker.createInstance<CodeBlockContext>(_ctx, getState());
  enterRule(_localctx, 2, ScannerParser::RuleCodeBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(34);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ScannerParser::TEXT:
      case ScannerParser::STYLE:
      case ScannerParser::SCRIPT:
      case ScannerParser::TEMPLATE_START:
      case ScannerParser::CUSTOM_START:
      case ScannerParser::CONFIG_START:
      case ScannerParser::NAMESPACE_START:
      case ScannerParser::IMPORT_START:
      case ScannerParser::ORIGIN_START:
      case ScannerParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(32);
        chtlBlock();
        break;
      }

      case ScannerParser::STRING_LITERAL:
      case ScannerParser::UNQUOTED_LITERAL:
      case ScannerParser::ANY_CONTENT: {
        enterOuterAlt(_localctx, 2);
        setState(33);
        textBlock();
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

//----------------- ChtlBlockContext ------------------------------------------------------------------

ScannerParser::ChtlBlockContext::ChtlBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ScannerParser::ChtlElementContext* ScannerParser::ChtlBlockContext::chtlElement() {
  return getRuleContext<ScannerParser::ChtlElementContext>(0);
}

ScannerParser::ChtlDeclarationContext* ScannerParser::ChtlBlockContext::chtlDeclaration() {
  return getRuleContext<ScannerParser::ChtlDeclarationContext>(0);
}

ScannerParser::ChtlStatementContext* ScannerParser::ChtlBlockContext::chtlStatement() {
  return getRuleContext<ScannerParser::ChtlStatementContext>(0);
}


size_t ScannerParser::ChtlBlockContext::getRuleIndex() const {
  return ScannerParser::RuleChtlBlock;
}

void ScannerParser::ChtlBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlBlock(this);
}

void ScannerParser::ChtlBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlBlock(this);
}

ScannerParser::ChtlBlockContext* ScannerParser::chtlBlock() {
  ChtlBlockContext *_localctx = _tracker.createInstance<ChtlBlockContext>(_ctx, getState());
  enterRule(_localctx, 4, ScannerParser::RuleChtlBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(39);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ScannerParser::TEXT:
      case ScannerParser::STYLE:
      case ScannerParser::SCRIPT:
      case ScannerParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(36);
        chtlElement();
        break;
      }

      case ScannerParser::TEMPLATE_START:
      case ScannerParser::CUSTOM_START:
      case ScannerParser::CONFIG_START:
      case ScannerParser::NAMESPACE_START: {
        enterOuterAlt(_localctx, 2);
        setState(37);
        chtlDeclaration();
        break;
      }

      case ScannerParser::IMPORT_START:
      case ScannerParser::ORIGIN_START: {
        enterOuterAlt(_localctx, 3);
        setState(38);
        chtlStatement();
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

//----------------- ChtlElementContext ------------------------------------------------------------------

ScannerParser::ChtlElementContext::ChtlElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ScannerParser::ElementStartContext* ScannerParser::ChtlElementContext::elementStart() {
  return getRuleContext<ScannerParser::ElementStartContext>(0);
}

ScannerParser::ElementEndContext* ScannerParser::ChtlElementContext::elementEnd() {
  return getRuleContext<ScannerParser::ElementEndContext>(0);
}

std::vector<ScannerParser::ElementContentContext *> ScannerParser::ChtlElementContext::elementContent() {
  return getRuleContexts<ScannerParser::ElementContentContext>();
}

ScannerParser::ElementContentContext* ScannerParser::ChtlElementContext::elementContent(size_t i) {
  return getRuleContext<ScannerParser::ElementContentContext>(i);
}


size_t ScannerParser::ChtlElementContext::getRuleIndex() const {
  return ScannerParser::RuleChtlElement;
}

void ScannerParser::ChtlElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlElement(this);
}

void ScannerParser::ChtlElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlElement(this);
}

ScannerParser::ChtlElementContext* ScannerParser::chtlElement() {
  ChtlElementContext *_localctx = _tracker.createInstance<ChtlElementContext>(_ctx, getState());
  enterRule(_localctx, 6, ScannerParser::RuleChtlElement);
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
    setState(41);
    elementStart();
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 376944) != 0)) {
      setState(42);
      elementContent();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(48);
    elementEnd();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementStartContext ------------------------------------------------------------------

ScannerParser::ElementStartContext::ElementStartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScannerParser::ElementStartContext::IDENTIFIER() {
  return getToken(ScannerParser::IDENTIFIER, 0);
}

tree::TerminalNode* ScannerParser::ElementStartContext::TEXT() {
  return getToken(ScannerParser::TEXT, 0);
}

tree::TerminalNode* ScannerParser::ElementStartContext::STYLE() {
  return getToken(ScannerParser::STYLE, 0);
}

tree::TerminalNode* ScannerParser::ElementStartContext::SCRIPT() {
  return getToken(ScannerParser::SCRIPT, 0);
}


size_t ScannerParser::ElementStartContext::getRuleIndex() const {
  return ScannerParser::RuleElementStart;
}

void ScannerParser::ElementStartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementStart(this);
}

void ScannerParser::ElementStartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementStart(this);
}

ScannerParser::ElementStartContext* ScannerParser::elementStart() {
  ElementStartContext *_localctx = _tracker.createInstance<ElementStartContext>(_ctx, getState());
  enterRule(_localctx, 8, ScannerParser::RuleElementStart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(58);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ScannerParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(50);
        match(ScannerParser::IDENTIFIER);
        setState(51);
        match(ScannerParser::T__0);
        break;
      }

      case ScannerParser::TEXT: {
        enterOuterAlt(_localctx, 2);
        setState(52);
        match(ScannerParser::TEXT);
        setState(53);
        match(ScannerParser::T__0);
        break;
      }

      case ScannerParser::STYLE: {
        enterOuterAlt(_localctx, 3);
        setState(54);
        match(ScannerParser::STYLE);
        setState(55);
        match(ScannerParser::T__0);
        break;
      }

      case ScannerParser::SCRIPT: {
        enterOuterAlt(_localctx, 4);
        setState(56);
        match(ScannerParser::SCRIPT);
        setState(57);
        match(ScannerParser::T__0);
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

//----------------- ElementEndContext ------------------------------------------------------------------

ScannerParser::ElementEndContext::ElementEndContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScannerParser::ElementEndContext::getRuleIndex() const {
  return ScannerParser::RuleElementEnd;
}

void ScannerParser::ElementEndContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementEnd(this);
}

void ScannerParser::ElementEndContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementEnd(this);
}

ScannerParser::ElementEndContext* ScannerParser::elementEnd() {
  ElementEndContext *_localctx = _tracker.createInstance<ElementEndContext>(_ctx, getState());
  enterRule(_localctx, 10, ScannerParser::RuleElementEnd);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    match(ScannerParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContentContext ------------------------------------------------------------------

ScannerParser::ElementContentContext::ElementContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ScannerParser::ChtlAttributeContext* ScannerParser::ElementContentContext::chtlAttribute() {
  return getRuleContext<ScannerParser::ChtlAttributeContext>(0);
}

ScannerParser::ChtlElementContext* ScannerParser::ElementContentContext::chtlElement() {
  return getRuleContext<ScannerParser::ChtlElementContext>(0);
}

ScannerParser::TextContentContext* ScannerParser::ElementContentContext::textContent() {
  return getRuleContext<ScannerParser::TextContentContext>(0);
}

tree::TerminalNode* ScannerParser::ElementContentContext::ANY_CONTENT() {
  return getToken(ScannerParser::ANY_CONTENT, 0);
}


size_t ScannerParser::ElementContentContext::getRuleIndex() const {
  return ScannerParser::RuleElementContent;
}

void ScannerParser::ElementContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementContent(this);
}

void ScannerParser::ElementContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementContent(this);
}

ScannerParser::ElementContentContext* ScannerParser::elementContent() {
  ElementContentContext *_localctx = _tracker.createInstance<ElementContentContext>(_ctx, getState());
  enterRule(_localctx, 12, ScannerParser::RuleElementContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(66);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(62);
      chtlAttribute();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(63);
      chtlElement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(64);
      textContent();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(65);
      match(ScannerParser::ANY_CONTENT);
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

//----------------- ChtlAttributeContext ------------------------------------------------------------------

ScannerParser::ChtlAttributeContext::ChtlAttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScannerParser::ChtlAttributeContext::IDENTIFIER() {
  return getToken(ScannerParser::IDENTIFIER, 0);
}

tree::TerminalNode* ScannerParser::ChtlAttributeContext::COLON_OR_EQUAL() {
  return getToken(ScannerParser::COLON_OR_EQUAL, 0);
}

tree::TerminalNode* ScannerParser::ChtlAttributeContext::ATTR_VALUE() {
  return getToken(ScannerParser::ATTR_VALUE, 0);
}


size_t ScannerParser::ChtlAttributeContext::getRuleIndex() const {
  return ScannerParser::RuleChtlAttribute;
}

void ScannerParser::ChtlAttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlAttribute(this);
}

void ScannerParser::ChtlAttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlAttribute(this);
}

ScannerParser::ChtlAttributeContext* ScannerParser::chtlAttribute() {
  ChtlAttributeContext *_localctx = _tracker.createInstance<ChtlAttributeContext>(_ctx, getState());
  enterRule(_localctx, 14, ScannerParser::RuleChtlAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(ScannerParser::IDENTIFIER);
    setState(69);
    match(ScannerParser::COLON_OR_EQUAL);
    setState(70);
    match(ScannerParser::ATTR_VALUE);
    setState(71);
    match(ScannerParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChtlDeclarationContext ------------------------------------------------------------------

ScannerParser::ChtlDeclarationContext::ChtlDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScannerParser::ChtlDeclarationContext::TEMPLATE_START() {
  return getToken(ScannerParser::TEMPLATE_START, 0);
}

std::vector<tree::TerminalNode *> ScannerParser::ChtlDeclarationContext::ANY_CONTENT() {
  return getTokens(ScannerParser::ANY_CONTENT);
}

tree::TerminalNode* ScannerParser::ChtlDeclarationContext::ANY_CONTENT(size_t i) {
  return getToken(ScannerParser::ANY_CONTENT, i);
}

tree::TerminalNode* ScannerParser::ChtlDeclarationContext::CUSTOM_START() {
  return getToken(ScannerParser::CUSTOM_START, 0);
}

tree::TerminalNode* ScannerParser::ChtlDeclarationContext::CONFIG_START() {
  return getToken(ScannerParser::CONFIG_START, 0);
}

tree::TerminalNode* ScannerParser::ChtlDeclarationContext::NAMESPACE_START() {
  return getToken(ScannerParser::NAMESPACE_START, 0);
}


size_t ScannerParser::ChtlDeclarationContext::getRuleIndex() const {
  return ScannerParser::RuleChtlDeclaration;
}

void ScannerParser::ChtlDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlDeclaration(this);
}

void ScannerParser::ChtlDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlDeclaration(this);
}

ScannerParser::ChtlDeclarationContext* ScannerParser::chtlDeclaration() {
  ChtlDeclarationContext *_localctx = _tracker.createInstance<ChtlDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 16, ScannerParser::RuleChtlDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(105);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ScannerParser::TEMPLATE_START: {
        enterOuterAlt(_localctx, 1);
        setState(73);
        match(ScannerParser::TEMPLATE_START);
        setState(77);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ScannerParser::ANY_CONTENT) {
          setState(74);
          match(ScannerParser::ANY_CONTENT);
          setState(79);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(80);
        match(ScannerParser::T__1);
        break;
      }

      case ScannerParser::CUSTOM_START: {
        enterOuterAlt(_localctx, 2);
        setState(81);
        match(ScannerParser::CUSTOM_START);
        setState(85);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ScannerParser::ANY_CONTENT) {
          setState(82);
          match(ScannerParser::ANY_CONTENT);
          setState(87);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(88);
        match(ScannerParser::T__1);
        break;
      }

      case ScannerParser::CONFIG_START: {
        enterOuterAlt(_localctx, 3);
        setState(89);
        match(ScannerParser::CONFIG_START);
        setState(93);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ScannerParser::ANY_CONTENT) {
          setState(90);
          match(ScannerParser::ANY_CONTENT);
          setState(95);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(96);
        match(ScannerParser::T__1);
        break;
      }

      case ScannerParser::NAMESPACE_START: {
        enterOuterAlt(_localctx, 4);
        setState(97);
        match(ScannerParser::NAMESPACE_START);
        setState(101);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ScannerParser::ANY_CONTENT) {
          setState(98);
          match(ScannerParser::ANY_CONTENT);
          setState(103);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(104);
        match(ScannerParser::T__1);
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

//----------------- ChtlStatementContext ------------------------------------------------------------------

ScannerParser::ChtlStatementContext::ChtlStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScannerParser::ChtlStatementContext::IMPORT_START() {
  return getToken(ScannerParser::IMPORT_START, 0);
}

std::vector<tree::TerminalNode *> ScannerParser::ChtlStatementContext::ANY_CONTENT() {
  return getTokens(ScannerParser::ANY_CONTENT);
}

tree::TerminalNode* ScannerParser::ChtlStatementContext::ANY_CONTENT(size_t i) {
  return getToken(ScannerParser::ANY_CONTENT, i);
}

tree::TerminalNode* ScannerParser::ChtlStatementContext::ORIGIN_START() {
  return getToken(ScannerParser::ORIGIN_START, 0);
}


size_t ScannerParser::ChtlStatementContext::getRuleIndex() const {
  return ScannerParser::RuleChtlStatement;
}

void ScannerParser::ChtlStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChtlStatement(this);
}

void ScannerParser::ChtlStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChtlStatement(this);
}

ScannerParser::ChtlStatementContext* ScannerParser::chtlStatement() {
  ChtlStatementContext *_localctx = _tracker.createInstance<ChtlStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, ScannerParser::RuleChtlStatement);
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
    setState(125);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ScannerParser::IMPORT_START: {
        enterOuterAlt(_localctx, 1);
        setState(107);
        match(ScannerParser::IMPORT_START);
        setState(111);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(108);
            match(ScannerParser::ANY_CONTENT); 
          }
          setState(113);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
        }
        setState(115);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ScannerParser::T__2) {
          setState(114);
          match(ScannerParser::T__2);
        }
        break;
      }

      case ScannerParser::ORIGIN_START: {
        enterOuterAlt(_localctx, 2);
        setState(117);
        match(ScannerParser::ORIGIN_START);
        setState(121);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ScannerParser::ANY_CONTENT) {
          setState(118);
          match(ScannerParser::ANY_CONTENT);
          setState(123);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(124);
        match(ScannerParser::T__1);
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

//----------------- TextBlockContext ------------------------------------------------------------------

ScannerParser::TextBlockContext::TextBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ScannerParser::TextContentContext* ScannerParser::TextBlockContext::textContent() {
  return getRuleContext<ScannerParser::TextContentContext>(0);
}


size_t ScannerParser::TextBlockContext::getRuleIndex() const {
  return ScannerParser::RuleTextBlock;
}

void ScannerParser::TextBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextBlock(this);
}

void ScannerParser::TextBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextBlock(this);
}

ScannerParser::TextBlockContext* ScannerParser::textBlock() {
  TextBlockContext *_localctx = _tracker.createInstance<TextBlockContext>(_ctx, getState());
  enterRule(_localctx, 20, ScannerParser::RuleTextBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    textContent();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TextContentContext ------------------------------------------------------------------

ScannerParser::TextContentContext::TextContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScannerParser::TextContentContext::STRING_LITERAL() {
  return getToken(ScannerParser::STRING_LITERAL, 0);
}

tree::TerminalNode* ScannerParser::TextContentContext::UNQUOTED_LITERAL() {
  return getToken(ScannerParser::UNQUOTED_LITERAL, 0);
}

tree::TerminalNode* ScannerParser::TextContentContext::ANY_CONTENT() {
  return getToken(ScannerParser::ANY_CONTENT, 0);
}


size_t ScannerParser::TextContentContext::getRuleIndex() const {
  return ScannerParser::RuleTextContent;
}

void ScannerParser::TextContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTextContent(this);
}

void ScannerParser::TextContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ScannerListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTextContent(this);
}

ScannerParser::TextContentContext* ScannerParser::textContent() {
  TextContentContext *_localctx = _tracker.createInstance<TextContentContext>(_ctx, getState());
  enterRule(_localctx, 22, ScannerParser::RuleTextContent);
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
    setState(129);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 360448) != 0))) {
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

void ScannerParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  scannerParserInitialize();
#else
  ::antlr4::internal::call_once(scannerParserOnceFlag, scannerParserInitialize);
#endif
}
