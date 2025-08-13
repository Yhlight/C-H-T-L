#ifndef CHTL_TEST_FRAMEWORK_H
#define CHTL_TEST_FRAMEWORK_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <chrono>
#include <exception>

namespace chtl {
namespace test {

// 测试结果
struct TestResult {
    std::string name;
    bool passed;
    std::string message;
    double duration; // 毫秒
};

// 测试套件
class TestSuite {
public:
    TestSuite(const std::string& name) : name_(name) {}
    
    // 添加测试用例
    void addTest(const std::string& testName, std::function<void()> testFunc) {
        tests_.push_back({testName, testFunc});
    }
    
    // 运行所有测试
    std::vector<TestResult> run() {
        std::vector<TestResult> results;
        
        std::cout << "\n=== Running Test Suite: " << name_ << " ===\n";
        
        for (const auto& [testName, testFunc] : tests_) {
            auto start = std::chrono::high_resolution_clock::now();
            TestResult result{testName, true, "OK", 0.0};
            
            try {
                testFunc();
                std::cout << "[PASS] " << testName << std::endl;
            } catch (const std::exception& e) {
                result.passed = false;
                result.message = e.what();
                std::cout << "[FAIL] " << testName << ": " << e.what() << std::endl;
            } catch (...) {
                result.passed = false;
                result.message = "Unknown exception";
                std::cout << "[FAIL] " << testName << ": Unknown exception" << std::endl;
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            result.duration = std::chrono::duration<double, std::milli>(end - start).count();
            
            results.push_back(result);
        }
        
        // 统计
        int passed = 0, failed = 0;
        double totalTime = 0.0;
        
        for (const auto& result : results) {
            if (result.passed) passed++;
            else failed++;
            totalTime += result.duration;
        }
        
        std::cout << "\nSummary: " << passed << " passed, " << failed << " failed";
        std::cout << " (Total time: " << totalTime << " ms)\n";
        
        return results;
    }
    
private:
    std::string name_;
    std::vector<std::pair<std::string, std::function<void()>>> tests_;
};

// 断言宏
#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        throw std::runtime_error("Assertion failed: " #condition); \
    }

#define ASSERT_FALSE(condition) \
    if (condition) { \
        throw std::runtime_error("Assertion failed: !" #condition); \
    }

#define ASSERT_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        throw std::runtime_error("Assertion failed: " #expected " != " #actual); \
    }

#define ASSERT_NE(expected, actual) \
    if ((expected) == (actual)) { \
        throw std::runtime_error("Assertion failed: " #expected " == " #actual); \
    }

#define ASSERT_THROWS(expression, exception_type) \
    try { \
        expression; \
        throw std::runtime_error("Expected exception not thrown"); \
    } catch (const exception_type&) { \
        /* Expected */ \
    } catch (...) { \
        throw std::runtime_error("Wrong exception type thrown"); \
    }

#define ASSERT_NO_THROW(expression) \
    try { \
        expression; \
    } catch (...) { \
        throw std::runtime_error("Unexpected exception thrown"); \
    }

// 测试注册宏
#define TEST(suite_name, test_name) \
    void test_##suite_name##_##test_name(); \
    static struct test_##suite_name##_##test_name##_registrar { \
        test_##suite_name##_##test_name##_registrar() { \
            TestRegistry::getInstance().registerTest(#suite_name, #test_name, \
                test_##suite_name##_##test_name); \
        } \
    } test_##suite_name##_##test_name##_instance; \
    void test_##suite_name##_##test_name()

// 测试注册表
class TestRegistry {
public:
    static TestRegistry& getInstance() {
        static TestRegistry instance;
        return instance;
    }
    
    void registerTest(const std::string& suiteName, 
                     const std::string& testName,
                     std::function<void()> testFunc) {
        suites_[suiteName].addTest(testName, testFunc);
    }
    
    void runAll() {
        int totalPassed = 0, totalFailed = 0;
        
        for (auto& [suiteName, suite] : suites_) {
            auto results = suite.run();
            
            for (const auto& result : results) {
                if (result.passed) totalPassed++;
                else totalFailed++;
            }
        }
        
        std::cout << "\n=== Total: " << totalPassed << " passed, " 
                  << totalFailed << " failed ===\n";
        
        if (totalFailed > 0) {
            exit(1);
        }
    }
    
private:
    std::unordered_map<std::string, TestSuite> suites_;
};

} // namespace test
} // namespace chtl

// 主函数宏
#define RUN_ALL_TESTS() \
    int main() { \
        chtl::test::TestRegistry::getInstance().runAll(); \
        return 0; \
    }

#endif // CHTL_TEST_FRAMEWORK_H