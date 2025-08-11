#ifndef CHTL_CJMOD_CONTEXT_IMPL_H
#define CHTL_CJMOD_CONTEXT_IMPL_H

#include "CJmod/CJmodCore.h"
#include <unordered_set>

namespace chtl {
namespace cjmod {

// ScanContext 的具体实现
class ScanContextImpl : public ScanContext {
public:
    ScanContextImpl(const std::string& code, size_t initialPosition = 0);
    
    // 实现接口方法
    bool isInString() const override;
    bool isInComment() const override;
    bool isInRegex() const override;
    int getBraceDepth() const override;
    int getParenDepth() const override;
    int getBracketDepth() const override;
    
    size_t findMatchingChar(size_t pos, char openChar, char closeChar) const override;
    void markProcessed(size_t start, size_t end) override;
    bool isProcessed(size_t pos) const override;
    
    // 其他辅助方法
    bool isInStringOrComment(size_t pos) const;
    std::string getCurrentLine(size_t pos) const;
    size_t getLineNumber(size_t pos) const;
    size_t getColumnNumber(size_t pos) const;
    
    // 设置和获取当前位置
    void setPosition(size_t pos) { position_ = pos; }
    size_t getPosition() const { return position_; }
    
private:
    void updateContextAt(size_t pos) const;
    
    const std::string& code_;
    mutable size_t position_;
    mutable bool inString_ = false;
    mutable bool inComment_ = false;
    mutable bool inRegex_ = false;
    mutable char stringChar_ = 0;
    mutable int braceDepth_ = 0;
    mutable int parenDepth_ = 0;
    mutable int bracketDepth_ = 0;
    std::unordered_set<size_t> processedPositions_;
    
    // 缓存行信息
    mutable std::vector<size_t> lineStarts_;
    mutable bool linesCached_ = false;
    void cacheLineStarts() const;
};

// GenerateContext 的具体实现  
class GenerateContextImpl : public GenerateContext {
public:
    GenerateContextImpl();
    
    // 实现接口方法
    void emit(const std::string& code) override;
    void emitLine(const std::string& line = "") override;
    void indent() override;
    void dedent() override;
    std::string uniqueVar(const std::string& prefix = "tmp") override;
    void injectRuntime(const std::string& name, const std::string& code) override;
    void error(const std::string& message) override;
    void warning(const std::string& message) override;
    
    // 获取生成的代码
    std::string getGeneratedCode() const { return output_; }
    const std::unordered_map<std::string, std::string>& getRuntimeInjections() const {
        return runtimeInjections_;
    }
    const std::vector<std::string>& getErrors() const { return errors_; }
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    
    // 重置状态
    void reset();
    
private:
    std::string output_;
    int indentLevel_ = 0;
    int varCounter_ = 0;
    std::unordered_map<std::string, std::string> runtimeInjections_;
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    std::string getIndentString() const;
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_CONTEXT_IMPL_H