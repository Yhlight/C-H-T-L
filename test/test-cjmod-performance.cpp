#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include "CJmod/CHTLJSProcessor.h"
#include "CJmod/CHTLJSProcessorOptimized.h"
#include "CJmod/CJmodLoader.h"

using namespace chtl::cjmod;
using namespace std::chrono;

// 生成测试代码
std::string generateTestCode(size_t size) {
    std::stringstream code;
    
    for (size_t i = 0; i < size; ++i) {
        // 生成各种CHTL JS语法
        code << "reactive count" << i << " = 0;\n";
        code << "watch(count" << i << ", (newVal) => console.log(newVal));\n";
        code << "computed sum" << i << " = () => { return count" << i << " + 1; }\n";
        code << "async* function fetchData" << i << "() { return await fetch('/api/" << i << "'); }\n";
        code << "let result" << i << " = data |> process |> format;\n";
        code << "console.log(`Result ${result" << i << "}!`);\n\n";
    }
    
    return code.str();
}

void runPerformanceTest() {
    std::cout << "=== CJmod Performance Test ===\n\n";
    
    // 创建处理器
    CHTLJSProcessor processor;
    CHTLJSProcessorOptimized optimizedProcessor;
    
    // 加载内置模块
    auto& loader = CJmodLoader::getInstance();
    loader.initializeBuiltins();
    
    // 注册响应式模块
    auto reactiveModule = loader.loadModule("builtin:reactive");
    if (reactiveModule) {
        processor.registerModule("reactive", reactiveModule);
        optimizedProcessor.registerModule("reactive", reactiveModule);
    }
    
    // 测试不同大小的代码
    std::vector<size_t> testSizes = {100, 500, 1000, 5000, 10000};
    std::vector<std::string> activeModules = {"reactive"};
    
    for (size_t size : testSizes) {
        std::cout << "Testing with " << size << " code blocks:\n";
        
        std::string testCode = generateTestCode(size);
        std::cout << "  Generated code size: " << testCode.size() / 1024.0 << " KB\n";
        
        // 测试原始处理器
        auto start = high_resolution_clock::now();
        std::string result1 = processor.processJavaScript(testCode, activeModules);
        auto end = high_resolution_clock::now();
        auto duration1 = duration_cast<milliseconds>(end - start).count();
        std::cout << "  Original processor: " << duration1 << " ms\n";
        
        // 测试优化处理器
        start = high_resolution_clock::now();
        std::string result2 = optimizedProcessor.process(testCode, activeModules);
        end = high_resolution_clock::now();
        auto duration2 = duration_cast<milliseconds>(end - start).count();
        std::cout << "  Optimized processor: " << duration2 << " ms\n";
        
        // 计算提升
        double improvement = ((double)duration1 - duration2) / duration1 * 100;
        std::cout << "  Performance improvement: " << improvement << "%\n";
        
        // 验证结果一致性
        if (result1 != result2) {
            std::cout << "  WARNING: Results differ!\n";
        }
        
        // 显示优化处理器的统计
        auto stats = optimizedProcessor.getStats();
        std::cout << "  Statistics:\n";
        std::cout << "    Total rules: " << stats.totalRules << "\n";
        std::cout << "    Total matches: " << stats.totalMatches << "\n";
        std::cout << "    Scan time: " << stats.scanTime * 1000 << " ms\n";
        std::cout << "    Replace time: " << stats.replaceTime * 1000 << " ms\n";
        std::cout << "    Throughput: " << stats.bytesProcessed / stats.scanTime / 1024 / 1024 << " MB/s\n";
        
        optimizedProcessor.resetStats();
        std::cout << "\n";
    }
    
    // 测试缓存效果
    std::cout << "Testing cache performance:\n";
    std::string testCode = generateTestCode(1000);
    
    // 第一次运行（无缓存）
    auto start = high_resolution_clock::now();
    optimizedProcessor.process(testCode, activeModules);
    auto end = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(end - start).count();
    std::cout << "  First run: " << duration1 << " μs\n";
    
    // 第二次运行（有缓存）
    start = high_resolution_clock::now();
    optimizedProcessor.process(testCode, activeModules);
    end = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(end - start).count();
    std::cout << "  Second run (cached): " << duration2 << " μs\n";
    std::cout << "  Cache speedup: " << duration1 / (double)duration2 << "x\n";
}

int main() {
    try {
        runPerformanceTest();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}