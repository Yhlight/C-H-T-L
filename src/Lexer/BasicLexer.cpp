#include "Lexer/BasicLexer.h"
#include "State/StateFactory.h"
#include "Context/ContextFactory.h"
#include <iostream>
#include <sstream>
#include <cstring>

namespace chtl {

BasicLexer::BasicLexer()
    : filename_("<unknown>"),
      currentLine_(1),
      currentColumn_(1),
      currentPosition_(0),
      bufferPos_(0),
      bufferSize_(0),
      hasError_(false) {
    std::memset(buffer_, 0, BUFFER_SIZE);
}

BasicLexer::~BasicLexer() {
    // 虚析构函数
}

bool BasicLexer::initialize(const std::string& filename) {
    auto fileStream = std::make_unique<std::ifstream>(filename, std::ios::binary);
    if (!fileStream->is_open()) {
        reportError("Failed to open file: " + filename);
        return false;
    }
    
    filename_ = filename;
    inputStream_ = std::move(fileStream);
    
    // 创建初始状态和上下文
    currentState_ = createInitialState();
    context_ = createInitialContext();
    
    if (!currentState_ || !context_) {
        reportError("Failed to create initial state or context");
        return false;
    }
    
    // 通知状态进入
    currentState_->onEnter();
    
    return true;
}

bool BasicLexer::initialize(std::unique_ptr<std::istream> stream, const std::string& sourceName) {
    if (!stream) {
        reportError("Invalid input stream");
        return false;
    }
    
    filename_ = sourceName;
    inputStream_ = std::move(stream);
    
    // 创建初始状态和上下文
    currentState_ = createInitialState();
    context_ = createInitialContext();
    
    if (!currentState_ || !context_) {
        reportError("Failed to create initial state or context");
        return false;
    }
    
    // 通知状态进入
    currentState_->onEnter();
    
    return true;
}

Token BasicLexer::getNextToken() {
    // 如果队列中有token，返回队列中的
    if (!tokenQueue_.empty()) {
        Token token = tokenQueue_.front();
        tokenQueue_.pop();
        return token;
    }
    
    // 处理字符直到产生token
    while (tokenQueue_.empty() && !isEOF()) {
        char ch = getNextChar();
        if (ch != '\0') {
            processChar(ch);
        }
    }
    
    // 如果到达文件末尾，让状态完成处理
    if (isEOF() && tokenQueue_.empty()) {
        if (currentState_) {
            currentState_->onEnd();
        }
        finalizeTokens();
    }
    
    // 返回token或EOF
    if (!tokenQueue_.empty()) {
        Token token = tokenQueue_.front();
        tokenQueue_.pop();
        return token;
    }
    
    return Token(TokenType::EOF_TOKEN, "", currentLine_, currentColumn_, filename_);
}

Token BasicLexer::peekNextToken() {
    if (!tokenQueue_.empty()) {
        return tokenQueue_.front();
    }
    
    // 获取下一个token但不移除
    Token token = getNextToken();
    if (token.getType() != TokenType::EOF_TOKEN) {
        // 将token放回队列前端
        std::queue<Token> tempQueue;
        tempQueue.push(token);
        while (!tokenQueue_.empty()) {
            tempQueue.push(tokenQueue_.front());
            tokenQueue_.pop();
        }
        tokenQueue_ = std::move(tempQueue);
    }
    
    return token;
}

bool BasicLexer::hasMoreTokens() {
    return !tokenQueue_.empty() || !isEOF();
}

std::vector<Token> BasicLexer::getAllTokens() {
    std::vector<Token> tokens;
    
    Token token;
    do {
        token = getNextToken();
        tokens.push_back(token);
    } while (token.getType() != TokenType::EOF_TOKEN);
    
    return tokens;
}

void BasicLexer::setState(std::shared_ptr<BasicState> state) {
    if (currentState_) {
        currentState_->onExit();
    }
    
    currentState_ = state;
    
    if (currentState_) {
        currentState_->onEnter();
    }
}

void BasicLexer::emitToken(const Token& token) {
    tokenQueue_.push(token);
}

void BasicLexer::emitToken(TokenType type, const std::string& value) {
    emitToken(Token(type, value, currentLine_, currentColumn_, filename_));
}

void BasicLexer::emitToken(TokenType type, const std::string& value, int line, int column) {
    emitToken(Token(type, value, line, column, filename_));
}

char BasicLexer::getNextChar() {
    if (bufferPos_ >= bufferSize_) {
        if (!fillBuffer()) {
            return '\0';
        }
    }
    
    char ch = buffer_[bufferPos_++];
    updatePosition(ch);
    return ch;
}

char BasicLexer::peekChar() {
    if (bufferPos_ >= bufferSize_) {
        if (!fillBuffer()) {
            return '\0';
        }
    }
    
    return buffer_[bufferPos_];
}

void BasicLexer::ungetChar() {
    if (bufferPos_ > 0) {
        bufferPos_--;
        // 更新位置（简单实现，可能不完全准确）
        if (currentColumn_ > 1) {
            currentColumn_--;
        }
        currentPosition_--;
    }
}

bool BasicLexer::isEOF() const {
    return !inputStream_ || (inputStream_->eof() && bufferPos_ >= bufferSize_);
}

bool BasicLexer::fillBuffer() {
    if (!inputStream_ || inputStream_->eof()) {
        return false;
    }
    
    inputStream_->read(buffer_, BUFFER_SIZE);
    bufferSize_ = static_cast<int>(inputStream_->gcount());
    bufferPos_ = 0;
    
    return bufferSize_ > 0;
}

void BasicLexer::reportError(const std::string& message) {
    reportError(message, currentLine_, currentColumn_);
}

void BasicLexer::reportError(const std::string& message, int line, int column) {
    hasError_ = true;
    std::stringstream ss;
    ss << filename_ << ":" << line << ":" << column << ": error: " << message;
    lastError_ = ss.str();
    
    // 输出到错误流
    std::cerr << lastError_ << std::endl;
    
    // 添加到上下文的错误列表
    if (context_) {
        context_->addError(lastError_);
    }
}

void BasicLexer::updatePosition(char ch) {
    currentPosition_++;
    
    if (ch == '\n') {
        currentLine_++;
        currentColumn_ = 1;
    } else if (ch == '\t') {
        // Tab通常算作4个空格
        currentColumn_ += 4 - ((currentColumn_ - 1) % 4);
    } else {
        currentColumn_++;
    }
}

void BasicLexer::skipWhitespace() {
    char ch = peekChar();
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        getNextChar();
        ch = peekChar();
    }
}

std::string BasicLexer::readUntil(const std::string& delimiters) {
    std::string result;
    char ch = peekChar();
    
    while (ch != '\0' && delimiters.find(ch) == std::string::npos) {
        result += getNextChar();
        ch = peekChar();
    }
    
    return result;
}

std::string BasicLexer::readWhile(const std::string& allowedChars) {
    std::string result;
    char ch = peekChar();
    
    while (ch != '\0' && allowedChars.find(ch) != std::string::npos) {
        result += getNextChar();
        ch = peekChar();
    }
    
    return result;
}

void BasicLexer::processChar(char ch) {
    if (currentState_) {
        // 让当前状态处理字符
        auto newState = currentState_->handleChar(ch);
        
        // 如果状态改变，切换状态
        if (newState) {
            setState(newState);
        }
    }
}

void BasicLexer::finalizeTokens() {
    // 确保所有待处理的token都被发出
    if (currentState_) {
        currentState_->onEnd();
    }
    
    // 如果队列为空，添加EOF token
    if (tokenQueue_.empty()) {
        emitToken(TokenType::EOF_TOKEN, "");
    }
}

void BasicLexer::autoTransitionState(const std::string& trigger) {
    if (!currentState_) {
        return;
    }
    
    // 尝试自动状态转换
    auto newState = StateFactory::autoTransition(this, currentState_, trigger);
    if (newState && newState != currentState_) {
        setState(newState);
    }
}

void BasicLexer::updateState(char ch) {
    if (!currentState_) {
        return;
    }
    
    // 尝试状态转换
    auto newState = StateFactory::transition(currentState_->getType(), ch);
    if (newState && newState != currentState_) {
        setState(newState);
    }
}

} // namespace chtl