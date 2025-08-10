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
    
    std::cout << "Testing constraint matching:\n";
    std::cout << "===========================\n\n";
    
    std::cout << "Constraint: 'span'\n";
    std::cout << "Constraints on div: ";
    for (const auto& c : divElement->getConstraints()) {
        std::cout << "'" << c << "' ";
    }
    std::cout << "\n\n";
    
    // 测试matchesConstraint
    auto validator = std::make_shared<ConstraintValidator>(nullptr);
    
    // 创建span元素
    auto spanElement = std::make_shared<Element>("span");
    std::cout << "Created element with tag: '" << spanElement->getTagName() << "'\n";
    std::cout << "Element type: " << static_cast<int>(spanElement->getType()) << " (ELEMENT=" << static_cast<int>(NodeType::ELEMENT) << ")\n\n";
    
    // 手动调用内部方法测试（需要friend class或者公开方法）
    // 由于是私有方法，我们通过完整的验证流程来测试
    
    // 添加span到div
    divElement->addChild(spanElement);
    
    // 创建root
    auto root = std::make_shared<Element>("body");
    root->addChild(divElement);
    
    // 运行验证
    bool valid = validator->validateConstraints(root);
    
    std::cout << "Validation result: " << (valid ? "PASSED" : "FAILED") << "\n";
    
    auto violations = validator->getViolations();
    std::cout << "Violations found: " << violations.size() << "\n";
    
    if (!violations.empty()) {
        for (const auto& v : violations) {
            std::cout << "  - " << v.violations[0] << "\n";
            std::cout << "    Type: " << static_cast<int>(v.type) << "\n";
            std::cout << "    Value: '" << v.value << "'\n";
            std::cout << "    Scope: '" << v.scope << "'\n";
        }
    }
    
    return 0;
}