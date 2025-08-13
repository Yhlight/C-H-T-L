
// Generated from grammars/chtl/CHTL_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTL_simpleLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, COMMENT = 2, TEMPLATE = 3, CUSTOM = 4, ORIGIN = 5, TEXT = 6, 
    STYLE = 7, SCRIPT = 8, LBRACE = 9, RBRACE = 10, SEMICOLON = 11, COLON = 12, 
    EQUALS = 13, DOT = 14, IDENTIFIER = 15, NUMBER = 16, STRING = 17
  };

  explicit CHTL_simpleLexer(antlr4::CharStream *input);

  ~CHTL_simpleLexer() override;


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

