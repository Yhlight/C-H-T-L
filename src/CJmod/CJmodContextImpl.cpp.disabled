#include "CJmod/CJmodContextImpl.h"
#include <regex>
#include <stack>
#include <algorithm>

namespace chtl {
namespace cjmod {

// ==================== ScanContextImpl ====================

ScanContextImpl::ScanContextImpl(const std::string& code, size_t position, StateManager* stateMgr)
    : code_(code), position_(position), stateManager_(stateMgr) {
    updateContextState();
}

const std::string& ScanContextImpl::getCode() const {
    return code_;
}

size_t ScanContextImpl::getPosition() const {
    return position_;
}

size_t ScanContextImpl::getLength() const {
    return code_.length();
}

bool ScanContextImpl::isInString() const {
    return inString_;
}

bool ScanContextImpl::isInComment() const {
    return inComment_;
}

bool ScanContextImpl::isInRegex() const {
    return inRegex_;
}

int ScanContextImpl::getBraceDepth() const {
    return braceDepth_;
}

int ScanContextImpl::getParenDepth() const {
    return parenDepth_;
}

int ScanContextImpl::getBracketDepth() const {
    return bracketDepth_;
}

StateManager* ScanContextImpl::getStateManager() {
    return stateManager_;
}

size_t ScanContextImpl::findNext(const std::string& str, size_t from) const {
    size_t pos = code_.find(str, position_ + from);
    return (pos != std::string::npos) ? pos - position_ : std::string::npos;
}

size_t ScanContextImpl::findMatching(char open, char close, size_t from) const {
    size_t pos = position_ + from;
    if (pos >= code_.length() || code_[pos] != open) {
        return std::string::npos;
    }
    
    int depth = 1;
    pos++;
    
    while (pos < code_.length() && depth > 0) {
        // 跳过字符串和注释
        if (code_[pos] == '"' || code_[pos] == '\'') {
            char quote = code_[pos];
            pos++;
            while (pos < code_.length() && code_[pos] != quote) {
                if (code_[pos] == '\\') pos++;
                pos++;
            }
        } else if (pos + 1 < code_.length() && code_[pos] == '/' && code_[pos + 1] == '/') {
            // 单行注释
            while (pos < code_.length() && code_[pos] != '\n') pos++;
        } else if (pos + 1 < code_.length() && code_[pos] == '/' && code_[pos + 1] == '*') {
            // 多行注释
            pos += 2;
            while (pos + 1 < code_.length() && !(code_[pos] == '*' && code_[pos + 1] == '/')) {
                pos++;
            }
            pos += 2;
            continue;
        } else if (code_[pos] == open) {
            depth++;
        } else if (code_[pos] == close) {
            depth--;
            if (depth == 0) {
                return pos - position_;
            }
        }
        pos++;
    }
    
    return std::string::npos;
}

std::string ScanContextImpl::substring(size_t start, size_t length) const {
    size_t actualStart = position_ + start;
    if (actualStart >= code_.length()) return "";
    
    size_t actualLength = std::min(length, code_.length() - actualStart);
    return code_.substr(actualStart, actualLength);
}

bool ScanContextImpl::matches(const std::string& pattern, size_t at) const {
    size_t pos = position_ + at;
    if (pos + pattern.length() > code_.length()) return false;
    
    return code_.compare(pos, pattern.length(), pattern) == 0;
}

void ScanContextImpl::markProcessed(size_t start, size_t end) {
    processedRegions_.push_back({position_ + start, position_ + end});
}

bool ScanContextImpl::isProcessed(size_t pos) const {
    size_t actualPos = position_ + pos;
    
    for (const auto& [start, end] : processedRegions_) {
        if (actualPos >= start && actualPos < end) {
            return true;
        }
    }
    return false;
}

void ScanContextImpl::updateContextState() {
    // 简化的上下文状态更新
    inString_ = false;
    inComment_ = false;
    inRegex_ = false;
    braceDepth_ = 0;
    parenDepth_ = 0;
    bracketDepth_ = 0;
    
    size_t pos = 0;
    while (pos < position_) {
        if (code_[pos] == '"' || code_[pos] == '\'') {
            char quote = code_[pos];
            pos++;
            while (pos < position_ && code_[pos] != quote) {
                if (code_[pos] == '\\') pos++;
                pos++;
            }
            if (pos == position_) {
                inString_ = true;
                return;
            }
        } else if (pos + 1 < code_.length() && code_[pos] == '/' && code_[pos + 1] == '/') {
            // 单行注释
            while (pos < position_ && code_[pos] != '\n') pos++;
            if (pos == position_ && code_[pos - 1] != '\n') {
                inComment_ = true;
                return;
            }
        } else if (pos + 1 < code_.length() && code_[pos] == '/' && code_[pos + 1] == '*') {
            // 多行注释
            pos += 2;
            while (pos + 1 < position_ && !(code_[pos] == '*' && code_[pos + 1] == '/')) {
                pos++;
            }
            if (pos >= position_ - 1) {
                inComment_ = true;
                return;
            }
            pos += 2;
        } else {
            switch (code_[pos]) {
                case '{': braceDepth_++; break;
                case '}': braceDepth_--; break;
                case '(': parenDepth_++; break;
                case ')': parenDepth_--; break;
                case '[': bracketDepth_++; break;
                case ']': bracketDepth_--; break;
            }
        }
        pos++;
    }
}

// ==================== GenerateContextImpl ====================

GenerateContextImpl::GenerateContextImpl(RuntimeBuilder* runtime, StateManager* stateMgr)
    : runtime_(runtime), stateManager_(stateMgr), indentLevel_(0), varCounter_(0), labelCounter_(0) {}

void GenerateContextImpl::emit(const std::string& code) {
    output_ << code;
}

void GenerateContextImpl::emitLine(const std::string& code) {
    output_ << code << "\n";
}

void GenerateContextImpl::emitIndented(const std::string& code) {
    output_ << getIndent() << code << "\n";
}

void GenerateContextImpl::pushIndent() {
    indentLevel_++;
}

void GenerateContextImpl::popIndent() {
    if (indentLevel_ > 0) indentLevel_--;
}

std::string GenerateContextImpl::getIndent() const {
    return std::string(indentLevel_ * 2, ' ');
}

std::string GenerateContextImpl::uniqueVar(const std::string& prefix) {
    return prefix + "_" + std::to_string(varCounter_++);
}

std::string GenerateContextImpl::uniqueLabel(const std::string& prefix) {
    return prefix + "_" + std::to_string(labelCounter_++);
}

RuntimeBuilder& GenerateContextImpl::runtime() {
    return *runtime_;
}

StateManager* GenerateContextImpl::getStateManager() {
    return stateManager_;
}

void GenerateContextImpl::error(const std::string& msg, const ScanResult& result) {
    errors_.push_back({msg, result});
}

void GenerateContextImpl::warning(const std::string& msg, const ScanResult& result) {
    warnings_.push_back({msg, result});
}

std::string GenerateContextImpl::getOutput() const {
    return output_.str();
}

const std::vector<std::pair<std::string, ScanResult>>& GenerateContextImpl::getErrors() const {
    return errors_;
}

const std::vector<std::pair<std::string, ScanResult>>& GenerateContextImpl::getWarnings() const {
    return warnings_;
}

} // namespace cjmod
} // namespace chtl