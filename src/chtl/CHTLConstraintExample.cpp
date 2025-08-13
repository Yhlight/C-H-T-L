#include "CHTLGenerator.h"
#include "CHTLConstraint.h"
#include <iostream>

using namespace chtl;

// 示例：演示CHTL约束的使用
int main() {
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取约束管理器
    auto constraintManager = generator.getConstraintManager();
    auto namespaceManager = generator.getNamespaceManager();
    
    // 示例1：精确约束
    std::cout << "=== 示例1：精确约束 ===" << std::endl;
    
    // 在div中禁止使用span和自定义元素Box
    generator.addElementConstraint("div", "except span, [Custom] @Element Box;");
    
    generator.generateElement("div", {});
    
    // 尝试使用被禁止的span（会失败）
    std::cout << "尝试在div中使用span（被禁止）：" << std::endl;
    generator.generateElement("span", {});  // 这会触发约束错误
    
    // 使用允许的元素
    generator.generateElement("p", {});
    generator.generateTextNode("这是允许的段落");
    generator.closeElement();
    
    generator.closeElement(); // </div>
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例2：类型约束
    std::cout << "\n=== 示例2：类型约束 ===" << std::endl;
    generator.reset();
    constraintManager->clear();
    
    // 在section中禁止所有HTML元素
    generator.addElementConstraint("section", "except @Html;");
    
    generator.generateElement("section", {});
    
    // 尝试使用HTML元素（会失败）
    std::cout << "尝试在section中使用HTML元素（被禁止）：" << std::endl;
    generator.generateElement("div", {});  // 这会触发约束错误
    
    // 可以使用自定义元素（如果有的话）
    generator.generateTextNode("Section只能包含文本和自定义元素");
    
    generator.closeElement(); // </section>
    
    // 示例3：禁止特定类型的模板
    std::cout << "\n=== 示例3：禁止特定类型的模板 ===" << std::endl;
    generator.reset();
    constraintManager->clear();
    
    // 在main中禁止使用变量组模板
    generator.addElementConstraint("main", "except [Template] @Var;");
    
    generator.generateElement("main", {});
    
    // 可以使用其他类型的模板
    generator.beginStyleBlock();
    // 这里可以使用样式模板
    generator.endStyleBlock();
    
    generator.closeElement(); // </main>
    
    // 示例4：禁止所有自定义
    std::cout << "\n=== 示例4：禁止所有自定义 ===" << std::endl;
    generator.reset();
    constraintManager->clear();
    
    // 在article中禁止所有自定义
    generator.addElementConstraint("article", "except [Custom];");
    
    generator.generateElement("article", {});
    
    // 只能使用HTML元素和模板
    generator.generateElement("h1", {});
    generator.generateTextNode("只能使用标准HTML");
    generator.closeElement();
    
    generator.closeElement(); // </article>
    
    // 示例5：全局约束（命名空间级别）
    std::cout << "\n=== 示例5：全局约束 ===" << std::endl;
    generator.reset();
    constraintManager->clear();
    
    // 创建命名空间并添加全局约束
    generator.beginNamespace("restricted");
    
    // 在此命名空间中禁止定义模板
    generator.addNamespaceConstraint("restricted", "except [Template];");
    
    std::cout << "在restricted命名空间中尝试定义模板（被禁止）：" << std::endl;
    // 尝试定义模板（会失败）
    if (!generator.checkConstraint("[Template]")) {
        std::cout << "模板定义被全局约束禁止" << std::endl;
    }
    
    // 可以定义自定义
    if (generator.checkConstraint("[Custom]")) {
        std::cout << "可以定义自定义（未被禁止）" << std::endl;
    }
    
    generator.endNamespace();
    
    // 示例6：组合约束
    std::cout << "\n=== 示例6：组合约束 ===" << std::endl;
    generator.reset();
    constraintManager->clear();
    
    // 在form中禁止多个元素
    generator.addElementConstraint("form", "except div, span, [Custom] @Element Card;");
    
    generator.generateElement("form", {});
    
    // 使用允许的元素
    generator.generateElement("input", {{"type", "text"}, {"name", "username"}});
    generator.closeElement();
    
    generator.generateElement("button", {{"type", "submit"}});
    generator.generateTextNode("提交");
    generator.closeElement();
    
    generator.closeElement(); // </form>
    
    std::cout << "HTML输出：" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    // 示例7：嵌套约束
    std::cout << "\n=== 示例7：嵌套约束 ===" << std::endl;
    generator.reset();
    constraintManager->clear();
    
    // 外层约束
    generator.addElementConstraint("outer", "except span;");
    // 内层约束
    generator.addElementConstraint("outer/inner", "except div;");
    
    generator.generateElement("outer", {});
    
    // 在outer中不能使用span
    generator.generateElement("p", {});
    generator.generateTextNode("外层段落");
    generator.closeElement();
    
    generator.generateElement("inner", {});
    // 在inner中不能使用div（同时继承了outer的约束，也不能使用span）
    generator.generateElement("em", {});
    generator.generateTextNode("内层强调");
    generator.closeElement();
    generator.closeElement(); // </inner>
    
    generator.closeElement(); // </outer>
    
    // 示例8：约束检查器
    std::cout << "\n=== 示例8：约束检查器 ===" << std::endl;
    
    ConstraintChecker checker(*constraintManager);
    checker.setCurrentElement("form");
    
    // 检查是否可以使用特定元素
    if (checker.canUseHtmlElement("input")) {
        std::cout << "可以在form中使用input元素" << std::endl;
    }
    
    if (!checker.canUseHtmlElement("div")) {
        std::cout << "不能在form中使用div元素（被约束禁止）" << std::endl;
    }
    
    // 检查是否可以使用自定义
    if (!checker.canUseCustom("@Element", "Card")) {
        std::cout << "不能在form中使用Card自定义元素（被约束禁止）" << std::endl;
    }
    
    return 0;
}

/* 预期输出示例：

=== 示例1：精确约束 ===
尝试在div中使用span（被禁止）：
Error: Constraint violation: Constraint in element 'div' prohibits use of HTML element 'span'
HTML输出：
<div>
  <p>这是允许的段落</p>
</div>

=== 示例2：类型约束 ===
尝试在section中使用HTML元素（被禁止）：
Error: Constraint violation: Constraint in element 'section' prohibits use of any HTML elements (@Html)

=== 示例5：全局约束 ===
在restricted命名空间中尝试定义模板（被禁止）：
模板定义被全局约束禁止
可以定义自定义（未被禁止）

=== 示例6：组合约束 ===
HTML输出：
<form>
  <input type="text" name="username">
  <button type="submit">提交</button>
</form>

=== 示例8：约束检查器 ===
可以在form中使用input元素
不能在form中使用div元素（被约束禁止）
不能在form中使用Card自定义元素（被约束禁止）

*/