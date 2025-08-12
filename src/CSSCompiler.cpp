#include "CSSCompiler.h"
#include "CSSLexer.h"
#include "CSSParser.h"
#include "CSSBaseVisitor.h"
#include <sstream>

namespace CHTL {

// 错误监听器实现
class CSSCompiler::ErrorListener : public antlr4::BaseErrorListener {
public:
    ErrorListener(std::vector<std::string>& errors) : errors_(errors) {}
    
    void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol,
                    size_t line, size_t charPositionInLine,
                    const std::string& msg, std::exception_ptr e) override {
        std::stringstream ss;
        ss << "CSS语法错误 [" << line << ":" << charPositionInLine << "] " << msg;
        errors_.push_back(ss.str());
    }
    
private:
    std::vector<std::string>& errors_;
};

// CSS访问者实现
class CSSCompiler::CSSVisitorImpl : public CSSBaseVisitor {
public:
    CSSVisitorImpl() {}
    
    // TODO: 实现各个visit方法
    
private:
    std::shared_ptr<ASTNode> currentNode_;
};

CSSCompiler::CSSCompiler() {
    visitor_ = std::make_unique<CSSVisitorImpl>();
    errorListener_ = std::make_unique<ErrorListener>(errors_);
}

CSSCompiler::~CSSCompiler() = default;

std::shared_ptr<ASTNode> CSSCompiler::compile(const std::string& code) {
    try {
        // 创建输入流
        antlr4::ANTLRInputStream input(code);
        
        // 创建词法分析器
        CSSLexer lexer(&input);
        lexer.removeErrorListeners();
        lexer.addErrorListener(errorListener_.get());
        
        // 创建词法单元流
        antlr4::CommonTokenStream tokens(&lexer);
        
        // 创建语法分析器
        CSSParser parser(&tokens);
        parser.removeErrorListeners();
        parser.addErrorListener(errorListener_.get());
        
        // 解析
        auto tree = parser.stylesheet();
        
        // 如果有语法错误，返回空
        if (!errors_.empty()) {
            return nullptr;
        }
        
        // 访问解析树并构建AST
        auto ast = visitor_->visit(tree);
        
        // 临时返回一个样式块节点
        auto styleNode = std::make_shared<StyleBlockNode>();
        // TODO: 填充样式内容
        
        return styleNode;
        
    } catch (const std::exception& e) {
        errors_.push_back(std::string("CSS编译错误: ") + e.what());
        return nullptr;
    }
}

std::shared_ptr<ASTNode> CSSCompiler::parseFile(const std::string& filePath) {
    // TODO: 实现文件解析
    return nullptr;
}

bool CSSCompiler::validate(const std::string& code) {
    auto ast = compile(code);
    return ast != nullptr && errors_.empty();
}

} // namespace CHTL