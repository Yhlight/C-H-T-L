#pragma once

namespace chtl::v2 {

/**
 * 解析上下文
 * 区分全局（定义）和局部（引用）
 */
enum class ChtlContext {
    GLOBAL,    // 全局上下文（顶层）- 声明是定义
    LOCAL      // 局部上下文（块内）- 声明是引用
};

/**
 * CHTL 解析状态（简化版）
 * 基于"全局定义，局部引用"的原则
 */
enum class ChtlParseState {
    // ===== 基础状态 =====
    INITIAL,            // 初始状态（等同于全局）
    
    // ===== 内容状态 =====
    ELEMENT,            // 元素（包括标签、属性、内容）
    STYLE,              // 样式块 style { }
    SCRIPT,             // 脚本块 script { }
    TEXT,               // 文本块 text { }
    
    // ===== 块内容状态 =====
    ELEMENT_CONTENT,    // 元素内容 { ... }
    STYLE_CONTENT,      // 样式内容（整块传递给 CSS 分析器）
    SCRIPT_CONTENT,     // 脚本内容（整块传递给 JS 分析器）
    TEXT_CONTENT,       // 文本内容
    
    // ===== 声明/引用状态 =====
    DECLARATION,        // [] 块（全局是定义，局部是引用）
    REFERENCE,          // @ 引用（总是引用）
    
    // ===== 特殊状态 =====
    STRING_LITERAL,     // 字符串字面量 "..."
    EXPRESSION,         // 表达式 (...)
    CHTL_JS,           // {{ }} 内的 CHTL-JS 表达式
};

/**
 * CHTL 子状态
 * 用于处理特定语法结构的细节
 */
enum class ChtlSubState {
    NONE,               // 无子状态
    
    // ===== 元素子状态 =====
    ELEMENT_TAG,        // 解析标签名
    ELEMENT_ID,         // 解析 #id
    ELEMENT_CLASS,      // 解析 .class
    ELEMENT_ATTR_NAME,  // 解析属性名
    ELEMENT_ATTR_VALUE, // 解析属性值
    
    // ===== CSS 选择器子状态（局部样式块） =====
    CSS_SELECTOR,       // 选择器（.class, #id, tag）
    CSS_PSEUDO,         // 伪类/伪元素 (:hover, ::before)
    CSS_COMBINATOR,     // 组合器 (>, +, ~)
    
    // ===== 声明子状态 =====
    DECLARATION_TYPE,   // [Template], [Custom] 等
    DECLARATION_NAME,   // 名称部分
    DECLARATION_PARAMS, // 参数列表
    
    // ===== 引用子状态 =====
    REFERENCE_TYPE,     // @Element, @Style 等
    REFERENCE_NAME,     // 引用名称
    REFERENCE_ARGS,     // 引用参数
    
    // ===== 表达式子状态 =====
    EXPR_LITERAL,       // 字面量
    EXPR_VARIABLE,      // 变量引用
    EXPR_FUNCTION,      // 函数调用
};

/**
 * 获取状态名称（用于调试）
 */
const char* getStateName(ChtlParseState state);

/**
 * 获取子状态名称（用于调试）
 */
const char* getSubStateName(ChtlSubState subState);

/**
 * 获取上下文名称（用于调试）
 */
const char* getContextName(ChtlContext context);

/**
 * 判断状态是否需要局部上下文
 */
bool requiresLocalContext(ChtlParseState state);

/**
 * 判断状态是否是内容状态
 */
bool isContentState(ChtlParseState state);

/**
 * 判断状态是否允许嵌套元素
 */
bool allowsNestedElements(ChtlParseState state);

} // namespace chtl::v2