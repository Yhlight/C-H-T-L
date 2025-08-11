#ifndef CHTL_BASIC_GENERATOR_H
#define CHTL_BASIC_GENERATOR_H

#include <memory>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <stack>
#include "Node/Node.h"
#include "Context/BasicContext.h"

namespace chtl {

// 生成器基类
class BasicGenerator {
public:
    // 生成器配置
    struct GeneratorConfig {
        bool prettyPrint = true;         // 是否格式化输出
        int indentSize = 2;              // 缩进空格数
        bool useSpaces = true;           // 使用空格还是Tab
        std::string lineEnding = "\n";   // 行结束符
        bool insertComments = true;      // 是否插入生成的注释
        bool minify = false;             // 是否压缩输出
        std::string encoding = "UTF-8";  // 输出编码
    };
    
    // 生成器状态
    enum class GeneratorState {
        INITIAL,
        GENERATING,
        SUCCESS,
        ERROR
    };
    
protected:
    std::shared_ptr<BasicContext> context_;   // 上下文
    std::shared_ptr<Node> rootNode_;         // 根节点
    GeneratorConfig config_;                  // 配置
    GeneratorState state_;                    // 状态
    std::ostream* output_;                    // 输出流
    std::unique_ptr<std::ofstream> fileStream_; // 文件流（如果输出到文件）
    
    // 缩进管理
    int currentIndentLevel_ = 0;
    std::string currentIndent_;
    
    // 错误和警告
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
    
    // 生成统计
    size_t linesGenerated_ = 0;
    size_t bytesGenerated_ = 0;
    
public:
    BasicGenerator();
    virtual ~BasicGenerator();
    
    // 初始化
    virtual bool initialize(std::shared_ptr<BasicContext> context);
    
    // 生成方法
    virtual bool generate(std::shared_ptr<Node> node) = 0;
    virtual bool generateToFile(std::shared_ptr<Node> node, const std::string& filename);
    virtual bool generateToStream(std::shared_ptr<Node> node, std::ostream& stream);
    virtual bool generateToString(std::shared_ptr<Node> node, std::string& result);
    
    // 配置管理
    void setConfig(const GeneratorConfig& config) { config_ = config; updateIndent(); }
    const GeneratorConfig& getConfig() const { return config_; }
    void setPrettyPrint(bool pretty) { config_.prettyPrint = pretty; }
    void setIndentSize(int size) { config_.indentSize = size; updateIndent(); }
    void setMinify(bool minify) { config_.minify = minify; }
    
    // 状态查询
    GeneratorState getState() const { return state_; }
    bool hasErrors() const { return !errors_.empty(); }
    bool hasWarnings() const { return !warnings_.empty(); }
    const std::vector<std::string>& getErrors() const { return errors_; }
    const std::vector<std::string>& getWarnings() const { return warnings_; }
    
    // 统计信息
    size_t getLinesGenerated() const { return linesGenerated_; }
    size_t getBytesGenerated() const { return bytesGenerated_; }
    
protected:
    // 输出方法
    void write(const std::string& text);
    void writeLine(const std::string& text = "");
    void writeIndent();
    void increaseIndent();
    void decreaseIndent();
    void updateIndent();
    
    // 错误处理
    void reportError(const std::string& message);
    void reportWarning(const std::string& message);
    void clearErrors() { errors_.clear(); }
    void clearWarnings() { warnings_.clear(); }
    
    // 节点访问方法（子类需要实现）
    virtual void generateNode(std::shared_ptr<Node> node);
    virtual void generateElement(std::shared_ptr<Node> node) = 0;
    virtual void generateText(std::shared_ptr<Node> node) = 0;
    virtual void generateComment(std::shared_ptr<Node> node) = 0;
    
    // CHTL特有节点（子类可选实现）
    virtual void generateTemplate(std::shared_ptr<Node> node) { (void)node; }
    virtual void generateCustom(std::shared_ptr<Node> node) { (void)node; }
    virtual void generateStyle(std::shared_ptr<Node> node) { (void)node; }
    virtual void generateConfig(std::shared_ptr<Node> node) { (void)node; }
    virtual void generateImport(std::shared_ptr<Node> node) { (void)node; }
    virtual void generateNamespace(std::shared_ptr<Node> node) { (void)node; }
    virtual void generateOperate(std::shared_ptr<Node> node) { (void)node; }
    virtual void generateOrigin(std::shared_ptr<Node> node) { (void)node; }
    
    // 工具方法
    std::string escapeHtml(const std::string& text);
    std::string escapeAttribute(const std::string& text);
    std::string escapeJavaScript(const std::string& text);
    std::string escapeCss(const std::string& text);
    
    // 初始化和清理
    virtual void beginGeneration();
    virtual void endGeneration();
};

} // namespace chtl

#endif // CHTL_BASIC_GENERATOR_H