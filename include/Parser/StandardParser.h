#ifndef CHTL_PARSER_STANDARD_PARSER_H
#define CHTL_PARSER_STANDARD_PARSER_H

#include "Parser/BasicParser.h"
#include "State/StateFactory.h"
#include "Context/ContextFactory.h"
#include "Common/Token.h"
#include <memory>
#include <vector>
#include <string>

namespace chtl {

// 前向声明
class Node;
class Style;
class Template;
class Custom;
class Namespace;
class Config;

class StandardParser : public BasicParser {
public:
    StandardParser(std::shared_ptr<BasicLexer> lexer, std::shared_ptr<BasicContext> context);
    ~StandardParser() override = default;

    // 设置CMOD模式
    void setCmodMode(bool cmodMode) { isCmodMode_ = cmodMode; }
    bool isCmodMode() const { return isCmodMode_; }

    // 主解析方法
    std::shared_ptr<Node> parse() override;

private:
    // 解析状态
    Token currentToken_;
    Token previousToken_;
    // TODO: Remove unused fields if not needed later
    // int currentIndent_;
    // int expectIndent_;
    
    // 解析标志
    // bool inAttribute_;
    // bool inStyleBlock_;
    // bool inTextBlock_;
    // bool inTemplateBlock_;
    // bool inCustomBlock_;
    // bool inConfigBlock_;
    // bool inOriginBlock_;
    
    // CMOD模式标志
    bool isCmodMode_ = false;
    
    // 顶层解析
    std::shared_ptr<Node> parseTopLevel();
    std::shared_ptr<Node> parseSpecialBlock();
    
    // 基础元素解析
    std::shared_ptr<Node> parseElement();
    std::shared_ptr<Node> parseNode();
    std::shared_ptr<Node> parseText();
    std::shared_ptr<Node> parseComment();
    
    // 属性解析
    bool checkAttribute();
    void parseAttributes(std::shared_ptr<Node> element);
    
    // 样式解析
    std::shared_ptr<Node> parseStyleBlock();
    void parseStyleContent(std::shared_ptr<Style> styleNode);
    void parseSelectorBlock(std::shared_ptr<Style> styleNode);
    
    // 脚本解析
    std::shared_ptr<Node> parseScriptBlock();
    void parseContextSelector(std::shared_ptr<Style> styleNode);
    void parseCssProperty(std::string& cssContent);
    
    // 模板解析
    std::shared_ptr<Node> parseTemplate();
    void parseStyleTemplateContent(std::shared_ptr<Template> templateNode);
    void parseElementTemplateContent(std::shared_ptr<Template> templateNode);
    void parseVarTemplateContent(std::shared_ptr<Template> templateNode);
    void parseTemplateProperty(std::shared_ptr<Template> templateNode);
    
    // 自定义解析
    std::shared_ptr<Node> parseCustom();
    void parseCustomStyleContent(std::shared_ptr<Custom> customNode);
    void parseCustomElementContent(std::shared_ptr<Custom> customNode);
    void parseCustomVarContent(std::shared_ptr<Custom> customNode);
    
    // 继承和引用
    void parseInherit(std::shared_ptr<Node> node);
    std::shared_ptr<Node> parseReference();
    std::shared_ptr<Node> parseStyleReference();
    void parseVarArguments(std::shared_ptr<Node> refNode);
    void parseSpecialization(std::shared_ptr<Node> refNode);
    void parseExceptConstraints(std::shared_ptr<Node> element);
    
    // 操作解析
    void parseDelete(std::shared_ptr<Node> parent);
    std::string parseDeleteTarget();
    std::shared_ptr<Node> parseOperation();
    std::shared_ptr<Node> parseInsert();
    std::string parseInsertTarget();
    
    // 原始嵌入
    std::shared_ptr<Node> parseOrigin();
    
    // 配置解析
    std::shared_ptr<Node> parseConfiguration();
    void parseConfigContent(std::shared_ptr<Config> configNode);
    void parseConfigItem(std::shared_ptr<Config> configNode);
    void parseNameConfig(std::shared_ptr<Config> configNode);
    
    // 导入解析
    std::shared_ptr<Node> parseImport();
    std::shared_ptr<Node> parseImportStatement();
    
    // 命名空间解析
    std::shared_ptr<Node> parseNamespace();
    void parseNamespaceContent(std::shared_ptr<Namespace> namespaceNode);

    
    // 信息和导出
    std::shared_ptr<Node> parseInfo();
    std::shared_ptr<Node> parseExport();
    
    // 脚本块
    std::shared_ptr<Node> parseScript();
    
    // Token操作辅助方法
    Token peek();
    Token previous();
    Token advance();
    bool isAtEnd();
    bool check(TokenType type);
    bool checkIdentifier(const std::string& value);
    bool match(TokenType type);
    bool matchIdentifier(const std::string& value);
    Token consume(TokenType type, const std::string& message);
    
    // 工具方法
    void skipWhitespaceAndComments();
    TokenType peekNext();  // 查看下一个token的类型
    void skipToNextStatement();
    void skipBlock();
    
    // 错误处理
    void addError(const std::string& message) {
        if (context_) {
            context_->addError(message + " at line " + std::to_string(currentToken_.line) + 
                              ", column " + std::to_string(currentToken_.column));
        }
    }
    
    void addWarning(const std::string& message) {
        if (context_) {
            context_->addWarning(message + " at line " + std::to_string(currentToken_.line) + 
                                ", column " + std::to_string(currentToken_.column));
        }
    }
};

} // namespace chtl

#endif // CHTL_PARSER_STANDARD_PARSER_H