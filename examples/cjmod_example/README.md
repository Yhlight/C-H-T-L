# CJMOD示例：MathUtils

这是一个简单的CJMOD示例，展示如何创建数学工具扩展。

## 功能

- 高级数学函数（阶乘、斐波那契、素数检测）
- 向量运算（点积、叉积、归一化）
- 矩阵运算（乘法、转置、行列式）

## 构建方法

```bash
# 1. 进入示例目录
cd examples/cjmod_example

# 2. 创建构建目录
mkdir build && cd build

# 3. 配置
cmake ..

# 4. 构建
cmake --build . --config Release

# 5. 打包（需要CHTL编译器）
cd ..
chtl --pack-cjmod .
```

## 使用示例

```chtl
// 导入CJMOD
[Import] @CJmod from MathUtils

script {
    // 创建数学工具实例
    var math = new MathUtils.Advanced();
    
    // 计算阶乘
    console.log("5! = " + math.factorial(5));
    
    // 检测素数
    if (math.isPrime(17)) {
        console.log("17 is prime");
    }
    
    // 向量运算
    var vec = new MathUtils.Vector3D();
    var v1 = [1, 2, 3];
    var v2 = [4, 5, 6];
    
    var dot = vec.dot(v1, v2);
    console.log("Dot product: " + dot);
    
    // 清理资源
    math.destroy();
    vec.destroy();
}
```

## 项目结构

```
cjmod_example/
├── CMakeLists.txt
├── README.md
├── info/
│   └── module.info
├── include/
│   └── mathutils.h
├── src/
│   └── mathutils.cpp
└── test.chtl
```