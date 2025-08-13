#include "CHTLCustom.h"
#include "CHTLGenerator.h"
#include <regex>
#include <algorithm>
#include <sstream>

namespace chtl {

// ElementSelector 实现
bool ElementSelector::matches(const std::string& name, int currentIndex) const {
    if (elementName != name) {
        return false;
    }
    
    // -1 表示匹配所有
    if (index == -1) {
        return true;
    }
    
    return index == currentIndex;
}

std::string ElementSelector::toString() const {
    if (index == -1) {
        return elementName;
    }
    return elementName + "[" + std::to_string(index) + "]";
}

ElementSelector ElementSelector::parse(const std::string& selector) {
    auto [name, idx] = CustomHelper::parseIndexedSelector(selector);
    return ElementSelector(name, idx);
}

// CustomStyleGroup 实现
void CustomStyleGroup::addValuelessProperty(const std::string& property) {
    valueRequiredProperties.push_back(property);
}

bool CustomStyleGroup::requiresValue(const std::string& property) const {
    return std::find(valueRequiredProperties.begin(), 
                    valueRequiredProperties.end(), 
                    property) != valueRequiredProperties.end();
}

void CustomStyleGroup::addDeleteOperation(const std::vector<std::string>& properties) {
    SpecializationOperation op;
    op.type = SpecializationType::DELETE;
    op.targets = properties;
    specializations.push_back(op);
}

void CustomStyleGroup::addDeleteInheritance(const std::string& inheritedName) {
    SpecializationOperation op;
    op.type = SpecializationType::DELETE;
    op.targets = {"@Style " + inheritedName};
    specializations.push_back(op);
}

void CustomStyleGroup::applySpecialization(const SpecializationOperation& op) {
    specializations.push_back(op);
}

std::vector<std::pair<std::string, std::string>> CustomStyleGroup::getEffectiveStyles(
    const std::unordered_map<std::string, std::shared_ptr<StyleTemplate>>& templateMap,
    const std::unordered_map<std::string, std::string>& providedValues) const {
    
    // 首先获取所有样式（包括继承的）
    auto allStyles = getAllStyles(templateMap);
    
    // 处理无值属性
    for (const auto& prop : valueRequiredProperties) {
        auto it = providedValues.find(prop);
        if (it != providedValues.end()) {
            // 使用提供的值
            bool found = false;
            for (auto& [p, v] : allStyles) {
                if (p == prop) {
                    v = it->second;
                    found = true;
                    break;
                }
            }
            if (!found) {
                allStyles.push_back({prop, it->second});
            }
        }
    }
    
    // 应用删除操作
    for (const auto& spec : specializations) {
        if (spec.type == SpecializationType::DELETE) {
            allStyles.erase(
                std::remove_if(allStyles.begin(), allStyles.end(),
                    [&spec](const auto& pair) {
                        return std::find(spec.targets.begin(), spec.targets.end(), pair.first) != spec.targets.end();
                    }),
                allStyles.end()
            );
        }
    }
    
    return allStyles;
}

// CustomElement 实现
void CustomElement::addElementSpecialization(const ElementSpecialization& spec) {
    specializations.push_back(spec);
}

void CustomElement::addInsertOperation(const InsertOperation& op) {
    insertOperations.push_back(op);
}

void CustomElement::addDeleteOperation(const DeleteOperation& op) {
    deleteOperations.push_back(op);
}

std::shared_ptr<ElementTemplate::ElementNode> CustomElement::getElementByIndex(
    const std::string& elementName, int index) const {
    
    auto allElements = getAllElements({});  // TODO: 需要传入模板映射
    int currentIndex = 0;
    
    for (const auto& elem : allElements) {
        if (elem->name == elementName) {
            if (currentIndex == index) {
                return elem;
            }
            currentIndex++;
        }
    }
    
    return nullptr;
}

std::vector<std::shared_ptr<ElementTemplate::ElementNode>> CustomElement::getElementsBySelector(
    const ElementSelector& selector) const {
    
    std::vector<std::shared_ptr<ElementNode>> result;
    auto allElements = getAllElements({});  // TODO: 需要传入模板映射
    int currentIndex = 0;
    std::unordered_map<std::string, int> indexMap;
    
    for (const auto& elem : allElements) {
        int elemIndex = indexMap[elem->name]++;
        if (selector.matches(elem->name, elemIndex)) {
            result.push_back(elem);
        }
    }
    
    return result;
}

void CustomElement::expandWithSpecialization(CHTLGenerator& generator,
    const std::vector<SpecializationOperation>& userSpecializations) const {
    
    // 获取所有元素
    auto elements = getAllElements({});  // TODO: 需要传入模板映射
    
    // 应用删除操作
    elements = applyDeletions(elements);
    
    // 应用插入操作
    elements = applyInsertions(elements);
    
    // 应用特例化
    for (const auto& spec : specializations) {
        // 找到匹配的元素并应用特例化
        auto matchedElements = getElementsBySelector(spec.selector);
        for (auto& elem : matchedElements) {
            if (spec.additionalStyles) {
                // 合并样式
                if (!elem->inlineStyles) {
                    elem->inlineStyles = spec.additionalStyles;
                } else {
                    // TODO: 合并样式
                }
            }
            
            // 合并属性
            for (const auto& [key, value] : spec.additionalAttributes) {
                elem->attributes[key] = value;
            }
            
            // 添加内容
            if (!spec.additionalContent.empty()) {
                elem->textContent += spec.additionalContent;
            }
        }
    }
    
    // 展开元素
    for (const auto& elem : elements) {
        generator.generateElement(elem->name, elem->attributes);
        
        if (elem->hasStyleBlock && elem->inlineStyles) {
            generator.beginStyleBlock();
            elem->inlineStyles->applyToElement(generator);
            generator.endStyleBlock();
        }
        
        if (!elem->textContent.empty()) {
            generator.beginTextBlock();
            generator.generateTextNode(elem->textContent);
            generator.endTextBlock();
        }
        
        generator.closeElement();
    }
}

std::vector<std::shared_ptr<ElementTemplate::ElementNode>> CustomElement::applyInsertions(
    const std::vector<std::shared_ptr<ElementNode>>& originalElements) const {
    
    std::vector<std::shared_ptr<ElementNode>> result = originalElements;
    
    // 按照插入操作的顺序处理
    for (const auto& insertOp : insertOperations) {
        std::vector<std::shared_ptr<ElementNode>> newResult;
        
        if (insertOp.position == InsertPosition::AT_TOP) {
            // 在顶部插入
            newResult.insert(newResult.end(), 
                           insertOp.elementsToInsert.begin(), 
                           insertOp.elementsToInsert.end());
            newResult.insert(newResult.end(), result.begin(), result.end());
        } else if (insertOp.position == InsertPosition::AT_BOTTOM) {
            // 在底部插入
            newResult = result;
            newResult.insert(newResult.end(), 
                           insertOp.elementsToInsert.begin(), 
                           insertOp.elementsToInsert.end());
        } else {
            // 基于选择器的插入
            int currentIndex = 0;
            std::unordered_map<std::string, int> indexMap;
            
            for (size_t i = 0; i < result.size(); ++i) {
                const auto& elem = result[i];
                int elemIndex = indexMap[elem->name]++;
                
                if (insertOp.position == InsertPosition::BEFORE &&
                    insertOp.targetSelector.matches(elem->name, elemIndex)) {
                    // 在匹配元素之前插入
                    newResult.insert(newResult.end(), 
                                   insertOp.elementsToInsert.begin(), 
                                   insertOp.elementsToInsert.end());
                }
                
                if (insertOp.position != InsertPosition::REPLACE ||
                    !insertOp.targetSelector.matches(elem->name, elemIndex)) {
                    // 保留原元素（除非是替换操作）
                    newResult.push_back(elem);
                }
                
                if (insertOp.position == InsertPosition::AFTER &&
                    insertOp.targetSelector.matches(elem->name, elemIndex)) {
                    // 在匹配元素之后插入
                    newResult.insert(newResult.end(), 
                                   insertOp.elementsToInsert.begin(), 
                                   insertOp.elementsToInsert.end());
                }
                
                if (insertOp.position == InsertPosition::REPLACE &&
                    insertOp.targetSelector.matches(elem->name, elemIndex)) {
                    // 替换操作：插入新元素
                    newResult.insert(newResult.end(), 
                                   insertOp.elementsToInsert.begin(), 
                                   insertOp.elementsToInsert.end());
                }
            }
        }
        
        result = newResult;
    }
    
    return result;
}

std::vector<std::shared_ptr<ElementTemplate::ElementNode>> CustomElement::applyDeletions(
    const std::vector<std::shared_ptr<ElementNode>>& originalElements) const {
    
    std::vector<std::shared_ptr<ElementNode>> result;
    std::unordered_map<std::string, int> indexMap;
    
    for (const auto& elem : originalElements) {
        int elemIndex = indexMap[elem->name]++;
        bool shouldDelete = false;
        
        // 检查是否应该删除
        for (const auto& deleteOp : deleteOperations) {
            if (!deleteOp.isInheritanceDeletion) {
                // 元素删除
                for (const auto& selector : deleteOp.selectors) {
                    if (selector.matches(elem->name, elemIndex)) {
                        shouldDelete = true;
                        break;
                    }
                }
            }
            
            if (shouldDelete) break;
        }
        
        if (!shouldDelete) {
            result.push_back(elem);
        }
    }
    
    return result;
}

// CustomVarGroup 实现
void CustomVarGroup::markAsOverridable(const std::string& varName) {
    overridableVariables.insert(varName);
}

bool CustomVarGroup::isOverridable(const std::string& varName) const {
    return overridableVariables.find(varName) != overridableVariables.end();
}

void CustomVarGroup::applySpecializationValue(const std::string& varName, const std::string& value) {
    if (isOverridable(varName)) {
        specializationValues[varName] = value;
    }
}

std::string CustomVarGroup::getVariableWithSpecialization(const std::string& varName,
    const std::optional<std::string>& runtimeValue) const {
    
    // 优先级：运行时值 > 特例化值 > 原始值
    if (runtimeValue.has_value() && isOverridable(varName)) {
        return runtimeValue.value();
    }
    
    auto specIt = specializationValues.find(varName);
    if (specIt != specializationValues.end()) {
        return specIt->second;
    }
    
    auto varOpt = getVariable(varName);
    return varOpt.value_or("");
}

// CustomManager 实现
bool CustomManager::registerCustomStyle(const std::string& name, std::shared_ptr<CustomStyleGroup> custom) {
    customStyles[name] = custom;
    
    // 注册全缀名别名
    QualifiedNameResolver resolver;
    resolver.parse(name);
    
    // TODO: 注册别名到管理器
    
    return true;
}

bool CustomManager::registerCustomElement(const std::string& name, std::shared_ptr<CustomElement> custom) {
    customElements[name] = custom;
    return true;
}

bool CustomManager::registerCustomVar(const std::string& name, std::shared_ptr<CustomVarGroup> custom) {
    customVars[name] = custom;
    return true;
}

std::shared_ptr<CustomStyleGroup> CustomManager::findCustomStyle(const std::string& name) const {
    auto it = customStyles.find(name);
    if (it != customStyles.end()) {
        return it->second;
    }
    
    // TODO: 处理全缀名查找
    
    return nullptr;
}

std::shared_ptr<CustomElement> CustomManager::findCustomElement(const std::string& name) const {
    auto it = customElements.find(name);
    if (it != customElements.end()) {
        return it->second;
    }
    
    // TODO: 处理全缀名查找
    
    return nullptr;
}

std::shared_ptr<CustomVarGroup> CustomManager::findCustomVar(const std::string& name) const {
    auto it = customVars.find(name);
    if (it != customVars.end()) {
        return it->second;
    }
    
    // TODO: 处理全缀名查找
    
    return nullptr;
}

bool CustomManager::useCustomStyle(const std::string& name, CHTLGenerator& generator,
    const std::unordered_map<std::string, std::string>& providedValues) {
    
    auto custom = findCustomStyle(name);
    if (!custom) {
        context->reportError("Custom style not found: " + name);
        return false;
    }
    
    // 获取有效样式（考虑特例化和提供的值）
    auto effectiveStyles = custom->getEffectiveStyles({}, providedValues);  // TODO: 传入模板映射
    
    // 应用样式
    for (const auto& [property, value] : effectiveStyles) {
        generator.generateInlineStyle(property, value);
    }
    
    return true;
}

bool CustomManager::useCustomElement(const std::string& name, CHTLGenerator& generator,
    const std::vector<SpecializationOperation>& specializations) {
    
    auto custom = findCustomElement(name);
    if (!custom) {
        context->reportError("Custom element not found: " + name);
        return false;
    }
    
    // 展开自定义元素（应用特例化）
    custom->expandWithSpecialization(generator, specializations);
    
    return true;
}

std::string CustomManager::useCustomVar(const std::string& templateName, const std::string& varName,
    const std::optional<std::string>& runtimeValue) {
    
    auto custom = findCustomVar(templateName);
    if (!custom) {
        context->reportError("Custom var group not found: " + templateName);
        return "";
    }
    
    return custom->getVariableWithSpecialization(varName, runtimeValue);
}

// SpecializationProcessor 实现
SpecializationOperation SpecializationProcessor::parseDeleteStatement(const std::string& statement) {
    SpecializationOperation op;
    op.type = SpecializationType::DELETE;
    
    // 解析 delete 语句
    // 格式: delete prop1, prop2, prop3;
    // 或: delete @Style StyleName;
    // 或: delete span;
    // 或: delete div[1];
    
    std::regex deleteRegex(R"(delete\s+(.+)\s*;?)");
    std::smatch match;
    
    if (std::regex_match(statement, match, deleteRegex)) {
        std::string targets = match[1];
        
        // 分割目标
        std::stringstream ss(targets);
        std::string target;
        while (std::getline(ss, target, ',')) {
            // 去除首尾空格
            target.erase(0, target.find_first_not_of(" \t"));
            target.erase(target.find_last_not_of(" \t") + 1);
            
            op.targets.push_back(target);
        }
    }
    
    return op;
}

InsertOperation SpecializationProcessor::parseInsertStatement(const std::string& statement) {
    InsertOperation op;
    
    // 解析格式: insert [position] [selector] { elements }
    std::regex insertRegex(R"(insert\s+(before|after|replace|at\s+top|at\s+bottom)\s+([^{]+)\s*\{([^}]*)\})");
    std::smatch match;
    
    if (std::regex_search(statement, match, insertRegex)) {
        std::string position = match[1];
        std::string selector = match[2];
        std::string content = match[3];
        
        // 解析位置
        if (position == "before") {
            op.position = InsertPosition::BEFORE;
        } else if (position == "after") {
            op.position = InsertPosition::AFTER;
        } else if (position == "replace") {
            op.position = InsertPosition::REPLACE;
        } else if (position == "at top") {
            op.position = InsertPosition::AT_TOP;
        } else if (position == "at bottom") {
            op.position = InsertPosition::AT_BOTTOM;
        }
        
        // 解析选择器
        op.targetSelector = parseElementSelector(selector);
        
        // 解析要插入的元素
        // 简化处理：将内容作为原始HTML
        auto element = std::make_shared<ElementNode>();
        element->name = "div";  // 默认使用div包装
        element->textContent = content;
        op.elementsToInsert.push_back(element);
    }
    
    return op;
}

ElementSelector SpecializationProcessor::parseElementSelector(const std::string& selector) {
    return ElementSelector::parse(selector);
}

std::pair<std::string, std::string> SpecializationProcessor::parseVariableSpecialization(const std::string& expr) {
    // 解析格式: ThemeColor(tableColor = rgb(145, 155, 200))
    std::regex varSpecRegex(R"((\w+)\((\w+)\s*=\s*(.+)\))");
    std::smatch match;
    
    if (std::regex_match(expr, match, varSpecRegex)) {
        std::string varName = match[2];
        std::string value = match[3];
        return {varName, value};
    }
    
    return {"", ""};
}

// CustomHelper 实现
namespace CustomHelper {

std::pair<std::string, int> parseIndexedSelector(const std::string& selector) {
    // 解析 "div[1]" -> ("div", 1)
    std::regex indexedRegex(R"((\w+)\[(\d+)\])");
    std::smatch match;
    
    if (std::regex_match(selector, match, indexedRegex)) {
        std::string name = match[1];
        int index = std::stoi(match[2]);
        return {name, index};
    }
    
    // 没有索引的情况
    return {selector, -1};
}

bool isValidInsertPosition(InsertPosition pos, const ElementSelector& target) {
    switch (pos) {
        case InsertPosition::BEFORE:
        case InsertPosition::AFTER:
        case InsertPosition::REPLACE:
            // 需要有效的目标选择器
            return !target.elementName.empty();
            
        case InsertPosition::AT_TOP:
        case InsertPosition::AT_BOTTOM:
            // 不需要目标选择器
            return target.elementName.empty();
    }
    
    return false;
}

std::vector<SpecializationOperation> mergeSpecializations(
    const std::vector<SpecializationOperation>& base,
    const std::vector<SpecializationOperation>& overrides) {
    
    // 简单合并策略：后面的覆盖前面的
    std::vector<SpecializationOperation> merged = base;
    merged.insert(merged.end(), overrides.begin(), overrides.end());
    
    // TODO: 实现更智能的合并策略
    
    return merged;
}

template<typename T>
std::vector<T> applyDeletionFilter(const std::vector<T>& items,
    const std::vector<std::string>& deletions) {
    
    std::vector<T> result;
    
    // TODO: 实现基于删除列表的过滤
    
    return result;
}

} // namespace CustomHelper

} // namespace chtl