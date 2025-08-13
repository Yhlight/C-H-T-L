#include "CHTLJSOptimizer.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include <chrono>

namespace chtl {

// JSVariableObfuscator 实现

JSVariableObfuscator::JSVariableObfuscator(const JSOptimizationOptions& options)
    : options(options), randomEngine(std::chrono::steady_clock::now().time_since_epoch().count()) {
    initializeReservedIdentifiers();
    enterScope(); // 全局作用域
}

void JSVariableObfuscator::initializeReservedIdentifiers() {
    // JavaScript 保留字
    static const std::vector<std::string> jsKeywords = {
        "break", "case", "catch", "class", "const", "continue", "debugger", "default",
        "delete", "do", "else", "export", "extends", "finally", "for", "function",
        "if", "import", "in", "instanceof", "let", "new", "return", "super", "switch",
        "this", "throw", "try", "typeof", "var", "void", "while", "with", "yield",
        "async", "await", "of", "static", "get", "set"
    };
    
    // 浏览器全局对象
    static const std::vector<std::string> browserGlobals = {
        "window", "document", "console", "alert", "prompt", "confirm", "setTimeout",
        "setInterval", "clearTimeout", "clearInterval", "localStorage", "sessionStorage",
        "location", "history", "navigator", "XMLHttpRequest", "fetch", "Promise",
        "Array", "Object", "String", "Number", "Boolean", "Function", "Date", "RegExp",
        "Error", "JSON", "Math", "parseInt", "parseFloat", "isNaN", "isFinite",
        "encodeURI", "decodeURI", "encodeURIComponent", "decodeURIComponent"
    };
    
    // Node.js 全局对象
    static const std::vector<std::string> nodeGlobals = {
        "global", "process", "Buffer", "require", "module", "exports", "__dirname",
        "__filename", "setImmediate", "clearImmediate"
    };
    
    for (const auto& keyword : jsKeywords) {
        reservedIdentifiers.insert(keyword);
    }
    
    if (options.preserveKeywords) {
        for (const auto& global : browserGlobals) {
            reservedIdentifiers.insert(global);
        }
        for (const auto& global : nodeGlobals) {
            reservedIdentifiers.insert(global);
        }
    }
}

std::string JSVariableObfuscator::obfuscate(const std::string& jsCode) {
    // 创建ANTLR输入流
    antlr4::ANTLRInputStream input(jsCode);
    JSLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    JSParser parser(&tokens);
    
    // 解析
    auto tree = parser.program();
    
    // 访问树进行混淆
    visit(tree);
    
    // 重建代码
    return rebuildCode(tree, &tokens, jsCode);
}

std::string JSVariableObfuscator::rebuildCode(antlr4::tree::ParseTree* tree, 
                                             antlr4::CommonTokenStream* tokens,
                                             const std::string& jsCode) {
    // 获取所有token
    tokens->fill();
    auto allTokens = tokens->getTokens();
    
    std::stringstream result;
    size_t lastEnd = 0;
    
    // 遍历所有token，替换标识符
    for (auto token : allTokens) {
        // 保留原始空白和注释
        if (token->getStartIndex() > lastEnd) {
            result << jsCode.substr(lastEnd, token->getStartIndex() - lastEnd);
        }
        
        if (token->getType() == JSLexer::Identifier) {
            std::string originalName = token->getText();
            std::string obfuscatedName = getObfuscatedName(originalName);
            result << obfuscatedName;
        } else {
            result << token->getText();
        }
        
        lastEnd = token->getStopIndex() + 1;
    }
    
    // 添加剩余内容
    if (lastEnd < jsCode.length()) {
        result << jsCode.substr(lastEnd);
    }
    
    return result.str();
}

antlrcpp::Any JSVariableObfuscator::visitProgram(JSParser::ProgramContext* ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any JSVariableObfuscator::visitVariableDeclaration(JSParser::VariableDeclarationContext* ctx) {
    // 获取变量名
    if (ctx->Identifier()) {
        std::string varName = ctx->Identifier()->getText();
        if (!isReserved(varName)) {
            addVariable(varName);
        }
    }
    return visitChildren(ctx);
}

antlrcpp::Any JSVariableObfuscator::visitFunctionDeclaration(JSParser::FunctionDeclarationContext* ctx) {
    // 函数名
    if (ctx->Identifier()) {
        std::string funcName = ctx->Identifier()->getText();
        if (!isReserved(funcName)) {
            addVariable(funcName, false, true);
        }
    }
    
    // 进入新作用域
    enterScope();
    
    // 处理参数和函数体
    visitChildren(ctx);
    
    // 退出作用域
    exitScope();
    
    return nullptr;
}

antlrcpp::Any JSVariableObfuscator::visitFormalParameterList(JSParser::FormalParameterListContext* ctx) {
    // 处理函数参数
    auto identifiers = ctx->Identifier();
    for (auto id : identifiers) {
        std::string paramName = id->getText();
        if (!isReserved(paramName)) {
            addVariable(paramName, true);
        }
    }
    return visitChildren(ctx);
}

antlrcpp::Any JSVariableObfuscator::visitIdentifierExpression(JSParser::IdentifierExpressionContext* ctx) {
    // 标识符使用时不需要特殊处理，在重建代码时会自动替换
    return visitChildren(ctx);
}

antlrcpp::Any JSVariableObfuscator::visitBlock(JSParser::BlockContext* ctx) {
    // 块级作用域
    enterScope();
    visitChildren(ctx);
    exitScope();
    return nullptr;
}

void JSVariableObfuscator::enterScope() {
    scopeStack.push_back(std::unordered_map<std::string, VariableScope>());
    currentScopeLevel++;
}

void JSVariableObfuscator::exitScope() {
    if (!scopeStack.empty()) {
        scopeStack.pop_back();
        currentScopeLevel--;
    }
}

void JSVariableObfuscator::addVariable(const std::string& name, bool isParameter, bool isFunction) {
    if (scopeStack.empty()) return;
    
    VariableScope varScope;
    varScope.originalName = name;
    varScope.obfuscatedName = generateObfuscatedName();
    varScope.scopeLevel = currentScopeLevel;
    varScope.isGlobal = (currentScopeLevel == 1);
    varScope.isParameter = isParameter;
    varScope.isFunction = isFunction;
    
    scopeStack.back()[name] = varScope;
    
    // 如果是全局变量，加入全局映射
    if (varScope.isGlobal) {
        globalObfuscationMap[name] = varScope.obfuscatedName;
    }
}

std::string JSVariableObfuscator::getObfuscatedName(const std::string& originalName) {
    // 检查是否是保留标识符
    if (isReserved(originalName)) {
        return originalName;
    }
    
    // 从当前作用域向上查找
    for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
        auto found = it->find(originalName);
        if (found != it->end()) {
            return found->second.obfuscatedName;
        }
    }
    
    // 检查全局映射
    auto globalFound = globalObfuscationMap.find(originalName);
    if (globalFound != globalObfuscationMap.end()) {
        return globalFound->second;
    }
    
    // 未找到，返回原名
    return originalName;
}

std::string JSVariableObfuscator::generateObfuscatedName() {
    std::string name;
    
    switch (options.obfuscationLevel) {
        case 1:
            name = generateShortName(nameCounter);
            break;
        case 2:
            name = generateMediumName(nameCounter);
            break;
        case 3:
            name = generateLongName(nameCounter);
            break;
        default:
            name = generateMediumName(nameCounter);
    }
    
    nameCounter++;
    
    // 确保不与保留字冲突
    while (isReserved(name)) {
        nameCounter++;
        switch (options.obfuscationLevel) {
            case 1:
                name = generateShortName(nameCounter);
                break;
            case 2:
                name = generateMediumName(nameCounter);
                break;
            case 3:
                name = generateLongName(nameCounter);
                break;
        }
    }
    
    return name;
}

std::string JSVariableObfuscator::generateShortName(int index) {
    // 生成短名称：a, b, c, ..., z, aa, ab, ...
    std::string name;
    do {
        name = char('a' + (index % 26)) + name;
        index /= 26;
    } while (index > 0);
    return name;
}

std::string JSVariableObfuscator::generateMediumName(int index) {
    // 生成中等长度名称：_a, _b, ..., _0a, _0b, ...
    static const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string name = "_";
    
    do {
        name += chars[index % chars.length()];
        index /= chars.length();
    } while (index > 0);
    
    return name;
}

std::string JSVariableObfuscator::generateLongName(int index) {
    // 生成长名称：使用随机字符
    static const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::uniform_int_distribution<> dis(0, chars.length() - 1);
    
    std::string name;
    int length = 8 + (index % 8); // 8-15 字符长度
    
    // 确保第一个字符是字母
    name += chars[dis(randomEngine)];
    
    for (int i = 1; i < length; i++) {
        name += chars[dis(randomEngine)];
    }
    
    return name;
}

bool JSVariableObfuscator::isReserved(const std::string& name) const {
    return reservedIdentifiers.find(name) != reservedIdentifiers.end();
}

// JSOptimizer 实现

JSOptimizer::JSOptimizer(const JSOptimizationOptions& options)
    : options(options), obfuscator(std::make_unique<JSVariableObfuscator>(options)) {
    stats = {};
}

std::string JSOptimizer::optimize(const std::string& jsCode) {
    stats.originalSize = jsCode.size();
    std::string optimized = jsCode;
    
    // 1. 移除注释
    if (options.removeComments) {
        optimized = removeComments(optimized);
    }
    
    // 2. 混淆变量
    if (options.enableObfuscation && options.renameVariables) {
        optimized = obfuscateVariables(optimized);
    }
    
    // 3. 压缩空白
    if (options.minifyCode) {
        optimized = minifyWhitespace(optimized);
    }
    
    stats.optimizedSize = optimized.size();
    stats.compressionRatio = 1.0 - (double)stats.optimizedSize / stats.originalSize;
    
    return optimized;
}

std::string JSOptimizer::removeComments(const std::string& code) {
    std::string result;
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;
    bool inString = false;
    char stringChar = 0;
    int commentsRemoved = 0;
    
    for (size_t i = 0; i < code.length(); i++) {
        char c = code[i];
        char next = (i + 1 < code.length()) ? code[i + 1] : '\0';
        
        // 处理字符串
        if (!inSingleLineComment && !inMultiLineComment) {
            if ((c == '"' || c == '\'' || c == '`') && (i == 0 || code[i-1] != '\\')) {
                if (!inString) {
                    inString = true;
                    stringChar = c;
                } else if (c == stringChar) {
                    inString = false;
                }
                result += c;
                continue;
            }
        }
        
        if (inString) {
            result += c;
            continue;
        }
        
        // 处理注释
        if (!inSingleLineComment && !inMultiLineComment && c == '/' && next == '/') {
            inSingleLineComment = true;
            commentsRemoved++;
            i++; // 跳过下一个 '/'
            continue;
        }
        
        if (!inSingleLineComment && !inMultiLineComment && c == '/' && next == '*') {
            inMultiLineComment = true;
            commentsRemoved++;
            i++; // 跳过下一个 '*'
            continue;
        }
        
        if (inSingleLineComment && c == '\n') {
            inSingleLineComment = false;
            result += c; // 保留换行
            continue;
        }
        
        if (inMultiLineComment && c == '*' && next == '/') {
            inMultiLineComment = false;
            i++; // 跳过下一个 '/'
            continue;
        }
        
        // 添加非注释内容
        if (!inSingleLineComment && !inMultiLineComment) {
            result += c;
        }
    }
    
    stats.commentsRemoved = commentsRemoved;
    return result;
}

std::string JSOptimizer::minifyWhitespace(const std::string& code) {
    std::string result;
    bool inString = false;
    char stringChar = 0;
    bool lastWasSpace = false;
    bool lastWasOperator = true; // 开始时假设是操作符，防止开头空格
    
    for (size_t i = 0; i < code.length(); i++) {
        char c = code[i];
        char prev = (i > 0) ? code[i-1] : '\0';
        char next = (i + 1 < code.length()) ? code[i + 1] : '\0';
        
        // 处理字符串
        if ((c == '"' || c == '\'' || c == '`') && prev != '\\') {
            if (!inString) {
                inString = true;
                stringChar = c;
            } else if (c == stringChar) {
                inString = false;
            }
            result += c;
            lastWasSpace = false;
            lastWasOperator = false;
            continue;
        }
        
        if (inString) {
            result += c;
            continue;
        }
        
        // 处理空白字符
        if (std::isspace(c)) {
            // 需要保留空格的情况
            bool needSpace = false;
            
            // 在标识符之间需要空格
            if (i > 0 && i + 1 < code.length()) {
                bool prevIsIdChar = std::isalnum(prev) || prev == '_' || prev == '$';
                bool nextIsIdChar = std::isalnum(next) || next == '_' || next == '$';
                
                if (prevIsIdChar && nextIsIdChar) {
                    needSpace = true;
                }
                
                // 关键字后需要空格
                static const std::regex keywordRegex(R"(\b(var|let|const|function|return|if|else|for|while|do|switch|case|break|continue|try|catch|finally|throw|new|delete|typeof|instanceof|in|of|class|extends|async|await)\b)");
                if (i >= 2) {
                    std::string precedingWord;
                    size_t j = i - 1;
                    while (j > 0 && (std::isalnum(code[j]) || code[j] == '_')) {
                        precedingWord = code[j] + precedingWord;
                        j--;
                    }
                    if (std::regex_match(precedingWord, keywordRegex)) {
                        needSpace = true;
                    }
                }
            }
            
            if (needSpace && !lastWasSpace) {
                result += ' ';
                lastWasSpace = true;
            }
            
            // 保留必要的换行（如在 return 语句后）
            if (c == '\n' && prev == '}') {
                result += '\n';
            }
            
            continue;
        }
        
        // 处理分号（可选的分号可以省略）
        if (c == ';' && next == '}') {
            continue; // 省略块结尾前的分号
        }
        
        result += c;
        lastWasSpace = false;
        
        // 检查是否是操作符
        static const std::string operators = "+-*/%=<>!&|^~?:,;(){}[]";
        lastWasOperator = (operators.find(c) != std::string::npos);
    }
    
    return result;
}

std::string JSOptimizer::obfuscateVariables(const std::string& code) {
    int originalVarCount = countVariables(code);
    std::string obfuscated = obfuscator->obfuscate(code);
    stats.variablesRenamed = originalVarCount; // 简化统计
    return obfuscated;
}

int JSOptimizer::countVariables(const std::string& code) {
    // 简单的变量计数（用于统计）
    std::regex varRegex(R"(\b(var|let|const|function)\s+(\w+))");
    auto begin = std::sregex_iterator(code.begin(), code.end(), varRegex);
    auto end = std::sregex_iterator();
    return std::distance(begin, end);
}

} // namespace chtl