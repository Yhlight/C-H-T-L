#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <chrono>
#include <filesystem>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Generator/WebGenerator.h"
#include "Context/ChtlContext.h"

namespace chtl {
namespace test {

// 测试结果
struct TestResult {
    std::string name;
    bool passed;
    std::string error;
    std::chrono::milliseconds duration;
};

// 测试套件
class TestSuite {
public:
    TestSuite(const std::string& name) : name_(name) {}
    
    // 添加测试用例
    void test(const std::string& testName, std::function<void()> testFunc) {
        tests_.emplace_back(testName, testFunc);
    }
    
    // 运行所有测试
    std::vector<TestResult> run() {
        std::vector<TestResult> results;
        
        std::cout << "\n[Suite] " << name_ << std::endl;
        
        for (const auto& [testName, testFunc] : tests_) {
            auto start = std::chrono::steady_clock::now();
            TestResult result{testName, true, "", {}};
            
            try {
                testFunc();
                std::cout << "  ✓ " << testName << std::endl;
            } catch (const std::exception& e) {
                result.passed = false;
                result.error = e.what();
                std::cout << "  ✗ " << testName << " - " << e.what() << std::endl;
            }
            
            auto end = std::chrono::steady_clock::now();
            result.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            
            results.push_back(result);
        }
        
        return results;
    }
    
private:
    std::string name_;
    std::vector<std::pair<std::string, std::function<void()>>> tests_;
};

// CHTL 专用断言
class Assert {
public:
    static void equals(const std::string& actual, const std::string& expected) {
        if (actual != expected) {
            throw std::runtime_error("Expected: " + expected + ", but got: " + actual);
        }
    }
    
    static void contains(const std::string& haystack, const std::string& needle) {
        if (haystack.find(needle) == std::string::npos) {
            throw std::runtime_error("String does not contain: " + needle);
        }
    }
    
    static void notContains(const std::string& haystack, const std::string& needle) {
        if (haystack.find(needle) != std::string::npos) {
            throw std::runtime_error("String should not contain: " + needle);
        }
    }
    
    static void isTrue(bool condition, const std::string& message = "") {
        if (!condition) {
            throw std::runtime_error(message.empty() ? "Condition is false" : message);
        }
    }
    
    static void isFalse(bool condition, const std::string& message = "") {
        if (condition) {
            throw std::runtime_error(message.empty() ? "Condition is true" : message);
        }
    }
    
    static void throws(std::function<void()> func, const std::string& expectedError = "") {
        bool thrown = false;
        try {
            func();
        } catch (const std::exception& e) {
            thrown = true;
            if (!expectedError.empty() && std::string(e.what()).find(expectedError) == std::string::npos) {
                throw std::runtime_error("Wrong error: " + std::string(e.what()));
            }
        }
        if (!thrown) {
            throw std::runtime_error("Expected exception was not thrown");
        }
    }
};

// CHTL 测试辅助类
class CHTLTestHelper {
public:
    // 编译 CHTL 代码并返回生成的结果
    static GenerationResult compile(const std::string& chtlCode) {
        auto context = std::make_shared<ChtlContext>();
        
        // 词法分析
        StandardLexer lexer(chtlCode, context);
        auto tokens = lexer.tokenize();
        
        // 语法分析
        StandardParser parser(tokens, context);
        auto ast = parser.parse();
        
        // 代码生成
        WebGenerator generator;
        generator.setContext(context);
        return generator.generate(ast);
    }
    
    // 验证 HTML 输出
    static void assertHTML(const std::string& chtlCode, const std::string& expectedHTML) {
        auto result = compile(chtlCode);
        std::string actualHTML = normalizeWhitespace(result.html);
        std::string expected = normalizeWhitespace(expectedHTML);
        Assert::equals(actualHTML, expected);
    }
    
    // 验证 CSS 输出
    static void assertCSS(const std::string& chtlCode, const std::string& expectedCSS) {
        auto result = compile(chtlCode);
        std::string actualCSS = normalizeWhitespace(result.css);
        std::string expected = normalizeWhitespace(expectedCSS);
        Assert::equals(actualCSS, expected);
    }
    
    // 验证 JavaScript 输出
    static void assertJS(const std::string& chtlCode, const std::string& expectedJS) {
        auto result = compile(chtlCode);
        Assert::contains(result.js, expectedJS);
    }
    
    // 验证编译错误
    static void assertCompileError(const std::string& chtlCode, const std::string& errorMessage) {
        Assert::throws([&]() { compile(chtlCode); }, errorMessage);
    }
    
private:
    // 规范化空白字符
    static std::string normalizeWhitespace(const std::string& str) {
        std::string result;
        bool inSpace = false;
        
        for (char c : str) {
            if (std::isspace(c)) {
                if (!inSpace) {
                    result += ' ';
                    inSpace = true;
                }
            } else {
                result += c;
                inSpace = false;
            }
        }
        
        // 去除首尾空白
        size_t start = result.find_first_not_of(" \t\n\r");
        size_t end = result.find_last_not_of(" \t\n\r");
        
        if (start != std::string::npos && end != std::string::npos) {
            return result.substr(start, end - start + 1);
        }
        
        return result;
    }
};

// 测试运行器
class TestRunner {
public:
    void addSuite(std::shared_ptr<TestSuite> suite) {
        suites_.push_back(suite);
    }
    
    void run() {
        std::cout << "\n========== CHTL Test Runner ==========" << std::endl;
        
        int totalTests = 0;
        int passedTests = 0;
        std::chrono::milliseconds totalDuration(0);
        
        for (auto& suite : suites_) {
            auto results = suite->run();
            
            for (const auto& result : results) {
                totalTests++;
                if (result.passed) passedTests++;
                totalDuration += result.duration;
            }
        }
        
        std::cout << "\n======================================" << std::endl;
        std::cout << "Total: " << totalTests << " tests" << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
        std::cout << "Duration: " << totalDuration.count() << "ms" << std::endl;
        
        if (passedTests < totalTests) {
            std::exit(1);
        }
    }
    
private:
    std::vector<std::shared_ptr<TestSuite>> suites_;
};

// 语法验证器
class SyntaxValidator {
public:
    static bool validate(const std::string& chtlCode) {
        try {
            CHTLTestHelper::compile(chtlCode);
            return true;
        } catch (...) {
            return false;
        }
    }
    
    static std::vector<std::string> getErrors(const std::string& chtlCode) {
        std::vector<std::string> errors;
        auto context = std::make_shared<ChtlContext>();
        
        try {
            StandardLexer lexer(chtlCode, context);
            auto tokens = lexer.tokenize();
            
            StandardParser parser(tokens, context);
            parser.parse();
        } catch (const std::exception& e) {
            errors.push_back(e.what());
        }
        
        // 添加上下文中的错误
        // TODO: 从 context 中获取详细错误信息
        
        return errors;
    }
};

// 性能测试
class PerformanceTest {
public:
    static void benchmark(const std::string& name, std::function<void()> func, int iterations = 1000) {
        std::cout << "\n[Benchmark] " << name << std::endl;
        
        // 预热
        for (int i = 0; i < 10; i++) {
            func();
        }
        
        // 实际测试
        auto start = std::chrono::steady_clock::now();
        
        for (int i = 0; i < iterations; i++) {
            func();
        }
        
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        double avgTime = static_cast<double>(duration.count()) / iterations;
        std::cout << "  Average time: " << avgTime << " μs" << std::endl;
        std::cout << "  Total time: " << duration.count() / 1000.0 << " ms" << std::endl;
        std::cout << "  Iterations: " << iterations << std::endl;
    }
};

} // namespace test
} // namespace chtl