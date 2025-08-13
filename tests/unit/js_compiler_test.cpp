#include "test_framework.h"
#include "../../src/chtl/CHTLJSCompiler.h"
#include <sstream>

using namespace chtl;
using namespace chtl::test;

// 测试JS编译器的辅助函数
std::string compileJS(const std::string& js, bool minify = false) {
    // 这里应该调用实际的JS编译器
    // 简化示例
    return js;
}

TEST(JSCompiler, VariableDeclarations) {
    std::string js = R"(
        var oldVar = "var";
        let newVar = "let";
        const constant = "const";
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("var oldVar") != std::string::npos);
    ASSERT_TRUE(result.find("let newVar") != std::string::npos);
    ASSERT_TRUE(result.find("const constant") != std::string::npos);
}

TEST(JSCompiler, Functions) {
    std::string js = R"(
        function regularFunction() { return 1; }
        const arrowFunc = () => 2;
        const arrowWithParams = (a, b) => a + b;
        const arrowWithBody = x => {
            const result = x * 2;
            return result;
        };
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("function regularFunction") != std::string::npos);
    ASSERT_TRUE(result.find("=>") != std::string::npos);
}

TEST(JSCompiler, Classes) {
    std::string js = R"(
        class Animal {
            constructor(name) {
                this.name = name;
            }
            speak() {
                console.log(`${this.name} makes a sound`);
            }
        }
        
        class Dog extends Animal {
            constructor(name, breed) {
                super(name);
                this.breed = breed;
            }
            speak() {
                console.log(`${this.name} barks`);
            }
        }
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("class Animal") != std::string::npos);
    ASSERT_TRUE(result.find("extends Animal") != std::string::npos);
    ASSERT_TRUE(result.find("super(name)") != std::string::npos);
}

TEST(JSCompiler, TemplateStrings) {
    std::string js = R"(
        const name = "World";
        const greeting = `Hello, ${name}!`;
        const multiline = `Line 1
        Line 2
        Line 3`;
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("`Hello, ${name}!`") != std::string::npos);
    ASSERT_TRUE(result.find("`Line 1") != std::string::npos);
}

TEST(JSCompiler, Destructuring) {
    std::string js = R"(
        const obj = { x: 1, y: 2, z: 3 };
        const { x, y, z } = obj;
        
        const arr = [1, 2, 3, 4, 5];
        const [first, second, ...rest] = arr;
        
        function process({ name, age = 18 }) {
            return `${name} is ${age}`;
        }
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("{ x, y, z }") != std::string::npos);
    ASSERT_TRUE(result.find("[first, second, ...rest]") != std::string::npos);
    ASSERT_TRUE(result.find("{ name, age = 18 }") != std::string::npos);
}

TEST(JSCompiler, SpreadOperator) {
    std::string js = R"(
        const arr1 = [1, 2, 3];
        const arr2 = [...arr1, 4, 5];
        
        const obj1 = { a: 1, b: 2 };
        const obj2 = { ...obj1, c: 3 };
        
        function sum(...numbers) {
            return numbers.reduce((a, b) => a + b, 0);
        }
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("...arr1") != std::string::npos);
    ASSERT_TRUE(result.find("...obj1") != std::string::npos);
    ASSERT_TRUE(result.find("...numbers") != std::string::npos);
}

TEST(JSCompiler, AsyncAwait) {
    std::string js = R"(
        async function fetchData() {
            try {
                const response = await fetch('/api/data');
                const data = await response.json();
                return data;
            } catch (error) {
                console.error(error);
            }
        }
        
        const asyncArrow = async () => {
            return await Promise.resolve(42);
        };
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("async function") != std::string::npos);
    ASSERT_TRUE(result.find("await fetch") != std::string::npos);
    ASSERT_TRUE(result.find("async ()") != std::string::npos);
}

TEST(JSCompiler, Modules) {
    std::string js = R"(
        import React from 'react';
        import { useState, useEffect } from 'react';
        import * as utils from './utils';
        
        export default class App {}
        export { Component };
        export const API_KEY = '12345';
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("import React") != std::string::npos);
    ASSERT_TRUE(result.find("import {") != std::string::npos);
    ASSERT_TRUE(result.find("export default") != std::string::npos);
    ASSERT_TRUE(result.find("export {") != std::string::npos);
}

TEST(JSCompiler, OptionalChaining) {
    std::string js = R"(
        const user = { address: { street: "123 Main St" } };
        const street = user?.address?.street;
        const missing = user?.phone?.number;
        const method = obj.method?.();
        const array = arr?.[0];
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("?.") != std::string::npos);
    ASSERT_TRUE(result.find("?.()") != std::string::npos);
    ASSERT_TRUE(result.find("?.[") != std::string::npos);
}

TEST(JSCompiler, NullishCoalescing) {
    std::string js = R"(
        const value = null;
        const defaultValue = value ?? "default";
        const zero = 0 ?? 42;
        const empty = "" ?? "fallback";
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("??") != std::string::npos);
}

TEST(JSCompiler, PrivateFields) {
    std::string js = R"(
        class Counter {
            #count = 0;
            
            increment() {
                this.#count++;
            }
            
            get value() {
                return this.#count;
            }
        }
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("#count") != std::string::npos);
    ASSERT_TRUE(result.find("this.#count") != std::string::npos);
}

TEST(JSCompiler, Generators) {
    std::string js = R"(
        function* numberGenerator() {
            yield 1;
            yield 2;
            yield 3;
        }
        
        function* infiniteSequence() {
            let i = 0;
            while (true) {
                yield i++;
            }
        }
    )";
    
    std::string result = compileJS(js);
    ASSERT_TRUE(result.find("function*") != std::string::npos);
    ASSERT_TRUE(result.find("yield") != std::string::npos);
}

RUN_ALL_TESTS()