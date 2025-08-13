#include "CHTLJSCompiler.h"
#include <antlr4-runtime.h>
#include <algorithm>
#include <regex>
#include <sstream>

namespace chtl {

// JSScope 实现
bool JSScope::addSymbol(const JSSymbol& symbol) {
    if (symbols.find(symbol.name) != symbols.end()) {
        return false;  // 符号已存在
    }
    symbols[symbol.name] = symbol;
    return true;
}

JSSymbol* JSScope::findSymbol(const std::string& name) {
    auto it = symbols.find(name);
    return (it != symbols.end()) ? &it->second : nullptr;
}

JSSymbol* JSScope::findSymbolInChain(const std::string& name) {
    JSSymbol* symbol = findSymbol(name);
    if (symbol) {
        return symbol;
    }
    
    if (parent) {
        return parent->findSymbolInChain(name);
    }
    
    return nullptr;
}

// JSCompilerListener 实现
JSCompilerListener::JSCompilerListener(std::shared_ptr<CHTLContext> ctx, bool minifyOutput)
    : context(ctx), minify(minifyOutput) {
    globalScope = std::make_shared<JSScope>(JSScopeType::Global);
    currentScope = globalScope;
    scopeStack.push_back(globalScope);
}

void JSCompilerListener::enterProgram(JavaScriptParser::ProgramContext* ctx) {
    // 开始处理程序
    if (!minify && preserveComments) {
        output << "// Compiled by CHTL JavaScript Compiler\n";
    }
}

void JSCompilerListener::exitProgram(JavaScriptParser::ProgramContext* ctx) {
    // 检查未使用的变量
    for (const auto& [name, symbol] : globalScope->getSymbols()) {
        if (!symbol.isUsed && !symbol.isExported) {
            reportWarning("Unused variable: " + name, symbol.line, symbol.column);
        }
    }
}

void JSCompilerListener::enterFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext* ctx) {
    std::string functionName = ctx->identifier()->getText();
    
    // 注册函数符号
    registerSymbol(functionName, "function");
    
    // 进入函数作用域
    enterScope(JSScopeType::Function, functionName);
    
    // 输出函数声明
    output << indent() << "function " << functionName << "(";
    
    // 处理参数
    if (ctx->formalParameterList()) {
        output << extractText(ctx->formalParameterList());
    }
    
    output << ") ";
    
    if (!minify) {
        output << "{\n";
        increaseIndent();
    } else {
        output << "{";
    }
}

void JSCompilerListener::exitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext* ctx) {
    exitScope();
    
    if (!minify) {
        decreaseIndent();
        output << indent() << "}\n";
    } else {
        output << "}";
    }
}

void JSCompilerListener::enterClassDeclaration(JavaScriptParser::ClassDeclarationContext* ctx) {
    std::string className = ctx->identifier()->getText();
    
    // 注册类符号
    registerSymbol(className, "class");
    
    // 进入类作用域
    enterScope(JSScopeType::Class, className);
    
    // 输出类声明
    output << indent() << "class " << className;
    
    if (ctx->classExtends()) {
        output << " extends " << extractText(ctx->classExtends());
    }
    
    if (!minify) {
        output << " {\n";
        increaseIndent();
    } else {
        output << "{";
    }
}

void JSCompilerListener::exitClassDeclaration(JavaScriptParser::ClassDeclarationContext* ctx) {
    exitScope();
    
    if (!minify) {
        decreaseIndent();
        output << indent() << "}\n";
    } else {
        output << "}";
    }
}

void JSCompilerListener::enterVariableDeclaration(JavaScriptParser::VariableDeclarationContext* ctx) {
    // 获取变量声明类型
    std::string declarationType = ctx->variableDeclarationKind()->getText();
    bool isConst = (declarationType == "const");
    bool isLet = (declarationType == "let");
    
    // 处理每个变量
    for (auto* declarator : ctx->variableDeclaratorList()->variableDeclarator()) {
        std::string varName = declarator->identifier()->getText();
        registerSymbol(varName, "variable", isConst, isLet);
    }
    
    // 输出变量声明
    output << indent() << declarationType << " ";
    output << extractText(ctx->variableDeclaratorList());
    output << ";";
    
    if (!minify) {
        output << "\n";
    }
}

void JSCompilerListener::enterImportDeclaration(JavaScriptParser::ImportDeclarationContext* ctx) {
    std::string importText = extractText(ctx);
    imports.push_back(importText);
    
    output << indent() << importText << ";";
    if (!minify) {
        output << "\n";
    }
}

void JSCompilerListener::enterExportDeclaration(JavaScriptParser::ExportDeclarationContext* ctx) {
    std::string exportText = extractText(ctx);
    exports.push_back(exportText);
    
    output << indent() << exportText;
    if (!minify && exportText.back() != '}') {
        output << "\n";
    }
}

void JSCompilerListener::enterBlockStatement(JavaScriptParser::BlockStatementContext* ctx) {
    enterScope(JSScopeType::Block);
    
    output << indent() << "{";
    if (!minify) {
        output << "\n";
        increaseIndent();
    }
}

void JSCompilerListener::exitBlockStatement(JavaScriptParser::BlockStatementContext* ctx) {
    exitScope();
    
    if (!minify) {
        decreaseIndent();
        output << indent() << "}\n";
    } else {
        output << "}";
    }
}

std::string JSCompilerListener::extractText(antlr4::ParserRuleContext* ctx) {
    if (!ctx) return "";
    
    antlr4::misc::Interval interval(ctx->getStart()->getStartIndex(), 
                                   ctx->getStop()->getStopIndex());
    return ctx->getStart()->getInputStream()->getText(interval);
}

std::string JSCompilerListener::indent() const {
    if (minify) return "";
    return std::string(indentLevel * indentString.length(), ' ');
}

void JSCompilerListener::enterScope(JSScopeType type, const std::string& name) {
    auto newScope = std::make_shared<JSScope>(type, currentScope, name);
    currentScope = newScope;
    scopeStack.push_back(newScope);
}

void JSCompilerListener::exitScope() {
    if (scopeStack.size() > 1) {
        scopeStack.pop_back();
        currentScope = scopeStack.back();
    }
}

void JSCompilerListener::registerSymbol(const std::string& name, const std::string& type, 
                                       bool isConst, bool isLet) {
    JSSymbol symbol;
    symbol.name = name;
    symbol.type = type;
    symbol.isConst = isConst;
    symbol.isLet = isLet;
    // TODO: 获取实际的行号和列号
    symbol.line = 0;
    symbol.column = 0;
    
    if (!currentScope->addSymbol(symbol)) {
        reportError("Duplicate identifier: " + name, symbol.line, symbol.column);
    }
}

void JSCompilerListener::markSymbolAsUsed(const std::string& name) {
    JSSymbol* symbol = currentScope->findSymbolInChain(name);
    if (symbol) {
        symbol->isUsed = true;
    } else {
        reportWarning("Undefined variable: " + name, 0, 0);
    }
}

void JSCompilerListener::reportError(const std::string& message, size_t line, size_t column) {
    std::stringstream ss;
    ss << "Error at line " << line << ":" << column << " - " << message;
    errors.push_back(ss.str());
    context->reportError(ss.str());
}

void JSCompilerListener::reportWarning(const std::string& message, size_t line, size_t column) {
    std::stringstream ss;
    ss << "Warning at line " << line << ":" << column << " - " << message;
    warnings.push_back(ss.str());
    context->reportWarning(ss.str());
}

// JSCompiler 实现
JSCompiler::JSCompiler(std::shared_ptr<CHTLContext> ctx) : context(ctx) {}

std::string JSCompiler::compile(const std::string& js) {
    antlr4::ANTLRInputStream input(js);
    JavaScriptLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    JavaScriptParser parser(&tokens);
    
    // 错误处理
    std::vector<std::string> errors;
    JSErrorListener errorListener(errors);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    
    // 解析
    JavaScriptParser::ProgramContext* tree = parser.program();
    
    if (!errors.empty()) {
        for (const auto& error : errors) {
            context->reportError(error);
        }
        return "";
    }
    
    // 编译
    JSCompilerListener listener(context, options.minify);
    listener.preserveComments = options.preserveComments;
    listener.addSourceMap = options.addSourceMap;
    
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    
    std::string result = listener.getCompiledJS();
    
    // 添加严格模式
    if (options.strictMode && result.find("\"use strict\"") == std::string::npos) {
        result = "\"use strict\";\n" + result;
    }
    
    return result;
}

JSCompiler::CompileResult JSCompiler::compileWithAnalysis(const std::string& js) {
    CompileResult result;
    
    antlr4::ANTLRInputStream input(js);
    JavaScriptLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    JavaScriptParser parser(&tokens);
    
    // 错误处理
    JSErrorListener errorListener(result.errors);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    
    // 解析
    JavaScriptParser::ProgramContext* tree = parser.program();
    
    if (!result.errors.empty()) {
        return result;
    }
    
    // 编译
    JSCompilerListener listener(context, options.minify);
    listener.preserveComments = options.preserveComments;
    
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    
    result.code = listener.getCompiledJS();
    result.warnings = listener.getWarnings();
    result.imports = listener.getImports();
    result.exports = listener.getExports();
    
    // TODO: 收集符号信息
    
    return result;
}

bool JSCompiler::validate(const std::string& js, std::vector<std::string>& errors) {
    antlr4::ANTLRInputStream input(js);
    JavaScriptLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    JavaScriptParser parser(&tokens);
    
    JSErrorListener errorListener(errors);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    
    parser.program();
    
    return errors.empty();
}

bool JSCompiler::checkSyntax(const std::string& js) {
    std::vector<std::string> errors;
    return validate(js, errors);
}

void JSCompiler::JSErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                             antlr4::Token* offendingSymbol,
                                             size_t line,
                                             size_t charPositionInLine,
                                             const std::string& msg,
                                             std::exception_ptr e) {
    std::stringstream error;
    error << "JavaScript Syntax Error at line " << line << ":" << charPositionInLine << " - " << msg;
    errors.push_back(error.str());
}

// JSOptimizer 实现
std::string JSOptimizer::optimize(const std::string& js) {
    std::string result = js;
    
    if (options.removeDeadCode) {
        result = removeDeadCode(result);
    }
    
    if (options.inlineConstants) {
        result = inlineConstants(result);
    }
    
    if (options.removeDebugger || options.removeConsoleLog) {
        result = removeDebugCode(result);
    }
    
    if (options.mangleVariables) {
        result = mangleVariableNames(result);
    }
    
    return result;
}

std::string JSOptimizer::minify(const std::string& js) {
    std::string result = js;
    
    // 移除注释
    result = std::regex_replace(result, std::regex("//.*$", std::regex::multiline), "");
    result = std::regex_replace(result, std::regex("/\\*.*?\\*/", std::regex::dotall), "");
    
    // 移除多余空白
    result = std::regex_replace(result, std::regex("\\s+"), " ");
    result = std::regex_replace(result, std::regex("\\s*([{}\\[\\]();,:])\\s*"), "$1");
    
    // 移除行尾分号前的空格
    result = std::regex_replace(result, std::regex("\\s*;"), ";");
    
    return result;
}

std::string JSOptimizer::removeDeadCode(const std::string& js) {
    // 简单的死代码删除实现
    std::string result = js;
    
    // 移除永远不会执行的代码
    result = std::regex_replace(result, 
        std::regex("if\\s*\\(\\s*false\\s*\\)\\s*{[^}]*}"), "");
    
    // 移除return后的代码
    result = std::regex_replace(result,
        std::regex("return[^;]*;[^}]+(?=})"), "return$1;");
    
    return result;
}

std::string JSOptimizer::inlineConstants(const std::string& js) {
    // 简单的常量内联实现
    std::string result = js;
    
    // 查找const声明
    std::regex constRegex("const\\s+(\\w+)\\s*=\\s*([^;]+);");
    std::smatch match;
    
    std::unordered_map<std::string, std::string> constants;
    
    // 收集常量
    std::string::const_iterator searchStart(js.cbegin());
    while (std::regex_search(searchStart, js.cend(), match, constRegex)) {
        constants[match[1]] = match[2];
        searchStart = match.suffix().first;
    }
    
    // 内联常量
    for (const auto& [name, value] : constants) {
        // 只内联简单的字面量值
        if (std::regex_match(value, std::regex("[0-9]+|\"[^\"]*\"|'[^']*'|true|false|null"))) {
            result = std::regex_replace(result, std::regex("\\b" + name + "\\b"), value);
        }
    }
    
    return result;
}

std::string JSOptimizer::mangleVariableNames(const std::string& js) {
    // 简单的变量名混淆
    std::string result = js;
    
    // 生成短变量名
    std::vector<std::string> shortNames;
    for (char c = 'a'; c <= 'z'; ++c) {
        shortNames.push_back(std::string(1, c));
    }
    
    // TODO: 实现完整的变量名混淆
    
    return result;
}

std::string JSOptimizer::removeDebugCode(const std::string& js) {
    std::string result = js;
    
    if (options.removeDebugger) {
        result = std::regex_replace(result, std::regex("\\bdebugger\\s*;"), "");
    }
    
    if (options.removeConsoleLog) {
        result = std::regex_replace(result, std::regex("console\\.log\\s*\\([^)]*\\)\\s*;?"), "");
        result = std::regex_replace(result, std::regex("console\\.(warn|error|info|debug)\\s*\\([^)]*\\)\\s*;?"), "");
    }
    
    return result;
}

// JSModuleProcessor 实现
std::string JSModuleProcessor::processModules(const std::string& js, const std::string& modulePath) {
    ModuleInfo moduleInfo;
    moduleInfo.path = modulePath;
    moduleInfo.imports = parseImports(js);
    moduleInfo.exports = parseExports(js);
    
    modules[modulePath] = moduleInfo;
    
    // TODO: 实现模块处理逻辑
    
    return js;
}

std::vector<std::string> JSModuleProcessor::parseImports(const std::string& js) {
    std::vector<std::string> imports;
    
    // 匹配import语句
    std::regex importRegex("import\\s+(?:([^\\s]+)\\s+from\\s+)?['\"]([^'\"]+)['\"];?");
    std::smatch match;
    
    std::string::const_iterator searchStart(js.cbegin());
    while (std::regex_search(searchStart, js.cend(), match, importRegex)) {
        imports.push_back(match[0]);
        searchStart = match.suffix().first;
    }
    
    return imports;
}

std::vector<std::string> JSModuleProcessor::parseExports(const std::string& js) {
    std::vector<std::string> exports;
    
    // 匹配export语句
    std::regex exportRegex("export\\s+(?:default\\s+)?(?:const|let|var|function|class)?\\s*([^;{]+)");
    std::smatch match;
    
    std::string::const_iterator searchStart(js.cbegin());
    while (std::regex_search(searchStart, js.cend(), match, exportRegex)) {
        exports.push_back(match[0]);
        searchStart = match.suffix().first;
    }
    
    return exports;
}

std::string JSModuleProcessor::bundleModules(const std::vector<std::string>& entryPoints) {
    // TODO: 实现模块打包
    return "";
}

std::string JSModuleProcessor::convertToCommonJS(const std::string& js) {
    std::string result = js;
    
    // 转换import为require
    result = std::regex_replace(result, 
        std::regex("import\\s+([^\\s]+)\\s+from\\s+['\"]([^'\"]+)['\"];?"),
        "const $1 = require('$2');");
    
    // 转换export为module.exports
    result = std::regex_replace(result,
        std::regex("export\\s+default\\s+"),
        "module.exports = ");
    
    result = std::regex_replace(result,
        std::regex("export\\s+{([^}]+)}"),
        "module.exports = {$1}");
    
    return result;
}

std::string JSModuleProcessor::convertToAMD(const std::string& js) {
    // TODO: 实现AMD转换
    return js;
}

// CHTLJSProcessor 实现
CHTLJSProcessor::CHTLJSProcessor(std::shared_ptr<CHTLContext> ctx) : context(ctx) {
    compiler = std::make_shared<JSCompiler>(ctx);
    optimizer = std::make_shared<JSOptimizer>();
    moduleProcessor = std::make_shared<JSModuleProcessor>(ctx);
}

void CHTLJSProcessor::addGlobalScript(const std::string& js, const std::string& type) {
    globalScripts.push_back(js);
}

void CHTLJSProcessor::addLocalScript(const std::string& js, const std::string& scope) {
    // 包装局部脚本以确保作用域隔离
    std::string wrappedScript = "(function() {\n" + js + "\n})();";
    localScripts.push_back(wrappedScript);
}

void CHTLJSProcessor::addInlineScript(const std::string& js, const std::string& element) {
    inlineScripts.push_back(js);
}

void CHTLJSProcessor::addModule(const std::string& name, const std::string& js) {
    modules[name] = js;
    moduleOrder.push_back(name);
}

std::string CHTLJSProcessor::generateFinalJS() {
    std::stringstream finalJS;
    
    // 添加运行时代码
    finalJS << JSRuntime::generateRuntimeCode() << "\n\n";
    
    // 处理模块
    for (const auto& moduleName : moduleOrder) {
        auto it = modules.find(moduleName);
        if (it != modules.end()) {
            std::string compiledModule = compiler->compile(it->second);
            finalJS << "// Module: " << moduleName << "\n";
            finalJS << compiledModule << "\n\n";
        }
    }
    
    // 处理全局脚本
    for (const auto& script : globalScripts) {
        std::string compiledScript = compiler->compile(script);
        finalJS << compiledScript << "\n\n";
    }
    
    // 处理局部脚本
    if (!localScripts.empty()) {
        finalJS << "// Local Scripts\n";
        for (const auto& script : localScripts) {
            std::string compiledScript = compiler->compile(script);
            finalJS << compiledScript << "\n";
        }
        finalJS << "\n";
    }
    
    // 优化最终代码
    if (compiler->getOptions().minify) {
        return optimizer->optimize(finalJS.str());
    }
    
    return finalJS.str();
}

std::unordered_map<std::string, JSSymbol> CHTLJSProcessor::getAllSymbols() {
    std::unordered_map<std::string, JSSymbol> allSymbols;
    
    // TODO: 收集所有符号信息
    
    return allSymbols;
}

void CHTLJSProcessor::validateReferences() {
    // TODO: 实现引用验证
}

std::string CHTLJSProcessor::generateSourceMap() {
    // TODO: 实现source map生成
    return "{}";
}

// JSRuntime 实现
namespace JSRuntime {

const char* CHTL_RUNTIME_CODE = R"(
// CHTL JavaScript Runtime
(function(window) {
    'use strict';
    
    // CHTL namespace
    window.CHTL = window.CHTL || {};
    
    // DOM utilities
    CHTL.$ = function(selector) {
        return document.querySelector(selector);
    };
    
    CHTL.$$ = function(selector) {
        return document.querySelectorAll(selector);
    };
    
    // Event utilities
    CHTL.on = function(element, event, handler) {
        element.addEventListener(event, handler);
    };
    
    CHTL.off = function(element, event, handler) {
        element.removeEventListener(event, handler);
    };
    
    // AJAX utilities
    CHTL.ajax = function(options) {
        return fetch(options.url, {
            method: options.method || 'GET',
            headers: options.headers || {},
            body: options.data
        }).then(response => response.json());
    };
    
})(window);
)";

std::string generateRuntimeCode() {
    return CHTL_RUNTIME_CODE;
}

std::string generatePolyfills(const std::vector<std::string>& features) {
    std::stringstream polyfills;
    
    for (const auto& feature : features) {
        if (feature == "Promise") {
            polyfills << "// Promise polyfill\n";
            polyfills << "// ... Promise implementation ...\n\n";
        } else if (feature == "fetch") {
            polyfills << "// Fetch polyfill\n";
            polyfills << "// ... Fetch implementation ...\n\n";
        } else if (feature == "Array.from") {
            polyfills << "// Array.from polyfill\n";
            polyfills << "if (!Array.from) { Array.from = function() { /* ... */ }; }\n\n";
        }
        // ... 更多polyfills
    }
    
    return polyfills.str();
}

} // namespace JSRuntime

} // namespace chtl