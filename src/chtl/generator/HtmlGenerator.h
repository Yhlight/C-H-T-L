#ifndef CHTL_HTML_GENERATOR_H
#define CHTL_HTML_GENERATOR_H

#include <string>
#include <sstream>
#include <map>
#include <memory>
#include "../core/Types.h"

namespace chtl {
namespace generator {

class HtmlGenerator {
public:
    HtmlGenerator();
    
    // HTML生成方法
    void generateElement(const std::string& tagName, 
                        const std::map<std::string, std::string>& attributes,
                        const std::string& content = "");
    
    void generateText(const std::string& text);
    void generateComment(const std::string& comment);
    
    void openTag(const std::string& tagName, 
                const std::map<std::string, std::string>& attributes = {});
    void closeTag(const std::string& tagName);
    
    // 获取生成的HTML
    std::string getOutput() const { return output.str(); }
    void clear() { output.str(""); output.clear(); }
    
private:
    std::stringstream output;
    int indentLevel = 0;
    bool prettyPrint = true;
    
    // 辅助方法
    void writeIndent();
    std::string escapeHtml(const std::string& text);
    bool isSelfClosingTag(const std::string& tagName);
};

} // namespace generator
} // namespace chtl

#endif // CHTL_HTML_GENERATOR_H