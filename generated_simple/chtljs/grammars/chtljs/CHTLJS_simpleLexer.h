
// Generated from grammars/chtljs/CHTLJS_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLJS_simpleLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, COMMENT = 2, CHTL_SCRIPT = 3, CHTL_LISTEN = 4, CHTL_DELEGATE = 5, 
    CHTL_ANIMATE = 6, CHTL_DOUBLE_BRACE = 7, CHTL_DOUBLE_BRACE_CLOSE = 8, 
    CHTL_ARROW = 9, IDENTIFIER = 10, NUMBER = 11, STRING = 12, LBRACE = 13, 
    RBRACE = 14, LPAREN = 15, RPAREN = 16, SEMICOLON = 17, COLON = 18, COMMA = 19, 
    DOT = 20, HASH = 21
  };

  explicit CHTLJS_simpleLexer(antlr4::CharStream *input);

  ~CHTLJS_simpleLexer() override;


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

