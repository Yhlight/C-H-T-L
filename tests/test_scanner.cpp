#include "../src/scanner/CodeScanner.h"
#include <iostream>
#include <cassert>

void testCodeScanner() {
    std::cout << "🧪 测试代码扫描器..." << std::endl;
    
    chtl::CodeScanner scanner;
    
    // 测试代码
    std::string testCode = R"(
html
{
    head
    {
        title
        {
            text
            {
                测试页面
            }
        }
    }
    
    body
    {
        style
        {
            .container
            {
                width: 100%;
                max-width: 800px;
                margin: 0 auto;
            }
        }
        
        div
        {
            class: container;
            text
            {
                这是一个测试
            }
        }
        
        script
        {
            console.log('Hello World');
        }
    }
}
)";
    
    // 扫描代码
    auto codeBlocks = scanner.scanCode(testCode);
    
    std::cout << "找到 " << codeBlocks.size() << " 个代码块:" << std::endl;
    
    for (size_t i = 0; i < codeBlocks.size(); i++) {
        const auto& block = codeBlocks[i];
        std::cout << "  代码块 " << (i + 1) << ":" << std::endl;
        std::cout << "    类型: " << static_cast<int>(block.type) << std::endl;
        std::cout << "    起始行: " << block.startLine << std::endl;
        std::cout << "    结束行: " << block.endLine << std::endl;
        std::cout << "    内容长度: " << block.content.length() << std::endl;
        std::cout << "    内容预览: " << block.content.substr(0, 50) << "..." << std::endl;
        std::cout << std::endl;
    }
    
    // 基本断言
    assert(!codeBlocks.empty());
    assert(codeBlocks.size() >= 1); // 至少应该有CHTL代码块
    
    std::cout << "✅ 代码扫描器测试通过!" << std::endl;
}

int main() {
    try {
        testCodeScanner();
        std::cout << "\n🎉 所有测试通过!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ 测试失败: " << e.what() << std::endl;
        return 1;
    }
}