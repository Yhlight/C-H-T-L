#include "v2/Parser/ChtlParser.h"
#include <iostream>
#include <fstream>

using namespace chtl::v2;

// 简单的 AST 打印访问者
class AstPrinter : public NodeVisitor {
public:
    void visitDocument(Document* node) override {
        std::cout << "Document {\n";
        indent_++;
        for (auto& child : node->getChildren()) {
            child->accept(*this);
        }
        indent_--;
        std::cout << "}\n";
    }
    
    void visitElement(Element* node) override {
        printIndent();
        std::cout << "Element: " << node->getTag();
        if (!node->getId().empty()) {
            std::cout << "#" << node->getId();
        }
        for (const auto& cls : node->getClasses()) {
            std::cout << "." << cls;
        }
        std::cout << " {\n";
        
        indent_++;
        
        // 打印属性
        for (const auto& [name, value] : node->getAttributes()) {
            printIndent();
            std::cout << "Attr: " << name << " = \"" << value << "\"\n";
        }
        
        // 打印局部样式
        if (!node->getLocalStyle().empty()) {
            printIndent();
            std::cout << "LocalStyle: " << node->getLocalStyle() << "\n";
        }
        
        // 打印子节点
        for (auto& child : node->getChildren()) {
            child->accept(*this);
        }
        
        indent_--;
        printIndent();
        std::cout << "}\n";
    }
    
    void visitText(Text* node) override {
        printIndent();
        std::cout << "Text: \"" << node->getContent() << "\"\n";
    }
    
    void visitStyle(Style* node) override {
        printIndent();
        std::cout << "Style (" << (node->isGlobal() ? "global" : "local") << "): {\n";
        indent_++;
        printIndent();
        std::cout << node->getCssContent() << "\n";
        indent_--;
        printIndent();
        std::cout << "}\n";
    }
    
    void visitScript(Script* node) override {
        printIndent();
        std::cout << "Script (" << (node->isGlobal() ? "global" : "local") << ")";
        if (node->hasChtlJs()) {
            std::cout << " [contains CHTL-JS]";
        }
        std::cout << ": {\n";
        indent_++;
        printIndent();
        std::cout << node->getJsContent() << "\n";
        indent_--;
        printIndent();
        std::cout << "}\n";
    }
    
    void visitTemplate(Template* node) override {
        printIndent();
        std::cout << "Template " << node->getTemplateType() << " " << node->getName();
        
        // 打印参数
        if (!node->getParameters().empty()) {
            std::cout << "(";
            bool first = true;
            for (const auto& [param, defaultVal] : node->getParameters()) {
                if (!first) std::cout << ", ";
                std::cout << param;
                if (!defaultVal.empty()) {
                    std::cout << " = \"" << defaultVal << "\"";
                }
                first = false;
            }
            std::cout << ")";
        }
        
        std::cout << " {\n";
        indent_++;
        for (auto& child : node->getChildren()) {
            child->accept(*this);
        }
        indent_--;
        printIndent();
        std::cout << "}\n";
    }
    
    void visitReference(Reference* node) override {
        printIndent();
        std::cout << "Reference " << node->getReferenceType() << " " << node->getName();
        
        // 打印参数
        if (!node->getArguments().empty()) {
            std::cout << "(";
            bool first = true;
            for (const auto& arg : node->getArguments()) {
                if (!first) std::cout << ", ";
                std::cout << "\"" << arg << "\"";
                first = false;
            }
            std::cout << ")";
        }
        
        std::cout << "\n";
    }
    
private:
    void printIndent() {
        for (int i = 0; i < indent_; ++i) {
            std::cout << "  ";
        }
    }
    
    int indent_ = 0;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.chtl>\n";
        return 1;
    }
    
    // 读取文件
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }
    
    std::string input((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
    
    // 创建解析器
    ChtlParser parser;
    
    // 解析
    std::cout << "Parsing " << argv[1] << "...\n\n";
    ParseResult result = parser.parse(input);
    
    // 打印结果
    if (result.success) {
        std::cout << "Parse successful!\n\n";
        
        // 打印 AST
        std::cout << "AST:\n";
        AstPrinter printer;
        result.ast->accept(printer);
        
        // 打印 CSS 分析结果
        if (!result.cssResults.empty()) {
            std::cout << "\nCSS Analysis:\n";
            for (const auto& css : result.cssResults) {
                std::cout << "  Valid: " << (css.valid ? "yes" : "no") << "\n";
                std::cout << "  Rules: " << css.rules.size() << "\n";
                std::cout << "  @Rules: " << css.atRules.size() << "\n";
                if (!css.errors.empty()) {
                    std::cout << "  Errors:\n";
                    for (const auto& error : css.errors) {
                        std::cout << "    - " << error << "\n";
                    }
                }
            }
        }
        
        // 打印 JS 分析结果
        if (!result.jsResults.empty()) {
            std::cout << "\nJS Analysis:\n";
            for (const auto& js : result.jsResults) {
                std::cout << "  Valid: " << (js.valid ? "yes" : "no") << "\n";
                std::cout << "  Variables: " << js.variables.size() << "\n";
                std::cout << "  Functions: " << js.functions.size() << "\n";
                std::cout << "  Imports: " << js.imports.size() << "\n";
                std::cout << "  Exports: " << js.exports.size() << "\n";
                if (!js.errors.empty()) {
                    std::cout << "  Errors:\n";
                    for (const auto& error : js.errors) {
                        std::cout << "    - " << error << "\n";
                    }
                }
            }
        }
    } else {
        std::cout << "Parse failed!\n\n";
    }
    
    // 打印错误和警告
    if (!result.errors.empty()) {
        std::cout << "\nErrors:\n";
        for (const auto& error : result.errors) {
            std::cout << "  " << error << "\n";
        }
    }
    
    if (!result.warnings.empty()) {
        std::cout << "\nWarnings:\n";
        for (const auto& warning : result.warnings) {
            std::cout << "  " << warning << "\n";
        }
    }
    
    return result.success ? 0 : 1;
}