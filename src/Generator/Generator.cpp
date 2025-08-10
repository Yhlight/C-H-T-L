#include "Generator/Generator.h"
#include "Runtime/ChtlJsRuntime.h"
#include "Generator/ConfigManager.h"
#include "Node/Element.h"
#include "Node/Text.h"
#include "Node/Custom.h"
#include "Node/Template.h"
#include "Node/Style.h"
#include "Node/Script.h"
#include "Node/Import.h"
#include "Node/Export.h"
#include "Node/Config.h"
#include "Node/Namespace.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <set>

namespace chtl {

// CodeCollector 实现
void Generator::CodeCollector::append(const std::string& code) {
    stream_ << code;
}

void Generator::CodeCollector::appendLine(const std::string& code) {
    if (!code.empty()) {
        for (int i = 0; i < indentLevel_; ++i) {
            stream_ << "  ";
        }
        stream_ << code;
    }
    stream_ << "\n";
}

// Generator 实现
Generator::Generator(const GeneratorOptions& options) 
    : options_(options), 
      configManager_(std::make_unique<ConfigManager>()),
      jsRuntime_(&ChtlJsRuntime::getInstance()) {
}

GeneratorResult Generator::generate(const std::shared_ptr<Node>& ast) {
    if (!ast) {
        result_.success = false;
        result_.errors.push_back("AST is null");
        return result_;
    }
    
    // 清空之前的结果
    result_ = GeneratorResult();
    htmlCollector_.clear();
    cssCollector_.clear();
    jsCollector_.clear();
    componentMap_.clear();
    styleMap_.clear();
    scopeStack_.clear();
    templateDefinitions_.clear();
    customDefinitions_.clear();
    jsRuntime_->reset();
    
    ast_ = ast;
    
    // 第一遍扫描：收集配置和定义
    scanConfiguration(ast);
    collectDefinitions(ast);
    
    // 第二遍处理：生成代码
    visit(ast);
    
    // 收集结果
    result_.html = htmlCollector_.getCode();
    result_.css = cssCollector_.getCode();
    result_.js = jsCollector_.getCode();
    
    result_.success = true;
    return result_;
}

void Generator::scanConfiguration(const std::shared_ptr<Node>& node) {
    if (!node) return;
    
    // 查找[Configuration]节点
    if (node->getType() == NodeType::CONFIG) {
        auto config = std::static_pointer_cast<Config>(node);
        configManager_->loadFromConfig(config);
        
        // 如果启用调试模式，输出配置信息
        if (configManager_->isDebugMode()) {
            result_.warnings.push_back("Debug mode enabled");
        }
    }
    
    // 递归扫描子节点
    for (const auto& child : node->getChildren()) {
        scanConfiguration(child);
    }
}

void Generator::collectDefinitions(const std::shared_ptr<Node>& node) {
    if (!node) return;
    
    // 收集Template定义
    if (auto tmpl = std::dynamic_pointer_cast<Template>(node)) {
        std::string key;
        switch (tmpl->getTemplateType()) {
            case Template::TemplateType::STYLE:
                key = "@Style " + tmpl->getTemplateName();
                break;
            case Template::TemplateType::ELEMENT:
                key = "@Element " + tmpl->getTemplateName();
                break;
            case Template::TemplateType::VAR:
                key = "@Var " + tmpl->getTemplateName();
                break;
        }
        templateDefinitions_[key] = tmpl;
    }
    
    // 收集Custom定义
    if (auto custom = std::dynamic_pointer_cast<Custom>(node)) {
        std::string key;
        switch (custom->getCustomType()) {
            case Custom::CustomType::STYLE:
                key = "@Style " + custom->getCustomName();
                break;
            case Custom::CustomType::ELEMENT:
                key = "@Element " + custom->getCustomName();
                break;
            case Custom::CustomType::VAR:
                key = "@Var " + custom->getCustomName();
                break;
        }
        customDefinitions_[key] = custom;
    }
    
    // 递归收集子节点
    for (const auto& child : node->getChildren()) {
        collectDefinitions(child);
    }
}

void Generator::visit(const std::shared_ptr<Node>& node) {
    if (!node) return;
    
    switch (node->getType()) {
        case NodeType::ELEMENT:
            visitElement(std::static_pointer_cast<Element>(node));
            break;
        case NodeType::TEXT:
            visitText(std::static_pointer_cast<Text>(node));
            break;
        case NodeType::CUSTOM:
            visitCustom(std::static_pointer_cast<Custom>(node));
            break;
        case NodeType::TEMPLATE:
            visitTemplate(std::static_pointer_cast<Template>(node));
            break;
        case NodeType::STYLE:
            visitStyle(std::static_pointer_cast<Style>(node));
            break;
        case NodeType::SCRIPT:
            visitScript(std::static_pointer_cast<Script>(node));
            break;
        case NodeType::IMPORT:
            visitImport(std::static_pointer_cast<Import>(node));
            break;
        case NodeType::EXPORT:
            visitExport(std::static_pointer_cast<Export>(node));
            break;
        case NodeType::CONFIG:
            visitConfig(std::static_pointer_cast<Config>(node));
            break;
        case NodeType::NAMESPACE:
            visitNamespace(std::static_pointer_cast<Namespace>(node));
            break;
        default:
            // 处理其他节点类型
            for (const auto& child : node->getChildren()) {
                visit(child);
            }
            break;
    }
}

void Generator::visitElement(const std::shared_ptr<Element>& element) {
    // 基础实现，子类会覆盖
    htmlCollector_.append("<" + element->getTagName());
    
    // 属性
    for (const auto& [key, value] : element->getAttributes()) {
        if (std::holds_alternative<std::string>(value)) {
            htmlCollector_.append(" " + key + "=\"" + escape(std::get<std::string>(value)) + "\"");
        } else {
            // Convert other types to string
            std::string valueStr;
            if (std::holds_alternative<int>(value)) {
                valueStr = std::to_string(std::get<int>(value));
            } else if (std::holds_alternative<double>(value)) {
                valueStr = std::to_string(std::get<double>(value));
            } else if (std::holds_alternative<bool>(value)) {
                valueStr = std::get<bool>(value) ? "true" : "false";
            }
            htmlCollector_.append(" " + key + "=\"" + valueStr + "\"");
        }
    }
    
    htmlCollector_.append(">");
    
    // 子节点
    for (const auto& child : element->getChildren()) {
        visit(child);
    }
    
    htmlCollector_.append("</" + element->getTagName() + ">");
}

void Generator::visitText(const std::shared_ptr<Text>& text) {
    htmlCollector_.append(escape(text->getData()));
}

void Generator::visitCustom(const std::shared_ptr<Custom>& custom) {
    // 处理继承
    resolveInheritance(custom);
    
    // 基础实现，子类会覆盖
    result_.warnings.push_back("Custom component not implemented: " + custom->getCustomName());
}

void Generator::visitTemplate(const std::shared_ptr<Template>& tmpl) {
    // 处理继承
    resolveInheritance(tmpl);
    
    // 模板定义，存储供后续使用
    componentMap_[tmpl->getTemplateName()] = tmpl->toString();
}

void Generator::visitStyle(const std::shared_ptr<Style>& style) {
    std::string css = style->getCssContent();
    
    // 添加作用域
    if (options_.scopeStyles && !currentScope_.empty()) {
        css = scopeSelector(css, currentScope_);
    }
    
    cssCollector_.appendLine(css);
}

void Generator::visitScript(const std::shared_ptr<Script>& script) {
    if (script->getScriptType() == Script::ScriptType::INLINE && script->isScoped()) {
        // 局部脚本由运行时处理
        std::string elementId = script->getScope();
        if (elementId.empty()) {
            elementId = generateUniqueId("element");
        }
        jsRuntime_->collectLocalScript(script->getContent(), elementId);
    } else {
        // 全局脚本
        jsCollector_.appendLine(script->generateWrappedCode());
    }
}

void Generator::visitImport(const std::shared_ptr<Import>& import) {
    // 处理导入，可能需要加载外部模块
    result_.warnings.push_back("Import handling not fully implemented: " + import->getPath());
}

void Generator::visitExport(const std::shared_ptr<Export>& exp) {
    // 处理导出
    for (const auto& item : exp->getExportItems()) {
        // 记录导出项
        (void)item; // TODO: Implement export handling
    }
}

void Generator::visitConfig(const std::shared_ptr<Config>& config) {
    // 处理配置
    for (const auto& [key, value] : config->getConfigItems()) {
        if (key == "title") {
            // 设置页面标题等
        }
    }
}

void Generator::visitNamespace(const std::shared_ptr<Namespace>& ns) {
    // 处理命名空间
    std::string oldScope = currentScope_;
    currentScope_ = ns->getName();
    scopeStack_.push_back(currentScope_);
    
    for (const auto& child : ns->getChildren()) {
        visit(child);
    }
    
    scopeStack_.pop_back();
    currentScope_ = oldScope;
}

// 工具方法
std::string Generator::indent(int level) const {
    return std::string(level * 2, ' ');
}

std::string Generator::escape(const std::string& str) const {
    std::string result;
    for (char c : str) {
        switch (c) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += c; break;
        }
    }
    return result;
}

std::string Generator::generateUniqueId(const std::string& prefix) const {
    return prefix + "-" + std::to_string(++uniqueIdCounter_);
}

std::string Generator::scopeSelector(const std::string& css, const std::string& scope) const {
    // 简单的作用域实现，为每个选择器添加作用域类
    std::regex selectorRegex(R"(([^{]+)\{)");
    std::string scopedCss = css;
    
    // Replace selectors with scoped versions
    std::string result;
    std::smatch match;
    auto searchStart = scopedCss.cbegin();
    
    while (std::regex_search(searchStart, scopedCss.cend(), match, selectorRegex)) {
        result.append(searchStart, match[0].first);
        
        std::string selector = match[1].str();
        // 去除前后空白
        selector.erase(0, selector.find_first_not_of(" \t\n\r"));
        selector.erase(selector.find_last_not_of(" \t\n\r") + 1);
        
        // 添加作用域
        if (selector.find("@") == 0 || selector.find(":root") == 0) {
            // 不处理@规则和:root
            result.append(match[0].str());
        } else {
            result.append("." + scope + " " + selector + "{");
        }
        
        searchStart = match[0].second;
    }
    result.append(searchStart, scopedCss.cend());
    scopedCss = result;
    
    return scopedCss;
}

// 工厂函数
std::unique_ptr<Generator> createGenerator(const std::string& platform, 
                                          const GeneratorOptions& options) {
    if (platform == "web") {
        return std::make_unique<WebGenerator>(options);
    } else if (platform == "react") {
        return std::make_unique<ReactGenerator>(options);
    } else if (platform == "vue") {
        return std::make_unique<VueGenerator>(options);
    } else {
        return std::make_unique<WebGenerator>(options); // 默认使用Web生成器
    }
}

// 添加继承解析方法
void Generator::resolveInheritance(std::shared_ptr<Node> node) {
    const auto& inheritances = node->getInheritances();
    
    for (const auto& inheritance : inheritances) {
        // 解析继承字符串，格式如 "@Style ThemeName" 或 "[Template] @Style ThemeName"
        std::istringstream iss(inheritance);
        std::string type1, type2, name;
        
        iss >> type1;
        if (type1 == "[Template]" || type1 == "[Custom]") {
            iss >> type2 >> name;
        } else {
            type2 = type1;
            iss >> name;
        }
        
        // 根据类型查找并合并
        if (type2 == "@Style") {
            mergeStyleInheritance(node, name);
        } else if (type2 == "@Element") {
            mergeElementInheritance(node, name);
        } else if (type2 == "@Var") {
            mergeVarInheritance(node, name);
        }
    }
}

void Generator::mergeStyleInheritance(std::shared_ptr<Node> target, const std::string& sourceName) {
    // 查找源样式定义
    auto source = findStyleDefinition(sourceName);
    if (!source) {
        result_.warnings.push_back("Style inheritance source not found: " + sourceName);
        return;
    }
    
    // 合并样式属性
    if (auto targetTemplate = std::dynamic_pointer_cast<Template>(target)) {
        if (auto sourceTemplate = std::dynamic_pointer_cast<Template>(source)) {
            // 合并参数
            for (const auto& [key, value] : sourceTemplate->getParameters()) {
                // 只添加目标中不存在的参数
                if (targetTemplate->getParameters().find(key) == targetTemplate->getParameters().end()) {
                    targetTemplate->setParameter(key, value);
                }
            }
        }
    } else if (auto targetCustom = std::dynamic_pointer_cast<Custom>(target)) {
        if (auto sourceCustom = std::dynamic_pointer_cast<Custom>(source)) {
            // 合并属性
            for (const auto& [key, value] : sourceCustom->getProperties()) {
                if (targetCustom->getProperties().find(key) == targetCustom->getProperties().end()) {
                    targetCustom->setProperty(key, value);
                }
            }
        }
    }
    
    // 合并子节点（样式规则）
    for (const auto& child : source->getChildren()) {
        if (child->getType() != NodeType::DELETE) {  // 跳过删除节点
            target->addChild(child->clone());
        }
    }
}

void Generator::mergeElementInheritance(std::shared_ptr<Node> target, const std::string& sourceName) {
    auto source = findElementDefinition(sourceName);
    if (!source) {
        result_.warnings.push_back("Element inheritance source not found: " + sourceName);
        return;
    }
    
    // 合并元素结构 - 只添加不在删除列表中的子节点
    std::set<std::string> deletedElements;
    collectDeletedItems(target, deletedElements);
    
    for (const auto& child : source->getChildren()) {
        if (child->getType() == NodeType::ELEMENT) {
            auto element = std::static_pointer_cast<Element>(child);
            if (deletedElements.find(element->getTagName()) == deletedElements.end()) {
                target->addChild(child->clone());
            }
        }
    }
}

void Generator::mergeVarInheritance(std::shared_ptr<Node> target, const std::string& sourceName) {
    auto source = findVarDefinition(sourceName);
    if (!source) {
        result_.warnings.push_back("Var inheritance source not found: " + sourceName);
        return;
    }
    
    // 合并变量定义
    if (auto targetTemplate = std::dynamic_pointer_cast<Template>(target)) {
        if (auto sourceTemplate = std::dynamic_pointer_cast<Template>(source)) {
            for (const auto& [key, value] : sourceTemplate->getParameters()) {
                if (targetTemplate->getParameters().find(key) == targetTemplate->getParameters().end()) {
                    targetTemplate->setParameter(key, value);
                }
            }
        }
    } else if (auto targetCustom = std::dynamic_pointer_cast<Custom>(target)) {
        if (auto sourceCustom = std::dynamic_pointer_cast<Custom>(source)) {
            for (const auto& [key, value] : sourceCustom->getProperties()) {
                if (targetCustom->getProperties().find(key) == targetCustom->getProperties().end()) {
                    targetCustom->setProperty(key, value);
                }
            }
        }
    }
}

std::shared_ptr<Node> Generator::findStyleDefinition(const std::string& name) {
    // 搜索已解析的样式定义
    for (const auto& [key, node] : templateDefinitions_) {
        if (key == "@Style " + name) {
            return node;
        }
    }
    for (const auto& [key, node] : customDefinitions_) {
        if (key == "@Style " + name) {
            return node;
        }
    }
    return nullptr;
}

std::shared_ptr<Node> Generator::findElementDefinition(const std::string& name) {
    for (const auto& [key, node] : templateDefinitions_) {
        if (key == "@Element " + name) {
            return node;
        }
    }
    for (const auto& [key, node] : customDefinitions_) {
        if (key == "@Element " + name) {
            return node;
        }
    }
    return nullptr;
}

std::shared_ptr<Node> Generator::findVarDefinition(const std::string& name) {
    for (const auto& [key, node] : templateDefinitions_) {
        if (key == "@Var " + name) {
            return node;
        }
    }
    for (const auto& [key, node] : customDefinitions_) {
        if (key == "@Var " + name) {
            return node;
        }
    }
    return nullptr;
}

void Generator::collectDeletedItems(std::shared_ptr<Node> node, std::set<std::string>& deletedItems) {
    (void)deletedItems; // TODO: Implement delete collection
    for (const auto& child : node->getChildren()) {
        if (child->getType() == NodeType::DELETE) {
            // 提取删除目标
            // TODO: Implement proper delete target extraction
            // For now, just skip
        }
    }
}

} // namespace chtl