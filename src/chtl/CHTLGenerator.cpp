#include "CHTLGenerator.h"
#include <algorithm>
#include <regex>

namespace chtl {

// CHTLGenerator 实现
CHTLGenerator::CHTLGenerator(std::shared_ptr<CHTLContext> ctx, const GeneratorOptions& opts) 
    : context(ctx), options(opts) {
    // 初始化管理器
    templateManager = std::make_shared<TemplateManager>(ctx);
    customManager = std::make_shared<CustomManager>(ctx);
    originManager = std::make_shared<OriginManager>(ctx);
    importManager = std::make_shared<ImportManager>(ctx);
    namespaceManager = std::make_shared<NamespaceManager>(ctx);
    constraintManager = std::make_shared<ConstraintManager>(ctx, namespaceManager);
    scriptManager = std::make_shared<ScriptManager>(ctx);
    cmodManager = std::make_shared<CMODManager>(ctx);
    cjmodManager = std::make_shared<CJMODManager>(ctx);
    cssProcessor = std::make_shared<CHTLCSSProcessor>(ctx);
    jsProcessor = std::make_shared<CHTLJSProcessor>(ctx);  // 初始化JS处理器
    
    // 设置交叉引用
    importManager->setTemplateManager(templateManager.get());
    importManager->setCustomManager(customManager.get());
    importManager->setOriginManager(originManager.get());
    importManager->setNamespaceManager(namespaceManager.get());
    importManager->setCMODManager(cmodManager);
    
    scriptManager->setCJMODManager(cjmodManager.get());
}

std::string CHTLGenerator::indent() const {
    std::string result;
    for (int i = 0; i < indentLevel; ++i) {
        result += options.indentString;
    }
    return result;
}

// 元素生成
void CHTLGenerator::generateElement(const std::string& tagName, 
                                   const std::map<std::string, std::string>& attributes) {
    // 检查约束
    if (constraintManager) {
        std::string error;
        if (!constraintManager->checkConstraint(ConstraintChecker::canUseHtmlElement, tagName, error)) {
            context->reportError(error);
            return;
        }
    }
    
    // 检查是否进入head元素
    if (tagName == "head") {
        inHeadElement = true;
    }
    
    // 更新元素栈
    elementStack.push_back(tagName);
    
    // 清空当前元素上下文
    currentElement = ElementContext();
    currentElement.tagName = tagName;
    currentElement.attributes = attributes;
    
    // 进入约束作用域
    if (constraintManager) {
        constraintManager->enterScope(ConstraintHelper::buildElementPath(elementStack));
    }
    
    // 生成开始标签
    htmlOutput << indent() << "<" << tagName;
    
    // 生成属性
    for (const auto& [key, value] : attributes) {
        htmlOutput << " " << key << "=\"" << escapeAttribute(value) << "\"";
    }
    
    // 如果有累积的内联样式，生成style属性
    if (!pendingInlineStyles.empty()) {
        std::stringstream styleValue;
        for (const auto& [prop, val] : pendingInlineStyles) {
            if (!styleValue.str().empty()) {
                styleValue << " ";
            }
            styleValue << prop << ": " << val << ";";
        }
        htmlOutput << " style=\"" << escapeAttribute(styleValue.str()) << "\"";
        
        // 清空累积的内联样式
        pendingInlineStyles.clear();
        isAccumulatingInlineStyles = false;
    }
    
    // 检查是否需要添加data-chtl-scope属性
    if (scriptManager) {
        std::string elementPath = ConstraintHelper::buildElementPath(elementStack);
        auto scripts = scriptManager->getScriptsForElement(elementPath);
        if (!scripts.empty()) {
            std::string scopeId = scriptManager->generateScopeId(elementPath);
            htmlOutput << " data-chtl-scope=\"" << scopeId << "\"";
        }
    }
    
    htmlOutput << ">" << std::endl;
    
    // 增加缩进
    indentLevel++;
}

void CHTLGenerator::closeElement() {
    if (elementStack.empty()) {
        context->reportError("No element to close");
        return;
    }
    
    // 获取当前元素名称
    std::string tagName = elementStack.back();
    
    // 检查是否离开head元素
    if (tagName == "head") {
        inHeadElement = false;
    }
    
    // 减少缩进
    if (indentLevel > 0) {
        indentLevel--;
    }
    
    // 生成结束标签
    htmlOutput << indent() << "</" << tagName << ">" << std::endl;
    
    // 退出约束作用域
    if (constraintManager) {
        constraintManager->exitScope();
    }
    
    // 更新元素栈
    elementStack.pop_back();
}

// 文本节点处理
void CHTLGenerator::generateTextNode(const std::string& content) {
    std::string processed = processLiteral(content, true);
    htmlOutput << "\n" << indent() << LiteralProcessor::escapeHTML(processed);
}

void CHTLGenerator::beginTextBlock() {
    // text块不生成额外的HTML标签
}

void CHTLGenerator::endTextBlock() {
    // text块结束
}

// 属性生成
void CHTLGenerator::generateAttribute(const std::string& name, const std::string& value) {
    std::string processedValue = formatAttributeValue(value);
    htmlOutput << " " << name << "=\"" << processedValue << "\"";
}

std::string CHTLGenerator::formatAttributeValue(const std::string& value) {
    // 处理CE对等式（:和=等价）
    std::string processed = processLiteral(value);
    
    // 转义属性值中的特殊字符
    std::string escaped;
    for (char c : processed) {
        switch (c) {
            case '"': escaped += "&quot;"; break;
            case '&': escaped += "&amp;"; break;
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            default: escaped += c;
        }
    }
    
    return escaped;
}

// 样式生成
void CHTLGenerator::beginStyleBlock() {
    // 局部样式块开始，不生成<style>标签
}

void CHTLGenerator::endStyleBlock() {
    // 处理收集的样式，提取到全局
    StyleExtractor extractor;
    extractor.extractNonInlineStyles(globalStyles);
    
    // 生成全局CSS
    for (const auto& rule : extractor.getExtractedRules()) {
        cssOutput << rule.selector << " {\n";
        for (const auto& [prop, value] : rule.properties) {
            cssOutput << "  " << prop << ": " << value << ";\n";
        }
        cssOutput << "}\n\n";
    }
}

void CHTLGenerator::beginInlineStyleBlock() {
    // 开始收集内联样式
    isAccumulatingInlineStyles = true;
}

void CHTLGenerator::endInlineStyleBlock() {
    // 内联样式块结束，但不清空累积的样式
    // 样式将在下一个元素生成时应用
}

void CHTLGenerator::generateInlineStyle(const std::string& property, const std::string& value) {
    // 内联样式直接添加到当前元素
    std::string processedValue = processLiteral(value);
    
    // 累积内联样式
    pendingInlineStyles.push_back({property, processedValue});
    isAccumulatingInlineStyles = true;
}

void CHTLGenerator::generateStyleRule(const std::string& selector, 
                                    const std::vector<std::pair<std::string, std::string>>& properties) {
    StyleRule rule;
    rule.selector = resolveContextSelector(selector);
    rule.properties = properties;
    rule.isInline = false;
    rule.sourceElement = currentElementName;
    
    // 检查是否应该提取到全局
    if (selector.find('.') == 0 || selector.find('#') == 0 || 
        selector.find('&') != std::string::npos) {
        rule.isInline = false;
        globalStyles.push_back(rule);
    } else {
        // 普通属性作为内联样式
        rule.isInline = true;
        // 将内联样式规则的属性添加到待处理列表
        for (const auto& prop : properties) {
            generateInlineStyle(prop.first, prop.second);
        }
    }
}

void CHTLGenerator::generateClassRule(const std::string& className, 
                                    const std::vector<std::pair<std::string, std::string>>& properties) {
    // 自动为当前元素添加类名
    autoAddClass(className);
    
    // 生成类规则
    std::string selector = "." + className;
    generateStyleRule(selector, properties);
}

void CHTLGenerator::generateIdRule(const std::string& idName, 
                                 const std::vector<std::pair<std::string, std::string>>& properties) {
    // 自动为当前元素添加ID
    autoAddId(idName);
    
    // 生成ID规则
    std::string selector = "#" + idName;
    generateStyleRule(selector, properties);
}

void CHTLGenerator::generatePseudoRule(const std::string& pseudo, 
                                     const std::vector<std::pair<std::string, std::string>>& properties) {
    // 处理伪类/伪元素
    std::string selector = resolveContextSelector("&" + pseudo);
    generateStyleRule(selector, properties);
}

// 注释处理
void CHTLGenerator::generateComment(const std::string& comment, bool isGeneratorComment) {
    if (isGeneratorComment) {
        processGeneratorComment(comment);
    } else {
        // 单行和多行注释不输出到HTML
    }
}

void CHTLGenerator::processSingleLineComment(const std::string& comment) {
    // // 注释不会被生成器识别，不输出
}

void CHTLGenerator::processMultiLineComment(const std::string& comment) {
    // /* */ 注释不会被生成器识别，不输出
}

void CHTLGenerator::processGeneratorComment(const std::string& comment) {
    // -- 注释会被生成器识别并输出为HTML注释
    if (options.preserveGeneratorComments) {
        pendingGeneratorComments.push_back(comment);
    }
}

// 自动化功能
void CHTLGenerator::autoAddClass(const std::string& className) {
    if (!currentElementName.empty()) {
        autoGeneratedClasses[currentElementName] = className;
    }
}

void CHTLGenerator::autoAddId(const std::string& idName) {
    if (!currentElementName.empty()) {
        autoGeneratedIds[currentElementName] = idName;
    }
}

std::string CHTLGenerator::getCurrentElementClass() const {
    auto it = autoGeneratedClasses.find(currentElementName);
    if (it != autoGeneratedClasses.end()) {
        return it->second;
    }
    return "";
}

std::string CHTLGenerator::getCurrentElementId() const {
    auto it = autoGeneratedIds.find(currentElementName);
    if (it != autoGeneratedIds.end()) {
        return it->second;
    }
    return "";
}

// 上下文推导
std::string CHTLGenerator::resolveContextSelector(const std::string& selector) {
    if (selector.find('&') != std::string::npos) {
        // 优先使用类名
        std::string context = getCurrentElementClass();
        if (!context.empty()) {
            context = "." + context;
        } else {
            context = getCurrentElementId();
            if (!context.empty()) {
                context = "#" + context;
            }
        }
        
        // 替换&符号
        std::string resolved = selector;
        size_t pos = 0;
        while ((pos = resolved.find('&', pos)) != std::string::npos) {
            resolved.replace(pos, 1, context);
            pos += context.length();
        }
        
        return resolved;
    }
    
    return selector;
}

// 字面量处理
std::string CHTLGenerator::processLiteral(const std::string& value, bool inTextBlock) {
    std::string processed = LiteralProcessor::removeQuotes(value);
    
    // 如果模板管理器存在，处理变量引用
    if (templateManager) {
        TemplateUseProcessor processor(*templateManager, *this);
        processed = processor.processVariableReference(processed);
    }
    
    // 如果自定义管理器存在，也尝试处理自定义变量
    if (customManager) {
        // 检查是否是自定义变量引用
        auto varRef = TemplateHelper::parseVarReference(processed);
        if (varRef.isValid) {
            std::string customValue = customManager->useCustomVar(varRef.templateName, varRef.varName);
            if (!customValue.empty()) {
                processed = customValue;
            }
        }
    }
    
    return processed;
}

// 模板定义支持
void CHTLGenerator::beginTemplateDefinition(const std::string& type, const std::string& name) {
    if (!templateManager) {
        context->reportError("Template manager not initialized");
        return;
    }
    
    // 设置为定义状态
    templateManager->setTemplateState(TemplateState::DEFINITION);
    
    // 根据类型创建相应的模板
    // 实际的模板创建会在解析过程中进行
}

void CHTLGenerator::endTemplateDefinition() {
    if (!templateManager) {
        return;
    }
    
    // 恢复为使用状态
    templateManager->setTemplateState(TemplateState::USE);
    
    // 处理继承关系
    templateManager->processInheritance();
}

// 模板使用
void CHTLGenerator::useTemplate(const std::string& statement) {
    if (!templateManager) {
        context->reportError("Template manager not initialized");
        return;
    }
    
    TemplateUseProcessor processor(*templateManager, *this);
    processor.processTemplateUse(statement);
}

std::string CHTLGenerator::processVariableReference(const std::string& reference) {
    if (!templateManager) {
        return reference;
    }
    
    TemplateUseProcessor processor(*templateManager, *this);
    return processor.processVariableReference(reference);
}

// 模板继承
void CHTLGenerator::addTemplateInheritance(const std::string& inheritStatement) {
    // 解析继承语句
    // 格式: inherit @Style TemplateName
    // 或: @Style TemplateName
    
    // 这个方法会在模板定义期间被调用
    // 实际的继承处理在具体的模板类中进行
}

// 自定义定义支持
void CHTLGenerator::beginCustomDefinition(const std::string& type, const std::string& name) {
    if (!customManager) {
        context->reportError("Custom manager not initialized");
        return;
    }
    
    // 自定义定义逻辑
    // 实际的自定义创建会在解析过程中进行
}

void CHTLGenerator::endCustomDefinition() {
    if (!customManager) {
        return;
    }
    
    // 自定义定义结束处理
}

// 自定义使用
void CHTLGenerator::useCustom(const std::string& statement, 
                             const std::unordered_map<std::string, std::string>& providedValues) {
    if (!customManager) {
        context->reportError("Custom manager not initialized");
        return;
    }
    
    // 解析语句类型
    if (statement.find("@Style") != std::string::npos) {
        customManager->useCustomStyle(statement, *this, providedValues);
    } else if (statement.find("@Element") != std::string::npos) {
        customManager->useCustomElement(statement, *this);
    }
}

void CHTLGenerator::useCustomWithSpecialization(const std::string& statement,
                                               const std::vector<SpecializationOperation>& specializations) {
    if (!customManager) {
        context->reportError("Custom manager not initialized");
        return;
    }
    
    // 使用带特例化的自定义元素
    if (statement.find("@Element") != std::string::npos) {
        customManager->useCustomElement(statement, *this, specializations);
    }
}

// 特例化支持
void CHTLGenerator::addSpecialization(const SpecializationOperation& op) {
    // 存储特例化操作，稍后应用
    // 这通常在自定义定义或使用时调用
}

void CHTLGenerator::addDeleteOperation(const std::string& deleteStatement) {
    auto op = SpecializationProcessor::parseDeleteStatement(deleteStatement);
    addSpecialization(op);
}

void CHTLGenerator::addInsertOperation(const std::string& insertStatement) {
    // 解析插入语句
    // 格式: insert after div[0] { ... }
    auto insertOp = SpecializationProcessor::parseInsertStatement(insertStatement);
    
    SpecializationOperation op;
    op.type = SpecializationType::INSERT;
    op.insertOp = insertOp;
    
    addSpecialization(op);
}

// 生成器辅助方法
std::string CHTLGenerator::generateAutoClassName(const std::string& hint) {
    std::string base = hint.empty() ? "auto" : hint;
    return base + "_" + std::to_string(++autoClassCounter);
}

std::string CHTLGenerator::generateAutoId(const std::string& hint) {
    std::string base = hint.empty() ? "id" : hint;
    return base + "_" + std::to_string(++autoIdCounter);
}

// 输出获取方法
std::string CHTLGenerator::getJS() const {
    // 合并来自scriptManager和jsProcessor的JavaScript
    std::string finalJS;
    
    // 首先获取CHTL JS处理器的输出（包含增强选择器等）
    if (scriptManager) {
        finalJS = scriptManager->generateJavaScript();
    }
    
    // 然后添加通过jsProcessor处理的标准JavaScript
    if (jsProcessor) {
        std::string processedJS = jsProcessor->generateFinalJS();
        if (!processedJS.empty()) {
            if (!finalJS.empty()) {
                finalJS += "\n\n";
            }
            finalJS += processedJS;
        }
    }
    
    // 最后添加任何直接输出到jsOutput的内容
    if (!jsOutput.str().empty()) {
        if (!finalJS.empty()) {
            finalJS += "\n\n";
        }
        finalJS += jsOutput.str();
    }
    
    return finalJS;
}

std::string CHTLGenerator::getCombinedOutput() const {
    std::stringstream combined;
    
    // HTML文档结构
    combined << "<!DOCTYPE html>\n";
    combined << "<html>\n";
    combined << "<head>\n";
    
    // 插入CSS
    if (!cssOutput.str().empty()) {
        combined << "<style>\n";
        combined << cssOutput.str();
        combined << "</style>\n";
    }
    
    combined << "</head>\n";
    combined << "<body>\n";
    combined << htmlOutput.str();
    combined << "\n</body>\n";
    
    // 插入JS
    if (!jsOutput.str().empty()) {
        combined << "<script>\n";
        combined << jsOutput.str();
        combined << "</script>\n";
    }
    
    combined << "</html>";
    
    return combined.str();
}

void CHTLGenerator::reset() {
    htmlOutput.str("");
    cssOutput.str("");
    jsOutput.str("");
    indentLevel = 0;
    currentElementName.clear();
    elementStack.clear();
    globalStyles.clear();
    autoGeneratedClasses.clear();
    autoGeneratedIds.clear();
    autoClassCounter = 0;
    autoIdCounter = 0;
    pendingGeneratorComments.clear();
}

// LiteralProcessor 实现
bool LiteralProcessor::isUnquotedLiteral(const std::string& value) {
    if (value.empty()) return false;
    
    // 检查是否有引号
    if (value.front() == '"' || value.front() == '\'') {
        return false;
    }
    
    // 无修饰字面量的规则：字母、数字、下划线、连字符等
    return true;
}

bool LiteralProcessor::hasQuotes(const std::string& value) {
    if (value.length() < 2) return false;
    
    return (value.front() == '"' && value.back() == '"') ||
           (value.front() == '\'' && value.back() == '\'');
}

std::string LiteralProcessor::removeQuotes(const std::string& value) {
    if (hasQuotes(value) && value.length() >= 2) {
        return value.substr(1, value.length() - 2);
    }
    return value;
}

std::string LiteralProcessor::escapeHTML(const std::string& value) {
    std::string escaped;
    for (char c : value) {
        switch (c) {
            case '&': escaped += "&amp;"; break;
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '"': escaped += "&quot;"; break;
            case '\'': escaped += "&#39;"; break;
            default: escaped += c;
        }
    }
    return escaped;
}

std::string LiteralProcessor::processCSSValue(const std::string& value) {
    // CSS值不需要引号的情况
    static const std::regex cssIdentifier("^[a-zA-Z_-][a-zA-Z0-9_-]*$");
    static const std::regex cssNumber("^-?[0-9]+(\\.[0-9]+)?(px|em|rem|%|vh|vw)?$");
    static const std::regex cssColor("^#[0-9a-fA-F]{3,8}$|^rgb\\(|^rgba\\(|^hsl\\(|^hsla\\(");
    
    std::string processed = removeQuotes(value);
    
    // 如果是标识符、数字或颜色，不需要引号
    if (std::regex_match(processed, cssIdentifier) ||
        std::regex_match(processed, cssNumber) ||
        std::regex_match(processed, cssColor)) {
        return processed;
    }
    
    // 否则需要引号
    return "\"" + processed + "\"";
}

// StyleExtractor 实现
void StyleExtractor::extractNonInlineStyles(const std::vector<StyleRule>& rules) {
    for (const auto& rule : rules) {
        if (!rule.isInline && shouldExtractToGlobal(rule.selector)) {
            extractedRules.push_back(rule);
            processedSelectors.insert(rule.selector);
        }
    }
}

bool StyleExtractor::shouldExtractToGlobal(const std::string& selector) const {
    // 类选择器、ID选择器、伪类、伪元素应该提取到全局
    return selector.find('.') == 0 || 
           selector.find('#') == 0 ||
           selector.find(':') != std::string::npos ||
           selector.find("::") != std::string::npos;
}

std::string StyleExtractor::generateGlobalStyleBlock() const {
    std::stringstream css;
    
    for (const auto& rule : extractedRules) {
        css << rule.selector << " {\n";
        for (const auto& [prop, value] : rule.properties) {
            css << "  " << prop << ": " << LiteralProcessor::processCSSValue(value) << ";\n";
        }
        css << "}\n\n";
    }
    
    return css.str();
}

// CommentProcessor 实现
CommentProcessor::CommentType CommentProcessor::detectCommentType(const std::string& text) {
    if (text.substr(0, 2) == "--") {
        return CommentType::GENERATOR;
    } else if (text.substr(0, 2) == "//") {
        return CommentType::SINGLE_LINE;
    } else if (text.substr(0, 2) == "/*") {
        return CommentType::MULTI_LINE;
    }
    
    return CommentType::SINGLE_LINE;
}

std::string CommentProcessor::extractCommentContent(const std::string& text, CommentType type) {
    switch (type) {
        case CommentType::SINGLE_LINE:
            return text.length() > 2 ? text.substr(2) : "";
            
        case CommentType::MULTI_LINE:
            if (text.length() > 4 && text.substr(text.length() - 2) == "*/") {
                return text.substr(2, text.length() - 4);
            }
            return text.length() > 2 ? text.substr(2) : "";
            
        case CommentType::GENERATOR:
            return text.length() > 2 ? text.substr(2) : "";
    }
    
    return "";
}

std::string CommentProcessor::formatAsHTMLComment(const std::string& content) {
    // 去除首尾空格
    std::string trimmed = content;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);
    
    return "<!-- " + trimmed + " -->";
}

// 原始内容生成
void CHTLGenerator::generateRawContent(const std::string& content) {
    // 原原本本输出内容，不做任何处理或转换
    htmlOutput << content;
}

// 原始嵌入处理
void CHTLGenerator::processOriginBlock(const std::string& declaration, const std::string& content) {
    if (!originManager) {
        context->reportError("Origin manager not initialized");
        return;
    }
    
    OriginProcessor processor(*originManager, *this);
    
    // 解析声明
    auto decl = processor.parseOriginDeclaration(declaration);
    
    // 创建原始嵌入实例
    auto origin = processor.createOriginInstance(decl);
    if (origin) {
        // 设置内容
        processor.processOriginContent(origin, content);
        
        if (decl.isNamed) {
            // 注册命名的原始嵌入
            originManager->registerNamedOrigin(decl.name, origin);
        } else {
            // 立即生成内容
            origin->generate(*this);
        }
    }
}

void CHTLGenerator::useOriginBlock(const std::string& name) {
    if (!originManager) {
        context->reportError("Origin manager not initialized");
        return;
    }
    
    originManager->useNamedOrigin(name, *this);
}

// 导入处理
void CHTLGenerator::processImportStatement(const std::string& statement) {
    if (!importManager) {
        context->reportError("Import manager not initialized");
        return;
    }
    
    ImportProcessor processor(*importManager, *this);
    ImportDeclaration decl = processor.parseImportStatement(statement);
    
    if (!importManager->processImport(decl, *this)) {
        context->reportError("Failed to process import: " + statement);
    }
}

void CHTLGenerator::processImports(const std::vector<std::string>& statements) {
    if (!importManager) {
        context->reportError("Import manager not initialized");
        return;
    }
    
    std::vector<ImportDeclaration> declarations;
    ImportProcessor processor(*importManager, *this);
    
    for (const auto& statement : statements) {
        declarations.push_back(processor.parseImportStatement(statement));
    }
    
    importManager->processImports(declarations, *this);
}

void CHTLGenerator::configureImportPaths(const ImportPathConfig& config) {
    if (!importManager) {
        context->reportError("Import manager not initialized");
        return;
    }
    
    importManager->configurePaths(config);
}

// 命名空间处理
void CHTLGenerator::beginNamespace(const std::string& name) {
    if (!namespaceManager) {
        context->reportError("Namespace manager not initialized");
        return;
    }
    
    namespaceManager->beginNamespace(name);
}

void CHTLGenerator::endNamespace() {
    if (!namespaceManager) {
        context->reportError("Namespace manager not initialized");
        return;
    }
    
    namespaceManager->endNamespace();
}

void CHTLGenerator::processNamespaceDeclaration(const std::string& declaration) {
    if (!namespaceManager) {
        context->reportError("Namespace manager not initialized");
        return;
    }
    
    NamespaceProcessor processor(*namespaceManager, *this);
    processor.processNamespaceDeclaration(declaration);
}

void CHTLGenerator::useTemplateFromNamespace(const std::string& templateName, const std::string& namespacePath) {
    if (!namespaceManager || !templateManager) {
        context->reportError("Namespace or template manager not initialized");
        return;
    }
    
    NamespaceResolver resolver(*namespaceManager);
    
    // 查找样式模板
    auto styleTemplate = std::static_pointer_cast<StyleTemplate>(
        resolver.resolveItem(templateName, NamespaceItemType::TEMPLATE_STYLE, namespacePath)
    );
    if (styleTemplate) {
        templateManager->useTemplate("@Style " + templateName, *this);
        return;
    }
    
    // 查找元素模板
    auto elementTemplate = std::static_pointer_cast<ElementTemplate>(
        resolver.resolveItem(templateName, NamespaceItemType::TEMPLATE_ELEMENT, namespacePath)
    );
    if (elementTemplate) {
        templateManager->useTemplate("@Element " + templateName, *this);
        return;
    }
    
    // 查找变量组模板
    auto varTemplate = std::static_pointer_cast<VarTemplate>(
        resolver.resolveItem(templateName, NamespaceItemType::TEMPLATE_VAR, namespacePath)
    );
    if (varTemplate) {
        templateManager->useTemplate("@Var " + templateName, *this);
        return;
    }
    
    context->reportError("Template not found in namespace: " + templateName + " from " + namespacePath);
}

void CHTLGenerator::useCustomFromNamespace(const std::string& customName, const std::string& namespacePath) {
    if (!namespaceManager || !customManager) {
        context->reportError("Namespace or custom manager not initialized");
        return;
    }
    
    NamespaceResolver resolver(*namespaceManager);
    
    // 查找自定义样式组
    auto customStyle = std::static_pointer_cast<CustomStyleGroup>(
        resolver.resolveItem(customName, NamespaceItemType::CUSTOM_STYLE, namespacePath)
    );
    if (customStyle) {
        customManager->useCustom("@Style " + customName, *this);
        return;
    }
    
    // 查找自定义元素
    auto customElement = std::static_pointer_cast<CustomElement>(
        resolver.resolveItem(customName, NamespaceItemType::CUSTOM_ELEMENT, namespacePath)
    );
    if (customElement) {
        customManager->useCustom("@Element " + customName, *this);
        return;
    }
    
    // 查找自定义变量组
    auto customVar = std::static_pointer_cast<CustomVarGroup>(
        resolver.resolveItem(customName, NamespaceItemType::CUSTOM_VAR, namespacePath)
    );
    if (customVar) {
        customManager->useCustomVar(customName, "", *this);
        return;
    }
    
    context->reportError("Custom not found in namespace: " + customName + " from " + namespacePath);
}

// 约束处理
void CHTLGenerator::processExceptStatement(const std::string& statement) {
    if (!constraintManager) {
        context->reportError("Constraint manager not initialized");
        return;
    }
    
    std::string currentScope;
    if (namespaceManager && namespaceManager->getCurrentNamespace()) {
        currentScope = namespaceManager->getCurrentNamespace()->getFullPath();
    } else if (!elementStack.empty()) {
        currentScope = ConstraintHelper::buildElementPath(elementStack);
    }
    
    ConstraintProcessor processor(*constraintManager, *this);
    processor.processExceptStatement(statement, currentScope);
}

void CHTLGenerator::addElementConstraint(const std::string& elementPath, const std::string& exceptClause) {
    if (!constraintManager) {
        context->reportError("Constraint manager not initialized");
        return;
    }
    
    ConstraintProcessor processor(*constraintManager, *this);
    auto decl = processor.parseExceptDeclaration(exceptClause);
    
    if (decl.isValid) {
        auto rule = std::make_shared<ConstraintRule>(decl.type, elementPath);
        for (const auto& target : decl.targets) {
            rule->addTarget(target);
        }
        constraintManager->addElementConstraint(elementPath, rule);
    }
}

void CHTLGenerator::addNamespaceConstraint(const std::string& namespacePath, const std::string& exceptClause) {
    if (!constraintManager) {
        context->reportError("Constraint manager not initialized");
        return;
    }
    
    ConstraintProcessor processor(*constraintManager, *this);
    auto decl = processor.parseExceptDeclaration(exceptClause);
    
    if (decl.isValid) {
        auto rule = std::make_shared<ConstraintRule>(ConstraintType::GLOBAL, namespacePath, true);
        for (const auto& target : decl.targets) {
            rule->addTarget(target);
        }
        constraintManager->addNamespaceConstraint(namespacePath, rule);
    }
}

bool CHTLGenerator::checkConstraint(const std::string& usage) {
    if (!constraintManager) {
        return true; // 没有约束管理器，允许所有使用
    }
    
    std::string currentScope = ConstraintHelper::buildElementPath(elementStack);
    ConstraintProcessor processor(*constraintManager, *this);
    return processor.validateUsage(usage, currentScope);
}

// 脚本处理
void CHTLGenerator::beginScriptBlock() {
    if (!scriptManager) {
        context->reportError("Script manager not initialized");
        return;
    }
    
    // 标记正在处理脚本块
    currentScriptContent.clear();
}

void CHTLGenerator::endScriptBlock() {
    if (!scriptManager) {
        context->reportError("Script manager not initialized");
        return;
    }
    
    // 处理脚本内容
    if (!currentScriptContent.empty()) {
        processLocalScript(currentScriptContent);
        currentScriptContent.clear();
    }
}

void CHTLGenerator::addScriptContent(const std::string& content) {
    currentScriptContent += content;
}

void CHTLGenerator::processLocalScript(const std::string& script) {
    if (!scriptManager) {
        context->reportError("Script manager not initialized");
        return;
    }
    
    // 获取当前元素路径
    std::string currentScope = ConstraintHelper::buildElementPath(elementStack);
    
    // 创建脚本处理器
    ScriptProcessor processor(*scriptManager, *this);
    processor.processScriptBlock(script, currentScope);
}

void CHTLGenerator::processGlobalStyleBlock(const std::string& cssContent) {
    if (!cssProcessor) {
        context->reportError("CSS processor not initialized");
        return;
    }
    
    // 设置管理器以支持样式组和变量组
    cssProcessor->setTemplateManager(templateManager);
    cssProcessor->setCustomManager(customManager);
    
    // 添加到CSS处理器
    cssProcessor->addGlobalStyleBlock(cssContent);
    
    // 如果在head元素中，生成style标签
    if (inHeadElement) {
        htmlOutput << "<style>\n";
        // CSS内容将在最后统一处理和优化
        htmlOutput << "/* Global CSS will be inserted here */\n";
        htmlOutput << "</style>\n";
    }
}

std::string CHTLGenerator::getCSS() const {
    if (!cssProcessor) {
        return cssOutput.str();
    }
    
    // 获取优化后的最终CSS
    std::string finalCSS = cssProcessor->generateFinalCSS();
    
    // 如果有额外的CSS输出，合并它们
    if (!cssOutput.str().empty()) {
        return finalCSS + "\n" + cssOutput.str();
    }
    
    return finalCSS;
}

void CHTLGenerator::processGlobalScriptBlock(const std::string& jsContent, const std::string& type) {
    if (!jsProcessor) {
        context->reportError("JavaScript processor not initialized");
        return;
    }
    
    // 添加到JS处理器
    jsProcessor->addGlobalScript(jsContent, type);
    
    // 如果在head元素中，生成script标签
    if (inHeadElement) {
        htmlOutput << "<script type=\"" << type << "\">\n";
        // JS内容将在最后统一处理和优化
        htmlOutput << "/* Global JavaScript will be inserted here */\n";
        htmlOutput << "</script>\n";
    }
}

} // namespace chtl