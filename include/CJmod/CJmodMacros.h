#ifndef CHTL_CJMOD_MACROS_H
#define CHTL_CJMOD_MACROS_H

#include "CJmodBuilder.h"

// 简化模块创建的宏
#define CJMOD_BEGIN(name, version) \
    auto module = cjmod::createModule(name, version)

#define CJMOD_DESC(description) \
    .description(description)

// 语法定义宏
#define CJMOD_SYNTAX(pattern, replacement) \
    .syntax(pattern, replacement)

#define CJMOD_SYNTAX_FN(pattern, lambda) \
    .syntax(pattern, lambda)

#define CJMOD_SYNTAX_WHEN(pattern, lambda, condition) \
    .syntaxWhen(pattern, lambda, condition)

// 方法定义宏
#define CJMOD_METHOD(target, name, impl) \
    .method(target, name, impl)

#define CJMOD_ASYNC_METHOD(target, name, impl) \
    .asyncMethod(target, name, impl)

// 运行时代码宏
#define CJMOD_RUNTIME(code) \
    .runtime(code)

#define CJMOD_RUNTIME_FILE(file) \
    .runtimeFile(file)

// 结束并注册
#define CJMOD_END() \
    .build(); \
    CJmodProcessor::getInstance().registerModule(std::move(module))

// 一体化宏 - 最简单的方式
#define DEFINE_CJMOD(name, version, body) \
    []() { \
        CJMOD_BEGIN(name, version) \
        body \
        CJMOD_END(); \
    }()

// 快速语法定义
#define SYNTAX_SIMPLE(from, to) \
    CJMOD_SYNTAX(from, to)

#define SYNTAX_TRANSFORM(pattern) \
    CJMOD_SYNTAX_FN(pattern, [](const std::smatch& m)

#define SYNTAX_TEMPLATE(pattern, template) \
    CJMOD_SYNTAX_FN(pattern, cjmod::transforms::template_(template))

// 快速方法定义
#define METHOD_SIMPLE(target, name, code) \
    CJMOD_METHOD(target, name, "function() { " code " }")

#define METHOD_WITH_PARAMS(target, name, params, code) \
    CJMOD_METHOD(target, name, "function(" params ") { " code " }")

#define ASYNC_METHOD(target, name, params, code) \
    CJMOD_ASYNC_METHOD(target, name, "async function(" params ") { " code " }")

// 预定义的常用语法模板
namespace cjmod {
namespace macros {

// 创建响应式语法的宏
inline void defineReactiveSyntax(CJmodBuilder& builder) {
    builder
        .syntax(R"((\w+)\s*:=\s*(.+);)", "const $1 = reactive($2);")
        .syntax(R"((\w+)\s*=>\s*(.+);)", "const $1 = computed(() => $2);")
        .syntax(R"(watch\s+(\w+)\s*\{)", "watch($1, () => {");
}

// 创建动画语法的宏
inline void defineAnimationSyntax(CJmodBuilder& builder) {
    builder
        .syntax(R"((\w+)\s*~>\s*(\w+)\()", "$1.animate().$2(")
        .syntax(R"((\w+)\s*~~\s*\{)", "$1.animateParallel({")
        .syntax(R"(delay\s*\((\d+)\))", "await new Promise(r => setTimeout(r, $1))");
}

// 创建调试语法的宏
inline void defineDebugSyntax(CJmodBuilder& builder) {
    builder
        .syntax(R"(log\s+(.+);)", "console.log($1);")
        .syntax(R"(assert\s+([^,]+),\s*(.+);)", "console.assert($1, $2);")
        .syntax(R"(debug\s+(\w+);)", "console.dir($1);");
}

} // namespace macros
} // namespace cjmod

#endif // CHTL_CJMOD_MACROS_H