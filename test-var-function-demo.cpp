#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <vector> // Added for std::vector

// 模拟变量组定义
std::map<std::string, std::map<std::string, std::string>> varGroups = {
    {"ThemeColor", {
        {"primary", "#3498db"},
        {"secondary", "#2ecc71"},
        {"danger", "#e74c3c"}
    }},
    {"Spacing", {
        {"small", "8px"},
        {"medium", "16px"},
        {"large", "24px"}
    }}
};

// 当前的实现：展开整个变量组
std::string expandVarGroup_Current(const std::string& varGroupName) {
    std::string result;
    if (varGroups.find(varGroupName) != varGroups.end()) {
        for (const auto& [key, value] : varGroups[varGroupName]) {
            result += key + ": " + value + ";\n";
        }
    }
    return result;
}

// 期望的实现：处理函数调用语法
std::string processVarReferences_Expected(const std::string& css) {
    std::string result = css;
    
    // 正则表达式匹配 VarName(property) 或 VarName(property = value)
    std::regex varRegex(R"((\w+)\((\w+)(?:\s*=\s*([^)]+))?\))");
    std::smatch match;
    
    auto searchStart = css.cbegin();
    std::vector<std::tuple<size_t, size_t, std::string>> replacements;
    
    while (std::regex_search(searchStart, css.cend(), match, varRegex)) {
        std::string varGroupName = match[1];
        std::string propertyName = match[2];
        std::string overrideValue = match[3]; // 可能为空
        
        size_t startPos = match.position() + (searchStart - css.cbegin());
        size_t length = match.length();
        
        std::string replacementValue;
        
        if (!overrideValue.empty()) {
            // 使用覆盖的值
            replacementValue = overrideValue;
        } else {
            // 查找变量组中的默认值
            if (varGroups.find(varGroupName) != varGroups.end() &&
                varGroups[varGroupName].find(propertyName) != varGroups[varGroupName].end()) {
                replacementValue = varGroups[varGroupName][propertyName];
            } else {
                replacementValue = "/* not found */";
            }
        }
        
        replacements.push_back({startPos, length, replacementValue});
        searchStart = match.suffix().first;
    }
    
    // 从后向前替换
    for (auto it = replacements.rbegin(); it != replacements.rend(); ++it) {
        result.replace(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it));
    }
    
    return result;
}

int main() {
    // 测试用例
    std::string testCss = R"(
div {
    color: ThemeColor(primary);
    background: ThemeColor(secondary);
    border-color: ThemeColor(danger = #ff0000);
    padding: Spacing(medium);
    margin: Spacing(large = 30px);
}
)";

    std::cout << "=== 测试输入 ===" << std::endl;
    std::cout << testCss << std::endl;
    
    std::cout << "\n=== 当前实现（错误）：展开整个变量组 ===" << std::endl;
    std::cout << "对于 @Var ThemeColor;  会生成：" << std::endl;
    std::cout << expandVarGroup_Current("ThemeColor") << std::endl;
    
    std::cout << "\n=== 期望实现：处理函数调用语法 ===" << std::endl;
    std::cout << processVarReferences_Expected(testCss) << std::endl;
    
    return 0;
}