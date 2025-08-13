#include "CHTLGenerator.h"
#include "CHTLCMOD.h"
#include <iostream>
#include <filesystem>

using namespace chtl;
namespace fs = std::filesystem;

// 创建示例CMOD模块结构
void createExampleModule() {
    // 创建Chtholly模块
    CMODHelper::createModuleTemplate(fs::current_path(), "Chtholly");
    
    // 修改主模块文件
    std::ofstream mainFile("Chtholly/src/Chtholly.chtl");
    mainFile << R"(// Chtholly Theme Module
[Namespace] Chtholly
{
    // 珂朵莉主题颜色
    [Template] @Var ChthollyColors
    {
        primary: "#FF6B6B";
        secondary: "#4ECDC4";
        accent: "#FFE66D";
        background: "#F7F7F7";
        text: "#2D3436";
    }
    
    // 珂朵莉样式组
    [Template] @Style ChthollyButton
    {
        padding: 10px 20px;
        border: none;
        border-radius: 5px;
        background-color: ChthollyColors(primary);
        color: white;
        cursor: pointer;
        transition: all 0.3s;
        
        &:hover
        {
            background-color: ChthollyColors(secondary);
            transform: translateY(-2px);
        }
    }
    
    // 珂朵莉卡片元素
    [Template] @Element ChthollyCard
    {
        div
        {
            class: chtholly-card;
            
            style
            {
                .chtholly-card
                {
                    background: white;
                    border-radius: 10px;
                    padding: 20px;
                    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
                    margin: 10px;
                }
            }
            
            h3
            {
                style
                {
                    color: ChthollyColors(primary);
                    margin-bottom: 10px;
                }
                
                text { "珂朵莉卡片" }
            }
            
            p
            {
                style
                {
                    color: ChthollyColors(text);
                    line-height: 1.6;
                }
                
                text { "世界上最幸福的女孩" }
            }
        }
    }
}
)";
    mainFile.close();
    
    // 创建子模块Space
    fs::create_directories("Chtholly/src/Space/src");
    fs::create_directories("Chtholly/src/Space/info");
    
    // Space模块信息
    std::ofstream spaceInfo("Chtholly/src/Space/info/Space.chtl");
    CMODInfo info;
    info.name = "Space";
    info.version = "1.0.0";
    info.description = "Space submodule for Chtholly theme";
    info.author = "CHTL Team";
    info.license = "MIT";
    spaceInfo << info.toString();
    spaceInfo.close();
    
    // Space模块内容
    std::ofstream spaceFile("Chtholly/src/Space/src/Space.chtl");
    spaceFile << R"(// Space Submodule
[Namespace] Space
{
    [Template] @Style SpaceLayout
    {
        display: flex;
        flex-direction: column;
        gap: 20px;
        padding: 20px;
    }
    
    [Custom] @Element SpaceContainer
    {
        div
        {
            class: space-container;
            
            style
            {
                @Style SpaceLayout;
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                min-height: 100vh;
            }
        }
    }
}
)";
    spaceFile.close();
}

// 示例：演示CMOD的使用
int main() {
    // 创建示例模块
    std::cout << "=== 创建示例CMOD模块 ===" << std::endl;
    createExampleModule();
    
    // 创建上下文和生成器
    auto context = std::make_shared<CHTLContext>();
    GeneratorOptions options;
    CHTLGenerator generator(context, options);
    
    // 获取CMOD管理器
    auto cmodManager = generator.getCMODManager();
    
    // 示例1：加载和使用CMOD模块
    std::cout << "\n=== 示例1：加载CMOD模块 ===" << std::endl;
    
    // 添加当前目录到模块路径
    cmodManager->addModulePath(fs::current_path());
    
    // 加载Chtholly模块
    auto chthollyModule = cmodManager->loadModule("Chtholly");
    if (chthollyModule) {
        std::cout << "成功加载模块: " << chthollyModule->getName() << std::endl;
        std::cout << "版本: " << chthollyModule->getInfo().version << std::endl;
        std::cout << "描述: " << chthollyModule->getInfo().description << std::endl;
        
        // 列出子模块
        auto subModules = chthollyModule->getSubModuleNames();
        std::cout << "子模块: ";
        for (const auto& sub : subModules) {
            std::cout << sub << " ";
        }
        std::cout << std::endl;
    }
    
    // 示例2：导入模块内容
    std::cout << "\n=== 示例2：导入模块内容 ===" << std::endl;
    
    // 导入整个Chtholly模块
    generator.processImportStatement("[Import] @Chtl from Chtholly");
    
    // 使用模块中的模板
    generator.generateElement("div", {});
    
    // 使用ChthollyColors变量组
    generator.beginStyleBlock();
    generator.addInlineStyle("background-color", "ChthollyColors(background)");
    generator.addInlineStyle("color", "ChthollyColors(text)");
    generator.endStyleBlock();
    
    // 使用ChthollyCard元素模板
    generator.useTemplate("@Element ChthollyCard");
    
    // 使用ChthollyButton样式
    generator.generateElement("button", {});
    generator.beginStyleBlock();
    generator.beginClassStyle("my-button");
    generator.useTemplate("@Style ChthollyButton");
    generator.endClassStyle();
    generator.endStyleBlock();
    generator.generateTextNode("点击我");
    generator.closeElement();
    
    generator.closeElement(); // </div>
    
    // 示例3：导入子模块
    std::cout << "\n=== 示例3：导入子模块 ===" << std::endl;
    
    // 导入Space子模块
    generator.processImportStatement("[Import] @Chtl from Chtholly.Space");
    
    // 使用Space子模块的内容
    generator.useCustom("[Custom] @Element SpaceContainer");
    
    // 示例4：打包CMOD
    std::cout << "\n=== 示例4：打包CMOD ===" << std::endl;
    
    CMODPacker packer(context);
    packer.setSourcePath(fs::current_path());
    packer.setOutputPath(fs::current_path());
    
    if (packer.pack("Chtholly")) {
        std::cout << "成功打包Chtholly.cmod" << std::endl;
    }
    
    // 示例5：解包CMOD
    std::cout << "\n=== 示例5：解包CMOD ===" << std::endl;
    
    CMODUnpacker unpacker(context);
    if (unpacker.validateCMODFile("Chtholly.cmod")) {
        if (unpacker.unpack("Chtholly.cmod", "unpacked_Chtholly")) {
            std::cout << "成功解包到unpacked_Chtholly目录" << std::endl;
        }
    }
    
    // 示例6：创建自定义模块
    std::cout << "\n=== 示例6：创建自定义模块 ===" << std::endl;
    
    if (CMODHelper::createModuleTemplate(fs::current_path(), "MyModule")) {
        std::cout << "成功创建MyModule模块模板" << std::endl;
        
        // 修改模块信息
        std::ofstream infoFile("MyModule/info/MyModule.chtl");
        CMODInfo myInfo;
        myInfo.name = "MyModule";
        myInfo.version = "0.1.0";
        myInfo.description = "我的自定义CHTL模块";
        myInfo.author = "开发者";
        myInfo.license = "MIT";
        myInfo.dependencies = "Chtholly";  // 依赖Chtholly模块
        myInfo.minCHTLVersion = "1.0.0";
        myInfo.category = "custom";
        
        infoFile << myInfo.toString();
        
        // 添加导出表（通常由系统自动生成）
        CMODExportTable exportTable;
        exportTable.addExport("@Style", "[Template]", "MyStyle");
        exportTable.addExport("@Element", "[Custom]", "MyElement");
        
        infoFile << "\n" << exportTable.toString();
        infoFile.close();
        
        std::cout << "已更新MyModule的信息" << std::endl;
    }
    
    // 输出生成的代码
    std::cout << "\n=== 生成的HTML ===" << std::endl;
    std::cout << generator.getHTML() << std::endl;
    
    std::cout << "\n=== 生成的CSS ===" << std::endl;
    std::cout << generator.getCSS() << std::endl;
    
    // 清理创建的文件和目录
    std::cout << "\n=== 清理示例文件 ===" << std::endl;
    fs::remove_all("Chtholly");
    fs::remove_all("MyModule");
    fs::remove_all("unpacked_Chtholly");
    fs::remove("Chtholly.cmod");
    
    return 0;
}

/* 预期功能：

1. 模块结构：
   - src/：源代码目录
   - info/：模块信息目录
   - 子模块：嵌套的模块结构

2. 模块信息：
   - 基本信息（名称、版本、作者等）
   - 依赖关系
   - CHTL版本要求
   - 导出表

3. 模块使用：
   - 导入整个模块
   - 导入子模块
   - 使用模块中的模板和自定义

4. 模块打包/解包：
   - 将目录结构打包成.cmod文件
   - 解包.cmod文件到目录

*/