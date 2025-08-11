# CHTL 语法实现审查

## 1. 块定义语法

### 模板定义
```chtl
[Template] @Element Name { ... }
[Template] @Style Name { ... }
[Template] @Var Name { ... }
```

### 自定义定义
```chtl
[Custom] @Element Name { ... }
[Custom] @Style Name { ... }
[Custom] @Var Name { ... }
```

### 其他块
```chtl
[Origin] @Type name { ... }
[Configuration] { ... }
[Import] ...
[Namespace] name { ... }
[Info] { ... }
[Export] { ... }
[Script] { ... }
```

## 2. 元素语法

### 基本元素
```chtl
tagname { ... }
tagname { attribute: value; ... }
```

### 文本内容
```chtl
text { "content" }
```

### 样式块
```chtl
style { ... }
```

### 脚本块
```chtl
script { ... }
```

## 3. 引用语法

### 基本引用
```chtl
@Element Name;
@Style Name;
@Var Name;
```

### 带参数引用
```chtl
@Var Name(param = value);
```

### 特例化引用
```chtl
@Element Name {
    delete ...;
    insert ...;
}
```

## 4. 继承语法
```chtl
inherit @Element Name;
inherit @Style Name;
inherit @Var Name;
```

## 5. 操作语法

### 删除
```chtl
delete item1, item2;
delete element[index];
delete @Element Name[index];
```

### 插入
```chtl
insert at top { ... }
insert at bottom { ... }
insert before target { ... }
insert after target { ... }
insert replace target { ... }
```

## 6. 约束语法
```chtl
except condition { ... }
```

## 7. 样式语法

### CSS 属性
```chtl
property: value;
```

### 伪类/伪元素
```chtl
&:hover { ... }
&::before { ... }
```

### 嵌套选择器
```chtl
.class { ... }
#id { ... }
element { ... }
```

## 8. JavaScript 增强语法

### 选择器
```chtl
{{selector}}
{{&}}
```

### 操作符
```chtl
{{selector}}->method()
```

## 9. 注释
```chtl
// 单行注释
/* 多行注释 */
-- 生成器识别的注释
```

## 10. 导入/导出
```chtl
[Import] path;
[Import] path as alias;
[Import] from namespace;
```

## 需要验证的语法

1. 变量组函数调用
2. 配置系统的实际应用
3. 命名空间的完整实现
4. 原始嵌入的各种用法
5. 导出块的自动生成和手动覆盖