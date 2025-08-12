#include "ChtlVisitor.h"
#include <sstream>

namespace CHTL {

ChtlVisitor::ChtlVisitor(SymbolTable* symbolTable)
    : symbolTable_(symbolTable) {
    // 创建根节点
    rootNode_ = std::make_shared<ElementNode>("document");
    currentNode_ = rootNode_;
    nodeStack_.push(rootNode_);
}

std::any ChtlVisitor::visitProgram(CHTLParser::ProgramContext* ctx) {
    // 访问所有语句
    for (auto statement : ctx->statement()) {
        visit(statement);
    }
    return rootNode_;
}

std::any ChtlVisitor::visitElement(CHTLParser::ElementContext* ctx) {
    // 获取元素名
    std::string tagName = ctx->elementName()->getText();
    
    // 创建元素节点
    auto elementNode = createElementNode(tagName);
    
    // 设置位置信息
    elementNode->setLocation(
        ctx->getStart()->getLine(),
        ctx->getStart()->getCharPositionInLine(),
        ctx->getStop()->getLine(),
        ctx->getStop()->getCharPositionInLine()
    );
    
    // 添加到当前节点
    currentNode_->addChild(elementNode);
    
    // 如果有元素体，处理子内容
    if (ctx->elementBody()) {
        // 压栈当前节点
        nodeStack_.push(currentNode_);
        currentNode_ = elementNode;
        
        // 处理属性和内容
        processElementAttributes(elementNode, ctx->elementBody());
        
        // 访问元素体中的内容
        for (auto content : ctx->elementBody()->elementContent()) {
            visit(content);
        }
        
        // 出栈
        currentNode_ = nodeStack_.top();
        nodeStack_.pop();
    }
    
    return elementNode;
}

std::any ChtlVisitor::visitAttribute(CHTLParser::AttributeContext* ctx) {
    // 属性在processElementAttributes中处理
    return nullptr;
}

std::any ChtlVisitor::visitTextNode(CHTLParser::TextNodeContext* ctx) {
    if (ctx->stringLiteral()) {
        std::string text = ctx->stringLiteral()->getText();
        // 去除引号
        if (text.size() >= 2 && ((text[0] == '"' && text[text.size()-1] == '"') ||
                                  (text[0] == '\'' && text[text.size()-1] == '\''))) {
            text = text.substr(1, text.size() - 2);
        }
        
        auto textNode = createTextNode(text);
        textNode->setLocation(
            ctx->getStart()->getLine(),
            ctx->getStart()->getCharPositionInLine(),
            ctx->getStop()->getLine(),
            ctx->getStop()->getCharPositionInLine()
        );
        
        currentNode_->addChild(textNode);
        return textNode;
    }
    return nullptr;
}

std::any ChtlVisitor::visitStringLiteral(CHTLParser::StringLiteralContext* ctx) {
    std::string text = ctx->getText();
    
    // 去除引号
    if (text.size() >= 2 && ((text[0] == '"' && text[text.size()-1] == '"') ||
                              (text[0] == '\'' && text[text.size()-1] == '\''))) {
        text = text.substr(1, text.size() - 2);
    }
    
    auto textNode = createTextNode(text);
    textNode->setLocation(
        ctx->getStart()->getLine(),
        ctx->getStart()->getCharPositionInLine(),
        ctx->getStop()->getLine(),
        ctx->getStop()->getCharPositionInLine()
    );
    
    currentNode_->addChild(textNode);
    return textNode;
}

std::any ChtlVisitor::visitComment(CHTLParser::CommentContext* ctx) {
    // 注释通常被忽略
    return nullptr;
}

std::any ChtlVisitor::visitStyleBlock(CHTLParser::StyleBlockContext* ctx) {
    auto styleNode = createStyleNode();
    styleNode->setLocation(
        ctx->getStart()->getLine(),
        ctx->getStart()->getCharPositionInLine(),
        ctx->getStop()->getLine(),
        ctx->getStop()->getCharPositionInLine()
    );
    
    // 设置作用域
    std::stringstream scopeStream;
    scopeStream << "style_" << ctx->getStart()->getLine() << "_" << ctx->getStart()->getCharPositionInLine();
    auto styleNodePtr = std::dynamic_pointer_cast<StyleNode>(styleNode);
    if (styleNodePtr) {
        styleNodePtr->setScope(scopeStream.str());
    }
    
    // 访问样式内容
    auto styleContents = ctx->styleContent();
    if (!styleContents.empty()) {
        nodeStack_.push(currentNode_);
        currentNode_ = styleNode;
        
        for (auto content : styleContents) {
            visit(content);
        }
        
        currentNode_ = nodeStack_.top();
        nodeStack_.pop();
    }
    
    currentNode_->addChild(styleNode);
    return styleNode;
}

std::any ChtlVisitor::visitStyleContent(CHTLParser::StyleContentContext* ctx) {
    // 访问子节点
    return visitChildren(ctx);
}

std::any ChtlVisitor::visitCssProperty(CHTLParser::CssPropertyContext* ctx) {
    auto styleNode = std::dynamic_pointer_cast<StyleNode>(currentNode_);
    if (styleNode && ctx->cssPropertyName() && ctx->cssPropertyValue()) {
        std::string property = ctx->cssPropertyName()->getText();
        std::string value = ctx->cssPropertyValue()->getText();
        
        // 根据当前选择器上下文决定如何添加属性
        if (currentSelectorType_ == SelectorType::CLASS && !currentSelectorName_.empty()) {
            styleNode->addClassRule(currentSelectorName_, property, value);
        } else if (currentSelectorType_ == SelectorType::ID && !currentSelectorName_.empty()) {
            styleNode->addIdRule(currentSelectorName_, property, value);
        } else {
            // 没有选择器，作为内联样式
            styleNode->addInlineStyle(property, value);
        }
    }
    return nullptr;
}

std::any ChtlVisitor::visitCssSelector(CHTLParser::CssSelectorContext* ctx) {
    auto styleNode = std::dynamic_pointer_cast<StyleNode>(currentNode_);
    if (!styleNode) return nullptr;
    
    // 获取选择器模式
    std::string selector;
    if (ctx->selectorPattern()) {
        // 检查选择器类型
        auto selectorPattern = ctx->selectorPattern();
        if (selectorPattern->classSelector()) {
            selector = selectorPattern->classSelector()->getText();
        } else if (selectorPattern->idSelector()) {
            selector = selectorPattern->idSelector()->getText();
        } else if (selectorPattern->ampersandSelector()) {
            selector = selectorPattern->ampersandSelector()->getText();
        } else if (selectorPattern->pseudoSelector()) {
            selector = selectorPattern->pseudoSelector()->getText();
        }
    }
    
    // 处理选择器中的CSS属性
    if (!selector.empty() && !ctx->cssProperty().empty()) {
        // 保存当前选择器
        currentSelector_ = selector;
        
        // 根据选择器类型添加到相应的集合
        if (selector[0] == '.') {
            std::string className = selector.substr(1);
            styleNode->addClassSelector(className);
            currentSelectorType_ = SelectorType::CLASS;
            currentSelectorName_ = className;
        } else if (selector[0] == '#') {
            std::string id = selector.substr(1);
            styleNode->addIdSelector(id);
            currentSelectorType_ = SelectorType::ID;
            currentSelectorName_ = id;
        }
        
        // 访问该选择器下的所有属性
        for (auto prop : ctx->cssProperty()) {
            visit(prop);
        }
        
        // 清除当前选择器
        currentSelector_.clear();
        currentSelectorType_ = SelectorType::NONE;
        currentSelectorName_.clear();
    }
    
    return nullptr;
}

std::any ChtlVisitor::visitClassSelector(CHTLParser::ClassSelectorContext* ctx) {
    auto styleNode = std::dynamic_pointer_cast<StyleNode>(currentNode_);
    if (styleNode && ctx->IDENTIFIER()) {
        std::string className = ctx->IDENTIFIER()->getText();
        styleNode->addClassSelector(className);
    }
    return nullptr;
}

std::any ChtlVisitor::visitIdSelector(CHTLParser::IdSelectorContext* ctx) {
    auto styleNode = std::dynamic_pointer_cast<StyleNode>(currentNode_);
    if (styleNode && ctx->IDENTIFIER()) {
        std::string id = ctx->IDENTIFIER()->getText();
        styleNode->addIdSelector(id);
    }
    return nullptr;
}

std::any ChtlVisitor::visitScriptBlock(CHTLParser::ScriptBlockContext* ctx) {
    std::string code;
    if (ctx->jsCode()) {
        code = ctx->jsCode()->getText();
    }
    
    bool isCHTLJS = containsCHTLJSExtensions(code);
    
    auto scriptNode = createScriptNode(code, isCHTLJS);
    scriptNode->setLocation(
        ctx->getStart()->getLine(),
        ctx->getStart()->getCharPositionInLine(),
        ctx->getStop()->getLine(),
        ctx->getStop()->getCharPositionInLine()
    );
    
    currentNode_->addChild(scriptNode);
    return scriptNode;
}

// 简化其他方法实现
std::any ChtlVisitor::visitTemplateDeclaration(CHTLParser::TemplateDeclarationContext* ctx) {
    if (!ctx->templateType() || !ctx->templateName()) {
        return nullptr;
    }
    
    // 获取模板类型
    std::string typeStr = ctx->templateType()->getText();
    TemplateNode::TemplateType type;
    
    if (typeStr == "@Style" || typeStr == "@style") {
        type = TemplateNode::TemplateType::STYLE;
    } else if (typeStr == "@Element" || typeStr == "@element") {
        type = TemplateNode::TemplateType::ELEMENT;
    } else if (typeStr == "@Var" || typeStr == "@var") {
        type = TemplateNode::TemplateType::VAR;
    } else {
        return nullptr;
    }
    
    // 获取模板名称
    std::string name = ctx->templateName()->getText();
    
    // 创建模板节点
    auto templateNode = createTemplateNode(type, name);
    templateNode->setLocation(
        ctx->getStart()->getLine(),
        ctx->getStart()->getCharPositionInLine(),
        ctx->getStop()->getLine(),
        ctx->getStop()->getCharPositionInLine()
    );
    
    // 设置命名空间
    if (!currentNamespace_.empty()) {
        auto templateNodePtr = std::dynamic_pointer_cast<TemplateNode>(templateNode);
        if (templateNodePtr) {
            templateNodePtr->setNamespace(currentNamespace_);
        }
    }
    
    // 注册到符号表
    registerTemplate(name, templateNode);
    
    // 处理模板内容
    if (ctx->templateBody()) {
        nodeStack_.push(currentNode_);
        currentNode_ = templateNode;
        
        // 访问模板内容
        auto templateContents = ctx->templateBody()->templateContent();
        if (!templateContents.empty()) {
            for (auto content : templateContents) {
                visit(content);
            }
        }
        
        currentNode_ = nodeStack_.top();
        nodeStack_.pop();
    }
    
    // 添加到根节点
    rootNode_->addChild(templateNode);
    
    return templateNode;
}

std::any ChtlVisitor::visitTemplateType(CHTLParser::TemplateTypeContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitTemplateName(CHTLParser::TemplateNameContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitTemplateUsage(CHTLParser::TemplateUsageContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitCustomDeclaration(CHTLParser::CustomDeclarationContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitCustomType(CHTLParser::CustomTypeContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitCustomName(CHTLParser::CustomNameContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitCustomUsage(CHTLParser::CustomUsageContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitOriginBlock(CHTLParser::OriginBlockContext* ctx) {
    if (!ctx->originType()) {
        return nullptr;
    }
    
    std::string originType = ctx->originType()->getText();
    std::string content;
    
    if (ctx->originBody() && ctx->originBody()->rawContent()) {
        content = ctx->originBody()->rawContent()->getText();
    }
    
    if (originType == "@Html" || originType == "@html" || originType == "@HTML") {
        // 创建原始HTML文本节点
        auto textNode = createTextNode(content);
        auto textNodePtr = std::dynamic_pointer_cast<TextNode>(textNode);
        if (textNodePtr) {
            textNodePtr->setRaw(true);
        }
        textNode->setLocation(
            ctx->getStart()->getLine(),
            ctx->getStart()->getCharPositionInLine(),
            ctx->getStop()->getLine(),
            ctx->getStop()->getCharPositionInLine()
        );
        currentNode_->addChild(textNode);
        return textNode;
    } else if (originType == "@Style" || originType == "@style" || originType == "@CSS" || originType == "@css") {
        // 创建原始CSS样式节点
        auto styleNode = createStyleNode();
        auto styleNodePtr = std::dynamic_pointer_cast<StyleNode>(styleNode);
        if (styleNodePtr) {
            styleNodePtr->setRawCSS(content);
        }
        styleNode->setLocation(
            ctx->getStart()->getLine(),
            ctx->getStart()->getCharPositionInLine(),
            ctx->getStop()->getLine(),
            ctx->getStop()->getCharPositionInLine()
        );
        currentNode_->addChild(styleNode);
        return styleNode;
    } else if (originType == "@JavaScript" || originType == "@javascript" || originType == "@JS" || originType == "@js") {
        // 创建原始JavaScript脚本节点
        auto scriptNode = createScriptNode(content, false);
        scriptNode->setLocation(
            ctx->getStart()->getLine(),
            ctx->getStart()->getCharPositionInLine(),
            ctx->getStop()->getLine(),
            ctx->getStop()->getCharPositionInLine()
        );
        currentNode_->addChild(scriptNode);
        return scriptNode;
    }
    
    return nullptr;
}

std::any ChtlVisitor::visitImportStatement(CHTLParser::ImportStatementContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitImportChtl(CHTLParser::ImportChtlContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitNamespaceDeclaration(CHTLParser::NamespaceDeclarationContext* ctx) {
    return nullptr; // TODO: 实现
}

std::any ChtlVisitor::visitConfigurationBlock(CHTLParser::ConfigurationBlockContext* ctx) {
    return nullptr; // TODO: 实现
}

// 辅助方法实现

NodePtr ChtlVisitor::createElementNode(const std::string& tagName) {
    return std::make_shared<ElementNode>(tagName);
}

NodePtr ChtlVisitor::createTextNode(const std::string& text) {
    return std::make_shared<TextNode>(text);
}

NodePtr ChtlVisitor::createStyleNode() {
    return std::make_shared<StyleNode>();
}

NodePtr ChtlVisitor::createScriptNode(const std::string& content, bool isCHTLJS) {
    return std::make_shared<ScriptNode>(content, isCHTLJS);
}

NodePtr ChtlVisitor::createTemplateNode(TemplateNode::TemplateType type, const std::string& name) {
    return std::make_shared<TemplateNode>(type, name);
}

NodePtr ChtlVisitor::createCustomNode(CustomNode::CustomType type, const std::string& name) {
    return std::make_shared<CustomNode>(type, name);
}

void ChtlVisitor::processElementAttributes(NodePtr node, CHTLParser::ElementBodyContext* ctx) {
    auto elementNode = std::dynamic_pointer_cast<ElementNode>(node);
    if (!elementNode || !ctx) return;
    
    // 遍历元素内容，查找属性
    for (auto content : ctx->elementContent()) {
        if (content->attribute()) {
            auto attr = content->attribute();
            if (attr->attributeName() && attr->attributeValue()) {
                std::string key = attr->attributeName()->getText();
                std::string value = attr->attributeValue()->getText();
                
                // 去除值的引号
                if (value.size() >= 2 && ((value[0] == '"' && value[value.size()-1] == '"') ||
                                          (value[0] == '\'' && value[value.size()-1] == '\''))) {
                    value = value.substr(1, value.size() - 2);
                }
                
                // 特殊处理id和class
                if (key == "id") {
                    elementNode->setId(value);
                } else if (key == "class") {
                    // 分割多个类名
                    std::stringstream ss(value);
                    std::string className;
                    while (ss >> className) {
                        elementNode->addClass(className);
                    }
                } else {
                    elementNode->setAttribute(key, value);
                }
            }
        }
    }
}

void ChtlVisitor::registerTemplate(const std::string& name, NodePtr templateNode) {
    auto symbol = std::make_shared<Symbol>(name, SymbolType::TEMPLATE_ELEMENT);
    symbol->setContent(templateNode);
    symbolTable_->defineSymbol(symbol);
}

void ChtlVisitor::registerCustom(const std::string& name, NodePtr customNode) {
    auto symbol = std::make_shared<Symbol>(name, SymbolType::CUSTOM_ELEMENT);
    symbol->setContent(customNode);
    symbolTable_->defineSymbol(symbol);
}

bool ChtlVisitor::containsCHTLJSExtensions(const std::string& code) const {
    // 检查CHTL JS特有的语法
    return code.find("{{") != std::string::npos ||
           code.find("->") != std::string::npos ||
           code.find("listen") != std::string::npos ||
           code.find("delegate") != std::string::npos ||
           code.find("animate") != std::string::npos;
}

std::string ChtlVisitor::getText(antlr4::tree::ParseTree* tree) {
    if (!tree) return "";
    return tree->getText();
}

} // namespace CHTL