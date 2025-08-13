#include "../src/chtl/CHTLCompiler.h"
#include <iostream>
#include <cassert>
#include <string>

void testBasicHTMLElements() {
    std::cout << "🧪 测试基本HTML元素..." << std::endl;
    
    chtl::CHTLCompiler compiler;
    
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
        div
        {
            text
            {
                这是一个测试div
            }
        }
        
        p
        {
            text
            {
                这是一个段落
            }
        }
    }
}
)";
    
    bool success = compiler.compile(testCode);
    assert(success);
    
    std::string html = compiler.getHTML();
    std::cout << "生成的HTML:" << std::endl << html << std::endl;
    
    // 验证HTML输出
    assert(html.find("<html>") != std::string::npos);
    assert(html.find("<head>") != std::string::npos);
    assert(html.find("<title>") != std::string::npos);
    assert(html.find("<body>") != std::string::npos);
    assert(html.find("<div>") != std::string::npos);
    assert(html.find("<p>") != std::string::npos);
    assert(html.find("测试页面") != std::string::npos);
    assert(html.find("这是一个测试div") != std::string::npos);
    assert(html.find("这是一个段落") != std::string::npos);
    
    std::cout << "✅ 基本HTML元素测试通过!" << std::endl;
}

void testTextBlocks() {
    std::cout << "🧪 测试text文本块..." << std::endl;
    
    chtl::CHTLCompiler compiler;
    
    std::string testCode = R"(
div
{
    text
    {
        这是第一行文本
        这是第二行文本
        这是第三行文本
    }
}
)";
    
    bool success = compiler.compile(testCode);
    assert(success);
    
    std::string html = compiler.getHTML();
    std::cout << "生成的HTML:" << std::endl << html << std::endl;
    
    // 验证文本块输出
    assert(html.find("这是第一行文本") != std::string::npos);
    assert(html.find("这是第二行文本") != std::string::npos);
    assert(html.find("这是第三行文本") != std::string::npos);
    
    std::cout << "✅ text文本块测试通过!" << std::endl;
}

void testLocalStyleBlocks() {
    std::cout << "🧪 测试局部样式块..." << std::endl;
    
    chtl::CHTLCompiler compiler;
    
    std::string testCode = R"(
div
{
    id: container;
    class: main;
    
    style
    {
        .main
        {
            width: 100%;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
        
        &:hover
        {
            background-color: #f0f0f0;
        }
    }
    
    text
    {
        带样式的div
    }
}
)";
    
    bool success = compiler.compile(testCode);
    assert(success);
    
    std::string html = compiler.getHTML();
    std::string css = compiler.getCSS();
    
    std::cout << "生成的HTML:" << std::endl << html << std::endl;
    std::cout << "生成的CSS:" << std::endl << css << std::endl;
    
    // 验证HTML输出
    assert(html.find("<div") != std::string::npos);
    assert(html.find("带样式的div") != std::string::npos);
    
    // 验证CSS输出
    assert(css.find(".main") != std::string::npos);
    assert(css.find("width: 100%") != std::string::npos);
    assert(css.find("max-width: 800px") != std::string::npos);
    assert(css.find("margin: 0 auto") != std::string::npos);
    assert(css.find("padding: 20px") != std::string::npos);
    
    std::cout << "✅ 局部样式块测试通过!" << std::endl;
}

void testContextDerivation() {
    std::cout << "🧪 测试上下文推导..." << std::endl;
    
    chtl::CHTLCompiler compiler;
    
    std::string testCode = R"(
div
{
    class: button;
    
    style
    {
        .button
        {
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        
        &:hover
        {
            background-color: #e0e0e0;
        }
        
        &:active
        {
            transform: scale(0.95);
        }
    }
    
    text
    {
        按钮
    }
}
)";
    
    bool success = compiler.compile(testCode);
    assert(success);
    
    std::string css = compiler.getCSS();
    std::cout << "生成的CSS:" << std::endl << css << std::endl;
    
    // 验证上下文推导
    assert(css.find(".button") != std::string::npos);
    assert(css.find(".button:hover") != std::string::npos);
    assert(css.find(".button:active") != std::string::npos);
    
    std::cout << "✅ 上下文推导测试通过!" << std::endl;
}

void testAttributes() {
    std::cout << "🧪 测试属性处理..." << std::endl;
    
    chtl::CHTLCompiler compiler;
    
    std::string testCode = R"(
div
{
    id: main;
    class: container;
    data-type: section;
    
    text
    {
        带属性的div
    }
}
)";
    
    bool success = compiler.compile(testCode);
    assert(success);
    
    std::string html = compiler.getHTML();
    std::cout << "生成的HTML:" << std::endl << html << std::endl;
    
    // 验证属性输出
    assert(html.find("<div") != std::string::npos);
    assert(html.find("带属性的div") != std::string::npos);
    
    std::cout << "✅ 属性处理测试通过!" << std::endl;
}

void testTemplates() {
    std::cout << "🧪 测试模板..." << std::endl;
    
    chtl::CHTLCompiler compiler;
    
    std::string testCode = R"(
[Template] @Style Button
{
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    background-color: #007bff;
    color: white;
}

[Template] @Element Card
{
    div
    {
        class: card;
        
        style
        {
            @Style Button;
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 20px;
            margin: 10px;
        }
        
        text
        {
            卡片内容
        }
    }
}

body
{
    @Element Card;
}
)";
    
    bool success = compiler.compile(testCode);
    assert(success);
    
    std::string html = compiler.getHTML();
    std::string css = compiler.getCSS();
    
    std::cout << "生成的HTML:" << std::endl << html << std::endl;
    std::cout << "生成的CSS:" << std::endl << css << std::endl;
    
    // 验证模板输出
    assert(html.find("卡片内容") != std::string::npos);
    assert(css.find(".card") != std::string::npos);
    
    std::cout << "✅ 模板测试通过!" << std::endl;
}

void testScriptBlocks() {
    std::cout << "🧪 测试脚本块..." << std::endl;
    
    chtl::CHTLCompiler compiler;
    
    std::string testCode = R"(
div
{
    id: button;
    
    text
    {
        点击我
    }
    
    script
    {
        document.getElementById('button').addEventListener('click', function() {
            alert('按钮被点击了!');
        });
    }
}
)";
    
    bool success = compiler.compile(testCode);
    assert(success);
    
    std::string html = compiler.getHTML();
    std::string js = compiler.getJavaScript();
    
    std::cout << "生成的HTML:" << std::endl << html << std::endl;
    std::cout << "生成的JavaScript:" << std::endl << js << std::endl;
    
    // 验证脚本块输出
    assert(html.find("点击我") != std::string::npos);
    assert(js.find("addEventListener") != std::string::npos);
    assert(js.find("alert") != std::string::npos);
    
    std::cout << "✅ 脚本块测试通过!" << std::endl;
}

int main() {
    try {
        std::cout << "🚀 开始CHTL编译器测试..." << std::endl;
        
        testBasicHTMLElements();
        testTextBlocks();
        testLocalStyleBlocks();
        testContextDerivation();
        testAttributes();
        testTemplates();
        testScriptBlocks();
        
        std::cout << "\n🎉 所有测试通过!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ 测试失败: " << e.what() << std::endl;
        return 1;
    }
}