#pragma once

#include "v2/Node/Node.h"
#include "v2/State/ChtlStateMachine.h"
#include "v2/Lexer/ChtlLexer.h"
#include "v2/Css/NativeCssAnalyzer.h"
#include "v2/Js/NativeJsAnalyzer.h"
#include <memory>
#include <vector>
#include <string>

namespace chtl::v2 {

/**
 * 解析结果
 */
struct ParseResult {
    bool success = false;
    std::shared_ptr<Node> ast;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
    // 各编译器的分析结果
    std::vector<css::CssAnalysisResult> cssResults;
    std::vector<js::JsAnalysisResult> jsResults;
};

/**
 * CHTL 语法分析器
 * 只负责解析 CHTL 语法结构，不处理 CSS/JS 内部语法
 */
class ChtlParser {
public:
    ChtlParser();
    ~ChtlParser();
    
    /**
     * 解析 CHTL 代码
     */
    ParseResult parse(const std::string& input);
    
    /**
     * 设置选项
     */
    void setOption(const std::string& name, bool value);
    
private:
    // ===== 解析方法 =====
    
    /**
     * 解析顶层
     */
    std::shared_ptr<Node> parseTopLevel();
    
    /**
     * 解析声明
     */
    std::shared_ptr<Node> parseDeclaration();
    
    /**
     * 解析元素
     */
    std::shared_ptr<Node> parseElement();
    
    /**
     * 解析元素标签和属性
     */
    void parseElementTag(std::shared_ptr<Element>& element);
    
    /**
     * 解析元素内容
     */
    void parseElementContent(std::shared_ptr<Element>& element);
    
    /**
     * 解析样式块
     */
    std::shared_ptr<Node> parseStyleBlock();
    
    /**
     * 解析脚本块
     */
    std::shared_ptr<Node> parseScriptBlock();
    
    /**
     * 解析文本块
     */
    std::shared_ptr<Node> parseTextBlock();
    
    /**
     * 解析引用
     */
    std::shared_ptr<Node> parseReference();
    
    /**
     * 解析模板声明
     */
    std::shared_ptr<Node> parseTemplateDeclaration();
    
    /**
     * 解析自定义组件声明
     */
    std::shared_ptr<Node> parseCustomDeclaration();
    
    /**
     * 解析导入声明
     */
    std::shared_ptr<Node> parseImportDeclaration();
    
    /**
     * 跳过到声明结束
     */
    void skipToDeclarationEnd();
    
    // ===== 辅助方法 =====
    
    /**
     * 消费 token
     */
    Token consume(TokenType expected, const std::string& message);
    
    /**
     * 检查当前 token
     */
    bool check(TokenType type) const;
    
    /**
     * 匹配 token
     */
    bool match(TokenType type);
    
    /**
     * 前进到下一个 token
     */
    Token advance();
    
    /**
     * 查看当前 token
     */
    Token peek() const;
    
    /**
     * 是否到达结尾
     */
    bool isAtEnd() const;
    
    /**
     * 添加错误
     */
    void addError(const std::string& message);
    
    /**
     * 添加警告
     */
    void addWarning(const std::string& message);
    
    /**
     * 收集 CSS 内容
     */
    std::string collectCssContent();
    
    /**
     * 收集 JS 内容
     */
    std::string collectJsContent();
    
    /**
     * 收集到匹配的大括号
     */
    std::string collectUntilBrace();
    
private:
    // 词法分析器
    std::unique_ptr<ChtlLexer> lexer_;
    
    // 状态机
    std::unique_ptr<ChtlStateMachine> stateMachine_;
    
    // CSS/JS 分析器
    std::unique_ptr<css::NativeCssAnalyzer> cssAnalyzer_;
    std::unique_ptr<js::NativeJsAnalyzer> jsAnalyzer_;
    
    // 当前 token
    Token currentToken_;
    
    // 解析结果
    ParseResult result_;
    
    // 选项
    struct Options {
        bool strictMode = false;
        bool allowLegacySyntax = true;
    } options_;
};

} // namespace chtl::v2