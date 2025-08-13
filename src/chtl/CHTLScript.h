#ifndef CHTL_SCRIPT_H
#define CHTL_SCRIPT_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <regex>
#include "CHTLContext.h"

namespace chtl {

// 前向声明
class CHTLGenerator;
class Scanner;
class CJMODManager;
class CHTLJSContext;

// 脚本类型
enum class ScriptType {
    JAVASCRIPT,     // 普通JavaScript代码
    CHTL_JS        // CHTL扩展的JavaScript代码
};

// 增强选择器类型
enum class SelectorType {
    TAG,           // 标签选择器 {{button}}
    CLASS,         // 类选择器 {{.box}}
    ID,            // ID选择器 {{#box}}
    AUTO,          // 自动推断 {{box}}
    DESCENDANT,    // 后代选择器 {{.box button}}
    INDEXED        // 索引选择器 {{button[0]}}
};

// 增强选择器
struct EnhancedSelector {
    SelectorType type;
    std::string selector;        // 原始选择器字符串
    std::string primaryTarget;   // 主要目标（如类名、ID或标签名）
    std::string secondaryTarget; // 次要目标（用于后代选择器）
    int index;                   // 索引（用于索引选择器）
    bool hasIndex;              // 是否有索引
    
    EnhancedSelector() : type(SelectorType::AUTO), index(-1), hasIndex(false) {}
};

// 脚本块
class ScriptBlock {
private:
    std::string content;              // 脚本内容
    ScriptType type;                  // 脚本类型
    std::string scope;                // 作用域（所属元素）
    std::vector<EnhancedSelector> selectors;  // 使用的增强选择器
    bool isProcessed;                 // 是否已处理
    
    // 源信息
    std::string sourceFile;
    int startLine;
    int endLine;
    
public:
    ScriptBlock(const std::string& content = "", ScriptType type = ScriptType::JAVASCRIPT)
        : content(content), type(type), isProcessed(false), startLine(0), endLine(0) {}
    
    // 获取器
    const std::string& getContent() const { return content; }
    ScriptType getType() const { return type; }
    const std::string& getScope() const { return scope; }
    const std::vector<EnhancedSelector>& getSelectors() const { return selectors; }
    bool hasBeenProcessed() const { return isProcessed; }
    
    // 设置器
    void setContent(const std::string& c) { content = c; }
    void setType(ScriptType t) { type = t; }
    void setScope(const std::string& s) { scope = s; }
    void addSelector(const EnhancedSelector& sel) { selectors.push_back(sel); }
    void markProcessed() { isProcessed = true; }
    
    // 源信息
    void setSourceInfo(const std::string& file, int start, int end) {
        sourceFile = file;
        startLine = start;
        endLine = end;
    }
};

// 脚本管理器
class ScriptManager {
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    ScriptManager(std::shared_ptr<CHTLContext> context);
    ~ScriptManager();
    
    // 获取上下文
    std::shared_ptr<CHTLContext> getContext() const;
    std::shared_ptr<CHTLJSContext> getJSContext() const;
    
    // 添加局部脚本
    void addLocalScript(const std::string& elementPath, std::shared_ptr<ScriptBlock> script);
    
    // 添加全局脚本
    void addGlobalScript(std::shared_ptr<ScriptBlock> script);
    
    // 获取元素的脚本
    std::vector<std::shared_ptr<ScriptBlock>> getScriptsForElement(const std::string& elementPath) const;
    
    // 生成作用域ID
    std::string generateScopeId(const std::string& elementPath);
    std::string getScopeId(const std::string& elementPath) const;
    
    // 处理所有脚本
    void processAllScripts();
    
    // 生成最终的JavaScript代码
    std::string generateJavaScript() const;
    
    // 清理
    void clear();
};

// 增强选择器处理器
class EnhancedSelectorProcessor {
private:
    const ScriptManager& scriptManager;
    
public:
    EnhancedSelectorProcessor(const ScriptManager& mgr) : scriptManager(mgr) {}
    
    // 解析增强选择器
    EnhancedSelector parseSelector(const std::string& selectorStr);
    
    // 转换为JavaScript代码
    std::string toJavaScript(const EnhancedSelector& selector, const std::string& currentScope = "");
    
    // 检测选择器类型
    SelectorType detectSelectorType(const std::string& selector);
    
    // 解析索引
    std::pair<std::string, int> parseIndexedSelector(const std::string& selector);
};

// 脚本处理器
class ScriptProcessor {
private:
    ScriptManager& manager;
    CJMODManager* cjmodManager = nullptr;
    
public:
    ScriptProcessor(ScriptManager& mgr) : manager(mgr) {}
    
    // 设置CJMOD管理器
    void setCJMODManager(CJMODManager* mgr) { cjmodManager = mgr; }
    
    // 获取上下文
    std::shared_ptr<CHTLContext> getContext() const;
    
    // 处理脚本块
    std::shared_ptr<ScriptBlock> processScriptBlock(const std::string& content,
                                                    const std::string& scope);
    
    // 处理增强选择器
    std::string processEnhancedSelectors(const std::string& script,
                                        std::vector<EnhancedSelector>& selectors);
    
    // 检测脚本类型
    ScriptType detectScriptType(const std::string& script);
    
    // 注册自定义函数（供CJMOD使用）
    void registerFunction(const std::string& name, 
                         std::function<std::string(const std::vector<std::string>&)> func);
    
    // 注册语法转换器（供CJMOD使用）
    void registerTransformer(const std::string& pattern,
                           std::function<std::string(const std::string&)> transformer);
    
private:
    // 自定义函数注册表
    std::unordered_map<std::string, std::function<std::string(const std::vector<std::string>&)>> customFunctions;
    
    // 语法转换器注册表
    std::vector<std::pair<std::string, std::function<std::string(const std::string&)>>> syntaxTransformers;
    
    // 应用CJMOD扩展
    std::string applyCJMODExtensions(const std::string& script);
    
    // 处理无修饰字面量
    std::string processUnquotedLiterals(const std::string& script, 
                                      std::shared_ptr<CHTLJSContext> jsContext);
    
    // 判断是否应该处理该行的无修饰字面量
    bool shouldProcessLineForUnquoted(const std::string& line);
    
    // 处理单行中的无修饰字面量
    std::string processLineForUnquotedLiterals(const std::string& line,
                                             std::shared_ptr<CHTLJSContext> jsContext);
    
    // 检测并处理方法调用
    std::string detectAndProcessMethods(const std::string& script);
};

// CHTL JS转换器
class CHTLJSTransformer {
private:
    const std::string& currentScope;
    const ScriptManager& scriptManager;
    
public:
    CHTLJSTransformer(const std::string& scope, const ScriptManager& mgr)
        : currentScope(scope), scriptManager(mgr) {}
    
    // 转换CHTL JS代码为标准JavaScript
    std::string transform(const std::string& chtljs);
    
    // 转换增强选择器
    std::string transformSelector(const std::string& selectorExpr);
    
    // 生成DOM查询代码
    std::string generateQueryCode(const EnhancedSelector& selector);
    
    // 生成作用域代码
    std::string generateScopeCode(const std::string& scopeId);
};

// 脚本隔离器
class ScriptIsolator {
public:
    // 生成隔离的脚本包装
    static std::string wrapInIsolation(const std::string& script, const std::string& scopeId);
    
    // 生成模块化包装
    static std::string wrapAsModule(const std::string& script, const std::string& moduleName);
    
    // 生成立即执行函数
    static std::string wrapInIIFE(const std::string& script);
    
    // 生成作用域绑定代码
    static std::string generateScopeBinding(const std::string& scopeId);
};

// 辅助函数
namespace ScriptHelper {
    // 检查是否包含增强选择器
    bool hasEnhancedSelector(const std::string& script);
    
    // 提取所有增强选择器
    std::vector<std::string> extractEnhancedSelectors(const std::string& script);
    
    // 验证选择器语法
    bool isValidSelector(const std::string& selector);
    
    // 转义JavaScript字符串
    std::string escapeJavaScript(const std::string& str);
    
    // 生成唯一的函数名
    std::string generateUniqueFunctionName(const std::string& base);
    
    // 检查是否是有效的CSS选择器
    bool isValidCSSSelector(const std::string& selector);
    
    // 分解复合选择器
    std::vector<std::string> decomposeSelector(const std::string& selector);
    
    // 检查是否包含箭头语法
    bool hasArrowSyntax(const std::string& script);
    
    // 转换箭头语法为点语法
    std::string convertArrowToDot(const std::string& script);
}

// CHTL JS扩展功能
namespace CHTLJSExtensions {

// 事件监听器配置
struct EventListenerConfig {
    std::string eventType;
    std::string callback;
    bool isInline;
};

// 事件委托配置
struct EventDelegationConfig {
    std::vector<std::string> targets;     // 目标选择器列表
    std::vector<EventListenerConfig> events;  // 事件配置列表
    std::string parentSelector;           // 父元素选择器
};

// 动画关键帧
struct AnimationKeyframe {
    double at;                            // 时间点（0-1）
    std::map<std::string, std::string> properties;  // CSS属性
};

// 动画配置
struct AnimationConfig {
    int duration;                         // 持续时间(ms)
    std::string easing;                   // 缓动函数
    std::map<std::string, std::string> begin;    // 起始状态
    std::vector<AnimationKeyframe> when;          // 关键帧
    std::map<std::string, std::string> end;      // 结束状态
    int loop;                             // 循环次数（-1为无限）
    std::string direction;                // 播放方向
    int delay;                            // 延迟(ms)
    std::string callback;                 // 回调函数
};

// 增强方法调用处理器
class EnhancedMethodProcessor {
public:
    // 处理listen方法
    static std::string processListen(const std::string& selector, const std::string& config);
    
    // 处理delegate方法
    static std::string processDelegate(const std::string& selector, const std::string& config);
    
    // 解析事件配置
    static std::vector<EventListenerConfig> parseEventConfig(const std::string& config);
    
    // 解析委托配置
    static EventDelegationConfig parseDelegateConfig(const std::string& config);
    
    // 生成事件监听代码
    static std::string generateEventListenerCode(const std::string& element, 
                                                const EventListenerConfig& event);
    
    // 生成事件委托代码
    static std::string generateDelegationCode(const EventDelegationConfig& config);
};

// 动画处理器
class AnimationProcessor {
public:
    // 处理animate函数 - 返回一个函数
    static std::string processAnimate(const std::string& config);
    
    // 解析动画配置
    static AnimationConfig parseAnimationConfig(const std::string& config);
    
    // 生成动画函数代码
    static std::string generateAnimationFunction(const AnimationConfig& config);
    
    // 生成关键帧代码
    static std::string generateKeyframeCode(const AnimationKeyframe& keyframe);
    
    // 解析缓动函数
    static std::string parseEasing(const std::string& easing);
    
    // 生成RAF循环代码
    static std::string generateRAFLoop(const AnimationConfig& config);
    
private:
    // 辅助函数：将map转换为JavaScript对象
    static std::string mapToJsObject(const std::map<std::string, std::string>& map);
};

// 事件委托管理器
class EventDelegationManager {
private:
    static std::map<std::string, std::vector<EventDelegationConfig>> delegationRegistry;
    static int delegationIdCounter;
    
public:
    // 注册事件委托
    static std::string registerDelegation(const EventDelegationConfig& config);
    
    // 获取或创建委托ID
    static std::string getOrCreateDelegationId(const std::string& parentSelector);
    
    // 合并委托配置
    static void mergeDelegation(const std::string& id, const EventDelegationConfig& config);
    
    // 生成委托初始化代码
    static std::string generateDelegationInit();
    
    // 清理
    static void clear();
};

// CHTL JS运行时代码生成器
class RuntimeCodeGenerator {
public:
    // 生成listen运行时支持
    static std::string generateListenRuntime();
    
    // 生成delegate运行时支持
    static std::string generateDelegateRuntime();
    
    // 生成animate运行时支持
    static std::string generateAnimateRuntime();
    
    // 生成完整的运行时代码
    static std::string generateFullRuntime();
};

} // namespace CHTLJSExtensions

} // namespace chtl

#endif // CHTL_SCRIPT_H