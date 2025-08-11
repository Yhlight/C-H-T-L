#include <iostream>
#include <sstream>
#include <memory>
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Utils/ConstraintValidator.h"

using namespace chtl;

int main() {
    // 直接创建一个带约束的AST
    auto divElement = std::make_shared<Element>("div");
    divElement->addConstraint("span");
    divElement->addConstraint("[Custom] @Element Box");
    
    // 添加一个合法的子元素
    auto pElement = std::make_shared<Element>("p");
    divElement->addChild(pElement);
    
    // 添加一个违反约束的子元素
    auto spanElement = std::make_shared<Element>("span");
    divElement->addChild(spanElement);
    
    // 创建root节点
    auto root = std::make_shared<Element>("body");
    root->addChild(divElement);
    
    // 测试约束验证
    auto context = std::make_shared<StandardContext>();
    auto validator = std::make_shared<ConstraintValidator>(nullptr);
    
    std::cout << "Testing constraint validation:\n";
    std::cout << "==============================\n\n";
    
    std::cout << "Constraints on div: span, [Custom] @Element Box\n";
    std::cout << "Children of div: p, span\n\n";
    
    bool valid = validator->validateConstraints(root);
    
    std::cout << "Validation result: " << (valid ? "PASSED" : "FAILED") << "\n";
    
    auto violations = validator->getViolations();
    if (!violations.empty()) {
        std::cout << "\nViolations found:\n";
        for (const auto& v : violations) {
            std::cout << "  - " << v.violations[0] << "\n";
        }
    }
    
    // 测试类型约束
    std::cout << "\n\nTesting type constraints:\n";
    std::cout << "=========================\n\n";
    
    auto divElement2 = std::make_shared<Element>("div");
    divElement2->addConstraint("@Html");  // 禁止所有HTML元素
    
    auto textElement = std::make_shared<Text>("Some text");
    divElement2->addChild(textElement);  // OK
    
    auto spanElement2 = std::make_shared<Element>("span");
    divElement2->addChild(spanElement2);  // Violation!
    
    auto root2 = std::make_shared<Element>("body");
    root2->addChild(divElement2);
    
    auto validator2 = std::make_shared<ConstraintValidator>(nullptr);
    bool valid2 = validator2->validateConstraints(root2);
    
    std::cout << "Constraints on div: @Html\n";
    std::cout << "Children of div: text, span\n\n";
    std::cout << "Validation result: " << (valid2 ? "PASSED" : "FAILED") << "\n";
    
    auto violations2 = validator2->getViolations();
    if (!violations2.empty()) {
        std::cout << "\nViolations found:\n";
        for (const auto& v : violations2) {
            std::cout << "  - " << v.violations[0] << "\n";
        }
    }
    
    return 0;
}