#ifndef CHTL_ORIGIN_H
#define CHTL_ORIGIN_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "CHTLContext.h"

namespace chtl {

// 前向声明
class CHTLGenerator;

// 原始嵌入类型
enum class OriginType {
    HTML,       // @Html
    STYLE,      // @Style
    JAVASCRIPT  // @JavaScript
};

// 原始嵌入定义
class OriginDefinition {
protected:
    std::string name;           // 定义名称（用于增强原始嵌入）
    OriginType type;           // 嵌入类型
    std::string content;       // 原始内容
    bool isNamed;             // 是否是命名的原始嵌入
    
    // 元数据
    std::string sourceFile;
    int startLine;
    int endLine;
    
public:
    OriginDefinition(const std::string& name, OriginType type, bool named = false)
        : name(name), type(type), isNamed(named), startLine(0), endLine(0) {}
    
    virtual ~OriginDefinition() = default;
    
    // 获取器
    const std::string& getName() const { return name; }
    OriginType getType() const { return type; }
    const std::string& getContent() const { return content; }
    bool hasName() const { return isNamed; }
    
    // 设置内容
    void setContent(const std::string& rawContent) { content = rawContent; }
    void appendContent(const std::string& moreContent) { content += moreContent; }
    
    // 元数据
    void setSourceLocation(const std::string& file, int start, int end) {
        sourceFile = file;
        startLine = start;
        endLine = end;
    }
    
    // 生成原始代码
    virtual void generate(CHTLGenerator& generator) const;
    
    // 获取类型字符串
    static std::string typeToString(OriginType type);
    static OriginType stringToType(const std::string& typeStr);
};

// HTML原始嵌入
class OriginHtml : public OriginDefinition {
private:
    bool shouldIndent;  // 是否应该缩进内容
    
public:
    OriginHtml(const std::string& name = "", bool named = false)
        : OriginDefinition(name, OriginType::HTML, named), shouldIndent(true) {}
    
    void setShouldIndent(bool indent) { shouldIndent = indent; }
    
    void generate(CHTLGenerator& generator) const override;
    
    // 验证HTML内容
    bool validateContent() const;
};

// CSS原始嵌入
class OriginStyle : public OriginDefinition {
private:
    bool isGlobal;      // 是否是全局样式
    bool wrapInStyle;   // 是否需要包装在<style>标签中
    
public:
    OriginStyle(const std::string& name = "", bool named = false)
        : OriginDefinition(name, OriginType::STYLE, named), 
          isGlobal(true), wrapInStyle(true) {}
    
    void setGlobal(bool global) { isGlobal = global; }
    void setWrapInStyle(bool wrap) { wrapInStyle = wrap; }
    
    void generate(CHTLGenerator& generator) const override;
    
    // 验证CSS内容
    bool validateContent() const;
};

// JavaScript原始嵌入
class OriginJavaScript : public OriginDefinition {
private:
    bool isModule;      // 是否是ES6模块
    bool wrapInScript;  // 是否需要包装在<script>标签中
    bool defer;         // 是否延迟执行
    bool async;         // 是否异步执行
    
public:
    OriginJavaScript(const std::string& name = "", bool named = false)
        : OriginDefinition(name, OriginType::JAVASCRIPT, named),
          isModule(false), wrapInScript(true), defer(false), async(false) {}
    
    void setModule(bool module) { isModule = module; }
    void setWrapInScript(bool wrap) { wrapInScript = wrap; }
    void setDefer(bool d) { defer = d; }
    void setAsync(bool a) { async = a; }
    
    void generate(CHTLGenerator& generator) const override;
    
    // 验证JavaScript内容
    bool validateContent() const;
};

// 原始嵌入管理器
class OriginManager {
private:
    // 存储命名的原始嵌入
    std::unordered_map<std::string, std::shared_ptr<OriginHtml>> namedHtmlOrigins;
    std::unordered_map<std::string, std::shared_ptr<OriginStyle>> namedStyleOrigins;
    std::unordered_map<std::string, std::shared_ptr<OriginJavaScript>> namedJsOrigins;
    
    // 临时存储（用于即时原始嵌入）
    std::vector<std::shared_ptr<OriginDefinition>> immediateOrigins;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
    // 配置
    bool allowUnsafeContent;    // 是否允许不安全的内容
    bool validateContent;       // 是否验证内容
    
public:
    OriginManager(std::shared_ptr<CHTLContext> ctx)
        : context(ctx), allowUnsafeContent(false), validateContent(true) {}
    
    // 注册命名的原始嵌入
    bool registerNamedHtml(const std::string& name, std::shared_ptr<OriginHtml> origin);
    bool registerNamedStyle(const std::string& name, std::shared_ptr<OriginStyle> origin);
    bool registerNamedJavaScript(const std::string& name, std::shared_ptr<OriginJavaScript> origin);
    
    // 查找命名的原始嵌入
    std::shared_ptr<OriginHtml> findNamedHtml(const std::string& name) const;
    std::shared_ptr<OriginStyle> findNamedStyle(const std::string& name) const;
    std::shared_ptr<OriginJavaScript> findNamedJavaScript(const std::string& name) const;
    
    // 使用命名的原始嵌入
    bool useNamedOrigin(const std::string& type, const std::string& name, CHTLGenerator& generator);
    
    // 添加即时原始嵌入
    void addImmediateOrigin(std::shared_ptr<OriginDefinition> origin);
    
    // 生成所有即时原始嵌入
    void generateImmediateOrigins(CHTLGenerator& generator);
    
    // 清理即时原始嵌入
    void clearImmediateOrigins() { immediateOrigins.clear(); }
    
    // 配置
    void setAllowUnsafeContent(bool allow) { allowUnsafeContent = allow; }
    void setValidateContent(bool validate) { validateContent = validate; }
    
    // 验证原始内容
    bool validateOriginContent(const OriginDefinition& origin) const;
};

// 原始嵌入处理器
class OriginProcessor {
private:
    OriginManager& manager;
    CHTLGenerator& generator;
    
public:
    OriginProcessor(OriginManager& mgr, CHTLGenerator& gen)
        : manager(mgr), generator(gen) {}
    
    // 处理原始嵌入语句
    bool processOriginStatement(const std::string& statement);
    
    // 解析原始嵌入声明
    struct OriginDeclaration {
        OriginType type;
        std::string name;
        bool isNamed;
        bool isUsage;  // true表示使用，false表示定义
    };
    
    OriginDeclaration parseOriginDeclaration(const std::string& declaration);
    
    // 创建原始嵌入实例
    std::shared_ptr<OriginDefinition> createOriginInstance(const OriginDeclaration& decl);
    
    // 处理原始内容
    void processOriginContent(std::shared_ptr<OriginDefinition> origin, const std::string& content);
};

// 原始内容验证器
class OriginValidator {
public:
    // 验证HTML内容
    static bool validateHtml(const std::string& content, std::vector<std::string>& errors);
    
    // 验证CSS内容
    static bool validateCss(const std::string& content, std::vector<std::string>& errors);
    
    // 验证JavaScript内容
    static bool validateJavaScript(const std::string& content, std::vector<std::string>& errors);
    
    // 检查危险内容
    static bool checkForDangerousContent(const std::string& content, OriginType type);
    
    // 基本语法检查
    static bool checkBasicSyntax(const std::string& content, OriginType type);
};

// 原始内容转换器
class OriginTransformer {
public:
    // 转换选项
    struct TransformOptions {
        bool escapeSpecialChars = false;
        bool addIndentation = true;
        std::string indentString = "  ";
        int baseIndentLevel = 0;
    };
    
    // 转换原始内容以适应输出
    static std::string transformContent(const std::string& content, 
                                      OriginType type,
                                      const TransformOptions& options);
    
    // 添加缩进
    static std::string addIndentation(const std::string& content, 
                                     const std::string& indent,
                                     int level);
    
    // 转义特殊字符
    static std::string escapeForHtml(const std::string& content);
    
    // 清理内容
    static std::string cleanupContent(const std::string& content, OriginType type);
};

// 辅助函数
namespace OriginHelper {
    // 解析原始嵌入语法
    // [Origin] @Html -> ("Html", "")
    // [Origin] @Style myStyle -> ("Style", "myStyle")
    std::pair<std::string, std::string> parseOriginSyntax(const std::string& syntax);
    
    // 检查是否是原始嵌入语句
    bool isOriginStatement(const std::string& statement);
    
    // 提取原始内容（去除包装）
    std::string extractRawContent(const std::string& wrappedContent);
    
    // 生成原始嵌入的全缀名
    std::string buildOriginFullName(OriginType type, const std::string& name);
}

} // namespace chtl

#endif // CHTL_ORIGIN_H