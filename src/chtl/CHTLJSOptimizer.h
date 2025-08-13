#ifndef CHTL_JS_OPTIMIZER_H
#define CHTL_JS_OPTIMIZER_H

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
#include "antlr4-runtime.h"
#include "generated/JSLexer.h"
#include "generated/JSParser.h"
#include "generated/JSParserBaseVisitor.h"

namespace chtl {

// JS优化选项
struct JSOptimizationOptions {
    bool enableObfuscation = true;      // 启用混淆
    bool minifyCode = true;             // 压缩代码
    bool removeComments = true;         // 移除注释
    bool renameVariables = true;        // 重命名变量
    bool preserveKeywords = true;       // 保留关键字（如document, window等）
    int obfuscationLevel = 2;           // 混淆级别（1-3）
};

// 变量作用域信息
struct VariableScope {
    std::string originalName;
    std::string obfuscatedName;
    int scopeLevel;
    bool isGlobal;
    bool isParameter;
    bool isFunction;
};

// JS变量混淆器
class JSVariableObfuscator : public JSParserBaseVisitor {
public:
    explicit JSVariableObfuscator(const JSOptimizationOptions& options);
    
    // 执行混淆
    std::string obfuscate(const std::string& jsCode);
    
    // ANTLR访问者方法
    antlrcpp::Any visitProgram(JSParser::ProgramContext* ctx) override;
    antlrcpp::Any visitVariableDeclaration(JSParser::VariableDeclarationContext* ctx) override;
    antlrcpp::Any visitFunctionDeclaration(JSParser::FunctionDeclarationContext* ctx) override;
    antlrcpp::Any visitFormalParameterList(JSParser::FormalParameterListContext* ctx) override;
    antlrcpp::Any visitIdentifierExpression(JSParser::IdentifierExpressionContext* ctx) override;
    antlrcpp::Any visitBlock(JSParser::BlockContext* ctx) override;
    
private:
    JSOptimizationOptions options;
    
    // 作用域管理
    int currentScopeLevel = 0;
    std::vector<std::unordered_map<std::string, VariableScope>> scopeStack;
    
    // 全局保留标识符
    std::unordered_set<std::string> reservedIdentifiers;
    
    // 混淆名称生成
    std::unordered_map<std::string, std::string> globalObfuscationMap;
    std::mt19937 randomEngine;
    int nameCounter = 0;
    
    // 辅助方法
    void enterScope();
    void exitScope();
    void addVariable(const std::string& name, bool isParameter = false, bool isFunction = false);
    std::string getObfuscatedName(const std::string& originalName);
    std::string generateObfuscatedName();
    bool isReserved(const std::string& name) const;
    void initializeReservedIdentifiers();
    std::string rebuildCode(antlr4::tree::ParseTree* tree, 
                          antlr4::CommonTokenStream* tokens,
                          const std::string& jsCode);
    
    // 名称生成策略
    std::string generateShortName(int index);
    std::string generateMediumName(int index);
    std::string generateLongName(int index);
};

// JS优化器主类
class JSOptimizer {
public:
    explicit JSOptimizer(const JSOptimizationOptions& options = {});
    
    // 优化JS代码
    std::string optimize(const std::string& jsCode);
    
    // 单独的优化步骤
    std::string removeComments(const std::string& code);
    std::string minifyWhitespace(const std::string& code);
    std::string obfuscateVariables(const std::string& code);
    
    // 获取优化统计
    struct OptimizationStats {
        size_t originalSize;
        size_t optimizedSize;
        int variablesRenamed;
        int commentsRemoved;
        double compressionRatio;
    };
    
    OptimizationStats getStats() const { return stats; }
    
private:
    JSOptimizationOptions options;
    OptimizationStats stats;
    std::unique_ptr<JSVariableObfuscator> obfuscator;
    
    // 辅助方法
    int countVariables(const std::string& code);
};

} // namespace chtl

#endif // CHTL_JS_OPTIMIZER_H