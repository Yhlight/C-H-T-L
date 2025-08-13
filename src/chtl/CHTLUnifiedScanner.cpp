#include "CHTLUnifiedScanner.h"
#include "CHTLTemplate.h"
#include "CHTLCustom.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <unordered_set>

namespace chtl {

// CHTLUnifiedScanner 实现
CHTLUnifiedScanner::CHTLUnifiedScanner(const std::string& source, std::shared_ptr<CHTLContext> ctx)
    : input(source), position(0), line(1), column(1), 
      currentState(ScannerState::Normal), currentContext(LanguageContext::CHTL),
      context(ctx), currentTokenIndex(0) {
    stateStack.push(currentState);
}

void CHTLUnifiedScanner::scan() {
    tokens.clear();
    currentTokenIndex = 0;
    
    while (position < input.length()) {
        switch (currentState) {
            case ScannerState::Normal:
                scanNormal();
                break;
            case ScannerState::InElement:
                scanElement();
                break;
            case ScannerState::InAttribute:
                scanAttribute();
                break;
            case ScannerState::InStyleBlock:
                scanStyleBlock();
                break;
            case ScannerState::InScriptBlock:
                scanScriptBlock();
                break;
            case ScannerState::InComment:
                scanComment();
                break;
            case ScannerState::InGenerativeComment:
                scanGenerativeComment();
                break;
            case ScannerState::InString:
                // String scanning is handled within other states
                break;
            case ScannerState::InTemplate:
                scanTemplate();
                break;
            case ScannerState::InImport:
                scanImport();
                break;
            case ScannerState::InOrigin:
                scanOrigin();
                break;
        }
    }
    
    // 添加EOF令牌
    emitToken(TokenType::EOF, "");
}

void CHTLUnifiedScanner::scanNormal() {
    if (config.preserveWhitespace && ScannerHelper::isWhitespace(peek())) {
        std::string ws;
        while (position < input.length() && ScannerHelper::isWhitespace(peek()) && !ScannerHelper::isNewline(peek())) {
            ws += advance();
        }
        if (!ws.empty()) {
            emitToken(TokenType::Whitespace, ws);
        }
        return;
    }
    
    if (ScannerHelper::isNewline(peek())) {
        std::string nl;
        nl += advance();
        if (peek() == '\n' && nl[0] == '\r') {
            nl += advance();  // 处理\r\n
        }
        emitToken(TokenType::NewLine, nl);
        return;
    }
    
    // 检查生成性注释
    if (peek() == '-' && peek(1) == '-') {
        advance(); advance();
        pushState(ScannerState::InGenerativeComment);
        scanGenerativeComment();
        return;
    }
    
    // 检查普通注释
    if (peek() == '/' && (peek(1) == '/' || peek(1) == '*')) {
        pushState(ScannerState::InComment);
        scanComment();
        return;
    }
    
    // 检查模板定义
    if (peek() == '[') {
        std::string ahead = input.substr(position, 10);
        if (ahead.find("[Template]") == 0 || ahead.find("[Custom]") == 0) {
            pushState(ScannerState::InTemplate);
            scanTemplate();
            return;
        }
        if (ahead.find("[Import]") == 0) {
            pushState(ScannerState::InImport);
            scanImport();
            return;
        }
        if (ahead.find("[Origin]") == 0) {
            pushState(ScannerState::InOrigin);
            scanOrigin();
            return;
        }
    }
    
    // 检查元素开始
    if (ScannerHelper::isAlpha(peek()) || peek() == '_') {
        std::string word = scanIdentifier();
        
        // 检查是否是style或script块
        if (word == "style") {
            skipWhitespace();
            if (peek() == '{') {
                pushState(ScannerState::InStyleBlock);
                switchContext(LanguageContext::CSS);
                emitToken(TokenType::ElementStart, word);
                advance(); // 消费 {
                return;
            }
        } else if (word == "script") {
            skipWhitespace();
            if (peek() == '{') {
                pushState(ScannerState::InScriptBlock);
                switchContext(LanguageContext::JavaScript);
                emitToken(TokenType::ElementStart, word);
                advance(); // 消费 {
                return;
            }
        }
        
        // 普通元素
        pushState(ScannerState::InElement);
        emitToken(TokenType::ElementStart, word);
        return;
    }
    
    // 其他文本
    std::string text;
    while (position < input.length()) {
        char ch = peek();
        if (ch == '-' && peek(1) == '-') break;
        if (ch == '/' && (peek(1) == '/' || peek(1) == '*')) break;
        if (ch == '[') break;
        if (ScannerHelper::isAlpha(ch) || ch == '_') break;
        if (ScannerHelper::isWhitespace(ch)) break;
        
        text += advance();
    }
    
    if (!text.empty()) {
        emitToken(TokenType::Text, text);
    }
}

void CHTLUnifiedScanner::scanElement() {
    skipWhitespace();
    
    // 检查元素结束
    if (peek() == '{') {
        advance();
        popState(); // 回到Normal状态
        return;
    }
    
    // 扫描属性
    if (ScannerHelper::isAlpha(peek()) || peek() == '_') {
        std::string attrName = scanIdentifier();
        emitToken(TokenType::AttributeName, attrName);
        
        skipWhitespace();
        if (peek() == ':' || peek() == '=') {
            advance(); // 消费 : 或 =
            skipWhitespace();
            
            // 扫描属性值
            if (peek() == '"' || peek() == '\'') {
                char quote = advance();
                std::string value = scanUntil(quote);
                advance(); // 消费结束引号
                emitToken(TokenType::AttributeValue, value);
            } else {
                // 无引号属性值
                std::string value = scanUntil(';');
                value.erase(value.find_last_not_of(" \t\n\r") + 1);
                emitToken(TokenType::AttributeValue, value);
            }
            
            skipWhitespace();
            if (peek() == ';') {
                advance();
            }
        }
    }
}

void CHTLUnifiedScanner::scanStyleBlock() {
    std::stringstream cssContent;
    int braceDepth = 0;
    
    while (position < input.length()) {
        // 检查生成性注释
        if (peek() == '-' && peek(1) == '-' && config.processGenerativeComments) {
            advance(); advance();
            std::string comment = scanUntil('\n');
            GenerativeCommentProcessor processor(context);
            std::string generated = processor.processComment(comment, LanguageContext::CSS);
            cssContent << generated;
            continue;
        }
        
        // 检查@Style使用
        if (peek() == '@' && config.expandStyleGroups) {
            std::string word = scanIdentifier();
            if (word == "@Style") {
                skipWhitespace();
                std::string styleName = scanIdentifier();
                std::string expanded = expandStyleGroup(styleName);
                cssContent << expanded;
                skipWhitespace();
                if (peek() == ';') advance();
                continue;
            } else {
                cssContent << word;
            }
        }
        
        // 检查变量组使用
        if (ScannerHelper::isAlpha(peek()) && config.expandVarGroups) {
            size_t savePos = position;
            std::string word = scanIdentifier();
            skipWhitespace();
            
            if (peek() == '(') {
                advance();
                skipWhitespace();
                std::string varName = scanIdentifier();
                skipWhitespace();
                if (peek() == ')') {
                    advance();
                    std::string value = expandVarGroup(word, varName);
                    cssContent << value;
                    continue;
                }
            }
            
            // 不是变量组，回退
            position = savePos;
            cssContent << advance();
            continue;
        }
        
        // 处理块结束
        if (peek() == '}') {
            if (braceDepth == 0) {
                advance();
                emitToken(TokenType::StyleContent, cssContent.str());
                popState();
                switchContext(LanguageContext::CHTL);
                return;
            } else {
                braceDepth--;
            }
        } else if (peek() == '{') {
            braceDepth++;
        }
        
        cssContent << advance();
    }
}

void CHTLUnifiedScanner::scanScriptBlock() {
    std::stringstream jsContent;
    int braceDepth = 0;
    
    while (position < input.length()) {
        // 检查生成性注释
        if (peek() == '-' && peek(1) == '-' && config.processGenerativeComments) {
            advance(); advance();
            std::string comment = scanUntil('\n');
            GenerativeCommentProcessor processor(context);
            std::string generated = processor.processComment(comment, LanguageContext::JavaScript);
            jsContent << generated;
            continue;
        }
        
        // 处理字符串字面量（避免误判块结束）
        if (peek() == '"' || peek() == '\'' || peek() == '`') {
            char quote = peek();
            jsContent << advance();
            while (position < input.length() && peek() != quote) {
                if (peek() == '\\') {
                    jsContent << advance();
                    if (position < input.length()) {
                        jsContent << advance();
                    }
                } else {
                    jsContent << advance();
                }
            }
            if (position < input.length()) {
                jsContent << advance(); // 结束引号
            }
            continue;
        }
        
        // 处理块结束
        if (peek() == '}') {
            if (braceDepth == 0) {
                advance();
                emitToken(TokenType::ScriptContent, jsContent.str());
                popState();
                switchContext(LanguageContext::CHTL);
                return;
            } else {
                braceDepth--;
            }
        } else if (peek() == '{') {
            braceDepth++;
        }
        
        jsContent << advance();
    }
}

void CHTLUnifiedScanner::scanComment() {
    if (peek() == '/' && peek(1) == '/') {
        advance(); advance();
        std::string comment = scanUntil('\n');
        emitToken(TokenType::NormalComment, "//" + comment);
    } else if (peek() == '/' && peek(1) == '*') {
        advance(); advance();
        std::string comment;
        while (position < input.length()) {
            if (peek() == '*' && peek(1) == '/') {
                advance(); advance();
                break;
            }
            comment += advance();
        }
        emitToken(TokenType::NormalComment, "/*" + comment + "*/");
    }
    
    popState();
}

void CHTLUnifiedScanner::scanGenerativeComment() {
    std::string comment = scanUntil('\n');
    
    if (config.processGenerativeComments) {
        GenerativeCommentProcessor processor(context);
        std::string generated = processor.processComment(comment, currentContext);
        emitToken(TokenType::GenerativeComment, generated, currentContext);
    } else {
        emitToken(TokenType::GenerativeComment, "--" + comment);
    }
    
    popState();
}

void CHTLUnifiedScanner::scanTemplate() {
    // 扫描模板定义 [Template] 或 [Custom]
    std::string content = scanUntil('}');
    if (position < input.length() && peek() == '}') {
        advance();
        content += '}';
    }
    
    emitToken(TokenType::TemplateDefinition, content);
    popState();
}

void CHTLUnifiedScanner::scanImport() {
    // 扫描导入语句
    std::string content = scanUntil(';');
    if (position < input.length() && peek() == ';') {
        advance();
    }
    
    emitToken(TokenType::ImportStatement, content);
    popState();
}

void CHTLUnifiedScanner::scanOrigin() {
    // 扫描原始嵌入
    std::string header = scanUntil('{');
    if (position < input.length() && peek() == '{') {
        advance();
        std::string content = scanBlock('{', '}');
        emitToken(TokenType::OriginContent, header + "{" + content + "}");
    }
    
    popState();
}

// 辅助方法实现
char CHTLUnifiedScanner::peek(size_t offset) const {
    if (position + offset < input.length()) {
        return input[position + offset];
    }
    return '\0';
}

char CHTLUnifiedScanner::advance() {
    if (position < input.length()) {
        char ch = input[position++];
        if (ch == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        return ch;
    }
    return '\0';
}

bool CHTLUnifiedScanner::match(const std::string& expected) {
    if (position + expected.length() <= input.length()) {
        if (input.substr(position, expected.length()) == expected) {
            for (size_t i = 0; i < expected.length(); i++) {
                advance();
            }
            return true;
        }
    }
    return false;
}

void CHTLUnifiedScanner::skipWhitespace() {
    while (position < input.length() && ScannerHelper::isWhitespace(peek())) {
        advance();
    }
}

std::string CHTLUnifiedScanner::scanIdentifier() {
    std::stringstream id;
    
    if (ScannerHelper::isIdentifierStart(peek())) {
        id << advance();
        
        while (position < input.length() && ScannerHelper::isIdentifierPart(peek())) {
            id << advance();
        }
    }
    
    return id.str();
}

std::string CHTLUnifiedScanner::scanUntil(char delimiter) {
    std::stringstream result;
    
    while (position < input.length() && peek() != delimiter) {
        result << advance();
    }
    
    return result.str();
}

std::string CHTLUnifiedScanner::scanBlock(char open, char close) {
    std::stringstream result;
    int depth = 1;
    
    while (position < input.length() && depth > 0) {
        char ch = advance();
        if (ch == open) depth++;
        else if (ch == close) depth--;
        
        if (depth > 0) {
            result << ch;
        }
    }
    
    return result.str();
}

void CHTLUnifiedScanner::pushState(ScannerState state) {
    stateStack.push(state);
    currentState = state;
}

void CHTLUnifiedScanner::popState() {
    if (stateStack.size() > 1) {
        stateStack.pop();
        currentState = stateStack.top();
    }
}

void CHTLUnifiedScanner::switchContext(LanguageContext ctx) {
    currentContext = ctx;
}

void CHTLUnifiedScanner::emitToken(TokenType type, const std::string& value) {
    emitToken(type, value, currentContext);
}

void CHTLUnifiedScanner::emitToken(TokenType type, const std::string& value, LanguageContext ctx) {
    tokens.emplace_back(type, value, line, column, position, ctx);
}

std::string CHTLUnifiedScanner::expandStyleGroup(const std::string& name) {
    if (!templateManager && !customManager) {
        return "@Style " + name + ";";
    }
    
    // 从模板管理器查找
    if (templateManager) {
        auto styleTemplate = templateManager->findTemplate(TemplateType::Style, name);
        if (styleTemplate) {
            std::stringstream expanded;
            auto styles = std::static_pointer_cast<StyleTemplate>(styleTemplate)->getAllStyles();
            for (const auto& [prop, value] : styles) {
                expanded << "    " << prop << ": " << value << ";\n";
            }
            return expanded.str();
        }
    }
    
    // 从自定义管理器查找
    if (customManager) {
        auto customStyle = customManager->findCustom(CustomType::Style, name);
        if (customStyle) {
            std::stringstream expanded;
            auto styleGroup = std::static_pointer_cast<CustomStyleGroup>(customStyle);
            auto styles = styleGroup->getEffectiveStyles();
            for (const auto& [prop, value] : styles) {
                expanded << "    " << prop << ": " << value << ";\n";
            }
            return expanded.str();
        }
    }
    
    reportWarning("Style group '" + name + "' not found");
    return "";
}

std::string CHTLUnifiedScanner::expandVarGroup(const std::string& group, const std::string& var) {
    if (!templateManager && !customManager) {
        return group + "(" + var + ")";
    }
    
    // 从模板管理器查找
    if (templateManager) {
        auto varTemplate = templateManager->findTemplate(TemplateType::Var, group);
        if (varTemplate) {
            auto varGroup = std::static_pointer_cast<VarTemplate>(varTemplate);
            std::string value = varGroup->getVariable(var);
            if (!value.empty()) {
                return value;
            }
        }
    }
    
    // 从自定义管理器查找
    if (customManager) {
        auto customVar = customManager->findCustom(CustomType::Var, group);
        if (customVar) {
            auto varGroup = std::static_pointer_cast<CustomVarGroup>(customVar);
            std::string value = varGroup->getVariable(var);
            if (!value.empty()) {
                return value;
            }
        }
    }
    
    reportWarning("Variable '" + var + "' not found in group '" + group + "'");
    return group + "(" + var + ")";
}

void CHTLUnifiedScanner::reportError(const std::string& message) {
    std::stringstream err;
    err << "Scanner Error at line " << line << ":" << column << " - " << message;
    context->reportError(err.str());
}

void CHTLUnifiedScanner::reportWarning(const std::string& message) {
    std::stringstream warn;
    warn << "Scanner Warning at line " << line << ":" << column << " - " << message;
    context->reportWarning(warn.str());
}

bool CHTLUnifiedScanner::hasMoreTokens() const {
    return currentTokenIndex < tokens.size();
}

Token CHTLUnifiedScanner::nextToken() {
    if (hasMoreTokens()) {
        return tokens[currentTokenIndex++];
    }
    return Token(TokenType::EOF, "", line, column, position, currentContext);
}

Token CHTLUnifiedScanner::peekToken() const {
    if (hasMoreTokens()) {
        return tokens[currentTokenIndex];
    }
    return Token(TokenType::EOF, "", line, column, position, currentContext);
}

void CHTLUnifiedScanner::rewind() {
    currentTokenIndex = 0;
}

// GenerativeCommentProcessor 实现
GenerativeCommentProcessor::GenerativeCommentProcessor(std::shared_ptr<CHTLContext> ctx) 
    : context(ctx) {
    // 注册默认生成器
    generators[LanguageContext::HTML] = [this](const std::string& c, LanguageContext) {
        return generateHTMLComment(c);
    };
    generators[LanguageContext::CSS] = [this](const std::string& c, LanguageContext) {
        return generateCSSComment(c);
    };
    generators[LanguageContext::JavaScript] = [this](const std::string& c, LanguageContext) {
        return generateJSComment(c);
    };
    generators[LanguageContext::CHTL] = [this](const std::string& c, LanguageContext) {
        return generateHTMLComment(c);  // CHTL默认生成HTML注释
    };
}

std::string GenerativeCommentProcessor::processComment(const std::string& content, LanguageContext context) {
    auto it = generators.find(context);
    if (it != generators.end()) {
        return it->second(content, context);
    }
    
    // 默认返回HTML注释
    return generateHTMLComment(content);
}

void GenerativeCommentProcessor::registerGenerator(LanguageContext lang, CommentGenerator gen) {
    generators[lang] = gen;
}

std::string GenerativeCommentProcessor::generateHTMLComment(const std::string& content) {
    return formatComment(content, "<!-- ", " -->", 80);
}

std::string GenerativeCommentProcessor::generateCSSComment(const std::string& content) {
    return formatComment(content, "/* ", " */", 80);
}

std::string GenerativeCommentProcessor::generateJSComment(const std::string& content) {
    // 对于多行内容，使用块注释；单行使用行注释
    if (content.find('\n') != std::string::npos) {
        return formatComment(content, "/* ", " */", 80);
    } else {
        return "// " + content;
    }
}

std::string GenerativeCommentProcessor::formatComment(const std::string& content, 
                                                    const std::string& prefix, 
                                                    const std::string& suffix, 
                                                    int width) {
    std::vector<std::string> lines = wrapText(content, width - prefix.length() - suffix.length());
    
    if (lines.size() == 1) {
        return prefix + lines[0] + suffix;
    }
    
    // 多行格式化
    std::stringstream formatted;
    formatted << prefix << "\n";
    
    for (const auto& line : lines) {
        formatted << " * " << line << "\n";
    }
    
    formatted << " *" << suffix;
    return formatted.str();
}

std::vector<std::string> GenerativeCommentProcessor::wrapText(const std::string& text, int width) {
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;
    
    while (std::getline(ss, line)) {
        if (line.length() <= width) {
            lines.push_back(line);
        } else {
            // 简单的断行处理
            size_t pos = 0;
            while (pos < line.length()) {
                size_t len = std::min(static_cast<size_t>(width), line.length() - pos);
                
                // 尝试在空格处断行
                if (pos + len < line.length()) {
                    size_t spacePos = line.rfind(' ', pos + len);
                    if (spacePos != std::string::npos && spacePos > pos) {
                        len = spacePos - pos;
                    }
                }
                
                lines.push_back(line.substr(pos, len));
                pos += len;
                
                // 跳过断行处的空格
                while (pos < line.length() && line[pos] == ' ') {
                    pos++;
                }
            }
        }
    }
    
    return lines;
}

// ScannerHelper 实现
namespace ScannerHelper {
    
bool isWhitespace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\r';
}

bool isNewline(char ch) {
    return ch == '\n';
}

bool isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isAlphaNumeric(char ch) {
    return isAlpha(ch) || isDigit(ch);
}

bool isIdentifierStart(char ch) {
    return isAlpha(ch) || ch == '_' || ch == '@';
}

bool isIdentifierPart(char ch) {
    return isAlphaNumeric(ch) || ch == '_' || ch == '-';
}

bool isCHTLKeyword(const std::string& word) {
    static const std::unordered_set<std::string> keywords = {
        "Template", "Custom", "Import", "Origin", "Namespace",
        "Style", "Element", "Var", "inherit", "delete", "insert",
        "from", "as", "except", "text", "style", "script"
    };
    return keywords.find(word) != keywords.end();
}

bool isCSSProperty(const std::string& word) {
    static const std::unordered_set<std::string> properties = {
        "color", "background", "background-color", "font-size",
        "font-family", "margin", "padding", "border", "width",
        "height", "display", "position", "top", "left", "right",
        "bottom", "z-index", "opacity", "transform", "transition"
    };
    return properties.find(word) != properties.end();
}

bool isJSKeyword(const std::string& word) {
    static const std::unordered_set<std::string> keywords = {
        "var", "let", "const", "function", "class", "if", "else",
        "for", "while", "do", "switch", "case", "break", "continue",
        "return", "try", "catch", "finally", "throw", "new", "this",
        "async", "await", "import", "export", "default"
    };
    return keywords.find(word) != keywords.end();
}

LanguageContext inferContextFromElement(const std::string& element) {
    if (element == "style") return LanguageContext::CSS;
    if (element == "script") return LanguageContext::JavaScript;
    return LanguageContext::HTML;
}

LanguageContext inferContextFromContent(const std::string& content) {
    // 简单的启发式推导
    if (content.find('{') != std::string::npos && 
        content.find(':') != std::string::npos &&
        content.find(';') != std::string::npos) {
        return LanguageContext::CSS;
    }
    
    if (content.find("function") != std::string::npos ||
        content.find("var ") != std::string::npos ||
        content.find("let ") != std::string::npos ||
        content.find("const ") != std::string::npos) {
        return LanguageContext::JavaScript;
    }
    
    if (content.find('<') != std::string::npos &&
        content.find('>') != std::string::npos) {
        return LanguageContext::HTML;
    }
    
    return LanguageContext::CHTL;
}

std::string stateToString(ScannerState state) {
    switch (state) {
        case ScannerState::Normal: return "Normal";
        case ScannerState::InElement: return "InElement";
        case ScannerState::InAttribute: return "InAttribute";
        case ScannerState::InStyleBlock: return "InStyleBlock";
        case ScannerState::InScriptBlock: return "InScriptBlock";
        case ScannerState::InComment: return "InComment";
        case ScannerState::InGenerativeComment: return "InGenerativeComment";
        case ScannerState::InString: return "InString";
        case ScannerState::InTemplate: return "InTemplate";
        case ScannerState::InImport: return "InImport";
        case ScannerState::InOrigin: return "InOrigin";
        default: return "Unknown";
    }
}

std::string contextToString(LanguageContext context) {
    switch (context) {
        case LanguageContext::CHTL: return "CHTL";
        case LanguageContext::HTML: return "HTML";
        case LanguageContext::CSS: return "CSS";
        case LanguageContext::JavaScript: return "JavaScript";
        default: return "Unknown";
    }
}

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Text: return "Text";
        case TokenType::ElementStart: return "ElementStart";
        case TokenType::ElementEnd: return "ElementEnd";
        case TokenType::AttributeName: return "AttributeName";
        case TokenType::AttributeValue: return "AttributeValue";
        case TokenType::StyleGroupUsage: return "StyleGroupUsage";
        case TokenType::VarGroupUsage: return "VarGroupUsage";
        case TokenType::GenerativeComment: return "GenerativeComment";
        case TokenType::NormalComment: return "NormalComment";
        case TokenType::ScriptContent: return "ScriptContent";
        case TokenType::StyleContent: return "StyleContent";
        case TokenType::TemplateDefinition: return "TemplateDefinition";
        case TokenType::ImportStatement: return "ImportStatement";
        case TokenType::OriginContent: return "OriginContent";
        case TokenType::Whitespace: return "Whitespace";
        case TokenType::NewLine: return "NewLine";
        case TokenType::EOF: return "EOF";
        default: return "Unknown";
    }
}

} // namespace ScannerHelper

// ScannerContextInferencer 实现
ScannerContextInferencer::ScannerContextInferencer() 
    : currentContext(LanguageContext::CHTL) {
    initializeElementContextMap();
}

void ScannerContextInferencer::initializeElementContextMap() {
    elementContextMap["style"] = LanguageContext::CSS;
    elementContextMap["script"] = LanguageContext::JavaScript;
    elementContextMap["svg"] = LanguageContext::HTML;
    elementContextMap["math"] = LanguageContext::HTML;
}

void ScannerContextInferencer::enterElement(const std::string& element) {
    elementStack.push(element);
    
    auto it = elementContextMap.find(element);
    if (it != elementContextMap.end()) {
        currentContext = it->second;
    }
}

void ScannerContextInferencer::exitElement() {
    if (!elementStack.empty()) {
        elementStack.pop();
    }
    
    // 推导新的上下文
    currentContext = inferContext();
}

LanguageContext ScannerContextInferencer::inferContext() const {
    if (elementStack.empty()) {
        return LanguageContext::CHTL;
    }
    
    // 根据栈顶元素推导
    const std::string& top = elementStack.top();
    auto it = elementContextMap.find(top);
    if (it != elementContextMap.end()) {
        return it->second;
    }
    
    return LanguageContext::HTML;
}

LanguageContext ScannerContextInferencer::inferFromAttribute(const std::string& attr, 
                                                            const std::string& value) {
    if (attr == "style") {
        return LanguageContext::CSS;
    }
    
    if (attr.find("on") == 0) {  // onclick, onmouseover等
        return LanguageContext::JavaScript;
    }
    
    return currentContext;
}

LanguageContext ScannerContextInferencer::inferFromContent(const std::string& content) {
    return ScannerHelper::inferContextFromContent(content);
}

void ScannerContextInferencer::reset() {
    while (!elementStack.empty()) {
        elementStack.pop();
    }
    currentContext = LanguageContext::CHTL;
}

} // namespace chtl