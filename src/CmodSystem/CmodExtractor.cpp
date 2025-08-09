#include "CmodSystem/CmodExtractor.h"
#include "Parser/StandardParser.h"
#include "Lexer/StandardLexer.h"
#include "Context/StandardContext.h"
#include "Node/Node.h"
#include "Node/Config.h"
#include "Node/Template.h"
#include "Node/Custom.h"
#include "Node/Import.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <variant>

namespace chtl {

namespace fs = std::filesystem;

CmodExtractor::CmodExtractor() {
    // 初始化解析器组件
    context_ = std::make_unique<StandardContext>();
    lexer_ = std::make_unique<StandardLexer>();
    parser_ = std::make_unique<StandardParser>(
        std::shared_ptr<BasicLexer>(lexer_.get(), [](BasicLexer*){}),
        std::shared_ptr<BasicContext>(context_.get(), [](BasicContext*){})
    );
}

CmodExtractor::~CmodExtractor() = default;

// 从目录提取模块信息  
std::unique_ptr<CmodInfo> CmodExtractor::extractFromDirectory(const std::string& modulePath) {
    auto info = std::make_unique<CmodInfo>();
    
    // 提取基本信息
    info->name = fs::path(modulePath).filename().string();
    
    // 扫描info目录
    std::string infoPath = modulePath + "/info";
    if (fs::exists(infoPath)) {
        // 查找info文件
        for (const auto& entry : fs::directory_iterator(infoPath)) {
            if (entry.is_regular_file() && isValidChtlFile(entry.path().string())) {
                auto parsedInfo = extractFromInfoFile(entry.path().string());
                if (parsedInfo) {
                    // 合并信息
                    *info = *parsedInfo;
                    break;
                }
            }
        }
    }
    
    // 扫描src目录提取导出信息
    auto structure = extractStructure(modulePath);
    if (structure) {
        // 扫描并提取导出的元素、样式、变量
        scanDirectory(structure->srcPath, info->exportedStyles, 
                     info->exportedElements, info->exportedVars);
    }
    
    return info;
}

// 从info文件提取模块信息
std::unique_ptr<CmodInfo> CmodExtractor::extractFromInfoFile(const std::string& infoFilePath) {
    auto rootNode = parseInfoFile(infoFilePath);
    if (!rootNode) {
        return nullptr;
    }
    
    auto info = std::make_unique<CmodInfo>();
    info->infoFilePath = infoFilePath;
    
    // 查找[Info]和[Export]块
    for (const auto& child : rootNode->getChildren()) {
        if (child->getType() == NodeType::INFO) {
            // 提取Info块的配置信息
            auto configNode = std::dynamic_pointer_cast<Config>(child);
            if (configNode) {
                info = extractFromConfig(configNode);
                info->infoFilePath = infoFilePath;
            }
        } else if (child->getType() == NodeType::EXPORT) {
            // 提取Export块的导出信息
            extractExports(*info, child);
        }
    }
    
    return info;
}

// 从已解析的配置节点提取信息
std::unique_ptr<CmodInfo> CmodExtractor::extractFromConfig(std::shared_ptr<Config> configNode) {
    auto info = std::make_unique<CmodInfo>();
    
    if (!configNode) {
        return info;
    }
    
    // Extract config items using getAttribute with proper variant handling
    auto nameAttr = configNode->getAttribute("name");
    if (std::holds_alternative<std::string>(nameAttr)) {
        info->name = std::get<std::string>(nameAttr);
    }
    
    auto versionAttr = configNode->getAttribute("version");
    if (std::holds_alternative<std::string>(versionAttr)) {
        info->version = std::get<std::string>(versionAttr);
    }
    
    auto descAttr = configNode->getAttribute("description");
    if (std::holds_alternative<std::string>(descAttr)) {
        info->description = std::get<std::string>(descAttr);
    }
    
    auto authorAttr = configNode->getAttribute("author");
    if (std::holds_alternative<std::string>(authorAttr)) {
        info->author = std::get<std::string>(authorAttr);
    }
    
    auto licenseAttr = configNode->getAttribute("license");
    if (std::holds_alternative<std::string>(licenseAttr)) {
        info->license = std::get<std::string>(licenseAttr);
    }
    
    auto depsAttr = configNode->getAttribute("dependencies");
    if (std::holds_alternative<std::string>(depsAttr)) {
        info->dependencies = std::get<std::string>(depsAttr);
    }
    
    auto categoryAttr = configNode->getAttribute("category");
    if (std::holds_alternative<std::string>(categoryAttr)) {
        info->category = std::get<std::string>(categoryAttr);
    }
    
    auto minVersionAttr = configNode->getAttribute("minCHTLVersion");
    if (std::holds_alternative<std::string>(minVersionAttr)) {
        info->minCHTLVersion = std::get<std::string>(minVersionAttr);
    }
    
    auto maxVersionAttr = configNode->getAttribute("maxCHTLVersion");
    if (std::holds_alternative<std::string>(maxVersionAttr)) {
        info->maxCHTLVersion = std::get<std::string>(maxVersionAttr);
    }
    
    return info;
}

// 提取导出信息
void CmodExtractor::extractExports(CmodInfo& info, std::shared_ptr<Node> exportNode) {
    if (!exportNode || exportNode->getType() != NodeType::EXPORT) {
        return;
    }
    
    // 遍历Export节点的子节点
    for (const auto& child : exportNode->getChildren()) {
        if (child->getType() == NodeType::REFERENCE) {
            // 提取引用信息
            std::string refType = child->getAttribute("type");
            std::string refName = child->getAttribute("name");
            
            if (refType == "Style") {
                info.exportedStyles.push_back(refName);
            } else if (refType == "Element") {
                info.exportedElements.push_back(refName);
            } else if (refType == "Var") {
                info.exportedVars.push_back(refName);
            }
        }
    }
}

// 扫描导出信息  
void CmodExtractor::scanExports(std::shared_ptr<Node> node,
                              std::vector<std::string>& styles,
                              std::vector<std::string>& elements,
                              std::vector<std::string>& vars) {
    if (!node) {
        return;
    }
    
    if (node->getType() == NodeType::EXPORT) {
        // 提取导出的符号
        for (const auto& child : node->getChildren()) {
            if (child->getType() == NodeType::ELEMENT) {
                auto nameAttr = child->getAttribute("name");
                if (std::holds_alternative<std::string>(nameAttr)) {
                    std::string name = std::get<std::string>(nameAttr);
                    if (name.find("@Style") == 0) {
                        styles.push_back(name.substr(6)); // 去除@Style前缀
                    } else if (name.find("@Element") == 0) {
                        elements.push_back(name.substr(8)); // 去除@Element前缀
                    } else if (name.find("@Var") == 0) {
                        vars.push_back(name.substr(4)); // 去除@Var前缀
                    }
                }
            }
        }
    }
    
    // 递归处理子节点
    for (const auto& child : node->getChildren()) {
        scanExports(child, styles, elements, vars);
    }
}

// 提取目录结构
std::unique_ptr<CmodStructure> CmodExtractor::extractStructure(const std::string& modulePath) {
    auto structure = std::make_unique<CmodStructure>();
    
    structure->rootPath = modulePath;
    structure->srcPath = modulePath + "/src";
    structure->infoPath = modulePath + "/info";
    
    // 获取模块名
    std::string moduleName = getModuleNameFromPath(modulePath);
    
    // 设置文件路径
    structure->mainModuleFile = structure->srcPath + "/" + moduleName + ".chtl";
    structure->infoFile = structure->infoPath + "/" + moduleName + ".chtl";
    
    // 检查子模块
    if (fs::exists(structure->srcPath)) {
        for (const auto& entry : fs::directory_iterator(structure->srcPath)) {
            if (entry.is_directory()) {
                // 递归提取子模块结构
                auto subStructure = extractStructure(entry.path().string());
                if (subStructure) {
                    structure->submodules.push_back(*subStructure);
                }
            }
        }
    }
    
    return structure;
}

// 提取子模块
std::vector<CmodStructure> CmodExtractor::extractSubmodules(const std::string& srcPath) {
    std::vector<CmodStructure> submodules;
    
    if (!fs::exists(srcPath) || !fs::is_directory(srcPath)) {
        return submodules;
    }
    
    // 扫描src目录下的子目录
    for (const auto& entry : fs::directory_iterator(srcPath)) {
        if (entry.is_directory()) {
            std::string subPath = entry.path().string();
            
            // 检查是否为有效的子模块
            if (fs::exists(subPath + "/src") && fs::exists(subPath + "/info")) {
                auto subStructure = extractStructure(subPath);
                if (subStructure && subStructure->isValid()) {
                    submodules.push_back(*subStructure);
                }
            }
        }
    }
    
    return submodules;
}

// 解析info文件
std::shared_ptr<Node> CmodExtractor::parseInfoFile(const std::string& filePath) {
    if (!fs::exists(filePath)) {
        return nullptr;
    }
    
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return nullptr;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    // 重新创建lexer和parser以重置状态
    context_ = std::make_unique<StandardContext>();
    lexer_ = std::make_unique<StandardLexer>();
    parser_ = std::make_unique<StandardParser>(
        std::shared_ptr<BasicLexer>(lexer_.get(), [](BasicLexer*){}),
        std::shared_ptr<BasicContext>(context_.get(), [](BasicContext*){})
    );
    
    // TODO: 需要为lexer提供setInput方法
    // 目前返回nullptr，因为没有lexer输入解析将无法工作
    return nullptr;
}

// 扫描源文件
std::shared_ptr<Node> CmodExtractor::scanSourceFile(const std::string& filePath) {
    if (!isValidChtlFile(filePath)) {
        return nullptr;
    }
    
    auto rootNode = parseInfoFile(filePath);
    if (!rootNode) {
        return nullptr;
    }
    
    return rootNode;
}

// 扫描目录
void CmodExtractor::scanDirectory(const std::string& dirPath,
                                std::vector<std::string>& styles,
                                std::vector<std::string>& elements,
                                std::vector<std::string>& vars) {
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        return;
    }
    
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (entry.is_regular_file() && isValidChtlFile(entry.path().string())) {
            auto node = scanSourceFile(entry.path().string());
            if (node) {
                scanExports(node, styles, elements, vars);
                extractDefinitions(node, styles, elements, vars);
            }
        }
    }
    
    // 去除重复项
    auto removeDuplicates = [](std::vector<std::string>& vec) {
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    };
    
    removeDuplicates(styles);
    removeDuplicates(elements);
    removeDuplicates(vars);
}

// 从节点提取定义
void CmodExtractor::extractDefinitions(std::shared_ptr<Node> node,
                                     std::vector<std::string>& styles,
                                     std::vector<std::string>& elements,
                                     std::vector<std::string>& vars) {
    if (!node) {
        return;
    }
    
    switch (node->getType()) {
        case NodeType::TEMPLATE: {
            auto templateNode = std::dynamic_pointer_cast<Template>(node);
            if (templateNode) {
                auto nameAttr = templateNode->getAttribute("name");
                auto typeAttr = templateNode->getAttribute("type");
                
                std::string name, typeStr;
                if (std::holds_alternative<std::string>(nameAttr)) {
                    name = std::get<std::string>(nameAttr);
                }
                if (std::holds_alternative<std::string>(typeAttr)) {
                    typeStr = std::get<std::string>(typeAttr);
                }
                
                if (typeStr == "Style") {
                    styles.push_back(name);
                } else if (typeStr == "Element") {
                    elements.push_back(name);
                } else if (typeStr == "Var") {
                    vars.push_back(name);
                }
            }
            break;
        }
        
        case NodeType::CUSTOM: {
            auto customNode = std::dynamic_pointer_cast<Custom>(node);
            if (customNode) {
                auto nameAttr = customNode->getAttribute("name");
                auto typeAttr = customNode->getAttribute("type");
                
                std::string name, typeStr;
                if (std::holds_alternative<std::string>(nameAttr)) {
                    name = std::get<std::string>(nameAttr);
                }
                if (std::holds_alternative<std::string>(typeAttr)) {
                    typeStr = std::get<std::string>(typeAttr);
                }
                
                if (typeStr == "Style") {
                    styles.push_back(name);
                } else if (typeStr == "Element") {
                    elements.push_back(name);
                } else if (typeStr == "Var") {
                    vars.push_back(name);
                }
            }
            break;
        }
        
        default:
            break;
    }
    
    // 递归处理子节点
    for (const auto& child : node->getChildren()) {
        extractDefinitions(child, styles, elements, vars);
    }
}

// 工具方法
std::string CmodExtractor::getModuleNameFromPath(const std::string& path) {
    fs::path fsPath(path);
    return fsPath.filename().string();
}

bool CmodExtractor::isValidChtlFile(const std::string& filePath) {
    fs::path path(filePath);
    return path.extension() == ".chtl";
}

} // namespace chtl