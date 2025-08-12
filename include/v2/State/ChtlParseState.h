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
    STYLE_CONTENT,      // 样式内容（整块传递）
    SCRIPT_CONTENT,     // 脚本内容（交给扫描器）
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
 * 获取状态名称（用于调试）
 */
const char* getStateName(ChtlParseState state);

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