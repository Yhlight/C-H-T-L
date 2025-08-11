# CJmod (CHTL JavaScript Module) 设计文档

## 1. 模块结构

### 1.1 文件格式
```
my-module/
├── package.json         # 模块元信息
├── index.cjmod.js      # 主模块文件
├── runtime/            # 运行时代码
│   ├── init.js        # 初始化代码
│   └── methods.js     # 方法实现
├── tests/             # 测试文件
└── docs/              # 文档
```

### 1.2 模块定义接口
```typescript
interface CJmodDefinition {
  name: string;
  version: string;
  description: string;
  author?: string;
  license?: string;
  
  // 扩展定义
  extensions: {
    methods?: Record<string, Function>;
    operators?: Record<string, Function>;
    selectors?: Record<string, Function>;
    transforms?: Record<string, Function>;
  };
  
  // 运行时代码
  runtime?: string | {
    init?: string;
    beforeCompile?: string;
    afterCompile?: string;
  };
  
  // 编译时插件
  compiler?: {
    preprocessor?: Function;
    postprocessor?: Function;
    optimizer?: Function;
  };
  
  // 依赖
  dependencies?: Record<string, string>;
  peerDependencies?: Record<string, string>;
}
```

## 2. 编译器集成

### 2.1 CJmod 加载器
```cpp
class CJmodLoader {
public:
    void loadModule(const std::string& moduleName);
    void registerExtension(const CJmodDefinition& def);
    std::string processScript(const std::string& script);
    
private:
    std::map<std::string, CJmodDefinition> modules_;
    std::vector<Extension> extensions_;
};
```

### 2.2 语法扩展机制
- 解析时注入：在 AST 构建阶段识别扩展语法
- 生成时转换：在代码生成阶段应用转换规则
- 运行时支持：生成必要的运行时辅助代码

## 3. 标准模块库

### 3.1 核心模块
- **@cjmod/core** - 基础工具函数
- **@cjmod/animate** - 动画功能
- **@cjmod/events** - 事件处理增强
- **@cjmod/ajax** - AJAX 请求封装
- **@cjmod/router** - 客户端路由

### 3.2 UI 组件模块
- **@cjmod/modal** - 模态框
- **@cjmod/tooltip** - 工具提示
- **@cjmod/dropdown** - 下拉菜单
- **@cjmod/tabs** - 标签页

### 3.3 表单模块
- **@cjmod/validate** - 表单验证
- **@cjmod/mask** - 输入掩码
- **@cjmod/datepicker** - 日期选择器

## 4. 示例模块实现

### 4.1 动画模块
```javascript
// @cjmod/animate/index.cjmod.js
export default {
  name: '@cjmod/animate',
  version: '1.0.0',
  
  extensions: {
    methods: {
      fadeIn(duration = 300, easing = 'ease') {
        const element = this;
        element.style.opacity = '0';
        element.style.transition = `opacity ${duration}ms ${easing}`;
        
        requestAnimationFrame(() => {
          element.style.opacity = '1';
        });
        
        return new Promise(resolve => {
          setTimeout(resolve, duration);
        });
      },
      
      shake(duration = 500, intensity = 10) {
        const keyframes = [
          { transform: 'translateX(0)' },
          { transform: `translateX(-${intensity}px)` },
          { transform: `translateX(${intensity}px)` },
          { transform: 'translateX(0)' }
        ];
        
        return this.animate(keyframes, {
          duration,
          iterations: 3
        });
      }
    }
  }
};
```

### 4.2 验证模块
```javascript
// @cjmod/validate/index.cjmod.js
export default {
  name: '@cjmod/validate',
  version: '1.0.0',
  
  extensions: {
    methods: {
      validate(rules) {
        const element = this;
        const validators = {
          required: (val) => val.trim() !== '',
          email: (val) => /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(val),
          minLength: (val, len) => val.length >= len,
          maxLength: (val, len) => val.length <= len,
          pattern: (val, regex) => new RegExp(regex).test(val)
        };
        
        element.addEventListener('blur', () => {
          const value = element.value;
          let isValid = true;
          let message = '';
          
          for (const [rule, param] of Object.entries(rules)) {
            if (!validators[rule](value, param)) {
              isValid = false;
              message = `Validation failed: ${rule}`;
              break;
            }
          }
          
          element.classList.toggle('invalid', !isValid);
          element.setCustomValidity(message);
        });
        
        return element;
      }
    }
  }
};
```

## 5. CLI 工具

### 5.1 模块管理命令
```bash
# 初始化新模块
chtl mod init <module-name>

# 安装模块
chtl mod install <module-name>
chtl mod install <module-name>@<version>
chtl mod install ./local-module

# 卸载模块
chtl mod uninstall <module-name>

# 更新模块
chtl mod update <module-name>
chtl mod update --all

# 发布模块
chtl mod publish
chtl mod publish --tag beta

# 搜索模块
chtl mod search <keyword>

# 查看模块信息
chtl mod info <module-name>
```

### 5.2 开发工具
```bash
# 本地测试
chtl mod test

# 构建模块
chtl mod build

# 链接本地模块
chtl mod link
chtl mod link <module-name>

# 生成文档
chtl mod docs
```

## 6. 模块仓库

### 6.1 中央仓库
- 官方仓库：https://cjmod.chtl.io
- 镜像支持：支持私有镜像
- CDN 加速：全球分发

### 6.2 私有仓库
```bash
# 配置私有仓库
chtl config set registry https://my-registry.com

# 使用特定仓库
chtl mod install <module> --registry https://custom-registry.com
```

## 7. 安全性

### 7.1 沙箱执行
- 模块代码在受限环境中执行
- 限制对敏感 API 的访问
- 防止恶意代码注入

### 7.2 签名验证
- 模块发布时自动签名
- 安装时验证签名
- 支持信任列表

## 8. 兼容性

### 8.1 版本管理
- 语义化版本控制
- 自动依赖解析
- 版本冲突处理

### 8.2 向后兼容
- 保持 API 稳定性
- 废弃功能的平滑过渡
- 迁移工具支持