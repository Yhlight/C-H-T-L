#include <iostream>
#include <sstream>
#include <memory>
#include "Lexer/ChtlLexer.h"
#include "State/ChtlState.h"
#include "Context/ChtlContext.h"
#include "Node/Node.h"
#include "Node/Comment.h"
#include "Generator/HtmlGenerator.h"

using namespace std;
using namespace chtl;

// 测试词法分析器对--注释的识别
void testCommentLexer() {
    cout << "========== Testing Comment Lexer ==========" << endl;
    
    ChtlLexer lexer;
    string chtlCode = R"(
-- 这是一个CHTL注释，会被生成器识别
// 这是普通注释，不会被生成器识别
/* 这是多行注释
   也不会被生成器识别 */

div {
    -- 这是div内部的注释
    text {
        "Hello World"
    }
}
)";
    
    auto stream = make_unique<istringstream>(chtlCode);
    if (lexer.initialize(std::move(stream), "test.chtl")) {
        Token token;
        while ((token = lexer.getNextToken()).getType() != TokenType::EOF_TOKEN) {
            if (token.getType() == TokenType::HTML_COMMENT) {
                cout << "Found CHTL comment: " << token.getValue() << endl;
            } else if (token.getType() == TokenType::SINGLE_LINE_COMMENT) {
                cout << "Found single-line comment: " << token.getValue() << endl;
            } else if (token.getType() == TokenType::MULTI_LINE_COMMENT) {
                cout << "Found multi-line comment: " << token.getValue() << endl;
            }
        }
    }
    cout << endl;
}

// 测试Comment节点的生成
void testCommentNode() {
    cout << "========== Testing Comment Node ==========" << endl;
    
    // 创建一个简单的DOM结构
    auto html = make_shared<Element>("html");
    auto body = make_shared<Element>("body");
    
    // 添加CHTL注释
    auto comment1 = make_shared<Comment>("这是页面顶部的注释");
    body->appendChild(comment1);
    
    // 添加一个div
    auto div = make_shared<Element>("div");
    div->setAttribute("class", "container");
    
    // 在div内添加注释
    auto comment2 = make_shared<Comment>("容器开始");
    div->appendChild(comment2);
    
    // 添加文本
    auto text = make_shared<Text>("Hello, CHTL!");
    div->appendChild(text);
    
    // 再添加一个注释
    auto comment3 = make_shared<Comment>("容器结束");
    div->appendChild(comment3);
    
    body->appendChild(div);
    html->appendChild(body);
    
    // 打印节点结构
    cout << "Node structure:" << endl;
    cout << html->toString() << endl;
    cout << endl;
}

// 测试HTML生成器对注释的处理
void testCommentGeneration() {
    cout << "========== Testing Comment Generation ==========" << endl;
    
    // 创建DOM结构
    auto html = make_shared<Element>("html");
    auto head = make_shared<Element>("head");
    auto title = make_shared<Element>("title");
    title->appendChild(make_shared<Text>("CHTL Comment Test"));
    head->appendChild(title);
    html->appendChild(head);
    
    auto body = make_shared<Element>("body");
    
    // 添加顶部注释
    body->appendChild(make_shared<Comment>("页面主体开始"));
    
    // 添加标题
    auto h1 = make_shared<Element>("h1");
    h1->appendChild(make_shared<Text>("CHTL注释测试"));
    body->appendChild(h1);
    
    // 添加带注释的div
    auto div = make_shared<Element>("div");
    div->setAttribute("id", "content");
    div->appendChild(make_shared<Comment>("内容区域"));
    
    auto p = make_shared<Element>("p");
    p->appendChild(make_shared<Text>("CHTL的--注释会被转换为HTML注释"));
    div->appendChild(p);
    
    div->appendChild(make_shared<Comment>("内容区域结束"));
    body->appendChild(div);
    
    // 添加底部注释
    body->appendChild(make_shared<Comment>("页面主体结束"));
    html->appendChild(body);
    
    // 使用HtmlGenerator生成HTML
    HtmlGenerator generator;
    generator.setGenerateDoctype(true);
    
    // 生成到字符串
    string output;
    if (generator.generateToString(html, output)) {
        cout << "Generated HTML:" << endl;
        cout << output << endl;
    } else {
        cout << "Generation failed!" << endl;
        for (const auto& error : generator.getErrors()) {
            cout << "Error: " << error << endl;
        }
    }
}

// 测试不同类型的注释
void testDifferentComments() {
    cout << "========== Testing Different Comment Types ==========" << endl;
    
    ChtlLexer lexer;
    string chtlCode = R"(
-- CHTL注释1：这会出现在HTML中
// C++风格注释：这不会出现在HTML中
/* C风格注释：
   这也不会出现在HTML中 */
-- CHTL注释2：支持中文和特殊字符!@#$%^&*()
-- CHTL注释3：可以包含HTML标签 <div>test</div>
-------- 多个横线也是注释
)";
    
    auto stream = make_unique<istringstream>(chtlCode);
    if (lexer.initialize(std::move(stream), "test.chtl")) {
        Token token;
        int commentCount = 0;
        while ((token = lexer.getNextToken()).getType() != TokenType::EOF_TOKEN) {
            if (token.getType() == TokenType::HTML_COMMENT) {
                commentCount++;
                cout << "CHTL Comment #" << commentCount << ": " << token.getValue() << endl;
            }
        }
        cout << "Total CHTL comments found: " << commentCount << endl;
    }
}

int main() {
    cout << "===== CHTL Comment System Test =====" << endl << endl;
    
    try {
        testCommentLexer();
        testCommentNode();
        testCommentGeneration();
        testDifferentComments();
        
        cout << "\n===== All tests completed successfully =====" << endl;
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}