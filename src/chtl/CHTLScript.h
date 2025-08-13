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
    // 局部脚本块（元素路径 -> 脚本块列表）
    std::unordered_map<std::string, std::vector<std::shared_ptr<ScriptBlock>>> localScripts;
    
    // 全局脚本块
    std::vector<std::shared_ptr<ScriptBlock>> globalScripts;
    
    // 自动生成的作用域ID映射
    std::unordered_map<std::string, std::string> scopeIdMap;
    int scopeIdCounter;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
public:
    ScriptManager(std::shared_ptr<CHTLContext> ctx)
        : context(ctx), scopeIdCounter(0) {}
    
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
    CHTLGenerator& generator;
    
public:
    ScriptProcessor(ScriptManager& mgr, CHTLGenerator& gen)
        : manager(mgr), generator(gen) {}
    
    // 处理脚本块
    void processScriptBlock(const std::string& content, const std::string& currentScope);
    
    // 提取并处理增强选择器
    std::string processEnhancedSelectors(const std::string& script, std::vector<EnhancedSelector>& selectors);
    
    // 判断脚本类型
    ScriptType detectScriptType(const std::string& content);
    
    // 分离JS和CHTL JS代码
    std::vector<std::pair<std::string, ScriptType>> separateScriptTypes(const std::string& content);
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
}

} // namespace chtl

#endif // CHTL_SCRIPT_H