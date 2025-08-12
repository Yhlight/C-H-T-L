
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1


#include "CHTLJS_simpleLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CHTLJS_simpleLexerStaticData final {
  CHTLJS_simpleLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CHTLJS_simpleLexerStaticData(const CHTLJS_simpleLexerStaticData&) = delete;
  CHTLJS_simpleLexerStaticData(CHTLJS_simpleLexerStaticData&&) = delete;
  CHTLJS_simpleLexerStaticData& operator=(const CHTLJS_simpleLexerStaticData&) = delete;
  CHTLJS_simpleLexerStaticData& operator=(CHTLJS_simpleLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag chtljs_simplelexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CHTLJS_simpleLexerStaticData *chtljs_simplelexerLexerStaticData = nullptr;

void chtljs_simplelexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (chtljs_simplelexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(chtljs_simplelexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CHTLJS_simpleLexerStaticData>(
    std::vector<std::string>{
      "WS", "COMMENT", "CHTL_SCRIPT", "CHTL_LISTEN", "CHTL_DELEGATE", "CHTL_ANIMATE", 
      "CHTL_DOUBLE_BRACE", "CHTL_DOUBLE_BRACE_CLOSE", "CHTL_ARROW", "IDENTIFIER", 
      "NUMBER", "STRING", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "SEMICOLON", 
      "COLON", "COMMA", "DOT", "HASH"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "", "'script'", "'listen'", "'delegate'", "'animate'", "'{{'", 
      "'}}'", "'->'", "", "", "", "'{'", "'}'", "'('", "')'", "';'", "':'", 
      "','", "'.'", "'#'"
    },
    std::vector<std::string>{
      "", "WS", "COMMENT", "CHTL_SCRIPT", "CHTL_LISTEN", "CHTL_DELEGATE", 
      "CHTL_ANIMATE", "CHTL_DOUBLE_BRACE", "CHTL_DOUBLE_BRACE_CLOSE", "CHTL_ARROW", 
      "IDENTIFIER", "NUMBER", "STRING", "LBRACE", "RBRACE", "LPAREN", "RPAREN", 
      "SEMICOLON", "COLON", "COMMA", "DOT", "HASH"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,21,150,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,
  	4,0,45,8,0,11,0,12,0,46,1,0,1,0,1,1,1,1,1,1,1,1,5,1,55,8,1,10,1,12,1,
  	58,9,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,6,1,6,1,6,1,7,1,7,1,7,1,8,1,8,1,8,1,9,1,9,5,9,104,8,9,10,9,12,9,107,
  	9,9,1,10,4,10,110,8,10,11,10,12,10,111,1,10,1,10,4,10,116,8,10,11,10,
  	12,10,117,3,10,120,8,10,1,11,1,11,1,11,1,11,5,11,126,8,11,10,11,12,11,
  	129,9,11,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,
  	1,17,1,17,1,18,1,18,1,19,1,19,1,20,1,20,0,0,21,1,1,3,2,5,3,7,4,9,5,11,
  	6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,
  	37,19,39,20,41,21,1,0,6,3,0,9,10,13,13,32,32,2,0,10,10,13,13,4,0,36,36,
  	65,90,95,95,97,122,5,0,36,36,48,57,65,90,95,95,97,122,1,0,48,57,2,0,34,
  	34,92,92,157,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,
  	0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,
  	0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,
  	1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,
  	0,0,1,44,1,0,0,0,3,50,1,0,0,0,5,61,1,0,0,0,7,68,1,0,0,0,9,75,1,0,0,0,
  	11,84,1,0,0,0,13,92,1,0,0,0,15,95,1,0,0,0,17,98,1,0,0,0,19,101,1,0,0,
  	0,21,109,1,0,0,0,23,121,1,0,0,0,25,132,1,0,0,0,27,134,1,0,0,0,29,136,
  	1,0,0,0,31,138,1,0,0,0,33,140,1,0,0,0,35,142,1,0,0,0,37,144,1,0,0,0,39,
  	146,1,0,0,0,41,148,1,0,0,0,43,45,7,0,0,0,44,43,1,0,0,0,45,46,1,0,0,0,
  	46,44,1,0,0,0,46,47,1,0,0,0,47,48,1,0,0,0,48,49,6,0,0,0,49,2,1,0,0,0,
  	50,51,5,47,0,0,51,52,5,47,0,0,52,56,1,0,0,0,53,55,8,1,0,0,54,53,1,0,0,
  	0,55,58,1,0,0,0,56,54,1,0,0,0,56,57,1,0,0,0,57,59,1,0,0,0,58,56,1,0,0,
  	0,59,60,6,1,0,0,60,4,1,0,0,0,61,62,5,115,0,0,62,63,5,99,0,0,63,64,5,114,
  	0,0,64,65,5,105,0,0,65,66,5,112,0,0,66,67,5,116,0,0,67,6,1,0,0,0,68,69,
  	5,108,0,0,69,70,5,105,0,0,70,71,5,115,0,0,71,72,5,116,0,0,72,73,5,101,
  	0,0,73,74,5,110,0,0,74,8,1,0,0,0,75,76,5,100,0,0,76,77,5,101,0,0,77,78,
  	5,108,0,0,78,79,5,101,0,0,79,80,5,103,0,0,80,81,5,97,0,0,81,82,5,116,
  	0,0,82,83,5,101,0,0,83,10,1,0,0,0,84,85,5,97,0,0,85,86,5,110,0,0,86,87,
  	5,105,0,0,87,88,5,109,0,0,88,89,5,97,0,0,89,90,5,116,0,0,90,91,5,101,
  	0,0,91,12,1,0,0,0,92,93,5,123,0,0,93,94,5,123,0,0,94,14,1,0,0,0,95,96,
  	5,125,0,0,96,97,5,125,0,0,97,16,1,0,0,0,98,99,5,45,0,0,99,100,5,62,0,
  	0,100,18,1,0,0,0,101,105,7,2,0,0,102,104,7,3,0,0,103,102,1,0,0,0,104,
  	107,1,0,0,0,105,103,1,0,0,0,105,106,1,0,0,0,106,20,1,0,0,0,107,105,1,
  	0,0,0,108,110,7,4,0,0,109,108,1,0,0,0,110,111,1,0,0,0,111,109,1,0,0,0,
  	111,112,1,0,0,0,112,119,1,0,0,0,113,115,5,46,0,0,114,116,7,4,0,0,115,
  	114,1,0,0,0,116,117,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,120,1,
  	0,0,0,119,113,1,0,0,0,119,120,1,0,0,0,120,22,1,0,0,0,121,127,5,34,0,0,
  	122,126,8,5,0,0,123,124,5,92,0,0,124,126,9,0,0,0,125,122,1,0,0,0,125,
  	123,1,0,0,0,126,129,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,130,1,
  	0,0,0,129,127,1,0,0,0,130,131,5,34,0,0,131,24,1,0,0,0,132,133,5,123,0,
  	0,133,26,1,0,0,0,134,135,5,125,0,0,135,28,1,0,0,0,136,137,5,40,0,0,137,
  	30,1,0,0,0,138,139,5,41,0,0,139,32,1,0,0,0,140,141,5,59,0,0,141,34,1,
  	0,0,0,142,143,5,58,0,0,143,36,1,0,0,0,144,145,5,44,0,0,145,38,1,0,0,0,
  	146,147,5,46,0,0,147,40,1,0,0,0,148,149,5,35,0,0,149,42,1,0,0,0,9,0,46,
  	56,105,111,117,119,125,127,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  chtljs_simplelexerLexerStaticData = staticData.release();
}

}

CHTLJS_simpleLexer::CHTLJS_simpleLexer(CharStream *input) : Lexer(input) {
  CHTLJS_simpleLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *chtljs_simplelexerLexerStaticData->atn, chtljs_simplelexerLexerStaticData->decisionToDFA, chtljs_simplelexerLexerStaticData->sharedContextCache);
}

CHTLJS_simpleLexer::~CHTLJS_simpleLexer() {
  delete _interpreter;
}

std::string CHTLJS_simpleLexer::getGrammarFileName() const {
  return "CHTLJS_simple.g4";
}

const std::vector<std::string>& CHTLJS_simpleLexer::getRuleNames() const {
  return chtljs_simplelexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CHTLJS_simpleLexer::getChannelNames() const {
  return chtljs_simplelexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CHTLJS_simpleLexer::getModeNames() const {
  return chtljs_simplelexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CHTLJS_simpleLexer::getVocabulary() const {
  return chtljs_simplelexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CHTLJS_simpleLexer::getSerializedATN() const {
  return chtljs_simplelexerLexerStaticData->serializedATN;
}

const atn::ATN& CHTLJS_simpleLexer::getATN() const {
  return *chtljs_simplelexerLexerStaticData->atn;
}




void CHTLJS_simpleLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  chtljs_simplelexerLexerInitialize();
#else
  ::antlr4::internal::call_once(chtljs_simplelexerLexerOnceFlag, chtljs_simplelexerLexerInitialize);
#endif
}
