
// Generated from grammars/css/CSS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CSS_simpleLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, COMMENT = 2, SELECTOR = 3, IDENTIFIER = 4, NUMBER = 5, STRING = 6, 
    LBRACE = 7, RBRACE = 8, LPAREN = 9, RPAREN = 10, SEMICOLON = 11, COLON = 12, 
    COMMA = 13, DOT = 14, HASH = 15
  };

  explicit CSS_simpleLexer(antlr4::CharStream *input);

  ~CSS_simpleLexer() override;


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

