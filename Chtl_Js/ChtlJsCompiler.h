#ifndef CHTL_JS_COMPILER_H
#define CHTL_JS_COMPILER_H

#include <string>
#include <memory>
#include <vector>

namespace chtl {
namespace chtl_js {

// 前向声明
class ChtlJsLexer;
class ChtlJsParser;
class ChtlJsState;
class ChtlJsContext;
class ChtlJsTransformer;
class ChtlJsGenerator;
class ChtlJsOptimizer;

/**
 * CHTL-JS编译器
 * 负责处理CHTL扩展的JavaScript语法
 * 作为CHTL编译器的内置模块
 */
class ChtlJsCompiler {
public:
    // 编译选项
    struct CompileOptions {
        bool enableOptimization = true;      // 启用优化
        bool injectRuntime = true;           // 注入运行时
        bool preserveComments = false;       // 保留注释
        bool minifyOutput = false;           // 压缩输出
        bool generateSourceMap = false;      // 生成source map
        bool strictMode = true;              // 严格模式
        bool cacheSelectors = true;          // 缓存选择器
        bool debugMode = false;              // 调试模式
        std::string runtimePath = "";        // 自定义运行时路径
    };
    
    // 编译结果
    struct CompileResult {
        std::string code;                    // 生成的JavaScript代码
        std::string sourceMap;               // source map（如果生成）
        std::vector<std::string> errors;     // 错误列表
        std::vector<std::string> warnings;   // 警告列表
        bool success;                        // 是否成功
        
        // 统计信息
        struct Statistics {
            int linesProcessed;
            int selectorsFound;
            int methodsTransformed;
            int animationsProcessed;
            int runtimeFunctionsUsed;
            double compilationTime;          // 毫秒
        } stats;
    };
    
private:
    // 编译器组件
    std::unique_ptr<ChtlJsLexer> lexer_;
    std::unique_ptr<ChtlJsParser> parser_;
    std::unique_ptr<ChtlJsState> state_;
    std::unique_ptr<ChtlJsContext> context_;
    std::unique_ptr<ChtlJsTransformer> transformer_;
    std::unique_ptr<ChtlJsGenerator> generator_;
    std::unique_ptr<ChtlJsOptimizer> optimizer_;
    
    // 编译选项
    CompileOptions options_;
    
    // 当前编译状态
    std::string currentFile_;
    CompileResult currentResult_;
    
public:
    ChtlJsCompiler();
    ~ChtlJsCompiler();
    
    /**
     * 编译CHTL-JS代码
     * @param code CHTL-JS源代码
     * @param filename 文件名（用于错误报告）
     * @param options 编译选项
     * @return 编译结果
     */
    CompileResult compile(const std::string& code, 
                         const std::string& filename = "<inline>",
                         const CompileOptions& options = CompileOptions());
    
    /**
     * 编译文件
     * @param filepath 文件路径
     * @param options 编译选项
     * @return 编译结果
     */
    CompileResult compileFile(const std::string& filepath,
                            const CompileOptions& options = CompileOptions());
    
    /**
     * 检查代码是否包含CHTL-JS语法
     * @param code JavaScript代码
     * @return 是否包含CHTL-JS语法
     */
    bool containsChtlJsSyntax(const std::string& code);
    
    /**
     * 获取CHTL运行时代码
     * @param minified 是否压缩
     * @return 运行时JavaScript代码
     */
    static std::string getChtlRuntime(bool minified = false);
    
    /**
     * 设置编译选项
     */
    void setOptions(const CompileOptions& options) { options_ = options; }
    const CompileOptions& getOptions() const { return options_; }
    
    /**
     * 获取最后的编译结果
     */
    const CompileResult& getLastResult() const { return currentResult_; }
    
private:
    // 编译流程
    void initializeComponents();
    void resetState();
    CompileResult doCompile(const std::string& code, const std::string& filename);
    
    // 编译阶段
    bool lexicalAnalysis(const std::string& code);
    bool syntaxAnalysis();
    bool semanticAnalysis();
    bool transformation();
    bool codeGeneration();
    bool optimization();
    
    // 错误处理
    void reportError(const std::string& error, int line = -1, int column = -1);
    void reportWarning(const std::string& warning, int line = -1, int column = -1);
    
    // 运行时注入
    std::string injectRuntime(const std::string& code);
    std::string generateRuntimeCode();
};

} // namespace chtl_js
} // namespace chtl

#endif // CHTL_JS_COMPILER_H