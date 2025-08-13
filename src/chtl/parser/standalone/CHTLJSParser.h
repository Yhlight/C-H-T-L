#ifndef CHTL_STANDALONE_JS_PARSER_H
#define CHTL_STANDALONE_JS_PARSER_H

#include "ParserRuntime.h"
#include "CHTLJSLexer.h"

namespace chtl {
namespace parser {

// CHTL JavaScript解析器 - 仅处理CHTL在JavaScript中的扩展
// 原生JavaScript代码作为原始文本传递，由JS编译器处理
class CHTLJSParser : public Parser {
public:
    CHTLJSParser(std::shared_ptr<TokenStream> tokens) : Parser(tokens) {}
    
    // 解析CHTL增强的JavaScript片段
    std::shared_ptr<ParseContext> parse() {
        auto ctx = std::make_shared<ParseContext>("chtlJSProgram");
        
        while (tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            // 只处理CHTL特有的结构
            if (tokens_->LT(1)->getType() == TokenType::AT ||
                tokens_->LT(1)->getType() == TokenType::AT_ELEMENT ||
                tokens_->LT(1)->getType() == TokenType::AT_STYLE ||
                tokens_->LT(1)->getType() == TokenType::AT_VAR) {
                ctx->addChild(chtlDirective());
            } else if (tokens_->LT(1)->getType() == TokenType::DOUBLE_LBRACE) {
                ctx->addChild(chtlInterpolation());
            } else if (tokens_->LT(1)->getType() == TokenType::KEYWORD_VAR &&
                      tokens_->LT(2)->getType() == TokenType::IDENTIFIER &&
                      tokens_->LT(3)->getType() == TokenType::EQUALS &&
                      tokens_->LT(4)->getType() == TokenType::AT) {
                // var element = @Element ...
                ctx->addChild(chtlVarDeclaration());
            } else {
                // 其他所有内容作为原始JavaScript文本
                ctx->addChild(rawJavaScript());
            }
        }
        
        return ctx;
    }
    
private:
    // CHTL指令
    std::shared_ptr<ParseContext> chtlDirective() {
        auto ctx = std::make_shared<ParseContext>("chtlDirective");
        
        auto atToken = tokens_->consume(); // @ 或 @Element 等
        ctx->addChild(std::make_shared<TerminalNode>(atToken));
        
        // 元素/样式/变量名
        auto name = consume(TokenType::IDENTIFIER, "Expected name after " + atToken->getText());
        ctx->addChild(std::make_shared<TerminalNode>(name));
        
        // 可选的from子句
        if (match(TokenType::KEYWORD_FROM)) {
            auto namespaceName = consume(TokenType::IDENTIFIER, "Expected namespace name");
            ctx->addChild(std::make_shared<TerminalNode>(namespaceName));
        }
        
        // 可选的参数（仅Element）
        if (atToken->getType() == TokenType::AT_ELEMENT && match(TokenType::LPAREN)) {
            ctx->addChild(argumentList());
            consume(TokenType::RPAREN, "Expected )");
        }
        
        return ctx;
    }
    
    // CHTL插值
    std::shared_ptr<ParseContext> chtlInterpolation() {
        auto ctx = std::make_shared<ParseContext>("chtlInterpolation");
        
        consume(TokenType::DOUBLE_LBRACE, "Expected {{");
        
        // 插值内容作为原始文本，直到遇到 }}
        std::string content;
        while (tokens_->LT(1)->getType() != TokenType::DOUBLE_RBRACE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            content += tokens_->consume()->getText() + " ";
        }
        
        ctx->addChild(std::make_shared<TerminalNode>(
            std::make_shared<Token>(TokenType::IDENTIFIER, content, 0, 0)
        ));
        
        consume(TokenType::DOUBLE_RBRACE, "Expected }}");
        
        return ctx;
    }
    
    // CHTL变量声明
    std::shared_ptr<ParseContext> chtlVarDeclaration() {
        auto ctx = std::make_shared<ParseContext>("chtlVarDeclaration");
        
        consume(TokenType::KEYWORD_VAR, "Expected var");
        
        auto varName = consume(TokenType::IDENTIFIER, "Expected variable name");
        ctx->addChild(std::make_shared<TerminalNode>(varName));
        
        consume(TokenType::EQUALS, "Expected =");
        
        ctx->addChild(chtlDirective());
        
        // 可选的分号
        if (match(TokenType::SEMICOLON)) {
            // 消费分号但不添加到AST
        }
        
        return ctx;
    }
    
    // 原始JavaScript文本
    std::shared_ptr<ParseContext> rawJavaScript() {
        auto ctx = std::make_shared<ParseContext>("rawJavaScript");
        
        std::string jsCode;
        
        // 收集所有非CHTL特有的token作为原始JS
        while (tokens_->LT(1)->getType() != TokenType::EOF_TOKEN &&
               tokens_->LT(1)->getType() != TokenType::AT &&
               tokens_->LT(1)->getType() != TokenType::AT_ELEMENT &&
               tokens_->LT(1)->getType() != TokenType::AT_STYLE &&
               tokens_->LT(1)->getType() != TokenType::AT_VAR &&
               tokens_->LT(1)->getType() != TokenType::DOUBLE_LBRACE &&
               !(tokens_->LT(1)->getType() == TokenType::KEYWORD_VAR &&
                 tokens_->LT(2)->getType() == TokenType::IDENTIFIER &&
                 tokens_->LT(3)->getType() == TokenType::EQUALS &&
                 tokens_->LT(4)->getType() == TokenType::AT)) {
            
            jsCode += tokens_->consume()->getText() + " ";
        }
        
        if (!jsCode.empty()) {
            ctx->addChild(std::make_shared<TerminalNode>(
                std::make_shared<Token>(TokenType::IDENTIFIER, jsCode, 0, 0)
            ));
        }
        
        return ctx;
    }
    
    // 参数列表
    std::shared_ptr<ParseContext> argumentList() {
        auto ctx = std::make_shared<ParseContext>("argumentList");
        
        if (tokens_->LT(1)->getType() == TokenType::RPAREN) {
            return ctx; // 空参数列表
        }
        
        // 参数作为原始文本处理，由JS编译器解析
        std::string args;
        int parenCount = 0;
        
        while (tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
            if (tokens_->LT(1)->getType() == TokenType::LPAREN) {
                parenCount++;
            } else if (tokens_->LT(1)->getType() == TokenType::RPAREN) {
                if (parenCount == 0) break;
                parenCount--;
            }
            
            args += tokens_->consume()->getText() + " ";
        }
        
        ctx->addChild(std::make_shared<TerminalNode>(
            std::make_shared<Token>(TokenType::IDENTIFIER, args, 0, 0)
        ));
        
        return ctx;
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_JS_PARSER_H