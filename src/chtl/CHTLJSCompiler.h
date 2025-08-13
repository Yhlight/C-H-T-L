#ifndef CHTL_JS_COMPILER_H
#define CHTL_JS_COMPILER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include "CHTLContext.h"
#include "../../generated/JavaScriptLexer.h"
#include "../../generated/JavaScriptParser.h"
#include "../../generated/JavaScriptBaseListener.h"

namespace chtl {

// JavaScript AST节点类型
enum class JSNodeType {
    Program,
    FunctionDeclaration,
    VariableDeclaration,
    ClassDeclaration,
    ImportDeclaration,
    ExportDeclaration,
    ExpressionStatement,
    BlockStatement,
    IfStatement,
    ForStatement,
    WhileStatement,
    ReturnStatement,
    // ... 更多类型
};

// JavaScript作用域类型
enum class JSScopeType {
    Global,
    Function,
    Block,
    Class,
    Module
};

// JavaScript符号信息
struct JSSymbol {
    std::string name;
    std::string type;  // variable, function, class, import
    bool isConst = false;
    bool isLet = false;
    bool isExported = false;
    bool isUsed = false;
    size_t line = 0;
    size_t column = 0;
};

// JavaScript作用域
class JSScope {
private:
    JSScopeType type;
    std::shared_ptr<JSScope> parent;
    std::unordered_map<std::string, JSSymbol> symbols;
    std::string name;
    
public:
    JSScope(JSScopeType t, std::shared_ptr<JSScope> p = nullptr, const std::string& n = "")
        : type(t), parent(p), name(n) {}
    
    // 符号管理
    bool addSymbol(const JSSymbol& symbol);
    JSSymbol* findSymbol(const std::string& name);
    JSSymbol* findSymbolInChain(const std::string& name);
    
    // 获取器
    JSScopeType getType() const { return type; }
    std::shared_ptr<JSScope> getParent() const { return parent; }
    const std::string& getName() const { return name; }
    const std::unordered_map<std::string, JSSymbol>& getSymbols() const { return symbols; }
};

// JavaScript编译器监听器
class JSCompilerListener : public JavaScriptBaseListener {
private:
    std::stringstream output;
    std::shared_ptr<CHTLContext> context;
    
    // 作用域管理
    std::shared_ptr<JSScope> globalScope;
    std::shared_ptr<JSScope> currentScope;
    std::vector<std::shared_ptr<JSScope>> scopeStack;
    
    // 编译选项
    bool minify = false;
    bool preserveComments = false;
    bool addSourceMap = false;
    
    // 缩进管理
    int indentLevel = 0;
    std::string indentString = "    ";
    
    // 导入/导出管理
    std::vector<std::string> imports;
    std::vector<std::string> exports;
    
    // 错误和警告
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
    
public:
    JSCompilerListener(std::shared_ptr<CHTLContext> ctx, bool minifyOutput = false);
    
    // 获取编译结果
    std::string getCompiledJS() const { return output.str(); }
    const std::vector<std::string>& getErrors() const { return errors; }
    const std::vector<std::string>& getWarnings() const { return warnings; }
    const std::vector<std::string>& getImports() const { return imports; }
    const std::vector<std::string>& getExports() const { return exports; }
    
    // JavaScript解析器监听器方法
    void enterProgram(JavaScriptParser::ProgramContext* ctx) override;
    void exitProgram(JavaScriptParser::ProgramContext* ctx) override;
    
    void enterFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext* ctx) override;
    void exitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext* ctx) override;
    
    void enterClassDeclaration(JavaScriptParser::ClassDeclarationContext* ctx) override;
    void exitClassDeclaration(JavaScriptParser::ClassDeclarationContext* ctx) override;
    
    void enterVariableDeclaration(JavaScriptParser::VariableDeclarationContext* ctx) override;
    void exitVariableDeclaration(JavaScriptParser::VariableDeclarationContext* ctx) override;
    
    void enterImportDeclaration(JavaScriptParser::ImportDeclarationContext* ctx) override;
    void enterExportDeclaration(JavaScriptParser::ExportDeclarationContext* ctx) override;
    
    void enterBlockStatement(JavaScriptParser::BlockStatementContext* ctx) override;
    void exitBlockStatement(JavaScriptParser::BlockStatementContext* ctx) override;
    
private:
    // 辅助方法
    std::string extractText(antlr4::ParserRuleContext* ctx);
    std::string indent() const;
    void increaseIndent() { if (!minify) indentLevel++; }
    void decreaseIndent() { if (!minify && indentLevel > 0) indentLevel--; }
    
    // 作用域管理
    void enterScope(JSScopeType type, const std::string& name = "");
    void exitScope();
    
    // 符号管理
    void registerSymbol(const std::string& name, const std::string& type, bool isConst = false, bool isLet = false);
    void markSymbolAsUsed(const std::string& name);
    
    // 错误报告
    void reportError(const std::string& message, size_t line, size_t column);
    void reportWarning(const std::string& message, size_t line, size_t column);
};

// JavaScript编译器
class JSCompiler {
private:
    std::shared_ptr<CHTLContext> context;
    
    // 编译选项
    struct Options {
        bool minify = false;
        bool preserveComments = true;
        bool addSourceMap = false;
        bool checkUnusedVariables = true;
        bool checkUndefinedVariables = true;
        bool modernizeCode = false;  // ES5 -> ES6+转换
        bool strictMode = false;
    } options;
    
public:
    JSCompiler(std::shared_ptr<CHTLContext> ctx);
    
    // 编译选项设置
    void setMinify(bool value) { options.minify = value; }
    void setPreserveComments(bool value) { options.preserveComments = value; }
    void setSourceMap(bool value) { options.addSourceMap = value; }
    void setStrictMode(bool value) { options.strictMode = value; }
    void setModernize(bool value) { options.modernizeCode = value; }
    Options& getOptions() { return options; }
    
    // 编译JavaScript
    std::string compile(const std::string& js);
    
    // 编译并返回详细信息
    struct CompileResult {
        std::string code;
        std::vector<std::string> errors;
        std::vector<std::string> warnings;
        std::vector<std::string> imports;
        std::vector<std::string> exports;
        std::unordered_map<std::string, JSSymbol> symbols;
    };
    
    CompileResult compileWithAnalysis(const std::string& js);
    
    // 验证JavaScript
    bool validate(const std::string& js, std::vector<std::string>& errors);
    
    // 语法检查
    bool checkSyntax(const std::string& js);
    
private:
    // 错误监听器
    class JSErrorListener : public antlr4::BaseErrorListener {
    private:
        std::vector<std::string>& errors;
        
    public:
        JSErrorListener(std::vector<std::string>& errs) : errors(errs) {}
        
        void syntaxError(antlr4::Recognizer* recognizer,
                        antlr4::Token* offendingSymbol,
                        size_t line,
                        size_t charPositionInLine,
                        const std::string& msg,
                        std::exception_ptr e) override;
    };
};

// JavaScript优化器
class JSOptimizer {
public:
    struct Options {
        bool removeDeadCode = true;
        bool inlineConstants = true;
        bool simplifyExpressions = true;
        bool mangleVariables = false;  // 变量名混淆
        bool removeConsoleLog = false;
        bool removeDebugger = false;
        bool optimizeLoops = true;
    };
    
private:
    Options options;
    
public:
    JSOptimizer(const Options& opts = Options()) : options(opts) {}
    
    // 优化JavaScript代码
    std::string optimize(const std::string& js);
    
    // 代码压缩
    std::string minify(const std::string& js);
    
    // 死代码删除
    std::string removeDeadCode(const std::string& js);
    
    // 常量内联
    std::string inlineConstants(const std::string& js);
    
private:
    // 变量名混淆
    std::string mangleVariableNames(const std::string& js);
    
    // 移除调试代码
    std::string removeDebugCode(const std::string& js);
};

// JavaScript模块处理器
class JSModuleProcessor {
private:
    std::shared_ptr<CHTLContext> context;
    
    // 模块信息
    struct ModuleInfo {
        std::string path;
        std::vector<std::string> imports;
        std::vector<std::string> exports;
        std::unordered_set<std::string> dependencies;
    };
    
    std::unordered_map<std::string, ModuleInfo> modules;
    
public:
    JSModuleProcessor(std::shared_ptr<CHTLContext> ctx) : context(ctx) {}
    
    // 处理ES6模块
    std::string processModules(const std::string& js, const std::string& modulePath);
    
    // 解析import语句
    std::vector<std::string> parseImports(const std::string& js);
    
    // 解析export语句
    std::vector<std::string> parseExports(const std::string& js);
    
    // 模块打包
    std::string bundleModules(const std::vector<std::string>& entryPoints);
    
    // 转换为CommonJS
    std::string convertToCommonJS(const std::string& js);
    
    // 转换为AMD
    std::string convertToAMD(const std::string& js);
};

// CHTL JavaScript处理器 - 集成到CHTL
class CHTLJSProcessor {
private:
    std::shared_ptr<CHTLContext> context;
    std::shared_ptr<JSCompiler> compiler;
    std::shared_ptr<JSOptimizer> optimizer;
    std::shared_ptr<JSModuleProcessor> moduleProcessor;
    
    // 存储所有的JS块
    std::vector<std::string> globalScripts;  // <script>标签中的脚本
    std::vector<std::string> localScripts;   // 局部script {}块
    std::vector<std::string> inlineScripts;  // 内联事件处理器
    
    // 模块管理
    std::unordered_map<std::string, std::string> modules;
    std::vector<std::string> moduleOrder;
    
public:
    CHTLJSProcessor(std::shared_ptr<CHTLContext> ctx);
    
    // 添加脚本
    void addGlobalScript(const std::string& js, const std::string& type = "text/javascript");
    void addLocalScript(const std::string& js, const std::string& scope = "");
    void addInlineScript(const std::string& js, const std::string& element = "");
    
    // 添加模块
    void addModule(const std::string& name, const std::string& js);
    
    // 处理并生成最终的JavaScript
    std::string generateFinalJS();
    
    // 获取所有符号信息（用于IDE支持）
    std::unordered_map<std::string, JSSymbol> getAllSymbols();
    
    // 验证引用
    void validateReferences();
    
    // 生成source map
    std::string generateSourceMap();
};

// JavaScript运行时支持
namespace JSRuntime {
    // CHTL JS运行时函数
    extern const char* CHTL_RUNTIME_CODE;
    
    // 生成运行时代码
    std::string generateRuntimeCode();
    
    // Polyfills
    std::string generatePolyfills(const std::vector<std::string>& features);
}

} // namespace chtl

#endif // CHTL_JS_COMPILER_H