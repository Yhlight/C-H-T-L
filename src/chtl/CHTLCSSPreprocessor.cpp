#include "CHTLCSSPreprocessor.h"
#include "CHTLCSSCompiler.h"
#include <sstream>
#include <algorithm>
#include <cctype>

namespace chtl {

// CSSPreprocessContext 实现
CSSPreprocessContext::CSSPreprocessContext() 
    : currentState(CSSPreprocessState::Normal), currentLine(1), currentColumn(1) {
    stateStack.push(currentState);
}

void CSSPreprocessContext::pushState(CSSPreprocessState state) {
    stateStack.push(state);
    currentState = state;
}

void CSSPreprocessContext::popState() {
    if (stateStack.size() > 1) {
        stateStack.pop();
        currentState = stateStack.top();
    }
}

void CSSPreprocessContext::setCurrentGroup(const std::string& name, const std::string& type) {
    currentGroupName = name;
    currentGroupType = type;
}

void CSSPreprocessContext::clearCurrentGroup() {
    currentGroupName.clear();
    currentGroupType.clear();
}

// CSSPreprocessScanner 实现
CSSPreprocessScanner::CSSPreprocessScanner(const std::string& css) 
    : input(css), position(0), line(1), column(1) {}

char CSSPreprocessScanner::peek() const {
    if (hasMore()) {
        return input[position];
    }
    return '\0';
}

char CSSPreprocessScanner::advance() {
    if (hasMore()) {
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

std::string CSSPreprocessScanner::peekWord() {
    size_t start = position;
    while (hasMore() && (std::isalnum(peek()) || peek() == '-' || peek() == '_')) {
        advance();
    }
    std::string word = input.substr(start, position - start);
    position = start;  // 回退
    return word;
}

bool CSSPreprocessScanner::match(const std::string& expected) {
    size_t start = position;
    for (char ch : expected) {
        if (advance() != ch) {
            position = start;  // 回退
            return false;
        }
    }
    return true;
}

void CSSPreprocessScanner::skipWhitespace() {
    while (hasMore() && std::isspace(peek())) {
        advance();
    }
}

void CSSPreprocessScanner::skipComment() {
    if (peek() == '/' && position + 1 < input.length()) {
        if (input[position + 1] == '*') {
            advance(); advance(); // 跳过 /*
            while (hasMore()) {
                if (peek() == '*' && position + 1 < input.length() && input[position + 1] == '/') {
                    advance(); advance(); // 跳过 */
                    break;
                }
                advance();
            }
        } else if (input[position + 1] == '/') {
            advance(); advance(); // 跳过 //
            while (hasMore() && peek() != '\n') {
                advance();
            }
        }
    }
}

std::string CSSPreprocessScanner::scanIdentifier() {
    std::stringstream id;
    
    // 首字符必须是字母、下划线或@
    if (std::isalpha(peek()) || peek() == '_' || peek() == '@') {
        id << advance();
        
        // 后续字符可以是字母、数字、下划线、连字符
        while (hasMore() && (std::isalnum(peek()) || peek() == '_' || peek() == '-')) {
            id << advance();
        }
    }
    
    return id.str();
}

std::string CSSPreprocessScanner::scanUntil(char delimiter) {
    std::stringstream result;
    while (hasMore() && peek() != delimiter) {
        result << advance();
    }
    return result.str();
}

std::string CSSPreprocessScanner::scanUntil(const std::string& delimiter) {
    std::stringstream result;
    while (hasMore()) {
        if (match(delimiter)) {
            position -= delimiter.length();  // 回退，不消费分隔符
            break;
        }
        result << advance();
    }
    return result.str();
}

std::string CSSPreprocessScanner::scanBlock(char open, char close) {
    std::stringstream result;
    int depth = 0;
    
    // 跳过开始字符
    if (peek() == open) {
        advance();
        depth = 1;
    }
    
    while (hasMore() && depth > 0) {
        char ch = peek();
        if (ch == open) {
            depth++;
        } else if (ch == close) {
            depth--;
            if (depth == 0) {
                advance();  // 消费结束字符
                break;
            }
        }
        result << advance();
    }
    
    return result.str();
}

// CSSPreprocessor 实现
CSSPreprocessor::CSSPreprocessor(std::shared_ptr<CHTLContext> ctx) : context(ctx) {}

std::string CSSPreprocessor::preprocess(const std::string& css) {
    scanner = std::make_unique<CSSPreprocessScanner>(css);
    output.str("");
    output.clear();
    
    while (scanner->hasMore()) {
        scanner->skipWhitespace();
        scanner->skipComment();
        
        if (!scanner->hasMore()) break;
        
        // 更新位置信息
        preprocessContext.updatePosition(scanner->getLine(), scanner->getColumn());
        
        switch (preprocessContext.getState()) {
            case CSSPreprocessState::Normal:
                processNormal();
                break;
            case CSSPreprocessState::InStyleGroup:
                processStyleGroupUsage();
                break;
            case CSSPreprocessState::InVarGroup:
                processVarGroupUsage();
                break;
            case CSSPreprocessState::InSelector:
                processSelector();
                break;
            case CSSPreprocessState::InDeclaration:
                processDeclaration();
                break;
            case CSSPreprocessState::InValue:
                processValue();
                break;
        }
    }
    
    return output.str();
}

void CSSPreprocessor::processNormal() {
    char ch = scanner->peek();
    
    // 检查是否是@规则
    if (ch == '@') {
        processAtRule();
        return;
    }
    
    // 检查是否是选择器开始
    if (std::isalpha(ch) || ch == '.' || ch == '#' || ch == '*' || ch == '[') {
        preprocessContext.pushState(CSSPreprocessState::InSelector);
        processSelector();
        return;
    }
    
    // 其他情况，直接输出
    output << scanner->advance();
}

void CSSPreprocessor::processAtRule() {
    std::string atWord = scanner->scanIdentifier();
    
    // 检查是否是@Style或@Var使用
    if (atWord == "@Style") {
        scanner->skipWhitespace();
        std::string styleName = scanner->scanIdentifier();
        
        if (!styleName.empty()) {
            output << expandStyleGroup(styleName);
        } else {
            reportError("Expected style group name after @Style");
        }
    } else if (atWord == "@Var") {
        // @Var不能直接在CSS中使用，只能在值中使用
        reportError("@Var can only be used within property values");
    } else {
        // 其他@规则，直接输出
        output << atWord;
    }
}

void CSSPreprocessor::processStyleGroupUsage() {
    // 样式组使用已经在processAtRule中处理
    preprocessContext.popState();
}

void CSSPreprocessor::processVarGroupUsage() {
    // 变量组使用在processValue中处理
    preprocessContext.popState();
}

void CSSPreprocessor::processSelector() {
    // 处理选择器，查找 {
    while (scanner->hasMore()) {
        char ch = scanner->peek();
        
        if (ch == '{') {
            output << scanner->advance();
            preprocessContext.popState();
            preprocessContext.pushState(CSSPreprocessState::InDeclaration);
            return;
        }
        
        output << scanner->advance();
    }
}

void CSSPreprocessor::processDeclaration() {
    scanner->skipWhitespace();
    
    char ch = scanner->peek();
    
    // 检查是否是块结束
    if (ch == '}') {
        output << scanner->advance();
        preprocessContext.popState();
        return;
    }
    
    // 检查是否是@Style使用
    if (ch == '@') {
        std::string atWord = scanner->peekWord();
        if (atWord == "@Style") {
            scanner->scanIdentifier();  // 消费@Style
            scanner->skipWhitespace();
            std::string styleName = scanner->scanIdentifier();
            
            if (!styleName.empty()) {
                std::string expanded = expandStyleGroup(styleName);
                output << expanded;
                
                // 跳过分号
                scanner->skipWhitespace();
                if (scanner->peek() == ';') {
                    scanner->advance();
                }
            }
            return;
        }
    }
    
    // 处理普通属性声明
    std::string property = scanner->scanUntil(':');
    if (scanner->peek() == ':') {
        output << property << scanner->advance();  // 输出属性名和冒号
        
        scanner->skipWhitespace();
        preprocessContext.pushState(CSSPreprocessState::InValue);
        processValue();
    }
}

void CSSPreprocessor::processValue() {
    std::stringstream valueBuffer;
    
    while (scanner->hasMore()) {
        scanner->skipWhitespace();
        char ch = scanner->peek();
        
        // 值结束
        if (ch == ';' || ch == '}') {
            output << valueBuffer.str();
            if (ch == ';') {
                output << scanner->advance();
            }
            preprocessContext.popState();
            return;
        }
        
        // 检查是否是变量组使用
        if (std::isalpha(ch) || ch == '_') {
            std::string word = scanner->peekWord();
            
            // 检查是否是VarGroup(varName)模式
            size_t savePos = scanner->getPosition();
            scanner->scanIdentifier();  // 消费标识符
            scanner->skipWhitespace();
            
            if (scanner->peek() == '(') {
                scanner->advance();  // 消费 (
                scanner->skipWhitespace();
                std::string varName = scanner->scanIdentifier();
                scanner->skipWhitespace();
                
                if (scanner->peek() == ')') {
                    scanner->advance();  // 消费 )
                    
                    // 这是一个变量组使用
                    std::string value = resolveVariable(word, varName);
                    valueBuffer << value;
                    continue;
                }
            }
            
            // 不是变量组使用，回退并输出原文
            size_t currentPos = scanner->getPosition();
            for (size_t i = savePos; i < currentPos; i++) {
                valueBuffer << input[i];
            }
        } else {
            valueBuffer << scanner->advance();
        }
    }
    
    output << valueBuffer.str();
    preprocessContext.popState();
}

std::string CSSPreprocessor::expandStyleGroup(const std::string& name) {
    // 先检查缓存
    auto it = resolvedStyleGroups.find(name);
    if (it != resolvedStyleGroups.end()) {
        return it->second;
    }
    
    std::stringstream expanded;
    
    // 从模板管理器获取样式组
    if (templateManager) {
        auto styleTemplate = templateManager->findTemplate(TemplateType::Style, name);
        if (styleTemplate) {
            auto styles = std::static_pointer_cast<StyleTemplate>(styleTemplate)->getAllStyles();
            for (const auto& [prop, value] : styles) {
                expanded << "    " << prop << ": " << value << ";\n";
            }
            
            resolvedStyleGroups[name] = expanded.str();
            return expanded.str();
        }
    }
    
    // 从自定义管理器获取样式组
    if (customManager) {
        auto customStyle = customManager->findCustom(CustomType::Style, name);
        if (customStyle) {
            auto styleGroup = std::static_pointer_cast<CustomStyleGroup>(customStyle);
            auto styles = styleGroup->getEffectiveStyles();
            
            for (const auto& [prop, value] : styles) {
                if (styleGroup->requiresValue(prop) && value.empty()) {
                    reportWarning("Style property '" + prop + "' requires a value");
                    continue;
                }
                expanded << "    " << prop << ": " << value << ";\n";
            }
            
            resolvedStyleGroups[name] = expanded.str();
            return expanded.str();
        }
    }
    
    reportError("Style group '" + name + "' not found");
    return "";
}

std::string CSSPreprocessor::resolveVariable(const std::string& varGroup, const std::string& varName) {
    // 构建缓存键
    std::string cacheKey = varGroup + "." + varName;
    
    // 检查缓存
    auto groupIt = resolvedVarGroups.find(varGroup);
    if (groupIt != resolvedVarGroups.end()) {
        auto varIt = groupIt->second.find(varName);
        if (varIt != groupIt->second.end()) {
            return varIt->second;
        }
    }
    
    // 从模板管理器获取变量组
    if (templateManager) {
        auto varTemplate = templateManager->findTemplate(TemplateType::Var, varGroup);
        if (varTemplate) {
            auto varGroupTemplate = std::static_pointer_cast<VarTemplate>(varTemplate);
            std::string value = varGroupTemplate->getVariable(varName);
            
            if (!value.empty()) {
                resolvedVarGroups[varGroup][varName] = value;
                return value;
            }
        }
    }
    
    // 从自定义管理器获取变量组
    if (customManager) {
        auto customVar = customManager->findCustom(CustomType::Var, varGroup);
        if (customVar) {
            auto varGroupCustom = std::static_pointer_cast<CustomVarGroup>(customVar);
            std::string value = varGroupCustom->getVariable(varName);
            
            if (!value.empty()) {
                resolvedVarGroups[varGroup][varName] = value;
                return value;
            }
        }
    }
    
    reportError("Variable '" + varName + "' not found in group '" + varGroup + "'");
    return "";
}

void CSSPreprocessor::reportError(const std::string& message) {
    std::stringstream err;
    err << "CSS Preprocessor Error at line " << preprocessContext.getLine() 
        << ":" << preprocessContext.getColumn() << " - " << message;
    context->reportError(err.str());
}

void CSSPreprocessor::reportWarning(const std::string& message) {
    std::stringstream warn;
    warn << "CSS Preprocessor Warning at line " << preprocessContext.getLine() 
         << ":" << preprocessContext.getColumn() << " - " << message;
    context->reportWarning(warn.str());
}

// CHTLEnhancedCSSCompiler 实现
CHTLEnhancedCSSCompiler::CHTLEnhancedCSSCompiler(std::shared_ptr<CHTLContext> ctx) 
    : context(ctx) {
    preprocessor = std::make_shared<CSSPreprocessor>(ctx);
    compiler = std::make_shared<CSSCompiler>(ctx);
}

void CHTLEnhancedCSSCompiler::setTemplateManager(std::shared_ptr<TemplateManager> mgr) {
    preprocessor->setTemplateManager(mgr);
}

void CHTLEnhancedCSSCompiler::setCustomManager(std::shared_ptr<CustomManager> mgr) {
    preprocessor->setCustomManager(mgr);
}

std::string CHTLEnhancedCSSCompiler::compile(const std::string& css) {
    // 检查缓存
    auto it = preprocessCache.find(css);
    if (it != preprocessCache.end()) {
        return compiler->compile(it->second);
    }
    
    // 预处理CSS
    std::string preprocessedCSS = preprocessor->preprocess(css);
    preprocessCache[css] = preprocessedCSS;
    
    // 编译预处理后的CSS
    return compiler->compile(preprocessedCSS);
}

void CHTLEnhancedCSSCompiler::setMinify(bool value) {
    compiler->setMinify(value);
}

void CHTLEnhancedCSSCompiler::setPreserveComments(bool value) {
    compiler->setPreserveComments(value);
}

bool CHTLEnhancedCSSCompiler::validate(const std::string& css, std::vector<std::string>& errors) {
    // 先预处理
    std::string preprocessedCSS = preprocessor->preprocess(css);
    
    // 再验证
    return compiler->validate(preprocessedCSS, errors);
}

// CSSContextInferencer 实现
CSSContextInferencer::CSSContextInferencer(std::shared_ptr<CHTLContext> ctx) : context(ctx) {}

CSSContextInferencer::InferredContext CSSContextInferencer::analyzeContext(const std::string& css, size_t position) {
    InferredContext ctx;
    
    // 分析CSS以确定上下文
    analyzeSelectors(css);
    analyzeDeclarations(css);
    analyzeMediaQueries(css);
    
    // 分析特定位置的上下文
    if (position < css.length()) {
        // 查找当前位置之前最近的属性名
        size_t colonPos = css.rfind(':', position);
        if (colonPos != std::string::npos) {
            size_t propStart = css.rfind('\n', colonPos);
            if (propStart == std::string::npos) propStart = 0;
            
            std::string property = css.substr(propStart, colonPos - propStart);
            property.erase(0, property.find_first_not_of(" \t\n\r"));
            property.erase(property.find_last_not_of(" \t\n\r") + 1);
            
            // 根据属性推导期望的类型
            if (isColorProperty(property)) {
                ctx.inferredTypes[property] = "color";
            } else if (isDimensionProperty(property)) {
                ctx.inferredTypes[property] = "dimension";
            } else if (isFontProperty(property)) {
                ctx.inferredTypes[property] = "font";
            }
        }
    }
    
    ctx.availableStyleGroups = getAvailableStyleGroups();
    ctx.availableVarGroups = getAvailableVarGroups();
    
    return ctx;
}

std::vector<std::string> CSSContextInferencer::getAvailableStyleGroups() const {
    // Scanner已经处理了样式组的识别和展开
    // 这里只返回空列表，实际功能由Scanner完成
    return {};
}

std::vector<std::string> CSSContextInferencer::getAvailableVarGroups() const {
    // Scanner已经处理了变量组的识别和展开
    // 这里只返回空列表，实际功能由Scanner完成
    return {};
}

void CSSContextInferencer::analyzeSelectors(const std::string& css) {
    // Scanner已经处理了CHTL扩展选择器
    // CSS编译器只需要处理标准CSS
}



void CSSContextInferencer::analyzeDeclarations(const std::string& css) {
    // Scanner已经处理了CHTL变量引用
    // CSS编译器只需要处理标准CSS
}



void CSSContextInferencer::analyzeMediaQueries(const std::string& css) {
    // 媒体查询是标准CSS特性，不需要特殊处理
    // CSS编译器会直接处理
}

bool CSSContextInferencer::isColorProperty(const std::string& property) {
    static const std::unordered_set<std::string> colorProps = {
        "color", "background-color", "border-color", "outline-color",
        "text-decoration-color", "column-rule-color", "caret-color"
    };
    return colorProps.find(property) != colorProps.end();
}

bool CSSContextInferencer::isDimensionProperty(const std::string& property) {
    static const std::unordered_set<std::string> dimProps = {
        "width", "height", "margin", "padding", "border-width",
        "font-size", "line-height", "letter-spacing", "word-spacing"
    };
    return dimProps.find(property) != dimProps.end();
}

bool CSSContextInferencer::isFontProperty(const std::string& property) {
    static const std::unordered_set<std::string> fontProps = {
        "font-family", "font-style", "font-weight", "font-variant"
    };
    return fontProps.find(property) != fontProps.end();
}

} // namespace chtl