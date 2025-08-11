#ifndef CHTL_CJMOD_EXTENSION_FACTORY_H
#define CHTL_CJMOD_EXTENSION_FACTORY_H

#include <memory>
#include <string>
#include <map>
#include <functional>
#include "CJmodManager.h"

namespace chtl {

// 方法扩展
class MethodExtension : public ICJmodExtension {
public:
    struct MethodInfo {
        std::string name;
        std::string implementation;
        std::vector<std::string> parameters;
        bool isAsync;
    };
    
    MethodExtension(const std::vector<MethodInfo>& methods) : methods_(methods) {}
    
    void transformAST(std::shared_ptr<Node> ast) override;
    std::string getRuntimeCode() const override;
    
private:
    std::vector<MethodInfo> methods_;
    std::string generateMethodWrapper(const MethodInfo& method) const;
};

// 操作符扩展
class OperatorExtension : public ICJmodExtension {
public:
    struct OperatorInfo {
        std::string symbol;
        std::string implementation;
        int precedence;
        bool isUnary;
    };
    
    OperatorExtension(const std::vector<OperatorInfo>& operators) : operators_(operators) {}
    
    void onParse(StandardParser* parser) override;
    void transformAST(std::shared_ptr<Node> ast) override;
    
private:
    std::vector<OperatorInfo> operators_;
};

// 选择器扩展
class SelectorExtension : public ICJmodExtension {
public:
    struct SelectorInfo {
        std::string pattern;      // 例如: "::visible"
        std::string transformer;  // 转换函数
    };
    
    SelectorExtension(const std::vector<SelectorInfo>& selectors) : selectors_(selectors) {}
    
    void transformAST(std::shared_ptr<Node> ast) override;
    
private:
    std::vector<SelectorInfo> selectors_;
};

// 语法糖扩展
class SyntaxExtension : public ICJmodExtension {
public:
    struct SyntaxRule {
        std::string pattern;      // 正则表达式
        std::string replacement;  // 替换模板
        std::string context;      // 应用上下文
    };
    
    SyntaxExtension(const std::vector<SyntaxRule>& rules) : rules_(rules) {}
    
    void onParse(StandardParser* parser) override;
    std::string transformScript(const std::string& script) const;
    
private:
    std::vector<SyntaxRule> rules_;
};

// 组合扩展（可以包含多种扩展类型）
class CompositeExtension : public ICJmodExtension {
public:
    void addExtension(std::unique_ptr<ICJmodExtension> extension) {
        extensions_.push_back(std::move(extension));
    }
    
    void onParse(StandardParser* parser) override {
        for (auto& ext : extensions_) {
            ext->onParse(parser);
        }
    }
    
    void transformAST(std::shared_ptr<Node> ast) override {
        for (auto& ext : extensions_) {
            ext->transformAST(ast);
        }
    }
    
    void onGenerate(WebGenerator* generator) override {
        for (auto& ext : extensions_) {
            ext->onGenerate(generator);
        }
    }
    
    std::string getRuntimeCode() const override {
        std::string combined;
        for (const auto& ext : extensions_) {
            combined += ext->getRuntimeCode() + "\n";
        }
        return combined;
    }
    
private:
    std::vector<std::unique_ptr<ICJmodExtension>> extensions_;
};

// 扩展工厂
class CJmodExtensionFactory {
public:
    static std::unique_ptr<ICJmodExtension> createFromDefinition(const CJmodDefinition& def);
    
    // 注册自定义扩展创建器
    static void registerExtensionCreator(
        const std::string& type,
        std::function<std::unique_ptr<ICJmodExtension>(const CJmodDefinition&)> creator
    );
    
private:
    static std::map<std::string, std::function<std::unique_ptr<ICJmodExtension>(const CJmodDefinition&)>> creators_;
    
    static std::unique_ptr<MethodExtension> createMethodExtension(const CJmodDefinition& def);
    static std::unique_ptr<OperatorExtension> createOperatorExtension(const CJmodDefinition& def);
    static std::unique_ptr<SelectorExtension> createSelectorExtension(const CJmodDefinition& def);
    static std::unique_ptr<SyntaxExtension> createSyntaxExtension(const CJmodDefinition& def);
};

} // namespace chtl

#endif // CHTL_CJMOD_EXTENSION_FACTORY_H