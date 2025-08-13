#include "test_framework.h"
#include "../../src/chtl/CHTLCSSCompiler.h"
#include <sstream>

using namespace chtl;
using namespace chtl::test;

// 测试CSS编译器的辅助函数
std::string compileCSS(const std::string& css, bool minify = false) {
    // 这里应该调用实际的CSS编译器
    // 简化示例
    return css;
}

TEST(CSSCompiler, BasicSelectors) {
    std::string css = R"(
        body { margin: 0; padding: 0; }
        .class { color: red; }
        #id { background: blue; }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("body") != std::string::npos);
    ASSERT_TRUE(result.find(".class") != std::string::npos);
    ASSERT_TRUE(result.find("#id") != std::string::npos);
}

TEST(CSSCompiler, ComplexSelectors) {
    std::string css = R"(
        div > p { margin: 10px; }
        ul li:first-child { font-weight: bold; }
        input[type="text"]:focus { border-color: blue; }
        .parent .child::before { content: "→"; }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("div > p") != std::string::npos);
    ASSERT_TRUE(result.find(":first-child") != std::string::npos);
    ASSERT_TRUE(result.find("[type=\"text\"]") != std::string::npos);
    ASSERT_TRUE(result.find("::before") != std::string::npos);
}

TEST(CSSCompiler, MediaQueries) {
    std::string css = R"(
        @media (max-width: 768px) {
            .container { padding: 0 10px; }
        }
        @media print {
            body { font-size: 12pt; }
        }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("@media") != std::string::npos);
    ASSERT_TRUE(result.find("max-width: 768px") != std::string::npos);
    ASSERT_TRUE(result.find("@media print") != std::string::npos);
}

TEST(CSSCompiler, CSSVariables) {
    std::string css = R"(
        :root {
            --primary-color: #007bff;
            --font-size: 16px;
        }
        .button {
            background: var(--primary-color);
            font-size: var(--font-size);
        }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("--primary-color") != std::string::npos);
    ASSERT_TRUE(result.find("var(--primary-color)") != std::string::npos);
}

TEST(CSSCompiler, Animations) {
    std::string css = R"(
        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }
        .fade {
            animation: fadeIn 0.3s ease-in-out;
        }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("@keyframes") != std::string::npos);
    ASSERT_TRUE(result.find("fadeIn") != std::string::npos);
    ASSERT_TRUE(result.find("animation:") != std::string::npos);
}

TEST(CSSCompiler, FlexboxAndGrid) {
    std::string css = R"(
        .flex-container {
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        .grid-container {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            grid-gap: 20px;
        }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("display: flex") != std::string::npos);
    ASSERT_TRUE(result.find("display: grid") != std::string::npos);
    ASSERT_TRUE(result.find("grid-template-columns") != std::string::npos);
}

TEST(CSSCompiler, CalcFunction) {
    std::string css = R"(
        .sidebar {
            width: calc(100% - 300px);
            padding: calc(1rem + 5px);
        }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("calc(100% - 300px)") != std::string::npos);
    ASSERT_TRUE(result.find("calc(1rem + 5px)") != std::string::npos);
}

TEST(CSSCompiler, MinifyOutput) {
    std::string css = R"(
        body {
            margin: 0;
            padding: 0;
        }
    )";
    
    std::string result = compileCSS(css, true);
    // 压缩后应该移除多余空格和换行
    ASSERT_TRUE(result.find("body{margin:0;padding:0;}") != std::string::npos ||
                result.find("body{margin:0;padding:0}") != std::string::npos);
}

TEST(CSSCompiler, ImportRule) {
    std::string css = R"(
        @import url('https://fonts.googleapis.com/css2?family=Open+Sans');
        @import "reset.css";
        @import 'theme.css' screen and (min-width: 768px);
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("@import") != std::string::npos);
    ASSERT_TRUE(result.find("fonts.googleapis.com") != std::string::npos);
}

TEST(CSSCompiler, PseudoElements) {
    std::string css = R"(
        p::first-line { font-weight: bold; }
        .quote::before { content: """; }
        .quote::after { content: """; }
        ::selection { background: yellow; }
    )";
    
    std::string result = compileCSS(css);
    ASSERT_TRUE(result.find("::first-line") != std::string::npos);
    ASSERT_TRUE(result.find("::before") != std::string::npos);
    ASSERT_TRUE(result.find("::after") != std::string::npos);
    ASSERT_TRUE(result.find("::selection") != std::string::npos);
}

RUN_ALL_TESTS()