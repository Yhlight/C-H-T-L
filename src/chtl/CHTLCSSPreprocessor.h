#ifndef CHTL_CSS_PREPROCESSOR_H
#define CHTL_CSS_PREPROCESSOR_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <regex>
#include <stack>
#include "CHTLContext.h"
#include "CHTLTemplate.h"
#include "CHTLCustom.h"

namespace chtl {

// CSS预处理状态
enum class CSSPreprocessState {
    Normal,              // 普通CSS
    InStyleGroup,        // 在@Style使用中
    InVarGroup,         // 在@Var使用中
    InSelector,         // 在选择器中
    InDeclaration,      // 在声明中
    InValue            // 在属性值中
};

// CSS预处理上下文
class CSSPreprocessContext {
private:
    std::stack<CSSPreprocessState> stateStack;
    CSSPreprocessState currentState;
    
    // 当前处理的样式组或变量组
    std::string currentGroupName;
    std::string currentGroupType;
    
    // 位置信息
    size_t currentLine;
    size_t currentColumn;
    
public:
    CSSPreprocessContext();
    
    // 状态管理
    void pushState(CSSPreprocessState state);
    void popState();
    CSSPreprocessState getState() const { return currentState; }
    
    // 组信息管理
    void setCurrentGroup(const std::string& name, const std::string& type);
    void clearCurrentGroup();
    std::string getCurrentGroupName() const { return currentGroupName; }
    std::string getCurrentGroupType() const { return currentGroupType; }
    
    // 位置管理
    void updatePosition(size_t line, size_t col) { currentLine = line; currentColumn = col; }
    size_t getLine() const { return currentLine; }
    size_t getColumn() const { return currentColumn; }
};

// CSS预处理扫描器
class CSSPreprocessScanner {
private:
    std::string input;
    size_t position;
    size_t line;
    size_t column;
    
public:
    CSSPreprocessScanner(const std::string& css);
    
    // 扫描方法
    bool hasMore() const { return position < input.length(); }
    char peek() const;
    char advance();
    std::string peekWord();
    bool match(const std::string& expected);
    void skipWhitespace();
    void skipComment();
    
    // 位置信息
    size_t getPosition() const { return position; }
    size_t getLine() const { return line; }
    size_t getColumn() const { return column; }
    
    // 扫描特定模式
    std::string scanIdentifier();
    std::string scanUntil(char delimiter);
    std::string scanUntil(const std::string& delimiter);
    std::string scanBlock(char open, char close);
};

// CSS预处理器
class CSSPreprocessor {
private:
    std::shared_ptr<CHTLContext> context;
    std::shared_ptr<TemplateManager> templateManager;
    std::shared_ptr<CustomManager> customManager;
    
    // 预处理上下文
    CSSPreprocessContext preprocessContext;
    
    // 扫描器
    std::unique_ptr<CSSPreprocessScanner> scanner;
    
    // 输出
    std::stringstream output;
    
    // 已解析的样式组和变量组
    std::unordered_map<std::string, std::string> resolvedStyleGroups;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> resolvedVarGroups;
    
public:
    CSSPreprocessor(std::shared_ptr<CHTLContext> ctx);
    
    // 设置管理器
    void setTemplateManager(std::shared_ptr<TemplateManager> mgr) { templateManager = mgr; }
    void setCustomManager(std::shared_ptr<CustomManager> mgr) { customManager = mgr; }
    
    // 预处理CSS
    std::string preprocess(const std::string& css);
    
private:
    // 处理方法
    void processNormal();
    void processAtRule();
    void processStyleGroupUsage();
    void processVarGroupUsage();
    void processSelector();
    void processDeclaration();
    void processValue();
    
    // 解析和展开
    std::string expandStyleGroup(const std::string& name);
    std::string expandVarGroup(const std::string& name, const std::string& varName);
    std::string resolveVariable(const std::string& varGroup, const std::string& varName);
    
    // 辅助方法
    bool isStyleGroupUsage(const std::string& text);
    bool isVarGroupUsage(const std::string& text);
    std::pair<std::string, std::string> parseGroupUsage(const std::string& text);
    std::string processNestedGroups(const std::string& css);
    
    // 错误报告
    void reportError(const std::string& message);
    void reportWarning(const std::string& message);
};

// CSS增强编译器 - 包装原CSS编译器并添加预处理
class CHTLEnhancedCSSCompiler {
private:
    std::shared_ptr<CHTLContext> context;
    std::shared_ptr<CSSPreprocessor> preprocessor;
    std::shared_ptr<CSSCompiler> compiler;
    
    // 缓存预处理结果
    std::unordered_map<std::string, std::string> preprocessCache;
    
public:
    CHTLEnhancedCSSCompiler(std::shared_ptr<CHTLContext> ctx);
    
    // 设置管理器
    void setTemplateManager(std::shared_ptr<TemplateManager> mgr);
    void setCustomManager(std::shared_ptr<CustomManager> mgr);
    
    // 编译CSS（带预处理）
    std::string compile(const std::string& css);
    
    // 编译选项
    void setMinify(bool value);
    void setPreserveComments(bool value);
    
    // 验证
    bool validate(const std::string& css, std::vector<std::string>& errors);
    
    // 获取内部编译器（用于高级操作）
    std::shared_ptr<CSSCompiler> getInternalCompiler() { return compiler; }
};

// CSS上下文推导器
class CSSContextInferencer {
private:
    std::shared_ptr<CHTLContext> context;
    
    // 推导的上下文信息
    struct InferredContext {
        std::vector<std::string> availableStyleGroups;
        std::vector<std::string> availableVarGroups;
        std::unordered_map<std::string, std::string> inferredTypes;
        bool isInMediaQuery = false;
        std::string mediaQueryCondition;
    };
    
    InferredContext currentContext;
    
public:
    CSSContextInferencer(std::shared_ptr<CHTLContext> ctx);
    
    // 分析CSS并推导上下文
    InferredContext analyzeContext(const std::string& css, size_t position);
    
    // 获取可用的样式组和变量组
    std::vector<std::string> getAvailableStyleGroups() const;
    std::vector<std::string> getAvailableVarGroups() const;
    
    // 推导特定位置的期望类型
    std::string inferExpectedType(const std::string& css, size_t position);
    
private:
    // 分析方法
    void analyzeSelectors(const std::string& css);
    void analyzeDeclarations(const std::string& css);
    void analyzeMediaQueries(const std::string& css);
    
    // 推导规则
    bool isColorProperty(const std::string& property);
    bool isDimensionProperty(const std::string& property);
    bool isFontProperty(const std::string& property);
    

};

} // namespace chtl

#endif // CHTL_CSS_PREPROCESSOR_H