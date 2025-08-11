#include "CJmod/CJmodAdvanced.h"
#include <regex>

using namespace chtl;
using namespace chtl::cjmod;

// 示例 1: 协程语法模块
CJMOD_ADVANCED(Coroutine, "1.0.0")

CJMOD_INIT(
    // 注册新的 token
    ctx->registerToken("yield", TokenType::KEYWORD);
    ctx->registerToken("async*", TokenType::KEYWORD);
    
    // 注册协程关键字解析器
    ctx->registerKeyword("async*", [](StandardParser* parser) -> std::shared_ptr<Node> {
        // async* 函数定义
        auto funcNode = std::make_shared<CustomNode>("AsyncGenerator");
        
        // 解析函数名
        if (parser->check(TokenType::IDENTIFIER)) {
            funcNode->setCustomData("name", parser->advance().value);
        }
        
        // 解析参数
        parser->consume(TokenType::LEFT_PAREN, "Expected '('");
        std::vector<std::string> params;
        while (!parser->check(TokenType::RIGHT_PAREN)) {
            params.push_back(parser->advance().value);
            if (parser->match(TokenType::COMMA)) continue;
        }
        parser->consume(TokenType::RIGHT_PAREN, "Expected ')'");
        funcNode->setCustomData("params", params);
        
        // 解析函数体
        parser->consume(TokenType::LEFT_BRACE, "Expected '{'");
        auto body = std::make_shared<Script>();
        
        // 解析直到遇到 }
        std::string bodyCode;
        int braceCount = 1;
        while (braceCount > 0 && !parser->isAtEnd()) {
            auto token = parser->advance();
            if (token.type == TokenType::LEFT_BRACE) braceCount++;
            else if (token.type == TokenType::RIGHT_BRACE) braceCount--;
            
            if (braceCount > 0) {
                bodyCode += token.value + " ";
            }
        }
        
        body->setContent(bodyCode);
        funcNode->addChild(body);
        
        return funcNode;
    });
    
    // 注册 yield 解析器
    ctx->registerKeyword("yield", [](StandardParser* parser) -> std::shared_ptr<Node> {
        auto yieldNode = std::make_shared<CustomNode>("Yield");
        
        // 解析 yield 的值
        std::string value;
        while (!parser->check(TokenType::SEMICOLON) && !parser->isAtEnd()) {
            value += parser->advance().value + " ";
        }
        parser->consume(TokenType::SEMICOLON, "Expected ';'");
        
        yieldNode->setCustomData("value", value);
        return yieldNode;
    });
    
    // 注册生成器
    ctx->registerGenerator(NodeType::CUSTOM, [](WebGenerator* gen, const std::shared_ptr<Node>& node) {
        if (auto customNode = std::dynamic_pointer_cast<CustomNode>(node)) {
            if (customNode->getCustomType() == "AsyncGenerator") {
                // 生成异步生成器函数
                auto name = std::any_cast<std::string>(customNode->getCustomData("name"));
                auto params = std::any_cast<std::vector<std::string>>(customNode->getCustomData("params"));
                
                std::string code = "async function* " + name + "(";
                for (size_t i = 0; i < params.size(); ++i) {
                    if (i > 0) code += ", ";
                    code += params[i];
                }
                code += ") {\n";
                
                // 获取函数体
                if (!customNode->getChildren().empty()) {
                    auto body = std::dynamic_pointer_cast<Script>(customNode->getChildren()[0]);
                    if (body) {
                        code += body->getContent();
                    }
                }
                
                code += "\n}";
                gen->appendToCurrentCollector(code);
                
            } else if (customNode->getCustomType() == "Yield") {
                auto value = std::any_cast<std::string>(customNode->getCustomData("value"));
                gen->appendToCurrentCollector("yield " + value + ";");
            }
        }
    });
    
    // 设置全局状态
    ctx->setState("coroutine.enabled", true);
    ctx->setState("coroutine.polyfill", std::string(R"(
        // Coroutine polyfill
        if (!window.AsyncGeneratorFunction) {
            window.AsyncGeneratorFunction = Object.getPrototypeOf(async function*(){}).constructor;
        }
    )"));
)

CJMOD_END()

// 示例 2: 类型注解模块
CJMOD_ADVANCED(TypeAnnotation, "1.0.0")

private:
    // 自定义解析类型注解
    std::string parseType(StandardParser* parser) {
        std::string type;
        
        // 基本类型
        if (parser->check(TokenType::IDENTIFIER)) {
            type = parser->advance().value;
            
            // 泛型
            if (parser->match(TokenType::LESS)) {
                type += "<";
                type += parseType(parser);
                while (parser->match(TokenType::COMMA)) {
                    type += ", " + parseType(parser);
                }
                parser->consume(TokenType::GREATER, "Expected '>'");
                type += ">";
            }
            
            // 数组
            while (parser->match(TokenType::LEFT_BRACKET)) {
                parser->consume(TokenType::RIGHT_BRACKET, "Expected ']'");
                type += "[]";
            }
        }
        
        return type;
    }

public:
CJMOD_INIT(
    // 注册 : 作为类型注解符号
    ctx->modifyParser([this](StandardParser* parser) {
        // 在解析变量声明时检查类型注解
        parser->addParseHook("afterIdentifier", [this, parser](const Token& identifier) {
            if (parser->match(TokenType::COLON)) {
                std::string type = parseType(parser);
                
                // 存储类型信息
                parser->getContext()->setAttribute(identifier.value, "type", type);
                
                // 在开发模式下生成运行时类型检查
                if (parser->getContext()->getAttribute("mode", "development") == "development") {
                    return std::make_shared<Comment>("@type " + type);
                }
            }
            return std::shared_ptr<Node>(nullptr);
        });
    });
    
    // 注册接口定义
    ctx->registerKeyword("interface", [](StandardParser* parser) -> std::shared_ptr<Node> {
        auto interfaceNode = std::make_shared<CustomNode>("Interface");
        
        // 接口名
        auto name = parser->consume(TokenType::IDENTIFIER, "Expected interface name").value;
        interfaceNode->setCustomData("name", name);
        
        // 解析接口体
        parser->consume(TokenType::LEFT_BRACE, "Expected '{'");
        
        std::map<std::string, std::string> properties;
        while (!parser->check(TokenType::RIGHT_BRACE) && !parser->isAtEnd()) {
            auto propName = parser->consume(TokenType::IDENTIFIER, "Expected property name").value;
            parser->consume(TokenType::COLON, "Expected ':'");
            
            // 简化：只读取到分号或逗号
            std::string propType;
            while (!parser->check(TokenType::SEMICOLON) && 
                   !parser->check(TokenType::COMMA) && 
                   !parser->isAtEnd()) {
                propType += parser->advance().value + " ";
            }
            
            properties[propName] = propType;
            
            if (parser->match(TokenType::SEMICOLON) || parser->match(TokenType::COMMA)) {
                continue;
            }
        }
        
        parser->consume(TokenType::RIGHT_BRACE, "Expected '}'");
        
        interfaceNode->setCustomData("properties", properties);
        return interfaceNode;
    });
    
    // 生成 TypeScript 声明文件
    ctx->registerGenerator(NodeType::CUSTOM, [](WebGenerator* gen, const std::shared_ptr<Node>& node) {
        if (auto customNode = std::dynamic_pointer_cast<CustomNode>(node)) {
            if (customNode->getCustomType() == "Interface") {
                auto name = std::any_cast<std::string>(customNode->getCustomData("name"));
                auto props = std::any_cast<std::map<std::string, std::string>>(customNode->getCustomData("properties"));
                
                // 生成 JSDoc 注释
                std::string jsdoc = "/**\n * @typedef {Object} " + name + "\n";
                for (const auto& [propName, propType] : props) {
                    jsdoc += " * @property {" + propType + "} " + propName + "\n";
                }
                jsdoc += " */\n";
                
                gen->appendToCurrentCollector(jsdoc);
            }
        }
    });
    
    // 包含类型检查库
    ctx->includeHeader("<type_traits>");
    ctx->setState("typescript.enabled", true);
)

CJMOD_END()

// 示例 3: 响应式系统（深度集成）
CJMOD_ADVANCED(ReactiveSystem, "2.0.0")

private:
    // 追踪响应式变量
    std::set<std::string> reactiveVars_;
    
    // 依赖图
    std::map<std::string, std::set<std::string>> dependencies_;

public:
CJMOD_INIT(
    // 修改词法分析器，识别响应式操作符
    ctx->modifyTokenizer([](StandardLexer* lexer) {
        lexer->addOperator(":=", TokenType::REACTIVE_ASSIGN);
        lexer->addOperator("=>", TokenType::COMPUTED);
        lexer->addOperator("~>", TokenType::EFFECT);
    });
    
    // 注册响应式变量声明
    ctx->registerKeyword(":=", [this](StandardParser* parser) -> std::shared_ptr<Node> {
        auto varNode = std::make_shared<CustomNode>("ReactiveVar");
        
        // 变量名应该在 := 之前已经被解析
        auto varName = parser->getPreviousToken().value;
        varNode->setCustomData("name", varName);
        
        // 记录响应式变量
        reactiveVars_.insert(varName);
        
        // 解析初始值
        std::string initValue;
        while (!parser->check(TokenType::SEMICOLON) && !parser->isAtEnd()) {
            initValue += parser->advance().value + " ";
        }
        parser->consume(TokenType::SEMICOLON, "Expected ';'");
        
        varNode->setCustomData("initialValue", initValue);
        
        // 在上下文中标记为响应式
        parser->getContext()->setAttribute(varName, "reactive", true);
        
        return varNode;
    });
    
    // 注册计算属性
    ctx->registerKeyword("=>", [this](StandardParser* parser) -> std::shared_ptr<Node> {
        auto computedNode = std::make_shared<CustomNode>("ComputedProperty");
        
        auto propName = parser->getPreviousToken().value;
        computedNode->setCustomData("name", propName);
        
        // 解析计算表达式，同时追踪依赖
        std::string expression;
        std::set<std::string> deps;
        
        while (!parser->check(TokenType::SEMICOLON) && !parser->isAtEnd()) {
            auto token = parser->advance();
            expression += token.value + " ";
            
            // 检查是否引用了响应式变量
            if (token.type == TokenType::IDENTIFIER && 
                reactiveVars_.count(token.value)) {
                deps.insert(token.value);
            }
        }
        parser->consume(TokenType::SEMICOLON, "Expected ';'");
        
        computedNode->setCustomData("expression", expression);
        computedNode->setCustomData("dependencies", deps);
        
        // 更新依赖图
        dependencies_[propName] = deps;
        
        return computedNode;
    });
    
    // 注册副作用
    ctx->registerKeyword("effect", [this](StandardParser* parser) -> std::shared_ptr<Node> {
        auto effectNode = std::make_shared<CustomNode>("Effect");
        
        // 解析副作用函数体
        parser->consume(TokenType::LEFT_BRACE, "Expected '{'");
        
        std::string body;
        std::set<std::string> deps;
        int braceCount = 1;
        
        while (braceCount > 0 && !parser->isAtEnd()) {
            auto token = parser->advance();
            
            if (token.type == TokenType::LEFT_BRACE) braceCount++;
            else if (token.type == TokenType::RIGHT_BRACE) braceCount--;
            
            if (braceCount > 0) {
                body += token.value + " ";
                
                // 追踪依赖
                if (token.type == TokenType::IDENTIFIER && 
                    reactiveVars_.count(token.value)) {
                    deps.insert(token.value);
                }
            }
        }
        
        effectNode->setCustomData("body", body);
        effectNode->setCustomData("dependencies", deps);
        
        return effectNode;
    });
    
    // 生成响应式运行时
    ctx->setState("reactive.runtime", std::string(R"(
        class ReactiveSystem {
            constructor() {
                this.dependencies = new Map();
                this.subscribers = new Map();
                this.currentComputation = null;
            }
            
            createReactive(initialValue) {
                let value = initialValue;
                const subscribers = new Set();
                
                const reactive = {
                    get value() {
                        if (ReactiveSystem.instance.currentComputation) {
                            subscribers.add(ReactiveSystem.instance.currentComputation);
                        }
                        return value;
                    },
                    set value(newValue) {
                        if (value !== newValue) {
                            value = newValue;
                            subscribers.forEach(fn => fn());
                        }
                    }
                };
                
                return reactive;
            }
            
            createComputed(fn) {
                let cache;
                let dirty = true;
                
                const computed = {
                    get value() {
                        if (dirty) {
                            const prevComputation = ReactiveSystem.instance.currentComputation;
                            ReactiveSystem.instance.currentComputation = () => { dirty = true; };
                            cache = fn();
                            ReactiveSystem.instance.currentComputation = prevComputation;
                            dirty = false;
                        }
                        return cache;
                    }
                };
                
                return computed;
            }
            
            createEffect(fn) {
                const run = () => {
                    const prevComputation = ReactiveSystem.instance.currentComputation;
                    ReactiveSystem.instance.currentComputation = run;
                    fn();
                    ReactiveSystem.instance.currentComputation = prevComputation;
                };
                
                run();
                return () => { /* cleanup */ };
            }
        }
        
        ReactiveSystem.instance = new ReactiveSystem();
        const reactive = (v) => ReactiveSystem.instance.createReactive(v);
        const computed = (fn) => ReactiveSystem.instance.createComputed(fn);
        const effect = (fn) => ReactiveSystem.instance.createEffect(fn);
    )"));
)

// 在 AST 转换后生成依赖图可视化
void onAfterParsing(std::shared_ptr<Node> ast, CJmodContext* context) override {
    if (!dependencies_.empty()) {
        std::string graphviz = "digraph Dependencies {\n";
        for (const auto& [computed, deps] : dependencies_) {
            for (const auto& dep : deps) {
                graphviz += "  " + dep + " -> " + computed + ";\n";
            }
        }
        graphviz += "}\n";
        
        context->setState("reactive.dependencyGraph", graphviz);
    }
}

CJMOD_END()

// 示例 4: 宏系统
CJMOD_ADVANCED(MacroSystem, "1.0.0")

private:
    struct Macro {
        std::vector<std::string> params;
        std::string body;
    };
    
    std::map<std::string, Macro> macros_;

public:
CJMOD_INIT(
    // 注册 defmacro 关键字
    ctx->registerKeyword("defmacro", [this](StandardParser* parser) -> std::shared_ptr<Node> {
        // 宏名
        auto macroName = parser->consume(TokenType::IDENTIFIER, "Expected macro name").value;
        
        // 参数列表
        parser->consume(TokenType::LEFT_PAREN, "Expected '('");
        std::vector<std::string> params;
        while (!parser->check(TokenType::RIGHT_PAREN)) {
            params.push_back(parser->consume(TokenType::IDENTIFIER, "Expected parameter").value);
            if (!parser->check(TokenType::RIGHT_PAREN)) {
                parser->consume(TokenType::COMMA, "Expected ','");
            }
        }
        parser->consume(TokenType::RIGHT_PAREN, "Expected ')'");
        
        // 宏体
        parser->consume(TokenType::LEFT_BRACE, "Expected '{'");
        std::string body;
        int braceCount = 1;
        
        while (braceCount > 0 && !parser->isAtEnd()) {
            auto token = parser->advance();
            if (token.type == TokenType::LEFT_BRACE) braceCount++;
            else if (token.type == TokenType::RIGHT_BRACE) braceCount--;
            
            if (braceCount > 0) {
                body += token.value + " ";
            }
        }
        
        // 注册宏
        macros_[macroName] = {params, body};
        
        // 注册宏调用解析器
        ctx->registerKeyword(macroName, [this, macroName](StandardParser* parser) -> std::shared_ptr<Node> {
            auto& macro = macros_[macroName];
            
            // 解析实参
            parser->consume(TokenType::LEFT_PAREN, "Expected '('");
            std::vector<std::string> args;
            
            while (!parser->check(TokenType::RIGHT_PAREN)) {
                std::string arg;
                int parenCount = 0;
                
                while (!parser->isAtEnd()) {
                    if (parser->check(TokenType::LEFT_PAREN)) parenCount++;
                    else if (parser->check(TokenType::RIGHT_PAREN)) {
                        if (parenCount == 0) break;
                        parenCount--;
                    }
                    else if (parser->check(TokenType::COMMA) && parenCount == 0) break;
                    
                    arg += parser->advance().value + " ";
                }
                
                args.push_back(arg);
                
                if (!parser->check(TokenType::RIGHT_PAREN)) {
                    parser->consume(TokenType::COMMA, "Expected ','");
                }
            }
            parser->consume(TokenType::RIGHT_PAREN, "Expected ')'");
            
            // 展开宏
            std::string expanded = macro.body;
            for (size_t i = 0; i < macro.params.size() && i < args.size(); ++i) {
                std::regex paramRegex("\\b" + macro.params[i] + "\\b");
                expanded = std::regex_replace(expanded, paramRegex, args[i]);
            }
            
            // 创建展开后的代码节点
            auto expandedNode = std::make_shared<CustomNode>("MacroExpansion");
            expandedNode->setCustomData("code", expanded);
            
            return expandedNode;
        });
        
        // 宏定义本身不生成代码
        return std::make_shared<Comment>("Macro defined: " + macroName);
    });
    
    // 宏展开生成器
    ctx->registerGenerator(NodeType::CUSTOM, [](WebGenerator* gen, const std::shared_ptr<Node>& node) {
        if (auto customNode = std::dynamic_pointer_cast<CustomNode>(node)) {
            if (customNode->getCustomType() == "MacroExpansion") {
                auto code = std::any_cast<std::string>(customNode->getCustomData("code"));
                gen->appendToCurrentCollector(code);
            }
        }
    });
)

CJMOD_END()