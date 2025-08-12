#include "v2/Js/NativeJsAnalyzer.h"
#include "v2/Js/JsParser.h"
#include <set>
#include <map>
#include <algorithm>

namespace chtl::v2::js {

class NativeJsAnalyzer::Impl {
public:
    JsAnalysisResult analyze(const std::string& js) {
        JsAnalysisResult result;
        result.valid = true;
        
        try {
            // 使用新的 JavaScript 解析器
            JsParser parser(js);
            auto parseResult = parser.parse();
            
            if (!parseResult.errors.empty()) {
                result.valid = false;
                result.errors = parseResult.errors;
            }
            
            result.warnings = parseResult.warnings;
            
            // 分析 AST
            if (parseResult.ast) {
                analyzeProgram(*parseResult.ast, result);
            }
            
            // 执行额外的检查
            performLintChecks(result);
            
        } catch (const std::exception& e) {
            result.valid = false;
            result.errors.push_back("JS parse error: " + std::string(e.what()));
        }
        
        return result;
    }
    
private:
    /**
     * 分析程序 AST
     */
    void analyzeProgram(const JsProgram& program, JsAnalysisResult& result) {
        // 遍历所有语句
        for (const auto& stmt : program.body) {
            analyzeStatement(stmt.get(), result);
        }
        
        // 分析复杂度
        analyzeComplexity(program, result);
        
        // 检查最佳实践
        checkBestPractices(result);
    }
    
    /**
     * 分析语句
     */
    void analyzeStatement(const JsStatement* stmt, JsAnalysisResult& result) {
        if (!stmt) return;
        
        switch (stmt->type) {
            case JsNodeType::VAR_DECLARATION: {
                auto* varDecl = static_cast<const JsVariableDeclaration*>(stmt);
                analyzeVariableDeclaration(varDecl, result);
                break;
            }
            
            case JsNodeType::FUNCTION_DECLARATION: {
                auto* funcDecl = static_cast<const JsFunction*>(stmt);
                analyzeFunctionDeclaration(funcDecl, result);
                break;
            }
            
            case JsNodeType::CLASS_DECLARATION: {
                result.features.hasClasses = true;
                result.classCount++;
                break;
            }
            
            case JsNodeType::IF_STMT:
            case JsNodeType::SWITCH_STMT:
            case JsNodeType::FOR_STMT:
            case JsNodeType::FOR_IN_STMT:
            case JsNodeType::FOR_OF_STMT:
            case JsNodeType::WHILE_STMT:
            case JsNodeType::DO_WHILE_STMT: {
                result.features.hasLoops = true;
                break;
            }
            
            case JsNodeType::TRY_STMT: {
                result.features.hasErrorHandling = true;
                break;
            }
            
            case JsNodeType::IMPORT_DECLARATION:
            case JsNodeType::EXPORT_DECLARATION: {
                result.features.hasModules = true;
                break;
            }
            
            case JsNodeType::BLOCK_STMT: {
                // 递归分析块内的语句
                auto* block = static_cast<const JsStatement*>(stmt);
                // 这里需要具体的块语句实现
                break;
            }
            
            case JsNodeType::EXPRESSION_STMT: {
                // 分析表达式语句
                // 这里需要具体的表达式语句实现
                break;
            }
            
            default:
                break;
        }
    }
    
    /**
     * 分析变量声明
     */
    void analyzeVariableDeclaration(const JsVariableDeclaration* decl, JsAnalysisResult& result) {
        for (const auto& [name, init] : decl->declarations) {
            result.variables.push_back(name);
            
            // 检查变量命名
            if (!isValidVariableName(name)) {
                result.warnings.push_back("Non-conventional variable name: " + name);
            }
            
            // 检查未初始化的 const
            if (decl->kind == "const" && !init) {
                result.errors.push_back("Missing initializer in const declaration: " + name);
            }
        }
        
        // 警告使用 var
        if (decl->kind == "var") {
            result.warnings.push_back("Consider using 'let' or 'const' instead of 'var'");
        }
    }
    
    /**
     * 分析函数声明
     */
    void analyzeFunctionDeclaration(const JsFunction* func, JsAnalysisResult& result) {
        result.functionCount++;
        
        if (func->name) {
            result.functions.push_back(*func->name);
            
            // 检查函数命名
            if (!isValidFunctionName(*func->name)) {
                result.warnings.push_back("Non-conventional function name: " + *func->name);
            }
        }
        
        // 检查异步函数
        if (func->isAsync) {
            result.features.hasAsyncAwait = true;
        }
        
        // 检查生成器函数
        if (func->isGenerator) {
            result.features.hasGenerators = true;
        }
        
        // 检查参数数量
        if (func->parameters.size() > 5) {
            result.warnings.push_back("Function has too many parameters (" + 
                                    std::to_string(func->parameters.size()) + ")");
        }
    }
    
    /**
     * 分析复杂度
     */
    void analyzeComplexity(const JsProgram& program, JsAnalysisResult& result) {
        // 计算圈复杂度
        int complexity = calculateCyclomaticComplexity(program);
        
        if (complexity > 10) {
            result.warnings.push_back("High cyclomatic complexity: " + 
                                    std::to_string(complexity));
        }
        
        // 计算嵌套深度
        int maxNesting = calculateMaxNestingDepth(program);
        
        if (maxNesting > 4) {
            result.warnings.push_back("Deep nesting detected (depth: " + 
                                    std::to_string(maxNesting) + ")");
        }
    }
    
    /**
     * 检查最佳实践
     */
    void checkBestPractices(JsAnalysisResult& result) {
        // 检查全局变量
        if (hasGlobalVariables(result)) {
            result.warnings.push_back("Global variables detected - consider using modules");
        }
        
        // 检查重复声明
        checkDuplicateDeclarations(result);
        
        // 检查未使用的变量
        checkUnusedVariables(result);
    }
    
    /**
     * 执行代码检查
     */
    void performLintChecks(JsAnalysisResult& result) {
        // 检查分号使用
        if (!result.features.hasConsistentSemicolons) {
            result.warnings.push_back("Inconsistent semicolon usage");
        }
        
        // 检查缩进
        if (!result.features.hasConsistentIndentation) {
            result.warnings.push_back("Inconsistent indentation");
        }
        
        // 检查引号使用
        if (result.features.hasMixedQuotes) {
            result.warnings.push_back("Mixed quote styles - use consistent quotes");
        }
    }
    
    /**
     * 辅助方法
     */
    
    bool isValidVariableName(const std::string& name) {
        // 检查驼峰命名或下划线命名
        return !name.empty() && 
               (std::islower(name[0]) || name[0] == '_' || name[0] == '$');
    }
    
    bool isValidFunctionName(const std::string& name) {
        // 函数名应该是动词或动词短语
        return !name.empty() && std::islower(name[0]);
    }
    
    int calculateCyclomaticComplexity(const JsProgram& program) {
        // 简化的圈复杂度计算
        int complexity = 1;
        
        // 每个决策点增加复杂度
        for (const auto& stmt : program.body) {
            complexity += countDecisionPoints(stmt.get());
        }
        
        return complexity;
    }
    
    int countDecisionPoints(const JsStatement* stmt) {
        if (!stmt) return 0;
        
        switch (stmt->type) {
            case JsNodeType::IF_STMT:
            case JsNodeType::WHILE_STMT:
            case JsNodeType::FOR_STMT:
            case JsNodeType::FOR_IN_STMT:
            case JsNodeType::FOR_OF_STMT:
            case JsNodeType::DO_WHILE_STMT:
                return 1;
                
            case JsNodeType::SWITCH_STMT:
                // switch 语句的每个 case 都是一个决策点
                return 2; // 简化计算
                
            case JsNodeType::TRY_STMT:
                return 1; // catch 块
                
            default:
                return 0;
        }
    }
    
    int calculateMaxNestingDepth(const JsProgram& program) {
        int maxDepth = 0;
        
        for (const auto& stmt : program.body) {
            maxDepth = std::max(maxDepth, calculateNestingDepth(stmt.get(), 0));
        }
        
        return maxDepth;
    }
    
    int calculateNestingDepth(const JsStatement* stmt, int currentDepth) {
        if (!stmt) return currentDepth;
        
        // 增加嵌套深度的语句
        switch (stmt->type) {
            case JsNodeType::IF_STMT:
            case JsNodeType::WHILE_STMT:
            case JsNodeType::FOR_STMT:
            case JsNodeType::FOR_IN_STMT:
            case JsNodeType::FOR_OF_STMT:
            case JsNodeType::DO_WHILE_STMT:
            case JsNodeType::SWITCH_STMT:
            case JsNodeType::TRY_STMT:
            case JsNodeType::BLOCK_STMT:
                return currentDepth + 1;
                
            default:
                return currentDepth;
        }
    }
    
    bool hasGlobalVariables(const JsAnalysisResult& result) {
        // 简化检查：如果没有使用模块，所有顶级变量都是全局的
        return !result.features.hasModules && !result.variables.empty();
    }
    
    void checkDuplicateDeclarations(JsAnalysisResult& result) {
        std::set<std::string> seen;
        
        for (const auto& var : result.variables) {
            if (!seen.insert(var).second) {
                result.warnings.push_back("Duplicate variable declaration: " + var);
            }
        }
        
        for (const auto& func : result.functions) {
            if (!seen.insert(func).second) {
                result.warnings.push_back("Duplicate function declaration: " + func);
            }
        }
    }
    
    void checkUnusedVariables(JsAnalysisResult& result) {
        // 这需要更复杂的分析，包括变量使用跟踪
        // 这里只是一个简化的实现
        for (const auto& var : result.variables) {
            if (var.starts_with("_unused")) {
                result.warnings.push_back("Potentially unused variable: " + var);
            }
        }
    }
};

NativeJsAnalyzer::NativeJsAnalyzer() 
    : impl_(std::make_unique<Impl>()) {
}

NativeJsAnalyzer::~NativeJsAnalyzer() = default;

JsAnalysisResult NativeJsAnalyzer::analyze(const std::string& js) {
    return impl_->analyze(js);
}

} // namespace chtl::v2::js