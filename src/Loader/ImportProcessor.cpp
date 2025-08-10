#include "Loader/ImportProcessor.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Node/Element.h"

namespace chtl {

namespace fs = std::filesystem;

ImportProcessor::ImportProcessor(std::shared_ptr<BasicContext> context)
    : context_(context), resolver_(std::make_shared<ImportResolver>()) {
}

ImportProcessResult ImportProcessor::processImport(std::shared_ptr<Import> importNode, 
                                                  const std::string& currentFilePath) {
    ImportProcessResult result;
    
    if (!importNode) {
        result.errors.push_back("Null import node");
        return result;
    }
    
    // 验证导入类型和as的组合
    if (!validateImportCombination(importNode)) {
        result.errors.push_back("Invalid import combination");
        return result;
    }
    
    // 解析文件路径
    auto resolveResult = resolver_->resolve(importNode->getPath(), 
                                           importNode->getType(), 
                                           currentFilePath);
    
    if (!resolveResult.success) {
        result.errors.push_back(resolveResult.errorMessage);
        return result;
    }
    
    // 根据导入类型处理
    switch (importNode->getType()) {
        case Import::ImportType::HTML:
            return processHtmlImport(importNode, resolveResult.resolvedPath);
            
        case Import::ImportType::CSS:
            return processCssImport(importNode, resolveResult.resolvedPath);
            
        case Import::ImportType::JS:
            return processJsImport(importNode, resolveResult.resolvedPath);
            
        case Import::ImportType::CHTL:
            return processChtlImport(importNode, resolveResult.resolvedPath);
            
        default:
            result.errors.push_back("Unsupported import type for direct processing");
            return result;
    }
}

ImportProcessResult ImportProcessor::processHtmlImport(std::shared_ptr<Import> importNode,
                                                      const std::string& resolvedPath) {
    ImportProcessResult result;
    
    // 如果没有as（别名），跳过此导入
    if (importNode->getAlias().empty()) {
        result.warnings.push_back("HTML import without 'as' clause is skipped");
        result.success = true;
        return result;
    }
    
    // 读取HTML文件内容
    std::string content = readFileContent(resolvedPath);
    if (content.empty()) {
        result.errors.push_back("Failed to read HTML file: " + resolvedPath);
        return result;
    }
    
    // 创建Origin节点
    auto originNode = createOriginNode(Origin::OriginType::HTML, content, importNode->getAlias());
    if (originNode) {
        result.generatedNodes.push_back(originNode);
        result.success = true;
        
        // 注册到上下文
        if (context_) {
            // TODO: 实现符号注册
            // context_->registerSymbol(importNode->getAlias(), originNode);
        }
    }
    
    return result;
}

ImportProcessResult ImportProcessor::processCssImport(std::shared_ptr<Import> importNode,
                                                     const std::string& resolvedPath) {
    ImportProcessResult result;
    
    // 创建link节点
    auto linkNode = createLinkNode(resolvedPath);
    if (linkNode) {
        result.generatedNodes.push_back(linkNode);
    }
    
    // 如果有别名，创建Origin节点（内容为@import语句）
    if (!importNode->getAlias().empty()) {
        std::string importContent = "@import url('" + resolvedPath + "');";
        auto originNode = createOriginNode(Origin::OriginType::STYLE, importContent, importNode->getAlias());
        result.generatedNodes.push_back(originNode);
        
        if (context_) {
            // TODO: 实现符号注册
            // context_->registerSymbol(importNode->getAlias(), originNode);
        }
    }
    
    result.success = true;
    return result;
}

ImportProcessResult ImportProcessor::processJsImport(std::shared_ptr<Import> importNode,
                                                    const std::string& resolvedPath) {
    ImportProcessResult result;
    
    // 创建script节点
    auto scriptNode = createScriptNode(resolvedPath);
    if (scriptNode) {
        result.generatedNodes.push_back(scriptNode);
    }
    
    // 如果有别名，创建Origin节点（内容为模块导入语句）
    if (!importNode->getAlias().empty()) {
        std::string importContent = "import * as " + importNode->getAlias() + " from '" + resolvedPath + "';";
        auto originNode = createOriginNode(Origin::OriginType::JAVASCRIPT, importContent, importNode->getAlias());
        result.generatedNodes.push_back(originNode);
        
        if (context_) {
            // TODO: 实现符号注册
            // context_->registerSymbol(importNode->getAlias(), originNode);
        }
    }
    
    result.success = true;
    return result;
}

ImportProcessResult ImportProcessor::processChtlImport(std::shared_ptr<Import> importNode,
                                                      const std::string& resolvedPath) {
    ImportProcessResult result;
    
    // CHTL导入由ImportManager处理，这里只返回成功
    result.success = true;
    result.warnings.push_back("CHTL import should be handled by ImportManager");
    
    return result;
}

std::shared_ptr<Origin> ImportProcessor::createOriginNode(Origin::OriginType type,
                                                         const std::string& content,
                                                         const std::string& name) {
    auto originNode = std::make_shared<Origin>(type);
    originNode->setContent(content);
    
    if (!name.empty()) {
        originNode->setAttribute("name", name);
    }
    
    return originNode;
}

std::shared_ptr<Node> ImportProcessor::createLinkNode(const std::string& href) {
    auto linkNode = std::make_shared<Element>("link");
    linkNode->setAttribute("rel", "stylesheet");
    linkNode->setAttribute("href", href);
    return linkNode;
}

std::shared_ptr<Node> ImportProcessor::createScriptNode(const std::string& src,
                                                       const std::string& content) {
    auto scriptNode = std::make_shared<Element>("script");
    
    if (!src.empty()) {
        scriptNode->setAttribute("src", src);
    }
    
    if (!content.empty()) {
        scriptNode->setText(content);
    }
    
    return scriptNode;
}

std::string ImportProcessor::readFileContent(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool ImportProcessor::validateImportCombination(std::shared_ptr<Import> importNode) {
    // @Html导入必须有as才有意义
    if (importNode->getType() == Import::ImportType::HTML && 
        importNode->getAlias().empty()) {
        // 这是有效的，只是会被跳过
        return true;
    }
    
    return true;
}

} // namespace chtl