#ifndef CHTL_CJMOD_ENHANCED_H
#define CHTL_CJMOD_ENHANCED_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <variant>

namespace chtl {
namespace cjmod {

// 前向声明
class TokenStream;
class ASTNode;

// 1. 基于 Token 的转换器
class TokenTransformer {
public:
    virtual ~TokenTransformer() = default;
    
    // 处理 token 流
    virtual bool canTransform(const TokenStream& tokens, size_t position) const = 0;
    virtual size_t transform(TokenStream& tokens, size_t position) = 0;
};

// 2. 基于 AST 的转换器（虽然 CJmod 不直接访问 CHTL AST，但可以构建 JS AST）
class JSASTTransformer {
public:
    virtual ~JSASTTransformer() = default;
    
    // 访问者模式处理 JavaScript AST
    virtual void visitIdentifier(const std::string& name) {}
    virtual void visitBinaryOp(const std::string& op, ASTNode* left, ASTNode* right) {}
    virtual void visitFunctionCall(const std::string& name, const std::vector<ASTNode*>& args) {}
};

// 3. 基于状态机的转换器
class StateMachineTransformer {
public:
    enum State {
        INITIAL,
        IN_REACTIVE_DECL,
        IN_COMPUTED_EXPR,
        IN_WATCH_BLOCK
    };
    
    virtual ~StateMachineTransformer() = default;
    
    // 状态转换
    virtual State processChar(char c, State currentState) = 0;
    virtual std::string getOutput(State state) = 0;
};

// 4. 基于语法树模式匹配的转换器
struct PatternNode {
    enum Type { LITERAL, WILDCARD, CAPTURE, REPEAT };
    Type type;
    std::string value;
    std::vector<std::unique_ptr<PatternNode>> children;
};

class PatternMatcher {
public:
    virtual ~PatternMatcher() = default;
    
    // 模式匹配
    virtual bool match(const std::string& code, const PatternNode& pattern) = 0;
    virtual std::string replace(const std::string& code, const PatternNode& pattern, 
                               const std::string& replacement) = 0;
};

// 5. 增强的扫描规则
struct EnhancedScanRule {
    std::string name;
    
    // 支持多种匹配方式
    std::variant<
        std::regex,                                          // 正则表达式
        std::function<bool(const std::string&, size_t)>,   // 自定义匹配函数
        std::unique_ptr<TokenTransformer>,                  // Token 转换器
        std::unique_ptr<PatternNode>                        // 模式树
    > matcher;
    
    // 支持多种替换方式
    std::variant<
        std::string,                                         // 简单字符串替换
        std::function<std::string(const std::smatch&)>,     // 基于匹配的函数
        std::function<std::string(const std::string&)>      // 完全自定义
    > replacer;
    
    int priority;
};

// 6. 优化的单次扫描处理器
class SinglePassProcessor {
public:
    struct RuleMatch {
        size_t start;
        size_t end;
        std::string replacement;
        int priority;
    };
    
    // 单次扫描收集所有匹配
    std::vector<RuleMatch> collectAllMatches(const std::string& code, 
                                            const std::vector<EnhancedScanRule>& rules);
    
    // 解决冲突并应用替换
    std::string applyReplacements(const std::string& code, 
                                 std::vector<RuleMatch>& matches);
};

// 7. 增量处理器（用于实时编辑）
class IncrementalProcessor {
public:
    // 只处理变更的部分
    void updateRegion(size_t start, size_t end, const std::string& newContent);
    
    // 获取更新后的结果
    std::string getProcessedCode() const;
    
private:
    std::string cachedCode_;
    std::vector<RuleMatch> cachedMatches_;
};

// 8. 并行处理器（用于大文件）
class ParallelProcessor {
public:
    // 将代码分块并行处理
    std::string processInParallel(const std::string& code, 
                                 const std::vector<EnhancedScanRule>& rules,
                                 size_t threadCount = 4);
};

// 9. 流式处理器（用于超大文件）
class StreamProcessor {
public:
    // 流式处理，不需要加载整个文件
    void processStream(std::istream& input, std::ostream& output,
                      const std::vector<EnhancedScanRule>& rules);
};

} // namespace cjmod
} // namespace chtl

#endif // CHTL_CJMOD_ENHANCED_H