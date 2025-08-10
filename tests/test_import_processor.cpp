#include <iostream>
#include <fstream>
#include <filesystem>
#include "Loader/ImportProcessor.h"
#include "Context/StandardContext.h"
#include "Node/Import.h"

using namespace chtl;
namespace fs = std::filesystem;

void createTestFile(const std::string& path, const std::string& content) {
    fs::path filePath(path);
    fs::create_directories(filePath.parent_path());
    
    std::ofstream file(path);
    file << content;
    file.close();
}

void printResult(const ImportProcessResult& result) {
    std::cout << "  Success: " << (result.success ? "YES" : "NO") << "\n";
    
    if (!result.errors.empty()) {
        std::cout << "  Errors:\n";
        for (const auto& error : result.errors) {
            std::cout << "    - " << error << "\n";
        }
    }
    
    if (!result.warnings.empty()) {
        std::cout << "  Warnings:\n";
        for (const auto& warning : result.warnings) {
            std::cout << "    - " << warning << "\n";
        }
    }
    
    std::cout << "  Generated nodes: " << result.generatedNodes.size() << "\n";
    for (size_t i = 0; i < result.generatedNodes.size(); ++i) {
        auto node = result.generatedNodes[i];
        std::string nodeType = "Node";
        if (auto origin = std::dynamic_pointer_cast<Origin>(node)) {
            nodeType = "Origin";
        } else if (auto elem = std::dynamic_pointer_cast<Element>(node)) {
            nodeType = "Element";
        }
        std::cout << "    [" << i << "] " << nodeType 
                  << " (" << node->getTagName() << ")\n";
    }
}

void testImportProcessor() {
    // 创建测试目录和文件
    fs::create_directories("test_imports");
    createTestFile("test_imports/page.html", "<div>Hello World</div>");
    createTestFile("test_imports/style.css", "body { color: red; }");
    createTestFile("test_imports/script.js", "console.log('loaded');");
    
    auto context = std::make_shared<StandardContext>();
    ImportProcessor processor(context);
    
    std::string currentFile = fs::absolute("test_imports/test.chtl").string();
    
    std::cout << "Testing Import Processor\n";
    std::cout << "=======================\n\n";
    
    // 测试1：HTML导入（无as）
    {
        std::cout << "Test 1: HTML import without 'as'\n";
        auto importNode = std::make_shared<Import>();
        importNode->setType(Import::ImportType::HTML);
        importNode->setPath("page.html");
        
        auto result = processor.processImport(importNode, currentFile);
        printResult(result);
    }
    
    // 测试2：HTML导入（有as）
    {
        std::cout << "\nTest 2: HTML import with 'as'\n";
        auto importNode = std::make_shared<Import>();
        importNode->setType(Import::ImportType::HTML);
        importNode->setPath("page.html");
        importNode->setAlias("myPage");
        
        auto result = processor.processImport(importNode, currentFile);
        printResult(result);
    }
    
    // 测试3：CSS导入（外部链接）
    {
        std::cout << "\nTest 3: CSS import (external link)\n";
        auto importNode = std::make_shared<Import>();
        importNode->setType(Import::ImportType::CSS);
        importNode->setPath("style.css");
        
        auto result = processor.processImport(importNode, currentFile);
        printResult(result);
    }
    
    // 测试4：CSS导入（内联）
    {
        std::cout << "\nTest 4: CSS import (inline)\n";
        auto importNode = std::make_shared<Import>();
        importNode->setType(Import::ImportType::CSS);
        importNode->setPath("style.css");
        importNode->setInline(true);
        
        auto result = processor.processImport(importNode, currentFile);
        printResult(result);
    }
    
    // 测试5：JS导入（带as和inline）
    {
        std::cout << "\nTest 5: JS import with 'as' and 'inline'\n";
        auto importNode = std::make_shared<Import>();
        importNode->setType(Import::ImportType::JS);
        importNode->setPath("script.js");
        importNode->setAlias("myScript");
        importNode->setInline(true);
        
        auto result = processor.processImport(importNode, currentFile);
        printResult(result);
    }
    
    // 清理
    fs::remove_all("test_imports");
}

int main() {
    try {
        testImportProcessor();
        std::cout << "\n✓ All import processor tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}