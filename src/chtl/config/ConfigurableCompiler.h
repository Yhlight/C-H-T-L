#pragma once

#include "ConfigurationSystem.h"
#include "ConfigurableLexer.h"
#include "ConfigurableParser.h"
#include "../generated/CHTLLexer.h"
#include "../generated/CHTLParser.h"
#include "antlr4-runtime.h"
#include <memory>
#include <string>

namespace chtl {
namespace config {

/**
 * 使用配置驱动体系的CHTL编译器
 */
class ConfigurableCompiler {
public:
    ConfigurableCompiler();
    ~ConfigurableCompiler() = default;
    
    /**
     * 编译CHTL源代码
     * @param source CHTL源代码
     * @param configPath 配置文件路径（可选）
     * @return 编译结果（HTML/CSS/JS）
     */
    std::string compile(const std::string& source, const std::string& configPath = "");
    
    /**
     * 从文件编译
     */
    std::string compileFile(const std::string& filePath, const std::string& configPath = "");
    
    /**
     * 获取配置系统
     */
    ConfigurationSystem& getConfig() { return ConfigurationSystem::getInstance(); }
    
    /**
     * 设置调试模式
     */
    void setDebugMode(bool debug);
    
private:
    /**
     * 提取并处理配置块
     */
    bool extractAndProcessConfiguration(const std::string& source);
    
    /**
     * 创建配置感知的Lexer
     */
    std::unique_ptr<antlr4::Lexer> createConfigurableLexer(antlr4::ANTLRInputStream& input);
    
    /**
     * 创建配置感知的Parser
     */
    std::unique_ptr<antlr4::Parser> createConfigurableParser(antlr4::CommonTokenStream& tokens);
    
    /**
     * 预处理源代码（提取配置等）
     */
    std::string preprocessSource(const std::string& source);
};

/**
 * 配置感知的CHTL Lexer
 */
class ConfigurableCHTLLexer : public ConfigurableLexerWrapper<CHTLLexer> {
public:
    ConfigurableCHTLLexer(antlr4::CharStream* input)
        : ConfigurableLexerWrapper<CHTLLexer>(input) {}
};

/**
 * 配置感知的CHTL Parser
 */
class ConfigurableCHTLParser : public ConfigurableParserWrapper<CHTLParser> {
public:
    ConfigurableCHTLParser(antlr4::TokenStream* input)
        : ConfigurableParserWrapper<CHTLParser>(input) {}
    
    /**
     * 重写的解析方法示例
     * 展示如何在语法规则中使用配置系统
     */
    CHTLParser::TemplateStyleContext* templateStyle() {
        // 原始规则: '[Template]' '@Style' IDENTIFIER
        
        if (getConfig().isNameGroupDisabled()) {
            // 使用原生行为
            return CHTLParser::templateStyle();
        }
        
        // 使用配置驱动的行为
        auto ctx = new CHTLParser::TemplateStyleContext(nullptr, 0);
        
        // 匹配 [Template] 或配置的变体
        if (!matchConfiguredKeyword("KEYWORD_TEMPLATE")) {
            throw antlr4::RecognitionException("Expected template keyword", 
                                              this, getInputStream(), ctx);
        }
        
        // 匹配 @Style 或配置的变体
        if (!matchConfiguredKeyword("TEMPLATE_STYLE")) {
            throw antlr4::RecognitionException("Expected style keyword", 
                                              this, getInputStream(), ctx);
        }
        
        // 匹配标识符
        match(CHTLParser::IDENTIFIER);
        
        return ctx;
    }
    
private:
    ConfigurationSystem& getConfig() { 
        return ConfigurationSystem::getInstance(); 
    }
    
    bool matchConfiguredKeyword(const std::string& keywordType) {
        ConfigurableParser adapter(this);
        return adapter.consumeKeyword(keywordType);
    }
};

/**
 * 编译器工厂
 * 根据配置创建合适的编译器实例
 */
class CompilerFactory {
public:
    /**
     * 创建编译器实例
     * @param useConfiguration 是否使用配置系统
     */
    static std::unique_ptr<ConfigurableCompiler> createCompiler(bool useConfiguration = true);
    
    /**
     * 创建带有预加载配置的编译器
     */
    static std::unique_ptr<ConfigurableCompiler> createCompilerWithConfig(
        const std::string& configPath);
};

} // namespace config
} // namespace chtl