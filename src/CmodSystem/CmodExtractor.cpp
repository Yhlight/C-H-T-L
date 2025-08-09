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

namespace chtl {

namespace fs = std::filesystem;

CmodExtractor::CmodExtractor() {
    // 初始化解析器组件
    context_ = std::make_unique<StandardContext>();
    lexer_ = std::make_unique<StandardLexer>(context_.get());
    parser_ = std::make_unique<StandardParser>(
        std::shared_ptr<BasicLexer>(lexer_.get(), [](BasicLexer*){}),
        std::shared_ptr<BasicContext>(context_.get(), [](BasicContext*){})
    );
}

CmodExtractor::~CmodExtractor() = default;

// 从目录结构提取CMOD信息
std::unique_ptr<CmodInfo> CmodExtractor::extractFromDirectory(const std::string& modulePath) {
    auto info = std::make_unique<CmodInfo>();
    
    // 设置基本路径信息
    info->modulePath = modulePath;
    info->name = getModuleNameFromPath(modulePath);
    
    // 提取目录结构
    auto structure = extractStructure(modulePath);
    if (!structure || !structure->isValid()) {
        return nullptr;
    }
    
    // 从info文件提取详细信息
    auto infoFromFile = extractFromInfoFile(structure->infoFile);
    if (infoFromFile) {
        *info = *infoFromFile;
        info->modulePath = modulePath; // 保留路径信息
    }
    
    // 扫描源代码提取导出信息
    scanExports(*info, structure->srcPath);
    
    // 提取子模块信息
    for (const auto& subStruct : structure->submodules) {
        info->submodules.push_back(subStruct.getModuleName());
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
    
    // 提取配置项
    // TODO: Config节点需要提供getItems()方法或类似的接口
    // 暂时使用getAttribute方法
    info->name = configNode->getAttribute("name");
    info->version = configNode->getAttribute("version");
    info->description = configNode->getAttribute("description");
    info->author = configNode->getAttribute("author");
    info->license = configNode->getAttribute("license");
    info->dependencies = configNode->getAttribute("dependencies");
    info->category = configNode->getAttribute("category");
    info->minCHTLVersion = configNode->getAttribute("minCHTLVersion");
    info->maxCHTLVersion = configNode->getAttribute("maxCHTLVersion");
    
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

// 扫描源代码提取导出信息
void CmodExtractor::scanExports(CmodInfo& info, const std::string& srcPath) {
    std::vector<std::string> styles, elements, vars;
    scanDirectory(srcPath, styles, elements, vars);
    
    // 合并到info中
    info.exportedStyles.insert(info.exportedStyles.end(), styles.begin(), styles.end());
    info.exportedElements.insert(info.exportedElements.end(), elements.begin(), elements.end());
    info.exportedVars.insert(info.exportedVars.end(), vars.begin(), vars.end());
    
    // 去重
    auto removeDuplicates = [](std::vector<std::string>& vec) {
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    };
    
    removeDuplicates(info.exportedStyles);
    removeDuplicates(info.exportedElements);
    removeDuplicates(info.exportedVars);
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

// 提取子模块信息
std::vector<std::unique_ptr<CmodInfo>> CmodExtractor::extractSubmodules(const std::string& modulePath) {
    std::vector<std::unique_ptr<CmodInfo>> submodules;
    
    std::string srcPath = modulePath + "/src";
    if (!fs::exists(srcPath)) {
        return submodules;
    }
    
    for (const auto& entry : fs::directory_iterator(srcPath)) {
        if (entry.is_directory()) {
            auto subInfo = extractFromDirectory(entry.path().string());
            if (subInfo) {
                submodules.push_back(std::move(subInfo));
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
    
    // 读取文件内容
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return nullptr;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    
    // 重新创建lexer和parser
    context_ = std::make_unique<StandardContext>();
    lexer_ = std::make_unique<StandardLexer>(context_.get());
    parser_ = std::make_unique<StandardParser>(
        std::shared_ptr<BasicLexer>(lexer_.get(), [](BasicLexer*){}),
        std::shared_ptr<BasicContext>(context_.get(), [](BasicContext*){})
    );
    
    // 设置输入并解析
    // TODO: 需要为lexer提供setInput方法
    // 暂时返回nullptr
    return nullptr;
}

// 扫描源文件
void CmodExtractor::scanSourceFile(const std::string& filePath,
                                 std::vector<std::string>& styles,
                                 std::vector<std::string>& elements,
                                 std::vector<std::string>& vars) {
    if (!isValidChtlFile(filePath)) {
        return;
    }
    
    auto rootNode = parseInfoFile(filePath);
    if (!rootNode) {
        return;
    }
    
    extractDefinitions(rootNode, styles, elements, vars);
}

// 递归扫描目录
void CmodExtractor::scanDirectory(const std::string& dirPath,
                                std::vector<std::string>& styles,
                                std::vector<std::string>& elements,
                                std::vector<std::string>& vars) {
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        return;
    }
    
    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (entry.is_regular_file() && isValidChtlFile(entry.path().string())) {
            scanSourceFile(entry.path().string(), styles, elements, vars);
        }
    }
}

// 从节点提取定义
void CmodExtractor::extractDefinitions(std::shared_ptr<Node> node,
                                     std::vector<std::string>& styles,
                                     std::vector<std::string>& elements,
                                     std::vector<std::string>& vars) {
    if (!node) {
        return;
    }
    
    // 根据节点类型提取定义
    switch (node->getType()) {
        case NodeType::TEMPLATE: {
            auto templateNode = std::dynamic_pointer_cast<Template>(node);
            if (templateNode) {
                std::string name = templateNode->getAttribute("name");
                std::string typeStr = templateNode->getAttribute("type");
                
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
                std::string name = customNode->getAttribute("name");
                std::string typeStr = customNode->getAttribute("type");
                
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