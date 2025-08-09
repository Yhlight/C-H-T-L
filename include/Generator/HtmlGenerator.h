#ifndef CHTL_HTML_GENERATOR_H
#define CHTL_HTML_GENERATOR_H

#include "Generator/BasicGenerator.h"
#include <set>
#include <stack>
#include <map>

namespace chtl {

// HTML生成器 - 将CHTL AST转换为HTML
class HtmlGenerator : public BasicGenerator {
private:
    // HTML5空元素集合
    static const std::set<std::string> voidElements_;
    
    // 生成状态
    struct HtmlGeneratorState {
        bool inHead = false;
        bool inBody = false;
        bool hasDoctype = false;
        std::stack<std::string> elementStack;
    } htmlState_;
    
    // CSS样式收集
    std::vector<std::string> collectedStyles_;
    
    // JavaScript代码收集
    std::vector<std::string> collectedScripts_;
    
public:
    HtmlGenerator();
    virtual ~HtmlGenerator() = default;
    
    // 主生成方法
    bool generate(std::shared_ptr<Node> node) override;
    
    // 启用特性
    void setGenerateDoctype(bool generate) { htmlState_.hasDoctype = generate; }
    void setCollectStyles(bool collect);
    void setCollectScripts(bool collect);
    
protected:
    // 实现基类的纯虚函数
    void generateElement(std::shared_ptr<Node> node) override;
    void generateText(std::shared_ptr<Node> node) override;
    void generateComment(std::shared_ptr<Node> node) override;
    
    // 重写CHTL特有节点生成
    void generateTemplate(std::shared_ptr<Node> node) override;
    void generateCustom(std::shared_ptr<Node> node) override;
    void generateStyle(std::shared_ptr<Node> node) override;
    void generateConfig(std::shared_ptr<Node> node) override;
    void generateImport(std::shared_ptr<Node> node) override;
    void generateNamespace(std::shared_ptr<Node> node) override;
    void generateOperate(std::shared_ptr<Node> node) override;
    void generateOrigin(std::shared_ptr<Node> node) override;
    
private:
    // HTML特定生成方法
    void generateDoctype();
    void generateOpenTag(const std::string& tagName, const std::map<std::string, std::string>& attributes);
    void generateCloseTag(const std::string& tagName);
    void generateSelfClosingTag(const std::string& tagName, const std::map<std::string, std::string>& attributes);
    void generateAttributes(const std::map<std::string, std::string>& attributes);
    
    // 样式和脚本处理
    void collectStyle(const std::string& style);
    void collectScript(const std::string& script);
    void generateCollectedStyles();
    void generateCollectedScripts();
    
    // 工具方法
    bool isVoidElement(const std::string& tagName) const;
    bool needsClosingTag(const std::string& tagName) const;
    std::string sanitizeAttributeName(const std::string& name) const;
    std::string sanitizeAttributeValue(const std::string& value) const;
};

} // namespace chtl

#endif // CHTL_HTML_GENERATOR_H