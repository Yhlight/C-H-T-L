# Chtholly Module 珂朵莉主题模块

> 致敬《末日时在做什么？有没有空？可以来拯救吗？》中最幸福的女孩 —— 珂朵莉·诺塔·瑟尼欧里斯

## 🌟 模块介绍

Chtholly模块是一个精心设计的CHTL主题模块，灵感来源于轻小说《末日时在做什么？有没有空？可以来拯救吗？》（简称SukaSuka）中的女主角珂朵莉·诺塔·瑟尼欧里斯。

这个模块包含了完整的UI组件系统，采用了与珂朵莉相关的设计元素：
- 天蓝色的主色调（象征她的头发）
- 深红色的强调色（象征她的眼睛）
- 优雅温柔的设计风格
- 妖精兵和圣剑主题的组件

## 📦 模块内容

### 颜色系统 (ChthollysColors)
- **主色调**：天蓝色、深红色、纯白色
- **情感色彩**：幸福的金黄、温柔的粉色、忧郁的蓝色
- **功能色彩**：主色、次色、背景色、文本色、边框色

### 字体系统 (ChthollysTypography)
- **优雅的衬线体**：用于标题和重要文本
- **清晰的无衬线体**：用于正文内容
- **多种字体大小**：从小号到英雄级别

### 间距系统 (ChthollysSpacing)
- **基础间距**：xs, sm, md, lg, xl, xxl
- **组件间距**：按钮内边距、卡片内边距、区块间距

### 组件样式

#### 按钮组件
- `SenioriousButton` - 圣剑风格的基础按钮
- `SenioriousPrimaryButton` - 主要按钮（深红色）
- `SenioriousGhostButton` - 幽灵按钮（透明背景）

#### 卡片组件
- `FairyCard` - 妖精兵风格的基础卡片
- `FairyCardHover` - 带悬停效果的卡片

#### 标题样式
- `ChthollysH1` - 大标题（带下划线装饰）
- `ChthollysH2` - 中标题
- `ChthollysH3` - 小标题

#### 其他组件
- `FairyList` - 妖精风格列表（花朵标记）
- `ChthollysQuote` - 优雅的引用样式
- `FairyBadge` - 徽章组件（多种颜色）
- `FairyWingAnimation` - 妖精之翼浮动动画

### 特殊元素

#### HappinessMemory（幸福记忆）
展示珂朵莉美好回忆的卡片组件，带有闪光装饰。

#### SenioriousContainer（圣剑容器）
象征圣剑瑟尼欧里斯力量的容器，顶部有发光动画效果。

#### MemoryFragment（记忆碎片）
用于展示图片和描述的组件，适合创建画廊或人物介绍。

## 🚀 使用方法

### 1. 导入模块

```chtl
[Import] @Chtl from Chtholly
```

### 2. 使用颜色系统

```chtl
style {
    color: Chtholly.ChthollysColors(primaryColor);
    background: Chtholly.ChthollysColors(softGray);
}
```

### 3. 应用样式

```chtl
button {
    style { @Style Chtholly.SenioriousPrimaryButton; }
    text { "点击我" }
}
```

### 4. 使用组件

```chtl
@Element Chtholly.HappinessMemory {
    h3 { text { "标题" } }
    p { text { "内容描述" } }
}
```

## 📋 完整示例

查看 `example.chtl` 文件，了解如何创建一个完整的珂朵莉主题页面。

## 🎨 设计理念

这个模块的设计理念基于珂朵莉的角色特征：

1. **温柔与坚强**：柔和的颜色搭配坚实的布局
2. **纯净与优雅**：简洁的设计风格，注重细节
3. **希望与忧郁**：明亮的主色调与深沉的辅助色
4. **动态与静谧**：适度的动画效果，不喧宾夺主

## 💝 致敬

> "即使是这样的我，也想要成为某个人的幸福。"

这个模块是对珂朵莉·诺塔·瑟尼欧里斯的致敬，她用自己的方式诠释了什么是真正的幸福。愿使用这个模块的每个人，都能创造出温暖而美好的作品。

## 📄 许可证

MIT License - 自由使用，但请保留对原作的敬意。

---

*"谢谢你，让我成为了世界上最幸福的女孩。" —— 珂朵莉*