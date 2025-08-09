#include <iostream>
#include <string>
#include <memory>
#include "Scanner/BridgeScanner.h"
#include "Chtl_Js/ChtlJsCompiler.h"

using namespace chtl;

void printSegment(std::shared_ptr<Segment> segment) {
    std::cout << "Segment Type: ";
    switch (segment->getType()) {
        case SegmentType::JavaScript:
            std::cout << "JavaScript";
            break;
        case SegmentType::ChtlJavaScript:
            std::cout << "CHTL-JavaScript";
            break;
        case SegmentType::Mixed:
            std::cout << "Mixed";
            break;
    }
    std::cout << "\n";
    std::cout << "Code:\n" << segment->getCode() << "\n";
    std::cout << "Location: " << segment->getSourceInfo().filename 
              << " (" << segment->getSourceInfo().startLine << ":"
              << segment->getSourceInfo().startColumn << " - "
              << segment->getSourceInfo().endLine << ":"
              << segment->getSourceInfo().endColumn << ")\n";
    std::cout << "---\n";
}

int main() {
    std::cout << "=== CHTL-JS Compiler Test ===\n\n";
    
    // 测试代码
    std::string testCode = R"(
// 标准JavaScript代码
function init() {
    console.log("Initializing...");
}

// CHTL-JS增强选择器
{{.box}}.textContent = "Hello CHTL!";
{{#header}}->listen({
    click: () => {
        console.log("Header clicked");
    },
    mouseenter: function() {
        this.style.color = "red";
    }
});

// 事件委托
{{document.body}}->delegate({
    target: [{{.button}}, {{.link}}],
    click: (e) => {
        console.log("Delegated click:", e.target);
    }
});

// 动画
animate({
    duration: 1000,
    easing: "ease-in-out",
    begin: {
        opacity: 0,
        transform: "scale(0.8)"
    },
    when: [
        {
            at: 0.5,
            opacity: 0.8,
            transform: "scale(1.1)"
        }
    ],
    end: {
        opacity: 1,
        transform: "scale(1)"
    }
});

// 更多标准JS
const data = [1, 2, 3, 4, 5];
data.forEach(item => console.log(item));
)";

    // 创建桥接扫描器
    BridgeScanner scanner;
    scanner.initialize();
    
    std::cout << "1. Scanning code...\n\n";
    
    // 扫描代码
    auto scanResult = scanner.scan(testCode, "test.chtl.js");
    
    if (!scanResult.success) {
        std::cout << "Scan failed!\n";
        for (const auto& error : scanResult.errors) {
            std::cout << "Error: " << error << "\n";
        }
        return 1;
    }
    
    std::cout << "Found " << scanResult.segments.size() << " segments\n\n";
    
    // 显示每个段
    for (const auto& segment : scanResult.segments) {
        printSegment(segment);
    }
    
    // 测试CHTL-JS编译器
    std::cout << "\n2. Compiling CHTL-JS segments...\n\n";
    
    chtl_js::ChtlJsCompiler compiler;
    
    // 设置编译选项
    chtl_js::ChtlJsCompiler::CompileOptions options;
    options.injectRuntime = true;
    options.cacheSelectors = true;
    options.debugMode = true;
    
    // 编译每个CHTL-JS段
    for (const auto& segment : scanResult.segments) {
        if (segment->getType() == SegmentType::ChtlJavaScript) {
            std::cout << "Compiling CHTL-JS segment...\n";
            
            auto result = compiler.compile(segment->getCode(), 
                                         segment->getSourceInfo().filename,
                                         options);
            
            if (result.success) {
                std::cout << "Compilation successful!\n";
                std::cout << "Generated code:\n" << result.code << "\n";
                std::cout << "Statistics:\n";
                std::cout << "  - Selectors found: " << result.stats.selectorsFound << "\n";
                std::cout << "  - Methods transformed: " << result.stats.methodsTransformed << "\n";
                std::cout << "  - Animations processed: " << result.stats.animationsProcessed << "\n";
            } else {
                std::cout << "Compilation failed!\n";
                for (const auto& error : result.errors) {
                    std::cout << "Error: " << error << "\n";
                }
            }
            std::cout << "---\n";
        }
    }
    
    // 测试运行时代码生成
    std::cout << "\n3. CHTL Runtime Code:\n\n";
    std::cout << chtl_js::ChtlJsCompiler::getChtlRuntime(false) << "\n";
    
    return 0;
}