#ifndef CHTL_STANDALONE_CSS_PARSER_H
#define CHTL_STANDALONE_CSS_PARSER_H

#include "ParserRuntime.h"
#include <regex>
#include <sstream>

namespace chtl {
namespace parser {

// 简化的CSS解析器 - 支持原生CSS
class CSSParser {
public:
    struct CSSRule {
        std::vector<std::string> selectors;
        std::map<std::string, std::string> properties;
        std::string toString() const {
            std::stringstream ss;
            for (size_t i = 0; i < selectors.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << selectors[i];
            }
            ss << " {\n";
            for (const auto& [prop, value] : properties) {
                ss << "  " << prop << ": " << value << ";\n";
            }
            ss << "}\n";
            return ss.str();
        }
    };
    
    struct CSSAtRule {
        std::string type;     // @media, @keyframes, @import等
        std::string condition;
        std::vector<CSSRule> rules;
        std::string content;  // 对于@import等简单规则
    };
    
    CSSParser(const std::string& css) : input_(css), pos_(0) {}
    
    std::string parse() {
        std::stringstream output;
        skipWhitespace();
        
        while (pos_ < input_.size()) {
            skipWhitespace();
            if (pos_ >= input_.size()) break;
            
            if (peek() == '@') {
                // @规则
                auto atRule = parseAtRule();
                output << formatAtRule(atRule);
            } else if (peek() == '/' && peekNext() == '*') {
                // 注释
                output << parseComment() << "\n";
            } else {
                // 普通规则
                auto rule = parseRule();
                output << rule.toString();
            }
            
            skipWhitespace();
        }
        
        return output.str();
    }
    
private:
    std::string input_;
    size_t pos_;
    
    char peek() {
        return pos_ < input_.size() ? input_[pos_] : '\0';
    }
    
    char peekNext() {
        return pos_ + 1 < input_.size() ? input_[pos_ + 1] : '\0';
    }
    
    char advance() {
        return pos_ < input_.size() ? input_[pos_++] : '\0';
    }
    
    void skipWhitespace() {
        while (pos_ < input_.size() && std::isspace(input_[pos_])) {
            pos_++;
        }
    }
    
    std::string parseComment() {
        std::string comment;
        advance(); advance(); // Skip /*
        comment = "/*";
        
        while (pos_ < input_.size() - 1) {
            if (peek() == '*' && peekNext() == '/') {
                comment += "*/";
                advance(); advance();
                break;
            }
            comment += advance();
        }
        
        return comment;
    }
    
    CSSRule parseRule() {
        CSSRule rule;
        
        // 解析选择器
        std::string selector;
        while (peek() != '{' && pos_ < input_.size()) {
            if (peek() == ',') {
                rule.selectors.push_back(trim(selector));
                selector.clear();
                advance(); // skip ,
                skipWhitespace();
            } else {
                selector += advance();
            }
        }
        if (!selector.empty()) {
            rule.selectors.push_back(trim(selector));
        }
        
        advance(); // skip {
        skipWhitespace();
        
        // 解析属性
        while (peek() != '}' && pos_ < input_.size()) {
            skipWhitespace();
            
            if (peek() == '/' && peekNext() == '*') {
                parseComment(); // 跳过注释
                continue;
            }
            
            // 属性名
            std::string propName;
            while (peek() != ':' && pos_ < input_.size()) {
                propName += advance();
            }
            propName = trim(propName);
            
            if (peek() == ':') {
                advance(); // skip :
                skipWhitespace();
                
                // 属性值
                std::string propValue;
                int parenCount = 0;
                while (pos_ < input_.size()) {
                    char c = peek();
                    if (c == '(') parenCount++;
                    else if (c == ')') parenCount--;
                    else if (c == ';' && parenCount == 0) break;
                    else if (c == '}' && parenCount == 0) break;
                    propValue += advance();
                }
                
                rule.properties[propName] = trim(propValue);
                
                if (peek() == ';') advance();
            }
            
            skipWhitespace();
        }
        
        if (peek() == '}') advance();
        
        return rule;
    }
    
    CSSAtRule parseAtRule() {
        CSSAtRule atRule;
        
        advance(); // skip @
        
        // 解析类型
        while (std::isalpha(peek()) || peek() == '-') {
            atRule.type += advance();
        }
        
        skipWhitespace();
        
        // 解析条件或URL
        if (atRule.type == "import") {
            // @import url(...) 或 @import "..."
            std::string importContent;
            while (peek() != ';' && pos_ < input_.size()) {
                importContent += advance();
            }
            atRule.content = importContent;
            if (peek() == ';') advance();
        } else if (atRule.type == "media" || atRule.type == "supports") {
            // 解析媒体查询条件
            int parenCount = 0;
            while (peek() != '{' && pos_ < input_.size()) {
                char c = peek();
                if (c == '(') parenCount++;
                else if (c == ')') parenCount--;
                atRule.condition += advance();
            }
            atRule.condition = trim(atRule.condition);
            
            advance(); // skip {
            skipWhitespace();
            
            // 解析内部规则
            while (peek() != '}' && pos_ < input_.size()) {
                skipWhitespace();
                if (peek() == '}') break;
                atRule.rules.push_back(parseRule());
                skipWhitespace();
            }
            
            if (peek() == '}') advance();
        } else if (atRule.type == "keyframes") {
            // 解析动画名称
            skipWhitespace();
            while (peek() != '{' && pos_ < input_.size()) {
                atRule.condition += advance();
            }
            atRule.condition = trim(atRule.condition);
            
            // 简化处理：将整个内容作为content
            advance(); // skip {
            int braceCount = 1;
            std::string content;
            while (braceCount > 0 && pos_ < input_.size()) {
                char c = advance();
                if (c == '{') braceCount++;
                else if (c == '}') {
                    braceCount--;
                    if (braceCount == 0) break;
                }
                content += c;
            }
            atRule.content = content;
        }
        
        return atRule;
    }
    
    std::string formatAtRule(const CSSAtRule& atRule) {
        std::stringstream ss;
        ss << "@" << atRule.type;
        
        if (!atRule.condition.empty()) {
            ss << " " << atRule.condition;
        }
        
        if (!atRule.content.empty()) {
            if (atRule.type == "import") {
                ss << " " << atRule.content << ";\n";
            } else {
                ss << " {\n" << atRule.content << "}\n";
            }
        } else if (!atRule.rules.empty()) {
            ss << " {\n";
            for (const auto& rule : atRule.rules) {
                ss << "  " << rule.toString();
            }
            ss << "}\n";
        }
        
        return ss.str();
    }
    
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, last - first + 1);
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_CSS_PARSER_H