
// Generated from grammars/chtljs/CHTLJS.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CHTLJSLexer : public antlr4::Lexer {
public:
  enum {
    CHTL_SCRIPT = 1, CHTL_LISTEN = 2, CHTL_DELEGATE = 3, CHTL_ANIMATE = 4, 
    CHTL_AT = 5, CHTL_WHEN = 6, CHTL_BEGIN = 7, CHTL_END = 8, CHTL_LOOP = 9, 
    CHTL_DIRECTION = 10, CHTL_DELAY = 11, CHTL_CALLBACK = 12, CHTL_TARGET = 13, 
    CHTL_EASING = 14, CHTL_DURATION = 15, CHTL_DOUBLE_BRACE = 16, CHTL_DOUBLE_BRACE_CLOSE = 17, 
    CHTL_ARROW = 18, LBRACE = 19, RBRACE = 20, LPAREN = 21, RPAREN = 22, 
    LBRACKET = 23, RBRACKET = 24, SEMICOLON = 25, COLON = 26, COMMA = 27, 
    DOT = 28, HASH = 29, EQUALS = 30, MINUS = 31, ASSIGN = 32, WS = 33
  };

  explicit CHTLJSLexer(antlr4::CharStream *input);

  ~CHTLJSLexer() override;


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

