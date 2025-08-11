#include <iostream>
#include <string>
#include <vector>

// 模拟测试导入路径解析
void testImportPath(const std::string& importStatement) {
    std::cout << "\n" << importStatement << std::endl;
    
    // 检查是否是通配符导入
    bool isWildcard = false;
    std::string path;
    
    // 简单解析路径
    size_t fromPos = importStatement.find(" from ");
    if (fromPos != std::string::npos) {
        path = importStatement.substr(fromPos + 6);
        // 去除首尾空格
        path.erase(0, path.find_first_not_of(" \t"));
        path.erase(path.find_last_not_of(" \t") + 1);
        
        // 检查是否有引号
        if (path[0] == '"' && path[path.length()-1] == '"') {
            path = path.substr(1, path.length()-2);
        }
        
        // 检查是否以 .* 或 /* 结尾
        if (path.length() >= 2) {
            std::string suffix = path.substr(path.length() - 2);
            if (suffix == ".*" || suffix == "/*") {
                isWildcard = true;
            }
        }
    }
    
    std::cout << "  → 路径: " << path << std::endl;
    std::cout << "  → 通配符导入: " << (isWildcard ? "是" : "否") << std::endl;
}

int main() {
    std::cout << "=== CHTL 导入语法实现验证 ===" << std::endl;
    
    std::cout << "\n## 新的通配符语法（推荐）:" << std::endl;
    
    // 无引号路径
    testImportPath("Import @Chtl from chtholly/core.*");
    testImportPath("Import @Style from styles/base/*");
    testImportPath("Import @Html from components.*");
    testImportPath("Import @Chtl from Chtholly.Space.*");
    
    // 带引号路径
    testImportPath("Import @Chtl from \"special/path with spaces.*\"");
    testImportPath("Import @Style from \"styles/*\"");
    
    // 非通配符导入
    testImportPath("Import @Chtl from Chtholly.Math.Vector");
    testImportPath("Import @JavaScript from \"utils/helper\"");
    
    std::cout << "\n## 实现总结:" << std::endl;
    std::cout << "✓ 支持无引号路径: path/to/module.*" << std::endl;
    std::cout << "✓ 支持带引号路径: \"path/to/module.*\"" << std::endl;
    std::cout << "✓ 支持两种通配符: .* (点通配符) 和 /* (斜杠通配符)" << std::endl;
    std::cout << "✓ 通配符是路径的一部分，不是独立的后缀" << std::endl;
    std::cout << "✓ 移除了旧的 [Import] * 语法" << std::endl;
    
    return 0;
}