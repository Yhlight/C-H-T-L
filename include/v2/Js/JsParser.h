#pragma once

#include "v2/Js/JsTokenizer.h"
#include <memory>
#include <variant>
#include <map>
#include <optional>

namespace chtl::v2::js {

// 前向声明
struct JsNode;
struct JsExpression;
struct JsStatement;
struct JsDeclaration;

/**
 * JavaScript AST 节点类型
 */
enum class JsNodeType {
    // 表达式
    LITERAL,              // 字面量
    IDENTIFIER,           // 标识符
    BINARY_EXPR,          // 二元表达式
    UNARY_EXPR,           // 一元表达式
    ASSIGNMENT_EXPR,      // 赋值表达式
    UPDATE_EXPR,          // 更新表达式 (++/--)
    LOGICAL_EXPR,         // 逻辑表达式
    CONDITIONAL_EXPR,     // 条件表达式 (?:)
    CALL_EXPR,            // 函数调用
    NEW_EXPR,             // new 表达式
    MEMBER_EXPR,          // 成员访问
    ARRAY_EXPR,           // 数组字面量
    OBJECT_EXPR,          // 对象字面量
    FUNCTION_EXPR,        // 函数表达式
    ARROW_FUNCTION_EXPR,  // 箭头函数
    CLASS_EXPR,           // 类表达式
    THIS_EXPR,            // this
    TEMPLATE_LITERAL,     // 模板字符串
    SEQUENCE_EXPR,        // 逗号表达式
    
    // 语句
    BLOCK_STMT,           // 块语句
    EXPRESSION_STMT,      // 表达式语句
    IF_STMT,              // if 语句
    SWITCH_STMT,          // switch 语句
    FOR_STMT,             // for 循环
    FOR_IN_STMT,          // for...in 循环
    FOR_OF_STMT,          // for...of 循环
    WHILE_STMT,           // while 循环
    DO_WHILE_STMT,        // do...while 循环
    BREAK_STMT,           // break 语句
    CONTINUE_STMT,        // continue 语句
    RETURN_STMT,          // return 语句
    THROW_STMT,           // throw 语句
    TRY_STMT,             // try 语句
    
    // 声明
    VAR_DECLARATION,      // var 声明
    FUNCTION_DECLARATION, // 函数声明
    CLASS_DECLARATION,    // 类声明
    
    // 模块
    IMPORT_DECLARATION,   // import 声明
    EXPORT_DECLARATION,   // export 声明
    
    // 程序
    PROGRAM               // 程序根节点
};

/**
 * JavaScript 字面量值
 */
using JsLiteralValue = std::variant<
    std::monostate,       // null/undefined
    bool,                 // boolean
    double,               // number
    std::string           // string
>;

/**
 * JavaScript AST 基础节点
 */
struct JsNode {
    JsNodeType type;
    int line;
    int column;
    
    JsNode(JsNodeType t, int l = 0, int c = 0) 
        : type(t), line(l), column(c) {}
    virtual ~JsNode() = default;
};

/**
 * JavaScript 表达式节点
 */
struct JsExpression : JsNode {
    using JsNode::JsNode;
};

/**
 * JavaScript 语句节点
 */
struct JsStatement : JsNode {
    using JsNode::JsNode;
};

/**
 * JavaScript 声明节点
 */
struct JsDeclaration : JsStatement {
    using JsStatement::JsStatement;
};

/**
 * 具体的 AST 节点类型
 */

// 字面量
struct JsLiteral : JsExpression {
    JsLiteralValue value;
    std::string raw;  // 原始文本
    
    JsLiteral() : JsExpression(JsNodeType::LITERAL) {}
};

// 标识符
struct JsIdentifier : JsExpression {
    std::string name;
    
    JsIdentifier() : JsExpression(JsNodeType::IDENTIFIER) {}
    explicit JsIdentifier(const std::string& n) 
        : JsExpression(JsNodeType::IDENTIFIER), name(n) {}
};

// 二元表达式
struct JsBinaryExpression : JsExpression {
    std::string operator_;
    std::unique_ptr<JsExpression> left;
    std::unique_ptr<JsExpression> right;
    
    JsBinaryExpression() : JsExpression(JsNodeType::BINARY_EXPR) {}
};

// 函数声明/表达式
struct JsFunction : JsNode {
    std::optional<std::string> name;
    std::vector<std::string> parameters;
    std::unique_ptr<JsStatement> body;
    bool isAsync = false;
    bool isGenerator = false;
    
    JsFunction(JsNodeType type) : JsNode(type) {}
};

// 变量声明
struct JsVariableDeclaration : JsDeclaration {
    std::string kind;  // "var", "let", "const"
    std::vector<std::pair<std::string, std::unique_ptr<JsExpression>>> declarations;
    
    JsVariableDeclaration() : JsDeclaration(JsNodeType::VAR_DECLARATION) {}
};

// 表达式语句
struct JsExpressionStatement : JsStatement {
    std::unique_ptr<JsExpression> expression;
    
    JsExpressionStatement() : JsStatement(JsNodeType::EXPRESSION_STMT) {}
};

// 程序节点
struct JsProgram : JsNode {
    std::vector<std::unique_ptr<JsStatement>> body;
    
    JsProgram() : JsNode(JsNodeType::PROGRAM) {}
};

/**
 * JavaScript 解析结果
 */
struct JsParseResult {
    std::unique_ptr<JsProgram> ast;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

/**
 * JavaScript 解析器
 */
class JsParser {
public:
    explicit JsParser(const std::string& input);
    
    /**
     * 解析 JavaScript 代码
     */
    JsParseResult parse();
    
    /**
     * 解析单个表达式
     */
    std::unique_ptr<JsExpression> parseExpression();
    
    /**
     * 解析单个语句
     */
    std::unique_ptr<JsStatement> parseStatement();
    
private:
    // 主要解析方法
    std::unique_ptr<JsProgram> parseProgram();
    
    // 声明解析
    std::unique_ptr<JsStatement> parseDeclaration();
    std::unique_ptr<JsVariableDeclaration> parseVariableDeclaration();
    std::unique_ptr<JsStatement> parseFunctionDeclaration();
    std::unique_ptr<JsStatement> parseClassDeclaration();
    
    // 语句解析
    std::unique_ptr<JsStatement> parseBlockStatement();
    std::unique_ptr<JsStatement> parseExpressionStatement();
    std::unique_ptr<JsStatement> parseIfStatement();
    std::unique_ptr<JsStatement> parseWhileStatement();
    std::unique_ptr<JsStatement> parseForStatement();
    std::unique_ptr<JsStatement> parseReturnStatement();
    std::unique_ptr<JsStatement> parseBreakStatement();
    std::unique_ptr<JsStatement> parseContinueStatement();
    std::unique_ptr<JsStatement> parseThrowStatement();
    std::unique_ptr<JsStatement> parseTryStatement();
    
    // 表达式解析（优先级递减）
    std::unique_ptr<JsExpression> parseAssignmentExpression();
    std::unique_ptr<JsExpression> parseConditionalExpression();
    std::unique_ptr<JsExpression> parseLogicalOrExpression();
    std::unique_ptr<JsExpression> parseLogicalAndExpression();
    std::unique_ptr<JsExpression> parseBitwiseOrExpression();
    std::unique_ptr<JsExpression> parseBitwiseXorExpression();
    std::unique_ptr<JsExpression> parseBitwiseAndExpression();
    std::unique_ptr<JsExpression> parseEqualityExpression();
    std::unique_ptr<JsExpression> parseRelationalExpression();
    std::unique_ptr<JsExpression> parseShiftExpression();
    std::unique_ptr<JsExpression> parseAdditiveExpression();
    std::unique_ptr<JsExpression> parseMultiplicativeExpression();
    std::unique_ptr<JsExpression> parseExponentiationExpression();
    std::unique_ptr<JsExpression> parseUnaryExpression();
    std::unique_ptr<JsExpression> parsePostfixExpression();
    std::unique_ptr<JsExpression> parseCallExpression();
    std::unique_ptr<JsExpression> parseMemberExpression();
    std::unique_ptr<JsExpression> parseNewExpression();
    std::unique_ptr<JsExpression> parsePrimaryExpression();
    std::unique_ptr<JsExpression> parseObjectLiteral();
    std::unique_ptr<JsExpression> parseArrayLiteral();
    std::unique_ptr<JsExpression> parseFunctionExpression();
    std::unique_ptr<JsExpression> parseArrowFunction();
    
    // 辅助方法
    JsToken advance();
    bool check(JsTokenType type);
    bool match(JsTokenType type);
    bool match(std::initializer_list<JsTokenType> types);
    JsToken consume(JsTokenType type, const std::string& message);
    bool isAtEnd();
    void synchronize();
    
    void error(const std::string& message);
    void warning(const std::string& message);
    
    // 自动分号插入
    bool canInsertSemicolon();
    void consumeSemicolon();
    
private:
    JsTokenizer tokenizer_;
    JsToken current_;
    JsToken previous_;
    std::vector<std::string> errors_;
    std::vector<std::string> warnings_;
};

} // namespace chtl::v2::js