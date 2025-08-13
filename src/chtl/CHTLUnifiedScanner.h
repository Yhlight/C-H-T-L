#ifndef CHTL_UNIFIED_SCANNER_H
#define CHTL_UNIFIED_SCANNER_H

#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <unordered_map>
#include <functional>
#include "CHTLContext.h"

namespace chtl {

// 扫描器状态
enum class ScannerState {
    Normal,              // 普通文本
    InElement,          // 在CHTL元素中
    InAttribute,        // 在属性中
    InStyleBlock,       // 在style块中
    InScriptBlock,      // 在script块中
    InComment,          // 在注释中
    InGenerativeComment,// 在生成性注释中（--）
    InString,           // 在字符串中
    InTemplate,         // 在模板定义中
    InImport,          // 在导入语句中
    InOrigin           // 在原始嵌入中
};

// 语言上下文
enum class LanguageContext {
    CHTL,      // CHTL语法上下文
    HTML,      // HTML上下文
    CSS,       // CSS上下文
    JavaScript // JavaScript上下文
};

// 扫描令牌类型
enum class TokenType {
    Text,                  // 普通文本
    ElementStart,         // 元素开始
    ElementEnd,           // 元素结束
    AttributeName,        // 属性名
    AttributeValue,       // 属性值
    StyleGroupUsage,      // @Style使用
    VarGroupUsage,        // VarGroup(name)使用
    GenerativeComment,    // --注释
    NormalComment,        // //或/**/注释
    ScriptContent,        // 脚本内容
    StyleContent,         // 样式内容
    TemplateDefinition,   // 模板定义
    ImportStatement,      // 导入语句
    OriginContent,       // 原始内容
    Whitespace,          // 空白
    NewLine,             // 换行
    EOF                  // 文件结束
};

// 扫描令牌
struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t column;
    size_t position;
    LanguageContext context;
    
    Token(TokenType t, const std::string& v, size_t l, size_t c, size_t p, LanguageContext ctx)
        : type(t), value(v), line(l), column(c), position(p), context(ctx) {}
};

// 扫描器配置
struct ScannerConfig {
    bool processGenerativeComments = true;  // 处理--注释
    bool expandStyleGroups = true;          // 展开样式组
    bool expandVarGroups = true;            // 展开变量组
    bool validateSyntax = true;             // 验证语法
    bool preserveWhitespace = true;         // 保留空白
    bool trackContext = true;               // 跟踪上下文
};

// 统一扫描器
class CHTLUnifiedScanner {
private:
    std::string input;
    size_t position;
    size_t line;
    size_t column;
    
    // 状态管理
    std::stack<ScannerState> stateStack;
    ScannerState currentState;
    LanguageContext currentContext;
    
    // 配置
    ScannerConfig config;
    
    // 上下文
    std::shared_ptr<CHTLContext> context;
    
    // 令牌缓冲
    std::vector<Token> tokens;
    size_t currentTokenIndex;
    
    // 模板和自定义管理器引用
    std::shared_ptr<TemplateManager> templateManager;
    std::shared_ptr<CustomManager> customManager;
    
public:
    CHTLUnifiedScanner(const std::string& source, std::shared_ptr<CHTLContext> ctx);
    
    // 配置
    void setConfig(const ScannerConfig& cfg) { config = cfg; }
    ScannerConfig& getConfig() { return config; }
    
    // 管理器设置
    void setTemplateManager(std::shared_ptr<TemplateManager> mgr) { templateManager = mgr; }
    void setCustomManager(std::shared_ptr<CustomManager> mgr) { customManager = mgr; }
    
    // 扫描
    void scan();
    bool hasMoreTokens() const;
    Token nextToken();
    Token peekToken() const;
    void rewind();
    
    // 获取所有令牌
    const std::vector<Token>& getTokens() const { return tokens; }
    
    // 上下文查询
    LanguageContext getCurrentContext() const { return currentContext; }
    ScannerState getCurrentState() const { return currentState; }
    
private:
    // 扫描方法
    void scanNormal();
    void scanElement();
    void scanAttribute();
    void scanStyleBlock();
    void scanScriptBlock();
    void scanComment();
    void scanGenerativeComment();
    void scanString(char quote);
    void scanTemplate();
    void scanImport();
    void scanOrigin();
    
    // 辅助方法
    char peek(size_t offset = 0) const;
    char advance();
    bool match(const std::string& expected);
    bool matchWord(const std::string& word);
    void skipWhitespace();
    std::string scanIdentifier();
    std::string scanUntil(char delimiter);
    std::string scanUntil(const std::string& delimiter);
    std::string scanBlock(char open, char close);
    
    // 状态管理
    void pushState(ScannerState state);
    void popState();
    void switchContext(LanguageContext ctx);
    
    // 令牌生成
    void emitToken(TokenType type, const std::string& value);
    void emitToken(TokenType type, const std::string& value, LanguageContext ctx);
    
    // 上下文推导
    LanguageContext inferContext();
    TokenType inferTokenType(const std::string& text);
    
    // 样式组和变量组处理
    bool isStyleGroupUsage(const std::string& text);
    bool isVarGroupUsage(const std::string& text);
    std::string expandStyleGroup(const std::string& name);
    std::string expandVarGroup(const std::string& group, const std::string& var);
    
    // 错误报告
    void reportError(const std::string& message);
    void reportWarning(const std::string& message);
};

// 生成性注释处理器
class GenerativeCommentProcessor {
private:
    std::shared_ptr<CHTLContext> context;
    
    // 注释生成器
    using CommentGenerator = std::function<std::string(const std::string&, LanguageContext)>;
    std::unordered_map<LanguageContext, CommentGenerator> generators;
    
public:
    GenerativeCommentProcessor(std::shared_ptr<CHTLContext> ctx);
    
    // 处理生成性注释
    std::string processComment(const std::string& content, LanguageContext context);
    
    // 注册自定义生成器
    void registerGenerator(LanguageContext lang, CommentGenerator gen);
    
private:
    // 默认生成器
    std::string generateHTMLComment(const std::string& content);
    std::string generateCSSComment(const std::string& content);
    std::string generateJSComment(const std::string& content);
    
    // 格式化
    std::string formatComment(const std::string& content, const std::string& prefix, 
                            const std::string& suffix, int width = 80);
    std::vector<std::string> wrapText(const std::string& text, int width);
};

// 扫描器辅助工具
namespace ScannerHelper {
    // 判断字符类型
    bool isWhitespace(char ch);
    bool isNewline(char ch);
    bool isAlpha(char ch);
    bool isDigit(char ch);
    bool isAlphaNumeric(char ch);
    bool isIdentifierStart(char ch);
    bool isIdentifierPart(char ch);
    
    // 判断关键字
    bool isCHTLKeyword(const std::string& word);
    bool isCSSProperty(const std::string& word);
    bool isJSKeyword(const std::string& word);
    
    // 上下文推导
    LanguageContext inferContextFromElement(const std::string& element);
    LanguageContext inferContextFromContent(const std::string& content);
    
    // 转换工具
    std::string stateToString(ScannerState state);
    std::string contextToString(LanguageContext context);
    std::string tokenTypeToString(TokenType type);
}

// 扫描器上下文推导器
class ScannerContextInferencer {
private:
    std::stack<std::string> elementStack;
    std::unordered_map<std::string, LanguageContext> elementContextMap;
    LanguageContext currentContext;
    
public:
    ScannerContextInferencer();
    
    // 元素进出
    void enterElement(const std::string& element);
    void exitElement();
    
    // 推导上下文
    LanguageContext inferContext() const;
    LanguageContext inferFromAttribute(const std::string& attr, const std::string& value);
    LanguageContext inferFromContent(const std::string& content);
    
    // 重置
    void reset();
    
private:
    void initializeElementContextMap();
};

} // namespace chtl

#endif // CHTL_UNIFIED_SCANNER_H