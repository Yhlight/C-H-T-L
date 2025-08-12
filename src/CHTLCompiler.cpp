#include "CHTLCompiler.h"
#include <sstream>
#include <fstream>

// 注意：这些头文件将由ANTLR生成
// #include "CHTLLexer.h"
// #include "CHTLParser.h"
// #include "CHTLBaseVisitor.h"

namespace CHTL {

// 错误监听器实现
class CHTLCompiler::ErrorListener : public antlr4::BaseErrorListener {
public:
    ErrorListener(std::vector<std::string>& errors) : errors_(errors) {}
    
    void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol,
                    size_t line, size_t charPositionInLine,
                    const std::string& msg, std::exception_ptr e) override {
        std::stringstream ss;
        ss << "语法错误 [" << line << ":" << charPositionInLine << "] " << msg;
        errors_.push_back(ss.str());
    }
    
private:
    std::vector<std::string>& errors_;
};

// CHTL访问者实现
// 注意：实际实现需要继承自ANTLR生成的CHTLBaseVisitor
class CHTLCompiler::CHTLVisitorImpl {
public:
    CHTLVisitorImpl(SymbolTable* symbolTable) : symbolTable_(symbolTable) {
        // 创建根节点
        rootNode_ = std::make_shared<ElementNode>("root");
        currentNode_ = rootNode_;
        nodeStack_.push(rootNode_);
    }
    
    std::shared_ptr<ASTNode> getAST() { return rootNode_; }
    
    // 模拟的访问方法（实际需要根据ANTLR生成的接口实现）
    void visitProgram() {
        // 程序入口处理
    }
    
    void visitElement(const std::string& tagName, const std::string& body) {
        auto elementNode = std::make_shared<ElementNode>(tagName);
        currentNode_->addChild(elementNode);
        
        // 压栈当前节点
        nodeStack_.push(elementNode);
        currentNode_ = elementNode;
        
        // 处理元素体
        // ...
        
        // 出栈
        nodeStack_.pop();
        currentNode_ = nodeStack_.top();
    }
    
    void visitTextNode(const std::string& text) {
        auto textNode = std::make_shared<TextNode>(text);
        currentNode_->addChild(textNode);
    }
    
    void visitAttribute(const std::string& name, const std::string& value) {
        if (auto element = std::dynamic_pointer_cast<ElementNode>(currentNode_)) {
            if (name == "id") {
                element->setId(value);
            } else if (name == "class") {
                // 处理多个类名
                std::istringstream iss(value);
                std::string className;
                while (iss >> className) {
                    element->addClass(className);
                }
            } else {
                element->setAttribute(name, value);
            }
        }
    }
    
    void visitStyleBlock() {
        auto styleNode = std::make_shared<StyleBlockNode>();
        currentNode_->addChild(styleNode);
        
        nodeStack_.push(styleNode);
        currentNode_ = styleNode;
    }
    
    void visitStyleProperty(const std::string& property, const std::string& value) {
        if (auto style = std::dynamic_pointer_cast<StyleBlockNode>(currentNode_)) {
            style->addInlineStyle(property, value);
        }
    }
    
    void visitClassSelector(const std::string& className) {
        if (auto style = std::dynamic_pointer_cast<StyleBlockNode>(currentNode_)) {
            style->addClassSelector(className);
            
            // 自动为父元素添加类名
            if (nodeStack_.size() > 1) {
                auto parent = nodeStack_.top();
                nodeStack_.pop();
                auto grandParent = nodeStack_.top();
                nodeStack_.push(parent);
                
                if (auto element = std::dynamic_pointer_cast<ElementNode>(grandParent)) {
                    element->addClass(className);
                }
            }
        }
    }
    
    void visitScriptBlock(const std::string& code) {
        // 检查是否包含CHTL JS语法
        bool isCHTLJS = containsCHTLJSExtensions(code);
        auto scriptNode = std::make_shared<ScriptBlockNode>(code, isCHTLJS);
        currentNode_->addChild(scriptNode);
    }
    
    void visitTemplateDeclaration(const std::string& type, const std::string& name) {
        TemplateNode::TemplateType templateType;
        SymbolType symbolType;
        
        if (type == "@Style") {
            templateType = TemplateNode::TemplateType::STYLE;
            symbolType = SymbolType::TEMPLATE_STYLE;
        } else if (type == "@Element") {
            templateType = TemplateNode::TemplateType::ELEMENT;
            symbolType = SymbolType::TEMPLATE_ELEMENT;
        } else if (type == "@Var") {
            templateType = TemplateNode::TemplateType::VAR;
            symbolType = SymbolType::TEMPLATE_VAR;
        }
        
        auto templateNode = std::make_shared<TemplateNode>(templateType, name);
        
        // 注册到符号表
        auto symbol = std::make_shared<Symbol>(name, symbolType);
        symbol->setContent(templateNode);
        symbolTable_->defineSymbol(symbol);
        
        // 处理模板内容
        nodeStack_.push(templateNode);
        currentNode_ = templateNode;
    }
    
    void visitCustomDeclaration(const std::string& type, const std::string& name) {
        CustomNode::CustomType customType;
        SymbolType symbolType;
        
        if (type == "@Style") {
            customType = CustomNode::CustomType::STYLE;
            symbolType = SymbolType::CUSTOM_STYLE;
        } else if (type == "@Element") {
            customType = CustomNode::CustomType::ELEMENT;
            symbolType = SymbolType::CUSTOM_ELEMENT;
        } else if (type == "@Var") {
            customType = CustomNode::CustomType::VAR;
            symbolType = SymbolType::CUSTOM_VAR;
        }
        
        auto customNode = std::make_shared<CustomNode>(customType, name);
        
        // 注册到符号表
        auto symbol = std::make_shared<Symbol>(name, symbolType);
        symbol->setContent(customNode);
        symbolTable_->defineSymbol(symbol);
        
        // 处理自定义内容
        nodeStack_.push(customNode);
        currentNode_ = customNode;
    }
    
private:
    bool containsCHTLJSExtensions(const std::string& code) {
        static const std::vector<std::string> patterns = {
            "{{", "->", "->listen", "->delegate", "animate("
        };
        
        for (const auto& pattern : patterns) {
            if (code.find(pattern) != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    
private:
    SymbolTable* symbolTable_;
    std::shared_ptr<ASTNode> rootNode_;
    std::shared_ptr<ASTNode> currentNode_;
    std::stack<std::shared_ptr<ASTNode>> nodeStack_;
};

CHTLCompiler::CHTLCompiler(SymbolTable* symbolTable) 
    : symbolTable_(symbolTable) {
    visitor_ = std::make_unique<CHTLVisitorImpl>(symbolTable);
    errorListener_ = std::make_unique<ErrorListener>(errors_);
}

CHTLCompiler::~CHTLCompiler() = default;

std::shared_ptr<ASTNode> CHTLCompiler::compile(const std::string& code) {
    try {
        // 临时实现：直接解析简单的CHTL结构
        // 实际实现需要使用ANTLR生成的词法分析器和语法分析器
        
        // 这里提供一个简化的解析示例
        return parseSimpleCHTL(code);
        
    } catch (const std::exception& e) {
        errors_.push_back(std::string("编译错误: ") + e.what());
        return nullptr;
    }
}

std::shared_ptr<ASTNode> CHTLCompiler::parseFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        errors_.push_back("无法打开文件: " + filePath);
        return nullptr;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();
    
    return compile(content);
}

// 简化的CHTL解析器（用于演示）
std::shared_ptr<ASTNode> CHTLCompiler::parseSimpleCHTL(const std::string& code) {
    auto root = std::make_shared<ElementNode>("html");
    
    // 简单的行解析
    std::istringstream iss(code);
    std::string line;
    std::stack<std::shared_ptr<ASTNode>> nodeStack;
    nodeStack.push(root);
    
    while (std::getline(iss, line)) {
        // 移除前后空格
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        if (line.empty() || line.substr(0, 2) == "//") {
            continue; // 跳过空行和注释
        }
        
        // 简单识别元素
        if (line.find("{") != std::string::npos) {
            std::string tagName = line.substr(0, line.find("{"));
            tagName.erase(tagName.find_last_not_of(" \t") + 1);
            
            if (!tagName.empty() && tagName != "text" && tagName != "style" && tagName != "script") {
                auto element = std::make_shared<ElementNode>(tagName);
                nodeStack.top()->addChild(element);
                nodeStack.push(element);
            } else if (tagName == "text") {
                // 处理文本节点
                std::string nextLine;
                if (std::getline(iss, nextLine)) {
                    nextLine.erase(0, nextLine.find_first_not_of(" \t\""));
                    nextLine.erase(nextLine.find_last_not_of(" \t\"") + 1);
                    auto textNode = std::make_shared<TextNode>(nextLine);
                    nodeStack.top()->addChild(textNode);
                }
            } else if (tagName == "style") {
                auto styleNode = std::make_shared<StyleBlockNode>();
                nodeStack.top()->addChild(styleNode);
                nodeStack.push(styleNode);
            } else if (tagName == "script") {
                // 收集脚本内容
                std::string scriptContent;
                std::string scriptLine;
                int braceCount = 1;
                while (braceCount > 0 && std::getline(iss, scriptLine)) {
                    for (char c : scriptLine) {
                        if (c == '{') braceCount++;
                        else if (c == '}') braceCount--;
                    }
                    if (braceCount > 0) {
                        scriptContent += scriptLine + "\n";
                    }
                }
                bool isCHTLJS = scriptContent.find("{{") != std::string::npos || 
                               scriptContent.find("->") != std::string::npos;
                auto scriptNode = std::make_shared<ScriptBlockNode>(scriptContent, isCHTLJS);
                nodeStack.top()->addChild(scriptNode);
            }
        } else if (line == "}") {
            if (nodeStack.size() > 1) {
                nodeStack.pop();
            }
        } else if (line.find(":") != std::string::npos) {
            // 处理属性
            size_t colonPos = line.find(":");
            std::string attrName = line.substr(0, colonPos);
            std::string attrValue = line.substr(colonPos + 1);
            
            attrName.erase(0, attrName.find_first_not_of(" \t"));
            attrName.erase(attrName.find_last_not_of(" \t") + 1);
            attrValue.erase(0, attrValue.find_first_not_of(" \t\""));
            attrValue.erase(attrValue.find_last_not_of(" \t\";") + 1);
            
            if (auto element = std::dynamic_pointer_cast<ElementNode>(nodeStack.top())) {
                if (attrName == "id") {
                    element->setId(attrValue);
                } else if (attrName == "class") {
                    std::istringstream classStream(attrValue);
                    std::string className;
                    while (classStream >> className) {
                        element->addClass(className);
                    }
                } else {
                    element->setAttribute(attrName, attrValue);
                }
            } else if (auto style = std::dynamic_pointer_cast<StyleBlockNode>(nodeStack.top())) {
                style->addInlineStyle(attrName, attrValue);
            }
        }
    }
    
    return root;
}

} // namespace CHTL