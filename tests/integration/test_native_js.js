// 原生JavaScript测试文件 - 验证JS编译器对标准JS的支持

// ES5语法
var oldVar = "这是var声明";
function oldFunction() {
    console.log("传统函数声明");
}

// ES6+ 语法
// let和const声明
let mutableVar = "可变变量";
const CONSTANT = "常量";

// 箭头函数
const arrowFunc = () => console.log("箭头函数");
const arrowWithParams = (a, b) => a + b;
const arrowWithBody = (x) => {
    const result = x * 2;
    return result;
};

// 模板字符串
const name = "CHTL";
const greeting = `Hello, ${name}!`;
const multiline = `
    这是一个
    多行字符串
`;

// 解构赋值
const obj = { x: 1, y: 2, z: 3 };
const { x, y, z } = obj;

const arr = [1, 2, 3, 4, 5];
const [first, second, ...rest] = arr;

// 默认参数
function greet(name = "World") {
    return `Hello, ${name}!`;
}

// 剩余参数
function sum(...numbers) {
    return numbers.reduce((acc, curr) => acc + curr, 0);
}

// 展开运算符
const newArr = [...arr, 6, 7, 8];
const newObj = { ...obj, w: 4 };

// 类定义
class Animal {
    constructor(name) {
        this.name = name;
    }
    
    speak() {
        console.log(`${this.name} makes a sound.`);
    }
}

class Dog extends Animal {
    constructor(name, breed) {
        super(name);
        this.breed = breed;
    }
    
    speak() {
        console.log(`${this.name} barks.`);
    }
    
    static createPuppy(name) {
        return new Dog(name, "Mixed");
    }
}

// Getter和Setter
class Circle {
    constructor(radius) {
        this._radius = radius;
    }
    
    get radius() {
        return this._radius;
    }
    
    set radius(value) {
        if (value > 0) {
            this._radius = value;
        }
    }
    
    get area() {
        return Math.PI * this._radius ** 2;
    }
}

// Promise
const myPromise = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve("Promise resolved!");
    }, 1000);
});

myPromise.then(result => console.log(result))
         .catch(error => console.error(error));

// Async/Await
async function fetchData() {
    try {
        const response = await fetch('https://api.example.com/data');
        const data = await response.json();
        return data;
    } catch (error) {
        console.error('Error fetching data:', error);
    }
}

// Generator函数
function* numberGenerator() {
    yield 1;
    yield 2;
    yield 3;
}

const gen = numberGenerator();
console.log(gen.next().value); // 1

// Map和Set
const myMap = new Map();
myMap.set('key1', 'value1');
myMap.set('key2', 'value2');

const mySet = new Set([1, 2, 3, 3, 4]);
console.log(mySet.size); // 4

// Symbol
const sym1 = Symbol('description');
const sym2 = Symbol.for('shared');

// Proxy
const target = {
    message: "Hello"
};

const handler = {
    get: function(target, prop) {
        return prop in target ? target[prop] : 'Property not found';
    }
};

const proxy = new Proxy(target, handler);

// 迭代器
const iterableObj = {
    data: ['a', 'b', 'c'],
    [Symbol.iterator]() {
        let index = 0;
        return {
            next: () => {
                if (index < this.data.length) {
                    return { value: this.data[index++], done: false };
                }
                return { done: true };
            }
        };
    }
};

// for...of循环
for (const item of iterableObj) {
    console.log(item);
}

// 动态导入
async function loadModule() {
    const module = await import('./module.js');
    module.doSomething();
}

// 可选链
const user = {
    address: {
        street: "123 Main St"
    }
};

const street = user?.address?.street;
const missing = user?.phone?.number;

// 空值合并
const value = null;
const defaultValue = value ?? "Default";

// BigInt
const bigNumber = 123456789012345678901234567890n;
const anotherBig = BigInt("999999999999999999999999999");

// 私有字段
class Counter {
    #count = 0;
    
    increment() {
        this.#count++;
    }
    
    get value() {
        return this.#count;
    }
}

// 正则表达式
const regex = /[a-z]+@[a-z]+\.[a-z]+/gi;
const email = "test@example.com";
console.log(regex.test(email));

// 异常处理
try {
    throw new Error("自定义错误");
} catch (e) {
    console.error("捕获错误:", e.message);
} finally {
    console.log("清理资源");
}

// 导出
export { Animal, Dog, Circle };
export default class Main {
    static run() {
        console.log("主程序运行");
    }
}