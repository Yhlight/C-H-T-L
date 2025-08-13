
// Generated from grammars/chtl/CHTL.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  CHTLLexer : public antlr4::Lexer {
public:
  enum {
    WS = 1, COMMENT = 2, MULTILINE_COMMENT = 3, GENERATOR_COMMENT = 4, TEMPLATE = 5, 
    CUSTOM = 6, ORIGIN = 7, CONFIGURATION = 8, IMPORT = 9, NAMESPACE = 10, 
    INFO = 11, EXPORT = 12, STYLE = 13, ELEMENT = 14, VAR = 15, HTML = 16, 
    CSS = 17, JAVASCRIPT = 18, CHTL = 19, INHERIT = 20, DELETE = 21, INSERT = 22, 
    AFTER = 23, BEFORE = 24, REPLACE = 25, AT_TOP = 26, AT_BOTTOM = 27, 
    FROM = 28, AS = 29, EXCEPT = 30, TEXT = 31, STYLE_BLOCK = 32, SCRIPT = 33, 
    LBRACE = 34, RBRACE = 35, LBRACKET = 36, RBRACKET = 37, LPAREN = 38, 
    RPAREN = 39, SEMICOLON = 40, COLON = 41, EQUALS = 42, COMMA = 43, DOT = 44, 
    HASH = 45, PERIOD = 46, IDENTIFIER = 47, NUMBER = 48, STRING = 49, LITERAL = 50
  };

  explicit CHTLLexer(antlr4::CharStream *input);
  ~CHTLLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual antlr4::atn::SerializedATNView getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

