#pragma once

namespace chtl::v2 {

/**
 * CHTL 解析状态
 * 定义了编译器在不同上下文中的状态
 */
enum class ChtlParseState {
    // ===== 顶层状态 =====
    TOP_LEVEL,              // 文件顶层，可以有声明或 HTML 片段
    
    // ===== 声明状态 =====
    TEMPLATE_DECLARATION,   // [Template] 声明内部
    CUSTOM_DECLARATION,     // [Custom] 声明内部  
    IMPORT_DECLARATION,     // [Import] 声明
    CONFIG_DECLARATION,     // [Configuration] 声明
    ORIGIN_DECLARATION,     // [Origin] 声明
    
    // ===== 元素状态 =====
    ELEMENT_TAG,            // 解析元素标签和属性
    ELEMENT_CONTENT,        // 元素内容
    ELEMENT_ATTRIBUTES,     // 元素属性
    
    // ===== 样式状态 =====
    STYLE_BLOCK,            // style { } 块
    STYLE_SELECTOR,         // CSS 选择器  
    STYLE_PROPERTY_NAME,    // CSS 属性名
    STYLE_PROPERTY_VALUE,   // CSS 属性值
    STYLE_TEXT_CONTENT,     // style { text { } } 中的文本
    
    // ===== 脚本状态 =====
    SCRIPT_BLOCK,           // script { } 块
    SCRIPT_CONTENT,         // JavaScript 内容
    
    // ===== 文本状态 =====
    TEXT_BLOCK,             // text { } 块
    TEXT_CONTENT,           // 文本内容
    
    // ===== 引用状态 =====
    ELEMENT_REFERENCE,      // @Element 引用
    STYLE_REFERENCE,        // @Style 引用
    VAR_REFERENCE,          // @Var 引用
    
    // ===== 表达式状态 =====
    EXPRESSION,             // 参数表达式
    STRING_LITERAL,         // 字符串字面量
    TEMPLATE_PARAMETER,     // 模板参数
    
    // ===== CHTL-JS 状态 =====
    CHTL_JS_EXPRESSION,     // {{ }} 内的表达式
    CHTL_JS_SELECTOR,       // {{#id}} 或 {{&}}
    
    // ===== 操作状态 =====
    INHERIT_OPERATION,      // inherit 操作
    DELETE_OPERATION,       // delete 操作  
    INSERT_OPERATION,       // insert 操作
};

/**
 * 获取状态名称（用于调试）
 */
const char* getStateName(ChtlParseState state);

/**
 * 判断是否是声明状态
 */
bool isDeclarationState(ChtlParseState state);

/**
 * 判断是否是引用状态
 */
bool isReferenceState(ChtlParseState state);

/**
 * 判断是否允许嵌套元素
 */
bool allowsNestedElements(ChtlParseState state);

} // namespace chtl::v2