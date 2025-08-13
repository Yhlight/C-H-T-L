#ifndef CHTL_CSS_PARSER_ADAPTER_H
#define CHTL_CSS_PARSER_ADAPTER_H

#include <string>
#include <memory>

namespace chtl {
namespace parser {

// CSS解析器接口 - 隐藏ANTLR4实现细节
class ICSSParser {
public:
    virtual ~ICSSParser() = default;
    
    struct Options {
        bool minify = false;
        bool keepComments = false;
        bool resolveImports = true;
        bool autoprefixer = false;
    };
    
    // 解析CSS并返回处理后的结果
    virtual std::string parse(const std::string& css, const Options& options = {}) = 0;
    
    // 验证CSS语法
    virtual bool validate(const std::string& css) = 0;
    
    // 获取错误信息
    virtual std::string getLastError() const = 0;
};

// CSS解析器工厂
class CSSParserFactory {
public:
    static std::unique_ptr<ICSSParser> create();
};

} // namespace parser
} // namespace chtl

#endif // CHTL_CSS_PARSER_ADAPTER_H