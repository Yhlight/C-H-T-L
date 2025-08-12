#ifndef CHTL_PARSER_STANDARDPARSER_H
#define CHTL_PARSER_STANDARDPARSER_H

#include <string>
#include <memory>
#include <vector>
#include "Node/Node.h"
#include "State/SymbolTable.h"
#include "Scanner/BridgeScanner/BridgeScanner.h"

namespace CHTL {

/**
 * 标准解析器 - 整合了ANTLR4和所有语言解析器的主解析器
 * 负责协调扫描器、各语言解析器和符号表的工作
 */
class StandardParser {
public:
    StandardParser();
    ~StandardParser();
    
    /**
     * 解析CHTL代码
     * @param content CHTL源代码
     * @return AST根节点，失败返回nullptr
     */
    NodePtr parse(const std::string& content);
    
    /**
     * 解析CHTL文件
     * @param filename 文件路径
     * @return AST根节点，失败返回nullptr
     */
    NodePtr parseFile(const std::string& filename);
    
    /**
     * 获取符号表
     */
    SymbolTable* getSymbolTable() { return symbolTable_.get(); }
    
    /**
     * 获取错误信息
     */
    const std::vector<std::string>& getErrors() const { return errors_; }
    
    /**
     * 获取警告信息
     */
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    
    /**
     * 设置调试模式
     */
    void setDebugMode(bool debug) { debugMode_ = debug; }
    
    /**
     * 设置配置选项
     */
    void setOption(const std::string& key, const std::string& value);
    
private:
    /**
     * 解析CHTL段
     */
    NodePtr parseCHTLSegment(const Segment& segment);
    
    /**
     * 解析CSS段
     */
    NodePtr parseCSSSegment(const Segment& segment);
    
    /**
     * 解析JavaScript段
     */
    NodePtr parseJavaScriptSegment(const Segment& segment);
    
    /**
     * 解析CHTL JavaScript段
     */
    NodePtr parseCHTLJavaScriptSegment(const Segment& segment);
    
    /**
     * 合并AST节点
     */
    void mergeAST(NodePtr root, NodePtr node, const Segment& segment);
    
    /**
     * 后处理AST
     */
    void postProcessAST(NodePtr root);
    
    /**
     * 验证AST
     */
    bool validateAST(NodePtr root);
    
    /**
     * 添加错误
     */
    void addError(const std::string& error, int line = 0, int column = 0);
    
    /**
     * 添加警告
     */
    void addWarning(const std::string& warning, int line = 0, int column = 0);
    
private:
    // 符号表
    std::unique_ptr<SymbolTable> symbolTable_;
    
    // 扫描器
    std::unique_ptr<BridgeScanner> scanner_;
    
    // 错误和警告
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    // 配置选项
    std::unordered_map<std::string, std::string> options_;
    
    // 调试模式
    bool debugMode_;
    
    // 当前解析的文件名
    std::string currentFile_;
};

} // namespace CHTL

#endif // CHTL_PARSER_STANDARDPARSER_H