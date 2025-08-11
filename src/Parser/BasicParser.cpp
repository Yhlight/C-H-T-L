#include "Parser/BasicParser.h"
#include "Common/GlobalMap.h"
#include <sstream>
#include <iostream>

namespace chtl {

BasicParser::BasicParser()
    : lexer_(nullptr), 
      context_(nullptr), 
      rootNode_(nullptr),
      state_(ParseState::INITIAL),
      hasLookahead_(false) {
}

bool BasicParser::initialize(std::shared_ptr<BasicLexer> lexer, 
                           std::shared_ptr<BasicContext> context) {
    if (!lexer || !context) {
        reportError("Invalid lexer or context provided to parser");
        return false;
    }
    
    lexer_ = lexer;
    context_ = context;
    state_ = ParseState::INITIAL;
    errors_.clear();
    warnings_.clear();
    hasLookahead_ = false;
    
    // 清空节点栈
    while (!nodeStack_.empty()) {
        nodeStack_.pop();
    }
    
    initializeParser();
    return true;
}

std::shared_ptr<Node> BasicParser::parseFile(const std::string& filename) {
    if (!lexer_) {
        reportError("Parser not initialized with lexer");
        return nullptr;
    }
    
    if (!lexer_->initialize(filename)) {
        reportError("Failed to initialize lexer with file: " + filename);
        return nullptr;
    }
    
    return parse();
}

std::shared_ptr<Node> BasicParser::parseString(const std::string& content) {
    if (!lexer_) {
        reportError("Parser not initialized with lexer");
        return nullptr;
    }
    
    auto stream = std::make_unique<std::istringstream>(content);
    if (!lexer_->initialize(std::move(stream), "<string>")) {
        reportError("Failed to initialize lexer with string content");
        return nullptr;
    }
    
    return parse();
}

Token BasicParser::getNextToken() {
    if (hasLookahead_) {
        hasLookahead_ = false;
        return currentToken_;
    }
    
    return lexer_->getNextToken();
}

Token BasicParser::peekNextToken() {
    if (!hasLookahead_) {
        currentToken_ = lexer_->getNextToken();
        hasLookahead_ = true;
    }
    return currentToken_;
}

void BasicParser::consumeToken() {
    getNextToken();
}

bool BasicParser::matchToken(TokenType type) {
    if (peekNextToken().getType() == type) {
        consumeToken();
        return true;
    }
    return false;
}

bool BasicParser::expectToken(TokenType type) {
    if (matchToken(type)) {
        return true;
    }
    
    std::string error = "Expected " + getTokenDescription(type) + 
                       " but got " + getTokenDescription(peekNextToken().getType());
    reportError(error, peekNextToken());
    return false;
}

bool BasicParser::expectToken(TokenType type, const std::string& errorMsg) {
    if (matchToken(type)) {
        return true;
    }
    
    reportError(errorMsg, peekNextToken());
    return false;
}

bool BasicParser::isAtEnd() const {
    return lexer_ && !lexer_->hasMoreTokens();
}

void BasicParser::synchronize() {
    // 基本的错误恢复策略
    // 跳过token直到找到一个同步点（如分号、右括号等）
    consumeToken();
    
    while (!isAtEnd()) {
        if (previousToken_.getType() == TokenType::SEMICOLON) {
            return;
        }
        
        switch (peekNextToken().getType()) {
            case TokenType::TEMPLATE:
            case TokenType::CUSTOM:
            case TokenType::NAMESPACE_KW:
            case TokenType::CONFIGURATION:
            case TokenType::IMPORT:
            case TokenType::LEFT_BRACE:
            case TokenType::RIGHT_BRACE:
                return;
            default:
                break;
        }
        
        consumeToken();
    }
}

std::shared_ptr<Node> BasicParser::popNode() {
    if (nodeStack_.empty()) {
        reportWarning("Attempted to pop from empty node stack");
        return nullptr;
    }
    
    auto node = nodeStack_.top();
    nodeStack_.pop();
    return node;
}

std::shared_ptr<Node> BasicParser::peekNode() const {
    if (nodeStack_.empty()) {
        return nullptr;
    }
    return nodeStack_.top();
}

void BasicParser::reportError(const std::string& message) {
    if (lexer_) {
        errors_.push_back(ParseError(
            message,
            lexer_->getCurrentLine(),
            lexer_->getCurrentColumn(),
            lexer_->getFilename()
        ));
    } else {
        errors_.push_back(ParseError(message, 0, 0, "<unknown>"));
    }
    state_ = ParseState::ERROR;
}

void BasicParser::reportError(const std::string& message, const Token& token) {
    errors_.push_back(ParseError(
        message,
        token.getLine(),
        token.getColumn(),
        lexer_ ? lexer_->getFilename() : "<unknown>"
    ));
    state_ = ParseState::ERROR;
}

void BasicParser::reportWarning(const std::string& message) {
    if (lexer_) {
        warnings_.push_back(ParseError(
            message,
            lexer_->getCurrentLine(),
            lexer_->getCurrentColumn(),
            lexer_->getFilename()
        ));
    } else {
        warnings_.push_back(ParseError(message, 0, 0, "<unknown>"));
    }
}

void BasicParser::reportWarning(const std::string& message, const Token& token) {
    warnings_.push_back(ParseError(
        message,
        token.getLine(),
        token.getColumn(),
        lexer_ ? lexer_->getFilename() : "<unknown>"
    ));
}

std::string BasicParser::getTokenDescription(TokenType type) const {
    // 暂时返回简单描述
    switch(type) {
        case TokenType::IDENTIFIER: return "identifier";
        case TokenType::NUMBER: return "number";
        case TokenType::STRING_LITERAL: return "string";
        case TokenType::LEFT_BRACE: return "'{'";
        case TokenType::RIGHT_BRACE: return "'}'";
        case TokenType::LEFT_PAREN: return "'('";
        case TokenType::RIGHT_PAREN: return "')'";
        case TokenType::SEMICOLON: return "';'";
        case TokenType::COMMA: return "','";
        case TokenType::COLON: return "':'";
        case TokenType::EOF_TOKEN: return "end of file";
        default: return "token";
    }
}

std::string BasicParser::getCurrentPosition() const {
    if (lexer_) {
        std::stringstream ss;
        ss << lexer_->getFilename() << ":" 
           << lexer_->getCurrentLine() << ":" 
           << lexer_->getCurrentColumn();
        return ss.str();
    }
    return "<unknown>:0:0";
}

} // namespace chtl