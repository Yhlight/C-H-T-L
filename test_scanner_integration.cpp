#include "v2/Scanner/Scanner.h"
#include "v2/ChtlJs/ChtlJsCompiler.h"
#include "v2/Js/NativeJsAnalyzer.h"
#include <iostream>
#include <iomanip>

using namespace chtl::v2;

void printSegment(const CodeSegment& segment) {
    std::cout << "  Type: ";
    switch (segment.type) {
        case SegmentType::JS: std::cout << "JavaScript"; break;
        case SegmentType::CHTL_JS: std::cout << "CHTL-JS"; break;
        default: std::cout << "Unknown"; break;
    }
    std::cout << std::endl;
    std::cout << "  Position: " << segment.startLine << ":" << segment.startColumn 
              << " - " << segment.endLine << ":" << segment.endColumn << std::endl;
    std::cout << "  Content: " << segment.content << std::endl;
    if (segment.type == SegmentType::CHTL_JS) {
        std::cout << "  Placeholder: " << segment.chtlJsInfo.placeholder << std::endl;
    }
    std::cout << std::endl;
}

void testJsScanner() {
    std::cout << "=== JavaScript 扫描器测试 ===" << std::endl;
    
    std::string jsCode = R"(
// 测试 CHTL-JS 语法
const app = {{#app}};
const header = {{#header}};

// 事件处理
{{#button}}.listen('click', (e) => {
    console.log('Button clicked');
    {{&}}.classList.add('active');
});

// 普通 JavaScript
function processData() {
    const items = document.querySelectorAll('.item');
    items.forEach(item => {
        item.addEventListener('mouseover', () => {
            console.log('Hover on item');
        });
    });
}

// 更多 CHTL-JS
const currentElement = {{&}};
if (currentElement) {
    currentElement.style.display = 'block';
}
)";

    // 测试不同扫描模式
    std::vector<ScanMode> modes = {ScanMode::STRICT, ScanMode::LOOSE, ScanMode::HYBRID};
    std::vector<std::string> modeNames = {"STRICT", "LOOSE", "HYBRID"};
    
    for (size_t i = 0; i < modes.size(); i++) {
        std::cout << "\n--- " << modeNames[i] << " 模式 ---" << std::endl;
        
        JsScanner scanner;
        scanner.setScanMode(modes[i]);
        
        auto segments = scanner.scan(jsCode, SegmentType::JS);
        
        std::cout << "扫描到 " << segments.size() << " 个代码段" << std::endl;
        
        for (size_t j = 0; j < segments.size(); j++) {
            std::cout << "\n段 " << (j + 1) << ":" << std::endl;
            printSegment(segments[j]);
        }
        
        auto errors = scanner.getErrors();
        if (!errors.empty()) {
            std::cout << "\n扫描错误:" << std::endl;
            for (const auto& error : errors) {
                std::cout << "  - " << error << std::endl;
            }
        }
    }
}

void testChtlJsCompilation() {
    std::cout << "\n\n=== CHTL-JS 编译测试 ===" << std::endl;
    
    std::string jsCode = R"(
// 初始化
const container = {{#container}};
const items = container.querySelectorAll('.item');

// 事件绑定
{{#submit-btn}}.listen('click', function(e) {
    e.preventDefault();
    const form = {{&}}.closest('form');
    if (validateForm(form)) {
        submitData(form);
    }
});

// 动态更新
function updateUI() {
    {{#status}}.textContent = 'Loading...';
    fetchData().then(data => {
        {{#status}}.textContent = 'Ready';
        renderData(data);
    });
}
)";

    // 设置上下文
    std::map<std::string, std::string> context;
    context["currentElement"] = "document.currentScript.parentElement";
    
    // 编译 CHTL-JS
    chtljs::ChtlJsCompiler compiler;
    auto result = compiler.compile(jsCode, context);
    
    std::cout << "\n编译结果:" << std::endl;
    std::cout << "成功: " << (result.success ? "是" : "否") << std::endl;
    
    if (!result.errors.empty()) {
        std::cout << "\n错误:" << std::endl;
        for (const auto& error : result.errors) {
            std::cout << "  - " << error << std::endl;
        }
    }
    
    std::cout << "\n编译后的 JavaScript:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << result.javascript << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::cout << "\n元数据:" << std::endl;
    std::cout << "  包含元素选择器: " << (result.hasElementSelectors ? "是" : "否") << std::endl;
    std::cout << "  包含当前元素引用: " << (result.hasCurrentElement ? "是" : "否") << std::endl;
    std::cout << "  包含 listen 方法: " << (result.hasListenMethod ? "是" : "否") << std::endl;
    
    if (!result.dependencies.empty()) {
        std::cout << "\n依赖:" << std::endl;
        for (const auto& dep : result.dependencies) {
            std::cout << "  - " << dep << std::endl;
        }
    }
    
    // 分析编译后的代码
    std::cout << "\n\n=== JavaScript 静态分析 ===" << std::endl;
    js::NativeJsAnalyzer analyzer;
    auto analysisResult = analyzer.analyze(result.javascript);
    
    std::cout << "分析结果:" << std::endl;
    std::cout << "  有效: " << (analysisResult.valid ? "是" : "否") << std::endl;
    std::cout << "  函数数: " << analysisResult.functionCount << std::endl;
    std::cout << "  变量数: " << analysisResult.variables.size() << std::endl;
    
    if (!analysisResult.warnings.empty()) {
        std::cout << "\n分析警告:" << std::endl;
        for (const auto& warning : analysisResult.warnings) {
            std::cout << "  - " << warning << std::endl;
        }
    }
}

void testPerformance() {
    std::cout << "\n\n=== 性能测试 ===" << std::endl;
    
    // 生成大型 JavaScript 代码
    std::ostringstream largeCode;
    for (int i = 0; i < 100; i++) {
        largeCode << "function func" << i << "() {\n";
        largeCode << "  const elem" << i << " = {{#elem" << i << "}};\n";
        largeCode << "  elem" << i << ".addEventListener('click', () => {\n";
        largeCode << "    console.log('Clicked " << i << "');\n";
        largeCode << "  });\n";
        largeCode << "}\n\n";
    }
    
    std::string code = largeCode.str();
    std::cout << "测试代码大小: " << code.size() << " 字节" << std::endl;
    
    // 测试宽判模式性能
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        JsScanner scanner;
        scanner.setScanMode(ScanMode::LOOSE);
        auto segments = scanner.scan(code, SegmentType::JS);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\n宽判模式:" << std::endl;
        std::cout << "  扫描时间: " << duration.count() << " 微秒" << std::endl;
        std::cout << "  代码段数: " << segments.size() << std::endl;
    }
    
    // 测试严判模式性能
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        JsScanner scanner;
        scanner.setScanMode(ScanMode::STRICT);
        auto segments = scanner.scan(code, SegmentType::JS);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\n严判模式:" << std::endl;
        std::cout << "  扫描时间: " << duration.count() << " 微秒" << std::endl;
        std::cout << "  代码段数: " << segments.size() << std::endl;
    }
    
    // 测试编译性能
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        chtljs::ChtlJsCompiler compiler;
        auto result = compiler.compile(code, {});
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\nCHTL-JS 编译:" << std::endl;
        std::cout << "  编译时间: " << duration.count() << " 微秒" << std::endl;
        std::cout << "  表达式数: " << result.expressions.size() << std::endl;
    }
}

int main() {
    try {
        testJsScanner();
        testChtlJsCompilation();
        testPerformance();
        
        std::cout << "\n\n=== 测试完成 ===" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}