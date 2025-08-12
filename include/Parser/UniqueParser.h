#ifndef CHTL_UNIQUE_PARSER_H
#define CHTL_UNIQUE_PARSER_H

#include "Node/UniqueNode.h"
#include "Lexer/Lexer.h"
#include <memory>
#include <stack>

namespace chtl {

// 基于 unique_ptr 的解析器示例
class UniqueParser {
private:
    Lexer* lexer_;
    Token currentToken_;
    std::stack<UniqueNode*> nodeStack_; // 用于构建树时的临时栈
    
public:
    explicit UniqueParser(Lexer* lexer) : lexer_(lexer) {
        advance();
    }
    
    // 解析并返回 AST 根节点（转移所有权）
    std::unique_ptr<UniqueNode> parse() {
        auto root = std::make_unique<UniqueNode>(NodeType::NODE, "root");
        
        while (!isAtEnd()) {
            auto node = parseNode();
            if (node) {
                root->addChild(std::move(node));
            }
        }
        
        return root;
    }
    
private:
    // 解析单个节点
    std::unique_ptr<UniqueNode> parseNode() {
        if (currentToken_.type == TokenType::IDENTIFIER) {
            return parseElement();
        }
        
        // 跳过不认识的 token
        advance();
        return nullptr;
    }
    
    // 解析元素节点
    std::unique_ptr<UniqueNode> parseElement() {
        std::string tagName = currentToken_.value;
        advance();
        
        auto element = std::make_unique<UniqueNode>(NodeType::ELEMENT, tagName);
        
        // 解析属性
        while (currentToken_.type == TokenType::IDENTIFIER && 
               peek().type == TokenType::COLON) {
            std::string attrName = currentToken_.value;
            advance(); // 跳过属性名
            advance(); // 跳过冒号
            
            if (currentToken_.type == TokenType::STRING_LITERAL ||
                currentToken_.type == TokenType::NUMBER ||
                currentToken_.type == TokenType::IDENTIFIER) {
                element->setAttribute(attrName, currentToken_.value);
                advance();
            }
        }
        
        // 解析子节点
        if (currentToken_.type == TokenType::LEFT_BRACE) {
            advance(); // 跳过 {
            
            while (currentToken_.type != TokenType::RIGHT_BRACE && !isAtEnd()) {
                auto child = parseNode();
                if (child) {
                    element->addChild(std::move(child));
                }
            }
            
            if (currentToken_.type == TokenType::RIGHT_BRACE) {
                advance(); // 跳过 }
            }
        }
        
        return element;
    }
    
    void advance() {
        if (!isAtEnd()) {
            currentToken_ = lexer_->nextToken();
        }
    }
    
    Token peek() {
        return lexer_->peekToken();
    }
    
    bool isAtEnd() {
        return currentToken_.type == TokenType::EOF_TOKEN;
    }
};

} // namespace chtl

#endif // CHTL_UNIQUE_PARSER_H