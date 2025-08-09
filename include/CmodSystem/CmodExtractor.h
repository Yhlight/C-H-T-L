#ifndef CHTL_CMOD_EXTRACTOR_H
#define CHTL_CMOD_EXTRACTOR_H

#include "CmodSystem/CmodInfo.h"
#include <string>
#include <memory>
#include <vector>

namespace chtl {

// 前向声明
class BasicParser;
class BasicLexer;
class BasicContext;
class Node;
class Config;

// CMOD信息提取器 - 从CMOD模块中提取信息
class CmodExtractor {
public:
    // 导出信息结构
    struct ExportInfo {
        std::vector<std::string> styles;
        std::vector<std::string> elements;
        std::vector<std::string> vars;
    };
    
    CmodExtractor();
    ~CmodExtractor();
    
    // 从目录结构提取CMOD信息
    std::unique_ptr<CmodInfo> extractFromDirectory(const std::string& modulePath);
    
    // 从info文件提取模块信息
    std::unique_ptr<CmodInfo> extractFromInfoFile(const std::string& infoFilePath);
    
    // 从config节点提取信息
    std::unique_ptr<CmodInfo> extractFromConfig(std::shared_ptr<Config> configNode);
    
    // 提取导出信息
    ExportInfo extractExports(const std::string& modulePath);
    
    // 扫描导出的符号
    void scanExports(std::shared_ptr<Node> node,
                    std::vector<std::string>& styles,
                    std::vector<std::string>& elements,
                    std::vector<std::string>& vars);
    
    // 提取目录结构
    std::unique_ptr<CmodStructure> extractStructure(const std::string& modulePath);
    
    // 提取子模块
    std::vector<CmodStructure> extractSubmodules(const std::string& srcPath);
    
private:
    // 解析info文件
    std::shared_ptr<Node> parseInfoFile(const std::string& filePath);
    
    // 扫描源文件
    std::shared_ptr<Node> scanSourceFile(const std::string& filePath);
    
    // 扫描目录
    void scanDirectory(const std::string& dirPath,
                      std::vector<std::string>& styles,
                      std::vector<std::string>& elements,
                      std::vector<std::string>& vars);
    
    // 从节点提取定义
    void extractDefinitions(std::shared_ptr<Node> node,
                          std::vector<std::string>& styles,
                          std::vector<std::string>& elements,
                          std::vector<std::string>& vars);
    
    // 工具方法
    std::string getModuleNameFromPath(const std::string& path);
    bool isValidChtlFile(const std::string& filePath);
    
    // 解析器组件
    std::unique_ptr<BasicParser> parser_;
    std::unique_ptr<BasicLexer> lexer_;
    std::unique_ptr<BasicContext> context_;
};

} // namespace chtl

#endif // CHTL_CMOD_EXTRACTOR_H