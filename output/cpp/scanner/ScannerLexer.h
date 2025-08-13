
// Generated from Scanner.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  ScannerLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, TEXT = 4, STYLE = 5, SCRIPT = 6, TEMPLATE_START = 7, 
    CUSTOM_START = 8, CONFIG_START = 9, NAMESPACE_START = 10, IMPORT_START = 11, 
    ORIGIN_START = 12, COLON_OR_EQUAL = 13, IDENTIFIER = 14, STRING_LITERAL = 15, 
    UNQUOTED_LITERAL = 16, ATTR_VALUE = 17, ANY_CONTENT = 18, WS = 19, COMMENT = 20, 
    MULTI_COMMENT = 21
  };

  explicit ScannerLexer(antlr4::CharStream *input);

  ~ScannerLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

