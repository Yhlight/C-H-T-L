# ANTLR4生成的CHTL编译器解析器文件

## 生成结果

使用ANTLR 4.13.1成功生成了CHTL编译器系统的所有解析器文件，包括Java和C++两种目标语言。

### 生成的解析器

1. **CHTL解析器** ✅
   - Java: `output/java/chtl/`
   - C++: `output/cpp/chtl/`
   - 包含: Lexer、Parser、Listener、BaseListener

2. **CSS解析器** ✅
   - Java: `output/java/css/`
   - C++: `output/cpp/css/`
   - 包含: Lexer、Parser、Listener、BaseListener

3. **JavaScript解析器** ✅
   - Java: `output/java/javascript/`
   - C++: `output/cpp/javascript/`
   - 包含: Lexer、Parser、Listener、BaseListener

4. **CHTL JavaScript解析器** ✅
   - Java: `output/java/chtljs/`
   - C++: `output/cpp/chtljs/`
   - 包含: Lexer、Parser、Listener、BaseListener

5. **Scanner解析器** ✅
   - Java: `output/java/scanner/`
   - C++: `output/cpp/scanner/`
   - 包含: Lexer、Parser、Listener、BaseListener

### 文件类型说明

- **Lexer**: 词法分析器，将输入文本转换为令牌流
- **Parser**: 语法分析器，根据语法规则构建解析树
- **Listener**: 监听器接口，用于遍历解析树
- **BaseListener**: 监听器的默认实现
- **.tokens**: 令牌定义文件
- **.interp**: 解释器数据文件

### 警告说明

生成过程中出现了一些警告（非错误）：
- `JavaScript.g4`和`CHTLJavaScript.g4`中的`arrayLiteral`规则包含可以匹配空字符串的可选块
- 这些警告不影响解析器的正常工作

### 使用方法

#### Java版本
```java
// 示例：使用CHTL解析器
import chtl.*;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class CHTLDemo {
    public static void main(String[] args) throws Exception {
        // 创建输入流
        ANTLRInputStream input = new ANTLRInputStream("div { text { \"Hello CHTL!\" } }");
        
        // 创建词法分析器
        CHTLLexer lexer = new CHTLLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        
        // 创建语法分析器
        CHTLParser parser = new CHTLParser(tokens);
        
        // 解析
        ParseTree tree = parser.program();
        
        // 遍历解析树
        ParseTreeWalker walker = new ParseTreeWalker();
        CHTLBaseListener listener = new CHTLBaseListener();
        walker.walk(listener, tree);
    }
}
```

#### C++版本
```cpp
#include "CHTLLexer.h"
#include "CHTLParser.h"
#include "CHTLBaseListener.h"
#include <antlr4-runtime.h>

int main() {
    // 创建输入流
    antlr4::ANTLRInputStream input("div { text { \"Hello CHTL!\" } }");
    
    // 创建词法分析器
    CHTLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    
    // 创建语法分析器
    CHTLParser parser(&tokens);
    
    // 解析
    auto tree = parser.program();
    
    // 遍历解析树
    CHTLBaseListener listener;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    
    return 0;
}
```

### 下一步

1. **实现监听器**：为每个解析器实现具体的监听器类来处理解析树
2. **代码生成**：基于解析树生成目标HTML/CSS/JS代码
3. **集成Scanner**：实现代码分发逻辑，将不同类型的代码块分配给相应的解析器
4. **错误处理**：添加语法错误处理和恢复机制
5. **测试**：编写测试用例验证解析器的正确性