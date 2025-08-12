#include "StandardGenerator.h"
#include <sstream>

namespace CHTL {

// 内部实现类
class StandardGenerator::HtmlGeneratorImpl {
public:
    std::string generate(NodePtr node) {
        // TODO: 实现HTML生成
        return "<html><!-- TODO: Implement HTML generation --></html>";
    }
};

class StandardGenerator::CssGeneratorImpl {
public:
    std::string generate(const std::vector<NodePtr>& styleNodes) {
        // TODO: 实现CSS生成
        return "/* TODO: Implement CSS generation */";
    }
};

class StandardGenerator::JsGeneratorImpl {
public:
    std::string generate(const std::vector<NodePtr>& scriptNodes) {
        // TODO: 实现JavaScript生成
        return "// TODO: Implement JavaScript generation";
    }
};

StandardGenerator::StandardGenerator() {
    htmlGenerator_ = std::make_unique<HtmlGeneratorImpl>();
    cssGenerator_ = std::make_unique<CssGeneratorImpl>();
    jsGenerator_ = std::make_unique<JsGeneratorImpl>();
}

StandardGenerator::~StandardGenerator() = default;

GenerateResult StandardGenerator::generate(NodePtr ast, SymbolTable* symbolTable) {
    GenerateResult result;
    
    if (!ast) {
        result.success = false;
        result.errors.push_back("AST根节点为空");
        return result;
    }
    
    try {
        // 预处理AST
        preprocessAST(ast, symbolTable);
        
        // 收集样式和脚本节点
        std::vector<NodePtr> styleNodes;
        std::vector<NodePtr> scriptNodes;
        collectStyles(ast, styleNodes);
        collectScripts(ast, scriptNodes);
        
        // 生成代码
        result.html = generateHTML(ast);
        result.css = generateCSS(styleNodes);
        result.javascript = generateJavaScript(scriptNodes);
        
        // 生成模块文件
        if (modularize_) {
            generateModules(ast, result);
        }
        
        // 优化代码
        if (optimizationLevel_ > 0) {
            optimizeCode(result);
        }
        
        // 格式化代码
        if (minify_) {
            result.html = minifyCode(result.html, "html");
            result.css = minifyCode(result.css, "css");
            result.javascript = minifyCode(result.javascript, "javascript");
        } else if (prettify_) {
            result.html = prettifyCode(result.html, "html");
            result.css = prettifyCode(result.css, "css");
            result.javascript = prettifyCode(result.javascript, "javascript");
        }
        
        result.success = true;
    } catch (const std::exception& e) {
        result.success = false;
        result.errors.push_back(std::string("生成错误: ") + e.what());
    }
    
    return result;
}

void StandardGenerator::setOutputConfig(const std::string& key, const std::string& value) {
    outputConfig_[key] = value;
}

void StandardGenerator::preprocessAST(NodePtr ast, SymbolTable* symbolTable) {
    if (!ast || !symbolTable) return;
    
    // 展开模板和自定义
    expandTemplatesAndCustoms(ast, symbolTable);
    
    // TODO: 其他预处理步骤
}

void StandardGenerator::expandTemplatesAndCustoms(NodePtr ast, SymbolTable* symbolTable) {
    // TODO: 实现模板和自定义展开
}

void StandardGenerator::collectStyles(NodePtr ast, std::vector<NodePtr>& styleNodes) {
    if (!ast) return;
    
    // 如果是样式节点，添加到列表
    if (ast->getType() == NodeType::STYLE) {
        styleNodes.push_back(ast);
    }
    
    // 递归处理子节点
    for (size_t i = 0; i < ast->getChildCount(); ++i) {
        collectStyles(ast->getChild(i), styleNodes);
    }
}

void StandardGenerator::collectScripts(NodePtr ast, std::vector<NodePtr>& scriptNodes) {
    if (!ast) return;
    
    // 如果是脚本节点，添加到列表
    if (ast->getType() == NodeType::SCRIPT) {
        scriptNodes.push_back(ast);
    }
    
    // 递归处理子节点
    for (size_t i = 0; i < ast->getChildCount(); ++i) {
        collectScripts(ast->getChild(i), scriptNodes);
    }
}

std::string StandardGenerator::generateHTML(NodePtr ast) {
    return htmlGenerator_->generate(ast);
}

std::string StandardGenerator::generateCSS(const std::vector<NodePtr>& styleNodes) {
    return cssGenerator_->generate(styleNodes);
}

std::string StandardGenerator::generateJavaScript(const std::vector<NodePtr>& scriptNodes) {
    return jsGenerator_->generate(scriptNodes);
}

void StandardGenerator::generateModules(NodePtr ast, GenerateResult& result) {
    // TODO: 实现模块生成
}

void StandardGenerator::optimizeCode(GenerateResult& result) {
    // TODO: 实现代码优化
}

std::string StandardGenerator::formatCode(const std::string& code, const std::string& language) {
    if (minify_) {
        return minifyCode(code, language);
    } else if (prettify_) {
        return prettifyCode(code, language);
    }
    return code;
}

std::string StandardGenerator::minifyCode(const std::string& code, const std::string& language) {
    // TODO: 实现代码压缩
    // 简单实现：移除多余空白
    std::stringstream ss;
    bool inString = false;
    char stringChar = 0;
    bool lastWasSpace = false;
    
    for (size_t i = 0; i < code.length(); ++i) {
        char c = code[i];
        
        if (!inString && (c == '"' || c == '\'')) {
            inString = true;
            stringChar = c;
            ss << c;
        } else if (inString && c == stringChar && (i == 0 || code[i-1] != '\\')) {
            inString = false;
            ss << c;
        } else if (inString) {
            ss << c;
        } else if (std::isspace(c)) {
            if (!lastWasSpace) {
                ss << ' ';
                lastWasSpace = true;
            }
        } else {
            ss << c;
            lastWasSpace = false;
        }
    }
    
    return ss.str();
}

std::string StandardGenerator::prettifyCode(const std::string& code, const std::string& language) {
    // TODO: 实现代码美化
    // 暂时返回原始代码
    return code;
}

} // namespace CHTL