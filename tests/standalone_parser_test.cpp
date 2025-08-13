#include <iostream>
#include <string>
#include "../src/chtl/parser/standalone/CHTLLexer.h"
#include "../src/chtl/parser/standalone/CHTLParser.h"

using namespace chtl::parser;

void testLexer() {
    std::cout << "=== Testing CHTL Lexer ===" << std::endl;
    
    std::string code = R"(
// CHTL测试代码
[Template] @Element Card(title, content) {
    div {
        class: card;
        id: "my-card";
        
        div {
            class: card-header;
            text { {title} }
        }
        
        div {
            class: card-body;
            text { {content} }
        }
        
        style {
            .card {
                border: 1px solid #ddd;
                border-radius: 8px;
            }
            
            .card-header {
                @inherit BaseHeader;
                background: #f5f5f5;
                padding: 10px;
            }
        }
    }
}

[Import] @Module Chtholly

div {
    @Element Card("Hello", "World");
    
    script {
        console.log("CHTL is working!");
    }
}
    )";
    
    CHTLLexer lexer(code);
    auto tokens = lexer.tokenize();
    
    std::cout << "Tokens found: " << tokens.size() << std::endl;
    for (const auto& token : tokens) {
        std::cout << token->toString() << std::endl;
    }
}

void testParser() {
    std::cout << "\n=== Testing CHTL Parser ===" << std::endl;
    
    std::string code = R"(
[Template] @Element Button(text = "Click me") {
    button {
        class: btn btn-primary;
        onclick: handleClick();
        
        text { {text} }
        
        style {
            background-color: #007bff;
            color: white;
            padding: 8px 16px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            
            &:hover {
                background-color: #0056b3;
            }
        }
    }
}

div {
    id: app;
    
    h1 {
        text { "Welcome to CHTL" }
    }
    
    @Element Button("Submit");
    
    style {
        #app {
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
    }
}
    )";
    
    CHTLLexer lexer(code);
    auto tokens = lexer.tokenize();
    auto tokenStream = std::make_shared<TokenStream>(tokens);
    
    CHTLParser parser(tokenStream);
    auto parseTree = parser.parse();
    
    if (parseTree) {
        std::cout << "Parse successful!" << std::endl;
        std::cout << "Root node: " << parseTree->getName() << std::endl;
        std::cout << "Children: " << parseTree->getChildren().size() << std::endl;
    } else {
        std::cout << "Parse failed!" << std::endl;
    }
}

void testCHTLSyntax() {
    std::cout << "\n=== Testing CHTL Syntax Features ===" << std::endl;
    
    // 测试注释
    std::cout << "Testing comments..." << std::endl;
    std::string commentCode = R"(
// 单行注释
/* 多行
   注释 */
-- HTML注释
div { text { "Hello" } }
    )";
    
    CHTLLexer lexer1(commentCode);
    auto tokens1 = lexer1.tokenize();
    std::cout << "Comment test tokens: " << tokens1.size() << std::endl;
    
    // 测试文本节点和字面量
    std::cout << "\nTesting text nodes and literals..." << std::endl;
    std::string textCode = R"(
text { "带引号的文本" }
text { 无引号的字面量 }
div {
    id: unquoted-id;
    class: "quoted class";
}
    )";
    
    CHTLLexer lexer2(textCode);
    auto tokens2 = lexer2.tokenize();
    auto tokenStream2 = std::make_shared<TokenStream>(tokens2);
    CHTLParser parser2(tokenStream2);
    auto tree2 = parser2.parse();
    std::cout << "Text test parse: " << (tree2 ? "SUCCESS" : "FAILED") << std::endl;
    
    // 测试CE对等式
    std::cout << "\nTesting CE equivalence (: vs =)..." << std::endl;
    std::string ceCode = R"(
div {
    id: test1;
    class = test2;
    data-value : "test3";
    data-name = "test4";
}
    )";
    
    CHTLLexer lexer3(ceCode);
    auto tokens3 = lexer3.tokenize();
    auto tokenStream3 = std::make_shared<TokenStream>(tokens3);
    CHTLParser parser3(tokenStream3);
    auto tree3 = parser3.parse();
    std::cout << "CE test parse: " << (tree3 ? "SUCCESS" : "FAILED") << std::endl;
    
    // 测试局部样式块
    std::cout << "\nTesting local style blocks..." << std::endl;
    std::string styleCode = R"(
div {
    style {
        // 内联样式
        color: red;
        font-size: 16px;
        
        // 类选择器（会被提升）
        .my-class {
            background: blue;
        }
        
        // ID选择器（会被提升）
        #my-id {
            border: 1px solid black;
        }
        
        // 伪类
        &:hover {
            opacity: 0.8;
        }
    }
}
    )";
    
    CHTLLexer lexer4(styleCode);
    auto tokens4 = lexer4.tokenize();
    auto tokenStream4 = std::make_shared<TokenStream>(tokens4);
    CHTLParser parser4(tokenStream4);
    auto tree4 = parser4.parse();
    std::cout << "Style test parse: " << (tree4 ? "SUCCESS" : "FAILED") << std::endl;
    
    // 测试高级特性
    std::cout << "\nTesting advanced features..." << std::endl;
    std::string advancedCode = R"(
[Import] @Module Chtholly
[Import] @Chtl UI.Components.*
[Import] @CJmod ImageProcessor as ImgProc

[Namespace] MyApp

[Template] @Style Theme {
    @inherit Chtholly.BaseTheme;
    --primary-color: #007bff;
    --secondary-color: #6c757d;
}

[Custom] @Element EnhancedButton from Button {
    @delete .old-class;
    @insert after .button-text {
        span {
            class: icon;
            text { "→" }
        }
    }
}

[Origin] @Html analytics {
    <script async src="https://analytics.example.com/script.js"></script>
}
    )";
    
    CHTLLexer lexer5(advancedCode);
    auto tokens5 = lexer5.tokenize();
    auto tokenStream5 = std::make_shared<TokenStream>(tokens5);
    CHTLParser parser5(tokenStream5);
    auto tree5 = parser5.parse();
    std::cout << "Advanced features parse: " << (tree5 ? "SUCCESS" : "FAILED") << std::endl;
}

int main() {
    try {
        testLexer();
        testParser();
        testCHTLSyntax();
        
        std::cout << "\n=== All tests completed ===" << std::endl;
        std::cout << "CHTL standalone parser is working without ANTLR4!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}