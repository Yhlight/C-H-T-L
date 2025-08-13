# CJMOD开发完整指南

## 目录

1. [概述](#概述)
2. [快速开始](#快速开始)
3. [项目结构](#项目结构)
4. [开发流程](#开发流程)
5. [API设计](#api设计)
6. [内存管理](#内存管理)
7. [错误处理](#错误处理)
8. [性能优化](#性能优化)
9. [调试技巧](#调试技巧)
10. [发布流程](#发布流程)
11. [最佳实践](#最佳实践)
12. [常见问题](#常见问题)

## 概述

CJMOD（CHTL JavaScript Module）是CHTL的C++扩展模块系统，允许开发者使用C++创建高性能的功能扩展，这些扩展可以在CHTL的JavaScript环境中直接调用。

### 特点

- **高性能**：原生C++实现，性能远超纯JavaScript
- **类型安全**：C++强类型系统保证代码质量
- **无缝集成**：自动生成JavaScript绑定
- **跨平台**：支持Windows、Linux、macOS
- **热加载**：支持动态加载和卸载

## 快速开始

### 1. 创建新的CJMOD项目

```bash
# 创建项目目录
mkdir my-cjmod && cd my-cjmod

# 创建标准目录结构
mkdir -p src include info

# 创建模块信息文件
cat > info/module.info << EOF
name = MyCJMOD
version = 1.0.0
author = Your Name
description = My awesome CJMOD extension
type = cjmod
license = MIT
min_chtl_version = 1.0.0
EOF
```

### 2. 编写C++代码

创建头文件 `include/my_cjmod.h`：

```cpp
#ifndef MY_CJMOD_H
#define MY_CJMOD_H

#include <string>
#include <vector>

#ifdef _WIN32
    #define CJMOD_EXPORT __declspec(dllexport)
#else
    #define CJMOD_EXPORT __attribute__((visibility("default")))
#endif

namespace my_cjmod {

// 示例类：计算器
class Calculator {
public:
    double add(double a, double b);
    double multiply(double a, double b);
    double power(double base, double exponent);
};

// 示例：字符串工具
class StringUtils {
public:
    std::string reverse(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string join(const std::vector<std::string>& parts, const std::string& delimiter);
};

} // namespace my_cjmod

// C接口 - 供CHTL调用
extern "C" {
    CJMOD_EXPORT void cjmod_init();
    CJMOD_EXPORT void cjmod_cleanup();
    
    // Calculator接口
    CJMOD_EXPORT void* calculator_create();
    CJMOD_EXPORT void calculator_destroy(void* calc);
    CJMOD_EXPORT double calculator_add(void* calc, double a, double b);
    CJMOD_EXPORT double calculator_multiply(void* calc, double a, double b);
    CJMOD_EXPORT double calculator_power(void* calc, double base, double exp);
    
    // StringUtils接口
    CJMOD_EXPORT void* string_utils_create();
    CJMOD_EXPORT void string_utils_destroy(void* utils);
    CJMOD_EXPORT const char* string_utils_reverse(void* utils, const char* str);
    CJMOD_EXPORT const char** string_utils_split(void* utils, const char* str, char delim, int* count);
    CJMOD_EXPORT const char* string_utils_join(void* utils, const char** parts, int count, const char* delim);
}

#endif // MY_CJMOD_H
```

创建实现文件 `src/my_cjmod.cpp`：

```cpp
#include "../include/my_cjmod.h"
#include <algorithm>
#include <cmath>
#include <sstream>
#include <cstring>

namespace my_cjmod {

// Calculator实现
double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::power(double base, double exponent) {
    return std::pow(base, exponent);
}

// StringUtils实现
std::string StringUtils::reverse(const std::string& str) {
    std::string result = str;
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<std::string> StringUtils::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string StringUtils::join(const std::vector<std::string>& parts, const std::string& delimiter) {
    if (parts.empty()) return "";
    
    std::string result = parts[0];
    for (size_t i = 1; i < parts.size(); ++i) {
        result += delimiter + parts[i];
    }
    
    return result;
}

} // namespace my_cjmod

// C接口实现
extern "C" {

// 用于存储返回的字符串
static thread_local std::string g_return_buffer;
static thread_local std::vector<std::string> g_split_result;
static thread_local std::vector<const char*> g_split_ptrs;

CJMOD_EXPORT void cjmod_init() {
    // 初始化代码
}

CJMOD_EXPORT void cjmod_cleanup() {
    // 清理代码
}

// Calculator接口
CJMOD_EXPORT void* calculator_create() {
    return new my_cjmod::Calculator();
}

CJMOD_EXPORT void calculator_destroy(void* calc) {
    delete static_cast<my_cjmod::Calculator*>(calc);
}

CJMOD_EXPORT double calculator_add(void* calc, double a, double b) {
    auto* calculator = static_cast<my_cjmod::Calculator*>(calc);
    return calculator->add(a, b);
}

CJMOD_EXPORT double calculator_multiply(void* calc, double a, double b) {
    auto* calculator = static_cast<my_cjmod::Calculator*>(calc);
    return calculator->multiply(a, b);
}

CJMOD_EXPORT double calculator_power(void* calc, double base, double exp) {
    auto* calculator = static_cast<my_cjmod::Calculator*>(calc);
    return calculator->power(base, exp);
}

// StringUtils接口
CJMOD_EXPORT void* string_utils_create() {
    return new my_cjmod::StringUtils();
}

CJMOD_EXPORT void string_utils_destroy(void* utils) {
    delete static_cast<my_cjmod::StringUtils*>(utils);
}

CJMOD_EXPORT const char* string_utils_reverse(void* utils, const char* str) {
    auto* string_utils = static_cast<my_cjmod::StringUtils*>(utils);
    g_return_buffer = string_utils->reverse(str);
    return g_return_buffer.c_str();
}

CJMOD_EXPORT const char** string_utils_split(void* utils, const char* str, char delim, int* count) {
    auto* string_utils = static_cast<my_cjmod::StringUtils*>(utils);
    g_split_result = string_utils->split(str, delim);
    
    g_split_ptrs.clear();
    for (const auto& s : g_split_result) {
        g_split_ptrs.push_back(s.c_str());
    }
    
    *count = static_cast<int>(g_split_ptrs.size());
    return g_split_ptrs.data();
}

CJMOD_EXPORT const char* string_utils_join(void* utils, const char** parts, int count, const char* delim) {
    auto* string_utils = static_cast<my_cjmod::StringUtils*>(utils);
    
    std::vector<std::string> vec;
    for (int i = 0; i < count; ++i) {
        vec.push_back(parts[i]);
    }
    
    g_return_buffer = string_utils->join(vec, delim);
    return g_return_buffer.c_str();
}

} // extern "C"
```

### 3. 创建CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyCJMOD VERSION 1.0.0 LANGUAGES CXX)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 源文件
set(SOURCES
    src/my_cjmod.cpp
)

# 创建共享库
add_library(my_cjmod SHARED ${SOURCES})

# 包含目录
target_include_directories(my_cjmod PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 设置属性
set_target_properties(my_cjmod PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/my_cjmod.h
)

# 导出符号
if(WIN32)
    set_target_properties(my_cjmod PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif()

# 安装规则
install(TARGETS my_cjmod
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

# 复制module.info
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/info/module.info"
    "${CMAKE_CURRENT_BINARY_DIR}/module.info"
    COPYONLY
)
```

### 4. 构建CJMOD

```bash
# 创建构建目录
mkdir build && cd build

# 配置
cmake ..

# 构建
cmake --build . --config Release

# 打包
cd ..
chtl --pack-cjmod .
```

## 项目结构

标准的CJMOD项目结构：

```
my-cjmod/
├── CMakeLists.txt          # CMake构建文件
├── info/
│   └── module.info         # 模块元数据
├── include/
│   └── my_cjmod.h         # 公共头文件
├── src/
│   ├── my_cjmod.cpp       # 主实现文件
│   └── ...                # 其他源文件
├── tests/
│   └── test_my_cjmod.cpp  # 单元测试
├── examples/
│   └── example.chtl       # 使用示例
└── README.md              # 文档
```

## 开发流程

### 1. 设计API

设计原则：
- **简单直观**：API应该易于理解和使用
- **类型安全**：充分利用C++类型系统
- **错误友好**：提供清晰的错误信息
- **向后兼容**：谨慎修改公共API

### 2. 实现功能

```cpp
// 良好的实现示例
class ImageProcessor {
private:
    struct Impl; // PIMPL模式
    std::unique_ptr<Impl> pImpl;
    
public:
    ImageProcessor();
    ~ImageProcessor();
    
    // 禁用拷贝
    ImageProcessor(const ImageProcessor&) = delete;
    ImageProcessor& operator=(const ImageProcessor&) = delete;
    
    // 启用移动
    ImageProcessor(ImageProcessor&&) = default;
    ImageProcessor& operator=(ImageProcessor&&) = default;
    
    // 公共接口
    bool loadImage(const std::string& path);
    bool saveImage(const std::string& path);
    void resize(int width, int height);
    void applyFilter(const std::string& filterName);
};
```

### 3. 导出C接口

```cpp
extern "C" {
    // 创建/销毁
    CJMOD_EXPORT void* image_processor_create() {
        try {
            return new ImageProcessor();
        } catch (...) {
            return nullptr;
        }
    }
    
    CJMOD_EXPORT void image_processor_destroy(void* processor) {
        delete static_cast<ImageProcessor*>(processor);
    }
    
    // 功能接口
    CJMOD_EXPORT int image_processor_load(void* processor, const char* path) {
        try {
            auto* p = static_cast<ImageProcessor*>(processor);
            return p->loadImage(path) ? 1 : 0;
        } catch (...) {
            return 0;
        }
    }
}
```

### 4. 创建JavaScript绑定

创建 `bindings/my_cjmod.js`：

```javascript
// 自动生成的JavaScript绑定
const MyCJMOD = {
    Calculator: class {
        constructor() {
            this._handle = __cjmod_calculator_create();
        }
        
        destroy() {
            if (this._handle) {
                __cjmod_calculator_destroy(this._handle);
                this._handle = null;
            }
        }
        
        add(a, b) {
            return __cjmod_calculator_add(this._handle, a, b);
        }
        
        multiply(a, b) {
            return __cjmod_calculator_multiply(this._handle, a, b);
        }
        
        power(base, exponent) {
            return __cjmod_calculator_power(this._handle, base, exponent);
        }
    },
    
    StringUtils: class {
        constructor() {
            this._handle = __cjmod_string_utils_create();
        }
        
        destroy() {
            if (this._handle) {
                __cjmod_string_utils_destroy(this._handle);
                this._handle = null;
            }
        }
        
        reverse(str) {
            return __cjmod_string_utils_reverse(this._handle, str);
        }
        
        split(str, delimiter) {
            return __cjmod_string_utils_split(this._handle, str, delimiter);
        }
        
        join(parts, delimiter) {
            return __cjmod_string_utils_join(this._handle, parts, delimiter);
        }
    }
};

// 导出
if (typeof module !== 'undefined' && module.exports) {
    module.exports = MyCJMOD;
}
```

## API设计

### 基本原则

1. **使用PIMPL模式**隐藏实现细节
2. **提供RAII包装器**自动管理资源
3. **使用智能指针**避免内存泄漏
4. **异常安全**保证强异常安全性

### 推荐的API模式

```cpp
// 1. 工厂模式
class ModuleFactory {
public:
    static std::unique_ptr<IModule> create(const std::string& type);
};

// 2. 建造者模式
class ConfigBuilder {
public:
    ConfigBuilder& setOption(const std::string& key, const std::string& value);
    ConfigBuilder& enableFeature(const std::string& feature);
    std::unique_ptr<Config> build();
};

// 3. 观察者模式
class EventEmitter {
public:
    void on(const std::string& event, std::function<void(const Event&)> handler);
    void emit(const std::string& event, const Event& data);
};
```

## 内存管理

### 基本规则

1. **谁分配谁释放**：同一模块负责分配和释放
2. **使用智能指针**：优先使用`unique_ptr`和`shared_ptr`
3. **避免裸指针**：除非与C接口交互
4. **提供清理函数**：确保资源能被正确释放

### 内存池实现

```cpp
template<typename T>
class ObjectPool {
private:
    std::stack<std::unique_ptr<T>> pool_;
    std::mutex mutex_;
    
public:
    std::unique_ptr<T> acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        if (pool_.empty()) {
            return std::make_unique<T>();
        }
        
        auto obj = std::move(pool_.top());
        pool_.pop();
        return obj;
    }
    
    void release(std::unique_ptr<T> obj) {
        std::lock_guard<std::mutex> lock(mutex_);
        obj->reset(); // 重置对象状态
        pool_.push(std::move(obj));
    }
};
```

## 错误处理

### 错误码设计

```cpp
enum class ErrorCode {
    SUCCESS = 0,
    INVALID_ARGUMENT = 1,
    OUT_OF_MEMORY = 2,
    FILE_NOT_FOUND = 3,
    PERMISSION_DENIED = 4,
    OPERATION_FAILED = 5,
    NOT_IMPLEMENTED = 6
};

// 错误信息结构
struct ErrorInfo {
    ErrorCode code;
    std::string message;
    std::string file;
    int line;
    
    std::string toString() const {
        return std::format("[{}:{}] Error {}: {}", 
            file, line, static_cast<int>(code), message);
    }
};

// 全局错误处理
class ErrorHandler {
private:
    static thread_local ErrorInfo lastError_;
    
public:
    static void setError(ErrorCode code, const std::string& message,
                        const char* file = __FILE__, int line = __LINE__) {
        lastError_ = {code, message, file, line};
    }
    
    static const ErrorInfo& getLastError() {
        return lastError_;
    }
    
    static void clearError() {
        lastError_ = {ErrorCode::SUCCESS, "", "", 0};
    }
};

// 使用宏简化错误设置
#define SET_ERROR(code, msg) ErrorHandler::setError(code, msg, __FILE__, __LINE__)
```

### C接口错误处理

```cpp
extern "C" {
    CJMOD_EXPORT int cjmod_get_last_error() {
        return static_cast<int>(ErrorHandler::getLastError().code);
    }
    
    CJMOD_EXPORT const char* cjmod_get_error_message() {
        static thread_local std::string errorMsg;
        errorMsg = ErrorHandler::getLastError().toString();
        return errorMsg.c_str();
    }
    
    CJMOD_EXPORT void cjmod_clear_error() {
        ErrorHandler::clearError();
    }
}
```

## 性能优化

### 1. 使用性能分析工具

```cpp
class PerformanceProfiler {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    
    struct ProfileData {
        std::string name;
        TimePoint start;
        double totalTime = 0;
        size_t callCount = 0;
    };
    
    static std::unordered_map<std::string, ProfileData> profiles_;
    
public:
    class ScopedTimer {
    private:
        std::string name_;
        TimePoint start_;
        
    public:
        ScopedTimer(const std::string& name) 
            : name_(name), start_(Clock::now()) {}
        
        ~ScopedTimer() {
            auto duration = Clock::now() - start_;
            auto ms = std::chrono::duration<double, std::milli>(duration).count();
            
            auto& profile = profiles_[name_];
            profile.name = name_;
            profile.totalTime += ms;
            profile.callCount++;
        }
    };
    
    static void printReport() {
        std::cout << "Performance Report:\n";
        std::cout << std::setw(30) << "Function" 
                  << std::setw(15) << "Total (ms)"
                  << std::setw(15) << "Calls"
                  << std::setw(15) << "Avg (ms)\n";
        
        for (const auto& [name, data] : profiles_) {
            std::cout << std::setw(30) << name
                      << std::setw(15) << data.totalTime
                      << std::setw(15) << data.callCount
                      << std::setw(15) << (data.totalTime / data.callCount) << "\n";
        }
    }
};

// 使用示例
#define PROFILE(name) PerformanceProfiler::ScopedTimer _timer(name)

void processData() {
    PROFILE("processData");
    // 处理逻辑
}
```

### 2. 优化技巧

- **减少内存分配**：使用对象池和预分配
- **避免不必要的拷贝**：使用移动语义和引用
- **并行处理**：利用多线程和SIMD指令
- **缓存友好**：优化数据布局

```cpp
// 缓存友好的矩阵乘法
void matrixMultiply(const float* A, const float* B, float* C, int n) {
    const int blockSize = 64; // 缓存块大小
    
    #pragma omp parallel for
    for (int i0 = 0; i0 < n; i0 += blockSize) {
        for (int j0 = 0; j0 < n; j0 += blockSize) {
            for (int k0 = 0; k0 < n; k0 += blockSize) {
                // 分块处理
                for (int i = i0; i < std::min(i0 + blockSize, n); ++i) {
                    for (int j = j0; j < std::min(j0 + blockSize, n); ++j) {
                        float sum = C[i * n + j];
                        for (int k = k0; k < std::min(k0 + blockSize, n); ++k) {
                            sum += A[i * n + k] * B[k * n + j];
                        }
                        C[i * n + j] = sum;
                    }
                }
            }
        }
    }
}
```

## 调试技巧

### 1. 日志系统

```cpp
enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Logger {
private:
    static LogLevel currentLevel_;
    static std::ofstream logFile_;
    
public:
    template<typename... Args>
    static void log(LogLevel level, const std::string& format, Args... args) {
        if (level < currentLevel_) return;
        
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
            << " [" << getLevelString(level) << "] "
            << std::vformat(format, std::make_format_args(args...));
        
        std::cout << oss.str() << std::endl;
        
        if (logFile_.is_open()) {
            logFile_ << oss.str() << std::endl;
            logFile_.flush();
        }
    }
    
private:
    static const char* getLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARN";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
};

// 便捷宏
#define LOG_DEBUG(...) Logger::log(LogLevel::DEBUG, __VA_ARGS__)
#define LOG_INFO(...) Logger::log(LogLevel::INFO, __VA_ARGS__)
#define LOG_WARNING(...) Logger::log(LogLevel::WARNING, __VA_ARGS__)
#define LOG_ERROR(...) Logger::log(LogLevel::ERROR, __VA_ARGS__)
```

### 2. 断言和检查

```cpp
#ifdef DEBUG
    #define CJMOD_ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                std::cerr << "Assertion failed: " << #condition << "\n" \
                         << "Message: " << message << "\n" \
                         << "File: " << __FILE__ << "\n" \
                         << "Line: " << __LINE__ << std::endl; \
                std::abort(); \
            } \
        } while (0)
#else
    #define CJMOD_ASSERT(condition, message) ((void)0)
#endif

// 运行时检查
#define CJMOD_CHECK(condition, error_code, message) \
    do { \
        if (!(condition)) { \
            SET_ERROR(error_code, message); \
            return {}; \
        } \
    } while (0)
```

## 发布流程

### 1. 版本管理

遵循语义化版本规范（Semantic Versioning）：
- **主版本号**：不兼容的API修改
- **次版本号**：向后兼容的功能性新增
- **修订号**：向后兼容的问题修正

### 2. 发布检查清单

```bash
#!/bin/bash
# release_checklist.sh

echo "CJMOD发布检查清单"
echo "=================="

# 1. 版本号更新
echo "[ ] 更新module.info中的版本号"
echo "[ ] 更新CMakeLists.txt中的版本号"
echo "[ ] 更新README.md中的版本号"

# 2. 代码质量
echo "[ ] 所有测试通过"
echo "[ ] 无编译警告"
echo "[ ] 代码格式化完成"
echo "[ ] 文档更新完成"

# 3. 构建测试
echo "[ ] Linux构建成功"
echo "[ ] Windows构建成功"
echo "[ ] macOS构建成功"

# 4. 打包
echo "[ ] 创建源码包"
echo "[ ] 创建二进制包"
echo "[ ] 验证包完整性"

# 5. 发布
echo "[ ] 创建Git标签"
echo "[ ] 推送到仓库"
echo "[ ] 发布到包管理器"
echo "[ ] 更新网站文档"
```

### 3. 自动化发布脚本

```bash
#!/bin/bash
# release.sh

VERSION=$1
if [ -z "$VERSION" ]; then
    echo "Usage: ./release.sh <version>"
    exit 1
fi

echo "Releasing version $VERSION..."

# 更新版本号
sed -i "s/version = .*/version = $VERSION/" info/module.info
sed -i "s/project(.* VERSION .*/project(MyCJMOD VERSION $VERSION LANGUAGES CXX)/" CMakeLists.txt

# 运行测试
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
ctest

# 创建发布包
cd ..
tar -czf my-cjmod-$VERSION.tar.gz --exclude=build --exclude=.git .

# 创建Git标签
git add .
git commit -m "Release version $VERSION"
git tag -a "v$VERSION" -m "Version $VERSION"
git push origin main --tags

echo "Release $VERSION completed!"
```

## 最佳实践

### 1. 代码组织

```cpp
// 使用命名空间避免冲突
namespace my_cjmod {
namespace detail {
    // 实现细节
}

// 公共API
class PublicClass {
    // ...
};

} // namespace my_cjmod
```

### 2. 资源管理

```cpp
// RAII包装器示例
template<typename T, typename Deleter>
class ResourceHandle {
private:
    T* resource_;
    Deleter deleter_;
    
public:
    explicit ResourceHandle(T* resource, Deleter deleter)
        : resource_(resource), deleter_(deleter) {}
    
    ~ResourceHandle() {
        if (resource_) {
            deleter_(resource_);
        }
    }
    
    // 禁用拷贝
    ResourceHandle(const ResourceHandle&) = delete;
    ResourceHandle& operator=(const ResourceHandle&) = delete;
    
    // 启用移动
    ResourceHandle(ResourceHandle&& other) noexcept
        : resource_(other.resource_), deleter_(std::move(other.deleter_)) {
        other.resource_ = nullptr;
    }
    
    ResourceHandle& operator=(ResourceHandle&& other) noexcept {
        if (this != &other) {
            if (resource_) {
                deleter_(resource_);
            }
            resource_ = other.resource_;
            deleter_ = std::move(other.deleter_);
            other.resource_ = nullptr;
        }
        return *this;
    }
    
    T* get() const { return resource_; }
    T* operator->() const { return resource_; }
    T& operator*() const { return *resource_; }
};
```

### 3. 线程安全

```cpp
// 线程安全的单例模式
template<typename T>
class Singleton {
private:
    static std::once_flag initFlag_;
    static std::unique_ptr<T> instance_;
    
public:
    static T& getInstance() {
        std::call_once(initFlag_, []() {
            instance_ = std::make_unique<T>();
        });
        return *instance_;
    }
    
    // 禁用拷贝和移动
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

template<typename T>
std::once_flag Singleton<T>::initFlag_;

template<typename T>
std::unique_ptr<T> Singleton<T>::instance_;
```

## 常见问题

### Q: 如何处理字符串编码？

A: 始终使用UTF-8编码：

```cpp
// UTF-8字符串处理
class UTF8String {
public:
    static std::u32string toUTF32(const std::string& utf8);
    static std::string fromUTF32(const std::u32string& utf32);
    static size_t length(const std::string& utf8);
    static std::string substr(const std::string& utf8, size_t start, size_t count);
};
```

### Q: 如何实现跨平台兼容？

A: 使用条件编译和抽象层：

```cpp
#ifdef _WIN32
    #include <windows.h>
    using NativeHandle = HANDLE;
#else
    #include <pthread.h>
    using NativeHandle = pthread_t;
#endif

class Thread {
private:
    NativeHandle handle_;
    
public:
    void start();
    void join();
    // 平台无关的接口
};
```

### Q: 如何优化模块加载时间？

A: 延迟初始化和按需加载：

```cpp
class LazyLoader {
private:
    mutable std::once_flag loadFlag_;
    mutable std::unique_ptr<Resource> resource_;
    
    void ensureLoaded() const {
        std::call_once(loadFlag_, [this]() {
            resource_ = loadResource();
        });
    }
    
public:
    const Resource& get() const {
        ensureLoaded();
        return *resource_;
    }
};
```

### Q: 如何调试崩溃问题？

A: 使用信号处理器和堆栈跟踪：

```cpp
#include <signal.h>
#include <execinfo.h>

void signalHandler(int sig) {
    void* array[20];
    size_t size = backtrace(array, 20);
    
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

void installSignalHandlers() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
}
```

## 总结

CJMOD开发需要注意：

1. **设计优先**：良好的API设计是成功的一半
2. **安全第一**：始终考虑内存安全和线程安全
3. **性能优化**：在正确的基础上追求性能
4. **用户友好**：提供清晰的错误信息和文档
5. **持续改进**：根据用户反馈不断优化

通过遵循这些指南，您可以创建高质量、高性能的CJMOD扩展，为CHTL生态系统贡献价值。