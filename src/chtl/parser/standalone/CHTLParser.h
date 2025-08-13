#ifndef CHTL_STANDALONE_PARSER_H
#define CHTL_STANDALONE_PARSER_H

#include "ParserRuntime.h"
#include "CHTLLexer.h"
#include <memory>
#include <vector>

namespace chtl {
namespace parser {

// CHTL解析器 - 根据CHTL语法文档实现
class CHTLParser : public Parser {
public:
    CHTLParser(std::shared_ptr<TokenStream> tokens) : Parser(tokens) {}
    
    // 主解析入口
    std::shared_ptr<ParseContext> parse() {
        return compilationUnit();
    }
    
    // 规则：compilationUnit
    std::shared_ptr<ParseContext> compilationUnit() {
        auto ctx = std::make_shared<ParseContext>("compilationUnit");
        
        while (tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            if (match(TokenType::KEYWORD_TEMPLATE)) {
                ctx->addChild(templateDefinition());
            } else if (match(TokenType::KEYWORD_CUSTOM)) {
                ctx->addChild(customDefinition());
            } else if (match(TokenType::KEYWORD_IMPORT)) {
                ctx->addChild(importStatement());
            } else if (match(TokenType::KEYWORD_NAMESPACE)) {
                ctx->addChild(namespaceDeclaration());
            } else if (match(TokenType::KEYWORD_ORIGIN)) {
                ctx->addChild(originDeclaration());
            } else {
                ctx->addChild(htmlElement());
            }
        }
        
        return ctx;
    }
    
    // Template定义
    std::shared_ptr<ParseContext> templateDefinition() {
        auto ctx = std::make_shared<ParseContext>("templateDefinition");
        
        // [Template] 已经被消费
        ctx->addChild(std::make_shared<TerminalNode>(
            std::make_shared<Token>(TokenType::KEYWORD_TEMPLATE, "[Template]", 0, 0)));
        
        // @Element, @Style, @Var
        if (match(TokenType::KEYWORD_ELEMENT)) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->LT(0)));
            ctx->addChild(templateElement());
        } else if (match(TokenType::KEYWORD_STYLE_GROUP)) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->LT(0)));
            ctx->addChild(templateStyle());
        } else if (match(TokenType::KEYWORD_VAR_GROUP)) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->LT(0)));
            ctx->addChild(templateVarGroup());
        }
        
        return ctx;
    }
    
    // HTML元素
    std::shared_ptr<ParseContext> htmlElement() {
        auto ctx = std::make_shared<ParseContext>("htmlElement");
        
        // 元素名
        auto tagName = consume(TokenType::IDENTIFIER, "Expected element name");
        ctx->addChild(std::make_shared<TerminalNode>(tagName));
        
        // {
        consume(TokenType::LBRACE, "Expected {");
        
        // 内容
        while (!match(TokenType::RBRACE) && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            if (tokens_->LT(1)->getType() == TokenType::IDENTIFIER && 
                tokens_->LT(2)->getType() == TokenType::COLON) {
                // 属性
                ctx->addChild(attribute());
            } else if (match(TokenType::KEYWORD_TEXT)) {
                // text节点
                ctx->addChild(textNode());
            } else if (match(TokenType::KEYWORD_STYLE)) {
                // style块
                ctx->addChild(styleBlock());
            } else if (match(TokenType::KEYWORD_SCRIPT)) {
                // script块
                ctx->addChild(scriptBlock());
            } else if (tokens_->LT(1)->getType() == TokenType::IDENTIFIER &&
                      tokens_->LT(2)->getType() == TokenType::LBRACE) {
                // 嵌套元素
                ctx->addChild(htmlElement());
            } else {
                // 错误处理
                auto token = tokens_->consume();
                error("Unexpected token in element: " + token->getText(), token);
            }
        }
        
        return ctx;
    }
    
    // 文本节点
    std::shared_ptr<ParseContext> textNode() {
        auto ctx = std::make_shared<ParseContext>("textNode");
        
        // text 已被消费
        consume(TokenType::LBRACE, "Expected { after text");
        
        // 文本内容 - 支持字面量和字符串
        if (tokens_->LT(1)->getType() == TokenType::STRING_LITERAL) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        } else {
            // 无引号字面量 - 读取到}
            std::string literal;
            while (tokens_->LT(1)->getType() != TokenType::RBRACE &&
                   tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
                literal += tokens_->consume()->getText() + " ";
            }
            ctx->addChild(std::make_shared<TerminalNode>(
                std::make_shared<Token>(TokenType::TEXT_LITERAL, literal, 0, 0)));
        }
        
        consume(TokenType::RBRACE, "Expected }");
        
        return ctx;
    }
    
    // 属性
    std::shared_ptr<ParseContext> attribute() {
        auto ctx = std::make_shared<ParseContext>("attribute");
        
        // 属性名
        auto name = consume(TokenType::IDENTIFIER, "Expected attribute name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // : 或 = (CE对等式)
        if (!match(TokenType::COLON) && !match(TokenType::EQUALS)) {
            error("Expected : or = after attribute name", tokens_->LT(1));
        }
        
        // 属性值
        if (tokens_->LT(1)->getType() == TokenType::STRING_LITERAL) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        } else {
            // 无引号字面量
            std::string value;
            while (tokens_->LT(1)->getType() != TokenType::SEMICOLON &&
                   tokens_->LT(1)->getType() != TokenType::RBRACE &&
                   tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
                value += tokens_->consume()->getText();
            }
            ctx->addChild(std::make_shared<TerminalNode>(
                std::make_shared<Token>(TokenType::TEXT_LITERAL, value, 0, 0)));
        }
        
        // 分号
        consume(TokenType::SEMICOLON, "Expected ; after attribute");
        
        return ctx;
    }
    
    // style块
    std::shared_ptr<ParseContext> styleBlock() {
        auto ctx = std::make_shared<ParseContext>("styleBlock");
        
        // style 已被消费
        consume(TokenType::LBRACE, "Expected { after style");
        
        // CSS规则
        while (!match(TokenType::RBRACE) && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            ctx->addChild(cssRule());
        }
        
        return ctx;
    }
    
    // CSS规则（简化版）
    std::shared_ptr<ParseContext> cssRule() {
        auto ctx = std::make_shared<ParseContext>("cssRule");
        
        // 选择器或属性
        if (tokens_->LT(1)->getType() == TokenType::DOT ||
            tokens_->LT(1)->getType() == TokenType::HASH ||
            tokens_->LT(1)->getType() == TokenType::AMPERSAND) {
            // 选择器
            ctx->addChild(cssSelector());
            consume(TokenType::LBRACE, "Expected { after selector");
            
            while (!match(TokenType::RBRACE) && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
                ctx->addChild(cssProperty());
            }
        } else if (tokens_->LT(1)->getType() == TokenType::AT) {
            // @规则 (@inherit, @use等)
            ctx->addChild(cssAtRule());
        } else {
            // 内联样式属性
            ctx->addChild(cssProperty());
        }
        
        return ctx;
    }
    
    // CSS选择器
    std::shared_ptr<ParseContext> cssSelector() {
        auto ctx = std::make_shared<ParseContext>("cssSelector");
        
        // 简化的选择器解析
        while (tokens_->LT(1)->getType() != TokenType::LBRACE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        }
        
        return ctx;
    }
    
    // CSS属性
    std::shared_ptr<ParseContext> cssProperty() {
        auto ctx = std::make_shared<ParseContext>("cssProperty");
        
        // 属性名
        auto name = consume(TokenType::IDENTIFIER, "Expected property name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // :
        consume(TokenType::COLON, "Expected : after property name");
        
        // 属性值
        while (tokens_->LT(1)->getType() != TokenType::SEMICOLON &&
               tokens_->LT(1)->getType() != TokenType::RBRACE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        }
        
        // 分号（可选）
        match(TokenType::SEMICOLON);
        
        return ctx;
    }
    
    // CSS @规则
    std::shared_ptr<ParseContext> cssAtRule() {
        auto ctx = std::make_shared<ParseContext>("cssAtRule");
        
        // @ 符号
        consume(TokenType::AT, "Expected @");
        
        // 规则名（inherit, use等）
        auto ruleName = tokens_->consume();
        ctx->addChild(std::make_shared<TerminalNode>(ruleName));
        
        // 参数
        while (tokens_->LT(1)->getType() != TokenType::SEMICOLON &&
               tokens_->LT(1)->getType() != TokenType::RBRACE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        }
        
        match(TokenType::SEMICOLON);
        
        return ctx;
    }
    
    // script块
    std::shared_ptr<ParseContext> scriptBlock() {
        auto ctx = std::make_shared<ParseContext>("scriptBlock");
        
        // script 已被消费
        consume(TokenType::LBRACE, "Expected { after script");
        
        // JavaScript代码 - 简化处理，读取到匹配的}
        int braceCount = 1;
        std::string jsCode;
        
        while (braceCount > 0 && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            auto token = tokens_->consume();
            if (token->getType() == TokenType::LBRACE) {
                braceCount++;
            } else if (token->getType() == TokenType::RBRACE) {
                braceCount--;
                if (braceCount == 0) break;
            }
            jsCode += token->getText() + " ";
        }
        
        ctx->addChild(std::make_shared<TerminalNode>(
            std::make_shared<Token>(TokenType::TEXT_LITERAL, jsCode, 0, 0)));
        
        return ctx;
    }
    
    // Template Element
    std::shared_ptr<ParseContext> templateElement() {
        auto ctx = std::make_shared<ParseContext>("templateElement");
        
        // 名称
        auto name = consume(TokenType::IDENTIFIER, "Expected template element name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // 参数（可选）
        if (match(TokenType::LPAREN)) {
            ctx->addChild(parameterList());
            consume(TokenType::RPAREN, "Expected )");
        }
        
        // 元素体
        consume(TokenType::LBRACE, "Expected {");
        ctx->addChild(htmlElement());
        
        return ctx;
    }
    
    // Template Style
    std::shared_ptr<ParseContext> templateStyle() {
        auto ctx = std::make_shared<ParseContext>("templateStyle");
        
        // 名称
        auto name = consume(TokenType::IDENTIFIER, "Expected template style name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // 参数（可选）
        if (match(TokenType::LPAREN)) {
            ctx->addChild(parameterList());
            consume(TokenType::RPAREN, "Expected )");
        }
        
        // 样式体
        consume(TokenType::LBRACE, "Expected {");
        
        while (!match(TokenType::RBRACE) && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            ctx->addChild(cssRule());
        }
        
        return ctx;
    }
    
    // Template Var Group
    std::shared_ptr<ParseContext> templateVarGroup() {
        auto ctx = std::make_shared<ParseContext>("templateVarGroup");
        
        // 名称
        auto name = consume(TokenType::IDENTIFIER, "Expected template var group name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // 变量体
        consume(TokenType::LBRACE, "Expected {");
        
        while (!match(TokenType::RBRACE) && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            // 变量定义
            auto varName = consume(TokenType::IDENTIFIER, "Expected variable name");
            ctx->addChild(std::make_shared<TerminalNode>(varName));
            
            consume(TokenType::COLON, "Expected :");
            
            // 变量值
            while (tokens_->LT(1)->getType() != TokenType::SEMICOLON &&
                   tokens_->LT(1)->getType() != TokenType::RBRACE &&
                   tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
                ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
            }
            
            match(TokenType::SEMICOLON);
        }
        
        return ctx;
    }
    
    // 参数列表
    std::shared_ptr<ParseContext> parameterList() {
        auto ctx = std::make_shared<ParseContext>("parameterList");
        
        if (tokens_->LT(1)->getType() == TokenType::RPAREN) {
            return ctx; // 空参数列表
        }
        
        do {
            auto param = consume(TokenType::IDENTIFIER, "Expected parameter name");
            ctx->addChild(std::make_shared<TerminalNode>(param));
            
            // 默认值（可选）
            if (match(TokenType::EQUALS)) {
                // 读取默认值
                while (tokens_->LT(1)->getType() != TokenType::COMMA &&
                       tokens_->LT(1)->getType() != TokenType::RPAREN &&
                       tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
                    ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
                }
            }
        } while (match(TokenType::COMMA));
        
        return ctx;
    }
    
    // Custom定义
    std::shared_ptr<ParseContext> customDefinition() {
        auto ctx = std::make_shared<ParseContext>("customDefinition");
        
        // [Custom] 已被消费
        ctx->addChild(std::make_shared<TerminalNode>(
            std::make_shared<Token>(TokenType::KEYWORD_CUSTOM, "[Custom]", 0, 0)));
        
        // 类型和处理类似Template
        if (match(TokenType::KEYWORD_ELEMENT)) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->LT(0)));
            ctx->addChild(customElement());
        } else if (match(TokenType::KEYWORD_STYLE_GROUP)) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->LT(0)));
            ctx->addChild(customStyle());
        }
        
        return ctx;
    }
    
    // Custom Element
    std::shared_ptr<ParseContext> customElement() {
        auto ctx = std::make_shared<ParseContext>("customElement");
        
        // 名称
        auto name = consume(TokenType::IDENTIFIER, "Expected custom element name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // from子句（可选）
        if (match(TokenType::KEYWORD_FROM)) {
            auto fromName = consume(TokenType::IDENTIFIER, "Expected source name");
            ctx->addChild(std::make_shared<TerminalNode>(fromName));
        }
        
        consume(TokenType::LBRACE, "Expected {");
        
        // 特化操作
        while (!match(TokenType::RBRACE) && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            if (match(TokenType::AT)) {
                ctx->addChild(customOperation());
            } else {
                // 元素内容
                ctx->addChild(htmlElement());
            }
        }
        
        return ctx;
    }
    
    // Custom Style
    std::shared_ptr<ParseContext> customStyle() {
        auto ctx = std::make_shared<ParseContext>("customStyle");
        
        // 名称
        auto name = consume(TokenType::IDENTIFIER, "Expected custom style name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // from子句（可选）
        if (match(TokenType::KEYWORD_FROM)) {
            auto fromName = consume(TokenType::IDENTIFIER, "Expected source name");
            ctx->addChild(std::make_shared<TerminalNode>(fromName));
        }
        
        consume(TokenType::LBRACE, "Expected {");
        
        // 样式规则
        while (!match(TokenType::RBRACE) && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            ctx->addChild(cssRule());
        }
        
        return ctx;
    }
    
    // Custom操作
    std::shared_ptr<ParseContext> customOperation() {
        auto ctx = std::make_shared<ParseContext>("customOperation");
        
        // @ 已被消费
        auto op = tokens_->consume();
        ctx->addChild(std::make_shared<TerminalNode>(op));
        
        // 操作参数
        while (tokens_->LT(1)->getType() != TokenType::SEMICOLON &&
               tokens_->LT(1)->getType() != TokenType::RBRACE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        }
        
        match(TokenType::SEMICOLON);
        
        return ctx;
    }
    
    // Import语句
    std::shared_ptr<ParseContext> importStatement() {
        auto ctx = std::make_shared<ParseContext>("importStatement");
        
        // [Import] 已被消费
        
        // 导入类型
        if (match(TokenType::AT)) {
            auto importType = tokens_->consume();
            ctx->addChild(std::make_shared<TerminalNode>(importType));
        }
        
        // 路径或名称
        auto path = tokens_->consume();
        ctx->addChild(std::make_shared<TerminalNode>(path));
        
        // as子句（可选）
        if (match(TokenType::KEYWORD_AS)) {
            auto alias = consume(TokenType::IDENTIFIER, "Expected alias name");
            ctx->addChild(std::make_shared<TerminalNode>(alias));
        }
        
        return ctx;
    }
    
    // Namespace声明
    std::shared_ptr<ParseContext> namespaceDeclaration() {
        auto ctx = std::make_shared<ParseContext>("namespaceDeclaration");
        
        // [Namespace] 已被消费
        
        // 命名空间名称
        auto name = consume(TokenType::IDENTIFIER, "Expected namespace name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        return ctx;
    }
    
    // Origin声明
    std::shared_ptr<ParseContext> originDeclaration() {
        auto ctx = std::make_shared<ParseContext>("originDeclaration");
        
        // [Origin] 已被消费
        
        // 类型
        if (match(TokenType::AT)) {
            auto originType = tokens_->consume();
            ctx->addChild(std::make_shared<TerminalNode>(originType));
        }
        
        // 名称（可选）
        if (tokens_->LT(1)->getType() == TokenType::IDENTIFIER) {
            auto name = tokens_->consume();
            ctx->addChild(std::make_shared<TerminalNode>(name));
        }
        
        consume(TokenType::LBRACE, "Expected {");
        
        // 原始内容
        std::string rawContent;
        int braceCount = 1;
        
        while (braceCount > 0 && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            auto token = tokens_->consume();
            if (token->getType() == TokenType::LBRACE) {
                braceCount++;
            } else if (token->getType() == TokenType::RBRACE) {
                braceCount--;
                if (braceCount == 0) break;
            }
            rawContent += token->getText() + " ";
        }
        
        ctx->addChild(std::make_shared<TerminalNode>(
            std::make_shared<Token>(TokenType::TEXT_LITERAL, rawContent, 0, 0)));
        
        return ctx;
    }
    
private:
    // 辅助方法
    std::shared_ptr<Token> LT(int k) {
        return tokens_->LT(k);
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_PARSER_H