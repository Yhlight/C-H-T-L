#include "Generator/HtmlGenerator.h"
#include "Node/Node.h"
#include "Node/Comment.h"
#include <algorithm>

namespace chtl {

// HTML5空元素集合
const std::set<std::string> HtmlGenerator::voidElements_ = {
    "area", "base", "br", "col", "embed", "hr", "img", "input",
    "link", "meta", "param", "source", "track", "wbr"
};

HtmlGenerator::HtmlGenerator() : BasicGenerator() {
}

bool HtmlGenerator::generate(std::shared_ptr<Node> node) {
    if (!node) {
        reportError("Cannot generate from null node");
        return false;
    }
    
    beginGeneration();
    
    // 如果需要生成DOCTYPE
    if (htmlState_.hasDoctype && node->getType() == NodeType::ELEMENT) {
        auto element = std::dynamic_pointer_cast<Element>(node);
        if (element && element->getTagName() == "html") {
            generateDoctype();
        }
    }
    
    // 生成节点
    generateNode(node);
    
    // 如果收集了样式和脚本，在适当位置输出
    if (!collectedStyles_.empty()) {
        generateCollectedStyles();
    }
    if (!collectedScripts_.empty()) {
        generateCollectedScripts();
    }
    
    endGeneration();
    return !hasErrors();
}

void HtmlGenerator::generateElement(std::shared_ptr<Node> node) {
    auto element = std::dynamic_pointer_cast<Element>(node);
    if (!element) {
        return;
    }
    
    const std::string& tagName = element->getTagName();
    
    // 转换属性格式
    std::map<std::string, std::string> attributes;
    for (const auto& [name, value] : element->getAttributes()) {
        // 将AttributeValue转换为字符串
        if (std::holds_alternative<std::string>(value)) {
            attributes[name] = std::get<std::string>(value);
        } else if (std::holds_alternative<int>(value)) {
            attributes[name] = std::to_string(std::get<int>(value));
        } else if (std::holds_alternative<double>(value)) {
            attributes[name] = std::to_string(std::get<double>(value));
        } else if (std::holds_alternative<bool>(value)) {
            attributes[name] = std::get<bool>(value) ? "true" : "false";
        }
    }
    
    // 处理空元素
    if (isVoidElement(tagName)) {
        generateSelfClosingTag(tagName, attributes);
        return;
    }
    
    // 生成开始标签
    generateOpenTag(tagName, attributes);
    
    // 生成子节点
    for (const auto& child : element->getChildren()) {
        generateNode(child);
    }
    
    // 生成结束标签
    generateCloseTag(tagName);
}

void HtmlGenerator::generateText(std::shared_ptr<Node> node) {
    auto textNode = std::dynamic_pointer_cast<Text>(node);
    if (!textNode) {
        return;
    }
    
    // 输出转义后的文本
    write(escapeHtml(textNode->getData()));
}

void HtmlGenerator::generateComment(std::shared_ptr<Node> node) {
    auto comment = std::dynamic_pointer_cast<Comment>(node);
    if (!comment) {
        return;
    }
    
    // CHTL的 -- 注释生成为HTML注释
    // CHTL: -- 这是注释
    // HTML: <!-- 这是注释 -->
    write("<!-- ");
    write(comment->getContent());
    write(" -->");
    
    // 如果配置了格式化输出，添加换行
    if (config_.prettyPrint && !config_.minify) {
        writeLine();
    }
}

void HtmlGenerator::generateDoctype() {
    writeLine("<!DOCTYPE html>");
}

void HtmlGenerator::generateOpenTag(const std::string& tagName, 
                                   const std::map<std::string, std::string>& attributes) {
    writeIndent();
    write("<" + tagName);
    generateAttributes(attributes);
    write(">");
    
    if (config_.prettyPrint && !config_.minify) {
        writeLine();
        increaseIndent();
    }
    
    htmlState_.elementStack.push(tagName);
}

void HtmlGenerator::generateCloseTag(const std::string& tagName) {
    if (config_.prettyPrint && !config_.minify) {
        decreaseIndent();
        writeIndent();
    }
    
    write("</" + tagName + ">");
    
    if (config_.prettyPrint && !config_.minify) {
        writeLine();
    }
    
    if (!htmlState_.elementStack.empty()) {
        htmlState_.elementStack.pop();
    }
}

void HtmlGenerator::generateSelfClosingTag(const std::string& tagName,
                                          const std::map<std::string, std::string>& attributes) {
    writeIndent();
    write("<" + tagName);
    generateAttributes(attributes);
    write(" />");
    
    if (config_.prettyPrint && !config_.minify) {
        writeLine();
    }
}

void HtmlGenerator::generateAttributes(const std::map<std::string, std::string>& attributes) {
    for (const auto& [name, value] : attributes) {
        write(" ");
        write(sanitizeAttributeName(name));
        write("=\"");
        write(sanitizeAttributeValue(value));
        write("\"");
    }
}

bool HtmlGenerator::isVoidElement(const std::string& tagName) const {
    return voidElements_.find(tagName) != voidElements_.end();
}

bool HtmlGenerator::needsClosingTag(const std::string& tagName) const {
    return !isVoidElement(tagName);
}

std::string HtmlGenerator::sanitizeAttributeName(const std::string& name) const {
    // HTML属性名转换：确保是有效的HTML属性名
    std::string result = name;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string HtmlGenerator::sanitizeAttributeValue(const std::string& value) const {
    // 转义属性值中的特殊字符
    std::string result;
    result.reserve(value.length() * 1.2);
    
    for (char c : value) {
        switch (c) {
            case '"':
                result += "&quot;";
                break;
            case '&':
                result += "&amp;";
                break;
            case '<':
                result += "&lt;";
                break;
            case '>':
                result += "&gt;";
                break;
            default:
                result += c;
                break;
        }
    }
    
    return result;
}

// 占位实现
void HtmlGenerator::generateTemplate(std::shared_ptr<Node> node) {
    reportWarning("Template node generation not yet implemented");
    (void)node;
}

void HtmlGenerator::generateCustom(std::shared_ptr<Node> node) {
    reportWarning("Custom node generation not yet implemented");
    (void)node;
}

void HtmlGenerator::generateStyle(std::shared_ptr<Node> node) {
    reportWarning("Style node generation not yet implemented");
    (void)node;
}

void HtmlGenerator::generateConfig(std::shared_ptr<Node> node) {
    // Config节点不应该出现在HTML生成中
    reportWarning("Config node should not appear in HTML generation");
    (void)node;
}

void HtmlGenerator::generateImport(std::shared_ptr<Node> node) {
    // Import节点不应该出现在HTML生成中
    reportWarning("Import node should not appear in HTML generation");
    (void)node;
}

void HtmlGenerator::generateNamespace(std::shared_ptr<Node> node) {
    // Namespace节点不应该出现在HTML生成中
    reportWarning("Namespace node should not appear in HTML generation");
    (void)node;
}

void HtmlGenerator::generateOperate(std::shared_ptr<Node> node) {
    reportWarning("Operate node generation not yet implemented");
    (void)node;
}

void HtmlGenerator::generateOrigin(std::shared_ptr<Node> node) {
    reportWarning("Origin node generation not yet implemented");
    (void)node;
}

void HtmlGenerator::setCollectStyles(bool collect) {
    (void)collect;
    // TODO: 实现样式收集功能
}

void HtmlGenerator::setCollectScripts(bool collect) {
    (void)collect;
    // TODO: 实现脚本收集功能
}

void HtmlGenerator::collectStyle(const std::string& style) {
    collectedStyles_.push_back(style);
}

void HtmlGenerator::collectScript(const std::string& script) {
    collectedScripts_.push_back(script);
}

void HtmlGenerator::generateCollectedStyles() {
    // TODO: 实现收集的样式输出
}

void HtmlGenerator::generateCollectedScripts() {
    // TODO: 实现收集的脚本输出
}

} // namespace chtl