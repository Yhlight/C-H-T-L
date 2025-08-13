#ifndef CHTL_STANDALONE_JS_PARSER_H
#define CHTL_STANDALONE_JS_PARSER_H

#include "CHTLParser.h"
#include "CHTLJSLexer.h"

namespace chtl {
namespace parser {

// CHTL JavaScript解析器 - 扩展CHTL解析器以支持在script块中的CHTL特性
class CHTLJSParser : public CHTLParser {
public:
    CHTLJSParser(std::shared_ptr<TokenStream> tokens) : CHTLParser(tokens) {}
    
    // 重写script块解析以支持CHTL扩展
    std::shared_ptr<ParseContext> scriptBlock() override {
        auto ctx = std::make_shared<ParseContext>("scriptBlock");
        
        // script 已被消费
        consume(TokenType::LBRACE, "Expected { after script");
        
        // 解析CHTL增强的JavaScript代码
        ctx->addChild(chtlJavaScript());
        
        consume(TokenType::RBRACE, "Expected }");
        
        return ctx;
    }
    
private:
    // CHTL JavaScript内容
    std::shared_ptr<ParseContext> chtlJavaScript() {
        auto ctx = std::make_shared<ParseContext>("chtlJavaScript");
        
        while (tokens_->LT(1)->getType() != TokenType::RBRACE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            
            // 检查CHTL特有的结构
            if (tokens_->LT(1)->getType() == TokenType::AT) {
                ctx->addChild(chtlDirective());
            } else if (tokens_->LT(1)->getText() == "{{") {
                ctx->addChild(chtlInterpolation());
            } else {
                // 普通JavaScript代码
                ctx->addChild(jsStatement());
            }
        }
        
        return ctx;
    }
    
    // CHTL指令（在JS中）
    std::shared_ptr<ParseContext> chtlDirective() {
        auto ctx = std::make_shared<ParseContext>("chtlDirective");
        
        consume(TokenType::AT, "Expected @");
        auto directive = tokens_->consume();
        ctx->addChild(std::make_shared<TerminalNode>(directive));
        
        // 根据指令类型处理
        if (directive->getText() == "Element") {
            ctx->addChild(elementReference());
        } else if (directive->getText() == "Style") {
            ctx->addChild(styleReference());
        } else if (directive->getText() == "Var") {
            ctx->addChild(varReference());
        }
        
        return ctx;
    }
    
    // CHTL插值
    std::shared_ptr<ParseContext> chtlInterpolation() {
        auto ctx = std::make_shared<ParseContext>("chtlInterpolation");
        
        // 消费 {{
        tokens_->consume();
        tokens_->consume();
        
        // 解析表达式
        ctx->addChild(jsExpression());
        
        // 消费 }}
        if (tokens_->LT(1)->getText() == "}" && tokens_->LT(2)->getText() == "}") {
            tokens_->consume();
            tokens_->consume();
        }
        
        return ctx;
    }
    
    // JavaScript语句
    std::shared_ptr<ParseContext> jsStatement() {
        auto ctx = std::make_shared<ParseContext>("jsStatement");
        
        // 简化的JS语句解析
        // 实际应用中需要完整的JS语法支持
        while (tokens_->LT(1)->getType() != TokenType::SEMICOLON &&
               tokens_->LT(1)->getType() != TokenType::RBRACE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN &&
               tokens_->LT(1)->getType() != TokenType::AT &&
               tokens_->LT(1)->getText() != "{{") {
            
            auto token = tokens_->consume();
            ctx->addChild(std::make_shared<TerminalNode>(token));
            
            // 处理嵌套的大括号
            if (token->getType() == TokenType::LBRACE) {
                ctx->addChild(jsBlock());
            }
        }
        
        // 可选的分号
        if (tokens_->LT(1)->getType() == TokenType::SEMICOLON) {
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        }
        
        return ctx;
    }
    
    // JavaScript块
    std::shared_ptr<ParseContext> jsBlock() {
        auto ctx = std::make_shared<ParseContext>("jsBlock");
        
        int braceCount = 1;
        while (braceCount > 0 && tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            auto token = tokens_->LT(1);
            
            if (token->getType() == TokenType::LBRACE) {
                braceCount++;
            } else if (token->getType() == TokenType::RBRACE) {
                braceCount--;
                if (braceCount == 0) break;
            } else if (token->getType() == TokenType::AT) {
                // 嵌套的CHTL指令
                ctx->addChild(chtlDirective());
                continue;
            } else if (token->getText() == "{{") {
                // 嵌套的CHTL插值
                ctx->addChild(chtlInterpolation());
                continue;
            }
            
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        }
        
        return ctx;
    }
    
    // JavaScript表达式
    std::shared_ptr<ParseContext> jsExpression() {
        auto ctx = std::make_shared<ParseContext>("jsExpression");
        
        // 简化的表达式解析
        int parenCount = 0;
        int braceCount = 0;
        
        while (tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            auto token = tokens_->LT(1);
            
            if (token->getType() == TokenType::LPAREN) parenCount++;
            else if (token->getType() == TokenType::RPAREN) parenCount--;
            else if (token->getType() == TokenType::LBRACE) braceCount++;
            else if (token->getType() == TokenType::RBRACE) braceCount--;
            
            // 检查是否到达表达式结尾
            if (parenCount == 0 && braceCount == 0) {
                if (token->getText() == "}" && tokens_->LT(2)->getText() == "}") {
                    break; // 结束插值
                }
                if (token->getType() == TokenType::SEMICOLON ||
                    token->getType() == TokenType::COMMA) {
                    break;
                }
            }
            
            ctx->addChild(std::make_shared<TerminalNode>(tokens_->consume()));
        }
        
        return ctx;
    }
    
    // 元素引用
    std::shared_ptr<ParseContext> elementReference() {
        auto ctx = std::make_shared<ParseContext>("elementReference");
        
        // 元素名
        auto name = consume(TokenType::IDENTIFIER, "Expected element name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // 可选的参数
        if (match(TokenType::LPAREN)) {
            ctx->addChild(argumentList());
            consume(TokenType::RPAREN, "Expected )");
        }
        
        return ctx;
    }
    
    // 样式引用
    std::shared_ptr<ParseContext> styleReference() {
        auto ctx = std::make_shared<ParseContext>("styleReference");
        
        // 样式名
        auto name = consume(TokenType::IDENTIFIER, "Expected style name");
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        return ctx;
    }
    
    // 变量引用
    std::shared_ptr<ParseContext> varReference() {
        auto ctx = std::make_shared<ParseContext>("varReference");
        
        // 变量组名
        auto groupName = consume(TokenType::IDENTIFIER, "Expected variable group name");
        ctx->addChild(std::make_shared<TerminalNode>(groupName));
        
        // 可选的具体变量
        if (match(TokenType::DOT)) {
            auto varName = consume(TokenType::IDENTIFIER, "Expected variable name");
            ctx->addChild(std::make_shared<TerminalNode>(varName));
        }
        
        return ctx;
    }
    
    // 参数列表
    std::shared_ptr<ParseContext> argumentList() {
        auto ctx = std::make_shared<ParseContext>("argumentList");
        
        if (tokens_->LT(1)->getType() == TokenType::RPAREN) {
            return ctx; // 空参数列表
        }
        
        do {
            ctx->addChild(jsExpression());
        } while (match(TokenType::COMMA));
        
        return ctx;
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_JS_PARSER_H