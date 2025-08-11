#include "../framework/CHTLTestFramework.cpp"

using namespace chtl::test;

// CJmod 响应式语法测试
auto cjmodReactiveTests = std::make_shared<TestSuite>("CJmod Reactive");

void setupCJmodReactiveTests() {
    cjmodReactiveTests->test("Reactive variable declaration", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:reactive";
            div {
                script {
                    count := 0;
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "let count = reactive(0);");
    });
    
    cjmodReactiveTests->test("Computed property", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:reactive";
            div {
                script {
                    count := 0;
                    doubled => count.value * 2;
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "let doubled = computed(() => count.value * 2);");
    });
    
    cjmodReactiveTests->test("Watch syntax", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:reactive";
            div {
                script {
                    count := 0;
                    watch count {
                        console.log("Changed");
                    }
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "watch(count, () => {");
        Assert::contains(result.js, "console.log(\"Changed\");");
    });
    
    cjmodReactiveTests->test("Reactive runtime injection", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:reactive";
            div { }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "window.reactive = function");
        Assert::contains(result.js, "window.computed = function");
        Assert::contains(result.js, "window.watch = function");
    });
}

// CJmod 动画语法测试
auto cjmodAnimationTests = std::make_shared<TestSuite>("CJmod Animation");

void setupCJmodAnimationTests() {
    cjmodAnimationTests->test("Animation chain syntax", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:animation";
            div {
                script {
                    {{#box}} ~> fadeIn;
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "document.getElementById('box').animate().fadeIn");
    });
    
    cjmodAnimationTests->test("Delay function", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:animation";
            div {
                script {
                    delay(1000);
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "await new Promise(r => setTimeout(r, 1000))");
    });
}

// CJmod 管道操作符测试
auto cjmodPipelineTests = std::make_shared<TestSuite>("CJmod Pipeline");

void setupCJmodPipelineTests() {
    cjmodPipelineTests->test("Basic pipe operator", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:pipeline";
            div {
                script {
                    result = value |> transform |> format;
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "pipe(");
    });
    
    cjmodPipelineTests->test("Array map pipe", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:pipeline";
            div {
                script {
                    result = array |>> double |>> square;
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        Assert::contains(result.js, "mapPipe(");
    });
}

// CJmod 模块加载测试
auto cjmodLoaderTests = std::make_shared<TestSuite>("CJmod Loader");

void setupCJmodLoaderTests() {
    cjmodLoaderTests->test("Multiple CJmod imports", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:reactive";
            [Import] @CJmod from "builtin:animation";
            div { }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        // 两个模块的运行时都应该被注入
        Assert::contains(result.js, "window.reactive");
        Assert::contains(result.js, "window.animate");
    });
    
    cjmodLoaderTests->test("CJmod path resolution", []() {
        // 测试不同的导入路径格式
        std::vector<std::string> validPaths = {
            "builtin:reactive",
            "./modules/custom.cjmod",
            "../shared/utils.cjmod"
        };
        
        for (const auto& path : validPaths) {
            auto code = "[Import] @CJmod from \"" + path + "\";\ndiv { }";
            // 应该能正常解析，不抛出异常
            CHTLTestHelper::compile(code);
        }
    });
}

// CJmod 语法优先级测试
auto cjmodPriorityTests = std::make_shared<TestSuite>("CJmod Priority");

void setupCJmodPriorityTests() {
    cjmodPriorityTests->test("Rule priority order", []() {
        auto code = R"(
            [Import] @CJmod from "builtin:reactive";
            div {
                script {
                    // 测试优先级：reactive 声明应该先于其他转换
                    count := {{#counter}}.value;
                }
            }
        )";
        
        auto result = CHTLTestHelper::compile(code);
        // reactive 转换应该先执行
        Assert::contains(result.js, "let count = reactive(document.getElementById('counter').value);");
    });
}

// CJmod 语法验证测试
auto cjmodValidationTests = std::make_shared<TestSuite>("CJmod Validation");

void setupCJmodValidationTests() {
    cjmodValidationTests->test("Valid reactive syntax", []() {
        Assert::isTrue(SyntaxValidator::validate(R"(
            [Import] @CJmod from "builtin:reactive";
            div {
                script {
                    count := 0;
                    doubled => count.value * 2;
                    watch count { }
                }
            }
        )"));
    });
    
    cjmodValidationTests->test("Invalid CJmod import", []() {
        auto errors = SyntaxValidator::getErrors(R"(
            [Import] @CJmod from;
            div { }
        )");
        
        Assert::isFalse(errors.empty(), "Should have parsing errors");
    });
}

// CJmod 性能测试
void runCJmodPerformanceTests() {
    std::cout << "\n========== CJmod Performance Tests ==========" << std::endl;
    
    PerformanceTest::benchmark("CJmod reactive compilation", []() {
        CHTLTestHelper::compile(R"(
            [Import] @CJmod from "builtin:reactive";
            div {
                script {
                    count := 0;
                    doubled => count.value * 2;
                    tripled => count.value * 3;
                    
                    watch count {
                        console.log("Count:", count.value);
                        console.log("Doubled:", doubled.value);
                        console.log("Tripled:", tripled.value);
                    }
                }
            }
        )");
    }, 100);
    
    PerformanceTest::benchmark("Multiple CJmod syntax transformations", []() {
        CHTLTestHelper::compile(R"(
            [Import] @CJmod from "builtin:reactive";
            [Import] @CJmod from "builtin:animation";
            [Import] @CJmod from "builtin:pipeline";
            
            div {
                script {
                    // Reactive
                    items := [];
                    filtered => items.value.filter(x => x > 0);
                    
                    // Pipeline
                    result = items |> filter |> map |> reduce;
                    
                    // Animation
                    {{#list}} ~> fadeIn ~> slideDown;
                    
                    // Mixed
                    watch filtered {
                        {{#display}} ~> update;
                        delay(100);
                    }
                }
            }
        )");
    }, 50);
}

// 主测试函数
int main() {
    // 设置测试
    setupCJmodReactiveTests();
    setupCJmodAnimationTests();
    setupCJmodPipelineTests();
    setupCJmodLoaderTests();
    setupCJmodPriorityTests();
    setupCJmodValidationTests();
    
    // 创建测试运行器
    TestRunner runner;
    runner.addSuite(cjmodReactiveTests);
    runner.addSuite(cjmodAnimationTests);
    runner.addSuite(cjmodPipelineTests);
    runner.addSuite(cjmodLoaderTests);
    runner.addSuite(cjmodPriorityTests);
    runner.addSuite(cjmodValidationTests);
    
    // 运行所有测试
    runner.run();
    
    // 运行性能测试
    runCJmodPerformanceTests();
    
    return 0;
}