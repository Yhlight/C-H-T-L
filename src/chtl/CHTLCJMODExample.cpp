#include "CHTLCJMOD.h"
#include "CHTLGenerator.h"
#include "CHTLScript.h"
#include <iostream>
#include <filesystem>

using namespace chtl;
namespace fs = std::filesystem;

// 示例：自定义的CJMOD扩展 - 添加async/await语法支持
class AsyncAwaitExtension : public CJMODExtensionBase {
public:
    AsyncAwaitExtension()
        : CJMODExtensionBase("AsyncAwait", "1.0.0", "Adds async/await syntax support") {}
    
    std::string preprocess(const std::string& script) override {
        // 将async函数转换为标记
        std::regex asyncFunc(R"(async\s+function\s+(\w+))");
        std::string result = std::regex_replace(script, asyncFunc, "function $1 /* __async__ */");
        
        // 将async箭头函数转换
        std::regex asyncArrow(R"(async\s*\(([^)]*)\)\s*=>)");
        result = std::regex_replace(result, asyncArrow, "($1) => /* __async_arrow__ */");
        
        return result;
    }
    
    std::string transform(const std::string& script) override {
        std::string result = script;
        
        // 转换await表达式
        std::regex awaitExpr(R"(await\s+([^;]+);)");
        result = std::regex_replace(result, awaitExpr, 
            "yield $1; /* __await__ */");
        
        // 将async函数转换为生成器
        std::regex asyncMarker(R"(function\s+(\w+)\s*/\*\s*__async__\s*\*/)");
        result = std::regex_replace(result, asyncMarker, 
            "function* $1");
        
        return result;
    }
    
    void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {
        // 注册delay函数作为示例
        processor->registerFunction("delay", 
            [](const std::vector<std::string>& args) -> std::string {
                if (args.empty()) return "Promise.resolve()";
                return "new Promise(resolve => setTimeout(resolve, " + args[0] + "))";
            });
    }
};

// 示例：创建一个提供数学扩展的CJMOD
class MathExtension : public CJMODExtensionBase {
public:
    MathExtension()
        : CJMODExtensionBase("MathExt", "1.0.0", "Advanced math operations") {}
    
    void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {
        // 注册阶乘函数
        processor->registerFunction("factorial",
            [](const std::vector<std::string>& args) -> std::string {
                if (args.empty()) return "1";
                return "(function(n) { "
                       "let r = 1; "
                       "for(let i = 2; i <= n; i++) r *= i; "
                       "return r; "
                       "})(" + args[0] + ")";
            });
        
        // 注册斐波那契函数
        processor->registerFunction("fibonacci",
            [](const std::vector<std::string>& args) -> std::string {
                if (args.empty()) return "0";
                return "(function(n) { "
                       "if (n <= 1) return n; "
                       "let a = 0, b = 1; "
                       "for(let i = 2; i <= n; i++) { "
                       "  let t = a + b; a = b; b = t; "
                       "} "
                       "return b; "
                       "})(" + args[0] + ")";
            });
    }
};

// 示例：创建一个提供自定义语法的CJMOD
class PipelineExtension : public CJMODExtensionBase {
public:
    PipelineExtension()
        : CJMODExtensionBase("Pipeline", "1.0.0", "Adds pipeline operator support") {}
    
    std::string transform(const std::string& script) override {
        // 实现管道操作符 |>
        std::regex pipeline(R"(([^|]+)\s*\|>\s*([^|;]+))");
        std::smatch match;
        std::string result = script;
        
        while (std::regex_search(result, match, pipeline)) {
            std::string value = match[1];
            std::string func = match[2];
            
            // 去除空格
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            func.erase(0, func.find_first_not_of(" \t"));
            func.erase(func.find_last_not_of(" \t") + 1);
            
            // 转换为函数调用
            std::string replacement = func + "(" + value + ")";
            result = result.substr(0, match.position()) + 
                    replacement + 
                    result.substr(match.position() + match.length());
        }
        
        return result;
    }
    
    void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {
        // 注册语法转换器
        processor->registerTransformer(R"([^|]+\s*\|>\s*[^|;]+)",
            [this](const std::string& matched) -> std::string {
                return this->transform(matched);
            });
    }
};

// 创建示例CJMOD模块
void createExampleCJMOD() {
    // 创建AsyncAwait模块
    CJMODHelper::createExtensionTemplate(fs::current_path(), "AsyncAwait", "syntax");
    
    // 修改生成的源文件
    std::ofstream impl("AsyncAwait/src/AsyncAwait.cpp");
    impl << R"(#include "AsyncAwait.h"
#include <regex>

// Implementation of AsyncAwaitExtension
std::string AsyncAwaitExtension::preprocess(const std::string& script) {
    // Implementation as shown above
    return script;
}

std::string AsyncAwaitExtension::transform(const std::string& script) {
    // Implementation as shown above
    return script;
}

// Export factory function
CJMOD_EXTENSION_FACTORY(AsyncAwaitExtension)
)";
    impl.close();
}

int main() {
    // 创建示例CJMOD
    std::cout << "=== 创建示例CJMOD模块 ===" << std::endl;
    createExampleCJMOD();
    
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 创建CJMOD管理器
    auto cjmodManager = std::make_shared<CJMODManager>(context);
    
    // 创建脚本管理器并设置CJMOD管理器
    auto scriptManager = generator.getScriptManager();
    auto scriptProcessor = std::make_shared<ScriptProcessor>(*scriptManager);
    scriptProcessor->setCJMODManager(cjmodManager.get());
    
    // 示例1：注册并使用内存中的扩展
    std::cout << "\n=== 示例1：使用内存中的CJMOD扩展 ===" << std::endl;
    
    // 注册扩展工厂
    cjmodManager->registerExtensionFactory("AsyncAwait", 
        []() { return std::make_unique<AsyncAwaitExtension>(); });
    
    cjmodManager->registerExtensionFactory("MathExt",
        []() { return std::make_unique<MathExtension>(); });
    
    cjmodManager->registerExtensionFactory("Pipeline",
        []() { return std::make_unique<PipelineExtension>(); });
    
    // 创建并初始化扩展
    auto asyncExt = cjmodManager->createExtension("AsyncAwait");
    auto mathExt = cjmodManager->createExtension("MathExt");
    auto pipeExt = cjmodManager->createExtension("Pipeline");
    
    // 注册扩展函数
    mathExt->registerFunctions(scriptProcessor);
    pipeExt->registerFunctions(scriptProcessor);
    
    // 示例2：使用async/await语法
    std::cout << "\n=== 示例2：async/await语法 ===" << std::endl;
    
    generator.generateElement("div", {{"id", "async-demo"}});
    
    generator.beginScriptBlock();
    std::string asyncScript = R"(
        async function loadData() {
            console.log('Loading...');
            await delay(1000);
            console.log('Data loaded!');
            return { message: 'Hello from async!' };
        }
        
        async () => {
            const data = await loadData();
            {{#async-demo}}->textContent = data.message;
        }
    )";
    
    // 预处理和转换脚本
    std::string preprocessed = asyncExt->preprocess(asyncScript);
    std::string transformed = asyncExt->transform(preprocessed);
    
    generator.addScriptContent(transformed);
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例3：使用数学扩展
    std::cout << "\n=== 示例3：数学扩展函数 ===" << std::endl;
    
    generator.generateElement("div", {{"id", "math-demo"}});
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 使用CJMOD提供的数学函数
        const fact5 = factorial(5);
        const fib10 = fibonacci(10);
        
        {{#math-demo}}->innerHTML = `
            <p>5! = ${fact5}</p>
            <p>F(10) = ${fib10}</p>
        `;
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例4：使用管道操作符
    std::cout << "\n=== 示例4：管道操作符 ===" << std::endl;
    
    generator.generateElement("div", {{"id", "pipeline-demo"}});
    
    generator.beginScriptBlock();
    std::string pipelineScript = R"(
        // 定义一些函数
        const double = x => x * 2;
        const add10 = x => x + 10;
        const toString = x => x.toString();
        
        // 使用管道操作符
        const result = 5 |> double |> add10 |> toString;
        
        {{#pipeline-demo}}->textContent = 'Result: ' + result;
    )";
    
    // 转换管道语法
    std::string pipeTransformed = pipeExt->transform(pipelineScript);
    generator.addScriptContent(pipeTransformed);
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 示例5：构建和加载CJMOD文件
    std::cout << "\n=== 示例5：构建CJMOD文件 ===" << std::endl;
    
    CJMODBuilder builder(context);
    builder.setSourcePath(fs::current_path());
    builder.setOutputPath(fs::current_path());
    
    // 构建AsyncAwait模块
    if (builder.buildFromTemplate("AsyncAwait", "syntax")) {
        std::cout << "成功构建AsyncAwait.cjmod" << std::endl;
    }
    
    // 示例6：创建复合扩展
    std::cout << "\n=== 示例6：复合CJMOD扩展 ===" << std::endl;
    
    // 创建一个结合多种功能的扩展
    class ReactiveExtension : public CJMODExtensionBase {
    public:
        ReactiveExtension()
            : CJMODExtensionBase("Reactive", "1.0.0", "Reactive programming support") {}
        
        void registerFunctions(std::shared_ptr<ScriptProcessor> processor) override {
            // 注册响应式函数
            processor->registerFunction("reactive",
                [](const std::vector<std::string>& args) -> std::string {
                    if (args.empty()) return "{}";
                    return "new Proxy(" + args[0] + ", {"
                           "set: function(obj, prop, value) {"
                           "  obj[prop] = value;"
                           "  console.log('Property', prop, 'changed to', value);"
                           "  return true;"
                           "}})";
                });
            
            // 注册computed函数
            processor->registerFunction("computed",
                [](const std::vector<std::string>& args) -> std::string {
                    if (args.empty()) return "null";
                    return "(function() { "
                           "let cached = null; "
                           "return function() { "
                           "  if (cached === null) cached = (" + args[0] + ")(); "
                           "  return cached; "
                           "}; "
                           "})()";
                });
        }
    };
    
    // 使用响应式扩展
    generator.generateElement("div", {{"id", "reactive-demo"}});
    
    auto reactiveExt = std::make_unique<ReactiveExtension>();
    reactiveExt->registerFunctions(scriptProcessor);
    
    generator.beginScriptBlock();
    generator.addScriptContent(R"(
        // 创建响应式对象
        const state = reactive({
            count: 0,
            message: 'Hello'
        });
        
        // 创建计算属性
        const doubleCount = computed(() => state.count * 2);
        
        // 修改状态
        state.count = 5;
        
        {{#reactive-demo}}->innerHTML = `
            <p>Count: ${state.count}</p>
            <p>Double: ${doubleCount()}</p>
        `;
    )");
    generator.endScriptBlock();
    
    generator.closeElement();
    
    // 输出生成的代码
    std::cout << "\n=== 生成的HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    std::cout << "\n=== 生成的JavaScript（部分） ===" << std::endl;
    std::string js = generator.getJS();
    std::cout << js.substr(0, 500) << "..." << std::endl;
    
    // 清理创建的文件
    std::cout << "\n=== 清理示例文件 ===" << std::endl;
    fs::remove_all("AsyncAwait");
    fs::remove("AsyncAwait.cjmod");
    
    return 0;
}

/* 预期功能：

1. CJMOD扩展接口：
   - preprocess: 预处理脚本
   - transform: 转换脚本
   - registerFunctions: 注册自定义函数

2. 扩展类型：
   - 语法扩展（async/await, pipeline）
   - 函数扩展（数学函数）
   - 框架扩展（响应式编程）

3. 动态加载：
   - 编译C++代码为.so文件
   - 动态加载扩展
   - 运行时注册功能

4. 模块化：
   - 标准目录结构
   - 信息文件
   - 导出控制

*/