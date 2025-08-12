
// Generated from grammars/js/JavaScript_simple.g4 by ANTLR 4.13.1


#include "JavaScript_simpleLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct JavaScript_simpleLexerStaticData final {
  JavaScript_simpleLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  JavaScript_simpleLexerStaticData(const JavaScript_simpleLexerStaticData&) = delete;
  JavaScript_simpleLexerStaticData(JavaScript_simpleLexerStaticData&&) = delete;
  JavaScript_simpleLexerStaticData& operator=(const JavaScript_simpleLexerStaticData&) = delete;
  JavaScript_simpleLexerStaticData& operator=(JavaScript_simpleLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag javascript_simplelexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
JavaScript_simpleLexerStaticData *javascript_simplelexerLexerStaticData = nullptr;

void javascript_simplelexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (javascript_simplelexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(javascript_simplelexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<JavaScript_simpleLexerStaticData>(
    std::vector<std::string>{
      "WS", "COMMENT", "FUNCTION", "VAR", "LET", "CONST", "IF", "ELSE", 
      "FOR", "WHILE", "RETURN", "IDENTIFIER", "NUMBER", "STRING", "LBRACE", 
      "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "SEMICOLON", 
      "COMMA", "DOT", "EQUALS", "PLUS", "MINUS", "MULTIPLY", "DIVIDE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "", "'function'", "'var'", "'let'", "'const'", "'if'", "'else'", 
      "'for'", "'while'", "'return'", "", "", "", "'{'", "'}'", "'('", "')'", 
      "'['", "']'", "';'", "','", "'.'", "'='", "'+'", "'-'", "'*'", "'/'"
    },
    std::vector<std::string>{
      "", "WS", "COMMENT", "FUNCTION", "VAR", "LET", "CONST", "IF", "ELSE", 
      "FOR", "WHILE", "RETURN", "IDENTIFIER", "NUMBER", "STRING", "LBRACE", 
      "RBRACE", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "SEMICOLON", 
      "COMMA", "DOT", "EQUALS", "PLUS", "MINUS", "MULTIPLY", "DIVIDE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,28,182,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,
  	4,0,59,8,0,11,0,12,0,60,1,0,1,0,1,1,1,1,1,1,1,1,5,1,69,8,1,10,1,12,1,
  	72,9,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,
  	4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,
  	1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,11,1,11,5,11,126,8,11,10,11,12,11,129,9,11,1,12,4,12,132,8,12,
  	11,12,12,12,133,1,12,1,12,4,12,138,8,12,11,12,12,12,139,3,12,142,8,12,
  	1,13,1,13,1,13,1,13,5,13,148,8,13,10,13,12,13,151,9,13,1,13,1,13,1,14,
  	1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,20,1,20,1,21,
  	1,21,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,1,26,1,26,1,27,1,27,0,0,
  	28,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,
  	14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,
  	51,26,53,27,55,28,1,0,6,3,0,9,10,13,13,32,32,2,0,10,10,13,13,4,0,36,36,
  	65,90,95,95,97,122,5,0,36,36,48,57,65,90,95,95,97,122,1,0,48,57,2,0,34,
  	34,92,92,189,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,
  	0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,
  	0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,
  	1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,
  	0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,
  	0,53,1,0,0,0,0,55,1,0,0,0,1,58,1,0,0,0,3,64,1,0,0,0,5,75,1,0,0,0,7,84,
  	1,0,0,0,9,88,1,0,0,0,11,92,1,0,0,0,13,98,1,0,0,0,15,101,1,0,0,0,17,106,
  	1,0,0,0,19,110,1,0,0,0,21,116,1,0,0,0,23,123,1,0,0,0,25,131,1,0,0,0,27,
  	143,1,0,0,0,29,154,1,0,0,0,31,156,1,0,0,0,33,158,1,0,0,0,35,160,1,0,0,
  	0,37,162,1,0,0,0,39,164,1,0,0,0,41,166,1,0,0,0,43,168,1,0,0,0,45,170,
  	1,0,0,0,47,172,1,0,0,0,49,174,1,0,0,0,51,176,1,0,0,0,53,178,1,0,0,0,55,
  	180,1,0,0,0,57,59,7,0,0,0,58,57,1,0,0,0,59,60,1,0,0,0,60,58,1,0,0,0,60,
  	61,1,0,0,0,61,62,1,0,0,0,62,63,6,0,0,0,63,2,1,0,0,0,64,65,5,47,0,0,65,
  	66,5,47,0,0,66,70,1,0,0,0,67,69,8,1,0,0,68,67,1,0,0,0,69,72,1,0,0,0,70,
  	68,1,0,0,0,70,71,1,0,0,0,71,73,1,0,0,0,72,70,1,0,0,0,73,74,6,1,0,0,74,
  	4,1,0,0,0,75,76,5,102,0,0,76,77,5,117,0,0,77,78,5,110,0,0,78,79,5,99,
  	0,0,79,80,5,116,0,0,80,81,5,105,0,0,81,82,5,111,0,0,82,83,5,110,0,0,83,
  	6,1,0,0,0,84,85,5,118,0,0,85,86,5,97,0,0,86,87,5,114,0,0,87,8,1,0,0,0,
  	88,89,5,108,0,0,89,90,5,101,0,0,90,91,5,116,0,0,91,10,1,0,0,0,92,93,5,
  	99,0,0,93,94,5,111,0,0,94,95,5,110,0,0,95,96,5,115,0,0,96,97,5,116,0,
  	0,97,12,1,0,0,0,98,99,5,105,0,0,99,100,5,102,0,0,100,14,1,0,0,0,101,102,
  	5,101,0,0,102,103,5,108,0,0,103,104,5,115,0,0,104,105,5,101,0,0,105,16,
  	1,0,0,0,106,107,5,102,0,0,107,108,5,111,0,0,108,109,5,114,0,0,109,18,
  	1,0,0,0,110,111,5,119,0,0,111,112,5,104,0,0,112,113,5,105,0,0,113,114,
  	5,108,0,0,114,115,5,101,0,0,115,20,1,0,0,0,116,117,5,114,0,0,117,118,
  	5,101,0,0,118,119,5,116,0,0,119,120,5,117,0,0,120,121,5,114,0,0,121,122,
  	5,110,0,0,122,22,1,0,0,0,123,127,7,2,0,0,124,126,7,3,0,0,125,124,1,0,
  	0,0,126,129,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,24,1,0,0,0,129,
  	127,1,0,0,0,130,132,7,4,0,0,131,130,1,0,0,0,132,133,1,0,0,0,133,131,1,
  	0,0,0,133,134,1,0,0,0,134,141,1,0,0,0,135,137,5,46,0,0,136,138,7,4,0,
  	0,137,136,1,0,0,0,138,139,1,0,0,0,139,137,1,0,0,0,139,140,1,0,0,0,140,
  	142,1,0,0,0,141,135,1,0,0,0,141,142,1,0,0,0,142,26,1,0,0,0,143,149,5,
  	34,0,0,144,148,8,5,0,0,145,146,5,92,0,0,146,148,9,0,0,0,147,144,1,0,0,
  	0,147,145,1,0,0,0,148,151,1,0,0,0,149,147,1,0,0,0,149,150,1,0,0,0,150,
  	152,1,0,0,0,151,149,1,0,0,0,152,153,5,34,0,0,153,28,1,0,0,0,154,155,5,
  	123,0,0,155,30,1,0,0,0,156,157,5,125,0,0,157,32,1,0,0,0,158,159,5,40,
  	0,0,159,34,1,0,0,0,160,161,5,41,0,0,161,36,1,0,0,0,162,163,5,91,0,0,163,
  	38,1,0,0,0,164,165,5,93,0,0,165,40,1,0,0,0,166,167,5,59,0,0,167,42,1,
  	0,0,0,168,169,5,44,0,0,169,44,1,0,0,0,170,171,5,46,0,0,171,46,1,0,0,0,
  	172,173,5,61,0,0,173,48,1,0,0,0,174,175,5,43,0,0,175,50,1,0,0,0,176,177,
  	5,45,0,0,177,52,1,0,0,0,178,179,5,42,0,0,179,54,1,0,0,0,180,181,5,47,
  	0,0,181,56,1,0,0,0,9,0,60,70,127,133,139,141,147,149,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  javascript_simplelexerLexerStaticData = staticData.release();
}

}

JavaScript_simpleLexer::JavaScript_simpleLexer(CharStream *input) : Lexer(input) {
  JavaScript_simpleLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *javascript_simplelexerLexerStaticData->atn, javascript_simplelexerLexerStaticData->decisionToDFA, javascript_simplelexerLexerStaticData->sharedContextCache);
}

JavaScript_simpleLexer::~JavaScript_simpleLexer() {
  delete _interpreter;
}

std::string JavaScript_simpleLexer::getGrammarFileName() const {
  return "JavaScript_simple.g4";
}

const std::vector<std::string>& JavaScript_simpleLexer::getRuleNames() const {
  return javascript_simplelexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& JavaScript_simpleLexer::getChannelNames() const {
  return javascript_simplelexerLexerStaticData->channelNames;
}

const std::vector<std::string>& JavaScript_simpleLexer::getModeNames() const {
  return javascript_simplelexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& JavaScript_simpleLexer::getVocabulary() const {
  return javascript_simplelexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView JavaScript_simpleLexer::getSerializedATN() const {
  return javascript_simplelexerLexerStaticData->serializedATN;
}

const atn::ATN& JavaScript_simpleLexer::getATN() const {
  return *javascript_simplelexerLexerStaticData->atn;
}




void JavaScript_simpleLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  javascript_simplelexerLexerInitialize();
#else
  ::antlr4::internal::call_once(javascript_simplelexerLexerOnceFlag, javascript_simplelexerLexerInitialize);
#endif
}
