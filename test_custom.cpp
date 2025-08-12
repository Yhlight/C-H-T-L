#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

// CHTL 自定义功能测试

struct CustomComponent {
    std::string name;
    std::string type;
    std::vector<std::string> params;
    std::string body;
    std::string extends;
};

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    
    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

std::vector<CustomComponent> parseCustomComponents(const std::string& source) {
    std::vector<CustomComponent> components;
    
    // 匹配 [Custom] 声明
    std::regex customRegex(R"(\[Custom\]\s*@(\w+)\s+(\w+)(?:\s*\(([^)]*)\))?(?:\s+extends\s+(\w+))?\s*\{)");
    std::smatch match;
    
    std::string::const_iterator searchStart(source.cbegin());
    while (std::regex_search(searchStart, source.cend(), match, customRegex)) {
        CustomComponent comp;
        comp.type = match[1];
        comp.name = match[2];
        
        // 解析参数
        if (match[3].matched) {
            std::string params = match[3];
            std::regex paramRegex(R"(\s*(\w+)(?:\s*=\s*\"([^\"]*)\")?\s*(?:,|$))");
            std::smatch paramMatch;
            
            std::string::const_iterator paramStart(params.cbegin());
            while (std::regex_search(paramStart, params.cend(), paramMatch, paramRegex)) {
                comp.params.push_back(paramMatch[1]);
                paramStart = paramMatch.suffix().first;
            }
        }
        
        // 继承
        if (match[4].matched) {
            comp.extends = match[4];
        }
        
        components.push_back(comp);
        searchStart = match.suffix().first;
    }
    
    return components;
}

void printCustomComponents(const std::vector<CustomComponent>& components) {
    std::cout << "\n发现的自定义组件:\n";
    std::cout << "==================\n\n";
    
    // 按类型分组
    std::map<std::string, std::vector<const CustomComponent*>> byType;
    for (const auto& comp : components) {
        byType[comp.type].push_back(&comp);
    }
    
    for (const auto& [type, comps] : byType) {
        std::cout << "## @" << type << " 组件:\n";
        for (const auto* comp : comps) {
            std::cout << "  - " << comp->name;
            
            if (!comp->params.empty()) {
                std::cout << "(";
                for (size_t i = 0; i < comp->params.size(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << comp->params[i];
                }
                std::cout << ")";
            }
            
            if (!comp->extends.empty()) {
                std::cout << " extends " << comp->extends;
            }
            
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void validateCustomFeatures(const std::string& source) {
    std::cout << "验证自定义功能特性:\n";
    std::cout << "===================\n\n";
    
    // 检查各种自定义类型
    struct FeatureTest {
        std::string feature;
        std::string pattern;
        std::string description;
    };
    
    std::vector<FeatureTest> tests = {
        {"Custom Element", R"(\[Custom\]\s*@Element)", "自定义元素组件"},
        {"Custom Style", R"(\[Custom\]\s*@Style)", "自定义样式组件"},
        {"Custom Script", R"(\[Custom\]\s*@Script)", "自定义脚本组件"},
        {"Custom Var", R"(\[Custom\]\s*@Var)", "自定义变量组件"},
        {"Component Parameters", R"(@\w+\s*\([^)]+\))", "组件参数传递"},
        {"Default Parameters", R"(\w+\s*=\s*\"[^\"]+\")", "默认参数值"},
        {"Component Inheritance", R"(extends\s+\w+)", "组件继承"},
        {"Slot Usage", R"(\{\{slot(?::[^}]+)?\}\})", "插槽使用"},
        {"Prepend Directive", R"(prepend\s+)", "prepend 指令"},
        {"Component Usage", R"(@\w+\s*\()", "组件使用"},
    };
    
    for (const auto& test : tests) {
        std::regex regex(test.pattern);
        if (std::regex_search(source, regex)) {
            std::cout << "✓ " << test.feature << " - " << test.description << "\n";
        } else {
            std::cout << "✗ " << test.feature << " - " << test.description << "\n";
        }
    }
}

void analyzeComponentUsage(const std::string& source) {
    std::cout << "\n组件使用分析:\n";
    std::cout << "=============\n\n";
    
    // 查找所有组件使用
    std::regex usageRegex(R"(@(\w+)(?:\s*\(([^)]*)\))?(?:\s+([^{]+))?\s*(?:\{|$))");
    std::smatch match;
    
    std::map<std::string, int> usageCount;
    
    std::string::const_iterator searchStart(source.cbegin());
    while (std::regex_search(searchStart, source.cend(), match, usageRegex)) {
        std::string compName = match[1];
        usageCount[compName]++;
        searchStart = match.suffix().first;
    }
    
    std::cout << "组件使用统计:\n";
    for (const auto& [name, count] : usageCount) {
        std::cout << "  - " << name << ": " << count << " 次\n";
    }
}

int main() {
    std::cout << "CHTL 自定义功能测试\n";
    std::cout << "===================\n";
    
    try {
        // 读取测试文件
        std::string testFile = "/workspace/test/test-custom.chtl";
        std::cout << "\n读取测试文件: " << testFile << "\n";
        
        std::string source = readFile(testFile);
        std::cout << "文件大小: " << source.size() << " 字节\n";
        
        // 解析自定义组件
        auto components = parseCustomComponents(source);
        printCustomComponents(components);
        
        // 验证功能特性
        validateCustomFeatures(source);
        
        // 分析组件使用
        analyzeComponentUsage(source);
        
        // 特殊功能分析
        std::cout << "\n特殊功能分析:\n";
        std::cout << "=============\n\n";
        
        // 检查插槽
        std::regex slotRegex(R"(\{\{slot(?::(\w+))?\}\})");
        std::smatch slotMatch;
        std::vector<std::string> slots;
        
        std::string::const_iterator slotStart(source.cbegin());
        while (std::regex_search(slotStart, source.cend(), slotMatch, slotRegex)) {
            if (slotMatch[1].matched) {
                slots.push_back("命名插槽: " + slotMatch[1].str());
            } else {
                slots.push_back("默认插槽");
            }
            slotStart = slotMatch.suffix().first;
        }
        
        if (!slots.empty()) {
            std::cout << "发现的插槽:\n";
            for (const auto& slot : slots) {
                std::cout << "  - " << slot << "\n";
            }
        }
        
        std::cout << "\n自定义功能测试完成！\n";
        std::cout << "\nCHTL 自定义功能的优势:\n";
        std::cout << "1. 组件化开发 - 创建可重用的自定义组件\n";
        std::cout << "2. 参数化 - 支持参数和默认值\n";
        std::cout << "3. 继承机制 - 扩展现有组件\n";
        std::cout << "4. 插槽系统 - 灵活的内容分发\n";
        std::cout << "5. 多类型支持 - Element/Style/Script/Var\n";
        std::cout << "6. 封装性 - 样式和脚本与组件绑定\n";
        
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}