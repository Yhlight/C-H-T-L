#ifndef CHTL_CJMOD_CONTEXT_IMPL_H
#define CHTL_CJMOD_CONTEXT_IMPL_H

#include "CJmod/CJmodCore.h"
#include <sstream>
#include <vector>

namespace chtl {
namespace cjmod {

// 扫描上下文实现
class ScanContextImpl : public ScanContext {
private:
    const std::string& code_;
    size_t position_;
    StateManager* stateManager_;
    
    // 上下文状态
    mutable bool inString_ = false;
    mutable bool inComment_ = false;
    mutable bool inRegex_ = false;
    mutable int braceDepth_ = 0;
    mutable int parenDepth_ = 0;
    mutable int bracketDepth_ = 0;
    
    // 已处理区域
    std::vector<std::pair<size_t, size_t>> processedRegions_;
    
    void updateContextState();
    
public:
    ScanContextImpl(const std::string& code, size_t position, StateManager* stateMgr);
    
    // ScanContext 接口实现
    const std::string& getCode() const override;
    size_t getPosition() const override;
    size_t getLength() const override;
    
    bool isInString() const override;
    bool isInComment() const override;
    bool isInRegex() const override;
    int getBraceDepth() const override;
    int getParenDepth() const override;
    int getBracketDepth() const override;
    
    size_t findNext(const std::string& str, size_t from = 0) const override;
    size_t findMatching(char open, char close, size_t from) const override;
    std::string substring(size_t start, size_t length) const override;
    bool matches(const std::string& pattern, size_t at) const override;
    
    StateManager* getStateManager() override;
    
    void markProcessed(size_t start, size_t end) override;
    bool isProcessed(size_t pos) const override;
};

// 生成上下文实现
class GenerateContextImpl : public GenerateContext {
private:
    std::stringstream output_;
    RuntimeBuilder* runtime_;
    StateManager* stateManager_;
    int indentLevel_;
    int varCounter_;
    int labelCounter_;
    
    std::vector<std::pair<std::string, ScanResult>> errors_;
    std::vector<std::pair<std::string, ScanResult>> warnings_;
    
public:
    GenerateContextImpl(RuntimeBuilder* runtime, StateManager* stateMgr);
    
    // GenerateContext 接口实现
    void emit(const std::string& code) override;
    void emitLine(const std::string& code) override;
    void emitIndented(const std::string& code) override;
    
    void pushIndent() override;
    void popIndent() override;
    std::string getIndent() const override;
    
    std::string uniqueVar(const std::string& prefix = "var") override;
    std::string uniqueLabel(const std::string& prefix = "label") override;
    
    RuntimeBuilder& runtime() override;
    StateManager* getStateManager() override;
    
    void error(const std::string& msg, const ScanResult& result) override;
    void warning(const std::string& msg, const ScanResult& result) override;
    
    // 获取结果
    std::string getOutput() const;
    const std::vector<std::pair<std::string, ScanResult>>& getErrors() const;
    const std::vector<std::pair<std::string, ScanResult>>& getWarnings() const;
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_CONTEXT_IMPL_H