#include "Generator/Generator.h"
#include <sstream>

namespace chtl {

GeneratorResult ReactGenerator::generate(const std::shared_ptr<Node>& ast) {
    // 调用基类的生成方法先处理 AST
    auto result = Generator::generate(ast);
    
    // 对于 React，我们需要将 HTML 转换为 JSX
    // 这里暂时返回基类的结果
    return result;
}

void ReactGenerator::visitElement(const std::shared_ptr<Element>& element) {
    // React 特定的元素处理
    // 例如：class -> className, for -> htmlFor
    auto className = element->getAttribute("class");
    if (std::holds_alternative<std::string>(className)) {
        element->setAttribute("className", std::get<std::string>(className));
        element->removeAttribute("class");
    }
    
    // 调用基类的处理
    Generator::visitElement(element);
}

void ReactGenerator::visitCustom(const std::shared_ptr<Custom>& custom) {
    // React 组件的特殊处理
    if (custom->getCustomType() == Custom::CustomType::ELEMENT) {
        generateReactComponent(custom->getCustomName());
    }
    
    // 调用基类的处理
    Generator::visitCustom(custom);
}

void ReactGenerator::generateReactComponent(const std::string& name) {
    // 生成 React 组件代码
    std::stringstream ss;
    ss << "const " << name << " = (props) => {\n";
    ss << "  return (\n";
    ss << "    <div>\n";
    ss << "      {/* Component content */}\n";
    ss << "    </div>\n";
    ss << "  );\n";
    ss << "};\n\n";
    
    result_.js += ss.str();
}

std::string ReactGenerator::convertToJSX(const std::shared_ptr<Node>& node) {
    // 将节点转换为 JSX
    std::stringstream ss;
    
    if (auto element = std::dynamic_pointer_cast<Element>(node)) {
        ss << "<" << element->getTagName();
        
        // 添加属性
        for (const auto& [key, value] : element->getAttributes()) {
            if (std::holds_alternative<std::string>(value)) {
                ss << " " << key << "=\"" << std::get<std::string>(value) << "\"";
            }
        }
        
        ss << ">";
        
        // 处理子节点
        for (const auto& child : element->getChildren()) {
            ss << convertToJSX(child);
        }
        
        ss << "</" << element->getTagName() << ">";
    }
    
    return ss.str();
}

std::string ReactGenerator::camelCase(const std::string& str) const {
    std::string result;
    bool capitalizeNext = false;
    
    for (char c : str) {
        if (c == '-' || c == '_') {
            capitalizeNext = true;
        } else if (capitalizeNext) {
            result += std::toupper(c);
            capitalizeNext = false;
        } else {
            result += c;
        }
    }
    
    return result;
}

} // namespace chtl