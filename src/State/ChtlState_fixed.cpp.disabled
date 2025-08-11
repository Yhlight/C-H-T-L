#include "State/ChtlState.h"
#include "Context/EnhancedContext.h"
#include "Error/ErrorHandler.h"

namespace chtl {

// 修复字符串处理 - 处理未闭合的字符串
std::shared_ptr<BasicState> ChtlState::handleStringSingle(char ch) {
    if (ch == '\'' && buffer_.empty() == false && buffer_.back() != '\\') {
        // 字符串正常结束
        emitTokenAndReset(TokenType::STRING_LITERAL);
        subState_ = SubState::INITIAL;
    } else if (ch == '\\') {
        // 处理转义序列
        buffer_ += ch;
        if (!isAtEnd()) {
            advance();
            char escaped = currentChar();
            switch (escaped) {
                case 'n': buffer_.pop_back(); buffer_ += '\n'; break;
                case 't': buffer_.pop_back(); buffer_ += '\t'; break;
                case 'r': buffer_.pop_back(); buffer_ += '\r'; break;
                case '\\': buffer_.pop_back(); buffer_ += '\\'; break;
                case '\'': buffer_.pop_back(); buffer_ += '\''; break;
                default: buffer_ += escaped; break;
            }
        }
    } else if (ch == '\n') {
        // 错误：字符串中出现换行符
        reportError("Unterminated string literal - newline found before closing quote");
        // 尝试恢复：结束当前字符串
        emitTokenAndReset(TokenType::STRING_LITERAL);
        subState_ = SubState::INITIAL;
    } else {
        buffer_ += ch;
    }
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleStringDouble(char ch) {
    if (ch == '"' && (buffer_.empty() || buffer_.back() != '\\')) {
        // 字符串正常结束
        emitTokenAndReset(TokenType::STRING_LITERAL);
        subState_ = SubState::INITIAL;
    } else if (ch == '\\') {
        // 处理转义序列
        buffer_ += ch;
        if (!isAtEnd()) {
            advance();
            char escaped = currentChar();
            switch (escaped) {
                case 'n': buffer_.pop_back(); buffer_ += '\n'; break;
                case 't': buffer_.pop_back(); buffer_ += '\t'; break;
                case 'r': buffer_.pop_back(); buffer_ += '\r'; break;
                case '\\': buffer_.pop_back(); buffer_ += '\\'; break;
                case '"': buffer_.pop_back(); buffer_ += '"'; break;
                default: buffer_ += escaped; break;
            }
        }
    } else if (ch == '\n') {
        // 错误：字符串中出现换行符
        reportError("Unterminated string literal - newline found before closing quote");
        // 尝试恢复：结束当前字符串
        emitTokenAndReset(TokenType::STRING_LITERAL);
        subState_ = SubState::INITIAL;
    } else {
        buffer_ += ch;
    }
    return nullptr;
}

// 完成 token 时检查未完成的状态
void ChtlState::completeToken() {
    switch (subState_) {
        case SubState::IDENTIFIER:
            emitToken(determineIdentifierType());
            break;
            
        case SubState::STRING_SINGLE:
            reportError("Unterminated string literal - expected closing single quote (')");
            emitToken(TokenType::STRING_LITERAL);
            break;
            
        case SubState::STRING_DOUBLE:
            reportError("Unterminated string literal - expected closing double quote (\")");
            emitToken(TokenType::STRING_LITERAL);
            break;
            
        case SubState::UNQUOTED_LITERAL:
            emitToken(TokenType::UNQUOTED_LITERAL);
            break;
            
        case SubState::NUMBER:
            emitToken(TokenType::NUMBER);
            break;
            
        case SubState::OPERATOR:
            emitToken(determineOperatorType());
            break;
            
        case SubState::COMMENT_SINGLE:
            emitTokenAndReset(TokenType::SINGLE_LINE_COMMENT);
            break;
            
        case SubState::COMMENT_MULTI:
            reportError("Unterminated comment - expected closing */");
            emitTokenAndReset(TokenType::MULTI_LINE_COMMENT);
            break;
            
        case SubState::HTML_COMMENT:
            emitTokenAndReset(TokenType::HTML_COMMENT);
            break;
            
        case SubState::AT_PREFIX:
            emitToken(determineAtPrefixType());
            break;
            
        case SubState::SPECIAL_MARKER:
            reportError("Incomplete special marker - expected closing ]");
            emitToken(TokenType::UNKNOWN);
            break;
            
        default:
            break;
    }
    
    buffer_.clear();
    subState_ = SubState::INITIAL;
}

// 处理大括号平衡
std::shared_ptr<BasicState> ChtlState::handleLeftBrace(char ch) {
    braceDepth_++;
    emitTokenAndReset(TokenType::LEFT_BRACE);
    
    // 检查是否进入特定块
    auto* enhancedContext = dynamic_cast<EnhancedContext*>(context_);
    if (enhancedContext) {
        // 根据上下文判断是否进入 style 或 script 块
        // 这需要配合 Parser 来实现
    }
    
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleRightBrace(char ch) {
    if (braceDepth_ > 0) {
        braceDepth_--;
    } else {
        reportWarning("Unmatched closing brace }");
    }
    
    emitTokenAndReset(TokenType::RIGHT_BRACE);
    
    // 检查是否需要切换状态
    if (braceDepth_ == 0) {
        // 可能需要返回到父状态
    }
    
    return nullptr;
}

// 错误报告辅助方法
void ChtlState::reportError(const std::string& message) {
    if (auto* enhancedContext = dynamic_cast<EnhancedContext*>(context_)) {
        ErrorContext errorContext;
        errorContext.line = lexer_->getCurrentLine();
        errorContext.column = lexer_->getCurrentColumn();
        errorContext.fileName = lexer_->getCurrentFile();
        errorContext.contextLines = getContextLines();
        
        ErrorDetail error(ErrorType::LEXICAL, message, errorContext);
        enhancedContext->reportError(error);
    } else if (context_) {
        context_->addError(message);
    }
}

void ChtlState::reportWarning(const std::string& message) {
    if (auto* enhancedContext = dynamic_cast<EnhancedContext*>(context_)) {
        ErrorContext errorContext;
        errorContext.line = lexer_->getCurrentLine();
        errorContext.column = lexer_->getCurrentColumn();
        errorContext.fileName = lexer_->getCurrentFile();
        
        ErrorDetail warning(ErrorType::GENERAL, message, errorContext);
        warning.setSeverity(ErrorSeverity::WARNING);
        enhancedContext->reportWarning(warning);
    } else if (context_) {
        context_->addWarning(message);
    }
}

// 获取错误上下文行
std::string ChtlState::getContextLines() const {
    // 从词法分析器获取当前行和周围的行
    std::stringstream ss;
    int currentLine = lexer_->getCurrentLine();
    
    for (int i = std::max(1, currentLine - 2); i <= currentLine + 2; i++) {
        std::string line = lexer_->getSourceLine(i);
        if (!line.empty()) {
            ss << std::setw(4) << i << " | " << line << "\n";
            if (i == currentLine) {
                int col = lexer_->getCurrentColumn();
                ss << "     | " << std::string(col - 1, ' ') << "^" << "\n";
            }
        }
    }
    
    return ss.str();
}

// 验证标识符
bool ChtlState::isValidIdentifier(const std::string& id) const {
    if (id.empty()) return false;
    
    // 首字符必须是字母或下划线
    if (!std::isalpha(id[0]) && id[0] != '_') {
        return false;
    }
    
    // 其余字符可以是字母、数字或下划线
    for (size_t i = 1; i < id.length(); i++) {
        if (!std::isalnum(id[i]) && id[i] != '_') {
            return false;
        }
    }
    
    return true;
}

} // namespace chtl