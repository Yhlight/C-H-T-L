#ifndef CHTL_CSS_TYPES_H
#define CHTL_CSS_TYPES_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace chtl {
namespace css {

// CSS Token类型
enum class CssTokenType {
    // 基础符号
    LEFT_BRACE,      // {
    RIGHT_BRACE,     // }
    LEFT_PAREN,      // (
    RIGHT_PAREN,     // )
    LEFT_BRACKET,    // [
    RIGHT_BRACKET,   // ]
    SEMICOLON,       // ;
    COLON,           // :
    COMMA,           // ,
    DOT,             // .
    HASH,            // #
    AT,              // @
    AMPERSAND,       // &
    STAR,            // *
    PLUS,            // +
    MINUS,           // -
    SLASH,           // /
    PERCENT,         // %
    EXCLAMATION,     // !
    GREATER_THAN,    // >
    TILDE,           // ~
    PIPE,            // |
    CARET,           // ^
    DOLLAR,          // $
    EQUALS,          // =
    
    // 复合符号
    DOUBLE_COLON,    // ::
    IMPORTANT,       // !important
    COMBINATOR,      // 组合器 (>, +, ~)
    
    // 标识符和值
    IDENTIFIER,      // 标识符
    STRING,          // 字符串
    NUMBER,          // 数字
    DIMENSION,       // 带单位的数字
    PERCENTAGE,      // 百分比
    URL,             // url()
    FUNCTION,        // 函数调用
    HEX_COLOR,       // 十六进制颜色
    
    // 现代CSS特性
    CSS_VARIABLE,    // --variable
    VAR_FUNCTION,    // var()
    CALC_FUNCTION,   // calc()
    
    // 注释
    COMMENT,         // /* */
    
    // 特殊
    WHITESPACE,      // 空白
    NEWLINE,         // 换行
    EOF_TOKEN,       // 文件结束
    UNKNOWN          // 未知
};

// CSS块类型
enum class CssBlockType {
    RULE_SET,        // 普通规则集 selector { ... }
    AT_RULE,         // @规则
    MEDIA_QUERY,     // @media
    KEYFRAMES,       // @keyframes
    IMPORT,          // @import
    CHARSET,         // @charset
    NAMESPACE,       // @namespace
    SUPPORTS,        // @supports
    PAGE,            // @page
    FONT_FACE,       // @font-face
    CONTAINER,       // @container (容器查询)
    LAYER,           // @layer (级联层)
    PROPERTY,        // @property (CSS属性定义)
    CUSTOM_PROPERTY, // CSS变量定义
    NESTED_RULE,     // 嵌套规则（CSS Nesting）
    UNKNOWN          // 未知块
};

// CSS现代特性
struct CssModernFeatures {
    bool cssVariables = false;          // CSS自定义属性
    bool cssGrid = false;               // Grid布局
    bool cssFlexbox = false;            // Flexbox布局
    bool cssNesting = false;            // CSS嵌套
    bool containerQueries = false;      // 容器查询
    bool cascadeLayers = false;         // 级联层
    bool hasOperator = false;           // :has()选择器
    bool whereIsOperator = false;       // :where()/:is()选择器
    bool logicalProperties = false;     // 逻辑属性
    bool aspectRatio = false;           // aspect-ratio属性
    bool colorFunction = false;         // color()函数
    bool subgrid = false;               // subgrid
    std::vector<std::string> unknownAtRules;  // 未知的@规则
};

// CSS块信息
struct CssBlock {
    CssBlockType type;
    std::string selector;                    // 选择器或@规则名
    std::string content;                     // 块内容
    size_t startLine;
    size_t endLine;
    size_t startColumn;
    size_t endColumn;
    std::vector<std::shared_ptr<CssBlock>> nestedBlocks;  // 嵌套块
    std::unordered_map<std::string, std::string> properties;  // 属性键值对
    
    CssBlock(CssBlockType t = CssBlockType::UNKNOWN) 
        : type(t), startLine(0), endLine(0), startColumn(0), endColumn(0) {}
};

// CSS分析结果
struct CssAnalysisResult {
    std::vector<std::shared_ptr<CssBlock>> blocks;
    std::vector<std::string> selectors;        // 所有选择器
    std::vector<std::string> classNames;       // 所有类名
    std::vector<std::string> idNames;          // 所有ID
    std::unordered_map<std::string, std::string> customProperties; // CSS变量及其值
    std::vector<std::string> mediaQueries;     // 媒体查询
    std::vector<std::string> imports;          // @import语句
    CssModernFeatures modernFeatures;          // 现代CSS特性使用情况
    
    // 统计信息
    size_t ruleCount = 0;
    size_t mediaQueryCount = 0;
    size_t keyframesCount = 0;
    size_t customPropertyCount = 0;
    
    bool hasErrors = false;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

} // namespace css
} // namespace chtl

#endif // CHTL_CSS_TYPES_H