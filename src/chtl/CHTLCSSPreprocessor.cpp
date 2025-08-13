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
    std::vector<std::string> groups;
    
    if (!context) {
        return groups;
    }
    
    // 从模板管理器获取模板样式组
    auto templateMgr = context->getTemplateManager();
    if (templateMgr) {
        auto templates = templateMgr->getAllTemplates();
        for (const auto& [name, tmpl] : templates) {
            if (tmpl && tmpl->type == TemplateType::Style) {
                groups.push_back(name);
            }
        }
    }
    
    // 从自定义管理器获取自定义样式组
    auto customMgr = context->getCustomManager();
    if (customMgr) {
        auto customs = customMgr->getAllCustoms();
        for (const auto& [name, custom] : customs) {
            if (custom && custom->type == CustomType::Style) {
                groups.push_back(name);
            }
        }
    }
    
    // 从当前命名空间获取可见的样式组
    auto namespaceMgr = context->getNamespaceManager();
    if (namespaceMgr) {
        auto currentNs = namespaceMgr->getCurrentNamespace();
        if (currentNs) {
            for (const auto& item : currentNs->items) {
                if (item->type == NamespaceItemType::StyleGroup) {
                    groups.push_back(item->name);
                }
            }
        }
    }
    
    return groups;
}

std::vector<std::string> CSSContextInferencer::getAvailableVarGroups() const {
    std::vector<std::string> groups;
    
    if (!context) {
        return groups;
    }
    
    // 从模板管理器获取模板变量组
    auto templateMgr = context->getTemplateManager();
    if (templateMgr) {
        auto templates = templateMgr->getAllTemplates();
        for (const auto& [name, tmpl] : templates) {
            if (tmpl && tmpl->type == TemplateType::Var) {
                groups.push_back(name);
            }
        }
    }
    
    // 从自定义管理器获取自定义变量组
    auto customMgr = context->getCustomManager();
    if (customMgr) {
        auto customs = customMgr->getAllCustoms();
        for (const auto& [name, custom] : customs) {
            if (custom && custom->type == CustomType::Var) {
                groups.push_back(name);
            }
        }
    }
    
    // 从当前命名空间获取可见的变量组
    auto namespaceMgr = context->getNamespaceManager();
    if (namespaceMgr) {
        auto currentNs = namespaceMgr->getCurrentNamespace();
        if (currentNs) {
            for (const auto& item : currentNs->items) {
                if (item->type == NamespaceItemType::VarGroup) {
                    groups.push_back(item->name);
                }
            }
        }
    }
    
    return groups;
}

void CSSContextInferencer::analyzeSelectors(const std::string& css) {
    // 分析CSS中的选择器，提取有用信息
    std::regex selectorRegex(R"(([^{]+)\s*\{[^}]*\})");
    auto begin = std::sregex_iterator(css.begin(), css.end(), selectorRegex);
    auto end = std::sregex_iterator();
    
    for (auto it = begin; it != end; ++it) {
        std::string selector = (*it)[1];
        
        // 去除首尾空白
        selector.erase(0, selector.find_first_not_of(" \t\n\r"));
        selector.erase(selector.find_last_not_of(" \t\n\r") + 1);
        
        // 分析选择器类型
        analyzeSelectorType(selector);
        
        // 分析选择器特异性
        calculateSpecificity(selector);
        
        // 检查是否使用了CHTL扩展选择器
        if (selector.find("@") != std::string::npos) {
            // CHTL样式组引用
            analyzeStyleGroupReference(selector);
        }
        
        if (selector.find("~") != std::string::npos) {
            // CHTL增强选择器
            analyzeEnhancedSelector(selector);
        }
    }
}

void CSSContextInferencer::analyzeSelectorType(const std::string& selector) {
    // 分类选择器类型
    if (selector[0] == '#') {
        // ID选择器
        currentContext.inferredTypes[selector] = "id";
    } else if (selector[0] == '.') {
        // 类选择器
        currentContext.inferredTypes[selector] = "class";
    } else if (selector.find('[') != std::string::npos) {
        // 属性选择器
        currentContext.inferredTypes[selector] = "attribute";
    } else if (selector.find(':') != std::string::npos) {
        // 伪类/伪元素选择器
        currentContext.inferredTypes[selector] = "pseudo";
    } else {
        // 元素选择器
        currentContext.inferredTypes[selector] = "element";
    }
}

void CSSContextInferencer::calculateSpecificity(const std::string& selector) {
    // 计算选择器特异性 (ID, Class, Element)
    int idCount = 0;
    int classCount = 0;
    int elementCount = 0;
    
    // 统计ID选择器
    size_t pos = 0;
    while ((pos = selector.find('#', pos)) != std::string::npos) {
        idCount++;
        pos++;
    }
    
    // 统计类选择器和属性选择器
    pos = 0;
    while ((pos = selector.find('.', pos)) != std::string::npos) {
        classCount++;
        pos++;
    }
    pos = 0;
    while ((pos = selector.find('[', pos)) != std::string::npos) {
        classCount++;
        pos = selector.find(']', pos) + 1;
    }
    
    // 统计伪类
    pos = 0;
    while ((pos = selector.find(':', pos)) != std::string::npos) {
        if (selector.substr(pos, 2) != "::") {  // 排除伪元素
            classCount++;
        }
        pos++;
    }
    
    // 统计元素选择器（简化处理）
    std::istringstream iss(selector);
    std::string token;
    while (iss >> token) {
        if (std::isalpha(token[0])) {
            elementCount++;
        }
    }
    
    // 存储特异性信息
    std::string specificity = std::to_string(idCount) + "," + 
                             std::to_string(classCount) + "," + 
                             std::to_string(elementCount);
    currentContext.inferredTypes[selector + "_specificity"] = specificity;
}

void CSSContextInferencer::analyzeStyleGroupReference(const std::string& selector) {
    // 分析样式组引用
    std::regex styleGroupRegex(R"(@(\w+))");
    std::smatch match;
    
    if (std::regex_search(selector, match, styleGroupRegex)) {
        std::string groupName = match[1];
        
        // 检查样式组是否可用
        auto availableGroups = getAvailableStyleGroups();
        bool isAvailable = std::find(availableGroups.begin(), 
                                    availableGroups.end(), 
                                    groupName) != availableGroups.end();
        
        if (isAvailable) {
            currentContext.inferredTypes["@" + groupName] = "available_style_group";
        } else {
            currentContext.inferredTypes["@" + groupName] = "unknown_style_group";
        }
    }
}

void CSSContextInferencer::analyzeEnhancedSelector(const std::string& selector) {
    // 分析CHTL增强选择器
    if (selector.find("~") != std::string::npos) {
        // 祖先选择器
        currentContext.inferredTypes[selector] = "enhanced_ancestor";
    }
}

void CSSContextInferencer::analyzeDeclarations(const std::string& css) {
    // 分析CSS声明（属性:值对）
    std::regex ruleRegex(R"(\{([^}]*)\})");
    auto ruleBegin = std::sregex_iterator(css.begin(), css.end(), ruleRegex);
    auto ruleEnd = std::sregex_iterator();
    
    for (auto it = ruleBegin; it != ruleEnd; ++it) {
        std::string declarations = (*it)[1];
        
        // 解析每个声明
        std::regex declRegex(R"(([^:;\s]+)\s*:\s*([^;]+);?)");
        auto declBegin = std::sregex_iterator(declarations.begin(), declarations.end(), declRegex);
        auto declEnd = std::sregex_iterator();
        
        for (auto decl = declBegin; decl != declEnd; ++decl) {
            std::string property = (*decl)[1];
            std::string value = (*decl)[2];
            
            // 去除首尾空白
            property.erase(0, property.find_first_not_of(" \t\n\r"));
            property.erase(property.find_last_not_of(" \t\n\r") + 1);
            value.erase(0, value.find_first_not_of(" \t\n\r"));
            value.erase(value.find_last_not_of(" \t\n\r") + 1);
            
            // 分析属性类型
            analyzePropertyType(property, value);
            
            // 检查CHTL扩展语法
            if (value.find("@") != std::string::npos) {
                analyzeVariableReference(property, value);
            }
            
            // 检查计算表达式
            if (value.find("calc(") != std::string::npos || 
                value.find("var(") != std::string::npos) {
                analyzeComputedValue(property, value);
            }
        }
    }
}

void CSSContextInferencer::analyzePropertyType(const std::string& property, const std::string& value) {
    // 推导属性类型
    if (isColorProperty(property)) {
        currentContext.inferredTypes[property] = "color";
        
        // 验证颜色值格式
        if (value.find("#") == 0 || 
            value.find("rgb") == 0 || 
            value.find("hsl") == 0) {
            currentContext.inferredTypes[property + "_value"] = "valid_color";
        }
    } else if (isDimensionProperty(property)) {
        currentContext.inferredTypes[property] = "dimension";
        
        // 验证尺寸值格式
        std::regex dimRegex(R"(\d+(?:\.\d+)?(?:px|em|rem|%|vh|vw))");
        if (std::regex_match(value, dimRegex)) {
            currentContext.inferredTypes[property + "_value"] = "valid_dimension";
        }
    } else if (isFontProperty(property)) {
        currentContext.inferredTypes[property] = "font";
    }
    
    // 检查供应商前缀
    if (property.find("-webkit-") == 0 || 
        property.find("-moz-") == 0 || 
        property.find("-ms-") == 0) {
        currentContext.inferredTypes[property + "_vendor"] = "prefixed";
    }
}

void CSSContextInferencer::analyzeVariableReference(const std::string& property, const std::string& value) {
    // 分析CHTL变量引用
    std::regex varRefRegex(R"(@(\w+)\.(\w+))");
    std::smatch match;
    
    if (std::regex_search(value, match, varRefRegex)) {
        std::string varGroup = match[1];
        std::string varName = match[2];
        
        // 检查变量组是否可用
        auto availableVars = getAvailableVarGroups();
        bool isAvailable = std::find(availableVars.begin(), 
                                    availableVars.end(), 
                                    varGroup) != availableVars.end();
        
        if (isAvailable) {
            currentContext.inferredTypes["@" + varGroup + "." + varName] = "available_variable";
            
            // 根据属性类型验证变量类型匹配
            if (isColorProperty(property)) {
                // 检查是否是颜色变量
                currentContext.inferredTypes[property + "_var_type"] = "should_be_color";
            } else if (isDimensionProperty(property)) {
                // 检查是否是尺寸变量
                currentContext.inferredTypes[property + "_var_type"] = "should_be_dimension";
            }
        } else {
            currentContext.inferredTypes["@" + varGroup + "." + varName] = "unknown_variable";
        }
    }
}

void CSSContextInferencer::analyzeComputedValue(const std::string& property, const std::string& value) {
    // 分析计算值
    if (value.find("calc(") != std::string::npos) {
        currentContext.inferredTypes[property + "_computed"] = "calc_expression";
        
        // 验证calc表达式的有效性
        std::regex calcRegex(R"(calc\s*\([^)]+\))");
        if (std::regex_match(value, calcRegex)) {
            currentContext.inferredTypes[property + "_calc"] = "valid_calc";
        }
    }
    
    if (value.find("var(") != std::string::npos) {
        currentContext.inferredTypes[property + "_computed"] = "css_variable";
        
        // 提取CSS变量名
        std::regex varRegex(R"(var\s*\(\s*--([^)]+)\))");
        std::smatch match;
        if (std::regex_search(value, match, varRegex)) {
            std::string cssVarName = match[1];
            currentContext.inferredTypes["--" + cssVarName] = "css_custom_property";
        }
    }
}

void CSSContextInferencer::analyzeMediaQueries(const std::string& css) {
    // 分析媒体查询
    std::regex mediaRegex(R"(@media\s+([^{]+)\s*\{([^{}]*(?:\{[^}]*\}[^{}]*)*)\})");
    auto mediaBegin = std::sregex_iterator(css.begin(), css.end(), mediaRegex);
    auto mediaEnd = std::sregex_iterator();
    
    for (auto it = mediaBegin; it != mediaEnd; ++it) {
        std::string condition = (*it)[1];
        std::string content = (*it)[2];
        
        // 去除首尾空白
        condition.erase(0, condition.find_first_not_of(" \t\n\r"));
        condition.erase(condition.find_last_not_of(" \t\n\r") + 1);
        
        // 分析媒体查询条件
        analyzeMediaCondition(condition);
        
        // 标记进入媒体查询上下文
        bool wasInMediaQuery = currentContext.isInMediaQuery;
        std::string prevCondition = currentContext.mediaQueryCondition;
        
        currentContext.isInMediaQuery = true;
        currentContext.mediaQueryCondition = condition;
        
        // 递归分析媒体查询内的规则
        analyzeSelectors(content);
        analyzeDeclarations(content);
        
        // 恢复上下文
        currentContext.isInMediaQuery = wasInMediaQuery;
        currentContext.mediaQueryCondition = prevCondition;
    }
}

void CSSContextInferencer::analyzeMediaCondition(const std::string& condition) {
    // 分析媒体查询条件类型
    
    // 检查媒体类型
    if (condition.find("screen") != std::string::npos) {
        currentContext.inferredTypes["media_type"] = "screen";
    } else if (condition.find("print") != std::string::npos) {
        currentContext.inferredTypes["media_type"] = "print";
    } else if (condition.find("all") != std::string::npos) {
        currentContext.inferredTypes["media_type"] = "all";
    }
    
    // 检查方向
    if (condition.find("orientation") != std::string::npos) {
        if (condition.find("portrait") != std::string::npos) {
            currentContext.inferredTypes["orientation"] = "portrait";
        } else if (condition.find("landscape") != std::string::npos) {
            currentContext.inferredTypes["orientation"] = "landscape";
        }
    }
    
    // 分析断点
    analyzeBreakpoints(condition);
    
    // 检查特性查询
    if (condition.find("hover") != std::string::npos) {
        currentContext.inferredTypes["feature_hover"] = "checked";
    }
    if (condition.find("pointer") != std::string::npos) {
        currentContext.inferredTypes["feature_pointer"] = "checked";
    }
    
    // 检查逻辑操作符
    if (condition.find(" and ") != std::string::npos) {
        currentContext.inferredTypes["media_logic"] = "and";
    } else if (condition.find(" or ") != std::string::npos || 
               condition.find(",") != std::string::npos) {
        currentContext.inferredTypes["media_logic"] = "or";
    } else if (condition.find("not ") != std::string::npos) {
        currentContext.inferredTypes["media_logic"] = "not";
    }
}

void CSSContextInferencer::analyzeBreakpoints(const std::string& condition) {
    // 分析响应式断点
    
    // 提取宽度条件
    std::regex widthRegex(R"((min|max)-width\s*:\s*(\d+(?:\.\d+)?)(px|em|rem))");
    auto widthBegin = std::sregex_iterator(condition.begin(), condition.end(), widthRegex);
    auto widthEnd = std::sregex_iterator();
    
    for (auto it = widthBegin; it != widthEnd; ++it) {
        std::string type = (*it)[1];  // min or max
        std::string value = (*it)[2];
        std::string unit = (*it)[3];
        
        // 转换为像素值进行分类
        double pixels = std::stod(value);
        if (unit == "em") {
            pixels *= 16;  // 假设1em = 16px
        } else if (unit == "rem") {
            pixels *= 16;  // 假设1rem = 16px
        }
        
        // 分类断点
        std::string breakpointType;
        if (pixels < 576) {
            breakpointType = "xs";  // Extra small
        } else if (pixels < 768) {
            breakpointType = "sm";  // Small
        } else if (pixels < 992) {
            breakpointType = "md";  // Medium
        } else if (pixels < 1200) {
            breakpointType = "lg";  // Large
        } else if (pixels < 1400) {
            breakpointType = "xl";  // Extra large
        } else {
            breakpointType = "xxl"; // Extra extra large
        }
        
        currentContext.inferredTypes[type + "_width_breakpoint"] = breakpointType;
        currentContext.inferredTypes[type + "_width_value"] = value + unit;
    }
    
    // 提取高度条件
    std::regex heightRegex(R"((min|max)-height\s*:\s*(\d+(?:\.\d+)?)(px|em|rem|vh))");
    auto heightBegin = std::sregex_iterator(condition.begin(), condition.end(), heightRegex);
    auto heightEnd = std::sregex_iterator();
    
    for (auto it = heightBegin; it != heightEnd; ++it) {
        std::string type = (*it)[1];
        std::string value = (*it)[2];
        std::string unit = (*it)[3];
        
        currentContext.inferredTypes[type + "_height_value"] = value + unit;
    }
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