#include <iostream>
#include <string>
#include <memory>
#include "Scanner/BridgeScanner.h"
#include "Scanner/Segment.h"

using namespace std;
using namespace chtl;

void printSegment(shared_ptr<Segment> segment) {
    cout << "\n=== Segment ===" << endl;
    cout << "Type: " << segment->getTypeString() << endl;
    cout << "Content Preview: " << endl;
    cout << segment->toString() << endl;
    
    if (segment->getType() == SegmentType::CHTL_JAVASCRIPT) {
        auto chtlSeg = dynamic_pointer_cast<ChtlJavaScriptSegment>(segment);
        if (chtlSeg) {
            auto& features = chtlSeg->getFeatures();
            cout << "CHTL Features:" << endl;
            if (features.hasTemplateFunction) cout << "  - Template Function" << endl;
            if (features.hasOperatorExtension) cout << "  - Operator Extension" << endl;
            if (features.hasNullSafety) cout << "  - Null Safety" << endl;
            if (features.hasPipeOperator) cout << "  - Pipe Operator" << endl;
            if (features.hasPatternMatching) cout << "  - Pattern Matching" << endl;
            if (features.hasAsyncExtensions) cout << "  - Async Extensions" << endl;
            if (features.hasReactiveBindings) cout << "  - Reactive Bindings" << endl;
        }
    }
}

void testBasicScanning() {
    cout << "\n========== Test Basic Scanning ==========" << endl;
    
    BridgeScanner scanner;
    scanner.initialize();
    
    // 注册处理器
    scanner.registerJsHandler([](shared_ptr<Segment> seg) {
        cout << "[JS Handler] Received JavaScript segment" << endl;
        (void)seg; // 避免未使用参数警告
    });
    
    scanner.registerChtlJsHandler([](shared_ptr<Segment> seg) {
        cout << "[CHTL Handler] Received CHTL JavaScript segment" << endl;
        (void)seg; // 避免未使用参数警告
    });
    
    // 测试纯JavaScript代码
    string jsCode = R"(
        function hello() {
            console.log("Hello, World!");
        }
        
        const arr = [1, 2, 3];
        arr.map(x => x * 2);
    )";
    
    cout << "\nScanning pure JavaScript code..." << endl;
    auto result1 = scanner.scan(jsCode, "test.js");
    cout << "Segments found: " << result1.segments.size() << endl;
    for (auto& seg : result1.segments) {
        printSegment(seg);
    }
}

void testChtlFeatures() {
    cout << "\n========== Test CHTL Features ==========" << endl;
    
    BridgeScanner scanner;
    scanner.initialize();
    
    // 测试CHTL特性代码
    string chtlCode = R"(
        // CHTL模板函数
        @template function render(data) {
            return `<div>${data.name}</div>`;
        }
        
        // 管道操作符
        const result = getData()
            |> filter(x => x > 0)
            |> map(x => x * 2)
            |> reduce((a, b) => a + b);
        
        // 空安全操作
        const value = obj?.property?.method?.();
        const defaultValue = value ?? "default";
        
        // 响应式绑定
        @reactive let count = 0;
        $count.subscribe(val => console.log(val));
    )";
    
    cout << "\nScanning CHTL JavaScript code..." << endl;
    auto result2 = scanner.scan(chtlCode, "test.chtl.js");
    cout << "Segments found: " << result2.segments.size() << endl;
    for (auto& seg : result2.segments) {
        printSegment(seg);
    }
}

void testMixedCode() {
    cout << "\n========== Test Mixed Code ==========" << endl;
    
    BridgeScanner scanner;
    scanner.initialize();
    
    // 测试混合代码
    string mixedCode = R"(
        // 普通JavaScript
        function normalFunction() {
            return 42;
        }
        
        // CHTL增强部分
        @async function* fetchData() {
            const data = await* fetchMultiple([
                '/api/users',
                '/api/posts'
            ]);
            
            yield* data |> processResults;
        }
        
        // 又回到普通JavaScript
        class MyClass {
            constructor() {
                this.value = 0;
            }
        }
        
        // CHTL模式匹配
        @match(value) {
            case 0: return "zero";
            case 1..10: return "small";
            case _: return "large";
        }
    )";
    
    cout << "\nScanning mixed JavaScript/CHTL code..." << endl;
    auto result3 = scanner.scan(mixedCode, "mixed.js");
    cout << "Segments found: " << result3.segments.size() << endl;
    for (auto& seg : result3.segments) {
        printSegment(seg);
    }
}

void testValidation() {
    cout << "\n========== Test Validation ==========" << endl;
    
    BridgeScanner scanner;
    scanner.initialize();
    
    // 配置严格模式
    BridgeScanner::ScanConfig config;
    config.defaultMode = BridgeScanner::ScanMode::STRICT;
    scanner.setConfig(config);
    
    // 测试无效的CHTL代码（没有CHTL特性）
    string invalidChtl = R"(
        // 这看起来像普通JS，但我们声称它是CHTL
        function test() {
            return 1 + 1;
        }
    )";
    
    cout << "\nScanning invalid CHTL code (strict mode)..." << endl;
    auto result4 = scanner.scan(invalidChtl, "invalid.chtl.js");
    cout << "Success: " << (result4.success ? "Yes" : "No") << endl;
    cout << "Errors: " << result4.errors.size() << endl;
    
    // 测试括号不匹配的代码
    string unbalancedCode = R"(
        function test() {
            if (true) {
                console.log("missing closing brace");
            // } <- missing
    )";
    
    // 切换到宽松模式
    config.defaultMode = BridgeScanner::ScanMode::LENIENT;
    scanner.setConfig(config);
    
    cout << "\nScanning unbalanced code (lenient mode)..." << endl;
    auto result5 = scanner.scan(unbalancedCode, "unbalanced.js");
    cout << "Success: " << (result5.success ? "Yes" : "No") << endl;
}

int main() {
    cout << "===== BridgeScanner Test Suite =====" << endl;
    
    try {
        testBasicScanning();
        testChtlFeatures();
        testMixedCode();
        testValidation();
        
        cout << "\n===== All tests completed =====" << endl;
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}