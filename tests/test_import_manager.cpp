#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>
#include "Loader/ImportManager.h"
#include "Loader/DependencyGraph.h"
#include "Context/StandardContext.h"

using namespace chtl;
namespace fs = std::filesystem;

// 创建测试模块文件
void createTestModules() {
    // 创建测试目录
    fs::create_directories("test_modules");
    
    // 模块A：导入B和C
    std::ofstream moduleA("test_modules/moduleA.chtl");
    moduleA << "Import @Chtl from \"moduleB\"\n";
    moduleA << "Import @Chtl from \"moduleC\"\n";
    moduleA << "[Template] @Element Box {\n";
    moduleA << "    div { class \"box-a\" }\n";
    moduleA << "}\n";
    moduleA.close();
    
    // 模块B：导入C
    std::ofstream moduleB("test_modules/moduleB.chtl");
    moduleB << "Import @Chtl from \"moduleC\"\n";
    moduleB << "[Template] @Element Card {\n";
    moduleB << "    div { class \"card-b\" }\n";
    moduleB << "}\n";
    moduleB.close();
    
    // 模块C：基础模块
    std::ofstream moduleC("test_modules/moduleC.chtl");
    moduleC << "[Template] @Style BaseStyle {\n";
    moduleC << "    .base { color: #333 }\n";
    moduleC << "}\n";
    moduleC.close();
    
    // 模块D：循环依赖测试 - D导入E
    std::ofstream moduleD("test_modules/moduleD.chtl");
    moduleD << "Import @Chtl from \"moduleE\"\n";
    moduleD << "[Template] @Element ItemD {\n";
    moduleD << "    div { class \"item-d\" }\n";
    moduleD << "}\n";
    moduleD.close();
    
    // 模块E：循环依赖测试 - E导入D
    std::ofstream moduleE("test_modules/moduleE.chtl");
    moduleE << "Import @Chtl from \"moduleD\"\n";
    moduleE << "[Template] @Element ItemE {\n";
    moduleE << "    div { class \"item-e\" }\n";
    moduleE << "}\n";
    moduleE.close();
    
    // 模块F：测试符号冲突 - 定义相同的模板名
    std::ofstream moduleF("test_modules/moduleF.chtl");
    moduleF << "[Template] @Element Box {\n";  // 与moduleA冲突
    moduleF << "    div { class \"box-f\" }\n";
    moduleF << "}\n";
    moduleF.close();
}

void testBasicImport() {
    std::cout << "\n=== Test: Basic Import ===\n";
    
    ImportManager manager;
    auto context = std::make_shared<StandardContext>();
    manager.setContext(context);
    
    // 设置搜索路径
    ImportConfig config;
    config.searchPaths.push_back("test_modules");
    manager.setConfig(config);
    
    // 导入模块A
    auto result = manager.importModule("moduleA");
    
    if (result.success) {
        std::cout << "✓ Successfully imported moduleA\n";
        std::cout << "  Resolved path: " << result.resolvedPath << "\n";
        
        // 检查依赖图
        auto& depGraph = manager.getDependencyGraph();
        depGraph.printGraph();
    } else {
        std::cout << "✗ Failed to import moduleA\n";
        for (const auto& error : result.errors) {
            std::cout << "  Error: " << error << "\n";
        }
    }
}

void testCircularDependency() {
    std::cout << "\n=== Test: Circular Dependency Detection ===\n";
    
    ImportManager manager;
    auto context = std::make_shared<StandardContext>();
    manager.setContext(context);
    
    // 设置搜索路径
    ImportConfig config;
    config.searchPaths.push_back("test_modules");
    config.allowCircularDependencies = false;  // 禁止循环依赖
    manager.setConfig(config);
    
    // 尝试导入有循环依赖的模块D
    auto result = manager.importModule("moduleD");
    
    if (!result.success) {
        std::cout << "✓ Correctly detected circular dependency\n";
        for (const auto& error : result.errors) {
            std::cout << "  Error: " << error << "\n";
        }
        for (const auto& cycle : result.circularDeps) {
            std::cout << "  " << cycle.description << "\n";
        }
    } else {
        std::cout << "✗ Failed to detect circular dependency\n";
    }
    
    // 允许循环依赖再试一次
    std::cout << "\n--- Allowing circular dependencies ---\n";
    config.allowCircularDependencies = true;
    manager.setConfig(config);
    manager.clearCache();
    
    result = manager.importModule("moduleD");
    if (result.success) {
        std::cout << "✓ Successfully handled circular dependency with placeholder\n";
        for (const auto& warning : result.warnings) {
            std::cout << "  Warning: " << warning << "\n";
        }
    }
}

void testCacheAndReimport() {
    std::cout << "\n=== Test: Cache and Reimport ===\n";
    
    ImportManager manager;
    auto context = std::make_shared<StandardContext>();
    manager.setContext(context);
    
    ImportConfig config;
    config.searchPaths.push_back("test_modules");
    config.enableCache = true;
    manager.setConfig(config);
    
    // 第一次导入
    auto start = std::chrono::steady_clock::now();
    auto result1 = manager.importModule("moduleA");
    auto end = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "First import took: " << duration1 << " μs\n";
    
    // 第二次导入（应该从缓存）
    start = std::chrono::steady_clock::now();
    auto result2 = manager.importModule("moduleA");
    end = std::chrono::steady_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Second import took: " << duration2 << " μs\n";
    
    if (duration2 < duration1 / 2) {
        std::cout << "✓ Cache is working (second import is " 
                  << (duration1 / duration2) << "x faster)\n";
    } else {
        std::cout << "✗ Cache might not be working properly\n";
    }
    
    // 显示统计
    auto stats = manager.getStats();
    std::cout << "\nImport Statistics:\n";
    std::cout << "  Total imports: " << stats.totalImports << "\n";
    std::cout << "  Cached imports: " << stats.cachedImports << "\n";
    std::cout << "  Failed imports: " << stats.failedImports << "\n";
    std::cout << "  Circular imports: " << stats.circularImports << "\n";
}

void testSymbolConflicts() {
    std::cout << "\n=== Test: Symbol Conflicts ===\n";
    
    ImportManager manager;
    auto context = std::make_shared<StandardContext>();
    manager.setContext(context);
    
    ImportConfig config;
    config.searchPaths.push_back("test_modules");
    config.autoResolveConflicts = true;
    manager.setConfig(config);
    
    // 创建主模块导入A和F（都定义了Box）
    std::ofstream mainModule("test_modules/main.chtl");
    mainModule << "Import @Chtl from \"moduleA\"\n";
    mainModule << "Import @Chtl from \"moduleF\"\n";
    mainModule << "div { class \"main\" }\n";
    mainModule.close();
    
    auto result = manager.importModule("main");
    
    if (result.success) {
        std::cout << "✓ Successfully handled symbol conflicts\n";
        
        // 检查警告
        auto warnings = context->getWarnings();
        if (!warnings.empty()) {
            std::cout << "  Warnings:\n";
            for (const auto& warning : warnings) {
                std::cout << "    - " << warning << "\n";
            }
        }
    }
}

void testUnusedImports() {
    std::cout << "\n=== Test: Unused Imports Detection ===\n";
    
    ImportManager manager;
    auto context = std::make_shared<StandardContext>();
    manager.setContext(context);
    
    ImportConfig config;
    config.searchPaths.push_back("test_modules");
    config.detectUnusedImports = true;
    manager.setConfig(config);
    
    // 导入一些模块
    manager.importModule("moduleA");
    manager.importModule("moduleB");
    
    // 获取未使用的导入
    auto unused = manager.getUnusedImports();
    
    std::cout << "Unused imports: " << unused.size() << "\n";
    for (const auto& module : unused) {
        std::cout << "  - " << module << "\n";
    }
}

void cleanup() {
    // 清理测试文件
    fs::remove_all("test_modules");
}

int main() {
    std::cout << "CHTL Import Manager Tests\n";
    std::cout << "========================\n";
    
    try {
        // 创建测试模块
        createTestModules();
        
        // 运行测试
        testBasicImport();
        testCircularDependency();
        testCacheAndReimport();
        testSymbolConflicts();
        testUnusedImports();
        
        // 清理
        cleanup();
        
        std::cout << "\n✓ All tests completed\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        cleanup();
        return 1;
    }
    
    return 0;
}