#ifndef CHTL_ERROR_TYPES_H
#define CHTL_ERROR_TYPES_H

namespace chtl {

// 错误严重程度
enum class ErrorSeverity {
    INFO,       // 信息
    WARNING,    // 警告
    ERROR,      // 错误
    FATAL       // 致命错误
};

// 错误类型
enum class ErrorType {
    // 通用错误
    GENERAL,  // 通用错误
    
    // 词法错误 (100-199)
    LEXER_UNEXPECTED_CHAR = 100,
    LEXER_UNKNOWN_CHARACTER = 1000,
    LEXER_UNTERMINATED_STRING,
    LEXER_UNTERMINATED_COMMENT,
    LEXER_INVALID_NUMBER,
    LEXER_INVALID_ESCAPE_SEQUENCE,
    
    // 语法错误 (2000-2999)
    PARSER_UNEXPECTED_TOKEN = 2000,
    PARSER_EXPECTED_TOKEN,
    PARSER_UNCLOSED_BLOCK,
    PARSER_INVALID_SYNTAX,
    PARSER_DUPLICATE_ATTRIBUTE,
    PARSER_MISSING_REQUIRED_ATTRIBUTE,
    PARSER_INVALID_IMPORT,
    PARSER_INVALID_EXPORT,
    PARSER_INVALID_IDENTIFIER,
    PARSER_UNEXPECTED_EOF,
    
    // 语义错误 (3000-3999)
    SEMANTIC_UNDEFINED_REFERENCE = 3000,
    SEMANTIC_DUPLICATE_DEFINITION,
    SEMANTIC_TYPE_MISMATCH,
    SEMANTIC_INVALID_OPERATION,
    SEMANTIC_CIRCULAR_DEPENDENCY,
    SEMANTIC_INCOMPATIBLE_VERSION,
    SEMANTIC_MISSING_REQUIRED_FIELD,
    SEMANTIC_INVALID_PROP_TYPE,
    SEMANTIC_UNUSED_VARIABLE,
    SEMANTIC_UNREACHABLE_CODE,
    
    // 类型错误 (4000-4999)
    TYPE_MISMATCH = 4000,
    TYPE_UNDEFINED,
    TYPE_INVALID_CAST,
    TYPE_MISSING_ANNOTATION,
    TYPE_INVALID_GENERIC,
    TYPE_CONSTRAINT_VIOLATION,
    
    // 模块错误 (5000-5999)
    MODULE_NOT_FOUND = 5000,
    MODULE_LOAD_FAILED,
    MODULE_INVALID_EXPORT,
    MODULE_INVALID_IMPORT,
    MODULE_CIRCULAR_IMPORT,
    MODULE_VERSION_MISMATCH,
    MODULE_ACCESS_VIOLATION,
    
    // 运行时错误 (6000-6999)
    RUNTIME_NULL_REFERENCE = 6000,
    RUNTIME_INDEX_OUT_OF_BOUNDS,
    RUNTIME_DIVISION_BY_ZERO,
    RUNTIME_STACK_OVERFLOW,
    RUNTIME_OUT_OF_MEMORY,
    RUNTIME_TYPE_ERROR,
    RUNTIME_REFERENCE_ERROR,
    
    // 生成器错误 (7000-7999)
    GENERATOR_INVALID_TARGET = 7000,
    GENERATOR_UNSUPPORTED_FEATURE,
    GENERATOR_TEMPLATE_ERROR,
    GENERATOR_OUTPUT_ERROR,
    GENERATOR_OPTIMIZATION_ERROR,
    
    // 配置错误 (8000-8999)
    CONFIG_INVALID_OPTION = 8000,
    CONFIG_MISSING_REQUIRED,
    CONFIG_PARSE_ERROR,
    CONFIG_VALIDATION_ERROR,
    
    // 系统错误 (9000-9999)
    SYSTEM_FILE_NOT_FOUND = 9000,
    SYSTEM_PERMISSION_DENIED,
    SYSTEM_IO_ERROR,
    SYSTEM_MEMORY_ERROR,
    SYSTEM_UNKNOWN_ERROR
};

// 错误类别
enum class ErrorCategory {
    LEXICAL,
    SYNTACTIC,
    SEMANTIC,
    TYPE,
    MODULE,
    RUNTIME,
    GENERATOR,
    CONFIG,
    SYSTEM
};

// 获取错误类别
inline ErrorCategory getErrorCategory(ErrorType type) {
    int code = static_cast<int>(type);
    if (code >= 1000 && code < 2000) return ErrorCategory::LEXICAL;
    if (code >= 2000 && code < 3000) return ErrorCategory::SYNTACTIC;
    if (code >= 3000 && code < 4000) return ErrorCategory::SEMANTIC;
    if (code >= 4000 && code < 5000) return ErrorCategory::TYPE;
    if (code >= 5000 && code < 6000) return ErrorCategory::MODULE;
    if (code >= 6000 && code < 7000) return ErrorCategory::RUNTIME;
    if (code >= 7000 && code < 8000) return ErrorCategory::GENERATOR;
    if (code >= 8000 && code < 9000) return ErrorCategory::CONFIG;
    return ErrorCategory::SYSTEM;
}

// 错误类型到字符串转换
const char* errorTypeToString(ErrorType type);
const char* errorSeverityToString(ErrorSeverity severity);
const char* errorCategoryToString(ErrorCategory category);

} // namespace chtl

#endif // CHTL_ERROR_TYPES_H