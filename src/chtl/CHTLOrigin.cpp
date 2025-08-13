#include "CHTLOrigin.h"
#include "CHTLGenerator.h"
#include <regex>
#include <sstream>

namespace chtl {

// OriginDefinition 实现
void OriginDefinition::generate(CHTLGenerator& generator) const {
    // 原原本本输出内容，不做任何处理
    generator.generateRawContent(content);
}

// OriginManager 实现
bool OriginManager::registerNamedOrigin(const std::string& name, std::shared_ptr<OriginDefinition> origin) {
    if (name.empty()) {
        context->reportError("Cannot register origin with empty name");
        return false;
    }
    
    namedOrigins[name] = origin;
    return true;
}

std::shared_ptr<OriginDefinition> OriginManager::findNamedOrigin(const std::string& name) const {
    auto it = namedOrigins.find(name);
    if (it != namedOrigins.end()) {
        return it->second;
    }
    return nullptr;
}

bool OriginManager::useNamedOrigin(const std::string& name, CHTLGenerator& generator) {
    auto origin = findNamedOrigin(name);
    if (!origin) {
        context->reportError("Named origin not found: " + name);
        return false;
    }
    
    // 生成原始内容
    origin->generate(generator);
    return true;
}

void OriginManager::addImmediateOrigin(std::shared_ptr<OriginDefinition> origin) {
    immediateOrigins.push_back(origin);
}

void OriginManager::generateImmediateOrigins(CHTLGenerator& generator) {
    for (const auto& origin : immediateOrigins) {
        origin->generate(generator);
    }
    clearImmediateOrigins();
}

// OriginProcessor 实现
bool OriginProcessor::processOriginStatement(const std::string& statement) {
    auto decl = parseOriginDeclaration(statement);
    
    if (decl.isUsage) {
        // 使用命名的原始嵌入
        return manager.useNamedOrigin(decl.name, generator);
    } else {
        // 创建新的原始嵌入
        auto origin = createOriginInstance(decl);
        if (origin) {
            if (decl.isNamed) {
                return manager.registerNamedOrigin(decl.name, origin);
            } else {
                manager.addImmediateOrigin(origin);
                return true;
            }
        }
    }
    
    return false;
}

OriginProcessor::OriginDeclaration OriginProcessor::parseOriginDeclaration(const std::string& declaration) {
    OriginDeclaration decl;
    
    // 解析格式：
    // [Origin] @Html { ... }
    // [Origin] @Style myStyle { ... }
    // [Origin] @Html myHtml;  (使用)
    
    std::regex defineRegex(R"(\[Origin\]\s+(@\w+)(?:\s+(\w+))?\s*\{)");
    std::regex useRegex(R"(\[Origin\]\s+(@\w+)\s+(\w+)\s*;)");
    
    std::smatch match;
    
    if (std::regex_match(declaration, match, defineRegex)) {
        decl.syntaxType = match[1];
        decl.name = match[2];
        decl.isNamed = !decl.name.empty();
        decl.isUsage = false;
    } else if (std::regex_match(declaration, match, useRegex)) {
        decl.syntaxType = match[1];
        decl.name = match[2];
        decl.isNamed = true;
        decl.isUsage = true;
    }
    
    return decl;
}

std::shared_ptr<OriginDefinition> OriginProcessor::createOriginInstance(const OriginDeclaration& decl) {
    return std::make_shared<OriginDefinition>(decl.name, decl.syntaxType, decl.isNamed);
}

void OriginProcessor::processOriginContent(std::shared_ptr<OriginDefinition> origin, const std::string& content) {
    // 直接存储内容，不做任何处理
    origin->setContent(content);
}

// OriginHelper 实现
namespace OriginHelper {

std::pair<std::string, std::string> parseOriginSyntax(const std::string& syntax) {
    // 解析 [Origin] @Html -> ("@Html", "")
    // 解析 [Origin] @Style myStyle -> ("@Style", "myStyle")
    
    std::regex syntaxRegex(R"(\[Origin\]\s+(@\w+)(?:\s+(\w+))?)");
    std::smatch match;
    
    if (std::regex_match(syntax, match, syntaxRegex)) {
        return {match[1], match[2]};
    }
    
    return {"", ""};
}

bool isOriginStatement(const std::string& statement) {
    return statement.find("[Origin]") == 0;
}

std::string extractRawContent(const std::string& wrappedContent) {
    // 去除首尾的大括号
    if (wrappedContent.length() >= 2) {
        size_t start = wrappedContent.find('{');
        size_t end = wrappedContent.rfind('}');
        
        if (start != std::string::npos && end != std::string::npos && start < end) {
            return wrappedContent.substr(start + 1, end - start - 1);
        }
    }
    
    return wrappedContent;
}

} // namespace OriginHelper

} // namespace chtl