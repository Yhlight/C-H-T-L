#include "v2/Parser/ChtlParser.h"
#include "v2/Generator/ChtlGenerator.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace chtl::v2;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input.chtl> <output-dir>\n";
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputDir = argv[2];
    
    // 读取输入文件
    std::ifstream file(inputFile);
    if (!file) {
        std::cerr << "Failed to open file: " << inputFile << "\n";
        return 1;
    }
    
    std::string input((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
    file.close();
    
    // 创建解析器
    ChtlParser parser;
    
    std::cout << "=== Parsing " << inputFile << " ===\n";
    ParseResult parseResult = parser.parse(input);
    
    if (!parseResult.success) {
        std::cerr << "\n❌ Parse failed!\n";
        for (const auto& error : parseResult.errors) {
            std::cerr << "  Error: " << error << "\n";
        }
        return 1;
    }
    
    std::cout << "✅ Parse successful!\n";
    
    // 打印警告
    if (!parseResult.warnings.empty()) {
        std::cout << "\n⚠️  Warnings:\n";
        for (const auto& warning : parseResult.warnings) {
            std::cout << "  " << warning << "\n";
        }
    }
    
    // 创建生成器
    ChtlGenerator generator;
    GeneratorOptions genOptions;
    genOptions.minify = false;
    genOptions.inlineStyles = false;
    genOptions.inlineScripts = false;
    generator.setOptions(genOptions);
    
    std::cout << "\n=== Generating code ===\n";
    GenerateResult genResult = generator.generate(parseResult.ast);
    
    if (!genResult.success) {
        std::cerr << "\n❌ Generation failed!\n";
        for (const auto& error : genResult.errors) {
            std::cerr << "  Error: " << error << "\n";
        }
        return 1;
    }
    
    std::cout << "✅ Generation successful!\n";
    
    // 打印生成器警告
    if (!genResult.warnings.empty()) {
        std::cout << "\n⚠️  Warnings:\n";
        for (const auto& warning : genResult.warnings) {
            std::cout << "  " << warning << "\n";
        }
    }
    
    // 创建输出目录
    try {
        fs::create_directories(outputDir);
    } catch (const std::exception& e) {
        std::cerr << "Failed to create output directory: " << e.what() << "\n";
        return 1;
    }
    
    // 写入 HTML 文件
    if (!genResult.html.empty()) {
        std::string htmlPath = outputDir + "/index.html";
        std::ofstream htmlFile(htmlPath);
        if (htmlFile) {
            // 如果有 CSS/JS 文件，添加引用
            if (!genOptions.inlineStyles && !genResult.css.empty()) {
                genResult.html = "<link rel=\"stylesheet\" href=\"" + 
                               genOptions.cssFileName + "\">\n" + genResult.html;
            }
            if (!genOptions.inlineScripts && !genResult.javascript.empty()) {
                genResult.html += "\n<script src=\"" + 
                                genOptions.jsFileName + "\"></script>";
            }
            
            htmlFile << genResult.html;
            htmlFile.close();
            std::cout << "\n✅ Written: " << htmlPath << "\n";
        } else {
            std::cerr << "Failed to write HTML file\n";
        }
    }
    
    // 写入 CSS 文件
    if (!genOptions.inlineStyles && !genResult.css.empty()) {
        std::string cssPath = outputDir + "/" + genOptions.cssFileName;
        std::ofstream cssFile(cssPath);
        if (cssFile) {
            cssFile << genResult.css;
            cssFile.close();
            std::cout << "✅ Written: " << cssPath << "\n";
        } else {
            std::cerr << "Failed to write CSS file\n";
        }
    }
    
    // 写入 JS 文件
    if (!genOptions.inlineScripts && !genResult.javascript.empty()) {
        std::string jsPath = outputDir + "/" + genOptions.jsFileName;
        std::ofstream jsFile(jsPath);
        if (jsFile) {
            jsFile << genResult.javascript;
            jsFile.close();
            std::cout << "✅ Written: " << jsPath << "\n";
        } else {
            std::cerr << "Failed to write JS file\n";
        }
    }
    
    // 输出统计
    std::cout << "\n=== Statistics ===\n";
    std::cout << "HTML size: " << genResult.html.size() << " bytes\n";
    std::cout << "CSS size: " << genResult.css.size() << " bytes\n";
    std::cout << "JS size: " << genResult.javascript.size() << " bytes\n";
    
    // CSS 分析结果
    if (!parseResult.cssResults.empty()) {
        std::cout << "\n=== CSS Analysis ===\n";
        int totalRules = 0;
        int totalAtRules = 0;
        for (const auto& css : parseResult.cssResults) {
            totalRules += css.rules.size();
            totalAtRules += css.atRules.size();
        }
        std::cout << "CSS rules: " << totalRules << "\n";
        std::cout << "CSS @rules: " << totalAtRules << "\n";
    }
    
    // JS 分析结果
    if (!parseResult.jsResults.empty()) {
        std::cout << "\n=== JS Analysis ===\n";
        int totalVars = 0;
        int totalFuncs = 0;
        for (const auto& js : parseResult.jsResults) {
            totalVars += js.variables.size();
            totalFuncs += js.functions.size();
        }
        std::cout << "JS variables: " << totalVars << "\n";
        std::cout << "JS functions: " << totalFuncs << "\n";
    }
    
    std::cout << "\n✅ Compilation complete!\n";
    
    return 0;
}