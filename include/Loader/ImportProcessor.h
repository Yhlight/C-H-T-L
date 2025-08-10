#ifndef CHTL_IMPORT_PROCESSOR_H
#define CHTL_IMPORT_PROCESSOR_H

#include <memory>
#include <string>
#include <vector>
#include "Node/Node.h"
#include "Node/Import.h"
#include "Node/Origin.h"
#include "Context/BasicContext.h"
#include "Loader/ImportResolver.h"

namespace chtl {

// 导入处理结果
struct ImportProcessResult {
    bool success = false;
    std::vector<std::shared_ptr<Node>> generatedNodes; // 生成的节点（Origin、link、script等）
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

// 导入处理器 - 处理导入语句并生成相应的节点
class ImportProcessor {
public:
    ImportProcessor(std::shared_ptr<BasicContext> context);
    ~ImportProcessor() = default;
    
    // 处理导入节点
    ImportProcessResult processImport(std::shared_ptr<Import> importNode, 
                                     const std::string& currentFilePath);
    
    // 设置导入解析器
    void setResolver(std::shared_ptr<ImportResolver> resolver) { resolver_ = resolver; }
    
private:
    // 处理HTML导入
    ImportProcessResult processHtmlImport(std::shared_ptr<Import> importNode,
                                         const std::string& resolvedPath);
    
    // 处理CSS导入
    ImportProcessResult processCssImport(std::shared_ptr<Import> importNode,
                                        const std::string& resolvedPath);
    
    // 处理JS导入
    ImportProcessResult processJsImport(std::shared_ptr<Import> importNode,
                                       const std::string& resolvedPath);
    
    // 处理CHTL导入
    ImportProcessResult processChtlImport(std::shared_ptr<Import> importNode,
                                         const std::string& resolvedPath);
    
    // 创建Origin节点
    std::shared_ptr<Origin> createOriginNode(Origin::OriginType type,
                                            const std::string& content,
                                            const std::string& name = "");
    
    // 读取文件内容
    std::string readFileContent(const std::string& path);
    
    // 验证导入类型和as的组合
    bool validateImportCombination(std::shared_ptr<Import> importNode);
    
    // 在AST中查找指定名称和类型的节点
    std::shared_ptr<Node> findNodeByNameAndType(std::shared_ptr<Node> root, 
                                                const std::string& name, 
                                                Import::ImportType type);
    
private:
    std::shared_ptr<BasicContext> context_;
    std::shared_ptr<ImportResolver> resolver_;
};

} // namespace chtl

#endif // CHTL_IMPORT_PROCESSOR_H