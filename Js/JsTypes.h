#ifndef CHTL_JS_TYPES_H
#define CHTL_JS_TYPES_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>

namespace chtl {
namespace js {

// JavaScript Token类型
enum class JsTokenType {
    // ES6+ 关键字
    CONST, LET, VAR,
    FUNCTION, CLASS, ASYNC, AWAIT,
    IF, ELSE, FOR, WHILE, DO,
    SWITCH, CASE, DEFAULT, BREAK, CONTINUE,
    RETURN, THROW, TRY, CATCH, FINALLY,
    IMPORT, EXPORT, FROM, AS,
    NEW, DELETE, TYPEOF, INSTANCEOF, IN, OF,
    THIS, SUPER,
    YIELD, STATIC, EXTENDS,
    
    // ES2022+ 特性
    PRIVATE_FIELD,   // #privateField
    TOP_LEVEL_AWAIT, // 顶层await
    USING,           // using声明 (ES2024提案)
    
    // 字面量
    IDENTIFIER,
    NUMBER,
    BIGINT,          // 123n
    STRING,
    TEMPLATE_LITERAL,
    REGEX,
    TRUE, FALSE, NULL_LITERAL, UNDEFINED,
    
    // 运算符
    PLUS, MINUS, STAR, SLASH, PERCENT, EXPONENT, // **
    EQUALS, PLUS_EQUALS, MINUS_EQUALS,
    EQUALS_EQUALS, NOT_EQUALS,
    EQUALS_EQUALS_EQUALS, NOT_EQUALS_EQUALS,
    LESS_THAN, GREATER_THAN,
    LESS_EQUALS, GREATER_EQUALS,
    AND_AND, OR_OR, NOT,
    NULLISH_COALESCING, // ??
    OPTIONAL_CHAINING,  // ?.
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
    AT_SIGN,  // @ (装饰器)
    
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
    // 函数相关
    FUNCTION_DECLARATION,
    FUNCTION_EXPRESSION,
    ARROW_FUNCTION,
    ASYNC_FUNCTION,
    GENERATOR_FUNCTION,
    ASYNC_GENERATOR,
    
    // 类相关
    CLASS_DECLARATION,
    CLASS_EXPRESSION,
    METHOD_DEFINITION,
    CONSTRUCTOR,
    GETTER,
    SETTER,
    STATIC_METHOD,
    PRIVATE_METHOD,
    STATIC_BLOCK,      // ES2022
    
    // 语句
    BLOCK_STATEMENT,
    IF_STATEMENT,
    FOR_LOOP,
    FOR_IN_LOOP,
    FOR_OF_LOOP,
    WHILE_LOOP,
    DO_WHILE_LOOP,
    SWITCH_STATEMENT,
    TRY_CATCH,
    
    // 模块
    MODULE_IMPORT,
    MODULE_EXPORT,
    DYNAMIC_IMPORT,
    
    // 字面量
    OBJECT_LITERAL,
    ARRAY_LITERAL,
    TEMPLATE_LITERAL_EXPR,
    
    // ES2022+ 特性
    FIELD_DECLARATION,
    PRIVATE_FIELD_DECLARATION,
    DECORATOR,          // 装饰器
    
    UNKNOWN
};

// ES特性级别
enum class EsVersion {
    ES5,
    ES6,     // ES2015
    ES2016,
    ES2017,
    ES2018,
    ES2019,
    ES2020,
    ES2021,
    ES2022,
    ES2023,
    ESNEXT   // 提案阶段特性
};

// JavaScript现代特性
struct JsModernFeatures {
    // ES6/ES2015
    bool arrowFunctions = false;
    bool classes = false;
    bool templateLiterals = false;
    bool destructuring = false;
    bool defaultParameters = false;
    bool restSpread = false;
    bool letConst = false;
    bool promises = false;
    bool modules = false;
    
    // ES2017+
    bool asyncAwait = false;
    bool objectRestSpread = false;
    
    // ES2018+
    bool asyncIterators = false;
    bool promiseFinally = false;
    
    // ES2019+
    bool optionalCatchBinding = false;
    bool arrayFlat = false;
    
    // ES2020+
    bool nullishCoalescing = false;
    bool optionalChaining = false;
    bool bigInt = false;
    bool dynamicImport = false;
    bool globalThis = false;
    
    // ES2021+
    bool numericSeparators = false;
    bool promiseAny = false;
    bool stringReplaceAll = false;
    bool weakRefs = false;
    
    // ES2022+
    bool topLevelAwait = false;
    bool privateFields = false;
    bool privateMethodsAccessors = false;
    bool staticClassFields = false;
    bool staticBlocks = false;
    bool errorCause = false;
    bool arrayAt = false;
    bool regexpMatchIndices = false;
    
    // ES2023+
    bool arrayFindLast = false;
    bool hashbang = false;
    bool symbolsAsWeakMapKeys = false;
    
    // 提案阶段
    bool decorators = false;
    bool pipelineOperator = false;
    bool recordTuple = false;
    bool patternMatching = false;
    
    EsVersion highestVersionUsed = EsVersion::ES5;
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
    std::vector<std::string> parameters;              // 函数参数
    std::vector<std::shared_ptr<JsBlock>> nestedBlocks;  // 嵌套块
    std::unordered_map<std::string, std::string> metadata; // 额外元数据
    
    JsBlock(JsBlockType t = JsBlockType::UNKNOWN)
        : type(t), startLine(0), endLine(0), startColumn(0), endColumn(0) {}
};

// JavaScript分析结果
struct JsAnalysisResult {
    std::vector<std::shared_ptr<JsBlock>> blocks;
    std::vector<std::string> functions;         // 所有函数名
    std::vector<std::string> classes;           // 所有类名
    std::vector<std::string> variables;         // 变量声明
    std::vector<std::string> constants;         // 常量声明
    std::vector<std::string> imports;           // import语句
    std::vector<std::string> exports;           // export语句
    std::unordered_set<std::string> identifiers; // 所有标识符
    std::unordered_set<std::string> dependencies; // 外部依赖
    JsModernFeatures modernFeatures;            // 现代特性使用情况
    
    // 统计信息
    size_t functionCount = 0;
    size_t classCount = 0;
    size_t asyncFunctionCount = 0;
    size_t lineCount = 0;
    size_t statementCount = 0;
    
    // 代码质量指标
    size_t cyclomaticComplexity = 0;
    size_t maxNestingDepth = 0;
    
    bool hasErrors = false;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

} // namespace js
} // namespace chtl

#endif // CHTL_JS_TYPES_H