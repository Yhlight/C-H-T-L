#include "../framework/CHTLTestFramework.cpp"

using namespace chtl::test;

// 基本元素测试
auto basicElementTests = std::make_shared<TestSuite>("Basic Elements");

void setupBasicElementTests() {
    basicElementTests->test("Simple div element", []() {
        CHTLTestHelper::assertHTML(
            "div { \"Hello World\" }",
            "<div>Hello World</div>"
        );
    });
    
    basicElementTests->test("Element with ID", []() {
        CHTLTestHelper::assertHTML(
            "div #myDiv { \"Content\" }",
            "<div id=\"myDiv\">Content</div>"
        );
    });
    
    basicElementTests->test("Element with class", []() {
        CHTLTestHelper::assertHTML(
            "div .container { \"Content\" }",
            "<div class=\"container\">Content</div>"
        );
    });
    
    basicElementTests->test("Element with ID and class", []() {
        CHTLTestHelper::assertHTML(
            "div #myDiv .container { \"Content\" }",
            "<div id=\"myDiv\" class=\"container\">Content</div>"
        );
    });
    
    basicElementTests->test("Nested elements", []() {
        CHTLTestHelper::assertHTML(
            "div { p { \"Nested\" } }",
            "<div><p>Nested</p></div>"
        );
    });
    
    basicElementTests->test("Multiple children", []() {
        CHTLTestHelper::assertHTML(
            "div { h1 { \"Title\" } p { \"Text\" } }",
            "<div><h1>Title</h1><p>Text</p></div>"
        );
    });
}

// 属性测试
auto attributeTests = std::make_shared<TestSuite>("Attributes");

void setupAttributeTests() {
    attributeTests->test("Single attribute", []() {
        CHTLTestHelper::assertHTML(
            "a { href: \"https://example.com\" \"Link\" }",
            "<a href=\"https://example.com\">Link</a>"
        );
    });
    
    attributeTests->test("Multiple attributes", []() {
        CHTLTestHelper::assertHTML(
            "img { src: \"image.jpg\" alt: \"Description\" }",
            "<img src=\"image.jpg\" alt=\"Description\">"
        );
    });
    
    attributeTests->test("Boolean attributes", []() {
        CHTLTestHelper::assertHTML(
            "input { type: \"checkbox\" checked: \"true\" }",
            "<input type=\"checkbox\" checked=\"true\">"
        );
    });
}

// 样式测试
auto styleTests = std::make_shared<TestSuite>("Styles");

void setupStyleTests() {
    styleTests->test("Inline styles", []() {
        auto result = CHTLTestHelper::compile(
            "div { style { color: red; padding: 10px; } }"
        );
        Assert::contains(result.html, "style=");
        Assert::contains(result.html, "color: red");
        Assert::contains(result.html, "padding: 10px");
    });
    
    styleTests->test("Global style block", []() {
        CHTLTestHelper::assertCSS(
            "[Style] { .container { width: 100%; } }",
            ".container { width: 100%; }"
        );
    });
}

// 脚本测试
auto scriptTests = std::make_shared<TestSuite>("Scripts");

void setupScriptTests() {
    scriptTests->test("Basic script block", []() {
        CHTLTestHelper::assertJS(
            "div { script { console.log(\"Hello\"); } }",
            "console.log(\"Hello\");"
        );
    });
    
    scriptTests->test("CHTL JS syntax - self reference", []() {
        CHTLTestHelper::assertJS(
            "div { script { {{&}}.style.color = \"red\"; } }",
            "this.style.color = \"red\";"
        );
    });
    
    scriptTests->test("CHTL JS syntax - ID selector", []() {
        CHTLTestHelper::assertJS(
            "div { script { {{#myDiv}}.innerHTML = \"Test\"; } }",
            "document.getElementById('myDiv').innerHTML = \"Test\";"
        );
    });
    
    scriptTests->test("CHTL JS syntax - class selector", []() {
        CHTLTestHelper::assertJS(
            "div { script { {{.active}}.forEach(el => el.classList.add(\"highlight\")); } }",
            "document.getElementsByClassName('active')"
        );
    });
    
    scriptTests->test("CHTL JS syntax - arrow method", []() {
        CHTLTestHelper::assertJS(
            "div { script { element->addEventListener(\"click\", handler); } }",
            "element.addEventListener(\"click\", handler);"
        );
    });
}

// 组件测试
auto componentTests = std::make_shared<TestSuite>("Components");

void setupComponentTests() {
    componentTests->test("Template component definition", []() {
        auto code = R"(
            [Template] @Element Button {
                button { "Click me" }
            }
            div { @Template Button }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.html, "<button>Click me</button>");
    });
    
    componentTests->test("Custom component definition", []() {
        auto code = R"(
            [Custom] @Element Counter {
                div {
                    span { "Count: 0" }
                    button { "+" }
                }
            }
            div { @Custom Counter }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.html, "Count: 0");
        Assert::contains(result.html, "<button>+</button>");
    });
}

// 导入测试
auto importTests = std::make_shared<TestSuite>("Imports");

void setupImportTests() {
    importTests->test("Import syntax parsing", []() {
        // 测试导入语法是否正确解析（不执行实际导入）
        auto code = R"(
            [Import] @Chtl from "./components.chtl";
            div { "Content" }
        )";
        
        // 应该能正常编译，不抛出异常
        CHTLTestHelper::compile(code);
    });
    
    importTests->test("CJmod import syntax", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:reactive";
            div { "Content" }
        )";
        
        CHTLTestHelper::compile(code);
    });
}

// 错误处理测试
auto errorTests = std::make_shared<TestSuite>("Error Handling");

void setupErrorTests() {
    errorTests->test("Unclosed element", []() {
        CHTLTestHelper::assertCompileError(
            "div { p { \"Unclosed\"",
            "Expected"
        );
    });
    
    errorTests->test("Invalid syntax", []() {
        CHTLTestHelper::assertCompileError(
            "div {{ }}",
            ""
        );
    });
    
    errorTests->test("Missing quotes in attribute", []() {
        CHTLTestHelper::assertCompileError(
            "div { class: unquoted }",
            ""
        );
    });
}

// 性能测试
void runPerformanceTests() {
    std::cout << "\n========== Performance Tests ==========" << std::endl;
    
    PerformanceTest::benchmark("Simple element compilation", []() {
        CHTLTestHelper::compile("div { \"Hello\" }");
    }, 1000);
    
    PerformanceTest::benchmark("Complex nested structure", []() {
        CHTLTestHelper::compile(R"(
            div .container {
                header {
                    h1 { "Title" }
                    nav {
                        ul {
                            li { a { href: "#" "Home" } }
                            li { a { href: "#" "About" } }
                            li { a { href: "#" "Contact" } }
                        }
                    }
                }
                main {
                    section {
                        h2 { "Content" }
                        p { "Lorem ipsum..." }
                    }
                }
                footer {
                    p { "Copyright 2024" }
                }
            }
        )");
    }, 100);
    
    PerformanceTest::benchmark("Large file with styles and scripts", []() {
        std::string largeFile = "[Style] { body { margin: 0; } }\n";
        for (int i = 0; i < 50; i++) {
            largeFile += "div { p { \"Paragraph " + std::to_string(i) + "\" } }\n";
        }
        CHTLTestHelper::compile(largeFile);
    }, 10);
}

// 主测试函数
int main() {
    // 设置测试
    setupBasicElementTests();
    setupAttributeTests();
    setupStyleTests();
    setupScriptTests();
    setupComponentTests();
    setupImportTests();
    setupErrorTests();
    
    // 创建测试运行器
    TestRunner runner;
    runner.addSuite(basicElementTests);
    runner.addSuite(attributeTests);
    runner.addSuite(styleTests);
    runner.addSuite(scriptTests);
    runner.addSuite(componentTests);
    runner.addSuite(importTests);
    runner.addSuite(errorTests);
    
    // 运行所有测试
    runner.run();
    
    // 运行性能测试
    runPerformanceTests();
    
    return 0;
}