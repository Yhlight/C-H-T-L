# CMOD与CJMOD完整指南

## 概述

CHTL模块系统提供两种类型的模块：

- **CMOD (CHTL Module)**: 纯CHTL源代码模块
- **CJMOD (CHTL JavaScript Module)**: C++扩展模块，提供原生性能和高级功能

## CMOD - CHTL模块

### 什么是CMOD？

CMOD是CHTL的标准模块格式，包含可重用的CHTL代码、样式和模板。

### CMOD结构

```
my-module.cmod/
├── info/
│   └── module.info        # 模块元数据
├── src/
│   ├── main.chtl         # 主入口文件
│   ├── components/       # 组件目录
│   └── styles/          # 样式目录
└── [Export]             # 导出表（自动生成）
```

### 创建CMOD

#### 1. 创建目录结构

```bash
mkdir -p my-module/{info,src}
```

#### 2. 编写module.info

```ini
name = MyModule
version = 1.0.0
author = Your Name
description = A reusable CHTL module
type = cmod
license = MIT
homepage = https://example.com
dependencies = Chtl.Core@1.0.0, Utils@2.0.0
min_chtl_version = 1.0.0
```

#### 3. 创建CHTL源文件

```chtl
// src/main.chtl
[Namespace] MyModule

[Template] @Style PrimaryButton {
    @inherit Chtl.Core.ButtonBase;
    background-color: #007bff;
    color: white;
    
    &:hover {
        background-color: #0056b3;
    }
}

[Template] @Element Card(title, content) {
    div {
        class: my-card;
        
        div {
            class: card-header;
            h3 { text { {title} } }
        }
        
        div {
            class: card-body;
            text { {content} }
        }
        
        style {
            .my-card {
                border: 1px solid #ddd;
                border-radius: 8px;
                overflow: hidden;
            }
        }
    }
}
```

#### 4. 打包CMOD

```bash
./scripts/pack_cmod.sh -m my-module -o output/
```

### 使用CMOD

```chtl
// 导入整个模块
[Import] @Module MyModule

// 使用模块内容
[Namespace] MyApp

div {
    @Element MyModule.Card("Welcome", "Hello CHTL!");
    
    button {
        style {
            @use MyModule.PrimaryButton;
        }
        text { "Click Me" }
    }
}
```

### CMOD最佳实践

1. **命名空间管理**
   - 始终使用唯一的命名空间
   - 避免与标准库冲突

2. **版本控制**
   - 遵循语义化版本
   - 记录破坏性更改

3. **依赖管理**
   - 明确声明所有依赖
   - 避免循环依赖

4. **文档编写**
   - 为每个公共API编写文档
   - 提供使用示例

## CJMOD - C++扩展模块

### 什么是CJMOD？

CJMOD允许使用C++编写高性能扩展，提供CHTL无法直接实现的功能。

### CJMOD结构

```
my-extension.cjmod/
├── info/
│   └── module.info       # 模块元数据
├── include/
│   └── my_extension.h    # 公共头文件
├── src/
│   └── my_extension.cpp  # 实现文件
├── CMakeLists.txt       # 构建配置
└── lib/
    └── libmy_extension.so # 编译后的库
```

### 创建CJMOD

#### 1. 创建项目结构

```bash
mkdir -p my-extension/{info,include,src}
```

#### 2. 编写module.info

```ini
name = MyExtension
version = 1.0.0
author = Your Name
description = High-performance CHTL extension
type = cjmod
license = MIT
homepage = https://example.com
dependencies = 
min_chtl_version = 1.0.0
cpp_standard = 17
```

#### 3. 编写C++接口

```cpp
// include/my_extension.h
#ifndef MY_EXTENSION_H
#define MY_EXTENSION_H

#include <string>
#include <memory>

namespace my_extension {

// 图像处理类
class ImageProcessor {
public:
    ImageProcessor();
    ~ImageProcessor();
    
    // 加载图像
    bool load(const std::string& path);
    
    // 应用滤镜
    void applyBlur(double radius);
    void applySharpen(double amount);
    void applyGrayscale();
    
    // 保存图像
    bool save(const std::string& path);
    
    // 获取base64编码
    std::string toBase64() const;
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

// 导出的C接口
extern "C" {
    // 创建处理器
    void* create_image_processor();
    
    // 销毁处理器
    void destroy_image_processor(void* processor);
    
    // 加载图像
    bool load_image(void* processor, const char* path);
    
    // 应用滤镜
    void apply_blur(void* processor, double radius);
    void apply_sharpen(void* processor, double amount);
    void apply_grayscale(void* processor);
    
    // 获取结果
    const char* get_base64(void* processor);
}

} // namespace my_extension

#endif // MY_EXTENSION_H
```

#### 4. 实现功能

```cpp
// src/my_extension.cpp
#include "../include/my_extension.h"
#include <opencv2/opencv.hpp>
#include <base64.h>

namespace my_extension {

class ImageProcessor::Impl {
public:
    cv::Mat image;
    std::string base64Result;
    
    bool loadImage(const std::string& path) {
        image = cv::imread(path);
        return !image.empty();
    }
    
    void blur(double radius) {
        if (!image.empty()) {
            cv::GaussianBlur(image, image, cv::Size(0, 0), radius);
        }
    }
    
    void sharpen(double amount) {
        if (!image.empty()) {
            cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
                0, -amount, 0,
                -amount, 1 + 4*amount, -amount,
                0, -amount, 0);
            cv::filter2D(image, image, -1, kernel);
        }
    }
    
    void grayscale() {
        if (!image.empty() && image.channels() > 1) {
            cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
        }
    }
    
    std::string encodeBase64() {
        if (image.empty()) return "";
        
        std::vector<uchar> buffer;
        cv::imencode(".png", image, buffer);
        
        // Base64编码
        return base64_encode(buffer.data(), buffer.size());
    }
};

ImageProcessor::ImageProcessor() : pImpl(std::make_unique<Impl>()) {}
ImageProcessor::~ImageProcessor() = default;

bool ImageProcessor::load(const std::string& path) {
    return pImpl->loadImage(path);
}

void ImageProcessor::applyBlur(double radius) {
    pImpl->blur(radius);
}

void ImageProcessor::applySharpen(double amount) {
    pImpl->sharpen(amount);
}

void ImageProcessor::applyGrayscale() {
    pImpl->grayscale();
}

std::string ImageProcessor::toBase64() const {
    return pImpl->encodeBase64();
}

// C接口实现
extern "C" {

void* create_image_processor() {
    return new ImageProcessor();
}

void destroy_image_processor(void* processor) {
    delete static_cast<ImageProcessor*>(processor);
}

bool load_image(void* processor, const char* path) {
    return static_cast<ImageProcessor*>(processor)->load(path);
}

void apply_blur(void* processor, double radius) {
    static_cast<ImageProcessor*>(processor)->applyBlur(radius);
}

void apply_sharpen(void* processor, double amount) {
    static_cast<ImageProcessor*>(processor)->applySharpen(amount);
}

void apply_grayscale(void* processor) {
    static_cast<ImageProcessor*>(processor)->applyGrayscale();
}

const char* get_base64(void* processor) {
    static std::string result;
    result = static_cast<ImageProcessor*>(processor)->toBase64();
    return result.c_str();
}

} // extern "C"

} // namespace my_extension
```

#### 5. 创建CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyExtension VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找依赖
find_package(OpenCV REQUIRED)

# 创建共享库
add_library(my_extension SHARED
    src/my_extension.cpp
)

# 包含目录
target_include_directories(my_extension PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 链接库
target_link_libraries(my_extension PRIVATE
    ${OpenCV_LIBS}
)

# 安装规则
install(TARGETS my_extension
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)
```

#### 6. 构建和打包

```bash
./scripts/pack_cjmod.sh -m my-extension -o output/
```

### 在CHTL中使用CJMOD

```chtl
[Import] @CJmod MyExtension

[Namespace] ImageApp

[Template] @Element ImageEditor(imagePath) {
    div {
        id: image-editor;
        
        img {
            id: preview;
            src: "";
        }
        
        div {
            class: controls;
            
            button {
                onclick: applyBlur();
                text { "模糊" }
            }
            
            button {
                onclick: applySharpen();
                text { "锐化" }
            }
            
            button {
                onclick: applyGrayscale();
                text { "灰度" }
            }
        }
        
        script {
            // 初始化处理器
            const processor = MyExtension.createImageProcessor();
            MyExtension.loadImage(processor, "{imagePath}");
            
            function updatePreview() {
                const base64 = MyExtension.getBase64(processor);
                document.getElementById("preview").src = "data:image/png;base64," + base64;
            }
            
            function applyBlur() {
                MyExtension.applyBlur(processor, 5.0);
                updatePreview();
            }
            
            function applySharpen() {
                MyExtension.applySharpen(processor, 0.5);
                updatePreview();
            }
            
            function applyGrayscale() {
                MyExtension.applyGrayscale(processor);
                updatePreview();
            }
            
            // 初始显示
            updatePreview();
            
            // 清理
            window.addEventListener("unload", () => {
                MyExtension.destroyImageProcessor(processor);
            });
        }
    }
}
```

### CJMOD开发指南

#### 1. 内存管理

- 使用RAII和智能指针
- 提供明确的创建/销毁函数
- 避免内存泄漏

```cpp
// 好的实践
class Resource {
    std::unique_ptr<Impl> pImpl;
public:
    Resource() : pImpl(std::make_unique<Impl>()) {}
    ~Resource() = default;
};

// C接口
extern "C" {
    void* create_resource() { return new Resource(); }
    void destroy_resource(void* r) { delete static_cast<Resource*>(r); }
}
```

#### 2. 错误处理

```cpp
// 使用错误码
enum ErrorCode {
    SUCCESS = 0,
    ERROR_INVALID_PARAM = -1,
    ERROR_FILE_NOT_FOUND = -2,
    ERROR_OUT_OF_MEMORY = -3
};

extern "C" {
    int process_data(void* processor, const char* input) {
        if (!processor || !input) return ERROR_INVALID_PARAM;
        
        try {
            // 处理逻辑
            return SUCCESS;
        } catch (const std::bad_alloc&) {
            return ERROR_OUT_OF_MEMORY;
        } catch (...) {
            return ERROR_INVALID_PARAM;
        }
    }
}
```

#### 3. 线程安全

```cpp
class ThreadSafeProcessor {
    mutable std::mutex mutex_;
    Data data_;
    
public:
    void process() {
        std::lock_guard<std::mutex> lock(mutex_);
        // 线程安全的操作
    }
};
```

#### 4. 性能优化

- 避免频繁的内存分配
- 使用对象池
- 批量处理

```cpp
class BatchProcessor {
    ObjectPool<Task> taskPool_;
    
public:
    void processBatch(const std::vector<Input>& inputs) {
        std::vector<std::future<Result>> futures;
        
        for (const auto& input : inputs) {
            futures.push_back(std::async(std::launch::async, 
                [this, &input] { return processOne(input); }));
        }
        
        for (auto& future : futures) {
            future.wait();
        }
    }
};
```

### CJMOD示例集合

#### 1. Chtholly动画库

提供高级动画和特效功能（见上文实现）。

#### 2. 数据库连接器

```cpp
namespace db_connector {

class Database {
public:
    bool connect(const std::string& connectionString);
    ResultSet query(const std::string& sql);
    bool execute(const std::string& sql);
    void close();
};

extern "C" {
    void* db_connect(const char* conn_str);
    const char* db_query_json(void* db, const char* sql);
    bool db_execute(void* db, const char* sql);
    void db_close(void* db);
}

}
```

#### 3. 加密工具

```cpp
namespace crypto {

class Encryptor {
public:
    std::string encrypt(const std::string& data, const std::string& key);
    std::string decrypt(const std::string& data, const std::string& key);
    std::string hash(const std::string& data, HashAlgorithm algo);
};

extern "C" {
    const char* encrypt_aes256(const char* data, const char* key);
    const char* decrypt_aes256(const char* data, const char* key);
    const char* hash_sha256(const char* data);
}

}
```

## 模块发布

### 1. 版本管理

遵循语义化版本规范：
- 主版本号：不兼容的API修改
- 次版本号：向下兼容的功能性新增
- 修订号：向下兼容的问题修正

### 2. 发布检查清单

- [ ] 更新版本号
- [ ] 编写更新日志
- [ ] 运行所有测试
- [ ] 更新文档
- [ ] 检查依赖版本
- [ ] 构建发布包
- [ ] 标记Git版本

### 3. 发布到仓库

```bash
# 构建模块
./scripts/pack_cmod.sh -m my-module -o dist/

# 发布到CHTL仓库
chtl publish dist/my-module-1.0.0.cmod
```

## 故障排除

### 常见问题

1. **CMOD加载失败**
   - 检查模块结构
   - 验证module.info格式
   - 确认依赖存在

2. **CJMOD链接错误**
   - 检查库路径
   - 验证ABI兼容性
   - 确认依赖库存在

3. **性能问题**
   - 使用性能分析工具
   - 检查内存泄漏
   - 优化热点代码

### 调试技巧

1. **启用调试日志**
```bash
export CHTL_MODULE_DEBUG=1
chtl compile app.chtl
```

2. **使用调试器**
```bash
gdb chtl
(gdb) break module_load
(gdb) run app.chtl
```

3. **模块测试**
```chtl
[Import] @Module MyModule except TestOnly

// 测试代码
@TestOnly {
    assert(MyModule.version == "1.0.0");
    assert(MyModule.Card != null);
}
```

## 总结

CMOD和CJMOD为CHTL提供了强大的扩展能力：

- CMOD适合纯CHTL组件和样式库
- CJMOD适合需要原生性能的功能扩展
- 两者可以相互配合，构建完整的应用

通过合理使用模块系统，可以构建可维护、可扩展的大型CHTL应用。