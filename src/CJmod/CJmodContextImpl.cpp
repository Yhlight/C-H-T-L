#include "CJmod/CJmodCore.h"
#include <regex>
#include <stack>

namespace chtl {
namespace cjmod {

// 扫描上下文实现
class ScanContextImpl : public ScanContext {
private:
    const std::string& code_;
    size_t position_;
    
    // 状态跟踪
    mutable std::stack<char> brackets_;
    mutable bool inString_ = false;
    mutable bool inComment_ = false;
    mutable bool inRegex_ = false;
    mutable char stringChar_ = 0;
    
    // 已处理区域
    std::vector<std::pair<size_t, size_t>> processedRegions_;
    
    // 状态管理器
    StateManager* stateManager_;
    
public:
    ScanContextImpl(const std::string& code, StateManager* stateMgr)
        : code_(code), position_(0), stateManager_(stateMgr) {}
    
    // 基础信息
    const std::string& getCode() const override { return code_; }
    size_t getPosition() const override { return position_; }
    size_t getLength() const override { return code_.length(); }
    
    // 上下文状态
    bool isInString() const override {
        updateContextState();
        return inString_;
    }
    
    bool isInComment() const override {
        updateContextState();
        return inComment_;
    }
    
    bool isInRegex() const override {
        updateContextState();
        return inRegex_;
    }
    
    int getBraceDepth() const override {
        int depth = 0;
        for (size_t i = 0; i < position_ && i < code_.length(); i++) {
            if (!isInStringOrComment(i)) {
                if (code_[i] == '{') depth++;
                else if (code_[i] == '}') depth--;
            }
        }
        return depth;
    }
    
    int getParenDepth() const override {
        int depth = 0;
        for (size_t i = 0; i < position_ && i < code_.length(); i++) {
            if (!isInStringOrComment(i)) {
                if (code_[i] == '(') depth++;
                else if (code_[i] == ')') depth--;
            }
        }
        return depth;
    }
    
    int getBracketDepth() const override {
        int depth = 0;
        for (size_t i = 0; i < position_ && i < code_.length(); i++) {
            if (!isInStringOrComment(i)) {
                if (code_[i] == '[') depth++;
                else if (code_[i] == ']') depth--;
            }
        }
        return depth;
    }
    
    // 工具方法
    size_t findNext(const std::string& str, size_t from) const override {
        return code_.find(str, from);
    }
    
    size_t findMatching(char open, char close, size_t from) const override {
        if (from >= code_.length() || code_[from] != open) {
            return std::string::npos;
        }
        
        int depth = 1;
        size_t pos = from + 1;
        
        while (pos < code_.length() && depth > 0) {
            if (!isInStringOrComment(pos)) {
                if (code_[pos] == open) depth++;
                else if (code_[pos] == close) depth--;
            }
            if (depth == 0) return pos;
            pos++;
        }
        
        return std::string::npos;
    }
    
    std::string substring(size_t start, size_t length) const override {
        if (start >= code_.length()) return "";
        return code_.substr(start, std::min(length, code_.length() - start));
    }
    
    bool matches(const std::string& pattern, size_t at) const override {
        if (at + pattern.length() > code_.length()) return false;
        return code_.compare(at, pattern.length(), pattern) == 0;
    }
    
    // 状态访问
    StateManager* getStateManager() override { return stateManager_; }
    
    // 标记处理
    void markProcessed(size_t start, size_t end) override {
        processedRegions_.push_back({start, end});
        // 合并重叠区域
        mergeProcessedRegions();
    }
    
    bool isProcessed(size_t pos) const override {
        for (const auto& [start, end] : processedRegions_) {
            if (pos >= start && pos < end) return true;
        }
        return false;
    }
    
private:
    void updateContextState() const {
        // 简化的状态更新逻辑
        inString_ = false;
        inComment_ = false;
        
        for (size_t i = 0; i < position_ && i < code_.length(); i++) {
            if (!inComment_) {
                // 检查字符串
                if ((code_[i] == '"' || code_[i] == '\'') && 
                    (i == 0 || code_[i-1] != '\\')) {
                    if (!inString_) {
                        inString_ = true;
                        stringChar_ = code_[i];
                    } else if (code_[i] == stringChar_) {
                        inString_ = false;
                    }
                }
                
                // 检查注释
                if (!inString_ && i + 1 < code_.length()) {
                    if (code_[i] == '/' && code_[i+1] == '/') {
                        // 单行注释到行尾
                        size_t lineEnd = code_.find('\n', i);
                        if (position_ > i && position_ < lineEnd) {
                            inComment_ = true;
                        }
                        i = lineEnd;
                    } else if (code_[i] == '/' && code_[i+1] == '*') {
                        inComment_ = true;
                    }
                }
            } else {
                // 检查注释结束
                if (i + 1 < code_.length() && 
                    code_[i] == '*' && code_[i+1] == '/') {
                    inComment_ = false;
                    i++;
                }
            }
        }
    }
    
    bool isInStringOrComment(size_t pos) const {
        size_t oldPos = position_;
        position_ = pos;
        bool result = isInString() || isInComment();
        position_ = oldPos;
        return result;
    }
    
    void mergeProcessedRegions() {
        if (processedRegions_.size() < 2) return;
        
        std::sort(processedRegions_.begin(), processedRegions_.end());
        
        std::vector<std::pair<size_t, size_t>> merged;
        merged.push_back(processedRegions_[0]);
        
        for (size_t i = 1; i < processedRegions_.size(); i++) {
            auto& last = merged.back();
            const auto& current = processedRegions_[i];
            
            if (current.first <= last.second) {
                // 重叠，合并
                last.second = std::max(last.second, current.second);
            } else {
                // 不重叠，添加
                merged.push_back(current);
            }
        }
        
        processedRegions_ = std::move(merged);
    }
};

// 生成上下文实现
class GenerateContextImpl : public GenerateContext {
private:
    std::stringstream output_;
    std::stack<std::string> indentStack_;
    std::string currentIndent_;
    int uniqueCounter_ = 0;
    RuntimeBuilder* runtimeBuilder_;
    StateManager* stateManager_;
    std::vector<std::pair<std::string, std::string>> errors_;
    std::vector<std::pair<std::string, std::string>> warnings_;
    
public:
    GenerateContextImpl(RuntimeBuilder* runtime, StateManager* stateMgr)
        : runtimeBuilder_(runtime), stateManager_(stateMgr) {
        indentStack_.push("");
    }
    
    // 代码生成
    void emit(const std::string& code) override {
        output_ << code;
    }
    
    void emitLine(const std::string& code) override {
        output_ << code << "\n";
    }
    
    void emitIndented(const std::string& code) override {
        output_ << currentIndent_ << code << "\n";
    }
    
    // 缩进管理
    void pushIndent() override {
        currentIndent_ += "  ";
        indentStack_.push(currentIndent_);
    }
    
    void popIndent() override {
        if (indentStack_.size() > 1) {
            indentStack_.pop();
            currentIndent_ = indentStack_.top();
        }
    }
    
    std::string getIndent() const override {
        return currentIndent_;
    }
    
    // 变量生成
    std::string uniqueVar(const std::string& prefix) override {
        return prefix + "_" + std::to_string(++uniqueCounter_);
    }
    
    std::string uniqueLabel(const std::string& prefix) override {
        return prefix + "_" + std::to_string(++uniqueCounter_);
    }
    
    // 运行时注入
    RuntimeBuilder& runtime() override {
        return *runtimeBuilder_;
    }
    
    // 状态访问
    StateManager* getStateManager() override {
        return stateManager_;
    }
    
    // 错误报告
    void error(const std::string& msg, const ScanResult& result) override {
        errors_.push_back({msg, result.content});
    }
    
    void warning(const std::string& msg, const ScanResult& result) override {
        warnings_.push_back({msg, result.content});
    }
    
    // 获取生成的代码
    std::string getOutput() const { return output_.str(); }
    
    // 获取错误和警告
    const auto& getErrors() const { return errors_; }
    const auto& getWarnings() const { return warnings_; }
};

} // namespace cjmod
} // namespace chtl