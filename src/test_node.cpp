#include <iostream>
#include "node/Node.h"

using namespace chtl;

int main() {
    std::cout << "CHTL Node System Test" << std::endl;
    std::cout << "====================" << std::endl << std::endl;
    
    // 创建一个简单的DOM结构
    auto html = NodeUtils::createElement("html");
    
    // 创建head
    auto head = NodeUtils::createElement("head");
    auto title = NodeUtils::createElement("title");
    auto titleText = NodeUtils::createTextNode("CHTL Test Page");
    title->appendChild(titleText);
    head->appendChild(title);
    html->appendChild(head);
    
    // 创建body
    auto body = NodeUtils::createElement("body");
    body->setAttribute("class", "main-body");
    body->setAttribute("id", "body-id");
    
    // 创建一个div容器
    auto div = NodeUtils::createElement("div");
    div->setAttribute("class", "container");
    div->setAttribute("id", "main");
    
    // 添加样式属性
    div->setStyleProperty("width", "100%");
    div->setStyleProperty("padding", "20px");
    
    // 创建标题
    auto h1 = NodeUtils::createElement("h1");
    h1->appendChild(NodeUtils::createTextNode("Welcome to CHTL"));
    div->appendChild(h1);
    
    // 创建段落
    auto p = NodeUtils::createElement("p");
    p->setAttribute("class", "intro text-primary");
    p->appendChild(NodeUtils::createTextNode("This is a test of the Node system."));
    div->appendChild(p);
    
    // 创建无引号文本（CHTL特有）
    auto unquotedDiv = NodeUtils::createElement("div");
    auto unquotedText = NodeUtils::createTextNode("HelloWorld", true); // true表示无引号
    unquotedDiv->appendChild(unquotedText);
    div->appendChild(unquotedDiv);
    
    // 创建自定义元素（CHTL特有）
    auto customCard = NodeUtils::createElement("Card");
    customCard->setCustomElement(true);
    customCard->setAttribute("title", "My Card");
    customCard->appendChild(NodeUtils::createTextNode("Custom element content"));
    div->appendChild(customCard);
    
    body->appendChild(div);
    html->appendChild(body);
    
    // 测试查询功能
    std::cout << "1. 查询测试" << std::endl;
    std::cout << "   - 通过ID查找: " << (html->getElementById("main") ? "找到" : "未找到") << std::endl;
    std::cout << "   - 通过类名查找: " << html->getElementsByClassName("container").size() << " 个元素" << std::endl;
    std::cout << "   - 通过标签名查找div: " << html->getElementsByTagName("div").size() << " 个元素" << std::endl;
    
    // 测试DOM操作
    std::cout << "\n2. DOM操作测试" << std::endl;
    auto mainDiv = html->getElementById("main");
    if (mainDiv) {
        std::cout << "   - 子节点数量: " << mainDiv->getChildren().size() << std::endl;
        std::cout << "   - 文本内容: " << mainDiv->getTextContent() << std::endl;
    }
    
    // 测试属性操作
    std::cout << "\n3. 属性操作测试" << std::endl;
    if (body) {
        std::cout << "   - body的class: " << body->getClassName() << std::endl;
        std::cout << "   - body的id: " << body->getId() << std::endl;
        
        body->addClass("additional-class");
        std::cout << "   - 添加class后: " << body->getClassName() << std::endl;
    }
    
    // 测试克隆
    std::cout << "\n4. 节点克隆测试" << std::endl;
    auto clonedDiv = std::static_pointer_cast<Element>(div->clone(true));
    std::cout << "   - 克隆的div子节点数: " << clonedDiv->getChildren().size() << std::endl;
    
    // 输出为HTML
    std::cout << "\n5. HTML输出:" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << NodeUtils::toHTML(html, true) << std::endl;
    
    // 输出为CHTL
    std::cout << "6. CHTL输出:" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << NodeUtils::toCHTL(html, true) << std::endl;
    
    // 测试文本节点操作
    std::cout << "7. 文本节点操作测试" << std::endl;
    auto text = std::make_shared<Text>("Hello World");
    std::cout << "   - 原始文本: " << text->getData() << std::endl;
    
    text->insertData(5, " Beautiful");
    std::cout << "   - 插入后: " << text->getData() << std::endl;
    
    auto splitText = text->splitText(5);
    std::cout << "   - 分割后第一部分: " << text->getData() << std::endl;
    std::cout << "   - 分割后第二部分: " << splitText->getData() << std::endl;
    
    return 0;
}