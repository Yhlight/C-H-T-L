#include "v2/Parser/ChtlParser.h"
#include "v2/Import/ImportSystem.h"  // For ImportType
#include <iostream>
#include <sstream>

namespace chtl::v2 {

ChtlParser::ChtlParser() 
    : cssAnalyzer_(std::make_unique<css::NativeCssAnalyzer>())
    , jsAnalyzer_(std::make_unique<js::NativeJsAnalyzer>()) {
}

ChtlParser::~ChtlParser() = default;

ParseResult ChtlParser::parse(const std::string& input) {
    // 初始化
    result_ = ParseResult();
    lexer_ = std::make_unique<ChtlLexer>(input);
    stateMachine_ = std::make_unique<ChtlStateMachine>();
    
    // 设置词法分析器和状态机的关联
    stateMachine_->setLexer(lexer_.get());
    lexer_->setStateMachine(stateMachine_.get());
    
    // 初始化状态机
    stateMachine_->initialize();
    
    // 创建文档根节点
    auto document = std::make_shared<Document>();
    
    // 获取第一个 token
    currentToken_ = lexer_->nextToken();
    
    // 解析顶层内容
    while (!isAtEnd()) {
        try {
            auto node = parseTopLevel();
            if (node) {
                document->addChild(node);
            }
        } catch (const std::exception& e) {
            addError(std::string("Parse error: ") + e.what());
            // 尝试恢复到下一个顶层元素
            while (!isAtEnd() && !check(TokenType::LEFT_BRACKET) &&
                   !check(TokenType::STYLE) && !check(TokenType::SCRIPT) &&
                   !currentToken_.metadata.isHtmlTag) {
                advance();
            }
        }
    }
    
    result_.ast = document;
    result_.success = result_.errors.empty();
    return result_;
}

void ChtlParser::setOption(const std::string& name, bool value) {
    if (name == "strictMode") {
        options_.strictMode = value;
    } else if (name == "allowLegacySyntax") {
        options_.allowLegacySyntax = value;
    }
}

std::shared_ptr<Node> ChtlParser::parseTopLevel() {
    // 在顶层（全局上下文）
    if (check(TokenType::LEFT_BRACKET)) {
        // 声明：[Template], [Custom] 等
        return parseDeclaration();
    }
    
    if (check(TokenType::STYLE)) {
        // 全局样式
        return parseStyleBlock();
    }
    
    if (check(TokenType::SCRIPT)) {
        // 全局脚本
        return parseScriptBlock();
    }
    
    if (currentToken_.metadata.isHtmlTag) {
        // HTML 元素
        return parseElement();
    }
    
    if (check(TokenType::AT)) {
        // 在全局上下文不允许引用
        addError("References (@) are not allowed at top level");
        advance();
        return nullptr;
    }
    
    // 未知的顶层元素
    addError("Unexpected token at top level: " + currentToken_.toString());
    advance();
    return nullptr;
}

std::shared_ptr<Node> ChtlParser::parseDeclaration() {
    stateMachine_->enterState(ChtlParseState::DECLARATION);
    
    consume(TokenType::LEFT_BRACKET, "Expected '['");
    
    Token keyword = consume(TokenType::IDENTIFIER, "Expected declaration keyword");
    
    std::shared_ptr<Node> result;
    
    if (keyword.value == "Template") {
        result = parseTemplateDeclaration();
    } else if (keyword.value == "Import") {
        result = parseImportDeclaration();
    } else if (keyword.value == "Custom") {
        // TODO: 实现自定义组件声明
        addError("Custom declarations not yet implemented");
        skipToDeclarationEnd();
    } else {
        addError("Unknown declaration type: " + keyword.value);
        skipToDeclarationEnd();
    }
    
    stateMachine_->exitState();
    
    return result;
}

std::shared_ptr<Node> ChtlParser::parseElement() {
    stateMachine_->enterState(ChtlParseState::ELEMENT, ChtlSubState::ELEMENT_TAG);
    
    // 元素标签
    Token tag = consume(TokenType::IDENTIFIER, "Expected element tag");
    auto element = std::make_shared<Element>(tag.value);
    element->setLocation(tag.line, tag.column);
    
    // 解析标签和属性
    parseElementTag(element);
    
    // 检查是否有内容
    if (match(TokenType::LEFT_BRACE)) {
        // 进入局部上下文
        stateMachine_->enterLocalContext();
        stateMachine_->enterState(ChtlParseState::ELEMENT_CONTENT);
        
        parseElementContent(element);
        
        consume(TokenType::RIGHT_BRACE, "Expected '}'");
        
        stateMachine_->exitState();
        stateMachine_->exitLocalContext();
    }
    
    stateMachine_->exitState();
    
    return element;
}

void ChtlParser::parseElementTag(std::shared_ptr<Element>& element) {
    while (!isAtEnd() && !check(TokenType::LEFT_BRACE)) {
        // # -> ID
        if (match(TokenType::HASH)) {
            stateMachine_->switchSubState(ChtlSubState::ELEMENT_ID);
            Token id = consume(TokenType::IDENTIFIER, "Expected ID after #");
            element->setId(id.value);
            stateMachine_->switchSubState(ChtlSubState::ELEMENT_TAG);
        }
        // . -> 类名
        else if (match(TokenType::DOT)) {
            stateMachine_->switchSubState(ChtlSubState::ELEMENT_CLASS);
            Token className = consume(TokenType::IDENTIFIER, "Expected class name after .");
            element->addClass(className.value);
            stateMachine_->switchSubState(ChtlSubState::ELEMENT_TAG);
        }
        // 属性名
        else if (check(TokenType::IDENTIFIER) && !currentToken_.metadata.isHtmlTag) {
            stateMachine_->switchSubState(ChtlSubState::ELEMENT_ATTR_NAME);
            Token attrName = advance();
            
            if (match(TokenType::EQUALS)) {
                stateMachine_->switchSubState(ChtlSubState::ELEMENT_ATTR_VALUE);
                Token attrValue = advance();
                element->setAttribute(attrName.value, attrValue.value);
                stateMachine_->switchSubState(ChtlSubState::ELEMENT_TAG);
            } else {
                // 布尔属性
                element->setAttribute(attrName.value, "");
            }
        }
        else {
            break;
        }
    }
}

void ChtlParser::parseElementContent(std::shared_ptr<Element>& element) {
    while (!isAtEnd() && !check(TokenType::RIGHT_BRACE)) {
        // style -> 局部样式
        if (check(TokenType::STYLE)) {
            auto style = parseStyleBlock();
            if (auto styleNode = std::dynamic_pointer_cast<Style>(style)) {
                styleNode->setGlobal(false);
                // 收集局部样式
                element->setLocalStyle(styleNode->getCssContent());
            }
        }
        // script -> 局部脚本
        else if (check(TokenType::SCRIPT)) {
            auto script = parseScriptBlock();
            if (auto scriptNode = std::dynamic_pointer_cast<Script>(script)) {
                scriptNode->setGlobal(false);
                element->addChild(script);
            }
        }
        // text -> 文本块
        else if (check(TokenType::TEXT)) {
            element->addChild(parseTextBlock());
        }
        // @ -> 引用
        else if (check(TokenType::AT) || check(TokenType::AT_ELEMENT)) {
            element->addChild(parseReference());
        }
        // [ -> 在局部上下文也是引用
        else if (check(TokenType::LEFT_BRACKET)) {
            // 局部上下文中，[Template] 也是引用
            element->addChild(parseReference());
        }
        // 嵌套元素
        else if (currentToken_.metadata.isHtmlTag) {
            element->addChild(parseElement());
        }
        else {
            addError("Unexpected token in element content: " + currentToken_.toString());
            advance();
        }
    }
}

std::shared_ptr<Node> ChtlParser::parseStyleBlock() {
    stateMachine_->enterState(ChtlParseState::STYLE);
    
    consume(TokenType::STYLE, "Expected 'style'");
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    auto style = std::make_shared<Style>();
    style->setLocation(currentToken_.line, currentToken_.column);
    
    // 检查是否是 text { } 形式（全局样式）
    if (check(TokenType::TEXT)) {
        advance();
        consume(TokenType::LEFT_BRACE, "Expected '{'");
        
        // 收集文本内容
        if (check(TokenType::STRING)) {
            Token content = advance();
            style->setCssContent(content.value);
        }
        
        consume(TokenType::RIGHT_BRACE, "Expected '}'");
    } else {
        // 收集 CSS 内容
        stateMachine_->enterState(ChtlParseState::STYLE_CONTENT);
        std::string cssContent = collectCssContent();
        style->setCssContent(cssContent);
        stateMachine_->exitState();
    }
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    // 分析 CSS（如果是全局样式）
    if (style->isGlobal() && !style->getCssContent().empty()) {
        auto cssResult = cssAnalyzer_->analyze(style->getCssContent());
        result_.cssResults.push_back(cssResult);
        
        // 报告 CSS 错误
        for (const auto& error : cssResult.errors) {
            addWarning("CSS: " + error);
        }
    }
    
    stateMachine_->exitState();
    
    return style;
}

std::shared_ptr<Node> ChtlParser::parseScriptBlock() {
    stateMachine_->enterState(ChtlParseState::SCRIPT);
    
    consume(TokenType::SCRIPT, "Expected 'script'");
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    auto script = std::make_shared<Script>();
    script->setLocation(currentToken_.line, currentToken_.column);
    
    // 收集 JS 内容
    stateMachine_->enterState(ChtlParseState::SCRIPT_CONTENT);
    std::string jsContent = collectJsContent();
    script->setJsContent(jsContent);
    
    // 检查是否包含 CHTL-JS
    if (jsContent.find("{{") != std::string::npos) {
        script->setHasChtlJs(true);
        // TODO: 调用 CHTL-JS 编译器
    }
    
    stateMachine_->exitState();
    
    // 分析 JS（如果不包含 CHTL-JS）
    if (!script->hasChtlJs() && !script->getJsContent().empty()) {
        auto jsResult = jsAnalyzer_->analyze(script->getJsContent());
        result_.jsResults.push_back(jsResult);
        
        // 报告 JS 错误
        for (const auto& error : jsResult.errors) {
            addWarning("JS: " + error);
        }
    }
    
    stateMachine_->exitState();
    
    return script;
}

std::shared_ptr<Node> ChtlParser::parseTextBlock() {
    stateMachine_->enterState(ChtlParseState::TEXT);
    
    consume(TokenType::TEXT, "Expected 'text'");
    consume(TokenType::LEFT_BRACE, "Expected '{'");
    
    std::string content;
    
    stateMachine_->enterState(ChtlParseState::TEXT_CONTENT);
    
    // 文本内容可以是字符串或模板参数
    if (check(TokenType::STRING)) {
        Token str = advance();
        content = str.value;
    } else if (check(TokenType::IDENTIFIER)) {
        // 模板参数引用
        Token param = advance();
        content = "{" + param.value + "}";  // 标记为参数
    }
    
    stateMachine_->exitState();
    
    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    
    stateMachine_->exitState();
    
    auto text = std::make_shared<Text>(content);
    text->setLocation(currentToken_.line, currentToken_.column);
    
    return text;
}

std::shared_ptr<Node> ChtlParser::parseReference() {
    stateMachine_->enterState(ChtlParseState::REFERENCE);
    
    auto ref = std::make_shared<Reference>();
    ref->setLocation(currentToken_.line, currentToken_.column);
    
    // @ 引用
    if (check(TokenType::AT_ELEMENT) || check(TokenType::AT_STYLE) || 
        check(TokenType::AT_VAR)) {
        Token refType = advance();
        ref->setReferenceType(refType.value);
        
        stateMachine_->switchSubState(ChtlSubState::REFERENCE_NAME);
        Token name = consume(TokenType::IDENTIFIER, "Expected reference name");
        ref->setName(name.value);
        
        // 参数
        if (match(TokenType::LEFT_PAREN)) {
            stateMachine_->switchSubState(ChtlSubState::REFERENCE_ARGS);
            
            while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
                if (check(TokenType::STRING)) {
                    ref->addArgument(advance().value);
                } else if (check(TokenType::IDENTIFIER)) {
                    ref->addArgument(advance().value);
                }
                
                if (!match(TokenType::COMMA)) {
                    break;
                }
            }
            
            consume(TokenType::RIGHT_PAREN, "Expected ')'");
        }
    }
    // [ 引用（局部上下文）
    else if (check(TokenType::LEFT_BRACKET)) {
        advance();  // [
        
        // 收集完整的引用名
        std::string fullName = "[";
        while (!check(TokenType::RIGHT_BRACKET) && !isAtEnd()) {
            fullName += currentToken_.value + " ";
            advance();
        }
        consume(TokenType::RIGHT_BRACKET, "Expected ']'");
        fullName += "]";
        
        ref->setReferenceType("composite");
        ref->setName(fullName);
        
        // 后续可能还有参数
        if (match(TokenType::LEFT_PAREN)) {
            // ... 解析参数
        }
    }
    
    stateMachine_->exitState();
    
    return ref;
}

std::shared_ptr<Node> ChtlParser::parseTemplateDeclaration() {
    auto templ = std::make_shared<Template>();
    templ->setLocation(currentToken_.line, currentToken_.column);
    
    // 已经消费了 @Element/Style/Var
    templ->setType(currentToken_.value);
    
    stateMachine_->switchSubState(ChtlSubState::DECLARATION_NAME);
    
    // 模板名
    Token name = consume(TokenType::IDENTIFIER, "Expected template name");
    templ->setName(name.value);
    
    // 参数列表
    if (match(TokenType::LEFT_PAREN)) {
        stateMachine_->switchSubState(ChtlSubState::DECLARATION_PARAMS);
        
        while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
            Token param = consume(TokenType::IDENTIFIER, "Expected parameter name");
            std::string defaultValue;
            
            if (match(TokenType::EQUALS)) {
                if (check(TokenType::STRING)) {
                    defaultValue = advance().value;
                }
            }
            
            templ->addParameter(param.value, defaultValue);
            
            if (!match(TokenType::COMMA)) {
                break;
            }
        }
        
        consume(TokenType::RIGHT_PAREN, "Expected ')'");
    }
    
    // 模板体
    if (match(TokenType::LEFT_BRACE)) {
        // 进入局部上下文
        stateMachine_->enterLocalContext();
        
        // 模板体就是元素内容
        auto body = std::make_shared<Element>("template-body");
        parseElementContent(body);
        
        for (const auto& child : body->getChildren()) {
            templ->addChild(child);
        }
        
        consume(TokenType::RIGHT_BRACE, "Expected '}'");
        
        stateMachine_->exitLocalContext();
    }
    
    return templ;
}

std::shared_ptr<Node> ChtlParser::parseImportDeclaration() {
    consume(TokenType::RIGHT_BRACKET, "Expected ']' after Import");
    
    // 期待 @Type
    Token atToken = currentToken_;
    if (!atToken.is(TokenType::AT) && !atToken.is(TokenType::AT_ELEMENT)) {
        addError("Expected @ after [Import]");
        return nullptr;
    }
    advance();
    
    // 导入类型
    Token typeToken = consume(TokenType::IDENTIFIER, "Expected import type");
    std::string importType = typeToken.value;
    
    // 创建导入节点
    auto import = std::make_shared<Import>();
    
    // 设置导入类型
    if (importType == "Style") {
        import->setType(ImportType::STYLE);
    } else if (importType == "JavaScript") {
        import->setType(ImportType::JAVASCRIPT);
    } else if (importType == "Html") {
        import->setType(ImportType::HTML);
    } else if (importType == "Chtl") {
        import->setType(ImportType::CHTL);
    } else if (importType == "Element") {
        import->setType(ImportType::ELEMENT);
    } else if (importType == "CJMOD") {
        import->setType(ImportType::CJMOD);
    } else {
        addError("Unknown import type: " + importType);
        import->setType(ImportType::ELEMENT); // 默认
    }
    
    // 路径或标识符
    Token pathToken = advance();
    if (pathToken.is(TokenType::STRING)) {
        // 字符串路径: "path/to/file"
        import->setPath(pathToken.value);
    } else if (pathToken.is(TokenType::IDENTIFIER)) {
        // 标识符路径: CHTL::Forms/Input
        std::string path = pathToken.value;
        
        // 检查是否有 ::
        if (match(TokenType::COLON)) {
            if (match(TokenType::COLON)) {
                // CHTL:: 官方模块
                path += "::";
                
                // 继续读取路径
                while (!isAtEnd()) {
                    if (check(TokenType::IDENTIFIER)) {
                        path += advance().value;
                    } else if (match(TokenType::SLASH)) {
                        path += "/";
                    } else {
                        break;
                    }
                }
            }
        }
        
        import->setPath(path);
    } else {
        addError("Expected import path");
    }
    
    // 可选的别名
    if (match(TokenType::AS)) {
        Token alias = consume(TokenType::IDENTIFIER, "Expected alias");
        import->setAlias(alias.value);
    }
    
    return import;
}

void ChtlParser::skipToDeclarationEnd() {
    while (!isAtEnd() && !check(TokenType::RIGHT_BRACKET)) {
        advance();
    }
    if (check(TokenType::RIGHT_BRACKET)) {
        advance();
    }
}

std::shared_ptr<Node> ChtlParser::parseCustomDeclaration() {
    // TODO: 实现自定义组件解析
    return nullptr;
}

std::string ChtlParser::collectCssContent() {
    std::string content;
    int braceDepth = 0;
    
    // 收集到匹配的 }
    while (!isAtEnd()) {
        if (check(TokenType::LEFT_BRACE)) {
            braceDepth++;
        } else if (check(TokenType::RIGHT_BRACE)) {
            if (braceDepth == 0) {
                break;  // 找到匹配的 }
            }
            braceDepth--;
        }
        
        content += currentToken_.value;
        if (currentToken_.type != TokenType::WHITESPACE) {
            content += " ";
        }
        
        advance();
    }
    
    return content;
}

std::string ChtlParser::collectJsContent() {
    // 期待 SCRIPT_CONTENT token
    if (check(TokenType::SCRIPT_CONTENT)) {
        return advance().value;
    }
    
    // 否则手动收集
    return collectUntilBrace();
}

std::string ChtlParser::collectUntilBrace() {
    std::string content;
    int braceDepth = 0;
    
    while (!isAtEnd()) {
        if (check(TokenType::LEFT_BRACE)) {
            braceDepth++;
        } else if (check(TokenType::RIGHT_BRACE)) {
            if (braceDepth == 0) {
                break;
            }
            braceDepth--;
        }
        
        content += currentToken_.value;
        advance();
    }
    
    return content;
}

Token ChtlParser::consume(TokenType expected, const std::string& message) {
    if (check(expected)) {
        return advance();
    }
    
    addError(message + " (got " + currentToken_.toString() + ")");
    throw std::runtime_error(message);
}

bool ChtlParser::check(TokenType type) const {
    return currentToken_.type == type;
}

bool ChtlParser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

Token ChtlParser::advance() {
    if (!isAtEnd()) {
        currentToken_ = lexer_->nextToken();
    }
    return currentToken_;
}

Token ChtlParser::peek() const {
    return lexer_->peekToken();
}

bool ChtlParser::isAtEnd() const {
    return currentToken_.type == TokenType::EOF_TOKEN;
}

void ChtlParser::addError(const std::string& message) {
    std::stringstream ss;
    ss << "Error at " << currentToken_.line << ":" << currentToken_.column 
       << ": " << message;
    result_.errors.push_back(ss.str());
}

void ChtlParser::addWarning(const std::string& message) {
    std::stringstream ss;
    ss << "Warning at " << currentToken_.line << ":" << currentToken_.column 
       << ": " << message;
    result_.warnings.push_back(ss.str());
}

} // namespace chtl::v2