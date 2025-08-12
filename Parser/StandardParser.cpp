#include "StandardParser.h"
#include <fstream>
#include <sstream>

namespace CHTL {

StandardParser::StandardParser() 
    : debugMode_(false) {
    symbolTable_ = std::make_unique<SymbolTable>();
    scanner_ = std::make_unique<BridgeScanner>();
}

StandardParser::~StandardParser() = default;

NodePtr StandardParser::parse(const std::string& content) {
    errors_.clear();
    warnings_.clear();
    
    // 使用扫描器切割代码
    auto segments = scanner_->scan(content);
    
    // 检查扫描错误
    for (const auto& error : scanner_->getErrors()) {
        addError(error);
    }
    
    if (!segments.empty() && errors_.empty()) {
        // 创建根节点
        auto root = std::make_shared<ElementNode>("root");
        
        // 处理每个代码段
        for (const auto& segment : segments) {
            NodePtr node = nullptr;
            
            switch (segment->getType()) {
                case LanguageType::CHTL:
                    node = parseCHTLSegment(*segment);
                    break;
                case LanguageType::CSS:
                    node = parseCSSSegment(*segment);
                    break;
                case LanguageType::JAVASCRIPT:
                    node = parseJavaScriptSegment(*segment);
                    break;
                case LanguageType::CHTL_JAVASCRIPT:
                    node = parseCHTLJavaScriptSegment(*segment);
                    break;
                case LanguageType::HTML:
                    // HTML段直接作为原始内容
                    node = std::make_shared<TextNode>(segment->getContent());
                    break;
                default:
                    addWarning("未知的语言类型段");
                    break;
            }
            
            if (node) {
                mergeAST(root, node, *segment);
            }
        }
        
        // 后处理AST
        postProcessAST(root);
        
        // 验证AST
        if (validateAST(root)) {
            return root;
        }
    }
    
    return nullptr;
}

NodePtr StandardParser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        addError("无法打开文件: " + filename);
        return nullptr;
    }
    
    currentFile_ = filename;
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    
    return parse(content);
}

void StandardParser::setOption(const std::string& key, const std::string& value) {
    options_[key] = value;
}

NodePtr StandardParser::parseCHTLSegment(const Segment& segment) {
    // TODO: 使用ANTLR4解析CHTL段
    // 暂时返回一个包含原始内容的文本节点
    auto node = std::make_shared<TextNode>(segment.getContent());
    node->setLocation(segment.getStartLine(), segment.getStartColumn(),
                     segment.getEndLine(), segment.getEndColumn());
    return node;
}

NodePtr StandardParser::parseCSSSegment(const Segment& segment) {
    // TODO: 使用ANTLR4解析CSS段
    // 暂时返回一个样式节点
    auto styleNode = std::make_shared<StyleNode>();
    styleNode->setRawCSS(segment.getContent());
    styleNode->setLocation(segment.getStartLine(), segment.getStartColumn(),
                          segment.getEndLine(), segment.getEndColumn());
    return styleNode;
}

NodePtr StandardParser::parseJavaScriptSegment(const Segment& segment) {
    // TODO: 使用ANTLR4解析JavaScript段
    // 暂时返回一个脚本节点
    auto scriptNode = std::make_shared<ScriptNode>(segment.getContent(), false);
    scriptNode->setLocation(segment.getStartLine(), segment.getStartColumn(),
                           segment.getEndLine(), segment.getEndColumn());
    return scriptNode;
}

NodePtr StandardParser::parseCHTLJavaScriptSegment(const Segment& segment) {
    // TODO: 使用ANTLR4解析CHTL JavaScript段
    // 暂时返回一个CHTL JS脚本节点
    auto scriptNode = std::make_shared<ScriptNode>(segment.getContent(), true);
    scriptNode->setLocation(segment.getStartLine(), segment.getStartColumn(),
                           segment.getEndLine(), segment.getEndColumn());
    return scriptNode;
}

void StandardParser::mergeAST(NodePtr root, NodePtr node, const Segment& segment) {
    if (!root || !node) return;
    
    // 根据上下文信息决定如何合并节点
    if (segment.getContext() == "style" || segment.getContext() == "script") {
        // style和script节点直接添加到根节点
        root->addChild(node);
    } else if (segment.getContext().find("origin:") == 0) {
        // origin块也直接添加
        root->addChild(node);
    } else {
        // 其他节点根据类型处理
        if (node->getType() == NodeType::ELEMENT) {
            root->addChild(node);
        } else {
            // 文本等节点添加到最后一个元素节点
            if (root->getChildCount() > 0) {
                auto lastChild = root->getChild(root->getChildCount() - 1);
                if (lastChild && lastChild->getType() == NodeType::ELEMENT) {
                    lastChild->addChild(node);
                } else {
                    root->addChild(node);
                }
            } else {
                root->addChild(node);
            }
        }
    }
}

void StandardParser::postProcessAST(NodePtr root) {
    if (!root) return;
    
    // TODO: 实现AST后处理
    // 1. 展开模板和自定义
    // 2. 处理命名空间
    // 3. 处理导入
    // 4. 优化AST结构
}

bool StandardParser::validateAST(NodePtr root) {
    if (!root) {
        addError("AST根节点为空");
        return false;
    }
    
    // TODO: 实现AST验证
    // 1. 检查元素名称是否有效
    // 2. 检查属性是否有效
    // 3. 检查模板引用是否存在
    // 4. 检查自定义引用是否存在
    
    return errors_.empty();
}

void StandardParser::addError(const std::string& error, int line, int column) {
    std::stringstream ss;
    if (!currentFile_.empty()) {
        ss << currentFile_ << ":";
    }
    if (line > 0) {
        ss << line << ":" << column << ": ";
    }
    ss << "错误: " << error;
    errors_.push_back(ss.str());
}

void StandardParser::addWarning(const std::string& warning, int line, int column) {
    std::stringstream ss;
    if (!currentFile_.empty()) {
        ss << currentFile_ << ":";
    }
    if (line > 0) {
        ss << line << ":" << column << ": ";
    }
    ss << "警告: " << warning;
    warnings_.push_back(ss.str());
}

} // namespace CHTL