#include "CodeGenerator.h"
#include <algorithm>
#include <cctype>

namespace CHTL {

CodeGenerator::CodeGenerator(SymbolTable* symbolTable) 
    : symbolTable_(symbolTable), currentStream_(&htmlStream_) {}

void CodeGenerator::generate(const std::shared_ptr<ASTNode>& ast) {
    if (!ast) return;
    
    // 设置当前流为HTML
    currentStream_ = &htmlStream_;
    
    // 访问AST节点
    ast->accept(this);
}

void CodeGenerator::visitElement(ElementNode* node) {
    if (!node) return;
    
    // 生成开始标签
    *currentStream_ << getIndent() << "<" << node->getTagName();
    
    // 生成属性
    generateAttributes(node);
    
    // 检查是否是空元素
    if (isVoidElement(node->getTagName())) {
        *currentStream_ << " />";
        if (config_.prettify) *currentStream_ << "\n";
        return;
    }
    
    *currentStream_ << ">";
    if (config_.prettify && !node->getChildren().empty()) {
        *currentStream_ << "\n";
        indent();
    }
    
    // 生成子节点
    for (const auto& child : node->getChildren()) {
        if (child) {
            child->accept(this);
        }
    }
    
    // 生成结束标签
    if (config_.prettify && !node->getChildren().empty()) {
        dedent();
        *currentStream_ << getIndent();
    }
    *currentStream_ << "</" << node->getTagName() << ">";
    if (config_.prettify) *currentStream_ << "\n";
}

void CodeGenerator::visitText(TextNode* node) {
    if (!node) return;
    
    std::string text = escapeHTML(node->getText());
    
    if (config_.prettify) {
        *currentStream_ << getIndent() << text << "\n";
    } else {
        *currentStream_ << text;
    }
}

void CodeGenerator::visitStyleBlock(StyleBlockNode* node) {
    if (!node) return;
    
    // 生成内联样式
    auto inlineStyles = node->getInlineStyles();
    if (!inlineStyles.empty()) {
        generateInlineStyles(inlineStyles);
    }
    
    // 生成类样式
    for (const auto& className : node->getClassSelectors()) {
        generateClassStyles(className, node);
    }
    
    // 生成ID样式
    for (const auto& id : node->getIdSelectors()) {
        // TODO: 生成ID样式
    }
}

void CodeGenerator::visitScriptBlock(ScriptBlockNode* node) {
    if (!node) return;
    
    // 切换到JavaScript流
    auto prevStream = currentStream_;
    currentStream_ = &jsStream_;
    
    // 如果是CHTL JS，添加辅助函数
    if (node->isCHTLJS()) {
        generateCHTLJSHelpers();
    }
    
    // 生成脚本代码
    *currentStream_ << node->getCode();
    if (config_.prettify) *currentStream_ << "\n\n";
    
    // 恢复流
    currentStream_ = prevStream;
}

void CodeGenerator::visitTemplate(TemplateNode* node) {
    if (!node) return;
    
    // 展开模板
    expandTemplate(node);
}

void CodeGenerator::visitCustom(CustomNode* node) {
    if (!node) return;
    
    // 展开自定义
    expandCustom(node);
}

void CodeGenerator::indent() {
    indentLevel_++;
}

void CodeGenerator::dedent() {
    if (indentLevel_ > 0) {
        indentLevel_--;
    }
}

std::string CodeGenerator::getIndent() const {
    if (!config_.prettify) return "";
    
    std::string indent;
    for (int i = 0; i < indentLevel_; i++) {
        for (int j = 0; j < config_.indentSize; j++) {
            indent += config_.indentChar;
        }
    }
    return indent;
}

void CodeGenerator::generateElement(ElementNode* node) {
    visitElement(node);
}

void CodeGenerator::generateAttributes(ElementNode* node) {
    // 生成ID
    if (!node->getId().empty()) {
        *currentStream_ << " id=\"" << node->getId() << "\"";
    }
    
    // 生成类
    auto classes = node->getClasses();
    if (!classes.empty()) {
        *currentStream_ << " class=\"";
        for (size_t i = 0; i < classes.size(); i++) {
            if (i > 0) *currentStream_ << " ";
            *currentStream_ << classes[i];
        }
        *currentStream_ << "\"";
    }
    
    // 生成其他属性
    // TODO: 从node的attributes_中获取并生成
}

void CodeGenerator::generateChildren(const std::shared_ptr<ASTNode>& node) {
    if (!node) return;
    
    for (const auto& child : node->getChildren()) {
        if (child) {
            child->accept(this);
        }
    }
}

void CodeGenerator::generateStyleBlock(StyleBlockNode* node) {
    visitStyleBlock(node);
}

void CodeGenerator::generateInlineStyles(const std::unordered_map<std::string, std::string>& styles) {
    if (styles.empty()) return;
    
    // 这些样式会作为style属性添加到元素上
    // 实际实现需要在生成元素时处理
}

void CodeGenerator::generateClassStyles(const std::string& className, StyleBlockNode* node) {
    // 切换到CSS流
    auto prevStream = currentStream_;
    currentStream_ = &cssStream_;
    
    // 生成唯一的类名（如果需要）
    std::string uniqueClassName = className;
    if (className.empty()) {
        uniqueClassName = generateUniqueClassName();
    }
    
    // 记录已生成的类名
    generatedClasses_.insert(uniqueClassName);
    
    // 生成CSS规则
    *currentStream_ << "." << uniqueClassName << " {";
    if (config_.prettify) {
        *currentStream_ << "\n";
        indent();
    }
    
    // TODO: 生成具体的CSS属性
    
    if (config_.prettify) {
        dedent();
        *currentStream_ << "}";
    } else {
        *currentStream_ << "}";
    }
    if (config_.prettify) *currentStream_ << "\n\n";
    
    // 恢复流
    currentStream_ = prevStream;
}

std::string CodeGenerator::generateUniqueClassName() {
    std::string className = "chtl-" + std::to_string(classNameCounter_++);
    while (generatedClasses_.find(className) != generatedClasses_.end()) {
        className = "chtl-" + std::to_string(classNameCounter_++);
    }
    return className;
}

void CodeGenerator::generateScriptBlock(ScriptBlockNode* node) {
    visitScriptBlock(node);
}

void CodeGenerator::generateCHTLJSHelpers() {
    // 只生成一次辅助函数
    static bool helpersGenerated = false;
    if (helpersGenerated) return;
    helpersGenerated = true;
    
    *currentStream_ << R"(
// CHTL JavaScript 辅助函数
(function() {
    // 事件委托辅助函数
    if (!Element.prototype.delegate) {
        Element.prototype.delegate = function(config) {
            const target = config.target;
            const targets = Array.isArray(target) ? target : [target];
            
            for (const event in config) {
                if (event === 'target') continue;
                
                this.addEventListener(event, function(e) {
                    for (const t of targets) {
                        const element = e.target.closest(t);
                        if (element) {
                            config[event].call(element, e);
                            break;
                        }
                    }
                });
            }
        };
    }
    
    // 动画辅助函数
    window.animate = function(config) {
        // TODO: 实现动画函数
    };
})();

)";
}

void CodeGenerator::expandTemplate(TemplateNode* node) {
    // 从符号表中查找模板定义
    SymbolType symbolType;
    switch (node->getTemplateType()) {
        case TemplateNode::TemplateType::STYLE:
            symbolType = SymbolType::TEMPLATE_STYLE;
            break;
        case TemplateNode::TemplateType::ELEMENT:
            symbolType = SymbolType::TEMPLATE_ELEMENT;
            break;
        case TemplateNode::TemplateType::VAR:
            symbolType = SymbolType::TEMPLATE_VAR;
            break;
    }
    
    auto symbol = symbolTable_->lookupSymbol(node->getName(), symbolType);
    if (!symbol) {
        // 错误：未定义的模板
        return;
    }
    
    // TODO: 展开模板内容
}

void CodeGenerator::expandCustom(CustomNode* node) {
    // 从符号表中查找自定义定义
    SymbolType symbolType;
    switch (node->getCustomType()) {
        case CustomNode::CustomType::STYLE:
            symbolType = SymbolType::CUSTOM_STYLE;
            break;
        case CustomNode::CustomType::ELEMENT:
            symbolType = SymbolType::CUSTOM_ELEMENT;
            break;
        case CustomNode::CustomType::VAR:
            symbolType = SymbolType::CUSTOM_VAR;
            break;
    }
    
    auto symbol = symbolTable_->lookupSymbol(node->getName(), symbolType);
    if (!symbol) {
        // 错误：未定义的自定义
        return;
    }
    
    // TODO: 展开自定义内容
}

std::string CodeGenerator::escapeHTML(const std::string& text) {
    std::string escaped;
    for (char c : text) {
        switch (c) {
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '&': escaped += "&amp;"; break;
            case '"': escaped += "&quot;"; break;
            case '\'': escaped += "&#39;"; break;
            default: escaped += c; break;
        }
    }
    return escaped;
}

std::string CodeGenerator::escapeJS(const std::string& text) {
    std::string escaped;
    for (char c : text) {
        switch (c) {
            case '"': escaped += "\\\""; break;
            case '\'': escaped += "\\'"; break;
            case '\\': escaped += "\\\\"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default: escaped += c; break;
        }
    }
    return escaped;
}

bool CodeGenerator::isVoidElement(const std::string& tagName) {
    static const std::unordered_set<std::string> voidElements = {
        "area", "base", "br", "col", "embed", "hr", "img", "input",
        "link", "meta", "param", "source", "track", "wbr"
    };
    
    std::string lowerTag = tagName;
    std::transform(lowerTag.begin(), lowerTag.end(), lowerTag.begin(), ::tolower);
    
    return voidElements.find(lowerTag) != voidElements.end();
}

} // namespace CHTL