#pragma once

#include "v2/Css/CssTokenizer.h"
#include <memory>
#include <variant>
#include <map>

namespace chtl::v2::css {

// 前向声明
struct CssRule;
struct CssDeclaration;
struct CssSelector;

/**
 * CSS 值类型
 */
using CssValue = std::variant<
    std::string,           // 标识符、字符串
    double,               // 数字
    std::pair<double, std::string>,  // 带单位的数字
    std::vector<std::variant<std::string, double>>  // 复合值
>;

/**
 * CSS 选择器类型
 */
enum class SelectorType {
    ELEMENT,          // 元素选择器
    CLASS,            // 类选择器
    ID,               // ID选择器
    ATTRIBUTE,        // 属性选择器
    PSEUDO_CLASS,     // 伪类
    PSEUDO_ELEMENT,   // 伪元素
    UNIVERSAL,        // 通配符
    COMBINATOR        // 组合器
};

/**
 * CSS 组合器类型
 */
enum class CombinatorType {
    DESCENDANT,       // 空格
    CHILD,            // >
    ADJACENT,         // +
    SIBLING,          // ~
    NONE
};

/**
 * CSS 选择器
 */
struct CssSelector {
    SelectorType type;
    std::string value;
    
    // 属性选择器特有
    std::string attribute;
    std::string op;  // =, ~=, |=, ^=, $=, *=
    std::string attributeValue;
    
    // 伪类/伪元素参数
    std::string argument;
    
    // 组合器
    CombinatorType combinator = CombinatorType::NONE;
    std::unique_ptr<CssSelector> next;
    
    std::string toString() const;
    int specificity() const;
};

/**
 * CSS 声明
 */
struct CssDeclaration {
    std::string property;
    CssValue value;
    bool important = false;
    
    std::string toString() const;
};

/**
 * CSS 规则类型
 */
enum class RuleType {
    STYLE_RULE,       // 普通样式规则
    AT_RULE,          // @规则
    MEDIA_RULE,       // @media
    IMPORT_RULE,      // @import
    KEYFRAMES_RULE,   // @keyframes
    SUPPORTS_RULE,    // @supports
    PAGE_RULE,        // @page
    FONT_FACE_RULE,   // @font-face
    NAMESPACE_RULE    // @namespace
};

/**
 * CSS 规则
 */
struct CssRule {
    RuleType type;
    
    // 样式规则
    std::vector<std::unique_ptr<CssSelector>> selectors;
    std::vector<CssDeclaration> declarations;
    
    // @规则特有
    std::string atKeyword;
    std::string prelude;  // @规则的条件部分
    std::vector<std::unique_ptr<CssRule>> nestedRules;
    
    std::string toString() const;
};

/**
 * CSS 样式表
 */
struct CssStylesheet {
    std::vector<std::unique_ptr<CssRule>> rules;
    std::map<std::string, std::string> namespaces;
    
    std::string toString() const;
};

/**
 * CSS 解析结果
 */
struct CssParseResult {
    std::unique_ptr<CssStylesheet> stylesheet;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

/**
 * CSS 解析器
 */
class CssParser {
public:
    explicit CssParser(const std::string& input);
    
    /**
     * 解析 CSS
     */
    CssParseResult parse();
    
    /**
     * 解析单个规则（用于测试）
     */
    std::unique_ptr<CssRule> parseRule();
    
    /**
     * 解析选择器列表
     */
    std::vector<std::unique_ptr<CssSelector>> parseSelectorList();
    
private:
    /**
     * 解析样式表
     */
    std::unique_ptr<CssStylesheet> parseStylesheet();
    
    /**
     * 解析 @规则
     */
    std::unique_ptr<CssRule> parseAtRule();
    
    /**
     * 解析样式规则
     */
    std::unique_ptr<CssRule> parseStyleRule();
    
    /**
     * 解析选择器
     */
    std::unique_ptr<CssSelector> parseSelector();
    
    /**
     * 解析简单选择器
     */
    std::unique_ptr<CssSelector> parseSimpleSelector();
    
    /**
     * 解析属性选择器
     */
    void parseAttributeSelector(CssSelector& selector);
    
    /**
     * 解析伪类/伪元素
     */
    void parsePseudoSelector(CssSelector& selector);
    
    /**
     * 解析声明块
     */
    std::vector<CssDeclaration> parseDeclarationBlock();
    
    /**
     * 解析声明
     */
    CssDeclaration parseDeclaration();
    
    /**
     * 解析值
     */
    CssValue parseValue();
    
    /**
     * 解析函数值
     */
    CssValue parseFunctionValue(const std::string& funcName);
    
    /**
     * 辅助方法
     */
    bool match(CssTokenType type);
    bool consume(CssTokenType type);
    CssToken advance();
    CssToken peek();
    bool isAtEnd();
    void synchronize();
    
    void error(const std::string& message);
    void warning(const std::string& message);
    
private:
    CssTokenizer tokenizer_;
    CssToken current_;
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
};

} // namespace chtl::v2::css