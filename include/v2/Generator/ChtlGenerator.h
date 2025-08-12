#pragma once

#include "v2/Node/Node.h"
#include "v2/Import/ImportSystem.h"
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <sstream>

namespace chtl::v2 {

/**
 * 代码收集器
 */
class CodeCollector {
public:
    void append(const std::string& code) {
        buffer_ << code;
    }
    
    void appendLine(const std::string& code) {
        buffer_ << code << "\n";
    }
    
    void indent() { indentLevel_++; }
    void dedent() { if (indentLevel_ > 0) indentLevel_--; }
    
    void appendIndent() {
        for (int i = 0; i < indentLevel_; ++i) {
            buffer_ << "  ";
        }
    }
    
    std::string getCode() const {
        return buffer_.str();
    }
    
    void clear() {
        buffer_.str("");
        buffer_.clear();
    }
    
private:
    std::stringstream buffer_;
    int indentLevel_ = 0;
};

/**
 * 生成选项
 */
struct GeneratorOptions {
    bool minify = false;              // 是否压缩输出
    bool includeSourceMap = false;    // 是否包含源映射
    bool inlineStyles = false;        // 是否内联样式
    bool inlineScripts = false;       // 是否内联脚本
    std::string cssFileName = "styles.css";
    std::string jsFileName = "script.js";
};

/**
 * 生成结果
 */
struct GenerateResult {
    bool success = false;
    std::string html;
    std::string css;
    std::string javascript;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // 文件映射
    std::map<std::string, std::string> files;
};

/**
 * 导入项
 */
struct ImportItem {
    ImportType type;
    std::string path;
    std::string alias;
};

/**
 * CHTL 代码生成器
 * 将 AST 转换为 HTML/CSS/JavaScript
 */
class ChtlGenerator : public NodeVisitor {
public:
    ChtlGenerator();
    ~ChtlGenerator();
    
    /**
     * 生成代码
     */
    GenerateResult generate(std::shared_ptr<Node> ast);
    
    /**
     * 设置选项
     */
    void setOptions(const GeneratorOptions& options);
    
    // 访问者方法
    void visitDocument(Document* node) override;
    void visitElement(Element* node) override;
    void visitText(Text* node) override;
    void visitStyle(Style* node) override;
    void visitScript(Script* node) override;
    void visitTemplate(Template* node) override;
    void visitReference(Reference* node) override;
    
private:
    /**
     * 生成元素开始标签
     */
    void generateElementStart(Element* node);
    
    /**
     * 生成元素结束标签
     */
    void generateElementEnd(Element* node);
    
    /**
     * 生成元素属性
     */
    void generateAttributes(Element* node);
    
    /**
     * 处理局部样式
     */
    void processLocalStyle(Element* node);
    
    /**
     * 处理选择器
     */
    void processSelector(const std::string& selector, 
                        const std::string& content,
                        Element* node,
                        std::vector<std::string>& autoClasses,
                        std::string& autoId,
                        std::string& globalStyles);
    
    /**
     * 查找匹配的大括号
     */
    size_t findMatchingBrace(const std::string& str, size_t start);
    
    /**
     * 去除字符串两端空白
     */
    std::string trim(const std::string& str);
    
    /**
     * 生成唯一类名
     */
    std::string generateUniqueClass();
    
    /**
     * 展开模板引用
     */
    void expandTemplateReference(Reference* node);
    
    /**
     * 处理模板参数
     */
    std::string processTemplateContent(const std::string& content, 
                                     const std::map<std::string, std::string>& params);
    
    /**
     * 收集模板定义
     */
    void collectTemplates(Node* node);
    
    /**
     * 添加错误
     */
    void addError(const std::string& message);
    
    /**
     * 添加警告
     */
    void addWarning(const std::string& message);
    
private:
    // 代码收集器
    CodeCollector htmlCollector_;
    CodeCollector cssCollector_;
    CodeCollector jsCollector_;
    
    // 模板存储
    std::map<std::string, Template*> templates_;
    
    // 导入信息
    std::vector<ImportItem> imports_;
    
    // 选项
    GeneratorOptions options_;
    
    // 结果
    GenerateResult result_;
    
    // 当前模板参数
    std::map<std::string, std::string> currentParams_;
    
    // 唯一ID计数器
    int uniqueIdCounter_ = 0;
    
    // 当前是否在模板内
    bool inTemplate_ = false;
};

} // namespace chtl::v2