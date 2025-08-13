#include "HtmlGenerator.h"
#include <algorithm>
#include <unordered_set>

namespace chtl {
namespace generator {

static const std::unordered_set<std::string> SELF_CLOSING_TAGS = {
    "area", "base", "br", "col", "embed", "hr", "img", "input",
    "link", "meta", "param", "source", "track", "wbr"
};

HtmlGenerator::HtmlGenerator() {
    // 初始化
}

void HtmlGenerator::generateElement(const std::string& tagName, 
                                  const std::map<std::string, std::string>& attributes,
                                  const std::string& content) {
    openTag(tagName, attributes);
    
    if (!content.empty()) {
        output << content;
    }
    
    if (!isSelfClosingTag(tagName)) {
        closeTag(tagName);
    }
}

void HtmlGenerator::generateText(const std::string& text) {
    writeIndent();
    output << escapeHtml(text);
    if (prettyPrint) {
        output << "\n";
    }
}

void HtmlGenerator::generateComment(const std::string& comment) {
    writeIndent();
    output << "<!-- " << comment << " -->";
    if (prettyPrint) {
        output << "\n";
    }
}

void HtmlGenerator::openTag(const std::string& tagName, 
                           const std::map<std::string, std::string>& attributes) {
    writeIndent();
    output << "<" << tagName;
    
    // 添加属性
    for (const auto& [key, value] : attributes) {
        output << " " << key;
        if (!value.empty()) {
            output << "=\"" << escapeHtml(value) << "\"";
        }
    }
    
    if (isSelfClosingTag(tagName)) {
        output << " />";
    } else {
        output << ">";
        indentLevel++;
    }
    
    if (prettyPrint) {
        output << "\n";
    }
}

void HtmlGenerator::closeTag(const std::string& tagName) {
    indentLevel--;
    writeIndent();
    output << "</" << tagName << ">";
    if (prettyPrint) {
        output << "\n";
    }
}

void HtmlGenerator::writeIndent() {
    if (prettyPrint) {
        for (int i = 0; i < indentLevel; i++) {
            output << "  ";
        }
    }
}

std::string HtmlGenerator::escapeHtml(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    
    for (char c : text) {
        switch (c) {
            case '&':  result += "&amp;"; break;
            case '<':  result += "&lt;"; break;
            case '>':  result += "&gt;"; break;
            case '"':  result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default:   result += c; break;
        }
    }
    
    return result;
}

bool HtmlGenerator::isSelfClosingTag(const std::string& tagName) {
    return SELF_CLOSING_TAGS.find(tagName) != SELF_CLOSING_TAGS.end();
}

} // namespace generator
} // namespace chtl