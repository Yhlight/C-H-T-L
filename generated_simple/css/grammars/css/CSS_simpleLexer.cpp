
// Generated from grammars/css/CSS_simple.g4 by ANTLR 4.13.1


#include "CSS_simpleLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CSS_simpleLexerStaticData final {
  CSS_simpleLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CSS_simpleLexerStaticData(const CSS_simpleLexerStaticData&) = delete;
  CSS_simpleLexerStaticData(CSS_simpleLexerStaticData&&) = delete;
  CSS_simpleLexerStaticData& operator=(const CSS_simpleLexerStaticData&) = delete;
  CSS_simpleLexerStaticData& operator=(CSS_simpleLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag css_simplelexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CSS_simpleLexerStaticData *css_simplelexerLexerStaticData = nullptr;

void css_simplelexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (css_simplelexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(css_simplelexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CSS_simpleLexerStaticData>(
    std::vector<std::string>{
      "WS", "COMMENT", "SELECTOR", "IDENTIFIER", "NUMBER", "STRING", "LBRACE", 
      "RBRACE", "LPAREN", "RPAREN", "SEMICOLON", "COLON", "COMMA", "DOT", 
      "HASH"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,15,103,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,1,0,4,0,33,8,0,11,0,12,0,34,1,0,1,0,1,1,1,1,1,1,1,1,5,1,43,8,1,10,
  	1,12,1,46,9,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,3,1,3,5,3,57,8,3,10,3,12,
  	3,60,9,3,1,4,4,4,63,8,4,11,4,12,4,64,1,4,1,4,4,4,69,8,4,11,4,12,4,70,
  	3,4,73,8,4,1,5,1,5,1,5,1,5,5,5,79,8,5,10,5,12,5,82,9,5,1,5,1,5,1,6,1,
  	6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,
  	1,14,1,44,0,15,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,
  	12,25,13,27,14,29,15,1,0,6,3,0,9,10,13,13,32,32,5,0,35,35,42,43,46,46,
  	62,62,126,126,3,0,65,90,95,95,97,122,5,0,45,45,48,57,65,90,95,95,97,122,
  	1,0,48,57,2,0,34,34,92,92,110,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,
  	1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,
  	0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,
  	29,1,0,0,0,1,32,1,0,0,0,3,38,1,0,0,0,5,52,1,0,0,0,7,54,1,0,0,0,9,62,1,
  	0,0,0,11,74,1,0,0,0,13,85,1,0,0,0,15,87,1,0,0,0,17,89,1,0,0,0,19,91,1,
  	0,0,0,21,93,1,0,0,0,23,95,1,0,0,0,25,97,1,0,0,0,27,99,1,0,0,0,29,101,
  	1,0,0,0,31,33,7,0,0,0,32,31,1,0,0,0,33,34,1,0,0,0,34,32,1,0,0,0,34,35,
  	1,0,0,0,35,36,1,0,0,0,36,37,6,0,0,0,37,2,1,0,0,0,38,39,5,47,0,0,39,40,
  	5,42,0,0,40,44,1,0,0,0,41,43,9,0,0,0,42,41,1,0,0,0,43,46,1,0,0,0,44,45,
  	1,0,0,0,44,42,1,0,0,0,45,47,1,0,0,0,46,44,1,0,0,0,47,48,5,42,0,0,48,49,
  	5,47,0,0,49,50,1,0,0,0,50,51,6,1,0,0,51,4,1,0,0,0,52,53,7,1,0,0,53,6,
  	1,0,0,0,54,58,7,2,0,0,55,57,7,3,0,0,56,55,1,0,0,0,57,60,1,0,0,0,58,56,
  	1,0,0,0,58,59,1,0,0,0,59,8,1,0,0,0,60,58,1,0,0,0,61,63,7,4,0,0,62,61,
  	1,0,0,0,63,64,1,0,0,0,64,62,1,0,0,0,64,65,1,0,0,0,65,72,1,0,0,0,66,68,
  	5,46,0,0,67,69,7,4,0,0,68,67,1,0,0,0,69,70,1,0,0,0,70,68,1,0,0,0,70,71,
  	1,0,0,0,71,73,1,0,0,0,72,66,1,0,0,0,72,73,1,0,0,0,73,10,1,0,0,0,74,80,
  	5,34,0,0,75,79,8,5,0,0,76,77,5,92,0,0,77,79,9,0,0,0,78,75,1,0,0,0,78,
  	76,1,0,0,0,79,82,1,0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,83,1,0,0,0,82,
  	80,1,0,0,0,83,84,5,34,0,0,84,12,1,0,0,0,85,86,5,123,0,0,86,14,1,0,0,0,
  	87,88,5,125,0,0,88,16,1,0,0,0,89,90,5,40,0,0,90,18,1,0,0,0,91,92,5,41,
  	0,0,92,20,1,0,0,0,93,94,5,59,0,0,94,22,1,0,0,0,95,96,5,58,0,0,96,24,1,
  	0,0,0,97,98,5,44,0,0,98,26,1,0,0,0,99,100,5,46,0,0,100,28,1,0,0,0,101,
  	102,5,35,0,0,102,30,1,0,0,0,9,0,34,44,58,64,70,72,78,80,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  css_simplelexerLexerStaticData = staticData.release();
}

}

CSS_simpleLexer::CSS_simpleLexer(CharStream *input) : Lexer(input) {
  CSS_simpleLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *css_simplelexerLexerStaticData->atn, css_simplelexerLexerStaticData->decisionToDFA, css_simplelexerLexerStaticData->sharedContextCache);
}

CSS_simpleLexer::~CSS_simpleLexer() {
  delete _interpreter;
}

std::string CSS_simpleLexer::getGrammarFileName() const {
  return "CSS_simple.g4";
}

const std::vector<std::string>& CSS_simpleLexer::getRuleNames() const {
  return css_simplelexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CSS_simpleLexer::getChannelNames() const {
  return css_simplelexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CSS_simpleLexer::getModeNames() const {
  return css_simplelexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CSS_simpleLexer::getVocabulary() const {
  return css_simplelexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CSS_simpleLexer::getSerializedATN() const {
  return css_simplelexerLexerStaticData->serializedATN;
}

const atn::ATN& CSS_simpleLexer::getATN() const {
  return *css_simplelexerLexerStaticData->atn;
}




void CSS_simpleLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  css_simplelexerLexerInitialize();
#else
  ::antlr4::internal::call_once(css_simplelexerLexerOnceFlag, css_simplelexerLexerInitialize);
#endif
}
