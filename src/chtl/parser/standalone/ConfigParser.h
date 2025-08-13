#ifndef CHTL_STANDALONE_CONFIG_PARSER_H
#define CHTL_STANDALONE_CONFIG_PARSER_H

#include "ParserRuntime.h"
#include <unordered_map>
#include <vector>

namespace chtl {
namespace parser {

// 配置解析器 - 支持灵活的关键字配置
class ConfigParser : public Parser {
public:
    struct ConfigEntry {
        std::string group;
        std::string key;
        std::string value;
        int line;
        int column;
    };
    
    struct ConfigResult {
        std::vector<ConfigEntry> entries;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> groups;
        bool success = true;
        std::string error;
    };
    
    ConfigParser(std::shared_ptr<TokenStream> tokens) : Parser(tokens) {}
    
    ConfigResult parse() {
        ConfigResult result;
        
        try {
            while (tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
                parseConfigItem(result);
            }
        } catch (const std::exception& e) {
            result.success = false;
            result.error = e.what();
        }
        
        return result;
    }
    
private:
    void parseConfigItem(ConfigResult& result) {
        auto token = tokens_->LT(1);
        
        // 跳过空白和注释
        while (token->getType() == TokenType::WHITESPACE || 
               token->getType() == TokenType::COMMENT ||
               token->getType() == TokenType::NEWLINE) {
            tokens_->consume();
            token = tokens_->LT(1);
        }
        
        if (token->getType() == TokenType::EOF_TOKEN) {
            return;
        }
        
        // 检查是否是组声明 [GroupName]
        if (token->getType() == TokenType::LBRACKET) {
            parseGroup(result);
        } else {
            // 键值对
            parseKeyValue(result);
        }
    }
    
    void parseGroup(ConfigResult& result) {
        consume(TokenType::LBRACKET, "Expected [");
        
        auto groupToken = tokens_->consume();
        std::string groupName = groupToken->getText();
        
        consume(TokenType::RBRACKET, "Expected ]");
        
        currentGroup_ = groupName;
        result.groups[groupName]; // 确保组存在
    }
    
    void parseKeyValue(ConfigResult& result) {
        auto keyToken = tokens_->consume();
        std::string key = keyToken->getText();
        
        // 期望 = 或 :
        auto sep = tokens_->LT(1);
        if (sep->getType() != TokenType::EQUALS && sep->getType() != TokenType::COLON) {
            error("Expected = or : after key", sep);
            return;
        }
        tokens_->consume();
        
        // 读取值（可能是多个token）
        std::string value;
        while (tokens_->LT(1)->getType() != TokenType::NEWLINE &&
               tokens_->LT(1)->getType() != TokenType::EOF_TOKEN &&
               tokens_->LT(1)->getType() != TokenType::COMMENT) {
            value += tokens_->consume()->getText();
            if (tokens_->LT(1)->getType() != TokenType::NEWLINE &&
                tokens_->LT(1)->getType() != TokenType::EOF_TOKEN) {
                value += " ";
            }
        }
        
        // 去除尾部空格
        while (!value.empty() && std::isspace(value.back())) {
            value.pop_back();
        }
        
        // 添加到结果
        ConfigEntry entry{
            currentGroup_,
            key,
            value,
            keyToken->getLine(),
            keyToken->getColumn()
        };
        
        result.entries.push_back(entry);
        result.groups[currentGroup_][key] = value;
    }
    
    std::string currentGroup_ = "DEFAULT";
};

// 配置词法分析器
class ConfigLexer : public Lexer {
public:
    ConfigLexer(const std::string& input) : Lexer(input) {}
    
protected:
    std::shared_ptr<Token> nextToken() override {
        skipWhitespace();
        
        if (pos_ >= input_.size()) {
            return std::make_shared<Token>(TokenType::EOF_TOKEN, "", line_, column_);
        }
        
        int startLine = line_;
        int startColumn = column_;
        
        // 注释
        if (peek() == '#' || (peek() == '/' && peekNext() == '/')) {
            return scanComment();
        }
        
        // 字符串
        if (peek() == '"' || peek() == '\'') {
            return scanString();
        }
        
        // 特殊字符
        char c = peek();
        switch (c) {
            case '[':
                advance();
                return std::make_shared<Token>(TokenType::LBRACKET, "[", startLine, startColumn);
            case ']':
                advance();
                return std::make_shared<Token>(TokenType::RBRACKET, "]", startLine, startColumn);
            case '=':
                advance();
                return std::make_shared<Token>(TokenType::EQUALS, "=", startLine, startColumn);
            case ':':
                advance();
                return std::make_shared<Token>(TokenType::COLON, ":", startLine, startColumn);
            case '\n':
                advance();
                return std::make_shared<Token>(TokenType::NEWLINE, "\\n", startLine, startColumn);
        }
        
        // 标识符或值
        return scanIdentifier();
    }
    
private:
    char peekNext() {
        return pos_ + 1 < input_.size() ? input_[pos_ + 1] : '\0';
    }
    
    std::shared_ptr<Token> scanComment() {
        int startLine = line_;
        int startColumn = column_;
        std::string text;
        
        if (peek() == '#') {
            text += advance();
        } else {
            text += advance(); // /
            text += advance(); // /
        }
        
        while (pos_ < input_.size() && peek() != '\n') {
            text += advance();
        }
        
        return std::make_shared<Token>(TokenType::COMMENT, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanString() {
        int startLine = line_;
        int startColumn = column_;
        char quote = advance();
        std::string text;
        
        while (pos_ < input_.size() && peek() != quote) {
            if (peek() == '\\') {
                advance();
                if (pos_ < input_.size()) {
                    char escaped = advance();
                    switch (escaped) {
                        case 'n': text += '\n'; break;
                        case 't': text += '\t'; break;
                        case 'r': text += '\r'; break;
                        case '\\': text += '\\'; break;
                        case '"': text += '"'; break;
                        case '\'': text += '\''; break;
                        default: text += escaped; break;
                    }
                }
            } else {
                text += advance();
            }
        }
        
        if (pos_ < input_.size()) {
            advance(); // 结束引号
        }
        
        return std::make_shared<Token>(TokenType::STRING_LITERAL, text, startLine, startColumn);
    }
    
    std::shared_ptr<Token> scanIdentifier() {
        int startLine = line_;
        int startColumn = column_;
        std::string text;
        
        // 配置文件中的标识符可以包含更多字符
        while (pos_ < input_.size() && 
               !std::isspace(peek()) &&
               peek() != '=' && peek() != ':' &&
               peek() != '[' && peek() != ']' &&
               peek() != '#' && !(peek() == '/' && peekNext() == '/')) {
            text += advance();
        }
        
        return std::make_shared<Token>(TokenType::IDENTIFIER, text, startLine, startColumn);
    }
};

} // namespace parser
} // namespace chtl

#endif // CHTL_STANDALONE_CONFIG_PARSER_H