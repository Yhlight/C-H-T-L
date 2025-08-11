#ifndef CHTL_CJMOD_INTEGRATION_H
#define CHTL_CJMOD_INTEGRATION_H

#include <memory>
#include <string>
#include <vector>
#include "Node/Node.h"
#include "CJmodManager.h"

namespace chtl {

// CJmod 编译管道集成
class CJmodPipeline {
public:
    CJmodPipeline();
    ~CJmodPipeline();
    
    // 编译阶段钩子
    struct CompileHooks {
        // 预处理阶段（在词法分析前）
        std::function<std::string(const std::string& source)> preprocess;
        
        // 词法分析阶段（可以注入新的 token 类型）
        std::function<void(class StandardLexer*)> onLexerInit;
        
        // 语法分析阶段（可以扩展语法规则）
        std::function<void(class StandardParser*)> onParserInit;
        
        // AST 转换阶段（可以修改 AST）
        std::function<void(std::shared_ptr<Node>)> transformAST;
        
        // 代码生成阶段（可以注入代码）
        std::function<void(class WebGenerator*)> onGenerate;
        
        // 后处理阶段（在生成最终代码后）
        std::function<std::string(const std::string& code)> postprocess;
    };
    
    // 注册钩子
    void registerHooks(const std::string& moduleName, const CompileHooks& hooks);
    
    // 执行管道
    void executePreprocess(std::string& source);
    void executeLexerInit(StandardLexer* lexer);
    void executeParserInit(StandardParser* parser);
    void executeASTTransform(std::shared_ptr<Node> ast);
    void executeGenerate(WebGenerator* generator);
    void executePostprocess(std::string& code);
    
private:
    std::map<std::string, CompileHooks> moduleHooks_;
};

// CJmod 导入处理器
class CJmodImportProcessor {
public:
    struct ImportInfo {
        std::string type;        // "@CJmod"
        std::string moduleName;  // "animate"
        std::string source;      // "from \"@cjmod/animate\""
        std::string alias;       // "as anim"
        std::string version;     // "@1.0.0"
    };
    
    // 解析导入语句
    static std::vector<ImportInfo> parseImports(const std::shared_ptr<Node>& ast);
    
    // 处理导入
    static void processImports(const std::vector<ImportInfo>& imports);
    
    // 验证导入
    static bool validateImport(const ImportInfo& import);
    
    // 解析导入路径
    static std::string resolveModulePath(const std::string& source);
};

// CJmod 运行时生成器
class CJmodRuntimeGenerator {
public:
    // 生成模块加载器代码
    static std::string generateModuleLoader();
    
    // 生成方法注入代码
    static std::string generateMethodInjection(const std::string& selector, 
                                               const std::string& methodName,
                                               const std::string& implementation);
    
    // 生成操作符重载代码
    static std::string generateOperatorOverload(const std::string& operator_,
                                                const std::string& implementation);
    
    // 生成初始化代码
    static std::string generateInitCode(const std::vector<std::string>& modules);
    
    // 生成 polyfill
    static std::string generatePolyfills();
    
private:
    static std::string wrapInIIFE(const std::string& code);
    static std::string generateModuleNamespace(const std::string& moduleName);
};

// CJmod 上下文管理器
class CJmodContext {
public:
    static CJmodContext& getInstance();
    
    // 设置当前编译上下文
    void setCurrentFile(const std::string& filename);
    void setCurrentModule(const std::string& moduleName);
    
    // 查询上下文
    std::string getCurrentFile() const { return currentFile_; }
    std::string getCurrentModule() const { return currentModule_; }
    
    // 作用域管理
    void pushScope(const std::string& scopeName);
    void popScope();
    std::string getCurrentScope() const;
    
    // 符号表
    void registerSymbol(const std::string& name, const std::string& type);
    bool hasSymbol(const std::string& name) const;
    std::string getSymbolType(const std::string& name) const;
    
private:
    CJmodContext() = default;
    
    std::string currentFile_;
    std::string currentModule_;
    std::vector<std::string> scopeStack_;
    std::map<std::string, std::string> symbolTable_;
};

} // namespace chtl

#endif // CHTL_CJMOD_INTEGRATION_H