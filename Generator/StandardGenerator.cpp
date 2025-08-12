#include "StandardGenerator.h"
#include "Node/ElementNode.h"
#include "Node/TextNode.h"
#include "Node/StyleNode.h"
#include "Node/ScriptNode.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <set>

namespace CHTL {

// 内部实现类
class StandardGenerator::HtmlGeneratorImpl {
public:
    std::string generate(NodePtr node) {
        if (!node) return "";
        
        std::stringstream ss;
        generateNode(node, ss, 0);
        return ss.str();
    }
    
private:
    void generateNode(NodePtr node, std::stringstream& ss, int indent) {
        if (!node) return;
        
        switch (node->getType()) {
            case NodeType::ELEMENT:
                generateElement(node, ss, indent);
                break;
            case NodeType::TEXT:
                generateText(node, ss, indent);
                break;
            case NodeType::STYLE:
                // Style节点在CSS生成器中处理
                break;
            case NodeType::SCRIPT:
                // Script节点在JS生成器中处理
                break;
            default:
                // 递归处理子节点
                for (size_t i = 0; i < node->getChildCount(); ++i) {
                    generateNode(node->getChild(i), ss, indent);
                }
                break;
        }
    }
    
    void generateElement(NodePtr node, std::stringstream& ss, int indent) {
        auto element = std::dynamic_pointer_cast<ElementNode>(node);
        if (!element) return;
        
        std::string tagName = element->getTagName();
        
        // 特殊处理document节点
        if (tagName == "document") {
            // 生成标准HTML5文档结构
            ss << "<!DOCTYPE html>\n";
            
            // 查找html节点
            NodePtr htmlNode = nullptr;
            for (size_t i = 0; i < element->getChildCount(); ++i) {
                auto child = element->getChild(i);
                if (child->getType() == NodeType::ELEMENT) {
                    auto childElement = std::dynamic_pointer_cast<ElementNode>(child);
                    if (childElement && childElement->getTagName() == "html") {
                        htmlNode = child;
                        break;
                    }
                }
            }
            
            if (htmlNode) {
                // 生成html节点
                generateNode(htmlNode, ss, 0);
            } else {
                // 如果没有html节点，生成默认结构
                ss << "<html>\n";
                
                // 查找head和body
                NodePtr head = nullptr;
                NodePtr body = nullptr;
                
                for (size_t i = 0; i < element->getChildCount(); ++i) {
                    auto child = element->getChild(i);
                    if (child->getType() == NodeType::ELEMENT) {
                        auto childElement = std::dynamic_pointer_cast<ElementNode>(child);
                        if (childElement) {
                            if (childElement->getTagName() == "head") {
                                head = child;
                            } else if (childElement->getTagName() == "body") {
                                body = child;
                            }
                        }
                    }
                }
                
                // 生成head
                if (head) {
                    generateNode(head, ss, 1);
                } else {
                    ss << "  <head>\n";
                    ss << "    <meta charset=\"UTF-8\">\n";
                    ss << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
                    ss << "  </head>\n";
                }
                
                // 生成body
                if (body) {
                    generateNode(body, ss, 1);
                } else {
                    ss << "  <body>\n";
                    // 生成其他子节点
                    for (size_t i = 0; i < element->getChildCount(); ++i) {
                        auto child = element->getChild(i);
                        if (child != head && child != body && child != htmlNode) {
                            generateNode(child, ss, 2);
                        }
                    }
                    ss << "  </body>\n";
                }
                
                ss << "</html>";
            }
            return;
        }
        
        // 生成缩进
        ss << std::string(indent * 2, ' ');
        
        // 开始标签
        ss << "<" << tagName;
        
        // 生成属性
        if (!element->getId().empty()) {
            ss << " id=\"" << escapeHtml(element->getId()) << "\"";
        }
        
        if (!element->getClasses().empty()) {
            ss << " class=\"";
            bool first = true;
            for (const auto& cls : element->getClasses()) {
                if (!first) ss << " ";
                ss << escapeHtml(cls);
                first = false;
            }
            ss << "\"";
        }
        
        for (const auto& [key, value] : element->getAttributes()) {
            ss << " " << key << "=\"" << escapeHtml(value) << "\"";
        }
        
        // 检查是否是自闭合标签
        if (isVoidElement(tagName) || element->isSelfClosing()) {
            ss << ">\n";
        } else {
            ss << ">";
            
            // 检查是否有子节点
            bool hasChildren = element->getChildCount() > 0;
            bool hasOnlyText = hasChildren && element->getChildCount() == 1 && 
                              element->getChild(0)->getType() == NodeType::TEXT;
            
            if (hasChildren && !hasOnlyText) {
                ss << "\n";
            }
            
            // 生成子节点
            for (size_t i = 0; i < element->getChildCount(); ++i) {
                generateNode(element->getChild(i), ss, hasOnlyText ? 0 : indent + 1);
            }
            
            // 结束标签
            if (hasChildren && !hasOnlyText) {
                ss << std::string(indent * 2, ' ');
            }
            ss << "</" << tagName << ">\n";
        }
    }
    
    void generateText(NodePtr node, std::stringstream& ss, int indent) {
        auto text = std::dynamic_pointer_cast<TextNode>(node);
        if (!text) return;
        
        std::string content = text->getText();
        if (content.empty()) return;
        
        if (indent > 0) {
            ss << std::string(indent * 2, ' ');
        }
        
        if (text->isRaw()) {
            ss << content;
        } else {
            ss << escapeHtml(content);
        }
        
        if (indent > 0) {
            ss << "\n";
        }
    }
    
    std::string escapeHtml(const std::string& text) {
        std::string result;
        for (char c : text) {
            switch (c) {
                case '&': result += "&amp;"; break;
                case '<': result += "&lt;"; break;
                case '>': result += "&gt;"; break;
                case '"': result += "&quot;"; break;
                case '\'': result += "&#39;"; break;
                default: result += c; break;
            }
        }
        return result;
    }
    
    bool isVoidElement(const std::string& tag) {
        static const std::set<std::string> voidElements = {
            "area", "base", "br", "col", "embed", "hr", "img", "input",
            "link", "meta", "param", "source", "track", "wbr"
        };
        return voidElements.find(tag) != voidElements.end();
    }
};

class StandardGenerator::CssGeneratorImpl {
public:
    std::string generate(const std::vector<NodePtr>& styleNodes) {
        std::stringstream ss;
        
        for (const auto& node : styleNodes) {
            auto styleNode = std::dynamic_pointer_cast<StyleNode>(node);
            if (styleNode) {
                generateStyleNode(styleNode, ss);
            }
        }
        
        return ss.str();
    }
    
private:
    void generateStyleNode(std::shared_ptr<StyleNode> styleNode, std::stringstream& ss) {
        // 如果有原始CSS，直接输出
        if (!styleNode->getRawCSS().empty()) {
            ss << styleNode->getRawCSS() << "\n";
            return;
        }
        
        // 生成内联样式（作为独立的样式块）
        if (!styleNode->getInlineStyles().empty()) {
            // 如果有作用域，生成作用域类
            std::string scopeSelector;
            if (!styleNode->getScope().empty() && !styleNode->isGlobal()) {
                scopeSelector = "." + styleNode->getScope() + " ";
            }
            
            // 处理内联样式
            bool hasBodyStyles = false;
            for (const auto& [prop, value] : styleNode->getInlineStyles()) {
                // 检查是否是选择器（以.或#开头）
                if (prop[0] != '.' && prop[0] != '#') {
                    if (!hasBodyStyles) {
                        ss << scopeSelector << "body {\n";
                        hasBodyStyles = true;
                    }
                    ss << "  " << prop << ": " << value << ";\n";
                }
            }
            if (hasBodyStyles) {
                ss << "}\n\n";
            }
        }
        
        // 生成类样式
        for (const auto& className : styleNode->getClassSelectors()) {
            std::string selector = "." + className;
            if (!styleNode->getScope().empty() && !styleNode->isGlobal()) {
                selector = "." + styleNode->getScope() + " " + selector;
            }
            
            ss << selector << " {\n";
            // 获取该类的所有规则
            const auto& classRules = styleNode->getClassRules();
            auto it = classRules.find(className);
            if (it != classRules.end()) {
                for (const auto& [prop, value] : it->second) {
                    ss << "  " << prop << ": " << value << ";\n";
                }
            }
            ss << "}\n\n";
        }
        
        // 生成ID样式
        for (const auto& id : styleNode->getIdSelectors()) {
            std::string selector = "#" + id;
            if (!styleNode->getScope().empty() && !styleNode->isGlobal()) {
                selector = "." + styleNode->getScope() + " " + selector;
            }
            
            ss << selector << " {\n";
            // 获取该ID的所有规则
            const auto& idRules = styleNode->getIdRules();
            auto it = idRules.find(id);
            if (it != idRules.end()) {
                for (const auto& [prop, value] : it->second) {
                    ss << "  " << prop << ": " << value << ";\n";
                }
            }
            ss << "}\n\n";
        }
    }
};

class StandardGenerator::JsGeneratorImpl {
public:
    std::string generate(const std::vector<NodePtr>& scriptNodes) {
        std::stringstream ss;
        
        // 添加CHTL运行时支持（如果需要）
        bool needsChtlRuntime = false;
        for (const auto& node : scriptNodes) {
            auto scriptNode = std::dynamic_pointer_cast<ScriptNode>(node);
            if (scriptNode && scriptNode->isCHTLJS()) {
                needsChtlRuntime = true;
                break;
            }
        }
        
        if (needsChtlRuntime) {
            ss << generateChtlRuntime() << "\n\n";
        }
        
        // 生成每个脚本
        for (const auto& node : scriptNodes) {
            auto scriptNode = std::dynamic_pointer_cast<ScriptNode>(node);
            if (scriptNode) {
                if (scriptNode->isCHTLJS()) {
                    ss << transformChtlJs(scriptNode->getCode()) << "\n";
                } else {
                    ss << scriptNode->getCode() << "\n";
                }
            }
        }
        
        return ss.str();
    }
    
private:
    std::string generateChtlRuntime() {
        return R"(// CHTL Runtime Support
const CHTL = {
  select: function(selector) {
    if (selector.startsWith('{{') && selector.endsWith('}}')) {
      selector = selector.slice(2, -2).trim();
    }
    const elements = document.querySelectorAll(selector);
    return {
      elements: elements,
      listen: function(event, handler) {
        elements.forEach(el => el.addEventListener(event, handler));
        return this;
      },
      delegate: function(childSelector, event, handler) {
        elements.forEach(el => {
          el.addEventListener(event, function(e) {
            const target = e.target.closest(childSelector);
            if (target && el.contains(target)) {
              handler.call(target, e);
            }
          });
        });
        return this;
      },
      animate: function(options) {
        // Simple animation implementation
        elements.forEach(el => {
          if (options.begin) {
            Object.assign(el.style, options.begin);
          }
          setTimeout(() => {
            el.style.transition = `all ${options.duration || 1000}ms ${options.easing || 'ease'}`;
            if (options.end) {
              Object.assign(el.style, options.end);
            }
          }, options.delay || 0);
        });
        return this;
      }
    };
  }
};)";
    }
    
    std::string transformChtlJs(const std::string& code) {
        std::string result = code;
        
        // 简单的CHTL JS转换
        // 1. 替换 {{selector}} -> CHTL.select('selector')
        size_t pos = 0;
        while ((pos = result.find("{{", pos)) != std::string::npos) {
            size_t endPos = result.find("}}", pos);
            if (endPos != std::string::npos) {
                std::string selector = result.substr(pos + 2, endPos - pos - 2);
                
                // 去除选择器两端的引号（如果有）
                if (selector.size() >= 2) {
                    if ((selector[0] == '"' && selector[selector.size()-1] == '"') ||
                        (selector[0] == '\'' && selector[selector.size()-1] == '\'')) {
                        selector = selector.substr(1, selector.size() - 2);
                    }
                }
                
                std::string replacement = "CHTL.select('" + selector + "')";
                result.replace(pos, endPos - pos + 2, replacement);
                pos += replacement.length();
            } else {
                break;
            }
        }
        
        // 2. 替换 -> 为 .
        pos = 0;
        while ((pos = result.find("->", pos)) != std::string::npos) {
            // 确保不是在字符串中
            bool inString = false;
            char stringChar = 0;
            for (size_t i = 0; i < pos; ++i) {
                if (result[i] == '"' || result[i] == '\'') {
                    if (!inString) {
                        inString = true;
                        stringChar = result[i];
                    } else if (result[i] == stringChar && (i == 0 || result[i-1] != '\\')) {
                        inString = false;
                    }
                }
            }
            
            if (!inString) {
                result.replace(pos, 2, ".");
                pos += 1;
            } else {
                pos += 2;
            }
        }
        
        return result;
    }
};

StandardGenerator::StandardGenerator() {
    htmlGenerator_ = std::make_unique<HtmlGeneratorImpl>();
    cssGenerator_ = std::make_unique<CssGeneratorImpl>();
    jsGenerator_ = std::make_unique<JsGeneratorImpl>();
}

StandardGenerator::~StandardGenerator() = default;

GenerateResult StandardGenerator::generate(NodePtr ast, SymbolTable* symbolTable) {
    GenerateResult result;
    
    if (!ast) {
        result.success = false;
        result.errors.push_back("AST根节点为空");
        return result;
    }
    
    try {
        // 预处理AST
        preprocessAST(ast, symbolTable);
        
        // 收集样式和脚本节点
        std::vector<NodePtr> styleNodes;
        std::vector<NodePtr> scriptNodes;
        collectStyles(ast, styleNodes);
        collectScripts(ast, scriptNodes);
        
        // 生成代码
        result.html = generateHTML(ast);
        result.css = generateCSS(styleNodes);
        result.javascript = generateJavaScript(scriptNodes);
        
        // 生成模块文件
        if (modularize_) {
            generateModules(ast, result);
        }
        
        // 优化代码
        if (optimizationLevel_ > 0) {
            optimizeCode(result);
        }
        
        // 格式化代码
        if (minify_) {
            result.html = minifyCode(result.html, "html");
            result.css = minifyCode(result.css, "css");
            result.javascript = minifyCode(result.javascript, "javascript");
        } else if (prettify_) {
            result.html = prettifyCode(result.html, "html");
            result.css = prettifyCode(result.css, "css");
            result.javascript = prettifyCode(result.javascript, "javascript");
        }
        
        result.success = true;
    } catch (const std::exception& e) {
        result.success = false;
        result.errors.push_back(std::string("生成错误: ") + e.what());
    }
    
    return result;
}

void StandardGenerator::setOutputConfig(const std::string& key, const std::string& value) {
    outputConfig_[key] = value;
}

void StandardGenerator::preprocessAST(NodePtr ast, SymbolTable* symbolTable) {
    if (!ast || !symbolTable) return;
    
    // 展开模板和自定义
    expandTemplatesAndCustoms(ast, symbolTable);
    
    // TODO: 其他预处理步骤
}

void StandardGenerator::expandTemplatesAndCustoms(NodePtr ast, SymbolTable* symbolTable) {
    // TODO: 实现模板和自定义展开
}

void StandardGenerator::collectStyles(NodePtr ast, std::vector<NodePtr>& styleNodes) {
    if (!ast) return;
    
    // 如果是样式节点，添加到列表
    if (ast->getType() == NodeType::STYLE) {
        styleNodes.push_back(ast);
    }
    
    // 递归处理子节点
    for (size_t i = 0; i < ast->getChildCount(); ++i) {
        collectStyles(ast->getChild(i), styleNodes);
    }
}

void StandardGenerator::collectScripts(NodePtr ast, std::vector<NodePtr>& scriptNodes) {
    if (!ast) return;
    
    // 如果是脚本节点，添加到列表
    if (ast->getType() == NodeType::SCRIPT) {
        scriptNodes.push_back(ast);
    }
    
    // 递归处理子节点
    for (size_t i = 0; i < ast->getChildCount(); ++i) {
        collectScripts(ast->getChild(i), scriptNodes);
    }
}

std::string StandardGenerator::generateHTML(NodePtr ast) {
    return htmlGenerator_->generate(ast);
}

std::string StandardGenerator::generateCSS(const std::vector<NodePtr>& styleNodes) {
    return cssGenerator_->generate(styleNodes);
}

std::string StandardGenerator::generateJavaScript(const std::vector<NodePtr>& scriptNodes) {
    return jsGenerator_->generate(scriptNodes);
}

void StandardGenerator::generateModules(NodePtr ast, GenerateResult& result) {
    // TODO: 实现模块生成
}

void StandardGenerator::optimizeCode(GenerateResult& result) {
    // TODO: 实现代码优化
}

std::string StandardGenerator::formatCode(const std::string& code, const std::string& language) {
    if (minify_) {
        return minifyCode(code, language);
    } else if (prettify_) {
        return prettifyCode(code, language);
    }
    return code;
}

std::string StandardGenerator::minifyCode(const std::string& code, const std::string& language) {
    // TODO: 实现代码压缩
    // 简单实现：移除多余空白
    std::stringstream ss;
    bool inString = false;
    char stringChar = 0;
    bool lastWasSpace = false;
    
    for (size_t i = 0; i < code.length(); ++i) {
        char c = code[i];
        
        if (!inString && (c == '"' || c == '\'')) {
            inString = true;
            stringChar = c;
            ss << c;
        } else if (inString && c == stringChar && (i == 0 || code[i-1] != '\\')) {
            inString = false;
            ss << c;
        } else if (inString) {
            ss << c;
        } else if (std::isspace(c)) {
            if (!lastWasSpace) {
                ss << ' ';
                lastWasSpace = true;
            }
        } else {
            ss << c;
            lastWasSpace = false;
        }
    }
    
    return ss.str();
}

std::string StandardGenerator::prettifyCode(const std::string& code, const std::string& language) {
    // TODO: 实现代码美化
    // 暂时返回原始代码
    return code;
}

} // namespace CHTL