#ifndef CHTL_CJMOD_INTERFACE_H
#define CHTL_CJMOD_INTERFACE_H

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <regex>

namespace chtl {
namespace cjmod {

// CJmod 语法转换规则
struct TransformRule {
    std::string name;           // 规则名称
    std::regex pattern;         // 匹配模式
    int priority;               // 优先级（越大越先执行）
    
    // 转换函数：输入匹配结果，返回替换内容
    std::function<std::string(const std::smatch&)> transformer;
    
    // 可选：验证函数，检查是否应该应用此规则
    std::function<bool(const std::string& context)> validator;
};

// CJmod 方法注入
struct MethodInjection {
    std::string target;         // 目标对象：Element, Document, Window
    std::string methodName;     // 方法名
    std::string implementation; // JavaScript 实现
    bool isAsync;              // 是否异步方法
};

// CJmod 运算符定义
struct OperatorDefinition {
    std::string symbol;         // 运算符符号
    std::string jsOperator;     // 对应的 JS 运算符或函数
    int precedence;            // 优先级
    bool isUnary;              // 是否一元运算符
    
    // 转换函数
    std::function<std::string(const std::string& left, const std::string& right)> transform;
};

// CJmod 接口 - 所有 CJmod 必须实现
class ICJmod {
public:
    virtual ~ICJmod() = default;
    
    // 基本信息
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual std::string getDescription() const = 0;
    
    // 获取转换规则
    virtual std::vector<TransformRule> getTransformRules() const = 0;
    
    // 获取方法注入
    virtual std::vector<MethodInjection> getMethodInjections() const = 0;
    
    // 获取运算符定义
    virtual std::vector<OperatorDefinition> getOperatorDefinitions() const = 0;
    
    // 获取运行时代码
    virtual std::string getRuntimeCode() const = 0;
    
    // 初始化钩子
    virtual void initialize() {}
    
    // 预处理钩子（在转换前）
    virtual std::string preprocess(const std::string& code) { return code; }
    
    // 后处理钩子（在转换后）
    virtual std::string postprocess(const std::string& code) { return code; }
};

// CJmod 工厂接口
class ICJmodFactory {
public:
    virtual ~ICJmodFactory() = default;
    virtual std::unique_ptr<ICJmod> create() = 0;
    virtual std::string getModuleName() const = 0;
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_INTERFACE_H