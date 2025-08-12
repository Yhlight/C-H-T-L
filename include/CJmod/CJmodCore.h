#ifndef CHTL_CJMOD_CORE_H
#define CHTL_CJMOD_CORE_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include <any>
#include <set>

namespace chtl {
namespace cjmod {

// 前向声明
class SyntaxBuilder;
class RuntimeBuilder;
class StateManager;

// 扫描结果
struct ScanResult {
    size_t start;
    size_t end;
    std::string content;
    std::unordered_map<std::string, std::string> captures;  // 捕获组
    std::any userData;  // 开发者自定义数据
};

// 扫描上下文 - 提供给规则使用
class ScanContext {
public:
    virtual ~ScanContext() = default;
    
    // 基础信息
    virtual const std::string& getCode() const = 0;
    virtual size_t getPosition() const = 0;
    virtual size_t getLength() const = 0;
    
    // 上下文状态
    virtual bool isInString() const = 0;
    virtual bool isInComment() const = 0;
    virtual bool isInRegex() const = 0;
    virtual int getBraceDepth() const = 0;
    virtual int getParenDepth() const = 0;
    virtual int getBracketDepth() const = 0;
    
    // 工具方法
    virtual size_t findNext(const std::string& str, size_t from = 0) const = 0;
    virtual size_t findMatching(char open, char close, size_t from) const = 0;
    virtual std::string substring(size_t start, size_t length) const = 0;
    virtual bool matches(const std::string& pattern, size_t at) const = 0;
    
    // 状态访问
    virtual StateManager* getStateManager() = 0;
    
    // 标记处理
    virtual void markProcessed(size_t start, size_t end) = 0;
    virtual bool isProcessed(size_t pos) const = 0;
};

// 生成上下文
class GenerateContext {
public:
    virtual ~GenerateContext() = default;
    
    // 代码生成
    virtual void emit(const std::string& code) = 0;
    virtual void emitLine(const std::string& code) = 0;
    virtual void emitIndented(const std::string& code) = 0;
    
    // 缩进管理
    virtual void pushIndent() = 0;
    virtual void popIndent() = 0;
    virtual std::string getIndent() const = 0;
    
    // 变量生成
    virtual std::string uniqueVar(const std::string& prefix = "var") = 0;
    virtual std::string uniqueLabel(const std::string& prefix = "label") = 0;
    
    // 运行时注入
    virtual RuntimeBuilder& runtime() = 0;
    
    // 状态访问
    virtual StateManager* getStateManager() = 0;
    
    // 错误报告
    virtual void error(const std::string& msg, const ScanResult& result) = 0;
    virtual void warning(const std::string& msg, const ScanResult& result) = 0;
};

// 状态管理器 - 允许模块管理自己的全局状态
class StateManager {
public:
    template<typename T>
    void set(const std::string& key, T&& value) {
        states_[key] = std::forward<T>(value);
    }
    
    template<typename T>
    T* get(const std::string& key) {
        auto it = states_.find(key);
        if (it != states_.end()) {
            return std::any_cast<T>(&it->second);
        }
        return nullptr;
    }
    
    template<typename T>
    T& getOrCreate(const std::string& key, T defaultValue = T{}) {
        if (!has(key)) {
            set(key, std::move(defaultValue));
        }
        return *std::any_cast<T>(&states_[key]);
    }
    
    bool has(const std::string& key) const {
        return states_.find(key) != states_.end();
    }
    
    void remove(const std::string& key) {
        states_.erase(key);
    }
    
    void clear() {
        states_.clear();
    }
    
private:
    std::unordered_map<std::string, std::any> states_;
};

// 语法构建器 - 优雅地创建语法规则
class SyntaxBuilder {
public:
    using ScanFunc = std::function<std::vector<ScanResult>(ScanContext*)>;
    using GenerateFunc = std::function<std::string(const ScanResult&, GenerateContext*)>;
    using ValidateFunc = std::function<bool(const ScanResult&)>;
    
    SyntaxBuilder(const std::string& name) : name_(name), priority_(100) {}
    
    // 设置优先级
    SyntaxBuilder& priority(int p) {
        priority_ = p;
        return *this;
    }
    
    // 设置描述
    SyntaxBuilder& description(const std::string& desc) {
        description_ = desc;
        return *this;
    }
    
    // 简单的模式匹配
    SyntaxBuilder& pattern(const std::string& regex) {
        pattern_ = regex;
        scanFunc_ = nullptr;  // 使用内置的正则扫描
        return *this;
    }
    
    // 自定义扫描函数
    SyntaxBuilder& scan(ScanFunc func) {
        scanFunc_ = std::move(func);
        pattern_.clear();
        return *this;
    }
    
    // 生成函数
    SyntaxBuilder& generate(GenerateFunc func) {
        generateFunc_ = std::move(func);
        return *this;
    }
    
    // 简单替换
    SyntaxBuilder& replace(const std::string& replacement) {
        generateFunc_ = [replacement](const ScanResult& result, GenerateContext* /*ctx*/) {
            std::string output = replacement;
            // 替换捕获组 $1, $2, etc.
            for (const auto& [name, value] : result.captures) {
                size_t pos = 0;
                std::string placeholder = "${" + name + "}";
                while ((pos = output.find(placeholder, pos)) != std::string::npos) {
                    output.replace(pos, placeholder.length(), value);
                    pos += value.length();
                }
            }
            return output;
        };
        return *this;
    }
    
    // 验证函数
    SyntaxBuilder& validate(ValidateFunc func) {
        validateFunc_ = std::move(func);
        return *this;
    }
    
    // 示例代码
    SyntaxBuilder& example(const std::string& before, const std::string& after) {
        examples_.push_back({before, after});
        return *this;
    }
    
    // 友元类需要访问内部数据
    friend class CJmodModule;
    
private:
    std::string name_;
    std::string description_;
    int priority_;
    std::string pattern_;
    ScanFunc scanFunc_;
    GenerateFunc generateFunc_;
    ValidateFunc validateFunc_;
    std::vector<std::pair<std::string, std::string>> examples_;
};

// 运行时构建器 - 管理运行时代码注入
class RuntimeBuilder {
public:
    // 添加函数（去重）
    RuntimeBuilder& function(const std::string& name, const std::string& code) {
        functions_[name] = code;
        return *this;
    }
    
    // 添加类
    RuntimeBuilder& class_(const std::string& name, const std::string& code) {
        classes_[name] = code;
        return *this;
    }
    
    // 添加到原型
    RuntimeBuilder& prototype(const std::string& target, const std::string& method, const std::string& code) {
        prototypes_[target + "." + method] = code;
        return *this;
    }
    
    // 添加全局变量
    RuntimeBuilder& global(const std::string& name, const std::string& code) {
        globals_[name] = code;
        return *this;
    }
    
    // 添加初始化代码
    RuntimeBuilder& init(const std::string& code) {
        initCode_.push_back(code);
        return *this;
    }
    
    // 依赖其他运行时
    RuntimeBuilder& require(const std::string& name) {
        dependencies_.insert(name);
        return *this;
    }
    
    // 生成最终的运行时代码
    std::string generate() const;
    
private:
    std::unordered_map<std::string, std::string> functions_;
    std::unordered_map<std::string, std::string> classes_;
    std::unordered_map<std::string, std::string> prototypes_;
    std::unordered_map<std::string, std::string> globals_;
    std::vector<std::string> initCode_;
    std::set<std::string> dependencies_;
};

// CJmod 模块基类
class CJmodModule {
public:
    CJmodModule(const std::string& name, const std::string& version)
        : name_(name), version_(version) {}
    
    virtual ~CJmodModule() = default;
    
    // 模块信息
    const std::string& getName() const { return name_; }
    const std::string& getVersion() const { return version_; }
    const std::string& getDescription() const { return description_; }
    const std::string& getAuthor() const { return author_; }
    
    // 设置模块信息
    CJmodModule& setDescription(const std::string& desc) {
        description_ = desc;
        return *this;
    }
    
    CJmodModule& setAuthor(const std::string& author) {
        author_ = author;
        return *this;
    }
    
    // 初始化 - 子类重写以设置规则
    virtual void initialize() = 0;
    
    // 获取状态管理器
    StateManager& state() { return stateManager_; }
    
protected:
    // 创建语法规则
    SyntaxBuilder& syntax(const std::string& name) {
        auto builder = std::make_unique<SyntaxBuilder>(name);
        SyntaxBuilder* ptr = builder.get();
        syntaxBuilders_.push_back(std::move(builder));
        return *ptr;
    }
    
    // 设置运行时
    RuntimeBuilder& runtime() {
        return runtimeBuilder_;
    }
    
    // 依赖其他模块
    void require(const std::string& module) {
        dependencies_.insert(module);
    }
    
private:
    std::string name_;
    std::string version_;
    std::string description_;
    std::string author_;
    
    std::vector<std::unique_ptr<SyntaxBuilder>> syntaxBuilders_;
    RuntimeBuilder runtimeBuilder_;
    StateManager stateManager_;
    std::set<std::string> dependencies_;
    
    friend class CJmodProcessor;
};

// 辅助宏 - 简化模块导出
#define CJMOD_MODULE_EXPORT(ModuleClass) \
    extern "C" { \
        CJmodModule* cjmod_create() { \
            return new ModuleClass(); \
        } \
        void cjmod_destroy(CJmodModule* module) { \
            delete module; \
        } \
        const char* cjmod_version() { \
            return "1.0"; \
        } \
    }

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_CORE_H