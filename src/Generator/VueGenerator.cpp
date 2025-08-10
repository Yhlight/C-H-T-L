#include "Generator/Generator.h"
#include <sstream>

namespace chtl {

GeneratorResult VueGenerator::generate(const std::shared_ptr<Node>& ast) {
    // 调用基类的生成方法先处理 AST
    auto result = Generator::generate(ast);
    
    // 对于 Vue，我们需要生成 Vue 单文件组件格式
    // 这里暂时返回基类的结果
    return result;
}

void VueGenerator::visitElement(const std::shared_ptr<Element>& element) {
    // Vue 特定的元素处理
    // 例如：v-for, v-if, v-model 等指令
    
    // 调用基类的处理
    Generator::visitElement(element);
}

void VueGenerator::visitCustom(const std::shared_ptr<Custom>& custom) {
    // Vue 组件的特殊处理
    if (custom->getCustomType() == Custom::CustomType::ELEMENT) {
        generateVueComponent(custom->getCustomName());
    }
    
    // 调用基类的处理
    Generator::visitCustom(custom);
}

void VueGenerator::generateVueComponent(const std::string& name) {
    // 生成 Vue 组件代码
    std::stringstream ss;
    ss << "<!-- " << name << ".vue -->\n";
    ss << "<template>\n";
    ss << "  <div>\n";
    ss << "    <!-- Component template -->\n";
    ss << "  </div>\n";
    ss << "</template>\n\n";
    ss << "<script>\n";
    ss << "export default {\n";
    ss << "  name: '" << name << "',\n";
    ss << "  props: {},\n";
    ss << "  data() {\n";
    ss << "    return {};\n";
    ss << "  },\n";
    ss << "  methods: {}\n";
    ss << "};\n";
    ss << "</script>\n\n";
    ss << "<style scoped>\n";
    ss << "/* Component styles */\n";
    ss << "</style>\n";
    
    // 将组件代码添加到结果中
    // TODO: 目前暂时将组件代码添加到 JS 中
    result_.js += "\n/* Component: " + name + ".vue */\n" + ss.str();
}

std::string VueGenerator::convertToTemplate(const std::shared_ptr<Node>& node) {
    // 将节点转换为 Vue 模板
    std::stringstream ss;
    
    if (auto element = std::dynamic_pointer_cast<Element>(node)) {
        ss << "<" << element->getTagName();
        
        // 添加属性
        for (const auto& [key, value] : element->getAttributes()) {
            if (std::holds_alternative<std::string>(value)) {
                std::string strValue = std::get<std::string>(value);
                
                // 检查是否是 Vue 指令
                if (key.substr(0, 2) == "v-" || key[0] == '@' || key[0] == ':') {
                    ss << " " << key << "=\"" << strValue << "\"";
                } else {
                    ss << " " << key << "=\"" << strValue << "\"";
                }
            }
        }
        
        ss << ">";
        
        // 处理子节点
        for (const auto& child : element->getChildren()) {
            ss << convertToTemplate(child);
        }
        
        ss << "</" << element->getTagName() << ">";
    } else if (auto text = std::dynamic_pointer_cast<Text>(node)) {
        ss << text->getData();
    }
    
    return ss.str();
}

} // namespace chtl