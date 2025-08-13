#include <iostream>
#include <string>
#include <memory>

// 包含生成的ANTLR4头文件
#include "generated_simple/chtl/grammars/chtl/CHTL_simpleLexer.h"
#include "generated_simple/chtl/grammars/chtl/CHTL_simpleParser.h"
#include "generated_simple/chtl/grammars/chtl/CHTL_simpleBaseVisitor.h"

// 包含ANTLR4运行时
#include "antlr4-runtime.h"

// 自定义访问者类
class CHTLVisitor : public CHTL_simpleBaseVisitor {
public:
    std::any visitProgram(CHTL_simpleParser::ProgramContext *ctx) override {
        std::cout << "🔍 解析CHTL程序..." << std::endl;
        
        // 访问所有语句
        for (auto* statement : ctx->statement()) {
            visit(statement);
        }
        
        return nullptr;
    }
    
    std::any visitElementStatement(CHTL_simpleParser::ElementStatementContext *ctx) override {
        std::string elementName = ctx->IDENTIFIER()->getText();
        std::cout << "📝 发现元素: " << elementName << std::endl;
        
        // 访问属性
        if (ctx->attributes()) {
            visit(ctx->attributes());
        }
        
        // 访问元素内容
        if (ctx->elementContent()) {
            visit(ctx->elementContent());
        }
        
        return nullptr;
    }
    
    std::any visitAttributes(CHTL_simpleParser::AttributesContext *ctx) override {
        std::cout << "  📋 属性:" << std::endl;
        
        // 访问所有属性
        for (auto* attribute : ctx->attribute()) {
            visit(attribute);
        }
        
        return nullptr;
    }
    
    std::any visitAttribute(CHTL_simpleParser::AttributeContext *ctx) override {
        std::string attrName = ctx->IDENTIFIER(0)->getText();
        std::string attrValue;
        
        if (ctx->STRING()) {
            attrValue = ctx->STRING()->getText();
        } else if (ctx->IDENTIFIER(1)) {
            attrValue = ctx->IDENTIFIER(1)->getText();
        }
        
        std::cout << "    - " << attrName << " = " << attrValue << std::endl;
        
        return nullptr;
    }
    
    std::any visitElementContent(CHTL_simpleParser::ElementContentContext *ctx) override {
        std::cout << "  📦 元素内容:" << std::endl;
        
        // 访问所有内容
        for (auto* content : ctx->elementStatement()) {
            visit(content);
        }
        
        for (auto* textBlock : ctx->textBlock()) {
            visit(textBlock);
        }
        
        for (auto* styleBlock : ctx->styleBlock()) {
            visit(styleBlock);
        }
        
        for (auto* scriptBlock : ctx->scriptBlock()) {
            visit(scriptBlock);
        }
        
        return nullptr;
    }
    
    std::any visitTextBlock(CHTL_simpleParser::TextBlockContext *ctx) override {
        std::cout << "    📄 文本块:" << std::endl;
        
        // 访问文本内容
        for (auto* token : ctx->STRING()) {
            std::cout << "      - " << token->getText() << std::endl;
        }
        
        for (auto* token : ctx->IDENTIFIER()) {
            std::cout << "      - " << token->getText() << std::endl;
        }
        
        return nullptr;
    }
    
    std::any visitStyleBlock(CHTL_simpleParser::StyleBlockContext *ctx) override {
        std::cout << "    🎨 样式块:" << std::endl;
        
        // 访问样式内容
        for (auto* token : ctx->STRING()) {
            std::cout << "      - " << token->getText() << std::endl;
        }
        
        for (auto* token : ctx->IDENTIFIER()) {
            std::cout << "      - " << token->getText() << std::endl;
        }
        
        return nullptr;
    }
    
    std::any visitScriptBlock(CHTL_simpleParser::ScriptBlockContext *ctx) override {
        std::cout << "    ⚡ 脚本块:" << std::endl;
        
        // 访问脚本内容
        for (auto* token : ctx->STRING()) {
            std::cout << "      - " << token->getText() << std::endl;
        }
        
        for (auto* token : ctx->IDENTIFIER()) {
            std::cout << "      - " << token->getText() << std::endl;
        }
        
        return nullptr;
    }
    
    std::any visitTemplateStatement(CHTL_simpleParser::TemplateStatementContext *ctx) override {
        std::string templateName = ctx->IDENTIFIER()->getText();
        std::cout << "📋 模板: " << templateName << std::endl;
        
        // 访问模板内容
        if (ctx->elementContent()) {
            visit(ctx->elementContent());
        }
        
        return nullptr;
    }
    
    std::any visitCustomStatement(CHTL_simpleParser::CustomStatementContext *ctx) override {
        std::string customName = ctx->IDENTIFIER()->getText();
        std::cout << "🔧 自定义: " << customName << std::endl;
        
        // 访问自定义内容
        if (ctx->elementContent()) {
            visit(ctx->elementContent());
        }
        
        return nullptr;
    }
    
    std::any visitOriginStatement(CHTL_simpleParser::OriginStatementContext *ctx) override {
        std::string originName = ctx->IDENTIFIER()->getText();
        std::cout << "🌐 原始嵌入: " << originName << std::endl;
        
        // 访问原始内容
        if (ctx->elementContent()) {
            visit(ctx->elementContent());
        }
        
        return nullptr;
    }
};

int main() {
    try {
        std::cout << "🚀 CHTL ANTLR4解析器示例" << std::endl;
        std::cout << "================================" << std::endl;
        
        // 测试CHTL代码
        std::string testCode = R"(
[Template] Button
{
    class: primary;
    
    text
    {
        "点击我"
    }
    
    style
    {
        "background-color: blue;"
        "color: white;"
    }
    
    script
    {
        "console.log('按钮被点击');"
    }
}

div
{
    id: container;
    class: main;
    
    text
    {
        "这是一个测试div"
        "包含多行文本"
    }
}
)";
        
        std::cout << "📝 测试代码:" << std::endl;
        std::cout << testCode << std::endl;
        std::cout << "================================" << std::endl;
        
        // 创建输入流
        std::istringstream inputStream(testCode);
        antlr4::ANTLRInputStream input(inputStream);
        
        // 创建词法分析器
        CHTL_simpleLexer lexer(&input);
        
        // 创建词法标记流
        antlr4::CommonTokenStream tokens(&lexer);
        
        // 创建语法分析器
        CHTL_simpleParser parser(&tokens);
        
        // 解析程序
        CHTL_simpleParser::ProgramContext* tree = parser.program();
        
        // 检查是否有语法错误
        if (parser.getNumberOfSyntaxErrors() > 0) {
            std::cout << "❌ 语法错误数量: " << parser.getNumberOfSyntaxErrors() << std::endl;
            return 1;
        }
        
        std::cout << "✅ 语法解析成功!" << std::endl;
        std::cout << "================================" << std::endl;
        
        // 创建访问者并遍历语法树
        CHTLVisitor visitor;
        visitor.visit(tree);
        
        std::cout << "================================" << std::endl;
        std::cout << "🎉 解析完成!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ 错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}