#include "State/ChtlState.h"
#include "State/CssState.h"
#include "State/JsState.h"
#include "State/ChtlJsState.h"
#include "Lexer/BasicLexer.h"
#include <algorithm>

namespace chtl {

ChtlState::ChtlState(BasicLexer* lexer) 
    : BasicState(StateType::CHTL, "ChtlState", lexer),
      subState_(SubState::INITIAL),
      startLine_(1),
      startColumn_(1),
      inStyleBlock_(false),
      inScriptBlock_(false),
      braceDepth_(0),
      inTextBlock_(false),
      inCssProperty_(false) {
    // 暂时使用这些成员变量避免编译警告
    (void)braceDepth_;
    (void)inTextBlock_;
}

std::shared_ptr<BasicState> ChtlState::handleChar(char ch) {
    switch (subState_) {
        case SubState::INITIAL:
            return handleInitial(ch);
        case SubState::IDENTIFIER:
            return handleIdentifier(ch);
        case SubState::STRING_SINGLE:
            return handleStringSingle(ch);
        case SubState::STRING_DOUBLE:
            return handleStringDouble(ch);
        case SubState::UNQUOTED_LITERAL:
            return handleUnquotedLiteral(ch);
        case SubState::NUMBER:
            return handleNumber(ch);
        case SubState::OPERATOR:
            return handleOperator(ch);
        case SubState::COMMENT_SINGLE:
            return handleCommentSingle(ch);
        case SubState::COMMENT_MULTI:
            return handleCommentMulti(ch);
        case SubState::HTML_COMMENT:
            return handleHtmlComment(ch);
        case SubState::AT_PREFIX:
            return handleAtPrefix(ch);
        case SubState::SPECIAL_MARKER:
            return handleSpecialMarker(ch);
        case SubState::WHITESPACE:
            return handleWhitespace(ch);
        case SubState::IN_TEXT_BLOCK:
            return handleTextBlock(ch);
        case SubState::CSS_PROPERTY_NAME:
            return handleCssPropertyName(ch);
        case SubState::CSS_PROPERTY_VALUE:
            return handleCssPropertyValue(ch);
        case SubState::CSS_COLOR_VALUE:
            return handleCssColorValue(ch);
    }
    
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleInitial(char ch) {
    // 记录起始位置
    if (lexer_) {
        startLine_ = lexer_->getCurrentLine();
        startColumn_ = lexer_->getCurrentColumn();
    }
    
    // 空白符
    if (isWhitespace(ch)) {
        subState_ = SubState::WHITESPACE;
        return nullptr;
    }
    
    // 字符串字面量
    if (ch == '"') {
        subState_ = SubState::STRING_DOUBLE;
        buffer_.clear();
        return nullptr;
    }
    if (ch == '\'') {
        subState_ = SubState::STRING_SINGLE;
        buffer_.clear();
        return nullptr;
    }
    
    // 数字
    if (std::isdigit(ch)) {
        subState_ = SubState::NUMBER;
        buffer_ = ch;
        return nullptr;
    }
    
    // 标识符
    if (isIdentifierStart(ch)) {
        // 如果在 style 块内，可能是 CSS 属性名
        if (inStyleBlock_ && !inCssProperty_) {
            subState_ = SubState::CSS_PROPERTY_NAME;
            buffer_ = ch;
            return nullptr;
        }
        
        subState_ = SubState::IDENTIFIER;
        buffer_ = ch;
        return nullptr;
    }
    
    // 特殊标记 [xxx]
    if (ch == '[') {
        subState_ = SubState::SPECIAL_MARKER;
        buffer_ = ch;
        return nullptr;
    }
    
    // AT前缀 @xxx
    if (ch == '@') {
        subState_ = SubState::AT_PREFIX;
        buffer_ = ch;
        return nullptr;
    }
    
    // 注释
    if (ch == '/') {
        buffer_ = ch;
        subState_ = SubState::OPERATOR; // 先当作操作符，可能是注释
        return nullptr;
    }
    
    // HTML注释
    if (ch == '-') {
        buffer_ = ch;
        subState_ = SubState::OPERATOR; // 先当作操作符，可能是HTML注释
        return nullptr;
    }
    
    // 操作符
    if (isOperatorChar(ch)) {
        // 特殊处理：如果是 # 且在 CSS 属性值中
        if (ch == '#' && inStyleBlock_ && inCssProperty_) {
            subState_ = SubState::CSS_COLOR_VALUE;
            buffer_ = ch;
            return nullptr;
        }
        
        subState_ = SubState::OPERATOR;
        buffer_ = ch;
        return nullptr;
    }
    
    // 未知字符，创建UNKNOWN token
    emitTokenAndReset(TokenType::UNKNOWN);
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleIdentifier(char ch) {
    if (isIdentifierContinue(ch)) {
        buffer_ += ch;
        return nullptr;
    }
    
    // 标识符结束，判断类型
    TokenType type = determineIdentifierType();
    
    // 检查是否在text块内，且后面是左大括号
    if (type == TokenType::TEXT && ch == '{') {
        emitToken(type);
        subState_ = SubState::INITIAL;
        return nullptr;  // 让下一次处理'{'
    }
    
    emitToken(type);
    
    // 特殊处理：如果是style或script，可能需要切换状态
    if (type == TokenType::STYLE && ch == '{') {
        inStyleBlock_ = true;
        // 不切换到 CSS 状态，继续使用 CHTL 状态处理局部样式块
    }
    if (type == TokenType::SCRIPT_KW && ch == '{') {
        inScriptBlock_ = true;
        // 切换到 JS 状态
        return StateFactory::createState(StateType::JS, lexer_);
    }
    
    // 如果在 style 块内且是标识符，可能是 CSS 属性名
    if (inStyleBlock_ && type == TokenType::IDENTIFIER) {
        // 检查后面是否是冒号，如果是则进入 CSS 属性名状态
        if (ch == ':') {
            inCssProperty_ = true;
            subState_ = SubState::CSS_PROPERTY_VALUE;
            buffer_.clear();
            return nullptr;
        }
    }
    
    subState_ = SubState::INITIAL;
    return handleChar(ch);
}

std::shared_ptr<BasicState> ChtlState::handleStringSingle(char ch) {
    if (ch == '\'') {
        // 字符串结束
        emitTokenAndReset(TokenType::STRING_LITERAL);
        subState_ = SubState::INITIAL;
    } else if (ch == '\\') {
        // 转义字符
        buffer_ += ch;
        // TODO: 处理转义序列
    } else {
        buffer_ += ch;
    }
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleStringDouble(char ch) {
    if (ch == '"') {
        // 字符串结束
        emitTokenAndReset(TokenType::STRING_LITERAL);
        subState_ = SubState::INITIAL;
    } else if (ch == '\\') {
        // 转义字符
        buffer_ += ch;
        // TODO: 处理转义序列
    } else {
        buffer_ += ch;
    }
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleUnquotedLiteral(char ch) {
    // 无引号字面量可以包含字母、数字、下划线、连字符等
    if (std::isalnum(ch) || ch == '_' || ch == '-' || ch == '.') {
        buffer_ += ch;
        return nullptr;
    }
    
    // 无引号字面量结束
    emitToken(TokenType::UNQUOTED_LITERAL);
    subState_ = SubState::INITIAL;
    return handleChar(ch);
}

std::shared_ptr<BasicState> ChtlState::handleNumber(char ch) {
    if (std::isdigit(ch) || ch == '.') {
        buffer_ += ch;
        return nullptr;
    }
    
    // 数字结束
    emitToken(TokenType::NUMBER);
    subState_ = SubState::INITIAL;
    return handleChar(ch);
}

std::shared_ptr<BasicState> ChtlState::handleOperator(char ch) {
    // 处理多字符操作符
    if (buffer_ == "/" && ch == '/') {
        // 单行注释
        buffer_.clear();
        subState_ = SubState::COMMENT_SINGLE;
        return nullptr;
    }
    if (buffer_ == "/" && ch == '*') {
        // 多行注释
        buffer_.clear();
        subState_ = SubState::COMMENT_MULTI;
        return nullptr;
    }
    if (buffer_ == "-" && ch == '-') {
        // HTML注释
        buffer_.clear();
        subState_ = SubState::HTML_COMMENT;
        return nullptr;
    }
    if (buffer_ == "-" && ch == '>') {
        // 箭头操作符
        buffer_ += ch;
        emitToken(TokenType::ARROW, buffer_);
        buffer_.clear();
        subState_ = SubState::INITIAL;
        return nullptr;
    }
    if (buffer_ == "{" && ch == '{') {
        // 双左大括号（JavaScript增强语法）
        buffer_ += ch;
        emitToken(TokenType::DOUBLE_LEFT_BRACE, buffer_);
        buffer_.clear();
        subState_ = SubState::INITIAL;
        // 可能需要切换到CHTL_JS状态
        if (inScriptBlock_) {
            return StateFactory::createState(StateType::CHTL_JS, lexer_);
        }
        return nullptr;
    }
    if (buffer_ == "}" && ch == '}') {
        // 双右大括号
        buffer_ += ch;
        emitToken(TokenType::DOUBLE_RIGHT_BRACE, buffer_);
        buffer_.clear();
        subState_ = SubState::INITIAL;
        return nullptr;
    }
    
    // 继续累积操作符字符（最多2个）
    if (isOperatorChar(ch) && buffer_.length() < 2) {
        buffer_ += ch;
        return nullptr;
    }
    
    // 操作符结束
    TokenType type = determineOperatorType();
    
    // 特殊处理：如果是冒号且在 style 块内
    if (type == TokenType::COLON && inStyleBlock_ && !inCssProperty_) {
        emitToken(type);
        inCssProperty_ = true;
        subState_ = SubState::CSS_PROPERTY_VALUE;
        buffer_.clear();
        return nullptr;
    }
    
    // 特殊处理：如果是右大括号且在 style 块内
    if (type == TokenType::RIGHT_BRACE && inStyleBlock_) {
        inStyleBlock_ = false;
        inCssProperty_ = false;
    }
    
    emitToken(type);
    subState_ = SubState::INITIAL;
    return handleChar(ch);
}

std::shared_ptr<BasicState> ChtlState::handleCommentSingle(char ch) {
    if (ch == '\n') {
        // 单行注释结束
        emitTokenAndReset(TokenType::SINGLE_LINE_COMMENT);
        subState_ = SubState::INITIAL;
    } else {
        buffer_ += ch;
    }
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleCommentMulti(char ch) {
    buffer_ += ch;
    if (buffer_.size() >= 2 && 
        buffer_[buffer_.size() - 2] == '*' && 
        buffer_[buffer_.size() - 1] == '/') {
        // 多行注释结束
        buffer_.pop_back(); // 移除 '/'
        buffer_.pop_back(); // 移除 '*'
        emitTokenAndReset(TokenType::MULTI_LINE_COMMENT);
        subState_ = SubState::INITIAL;
    }
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleHtmlComment(char ch) {
    if (ch == '\n') {
        // CHTL的 -- 注释是单行注释，遇到换行符结束
        emitTokenAndReset(TokenType::HTML_COMMENT);
        subState_ = SubState::INITIAL;
    } else {
        buffer_ += ch;
    }
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleAtPrefix(char ch) {
    if (std::isalpha(ch)) {
        buffer_ += ch;
        return nullptr;
    }
    
    // AT前缀结束
    TokenType type = determineAtPrefixType();
    emitToken(type);
    subState_ = SubState::INITIAL;
    return handleChar(ch);
}

std::shared_ptr<BasicState> ChtlState::handleSpecialMarker(char ch) {
    // 检查是否是预定义的特殊标记开始
    if (buffer_.length() == 1 && ch != ']') {
        // 检查第二个字符是否可能是特殊标记的一部分
        std::string potentialMarker = buffer_ + ch;
        bool couldBeSpecialMarker = false;
        
        // 检查是否可能是特殊标记的前缀
        if (potentialMarker == "[C" || potentialMarker == "[T" || 
            potentialMarker == "[S" || potentialMarker == "[O" ||
            potentialMarker == "[I" || potentialMarker == "[N" ||
            potentialMarker == "[E" || potentialMarker == "[D") {
            couldBeSpecialMarker = true;
        }
        
        if (!couldBeSpecialMarker) {
            // 不是特殊标记，是普通的左括号
            emitToken(TokenType::LEFT_BRACKET);
            buffer_.clear();
            subState_ = SubState::INITIAL;
            return handleInitial(ch);  // 重新处理当前字符
        }
    }
    
    buffer_ += ch;
    if (ch == ']') {
        // 特殊标记结束
        TokenType type = GlobalMap::getSpecialMarkerType(buffer_);
        if (type == TokenType::UNKNOWN) {
            // 不是预定义的特殊标记，是数组索引
            // 只发送左括号，内容已经被跳过了，需要重新处理
            emitToken(TokenType::LEFT_BRACKET);
            
            // 提取括号内的内容
            std::string content = buffer_.substr(1, buffer_.length() - 2);
            if (!content.empty()) {
                // 如果内容是数字，发送NUMBER token
                bool isNumber = true;
                for (char c : content) {
                    if (!std::isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }
                
                if (isNumber) {
                    buffer_ = content;
                    emitToken(TokenType::NUMBER);
                } else {
                    // 其他内容作为标识符
                    buffer_ = content;
                    emitToken(TokenType::IDENTIFIER);
                }
            }
            
            buffer_ = "]";
            emitTokenAndReset(TokenType::RIGHT_BRACKET);
        } else {
            emitTokenAndReset(type);
        }
        subState_ = SubState::INITIAL;
    }
    return nullptr;
}

void ChtlState::onEnter() {
    reset();
}

void ChtlState::onExit() {
    if (!buffer_.empty()) {
        completeToken();
    }
}

void ChtlState::onEnd() {
    if (!buffer_.empty()) {
        completeToken();
    }
    // 发送EOF token
    emitToken(TokenType::EOF_TOKEN);
}

bool ChtlState::accepts(char ch) const {
    // CHTL状态接受所有字符
    (void)ch; // 避免未使用参数警告
    return true;
}

void ChtlState::reset() {
    subState_ = SubState::INITIAL;
    buffer_.clear();
    startLine_ = 1;
    startColumn_ = 1;
}

bool ChtlState::isIdentifierStart(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || ch == '$';
}

bool ChtlState::isIdentifierContinue(char ch) {
    return isIdentifierStart(ch) || (ch >= '0' && ch <= '9');
}

bool ChtlState::isOperatorChar(char ch) {
    static const std::string operators = ":;=,.->&{}()[]*/+!#";
    return operators.find(ch) != std::string::npos;
}

bool ChtlState::isWhitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

void ChtlState::completeToken() {
    switch (subState_) {
        case SubState::IDENTIFIER:
            emitToken(determineIdentifierType());
            break;
        case SubState::STRING_SINGLE:
        case SubState::STRING_DOUBLE:
            emitToken(TokenType::STRING_LITERAL);
            break;
        case SubState::UNQUOTED_LITERAL:
            emitToken(TokenType::UNQUOTED_LITERAL);
            break;
        case SubState::NUMBER:
            emitToken(TokenType::NUMBER);
            break;
        case SubState::OPERATOR:
            emitToken(determineOperatorType());
            break;
        case SubState::AT_PREFIX:
            emitToken(determineAtPrefixType());
            break;
        case SubState::SPECIAL_MARKER:
            emitToken(TokenType::UNKNOWN);
            break;
        default:
            break;
    }
    buffer_.clear();
}

void ChtlState::emitToken(TokenType type) {
    if (lexer_) {
        lexer_->emitToken(type, buffer_, startLine_, startColumn_);
    }
}

void ChtlState::emitTokenAndReset(TokenType type) {
    emitToken(type);
    buffer_.clear();
}

TokenType ChtlState::determineIdentifierType() {
    // 检查是否是关键字
    TokenType keywordType = GlobalMap::getKeywordType(buffer_);
    if (keywordType != TokenType::UNKNOWN) {
        return keywordType;
    }
    
    // 检查是否是HTML标签
    if (GlobalMap::isHtmlTag(buffer_)) {
        return TokenType::IDENTIFIER; // HTML标签也是标识符
    }
    
    // 在CSS上下文中，可能是CSS属性
    if (inStyleBlock_ && GlobalMap::isCssProperty(buffer_)) {
        return TokenType::IDENTIFIER;
    }
    
    return TokenType::IDENTIFIER;
}

TokenType ChtlState::determineOperatorType() {
    if (buffer_ == ":") return TokenType::COLON;
    if (buffer_ == ";") return TokenType::SEMICOLON;
    if (buffer_ == "=") return TokenType::EQUALS;
    if (buffer_ == ",") return TokenType::COMMA;
    if (buffer_ == ".") return TokenType::DOT;
    if (buffer_ == "->") return TokenType::ARROW;
    if (buffer_ == "&") return TokenType::AMPERSAND;
    if (buffer_ == "{") return TokenType::LEFT_BRACE;
    if (buffer_ == "}") return TokenType::RIGHT_BRACE;
    if (buffer_ == "(") return TokenType::LEFT_PAREN;
    if (buffer_ == ")") return TokenType::RIGHT_PAREN;
    if (buffer_ == "[") return TokenType::LEFT_BRACKET;
    if (buffer_ == "]") return TokenType::RIGHT_BRACKET;
    if (buffer_ == "*") return TokenType::WILDCARD;
    if (buffer_ == "{{") return TokenType::DOUBLE_LEFT_BRACE;
    if (buffer_ == "}}") return TokenType::DOUBLE_RIGHT_BRACE;
    
    return TokenType::UNKNOWN;
}

TokenType ChtlState::determineAtPrefixType() {
    if (buffer_ == "@Style") return TokenType::AT_STYLE;
    if (buffer_ == "@Element") return TokenType::AT_ELEMENT;
    if (buffer_ == "@Var") return TokenType::AT_VAR;
    if (buffer_ == "@Html") return TokenType::AT_HTML;
    if (buffer_ == "@JavaScript") return TokenType::AT_JAVASCRIPT;
    if (buffer_ == "@Chtl") return TokenType::AT_CHTL;
    if (buffer_ == "@CJmod") return TokenType::AT_CJMOD;
    return TokenType::IDENTIFIER;
}

std::shared_ptr<BasicState> ChtlState::transitionToState(StateType newStateType) {
    switch (newStateType) {
        case StateType::CSS:
            return std::make_shared<CssState>(lexer_);
        case StateType::JS:
            return std::make_shared<JsState>(lexer_);
        case StateType::CHTL_JS:
            return std::make_shared<ChtlJsState>(lexer_);
        default:
            return nullptr;
    }
}

std::shared_ptr<BasicState> ChtlState::handleWhitespace(char ch) {
    if (!isWhitespace(ch)) {
        subState_ = SubState::INITIAL;
        return handleChar(ch);
    }
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleTextBlock(char ch) {
    // 暂时处理为普通标识符
    return handleIdentifier(ch);
}

std::shared_ptr<BasicState> ChtlState::handleCssPropertyName(char ch) {
    if (isIdentifierContinue(ch) || ch == '-') {
        buffer_ += ch;
        return nullptr;
    }
    
    // 属性名结束
    if (ch == ':') {
        emitToken(TokenType::IDENTIFIER, buffer_);
        buffer_.clear();
        emitToken(TokenType::COLON, ":");
        subState_ = SubState::CSS_PROPERTY_VALUE;
        inCssProperty_ = true;
        return nullptr;
    }
    
    // 其他情况，回到初始状态
    emitToken(TokenType::IDENTIFIER, buffer_);
    buffer_.clear();
    subState_ = SubState::INITIAL;
    return handleChar(ch);
}

std::shared_ptr<BasicState> ChtlState::handleCssPropertyValue(char ch) {
    // 跳过属性值开始的空白
    if (buffer_.empty() && isWhitespace(ch)) {
        return nullptr;
    }
    
    // 检查是否是颜色值
    if (ch == '#') {
        // 如果当前 buffer 不为空，先发出
        if (!buffer_.empty()) {
            if (std::isdigit(buffer_[0]) || (buffer_[0] == '-' && buffer_.length() > 1 && std::isdigit(buffer_[1]))) {
                emitToken(TokenType::NUMBER, buffer_);
            } else {
                emitToken(TokenType::IDENTIFIER, buffer_);
            }
            buffer_.clear();
        }
        buffer_ = "#";
        subState_ = SubState::CSS_COLOR_VALUE;
        return nullptr;
    }
    
    // 检查是否是字符串
    if (ch == '"' || ch == '\'') {
        subState_ = (ch == '"') ? SubState::STRING_DOUBLE : SubState::STRING_SINGLE;
        buffer_ = ch;
        startLine_ = lexer_->getCurrentLine();
        startColumn_ = lexer_->getCurrentColumn();
        return nullptr;
    }
    
    // 检查是否是分号（值结束）
    if (ch == ';') {
        if (!buffer_.empty()) {
            // 发出最后的值 token
            if (std::isdigit(buffer_[0]) || (buffer_[0] == '-' && buffer_.length() > 1 && std::isdigit(buffer_[1]))) {
                emitToken(TokenType::NUMBER, buffer_);
            } else {
                emitToken(TokenType::IDENTIFIER, buffer_);
            }
            buffer_.clear();
        }
        emitToken(TokenType::SEMICOLON, ";");
        inCssProperty_ = false;
        subState_ = SubState::INITIAL;
        return nullptr;
    }
    
    // 检查是否是右大括号（style 块结束）
    if (ch == '}') {
        if (!buffer_.empty()) {
            // 发出最后的值 token
            if (std::isdigit(buffer_[0]) || (buffer_[0] == '-' && buffer_.length() > 1 && std::isdigit(buffer_[1]))) {
                emitToken(TokenType::NUMBER, buffer_);
            } else {
                emitToken(TokenType::IDENTIFIER, buffer_);
            }
            buffer_.clear();
        }
        inCssProperty_ = false;
        inStyleBlock_ = false;
        subState_ = SubState::INITIAL;
        return handleChar(ch);  // 重新处理 }
    }
    
    // 检查是否需要分割 token
    if (isWhitespace(ch)) {
        if (!buffer_.empty()) {
            // 发出当前 token
            if (std::isdigit(buffer_[0]) || (buffer_[0] == '-' && buffer_.length() > 1 && std::isdigit(buffer_[1]))) {
                emitToken(TokenType::NUMBER, buffer_);
            } else {
                emitToken(TokenType::IDENTIFIER, buffer_);
            }
            buffer_.clear();
        }
        // 空白字符直接忽略，不产生 token
        return nullptr;
    }
    
    // 特殊字符处理
    if (ch == ',' || ch == '(' || ch == ')') {
        if (!buffer_.empty()) {
            // 发出当前 token
            if (std::isdigit(buffer_[0]) || (buffer_[0] == '-' && buffer_.length() > 1 && std::isdigit(buffer_[1]))) {
                emitToken(TokenType::NUMBER, buffer_);
            } else {
                emitToken(TokenType::IDENTIFIER, buffer_);
            }
            buffer_.clear();
        }
        
        // 处理特殊字符
        if (ch == ',') {
            emitToken(TokenType::COMMA, ",");
        } else if (ch == '(') {
            emitToken(TokenType::LEFT_PAREN, "(");
        } else if (ch == ')') {
            emitToken(TokenType::RIGHT_PAREN, ")");
        }
        
        return nullptr;
    }
    
    // 累积字符
    buffer_ += ch;
    return nullptr;
}

std::shared_ptr<BasicState> ChtlState::handleCssColorValue(char ch) {
    // 颜色值可以是 3、4、6 或 8 位十六进制
    if (isHexDigit(ch)) {
        buffer_ += ch;
        return nullptr;
    }
    
    // 颜色值结束
    if (!buffer_.empty() && buffer_[0] == '#' && buffer_.length() > 1) {
        emitToken(TokenType::IDENTIFIER, buffer_);  // 将颜色值作为标识符发出
        buffer_.clear();
    }
    
    subState_ = SubState::CSS_PROPERTY_VALUE;
    return handleChar(ch);
}

bool ChtlState::isHexDigit(char ch) {
    return (ch >= '0' && ch <= '9') || 
           (ch >= 'a' && ch <= 'f') || 
           (ch >= 'A' && ch <= 'F');
}

bool ChtlState::isIdentifierPart(char ch) {
    return isIdentifierStart(ch) || isDigit(ch);
}

bool ChtlState::isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

void ChtlState::emitToken(TokenType type, const std::string& value) {
    lexer_->emitToken(type, value, startLine_, startColumn_);
}

} // namespace chtl