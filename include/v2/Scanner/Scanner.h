#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>

namespace chtl::v2 {

/**
 * 代码段类型
 */
enum class SegmentType {
    CHTL,       // CHTL 代码
    CSS,        // CSS 代码
    JS,         // JavaScript 代码
    CHTL_JS,    // CHTL-JS 增强代码
    TEXT,       // 纯文本内容
    HTML        // HTML 代码
};

/**
 * 代码段
 */
struct CodeSegment {
    SegmentType type;
    std::string content;
    size_t startLine;
    size_t startColumn;
    size_t endLine;
    size_t endColumn;
    
    // 对于 CHTL-JS，记录原始位置信息用于拼接
    struct {
        size_t originalStart;
        size_t originalEnd;
        std::string placeholder;  // 替换占位符
    } chtlJsInfo;
    
    // 上下文信息
    struct {
        std::string parentElement;  // 父元素标签
        std::string elementId;      // 元素 ID
        std::string elementClass;   // 元素类名
        bool isGlobal;             // 是否全局代码
    } context;
};

/**
 * 扫描模式
 */
enum class ScanMode {
    LOOSE,      // 宽判 - 用于 JS 代码分块，提高并行处理能力
    STRICT,     // 严判 - 用于精确提取 CHTL-JS 语法
    HYBRID      // 混合 - 先宽判分块，再严判处理
};

/**
 * 扫描器接口
 */
class Scanner {
public:
    virtual ~Scanner() = default;
    
    /**
     * 扫描代码，返回代码段列表
     */
    virtual std::vector<CodeSegment> scan(const std::string& source, 
                                         SegmentType initialType = SegmentType::CHTL) = 0;
    
    /**
     * 设置扫描模式
     */
    virtual void setScanMode(ScanMode mode) = 0;
    
    /**
     * 获取错误信息
     */
    virtual std::vector<std::string> getErrors() const = 0;
};

/**
 * CHTL 扫描器
 */
class ChtlScanner : public Scanner {
public:
    ChtlScanner();
    ~ChtlScanner() override;
    
    std::vector<CodeSegment> scan(const std::string& source, 
                                 SegmentType initialType) override;
    
    void setScanMode(ScanMode mode) override;
    
    std::vector<std::string> getErrors() const override;
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

/**
 * JavaScript 扫描器
 * 专门处理 JS 代码的切割和 CHTL-JS 提取
 */
class JsScanner : public Scanner {
public:
    JsScanner();
    ~JsScanner() override;
    
    std::vector<CodeSegment> scan(const std::string& source, 
                                 SegmentType initialType) override;
    
    void setScanMode(ScanMode mode) override;
    
    std::vector<std::string> getErrors() const override;
    
    /**
     * 设置 CHTL-JS 表达式验证器
     */
    void setChtlJsValidator(std::function<bool(const std::string&)> validator);
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

/**
 * CSS 扫描器
 * 处理 CSS 代码的切割
 */
class CssScanner : public Scanner {
public:
    CssScanner();
    ~CssScanner() override;
    
    std::vector<CodeSegment> scan(const std::string& source, 
                                 SegmentType initialType) override;
    
    void setScanMode(ScanMode mode) override;
    
    std::vector<std::string> getErrors() const override;
    
private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};

/**
 * 扫描器工厂
 */
class ScannerFactory {
public:
    static std::unique_ptr<Scanner> createScanner(SegmentType type);
    
    static std::unique_ptr<ChtlScanner> createChtlScanner() {
        return std::make_unique<ChtlScanner>();
    }
    
    static std::unique_ptr<JsScanner> createJsScanner() {
        return std::make_unique<JsScanner>();
    }
    
    static std::unique_ptr<CssScanner> createCssScanner() {
        return std::make_unique<CssScanner>();
    }
};

/**
 * 代码合并器
 * 将切割的代码段重新组合
 */
class CodeMerger {
public:
    /**
     * 合并代码段
     */
    static std::string merge(const std::vector<CodeSegment>& segments);
    
    /**
     * 合并 JS 代码段，处理 CHTL-JS 占位符
     */
    static std::string mergeJs(const std::vector<CodeSegment>& segments,
                              const std::map<std::string, std::string>& chtlJsReplacements);
    
    /**
     * 生成源映射
     */
    static std::string generateSourceMap(const std::vector<CodeSegment>& segments);
};

} // namespace chtl::v2