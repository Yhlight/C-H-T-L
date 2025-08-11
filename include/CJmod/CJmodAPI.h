#ifndef CHTL_CJMOD_API_H
#define CHTL_CJMOD_API_H

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <regex>

namespace chtl {
namespace cjmod {

// 前向声明
class ScanContext;
class GenerateContext;

// 扫描切割点
struct CutPoint {
    size_t start;
    size_t end;
    std::string type;      // 切割类型标识
    std::string content;   // 切割的内容
};

// 语法规则定义
class SyntaxRule {
public:
    virtual ~SyntaxRule() = default;
    
    // 规则名称
    virtual std::string getName() const = 0;
    
    // 优先级（数字越大越先执行）
    virtual int getPriority() const = 0;
    
    // 扫描阶段：识别并切割代码片段
    virtual std::vector<CutPoint> scan(const std::string& code, ScanContext* ctx) = 0;
    
    // 生成阶段：将切割的片段转换为 JavaScript
    virtual std::string generate(const CutPoint& cut, GenerateContext* ctx) = 0;
    
    // 可选：验证切割点是否有效
    virtual bool validate(const CutPoint& cut) const { return true; }
};

// 扫描上下文 - 提供扫描时的辅助功能
class ScanContext {
public:
    virtual ~ScanContext() = default;
    
    // 获取当前位置的上下文信息
    virtual bool isInString() const = 0;
    virtual bool isInComment() const = 0;
    virtual int getBraceDepth() const = 0;
    virtual int getParenDepth() const = 0;
    
    // 查找匹配的括号/引号
    virtual size_t findMatchingBrace(size_t pos) const = 0;
    virtual size_t findMatchingParen(size_t pos) const = 0;
    virtual size_t findMatchingQuote(size_t pos, char quote) const = 0;
    
    // 获取行列信息
    virtual int getLine(size_t pos) const = 0;
    virtual int getColumn(size_t pos) const = 0;
    
    // 标记已处理的区域（避免重复处理）
    virtual void markProcessed(size_t start, size_t end) = 0;
    virtual bool isProcessed(size_t pos) const = 0;
};

// 生成上下文 - 提供代码生成时的辅助功能
class GenerateContext {
public:
    virtual ~GenerateContext() = default;
    
    // 生成唯一的变量名
    virtual std::string generateUniqueVar(const std::string& prefix = "var") = 0;
    
    // 添加运行时代码（只会添加一次）
    virtual void addRuntimeOnce(const std::string& name, const std::string& code) = 0;
    
    // 添加导入
    virtual void addImport(const std::string& module, const std::string& name = "") = 0;
    
    // 获取当前缩进
    virtual std::string getCurrentIndent() const = 0;
    
    // 错误报告
    virtual void reportError(const std::string& message, const CutPoint& cut) = 0;
    virtual void reportWarning(const std::string& message, const CutPoint& cut) = 0;
};

// CJmod 模块接口
class ICJmodModule {
public:
    virtual ~ICJmodModule() = default;
    
    // 模块信息
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getAuthor() const = 0;
    
    // 获取所有语法规则
    virtual std::vector<std::unique_ptr<SyntaxRule>> createRules() = 0;
    
    // 模块初始化（可选）
    virtual void initialize() {}
    
    // 模块清理（可选）
    virtual void cleanup() {}
    
    // 依赖检查（可选）
    virtual bool checkDependencies() { return true; }
};

// 辅助类：基于正则的简单规则
class RegexRule : public SyntaxRule {
protected:
    std::string name_;
    std::regex pattern_;
    int priority_;
    std::string type_;
    
public:
    RegexRule(const std::string& name, 
              const std::string& pattern, 
              int priority = 100,
              const std::string& type = "")
        : name_(name)
        , pattern_(pattern)
        , priority_(priority)
        , type_(type.empty() ? name : type) {}
    
    std::string getName() const override { return name_; }
    int getPriority() const override { return priority_; }
    
    std::vector<CutPoint> scan(const std::string& code, ScanContext* ctx) override {
        std::vector<CutPoint> cuts;
        std::sregex_iterator it(code.begin(), code.end(), pattern_);
        std::sregex_iterator end;
        
        for (; it != end; ++it) {
            size_t start = it->position();
            size_t length = it->length();
            
            // 检查是否在字符串或注释中
            if (ctx->isInString() || ctx->isInComment()) {
                continue;
            }
            
            // 检查是否已处理
            if (ctx->isProcessed(start)) {
                continue;
            }
            
            CutPoint cut;
            cut.start = start;
            cut.end = start + length;
            cut.type = type_;
            cut.content = it->str();
            
            if (validate(cut)) {
                cuts.push_back(cut);
                ctx->markProcessed(cut.start, cut.end);
            }
        }
        
        return cuts;
    }
};

// 辅助类：复杂语法规则基类
class ComplexRule : public SyntaxRule {
protected:
    std::string name_;
    int priority_;
    
    // 辅助方法：查找特定模式
    size_t findPattern(const std::string& code, size_t start, const std::string& pattern) {
        return code.find(pattern, start);
    }
    
    // 辅助方法：提取标识符
    std::string extractIdentifier(const std::string& code, size_t pos) {
        size_t start = pos;
        while (start < code.length() && 
               (std::isalnum(code[start]) || code[start] == '_')) {
            start++;
        }
        return code.substr(pos, start - pos);
    }
    
    // 辅助方法：跳过空白
    size_t skipWhitespace(const std::string& code, size_t pos) {
        while (pos < code.length() && std::isspace(code[pos])) {
            pos++;
        }
        return pos;
    }
    
public:
    ComplexRule(const std::string& name, int priority = 100)
        : name_(name), priority_(priority) {}
    
    std::string getName() const override { return name_; }
    int getPriority() const override { return priority_; }
};

// 导出宏 - 用于创建模块
#define CJMOD_EXPORT extern "C"

// 模块创建函数类型
using CreateModuleFunc = ICJmodModule* (*)();
using DestroyModuleFunc = void (*)(ICJmodModule*);

// 标准导出函数
#define CJMOD_MODULE(ModuleClass) \
    CJMOD_EXPORT ICJmodModule* cjmod_create() { \
        return new ModuleClass(); \
    } \
    CJMOD_EXPORT void cjmod_destroy(ICJmodModule* module) { \
        delete module; \
    }

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_API_H