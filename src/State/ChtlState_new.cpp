#include "State/ChtlState.h"
#include "Context/EnhancedContext.h"
#include "Scanner/ChtlScanner.h"
#include <cctype>
#include <sstream>

namespace chtl {

// 新的 handleAtPrefix 实现 - 基于上下文处理
std::shared_ptr<BasicState> ChtlState::handleAtPrefix(char ch) {
    // 读取完整的 @Type 标记
    std::string marker = "@";
    buffer_ = "";
    
    // 读取类型名（Element/Style/Var等）
    while (!isAtEnd() && (std::isalpha(peekChar()) || peekChar() == '_')) {
        advance();
        marker += currentChar();
        buffer_ += currentChar();
    }
    
    // 确定类型
    TokenType type = TokenType::UNKNOWN;
    if (marker == "@Element") {
        type = TokenType::AT_ELEMENT;
    } else if (marker == "@Style") {
        type = TokenType::AT_STYLE;
    } else if (marker == "@Var") {
        type = TokenType::AT_VAR;
    } else if (marker == "@Html") {
        type = TokenType::AT_HTML;
    } else if (marker == "@JavaScript") {
        type = TokenType::AT_JAVASCRIPT;
    } else if (marker == "@Chtl") {
        type = TokenType::AT_CHTL;
    } else {
        // 未知的 @ 标记
        emitToken(TokenType::UNKNOWN);
        subState_ = SubState::INITIAL;
        return nullptr;
    }
    
    // 发出类型 token
    emitToken(type);
    
    // 读取名称
    skipWhitespace();
    if (std::isalpha(peekChar()) || peekChar() == '_') {
        subState_ = SubState::IDENTIFIER;
        buffer_.clear();
    } else {
        subState_ = SubState::INITIAL;
    }
    
    return nullptr;
}

// 处理变量函数调用 - Colors(primary)
void ChtlState::handleVariableFunction() {
    // 当前 buffer_ 包含标识符
    std::string varName = buffer_;
    
    // 检查是否是变量函数调用
    auto* enhancedContext = dynamic_cast<EnhancedContext*>(context_);
    if (!enhancedContext) {
        // 不是增强上下文，按普通标识符处理
        emitToken(TokenType::IDENTIFIER);
        return;
    }
    
    // 检查是否是已注册的变量组
    if (!enhancedContext->findVariable(varName)) {
        // 不是变量组，按普通标识符处理
        emitToken(TokenType::IDENTIFIER);
        return;
    }
    
    // 确认后面是 '('
    if (peekChar() != '(') {
        emitToken(TokenType::IDENTIFIER);
        return;
    }
    
    // 跳过 '('
    advance();
    
    // 读取变量键
    std::string key;
    int parenDepth = 1;
    bool inString = false;
    char stringChar = 0;
    
    while (!isAtEnd() && parenDepth > 0) {
        advance();
        char ch = currentChar();
        
        if (inString) {
            if (ch == stringChar && peekChar(-1) != '\\') {
                inString = false;
            }
            key += ch;
        } else {
            if (ch == '"' || ch == '\'') {
                inString = true;
                stringChar = ch;
                // 不包含引号在 key 中
            } else if (ch == '(') {
                parenDepth++;
                key += ch;
            } else if (ch == ')') {
                parenDepth--;
                if (parenDepth > 0) {
                    key += ch;
                }
            } else if (!std::isspace(ch) || !key.empty()) {
                // 跳过前导空格，但保留中间的空格
                key += ch;
            }
        }
    }
    
    // 去除尾部空格
    while (!key.empty() && std::isspace(key.back())) {
        key.pop_back();
    }
    
    // 处理键中的 = 赋值（用于覆盖）
    std::string actualKey = key;
    std::string overrideValue;
    size_t eqPos = key.find('=');
    if (eqPos != std::string::npos) {
        actualKey = key.substr(0, eqPos);
        overrideValue = key.substr(eqPos + 1);
        
        // 去除空格
        while (!actualKey.empty() && std::isspace(actualKey.back())) {
            actualKey.pop_back();
        }
        while (!overrideValue.empty() && std::isspace(overrideValue.front())) {
            overrideValue.erase(0, 1);
        }
    }
    
    // 获取变量值
    std::optional<std::string> value;
    if (!overrideValue.empty()) {
        // 使用覆盖值
        value = overrideValue;
    } else {
        // 从变量组获取值
        value = enhancedContext->getVariableValue(varName, actualKey);
    }
    
    if (value.has_value()) {
        // 发出替换后的值作为字面量
        buffer_ = value.value();
        emitToken(TokenType::STRING_LITERAL);
    } else {
        // 变量未找到，报告错误
        enhancedContext->reportUndefinedVariable(varName, actualKey);
        // 发出原始文本作为后备
        buffer_ = varName + "(" + key + ")";
        emitToken(TokenType::IDENTIFIER);
    }
    
    buffer_.clear();
    subState_ = SubState::INITIAL;
}

// 处理局部样式块中的选择器
void ChtlState::handleLocalStyleSelector() {
    auto* enhancedContext = dynamic_cast<EnhancedContext*>(context_);
    if (!enhancedContext || !enhancedContext->isInScope(Scope::STYLE_BLOCK)) {
        // 不在局部样式块中，正常处理
        return;
    }
    
    ElementContext* currentElement = enhancedContext->getCurrentElement();
    if (!currentElement) {
        return;
    }
    
    // 检查是否是类选择器或ID选择器
    if (buffer_.length() > 1 && (buffer_[0] == '.' || buffer_[0] == '#')) {
        std::string name = buffer_.substr(1);
        
        if (buffer_[0] == '.') {
            // 自动添加类名
            currentElement->classes.push_back(name);
            // 标记这个样式应该被提取到全局
            markForGlobalExtraction(buffer_);
        } else if (buffer_[0] == '#') {
            // 自动设置ID
            currentElement->id = name;
            // 标记这个样式应该被提取到全局
            markForGlobalExtraction(buffer_);
        }
    }
}

// 处理 & 符号
void ChtlState::handleAmpersand() {
    auto* enhancedContext = dynamic_cast<EnhancedContext*>(context_);
    if (!enhancedContext) {
        emitToken(TokenType::AMPERSAND);
        return;
    }
    
    if (enhancedContext->isInScope(Scope::STYLE_BLOCK)) {
        // 在样式块中，& 需要被解析
        std::string resolved = enhancedContext->resolveAmpersand();
        if (!resolved.empty()) {
            buffer_ = resolved;
            emitToken(TokenType::IDENTIFIER);
            buffer_.clear();
        } else {
            emitToken(TokenType::AMPERSAND);
        }
    } else {
        // 在其他地方，& 保持原样
        emitToken(TokenType::AMPERSAND);
    }
}

// 标记样式规则需要被提取到全局
void ChtlState::markForGlobalExtraction(const std::string& selector) {
    // TODO: 实现样式提取逻辑
    // 这里应该记录哪些样式规则需要被移到全局样式表
}

// 辅助方法
char ChtlState::currentChar() const {
    return lexer_->getCurrentChar();
}

char ChtlState::peekChar(int offset) const {
    return lexer_->peekChar(offset);
}

void ChtlState::advance() {
    lexer_->advance();
}

bool ChtlState::isAtEnd() const {
    return lexer_->isAtEnd();
}

void ChtlState::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peekChar())) {
        advance();
    }
}

void ChtlState::emitToken(TokenType type) {
    lexer_->emitToken(type, buffer_);
}

} // namespace chtl