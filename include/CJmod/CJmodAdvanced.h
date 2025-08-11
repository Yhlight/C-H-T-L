#ifndef CHTL_CJMOD_ADVANCED_H
#define CHTL_CJMOD_ADVANCED_H

#include <string>
#include <memory>
#include <functional>
#include <any>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Generator/WebGenerator.h"

namespace chtl {
namespace cjmod {

// CJmod 上下文 - 提供对编译器内部的访问
class CJmodContext {
public:
    // 词法分析器钩子
    virtual void registerToken(const std::string& pattern, TokenType type) = 0;
    virtual void modifyTokenizer(std::function<void(StandardLexer*)> modifier) = 0;
    
    // 语法分析器钩子
    virtual void registerKeyword(const std::string& keyword, 
                                std::function<std::shared_ptr<Node>(StandardParser*)> parser) = 0;
    virtual void registerNodeType(const std::string& typeName) = 0;
    virtual void modifyParser(std::function<void(StandardParser*)> modifier) = 0;
    
    // 生成器钩子
    virtual void registerGenerator(NodeType type, 
                                  std::function<void(WebGenerator*, const std::shared_ptr<Node>&)> generator) = 0;
    virtual void modifyGenerator(std::function<void(WebGenerator*)> modifier) = 0;
    
    // 全局状态管理
    virtual void setState(const std::string& key, std::any value) = 0;
    virtual std::any getState(const std::string& key) = 0;
    virtual bool hasState(const std::string& key) = 0;
    
    // 包含其他文件
    virtual void includeHeader(const std::string& header) = 0;
    virtual void includeSource(const std::string& source) = 0;
    
    // 访问编译器内部
    virtual StandardLexer* getLexer() = 0;
    virtual StandardParser* getParser() = 0;
    virtual WebGenerator* getGenerator() = 0;
    virtual std::shared_ptr<StandardContext> getCompilerContext() = 0;
};

// 高级 CJmod 接口
class ICJmodAdvanced {
public:
    virtual ~ICJmodAdvanced() = default;
    
    // 基本信息
    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    
    // 初始化 - 可以注册各种扩展
    virtual void initialize(CJmodContext* context) = 0;
    
    // 编译阶段钩子
    virtual void onBeforeLexing(const std::string& source, CJmodContext* context) {}
    virtual void onAfterLexing(const std::vector<Token>& tokens, CJmodContext* context) {}
    virtual void onBeforeParsing(CJmodContext* context) {}
    virtual void onAfterParsing(std::shared_ptr<Node> ast, CJmodContext* context) {}
    virtual void onBeforeGeneration(CJmodContext* context) {}
    virtual void onAfterGeneration(const GeneratedCode& code, CJmodContext* context) {}
    
    // 依赖管理
    virtual std::vector<std::string> getDependencies() const { return {}; }
};

// 创建自定义节点类型的基类
class CustomNode : public Node {
protected:
    std::string customType_;
    std::map<std::string, std::any> customData_;
    
public:
    CustomNode(const std::string& customType) : Node(NodeType::CUSTOM), customType_(customType) {}
    
    std::string getCustomType() const { return customType_; }
    void setCustomData(const std::string& key, std::any value) { customData_[key] = value; }
    std::any getCustomData(const std::string& key) const {
        auto it = customData_.find(key);
        return it != customData_.end() ? it->second : std::any{};
    }
};

// 宏来简化创建
#define CJMOD_ADVANCED(name, version) \
    class name##Module : public ICJmodAdvanced { \
    public: \
        std::string getName() const override { return #name; } \
        std::string getVersion() const override { return version; }

#define CJMOD_INIT(body) \
        void initialize(CJmodContext* ctx) override { \
            body \
        }

#define CJMOD_END() \
    };

// 辅助函数
namespace helpers {
    // 创建自定义解析器
    inline auto createKeywordParser(const std::string& keyword, 
                                   std::function<std::shared_ptr<Node>(StandardParser*, const Token&)> handler) {
        return [keyword, handler](StandardParser* parser) -> std::shared_ptr<Node> {
            if (parser->getCurrentToken().value == keyword) {
                auto token = parser->getCurrentToken();
                parser->advance();  // 消费关键字
                return handler(parser, token);
            }
            return nullptr;
        };
    }
    
    // 创建自定义生成器
    inline auto createNodeGenerator(std::function<std::string(const CustomNode*)> handler) {
        return [handler](WebGenerator* gen, const std::shared_ptr<Node>& node) {
            if (auto customNode = std::dynamic_pointer_cast<CustomNode>(node)) {
                std::string code = handler(customNode.get());
                gen->appendToCurrentCollector(code);
            }
        };
    }
}

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_ADVANCED_H