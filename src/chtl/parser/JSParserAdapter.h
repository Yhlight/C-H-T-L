#ifndef CHTL_JS_PARSER_ADAPTER_H
#define CHTL_JS_PARSER_ADAPTER_H

#include <string>
#include <memory>
#include <vector>

namespace chtl {
namespace parser {

// JS解析器接口 - 隐藏ANTLR4实现细节
class IJSParser {
public:
    virtual ~IJSParser() = default;
    
    struct Options {
        bool minify = false;
        bool removeComments = true;
        bool obfuscateVariables = false;
        bool preserveConsole = true;
        bool esModules = true;
        bool sourceMap = false;
    };
    
    struct ParseResult {
        std::string code;
        std::string sourceMap;
        bool success = false;
        std::string error;
    };
    
    // 解析JavaScript
    virtual ParseResult parse(const std::string& js, const Options& options = {}) = 0;
    
    // 解析CHTL JavaScript（支持CHTL扩展）
    virtual ParseResult parseCHTLJS(const std::string& js, const Options& options = {}) = 0;
    
    // 验证语法
    virtual bool validate(const std::string& js) = 0;
    
    // 获取AST（用于高级优化）
    virtual std::string getAST(const std::string& js) = 0;
};

// JS解析器工厂
class JSParserFactory {
public:
    static std::unique_ptr<IJSParser> create();
};

} // namespace parser
} // namespace chtl

#endif // CHTL_JS_PARSER_ADAPTER_H