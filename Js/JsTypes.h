#ifndef CHTL_JS_TYPES_H
#define CHTL_JS_TYPES_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

namespace chtl {
namespace js {

// JavaScript Token类型
enum class JsTokenType {
    // 关键字
    CONST, LET, VAR,
    FUNCTION, CLASS, ASYNC, AWAIT,
    IF, ELSE, FOR, WHILE, DO,
    SWITCH, CASE, DEFAULT, BREAK, CONTINUE,
    RETURN, THROW, TRY, CATCH, FINALLY,
    IMPORT, EXPORT, FROM, AS,
    NEW, DELETE, TYPEOF, INSTANCEOF,
    THIS, SUPER,
    
    // 字面量
    IDENTIFIER,
    NUMBER,
    STRING,
    TEMPLATE_LITERAL,
    REGEX,
    TRUE, FALSE, NULL_LITERAL, UNDEFINED,
    
    // 运算符
    PLUS, MINUS, STAR, SLASH, PERCENT,
    EQUALS, PLUS_EQUALS, MINUS_EQUALS,
    EQUALS_EQUALS, NOT_EQUALS,
    EQUALS_EQUALS_EQUALS, NOT_EQUALS_EQUALS,
    LESS_THAN, GREATER_THAN,
    LESS_EQUALS, GREATER_EQUALS,
    AND_AND, OR_OR, NOT,
    AMPERSAND, PIPE, CARET, TILDE,
    LEFT_SHIFT, RIGHT_SHIFT, UNSIGNED_RIGHT_SHIFT,
    PLUS_PLUS, MINUS_MINUS,
    ARROW,  // =>
    SPREAD, // ...
    
    // 符号
    LEFT_BRACE, RIGHT_BRACE,
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACKET, RIGHT_BRACKET,
    SEMICOLON, COMMA, DOT,
    COLON, QUESTION,
    
    // 注释
    SINGLE_LINE_COMMENT,
    MULTI_LINE_COMMENT,
    
    // 特殊
    WHITESPACE,
    NEWLINE,
    EOF_TOKEN,
    UNKNOWN
};

// JavaScript块类型
enum class JsBlockType {
    FUNCTION_DECLARATION,
    FUNCTION_EXPRESSION,
    ARROW_FUNCTION,
    CLASS_DECLARATION,
    METHOD_DEFINITION,
    BLOCK_STATEMENT,
    OBJECT_LITERAL,
    ARRAY_LITERAL,
    IF_STATEMENT,
    FOR_LOOP,
    WHILE_LOOP,
    SWITCH_STATEMENT,
    TRY_CATCH,
    MODULE_IMPORT,
    MODULE_EXPORT,
    CHTL_EXTENSION,    // CHTL特殊扩展
    UNKNOWN
};

// JavaScript块信息
struct JsBlock {
    JsBlockType type;
    std::string name;               // 函数名、类名等
    std::string content;            // 块内容
    size_t startLine;
    size_t endLine;
    size_t startColumn;
    size_t endColumn;
    std::vector<std::string> parameters;    // 函数参数
    std::vector<std::shared_ptr<JsBlock>> nestedBlocks;  // 嵌套块
    
    JsBlock(JsBlockType t = JsBlockType::UNKNOWN)
        : type(t), startLine(0), endLine(0), startColumn(0), endColumn(0) {}
};

// JavaScript分析结果
struct JsAnalysisResult {
    std::vector<std::shared_ptr<JsBlock>> blocks;
    std::vector<std::string> functions;         // 所有函数名
    std::vector<std::string> classes;           // 所有类名
    std::vector<std::string> variables;         // 变量声明
    std::vector<std::string> imports;           // import语句
    std::vector<std::string> exports;           // export语句
    std::unordered_set<std::string> identifiers; // 所有标识符
    std::vector<std::string> chtlReferences;    // CHTL特殊引用
    bool hasErrors;
    std::vector<std::string> errors;
    
    // 统计信息
    size_t functionCount = 0;
    size_t classCount = 0;
    size_t asyncFunctionCount = 0;
    bool usesES6Features = false;
    bool usesChtlExtensions = false;
};

} // namespace js
} // namespace chtl

#endif // CHTL_JS_TYPES_H