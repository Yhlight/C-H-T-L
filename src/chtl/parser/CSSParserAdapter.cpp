#include "CSSParserAdapter.h"

#ifdef USE_ANTLR4_FOR_CSS_JS
    // 使用ANTLR4生成的CSS解析器
    #include "antlr4-runtime.h"
    #include "generated/css/CSSLexer.h"
    #include "generated/css/CSSParser.h"
    #include "generated/css/CSSBaseListener.h"
    
    using namespace antlr4;
#else
    // 使用独立的简化CSS解析器
    #include "standalone/CSSParser.h"
#endif

namespace chtl {
namespace parser {

#ifdef USE_ANTLR4_FOR_CSS_JS

// ANTLR4 CSS解析器实现
class ANTLR4CSSParser : public ICSSParser {
public:
    std::string parse(const std::string& css, const Options& options) override {
        try {
            ANTLRInputStream input(css);
            CSSLexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            CSSParser parser(&tokens);
            
            // 移除默认错误监听器，使用自定义的
            parser.removeErrorListeners();
            parser.addErrorListener(&errorListener_);
            
            // 解析
            auto tree = parser.stylesheet();
            
            if (errorListener_.hasError()) {
                lastError_ = errorListener_.getError();
                return "";
            }
            
            // 处理解析树
            CSSProcessListener listener(options);
            tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
            
            return listener.getOutput();
            
        } catch (const std::exception& e) {
            lastError_ = std::string("CSS parsing error: ") + e.what();
            return "";
        }
    }
    
    bool validate(const std::string& css) override {
        try {
            ANTLRInputStream input(css);
            CSSLexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            CSSParser parser(&tokens);
            
            parser.removeErrorListeners();
            parser.addErrorListener(&errorListener_);
            
            parser.stylesheet();
            
            return !errorListener_.hasError();
            
        } catch (...) {
            return false;
        }
    }
    
    std::string getLastError() const override {
        return lastError_;
    }
    
private:
    // 自定义错误监听器
    class ErrorListener : public BaseErrorListener {
    public:
        void syntaxError(Recognizer* recognizer, Token* offendingSymbol,
                        size_t line, size_t charPositionInLine,
                        const std::string& msg, std::exception_ptr e) override {
            hasError_ = true;
            error_ = "Line " + std::to_string(line) + ":" + 
                    std::to_string(charPositionInLine) + " - " + msg;
        }
        
        bool hasError() const { return hasError_; }
        std::string getError() const { return error_; }
        void reset() { hasError_ = false; error_.clear(); }
        
    private:
        bool hasError_ = false;
        std::string error_;
    };
    
    // CSS处理监听器
    class CSSProcessListener : public CSSBaseListener {
    public:
        CSSProcessListener(const Options& options) : options_(options) {}
        
        void enterStylesheet(CSSParser::StylesheetContext* ctx) override {
            // 处理样式表开始
        }
        
        void exitRuleset(CSSParser::RulesetContext* ctx) override {
            // 处理规则集
            if (options_.minify) {
                // 压缩输出
                processMinified(ctx);
            } else {
                // 格式化输出
                processFormatted(ctx);
            }
        }
        
        std::string getOutput() const { return output_.str(); }
        
    private:
        const Options& options_;
        std::stringstream output_;
        
        void processMinified(CSSParser::RulesetContext* ctx) {
            // 实现压缩逻辑
            output_ << ctx->getText();
        }
        
        void processFormatted(CSSParser::RulesetContext* ctx) {
            // 实现格式化逻辑
            output_ << ctx->getText() << "\n";
        }
    };
    
    mutable ErrorListener errorListener_;
    std::string lastError_;
};

#else

// 简化CSS解析器实现
class SimpleCSSParser : public ICSSParser {
public:
    std::string parse(const std::string& css, const Options& options) override {
        try {
            CSSParser parser(css);
            return parser.parse();
        } catch (const std::exception& e) {
            lastError_ = std::string("CSS parsing error: ") + e.what();
            return "";
        }
    }
    
    bool validate(const std::string& css) override {
        try {
            CSSParser parser(css);
            parser.parse();
            return true;
        } catch (...) {
            return false;
        }
    }
    
    std::string getLastError() const override {
        return lastError_;
    }
    
private:
    std::string lastError_;
};

#endif

// 工厂实现
std::unique_ptr<ICSSParser> CSSParserFactory::create() {
#ifdef USE_ANTLR4_FOR_CSS_JS
    return std::make_unique<ANTLR4CSSParser>();
#else
    return std::make_unique<SimpleCSSParser>();
#endif
}

} // namespace parser
} // namespace chtl