#ifndef CHTL_COMPILER_CHTL_JS_COMPILER_H
#define CHTL_COMPILER_CHTL_JS_COMPILER_H

#include "../compiler/Compiler.h"
#include <string>
#include <vector>
#include <map>

namespace chtl {

// CHTL JS编译器类
class CHTLJSCompiler : public Compiler {
public:
    CHTLJSCompiler();
    ~CHTLJSCompiler() = default;

    // 编译CHTL JS代码
    bool compile(const std::string& sourceCode);
    
    // 获取编译后的JavaScript
    std::string getJavaScript() const { return jsOutput_; }
    
    // 验证CHTL JS语法
    bool validate(const std::string& sourceCode);
    
    // 转换CHTL JS语法为标准JavaScript
    std::string transpile(const std::string& sourceCode);

private:
    std::string jsOutput_;
    
    // 解析CHTL JS语法树
    void parseCHTLJS(const std::string& sourceCode);
    
    // 生成JavaScript输出
    void generateJavaScript();
    
    // 处理CHTL选择器
    void processCHTLSelectors();
    
    // 处理监听器
    void processListeners();
    
    // 处理事件委托
    void processEventDelegation();
    
    // 处理动画
    void processAnimations();
    
    // 转换选择器语法
    std::string convertSelector(const std::string& chtlSelector);
    
    // 转换监听器语法
    std::string convertListener(const std::string& chtlListener);
    
    // 转换事件委托语法
    std::string convertEventDelegation(const std::string& chtlDelegate);
    
    // 转换动画语法
    std::string convertAnimation(const std::string& chtlAnimation);
    
    // 生成DOM查询代码
    std::string generateDOMQuery(const std::string& selector);
    
    // 生成事件绑定代码
    std::string generateEventBinding(const std::string& eventType, const std::string& handler);
    
    // 生成动画代码
    std::string generateAnimationCode(const std::map<std::string, std::string>& animationConfig);
    
    // 验证选择器语法
    bool validateSelector(const std::string& selector);
    
    // 验证事件处理器
    bool validateEventHandler(const std::string& handler);
    
    // 验证动画配置
    bool validateAnimationConfig(const std::map<std::string, std::string>& config);
    
    // 解析选择器内容
    std::vector<std::string> parseSelectorContent(const std::string& selector);
    
    // 解析动画配置
    std::map<std::string, std::string> parseAnimationConfig(const std::string& config);
};

} // namespace chtl

#endif // CHTL_COMPILER_CHTL_JS_COMPILER_H