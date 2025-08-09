#ifndef CHTL_CSS_TYPES_H
#define CHTL_CSS_TYPES_H

#include <string>
#include <vector>
#include <memory>

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
    
    // 复合符号
    DOUBLE_COLON,    // ::
    IMPORTANT,       // !important
    
    // 标识符和值
    IDENTIFIER,      // 标识符
    STRING,          // 字符串
    NUMBER,          // 数字
    URL,             // url()
    FUNCTION,        // 函数调用
    
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
    CUSTOM_PROPERTY, // CSS变量
    UNKNOWN          // 未知块
};

// CSS块信息
struct CssBlock {
    CssBlockType type;
    std::string selector;           // 选择器或@规则名
    std::string content;            // 块内容
    size_t startLine;
    size_t endLine;
    size_t startColumn;
    size_t endColumn;
    std::vector<std::shared_ptr<CssBlock>> nestedBlocks;  // 嵌套块
    
    CssBlock(CssBlockType t = CssBlockType::UNKNOWN) 
        : type(t), startLine(0), endLine(0), startColumn(0), endColumn(0) {}
};

// CSS分析结果
struct CssAnalysisResult {
    std::vector<std::shared_ptr<CssBlock>> blocks;
    std::vector<std::string> selectors;        // 所有选择器
    std::vector<std::string> classNames;       // 所有类名
    std::vector<std::string> idNames;          // 所有ID
    std::vector<std::string> customProperties; // CSS变量
    std::vector<std::string> mediaQueries;     // 媒体查询
    std::vector<std::string> imports;          // @import语句
    bool hasErrors;
    std::vector<std::string> errors;
};

} // namespace css
} // namespace chtl

#endif // CHTL_CSS_TYPES_H