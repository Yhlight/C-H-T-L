#include "v2/Lexer/Token.h"
#include <sstream>

namespace chtl::v2 {

std::string Token::toString() const {
    std::stringstream ss;
    ss << "Token(";
    ss << getTokenTypeName(type);
    if (!value.empty()) {
        ss << ", \"" << value << "\"";
    }
    ss << ", " << line << ":" << column;
    
    // 添加元数据信息
    if (metadata.isHtmlTag) {
        ss << ", HTML";
    }
    if (metadata.isCssProperty) {
        ss << ", CSS";
    }
    if (metadata.isTemplateParam) {
        ss << ", PARAM";
    }
    if (!metadata.contextHint.empty()) {
        ss << ", " << metadata.contextHint;
    }
    
    ss << ")";
    return ss.str();
}

const char* getTokenTypeName(TokenType type) {
    switch (type) {
        // 字面量
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";
        
        // 关键字
        case TokenType::STYLE: return "STYLE";
        case TokenType::SCRIPT: return "SCRIPT";
        case TokenType::TEXT: return "TEXT";
        case TokenType::INHERIT: return "INHERIT";
        case TokenType::DELETE: return "DELETE";
        case TokenType::INSERT: return "INSERT";
        
        // 声明标记
        case TokenType::TEMPLATE: return "TEMPLATE";
        case TokenType::CUSTOM: return "CUSTOM";
        case TokenType::IMPORT: return "IMPORT";
        case TokenType::CONFIGURATION: return "CONFIGURATION";
        case TokenType::ORIGIN: return "ORIGIN";
        case TokenType::EXPORT: return "EXPORT";
        case TokenType::INFO: return "INFO";
        
        // 引用标记
        case TokenType::AT_ELEMENT: return "AT_ELEMENT";
        case TokenType::AT_STYLE: return "AT_STYLE";
        case TokenType::AT_VAR: return "AT_VAR";
        case TokenType::AT_HTML: return "AT_HTML";
        case TokenType::AT_JAVASCRIPT: return "AT_JAVASCRIPT";
        case TokenType::AT_CHTL: return "AT_CHTL";
        case TokenType::AT_CJMOD: return "AT_CJMOD";
        
        // 操作符
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COLON: return "COLON";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::HASH: return "HASH";
        case TokenType::AT: return "AT";
        case TokenType::EQUALS: return "EQUALS";
        case TokenType::ARROW: return "ARROW";
        
        // CSS 特定
        case TokenType::CSS_PROPERTY: return "CSS_PROPERTY";
        case TokenType::CSS_VALUE: return "CSS_VALUE";
        case TokenType::CSS_UNIT: return "CSS_UNIT";
        
        // CHTL-JS 特定
        case TokenType::DOUBLE_LEFT_BRACE: return "DOUBLE_LEFT_BRACE";
        case TokenType::DOUBLE_RIGHT_BRACE: return "DOUBLE_RIGHT_BRACE";
        case TokenType::AMPERSAND: return "AMPERSAND";
        
        // 特殊
        case TokenType::WHITESPACE: return "WHITESPACE";
        case TokenType::NEWLINE: return "NEWLINE";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::EOF_TOKEN: return "EOF_TOKEN";
        
        // 错误
        case TokenType::UNKNOWN: return "UNKNOWN";
        case TokenType::ERROR: return "ERROR";
        
        default: return "???";
    }
}

} // namespace chtl::v2