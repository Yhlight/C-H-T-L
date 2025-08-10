#include "Loader/ImportProcessor.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Node/Element.h"
#include "Node/Custom.h"
#include "Node/Template.h"
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"

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
        case Import::ImportType::CUSTOM_ELEMENT:
        case Import::ImportType::CUSTOM_STYLE:
        case Import::ImportType::CUSTOM_VAR:
        case Import::ImportType::TEMPLATE_ELEMENT:
        case Import::ImportType::TEMPLATE_STYLE:
        case Import::ImportType::TEMPLATE_VAR:
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
    
    // 如果没有as（别名），跳过此导入
    if (importNode->getAlias().empty()) {
        result.warnings.push_back("CSS import without 'as' clause is skipped");
        result.success = true;
        return result;
    }
    
    // 读取CSS文件内容
    std::string content = readFileContent(resolvedPath);
    if (content.empty()) {
        result.errors.push_back("Failed to read CSS file: " + resolvedPath);
        return result;
    }
    
    // 创建Origin节点
    auto originNode = createOriginNode(Origin::OriginType::STYLE, content, importNode->getAlias());
    if (originNode) {
        result.generatedNodes.push_back(originNode);
        result.success = true;
        
        if (context_) {
            // TODO: 实现符号注册
            // context_->registerSymbol(importNode->getAlias(), originNode);
        }
    }
    
    return result;
}

ImportProcessResult ImportProcessor::processJsImport(std::shared_ptr<Import> importNode,
                                                    const std::string& resolvedPath) {
    ImportProcessResult result;
    
    // 如果没有as（别名），跳过此导入
    if (importNode->getAlias().empty()) {
        result.warnings.push_back("JavaScript import without 'as' clause is skipped");
        result.success = true;
        return result;
    }
    
    // 读取JS文件内容
    std::string content = readFileContent(resolvedPath);
    if (content.empty()) {
        result.errors.push_back("Failed to read JavaScript file: " + resolvedPath);
        return result;
    }
    
    // 创建Origin节点
    auto originNode = createOriginNode(Origin::OriginType::JAVASCRIPT, content, importNode->getAlias());
    if (originNode) {
        result.generatedNodes.push_back(originNode);
        result.success = true;
        
        if (context_) {
            // TODO: 实现符号注册
            // context_->registerSymbol(importNode->getAlias(), originNode);
        }
    }
    
    return result;
}

ImportProcessResult ImportProcessor::processChtlImport(std::shared_ptr<Import> importNode,
                                                      const std::string& resolvedPath) {
    ImportProcessResult result;
    
    // 对于具体的Custom和Template导入，需要解析CHTL文件并提取特定元素
    if (importNode->getType() >= Import::ImportType::CUSTOM_ELEMENT &&
        importNode->getType() <= Import::ImportType::TEMPLATE_VAR) {
        
        // 读取CHTL文件
        std::string content = readFileContent(resolvedPath);
        if (content.empty()) {
            result.errors.push_back("Failed to read CHTL file: " + resolvedPath);
            return result;
        }
        
        // 解析CHTL文件
        auto lexer = std::make_shared<StandardLexer>();
        auto parseContext = std::make_shared<StandardContext>();
        StandardParser parser(lexer, parseContext);
        
        auto input = std::make_unique<std::istringstream>(content);
        lexer->initialize(std::move(input), resolvedPath);
        
        auto ast = parser.parse();
        if (!ast || parseContext->hasErrors()) {
            result.errors.push_back("Failed to parse CHTL file: " + resolvedPath);
            for (const auto& error : parseContext->getErrors()) {
                result.errors.push_back("  " + error);
            }
            return result;
        }
        
        // 查找指定的元素
        std::string targetName = importNode->getName();
        std::shared_ptr<Node> foundNode = findNodeByNameAndType(ast, targetName, importNode->getType());
        
        if (!foundNode) {
            result.errors.push_back("Element '" + targetName + "' not found in " + resolvedPath);
            return result;
        }
        
        // 如果有别名，使用别名；否则使用原名
        std::string finalName = importNode->getAlias().empty() ? targetName : importNode->getAlias();
        
        // 克隆找到的节点并设置名称
        auto clonedNode = foundNode->clone(true);
        if (auto customNode = std::dynamic_pointer_cast<Custom>(clonedNode)) {
            customNode->setName(finalName);
        } else if (auto templateNode = std::dynamic_pointer_cast<Template>(clonedNode)) {
            templateNode->setName(finalName);
        }
        
        result.generatedNodes.push_back(clonedNode);
        result.success = true;
        
        if (context_) {
            // TODO: 注册符号
            // context_->registerSymbol(finalName, clonedNode);
        }
    } else {
        // 整个CHTL文件导入应该由ImportManager处理
        result.warnings.push_back("Full CHTL imports should be handled by ImportManager");
        result.success = true;
    }
    
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

std::shared_ptr<Node> ImportProcessor::findNodeByNameAndType(
    std::shared_ptr<Node> root, 
    const std::string& name, 
    Import::ImportType type) {
    
    // 递归查找匹配的节点
    std::function<std::shared_ptr<Node>(std::shared_ptr<Node>)> findNode;
    findNode = [&](std::shared_ptr<Node> node) -> std::shared_ptr<Node> {
        // 检查当前节点
        switch (type) {
            case Import::ImportType::CUSTOM_ELEMENT:
            case Import::ImportType::CUSTOM_STYLE:
            case Import::ImportType::CUSTOM_VAR:
                if (auto customNode = std::dynamic_pointer_cast<Custom>(node)) {
                    if (customNode->getCustomName() == name) {
                        // 还需要检查Custom类型
                        Custom::CustomType expectedType;
                        switch (type) {
                            case Import::ImportType::CUSTOM_ELEMENT:
                                expectedType = Custom::CustomType::ELEMENT;
                                break;
                            case Import::ImportType::CUSTOM_STYLE:
                                expectedType = Custom::CustomType::STYLE;
                                break;
                            case Import::ImportType::CUSTOM_VAR:
                                expectedType = Custom::CustomType::VAR;
                                break;
                            default:
                                return nullptr;
                        }
                        if (customNode->getCustomType() == expectedType) {
                            return node;
                        }
                    }
                }
                break;
                
            case Import::ImportType::TEMPLATE_ELEMENT:
            case Import::ImportType::TEMPLATE_STYLE:
            case Import::ImportType::TEMPLATE_VAR:
                if (auto templateNode = std::dynamic_pointer_cast<Template>(node)) {
                    if (templateNode->getTemplateName() == name) {
                        // 还需要检查Template类型
                        Template::TemplateType expectedType;
                        switch (type) {
                            case Import::ImportType::TEMPLATE_ELEMENT:
                                expectedType = Template::TemplateType::ELEMENT;
                                break;
                            case Import::ImportType::TEMPLATE_STYLE:
                                expectedType = Template::TemplateType::STYLE;
                                break;
                            case Import::ImportType::TEMPLATE_VAR:
                                expectedType = Template::TemplateType::VAR;
                                break;
                            default:
                                return nullptr;
                        }
                        if (templateNode->getTemplateType() == expectedType) {
                            return node;
                        }
                    }
                }
                break;
                
            default:
                break;
        }
        
        // 递归查找子节点
        for (const auto& child : node->getChildren()) {
            if (auto found = findNode(child)) {
                return found;
            }
        }
        
        return nullptr;
    };
    
    return findNode(root);
}

} // namespace chtl