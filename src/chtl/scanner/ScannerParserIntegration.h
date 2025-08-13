#pragma once

#include "../CHTLUnifiedScanner.h"
#include "../generated/CHTLLexer.h"
#include "../generated/CHTLParser.h"
#include "../generated/CSSLexer.h"
#include "../generated/CSSParser.h"
#include "../generated/JSLexer.h"
#include "../generated/JSParser.h"
#include "../generated/CHTLJSLexer.h"
#include "../generated/CHTLJSParser.h"
#include "antlr4-runtime.h"
#include <memory>
#include <vector>

namespace chtl {
namespace scanner {

/**
 * 扫描结果片段
 */
struct ScanFragment {
    Token token;
    std::string content;
    LanguageContext language;
    size_t startLine;
    size_t startColumn;
    size_t endLine;
    size_t endColumn;
};

/**
 * 解析结果
 */
struct ParseResult {
    bool success;
    std::string errorMessage;
    
    // 各语言的解析树
    antlr4::tree::ParseTree* chtlTree = nullptr;
    antlr4::tree::ParseTree* cssTree = nullptr;
    antlr4::tree::ParseTree* jsTree = nullptr;
    antlr4::tree::ParseTree* chtljsTree = nullptr;
    
    // 解析的片段信息
    std::vector<ScanFragment> fragments;
};

/**
 * Scanner与Parser的集成器
 * 负责将Scanner的输出转换为Parser的输入
 */
class ScannerParserIntegration {
public:
    ScannerParserIntegration(std::shared_ptr<CHTLContext> context);
    ~ScannerParserIntegration();
    
    /**
     * 解析CHTL源代码
     * @param source 源代码
     * @param configPath 配置文件路径（可选）
     * @return 解析结果
     */
    ParseResult parse(const std::string& source, const std::string& configPath = "");
    
    /**
     * 从Scanner结果构建解析树
     */
    ParseResult parseFromScanner(CHTLUnifiedScanner& scanner);
    
    /**
     * 设置是否启用配置驱动
     */
    void setConfigurationEnabled(bool enabled) { useConfiguration = enabled; }
    
    /**
     * 获取错误监听器
     */
    antlr4::ANTLRErrorListener* getErrorListener() { return errorListener.get(); }
    
private:
    std::shared_ptr<CHTLContext> context;
    bool useConfiguration = true;
    std::unique_ptr<antlr4::ANTLRErrorListener> errorListener;
    
    // 解析器实例
    std::unique_ptr<CHTLParser> chtlParser;
    std::unique_ptr<CSSParser> cssParser;
    std::unique_ptr<JSParser> jsParser;
    std::unique_ptr<CHTLJSParser> chtljsParser;
    
    /**
     * 从片段创建ANTLR输入流
     */
    std::unique_ptr<antlr4::ANTLRInputStream> createInputStream(
        const std::vector<ScanFragment>& fragments,
        LanguageContext targetLanguage
    );
    
    /**
     * 解析CHTL片段
     */
    antlr4::tree::ParseTree* parseCHTLFragments(
        const std::vector<ScanFragment>& fragments
    );
    
    /**
     * 解析CSS片段
     */
    antlr4::tree::ParseTree* parseCSSFragments(
        const std::vector<ScanFragment>& fragments
    );
    
    /**
     * 解析JS片段
     */
    antlr4::tree::ParseTree* parseJSFragments(
        const std::vector<ScanFragment>& fragments
    );
    
    /**
     * 解析CHTL JS片段
     */
    antlr4::tree::ParseTree* parseCHTLJSFragments(
        const std::vector<ScanFragment>& fragments
    );
    
    /**
     * 合并同语言的连续片段
     */
    std::vector<ScanFragment> mergeFragments(
        const std::vector<Token>& tokens,
        const std::string& source
    );
    
    /**
     * 按语言分组片段
     */
    std::unordered_map<LanguageContext, std::vector<ScanFragment>> 
    groupFragmentsByLanguage(const std::vector<ScanFragment>& fragments);
};

/**
 * 自定义错误监听器
 */
class IntegrationErrorListener : public antlr4::BaseErrorListener {
public:
    void syntaxError(
        antlr4::Recognizer* recognizer,
        antlr4::Token* offendingSymbol,
        size_t line,
        size_t charPositionInLine,
        const std::string& msg,
        std::exception_ptr e
    ) override;
    
    bool hasErrors() const { return !errors.empty(); }
    const std::vector<std::string>& getErrors() const { return errors; }
    void clearErrors() { errors.clear(); }
    
private:
    std::vector<std::string> errors;
};

} // namespace scanner
} // namespace chtl