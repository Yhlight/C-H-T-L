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

// 原始嵌入定义
class OriginDefinition {
protected:
    std::string name;           // 定义名称（用于增强原始嵌入）
    std::string syntaxType;     // 语法类型标记（@Html、@Style、@JavaScript）仅用于语法
    std::string content;        // 原始内容
    bool isNamed;              // 是否是命名的原始嵌入
    
public:
    OriginDefinition(const std::string& name = "", const std::string& type = "", bool named = false)
        : name(name), syntaxType(type), isNamed(named) {}
    
    virtual ~OriginDefinition() = default;
    
    // 获取器
    const std::string& getName() const { return name; }
    const std::string& getSyntaxType() const { return syntaxType; }
    const std::string& getContent() const { return content; }
    bool hasName() const { return isNamed; }
    
    // 设置内容
    void setContent(const std::string& rawContent) { content = rawContent; }
    void appendContent(const std::string& moreContent) { content += moreContent; }
    
    // 生成原始代码 - 原原本本输出
    virtual void generate(CHTLGenerator& generator) const;
};

// 原始嵌入管理器
class OriginManager {
private:
    // 存储命名的原始嵌入（不区分类型）
    std::unordered_map<std::string, std::shared_ptr<OriginDefinition>> namedOrigins;
    
    // 临时存储（用于即时原始嵌入）
    std::vector<std::shared_ptr<OriginDefinition>> immediateOrigins;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
public:
    OriginManager(std::shared_ptr<CHTLContext> ctx)
        : context(ctx) {}
    
    // 注册命名的原始嵌入
    bool registerNamedOrigin(const std::string& name, std::shared_ptr<OriginDefinition> origin);
    
    // 查找命名的原始嵌入
    std::shared_ptr<OriginDefinition> findNamedOrigin(const std::string& name) const;
    
    // 使用命名的原始嵌入
    bool useNamedOrigin(const std::string& name, CHTLGenerator& generator);
    
    // 添加即时原始嵌入
    void addImmediateOrigin(std::shared_ptr<OriginDefinition> origin);
    
    // 生成所有即时原始嵌入
    void generateImmediateOrigins(CHTLGenerator& generator);
    
    // 清理即时原始嵌入
    void clearImmediateOrigins() { immediateOrigins.clear(); }
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
        std::string syntaxType;  // @Html、@Style、@JavaScript（仅语法标记）
        std::string name;
        bool isNamed;
        bool isUsage;  // true表示使用，false表示定义
    };
    
    OriginDeclaration parseOriginDeclaration(const std::string& declaration);
    
    // 创建原始嵌入实例
    std::shared_ptr<OriginDefinition> createOriginInstance(const OriginDeclaration& decl);
    
    // 处理原始内容 - 直接存储，不做任何处理
    void processOriginContent(std::shared_ptr<OriginDefinition> origin, const std::string& content);
};

// 辅助函数
namespace OriginHelper {
    // 解析原始嵌入语法
    // [Origin] @Html -> ("@Html", "")
    // [Origin] @Style myStyle -> ("@Style", "myStyle")
    std::pair<std::string, std::string> parseOriginSyntax(const std::string& syntax);
    
    // 检查是否是原始嵌入语句
    bool isOriginStatement(const std::string& statement);
    
    // 提取原始内容（去除大括号）
    std::string extractRawContent(const std::string& wrappedContent);
}

} // namespace chtl

#endif // CHTL_ORIGIN_H