
// Generated from grammars/js/JavaScript_simple.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  JavaScript_simpleLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, COMMENT = 2, FUNCTION = 3, VAR = 4, LET = 5, CONST = 6, IF = 7, 
    ELSE = 8, FOR = 9, WHILE = 10, RETURN = 11, IDENTIFIER = 12, NUMBER = 13, 
    STRING = 14, LBRACE = 15, RBRACE = 16, LPAREN = 17, RPAREN = 18, LBRACKET = 19, 
    RBRACKET = 20, SEMICOLON = 21, COMMA = 22, DOT = 23, EQUALS = 24, PLUS = 25, 
    MINUS = 26, MULTIPLY = 27, DIVIDE = 28
  };

  explicit JavaScript_simpleLexer(antlr4::CharStream *input);

  ~JavaScript_simpleLexer() override;


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

