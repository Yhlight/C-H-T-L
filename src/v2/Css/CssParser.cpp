#include "v2/Css/CssParser.h"
#include <sstream>
#include <algorithm>

namespace chtl::v2::css {

// CssSelector 实现
std::string CssSelector::toString() const {
    std::string result;
    
    switch (type) {
        case SelectorType::ELEMENT:
            result = value;
            break;
        case SelectorType::CLASS:
            result = "." + value;
            break;
        case SelectorType::ID:
            result = "#" + value;
            break;
        case SelectorType::UNIVERSAL:
            result = "*";
            break;
        case SelectorType::ATTRIBUTE:
            result = "[" + attribute;
            if (!op.empty()) {
                result += op + "\"" + attributeValue + "\"";
            }
            result += "]";
            break;
        case SelectorType::PSEUDO_CLASS:
            result = ":" + value;
            if (!argument.empty()) {
                result += "(" + argument + ")";
            }
            break;
        case SelectorType::PSEUDO_ELEMENT:
            result = "::" + value;
            break;
        default:
            break;
    }
    
    if (next) {
        switch (combinator) {
            case CombinatorType::DESCENDANT:
                result += " ";
                break;
            case CombinatorType::CHILD:
                result += " > ";
                break;
            case CombinatorType::ADJACENT:
                result += " + ";
                break;
            case CombinatorType::SIBLING:
                result += " ~ ";
                break;
            default:
                break;
        }
        result += next->toString();
    }
    
    return result;
}

int CssSelector::specificity() const {
    int a = 0, b = 0, c = 0;
    
    const CssSelector* current = this;
    while (current) {
        switch (current->type) {
            case SelectorType::ID:
                a++;
                break;
            case SelectorType::CLASS:
            case SelectorType::ATTRIBUTE:
            case SelectorType::PSEUDO_CLASS:
                b++;
                break;
            case SelectorType::ELEMENT:
            case SelectorType::PSEUDO_ELEMENT:
                c++;
                break;
            default:
                break;
        }
        current = current->next.get();
    }
    
    return a * 100 + b * 10 + c;
}

// CssDeclaration 实现
std::string CssDeclaration::toString() const {
    std::ostringstream oss;
    oss << property << ": ";
    
    // 将 CssValue 转换为字符串
    std::visit([&oss](const auto& val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, std::string>) {
            oss << val;
        } else if constexpr (std::is_same_v<T, double>) {
            oss << val;
        } else if constexpr (std::is_same_v<T, std::pair<double, std::string>>) {
            oss << val.first << val.second;
        } else if constexpr (std::is_same_v<T, std::vector<std::variant<std::string, double>>>) {
            bool first = true;
            for (const auto& item : val) {
                if (!first) oss << " ";
                std::visit([&oss](const auto& v) {
                    oss << v;
                }, item);
                first = false;
            }
        }
    }, value);
    
    if (important) {
        oss << " !important";
    }
    
    return oss.str();
}

// CssRule 实现
std::string CssRule::toString() const {
    std::ostringstream oss;
    
    if (type == RuleType::STYLE_RULE) {
        // 输出选择器
        bool first = true;
        for (const auto& selector : selectors) {
            if (!first) oss << ", ";
            oss << selector->toString();
            first = false;
        }
        
        oss << " {\n";
        
        // 输出声明
        for (const auto& decl : declarations) {
            oss << "  " << decl.toString() << ";\n";
        }
        
        oss << "}";
    } else {
        // @规则
        oss << "@" << atKeyword;
        if (!prelude.empty()) {
            oss << " " << prelude;
        }
        
        if (!nestedRules.empty() || !declarations.empty()) {
            oss << " {\n";
            
            // 输出声明
            for (const auto& decl : declarations) {
                oss << "  " << decl.toString() << ";\n";
            }
            
            // 输出嵌套规则
            for (const auto& rule : nestedRules) {
                oss << rule->toString() << "\n";
            }
            
            oss << "}";
        } else {
            oss << ";";
        }
    }
    
    return oss.str();
}

// CssStylesheet 实现
std::string CssStylesheet::toString() const {
    std::ostringstream oss;
    
    for (const auto& rule : rules) {
        oss << rule->toString() << "\n\n";
    }
    
    return oss.str();
}

// CssParser 实现
CssParser::CssParser(const std::string& input) 
    : tokenizer_(input) {
    current_ = tokenizer_.nextToken();
}

CssParseResult CssParser::parse() {
    CssParseResult result;
    result.stylesheet = parseStylesheet();
    result.errors = std::move(errors_);
    result.warnings = std::move(warnings_);
    return result;
}

std::unique_ptr<CssRule> CssParser::parseRule() {
    if (current_.type == CssTokenType::AT_KEYWORD) {
        return parseAtRule();
    } else {
        return parseStyleRule();
    }
}

std::vector<std::unique_ptr<CssSelector>> CssParser::parseSelectorList() {
    std::vector<std::unique_ptr<CssSelector>> selectors;
    
    do {
        auto selector = parseSelector();
        if (selector) {
            selectors.push_back(std::move(selector));
        }
    } while (consume(CssTokenType::COMMA));
    
    return selectors;
}

std::unique_ptr<CssStylesheet> CssParser::parseStylesheet() {
    auto stylesheet = std::make_unique<CssStylesheet>();
    
    while (!isAtEnd()) {
        try {
            auto rule = parseRule();
            if (rule) {
                stylesheet->rules.push_back(std::move(rule));
            }
        } catch (const std::exception& e) {
            error(e.what());
            synchronize();
        }
    }
    
    return stylesheet;
}

std::unique_ptr<CssRule> CssParser::parseAtRule() {
    auto rule = std::make_unique<CssRule>();
    rule->type = RuleType::AT_RULE;
    
    // 获取 @规则名称
    rule->atKeyword = current_.value;
    advance();
    
    // 确定规则类型
    if (rule->atKeyword == "media") {
        rule->type = RuleType::MEDIA_RULE;
    } else if (rule->atKeyword == "import") {
        rule->type = RuleType::IMPORT_RULE;
    } else if (rule->atKeyword == "keyframes") {
        rule->type = RuleType::KEYFRAMES_RULE;
    } else if (rule->atKeyword == "supports") {
        rule->type = RuleType::SUPPORTS_RULE;
    } else if (rule->atKeyword == "page") {
        rule->type = RuleType::PAGE_RULE;
    } else if (rule->atKeyword == "font-face") {
        rule->type = RuleType::FONT_FACE_RULE;
    } else if (rule->atKeyword == "namespace") {
        rule->type = RuleType::NAMESPACE_RULE;
    }
    
    // 解析前导（条件部分）
    std::ostringstream prelude;
    while (!isAtEnd() && current_.type != CssTokenType::LEFT_BRACE && 
           current_.type != CssTokenType::SEMICOLON) {
        prelude << current_.value << " ";
        advance();
    }
    rule->prelude = prelude.str();
    if (!rule->prelude.empty()) {
        rule->prelude.pop_back(); // 移除最后的空格
    }
    
    // 解析规则体或分号
    if (match(CssTokenType::LEFT_BRACE)) {
        advance();
        
        if (rule->type == RuleType::MEDIA_RULE || 
            rule->type == RuleType::SUPPORTS_RULE) {
            // 解析嵌套规则
            while (!isAtEnd() && !match(CssTokenType::RIGHT_BRACE)) {
                auto nestedRule = parseRule();
                if (nestedRule) {
                    rule->nestedRules.push_back(std::move(nestedRule));
                }
            }
        } else {
            // 解析声明
            rule->declarations = parseDeclarationBlock();
        }
        
        consume(CssTokenType::RIGHT_BRACE);
    } else {
        consume(CssTokenType::SEMICOLON);
    }
    
    return rule;
}

std::unique_ptr<CssRule> CssParser::parseStyleRule() {
    auto rule = std::make_unique<CssRule>();
    rule->type = RuleType::STYLE_RULE;
    
    // 解析选择器列表
    rule->selectors = parseSelectorList();
    
    // 解析声明块
    if (consume(CssTokenType::LEFT_BRACE)) {
        rule->declarations = parseDeclarationBlock();
        consume(CssTokenType::RIGHT_BRACE);
    }
    
    return rule;
}

std::unique_ptr<CssSelector> CssParser::parseSelector() {
    auto selector = parseSimpleSelector();
    if (!selector) return nullptr;
    
    // 处理组合器和后续选择器
    while (!isAtEnd()) {
        CombinatorType combinator = CombinatorType::NONE;
        
        // 检查组合器
        if (match(CssTokenType::GT)) {
            combinator = CombinatorType::CHILD;
            advance();
        } else if (match(CssTokenType::PLUS)) {
            combinator = CombinatorType::ADJACENT;
            advance();
        } else if (match(CssTokenType::TILDE)) {
            combinator = CombinatorType::SIBLING;
            advance();
        } else if (match(CssTokenType::IDENT) || match(CssTokenType::HASH) ||
                   match(CssTokenType::DOT) || match(CssTokenType::LEFT_BRACKET) ||
                   match(CssTokenType::COLON) || match(CssTokenType::STAR)) {
            combinator = CombinatorType::DESCENDANT;
        } else {
            break;
        }
        
        auto next = parseSimpleSelector();
        if (!next) break;
        
        // 找到最后一个选择器
        CssSelector* last = selector.get();
        while (last->next) {
            last = last->next.get();
        }
        
        last->combinator = combinator;
        last->next = std::move(next);
    }
    
    return selector;
}

std::unique_ptr<CssSelector> CssParser::parseSimpleSelector() {
    auto selector = std::make_unique<CssSelector>();
    
    if (match(CssTokenType::STAR)) {
        selector->type = SelectorType::UNIVERSAL;
        advance();
    } else if (match(CssTokenType::IDENT)) {
        selector->type = SelectorType::ELEMENT;
        selector->value = current_.value;
        advance();
    } else if (match(CssTokenType::HASH)) {
        selector->type = SelectorType::ID;
        selector->value = current_.value;
        advance();
    } else if (match(CssTokenType::DOT)) {
        advance();
        if (match(CssTokenType::IDENT)) {
            selector->type = SelectorType::CLASS;
            selector->value = current_.value;
            advance();
        }
    } else if (match(CssTokenType::LEFT_BRACKET)) {
        parseAttributeSelector(*selector);
    } else if (match(CssTokenType::COLON)) {
        parsePseudoSelector(*selector);
    } else {
        return nullptr;
    }
    
    // 解析附加的选择器部分（类、ID、属性、伪类等）
    while (!isAtEnd()) {
        if (match(CssTokenType::HASH)) {
            // 附加 ID（罕见但合法）
            selector->value += "#" + current_.value;
            advance();
        } else if (match(CssTokenType::DOT)) {
            advance();
            if (match(CssTokenType::IDENT)) {
                // 附加类
                selector->value += "." + current_.value;
                advance();
            }
        } else if (match(CssTokenType::LEFT_BRACKET)) {
            parseAttributeSelector(*selector);
        } else if (match(CssTokenType::COLON)) {
            parsePseudoSelector(*selector);
        } else {
            break;
        }
    }
    
    return selector;
}

void CssParser::parseAttributeSelector(CssSelector& selector) {
    selector.type = SelectorType::ATTRIBUTE;
    advance(); // [
    
    if (match(CssTokenType::IDENT)) {
        selector.attribute = current_.value;
        advance();
        
        // 检查操作符
        if (match(CssTokenType::EQUALS)) {
            selector.op = "=";
            advance();
        } else if (match(CssTokenType::TILDE) && peek().type == CssTokenType::EQUALS) {
            selector.op = "~=";
            advance(); advance();
        } else if (match(CssTokenType::PIPE) && peek().type == CssTokenType::EQUALS) {
            selector.op = "|=";
            advance(); advance();
        } else if (match(CssTokenType::CARET) && peek().type == CssTokenType::EQUALS) {
            selector.op = "^=";
            advance(); advance();
        } else if (match(CssTokenType::DOLLAR) && peek().type == CssTokenType::EQUALS) {
            selector.op = "$=";
            advance(); advance();
        } else if (match(CssTokenType::STAR) && peek().type == CssTokenType::EQUALS) {
            selector.op = "*=";
            advance(); advance();
        }
        
        // 获取属性值
        if (!selector.op.empty()) {
            if (match(CssTokenType::STRING) || match(CssTokenType::IDENT)) {
                selector.attributeValue = current_.value;
                advance();
            }
        }
    }
    
    consume(CssTokenType::RIGHT_BRACKET);
}

void CssParser::parsePseudoSelector(CssSelector& selector) {
    advance(); // :
    
    // 检查是否是伪元素
    if (match(CssTokenType::COLON)) {
        advance();
        selector.type = SelectorType::PSEUDO_ELEMENT;
    } else {
        selector.type = SelectorType::PSEUDO_CLASS;
    }
    
    if (match(CssTokenType::IDENT) || match(CssTokenType::FUNCTION)) {
        selector.value = current_.value;
        
        if (current_.type == CssTokenType::FUNCTION) {
            advance();
            consume(CssTokenType::LEFT_PAREN);
            
            // 解析参数
            std::ostringstream args;
            int parenDepth = 1;
            while (!isAtEnd() && parenDepth > 0) {
                if (match(CssTokenType::LEFT_PAREN)) {
                    parenDepth++;
                } else if (match(CssTokenType::RIGHT_PAREN)) {
                    parenDepth--;
                    if (parenDepth == 0) break;
                }
                args << current_.value;
                advance();
            }
            
            selector.argument = args.str();
            consume(CssTokenType::RIGHT_PAREN);
        } else {
            advance();
        }
    }
}

std::vector<CssDeclaration> CssParser::parseDeclarationBlock() {
    std::vector<CssDeclaration> declarations;
    
    while (!isAtEnd() && !match(CssTokenType::RIGHT_BRACE)) {
        try {
            auto decl = parseDeclaration();
            declarations.push_back(decl);
        } catch (const std::exception& e) {
            error(e.what());
            // 跳到下一个声明
            while (!isAtEnd() && !match(CssTokenType::SEMICOLON) && 
                   !match(CssTokenType::RIGHT_BRACE)) {
                advance();
            }
            if (match(CssTokenType::SEMICOLON)) advance();
        }
    }
    
    return declarations;
}

CssDeclaration CssParser::parseDeclaration() {
    CssDeclaration decl;
    
    // 属性名
    if (!match(CssTokenType::IDENT)) {
        throw std::runtime_error("Expected property name");
    }
    
    decl.property = current_.value;
    advance();
    
    if (!consume(CssTokenType::COLON)) {
        throw std::runtime_error("Expected ':' after property name");
    }
    
    // 属性值
    decl.value = parseValue();
    
    // 检查 !important
    if (match(CssTokenType::IMPORTANT)) {
        decl.important = true;
        advance();
    }
    
    // 可选的分号
    consume(CssTokenType::SEMICOLON);
    
    return decl;
}

CssValue CssParser::parseValue() {
    std::vector<std::variant<std::string, double>> values;
    
    while (!isAtEnd() && !match(CssTokenType::SEMICOLON) && 
           !match(CssTokenType::RIGHT_BRACE) && !match(CssTokenType::IMPORTANT)) {
        
        if (match(CssTokenType::NUMBER)) {
            values.push_back(current_.extra.numericValue);
            advance();
        } else if (match(CssTokenType::PERCENTAGE)) {
            values.push_back(current_.value);
            advance();
        } else if (match(CssTokenType::DIMENSION)) {
            values.push_back(current_.value);
            advance();
        } else if (match(CssTokenType::STRING)) {
            values.push_back(current_.value);
            advance();
        } else if (match(CssTokenType::IDENT)) {
            values.push_back(current_.value);
            advance();
        } else if (match(CssTokenType::HASH)) {
            values.push_back("#" + current_.value);
            advance();
        } else if (match(CssTokenType::FUNCTION)) {
            std::string funcName = current_.value;
            advance();
            values.push_back(funcName + "(" + 
                           std::get<std::string>(parseFunctionValue(funcName)) + ")");
        } else if (match(CssTokenType::URL)) {
            values.push_back("url(" + current_.value + ")");
            advance();
        } else {
            // 其他 token
            values.push_back(current_.value);
            advance();
        }
    }
    
    if (values.empty()) {
        throw std::runtime_error("Expected property value");
    } else if (values.size() == 1) {
        // 单个值
        return std::visit([](auto&& arg) -> CssValue { return arg; }, values[0]);
    } else {
        // 多个值
        return values;
    }
}

CssValue CssParser::parseFunctionValue(const std::string& funcName) {
    consume(CssTokenType::LEFT_PAREN);
    
    std::ostringstream args;
    int parenDepth = 1;
    
    while (!isAtEnd() && parenDepth > 0) {
        if (match(CssTokenType::LEFT_PAREN)) {
            parenDepth++;
        } else if (match(CssTokenType::RIGHT_PAREN)) {
            parenDepth--;
            if (parenDepth == 0) break;
        }
        
        if (parenDepth > 0) {
            args << current_.value;
            if (current_.type != CssTokenType::RIGHT_PAREN) {
                args << " ";
            }
        }
        advance();
    }
    
    return args.str();
}

bool CssParser::match(CssTokenType type) {
    return current_.type == type;
}

bool CssParser::consume(CssTokenType type) {
    if (match(type)) {
        advance();
        return true;
    }
    return false;
}

CssToken CssParser::advance() {
    if (!isAtEnd()) {
        current_ = tokenizer_.nextToken();
    }
    return current_;
}

CssToken CssParser::peek() {
    return tokenizer_.peekToken();
}

bool CssParser::isAtEnd() {
    return current_.type == CssTokenType::EOF_TOKEN;
}

void CssParser::synchronize() {
    // 恢复到一个安全的解析状态
    while (!isAtEnd()) {
        if (current_.type == CssTokenType::SEMICOLON ||
            current_.type == CssTokenType::RIGHT_BRACE) {
            advance();
            return;
        }
        advance();
    }
}

void CssParser::error(const std::string& message) {
    errors_.push_back("CSS Parse Error at line " + std::to_string(current_.line) + 
                     ", column " + std::to_string(current_.column) + ": " + message);
}

void CssParser::warning(const std::string& message) {
    warnings_.push_back("CSS Warning at line " + std::to_string(current_.line) + 
                       ", column " + std::to_string(current_.column) + ": " + message);
}

} // namespace chtl::v2::css