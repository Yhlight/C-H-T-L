#include <iostream>
#include <fstream>
#include <filesystem>
#include "Loader/ImportResolver.h"

using namespace chtl;
namespace fs = std::filesystem;

void createTestFile(const std::string& path, const std::string& content = "") {
    fs::path filePath(path);
    fs::create_directories(filePath.parent_path());
    
    std::ofstream file(path);
    file << content;
    file.close();
}

void testImportResolver() {
    std::cout << "Testing Import Resolver\n";
    std::cout << "======================\n\n";
    
    // 创建测试目录结构
    fs::create_directories("test_imports/components");
    fs::create_directories("test_imports/styles");
    fs::create_directories("test_imports/scripts");
    
    // 创建测试文件
    createTestFile("test_imports/main.html", "<h1>Main</h1>");
    createTestFile("test_imports/styles/main.css", "body { margin: 0; }");
    createTestFile("test_imports/scripts/main.js", "console.log('Hello');");
    createTestFile("test_imports/components/button.chtl", "[Custom] @Element Button {}");
    createTestFile("test_imports/test.chtl", "// Test file");
    
    ImportResolver resolver;
    std::string currentFile = fs::absolute("test_imports/test.chtl").string();
    
    // 测试1：导入HTML文件（带扩展名）
    {
        std::cout << "Test 1: Import HTML with extension\n";
        auto result = resolver.resolve("main.html", Import::ImportType::HTML, currentFile);
        
        std::cout << "  Success: " << (result.success ? "YES" : "NO") << "\n";
        if (result.success) {
            std::cout << "  Resolved path: " << result.resolvedPath << "\n";
            std::cout << "  Extension: " << result.fileExtension << "\n";
        } else {
            std::cout << "  Error: " << result.errorMessage << "\n";
        }
    }
    
    // 测试2：导入HTML文件（不带扩展名）
    {
        std::cout << "\nTest 2: Import HTML without extension\n";
        auto result = resolver.resolve("main", Import::ImportType::HTML, currentFile);
        
        std::cout << "  Success: " << (result.success ? "YES" : "NO") << "\n";
        if (result.success) {
            std::cout << "  Resolved path: " << result.resolvedPath << "\n";
            std::cout << "  Extension: " << result.fileExtension << "\n";
        } else {
            std::cout << "  Error: " << result.errorMessage << "\n";
        }
    }
    
    // 测试3：导入CSS文件（使用.表示/）
    {
        std::cout << "\nTest 3: Import CSS with dot notation\n";
        auto result = resolver.resolve("styles.main", Import::ImportType::CSS, currentFile);
        
        std::cout << "  Success: " << (result.success ? "YES" : "NO") << "\n";
        if (result.success) {
            std::cout << "  Resolved path: " << result.resolvedPath << "\n";
        } else {
            std::cout << "  Error: " << result.errorMessage << "\n";
            std::cout << "  Note: This should convert 'styles.main' to 'styles/main.css'\n";
        }
    }
    
    // 测试4：导入JS文件（相对路径）
    {
        std::cout << "\nTest 4: Import JS with relative path\n";
        auto result = resolver.resolve("scripts/main.js", Import::ImportType::JS, currentFile);
        
        std::cout << "  Success: " << (result.success ? "YES" : "NO") << "\n";
        if (result.success) {
            std::cout << "  Resolved path: " << result.resolvedPath << "\n";
        } else {
            std::cout << "  Error: " << result.errorMessage << "\n";
        }
    }
    
    // 测试5：导入不存在的文件
    {
        std::cout << "\nTest 5: Import non-existent file\n";
        auto result = resolver.resolve("notfound.html", Import::ImportType::HTML, currentFile);
        
        std::cout << "  Success: " << (result.success ? "YES" : "NO") << "\n";
        std::cout << "  Error: " << result.errorMessage << "\n";
    }
    
    // 测试6：错误的扩展名
    {
        std::cout << "\nTest 6: Wrong extension\n";
        auto result = resolver.resolve("main.css", Import::ImportType::HTML, currentFile);
        
        std::cout << "  Success: " << (result.success ? "YES" : "NO") << "\n";
        std::cout << "  Error: " << result.errorMessage << "\n";
    }
    
    // 清理测试文件
    fs::remove_all("test_imports");
}

int main() {
    try {
        testImportResolver();
        std::cout << "\n✓ All import resolver tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}