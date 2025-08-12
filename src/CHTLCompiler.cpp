#include "CHTLCompiler.h"
#include "CHTLLexer.h"
#include "CHTLParser.h"
#include "CHTLBaseVisitor.h"
#include <sstream>

namespace CHTL {

// 错误监听器实现
class CHTLCompiler::ErrorListener : public antlr4::BaseErrorListener {
public:
    ErrorListener(std::vector<std::string>& errors) : errors_(errors) {}
    
    void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol,
                    size_t line, size_t charPositionInLine,
                    const std::string& msg, std::exception_ptr e) override {
        std::stringstream ss;
        ss << "语法错误 [" << line << ":" << charPositionInLine << "] " << msg;
        errors_.push_back(ss.str());
    }
    
private:
    std::vector<std::string>& errors_;
};

// CHTL访问者实现
class CHTLCompiler::CHTLVisitorImpl : public CHTLBaseVisitor {
public:
    CHTLVisitorImpl(SymbolTable* symbolTable) : symbolTable_(symbolTable) {}
    
    // TODO: 实现各个visit方法
    // 这里只是一个框架，实际实现需要根据ANTLR生成的代码来完成
    
private:
    SymbolTable* symbolTable_;
    std::shared_ptr<ASTNode> currentNode_;
};

CHTLCompiler::CHTLCompiler(SymbolTable* symbolTable) 
    : symbolTable_(symbolTable) {
    visitor_ = std::make_unique<CHTLVisitorImpl>(symbolTable);
    errorListener_ = std::make_unique<ErrorListener>(errors_);
}

CHTLCompiler::~CHTLCompiler() = default;

std::shared_ptr<ASTNode> CHTLCompiler::compile(const std::string& code) {
    try {
        // 创建输入流
        antlr4::ANTLRInputStream input(code);
        
        // 创建词法分析器
        CHTLLexer lexer(&input);
        lexer.removeErrorListeners();
        lexer.addErrorListener(errorListener_.get());
        
        // 创建词法单元流
        antlr4::CommonTokenStream tokens(&lexer);
        
        // 创建语法分析器
        CHTLParser parser(&tokens);
        parser.removeErrorListeners();
        parser.addErrorListener(errorListener_.get());
        
        // 解析
        auto tree = parser.program();
        
        // 如果有语法错误，返回空
        if (!errors_.empty()) {
            return nullptr;
        }
        
        // 访问解析树并构建AST
        auto ast = visitor_->visit(tree);
        
        // TODO: 转换ANTLR的Any类型到我们的ASTNode
        // 这需要根据实际生成的代码来实现
        
        // 临时返回一个空节点
        return std::make_shared<ElementNode>("program");
        
    } catch (const std::exception& e) {
        errors_.push_back(std::string("编译错误: ") + e.what());
        return nullptr;
    }
}

std::shared_ptr<ASTNode> CHTLCompiler::parseFile(const std::string& filePath) {
    // TODO: 实现文件解析
    return nullptr;
}

} // namespace CHTL