#include <iostream>
#include <memory>
#include "node/Node.h"
#include "node/Comment.h"
#include "node/Template.h"
#include "node/Custom.h"
#include "node/Style.h"
#include "node/Config.h"
#include "node/Import.h"
#include "node/Namespace.h"
#include "node/Operate.h"

using namespace chtl;
using namespace std;

void printSeparator(const string& title) {
    cout << "\n========== " << title << " ==========\n";
}

void testCommentNode() {
    printSeparator("Testing Comment Node");
    
    // 单行注释
    auto singleLine = make_shared<Comment>(Comment::CommentType::SINGLE_LINE, " This is a single line comment");
    cout << "Single line: " << singleLine->toString() << endl;
    
    // 多行注释
    auto multiLine = make_shared<Comment>(Comment::CommentType::MULTI_LINE, " This is a\nmulti-line comment ");
    cout << "Multi line: " << multiLine->toString() << endl;
    
    // HTML注释
    auto htmlComment = make_shared<Comment>(Comment::CommentType::HTML, " HTML style comment ");
    cout << "HTML: " << htmlComment->toString() << endl;
}

void testTemplateNode() {
    printSeparator("Testing Template Node");
    
    // @Style模板
    auto styleTemplate = make_shared<Template>(Template::TemplateType::STYLE, "Button");
    styleTemplate->setParameter("background", "#007bff");
    styleTemplate->setParameter("color", "white");
    styleTemplate->addInheritance("BaseButton");
    cout << "Style Template:\n" << styleTemplate->toString() << endl;
    
    // @Element模板
    auto elementTemplate = make_shared<Template>(Template::TemplateType::ELEMENT, "Card");
    elementTemplate->setParameter("width", "300px");
    elementTemplate->setParameter("shadow", "true");
    auto cardContent = make_shared<Element>("div");
    cardContent->addClass("card-body");
    elementTemplate->appendChild(cardContent);
    cout << "\nElement Template:\n" << elementTemplate->toString() << endl;
    
    // @Var模板
    auto varTemplate = make_shared<Template>(Template::TemplateType::VAR, "colors");
    varTemplate->setParameter("primary", "#007bff");
    varTemplate->setParameter("secondary", "#6c757d");
    cout << "\nVar Template:\n" << varTemplate->toString() << endl;
}

void testCustomNode() {
    printSeparator("Testing Custom Node");
    
    // 自定义元素
    auto customElement = make_shared<Custom>(Custom::CustomType::ELEMENT, "MyButton");
    customElement->setProperty("extends", "button");
    customElement->setProperty("variant", "primary");
    customElement->addDelete("disabled");
    cout << "Custom Element:\n" << customElement->toString() << endl;
    
    // 自定义样式
    auto customStyle = make_shared<Custom>(Custom::CustomType::STYLE, "hover-effect");
    customStyle->setProperty("transition", "all 0.3s ease");
    customStyle->setProperty("transform", "scale(1.05)");
    cout << "\nCustom Style:\n" << customStyle->toString() << endl;
    
    // 自定义变量
    auto customVar = make_shared<Custom>(Custom::CustomType::VAR, "theme");
    customVar->setProperty("mode", "dark");
    customVar->setProperty("accent", "#ff6b6b");
    cout << "\nCustom Var:\n" << customVar->toString() << endl;
}

void testStyleNode() {
    printSeparator("Testing Style Node");
    
    // 全局样式
    auto globalStyle = make_shared<Style>(Style::StyleScope::GLOBAL);
    globalStyle->setCssContent("body {\n  margin: 0;\n  padding: 0;\n  font-family: Arial, sans-serif;\n}");
    cout << "Global Style:\n" << globalStyle->toString() << endl;
    
    // 局部样式
    auto localStyle = make_shared<Style>(Style::StyleScope::LOCAL);
    localStyle->addSelector(".container");
    localStyle->addRule("max-width", "1200px");
    localStyle->addRule("margin", "0 auto");
    localStyle->setParentElement("div");
    cout << "\nLocal Style:\n" << localStyle->toString() << endl;
    
    // 作用域样式
    auto scopedStyle = make_shared<Style>(Style::StyleScope::GLOBAL);
    scopedStyle->setScoped(true);
    scopedStyle->setCssContent(".scoped-class {\n  color: red;\n}");
    cout << "\nScoped Style:\n" << scopedStyle->toString() << endl;
}

void testConfigNode() {
    printSeparator("Testing Config Node");
    
    auto config = make_shared<Config>("app-config");
    config->setConfig("version", "1.0.0");
    config->setConfig("debug", "true");
    config->setConfig("output_dir", "./dist");
    
    vector<string> features = {"responsive", "dark-mode", "animations"};
    config->setArrayConfig("features", features);
    
    cout << "Configuration:\n" << config->toString() << endl;
}

void testImportNode() {
    printSeparator("Testing Import Node");
    
    // 简单导入
    auto simpleImport = make_shared<Import>("./components/Button.chtl");
    cout << "Simple Import: " << simpleImport->toString() << endl;
    
    // 具体导入项
    auto specificImport = make_shared<Import>("./utils/helpers.chtl");
    specificImport->addImportItem("formatDate", "fmtDate");
    specificImport->addImportItem("parseJSON");
    cout << "\nSpecific Import:\n" << specificImport->toString() << endl;
    
    // 导入所有
    auto importAll = make_shared<Import>("./styles/theme.chtl");
    importAll->addImportItem("*");
    cout << "\nImport All: " << importAll->toString() << endl;
    
    // 命名空间导入
    auto namespaceImport = make_shared<Import>("./lib/components.chtl");
    namespaceImport->setNamespaceImport(true);
    namespaceImport->setTargetNamespace("Components");
    cout << "\nNamespace Import: " << namespaceImport->toString() << endl;
}

void testNamespaceNode() {
    printSeparator("Testing Namespace Node");
    
    // 基本命名空间
    auto ns = make_shared<Namespace>("Utils");
    auto func = make_shared<Element>("function");
    func->setAttribute("name", "helper");
    ns->appendChild(func);
    cout << "Basic Namespace:\n" << ns->toString() << endl;
    
    // 导出的命名空间
    auto exportNs = make_shared<Namespace>("Components");
    exportNs->setExport(true);
    auto button = make_shared<Element>("Button");
    exportNs->appendChild(button);
    cout << "\nExported Namespace:\n" << exportNs->toString() << endl;
}

void testOperateNode() {
    printSeparator("Testing Operate Node");
    
    // Insert操作
    auto insertOp = make_shared<Operate>(Operate::OperationType::INSERT);
    insertOp->setPosition(Operate::Position::AFTER);
    insertOp->setTarget("#header");
    auto nav = make_shared<Element>("nav");
    nav->addClass("main-nav");
    insertOp->appendChild(nav);
    cout << "Insert Operation:\n" << insertOp->toString() << endl;
    
    // Delete操作
    auto deleteOp = make_shared<Operate>(Operate::OperationType::DELETE);
    deleteOp->setSelector(".deprecated");
    deleteOp->addConstraint(".keep-this");
    cout << "\nDelete Operation:\n" << deleteOp->toString() << endl;
    
    // Replace操作
    auto replaceOp = make_shared<Operate>(Operate::OperationType::REPLACE);
    replaceOp->setTarget(".old-component");
    auto newComponent = make_shared<Element>("div");
    newComponent->addClass("new-component");
    replaceOp->setContent(newComponent);
    cout << "\nReplace Operation:\n" << replaceOp->toString() << endl;
}

int main() {
    cout << "CHTL Node System Test\n";
    cout << "====================\n";
    
    try {
        testCommentNode();
        testTemplateNode();
        testCustomNode();
        testStyleNode();
        testConfigNode();
        testImportNode();
        testNamespaceNode();
        testOperateNode();
        
        cout << "\n\nAll tests completed successfully!\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}