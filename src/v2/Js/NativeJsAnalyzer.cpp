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
            // Parse JavaScript using the parser
            JsParser parser(js);
            auto parseResult = parser.parse();
            
            if (!parseResult.errors.empty()) {
                result.valid = false;
                result.errors = parseResult.errors;
            }
            
            if (parseResult.ast) {
                // Analyze the AST
                analyzeProgram(*parseResult.ast, result);
            }
            
            // Perform additional lint checks
            performLintChecks(result);
            
        } catch (const std::exception& e) {
            result.valid = false;
            result.errors.push_back(std::string("Analysis error: ") + e.what());
        }
        
        return result;
    }
    
    void setOption(const std::string& name, bool value) {
        options_[name] = value;
    }
    
private:
    std::map<std::string, bool> options_;
    
    void analyzeProgram(const JsProgram& program, JsAnalysisResult& result) {
        // Simplified analysis - just count basic elements
        for (const auto& stmt : program.body) {
            analyzeStatement(stmt.get(), result);
        }
        
        // Check complexity
        analyzeComplexity(program, result);
    }
    
    void analyzeStatement(const JsStatement* stmt, JsAnalysisResult& result) {
        if (!stmt) return;
        
        switch (stmt->type) {
            case JsNodeType::VAR_DECLARATION:
                analyzeVariableDeclaration(static_cast<const JsVariableDeclaration*>(stmt), result);
                break;
            case JsNodeType::FUNCTION_DECLARATION:
                // TODO: Need proper AST structure for function declarations
                result.functionCount++;
                result.features.hasAsyncAwait = true; // Simplified assumption
                break;
            case JsNodeType::FOR_STMT:
            case JsNodeType::WHILE_STMT:
            case JsNodeType::DO_WHILE_STMT:
                result.features.hasLoops = true;
                break;
            case JsNodeType::TRY_STMT:
                result.features.hasErrorHandling = true;
                break;
            case JsNodeType::IMPORT_DECLARATION:
            case JsNodeType::EXPORT_DECLARATION:
                result.features.hasModules = true;
                break;
            default:
                break;
        }
    }
    
    void analyzeVariableDeclaration(const JsVariableDeclaration* decl, JsAnalysisResult& result) {
        if (!decl) return;
        
        for (const auto& [name, init] : decl->declarations) {
            JsAnalysisResult::Variable var;
            var.name = name;
            var.type = decl->kind;
            var.line = 0; // Line info not available in simplified parser
            result.variables.push_back(var);
        }
    }
    
    void analyzeFunctionDeclaration(const JsFunction* func, JsAnalysisResult& result) {
        if (!func) return;
        
        JsAnalysisResult::Function fn;
        fn.name = func->name ? *func->name : "<anonymous>";
        fn.isAsync = func->isAsync;
        fn.isArrow = false; // Arrow functions not properly supported yet
        fn.line = 0; // Line info not available in simplified parser
        
        result.functions.push_back(fn);
        result.functionCount++;
        
        if (func->isAsync) {
            result.features.hasAsyncAwait = true;
        }
        if (func->isGenerator) {
            result.features.hasGenerators = true;
        }
    }
    
    void analyzeComplexity(const JsProgram& program, JsAnalysisResult& result) {
        // Basic complexity analysis
        int complexity = calculateCyclomaticComplexity(program);
        if (complexity > 10) {
            result.warnings.push_back("High cyclomatic complexity: " + std::to_string(complexity));
        }
        
        int nesting = calculateMaxNestingDepth(program);
        if (nesting > 4) {
            result.warnings.push_back("Deep nesting detected: " + std::to_string(nesting) + " levels");
        }
    }
    
    int calculateCyclomaticComplexity(const JsProgram& program) {
        // Simplified: count decision points
        int complexity = 1; // Base complexity
        
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
                return 1;
            case JsNodeType::LOGICAL_EXPR:
                return 2; // && and || add complexity
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
        // Simplified nesting calculation
        if (!stmt) return currentDepth;
        
        switch (stmt->type) {
            case JsNodeType::BLOCK_STMT:
            case JsNodeType::IF_STMT:
            case JsNodeType::WHILE_STMT:
            case JsNodeType::FOR_STMT:
            case JsNodeType::TRY_STMT:
                return currentDepth + 1;
            default:
                return currentDepth;
        }
    }
    
    bool hasGlobalVariables(const JsAnalysisResult& result) {
        // Simplified: assume variables at top level are global
        return !result.variables.empty();
    }
    
    void checkDuplicateDeclarations(JsAnalysisResult& result) {
        std::set<std::string> seenVars;
        for (const auto& var : result.variables) {
            if (!seenVars.insert(var.name).second) {
                result.warnings.push_back("Duplicate variable declaration: " + var.name);
            }
        }
        
        std::set<std::string> seenFuncs;
        for (const auto& func : result.functions) {
            if (!seenFuncs.insert(func.name).second) {
                result.warnings.push_back("Duplicate function declaration: " + func.name);
            }
        }
    }
    
    void checkUnusedVariables(JsAnalysisResult& result) {
        // Simplified: just warn about variables that start with _
        for (const auto& var : result.variables) {
            if (!var.name.empty() && var.name[0] == '_') {
                result.warnings.push_back("Variable '" + var.name + "' starts with underscore (possibly unused)");
            }
        }
    }
    
    void performLintChecks(JsAnalysisResult& result) {
        // Basic lint checks
        checkDuplicateDeclarations(result);
        checkUnusedVariables(result);
        
        // Check for global variables
        if (hasGlobalVariables(result)) {
            result.warnings.push_back("Global variables detected");
        }
        
        // Add basic feature warnings
        if (!result.features.hasConsistentSemicolons) {
            result.warnings.push_back("Inconsistent semicolon usage");
        }
    }
};

// Public interface implementation
NativeJsAnalyzer::NativeJsAnalyzer() : impl_(std::make_unique<Impl>()) {}
NativeJsAnalyzer::~NativeJsAnalyzer() = default;

JsAnalysisResult NativeJsAnalyzer::analyze(const std::string& js) {
    return impl_->analyze(js);
}

void NativeJsAnalyzer::setOption(const std::string& name, bool value) {
    impl_->setOption(name, value);
}

} // namespace chtl::v2::js