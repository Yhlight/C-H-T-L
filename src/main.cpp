#include "compiler/MainCompiler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

void printUsage(const char* programName) {
    std::cout << "CHTL编译器 v1.0.0\n";
    std::cout << "用法: " << programName << " [选项] <输入文件>\n\n";
    std::cout << "选项:\n";
    std::cout << "  -o, --output <目录>    指定输出目录 (默认: ./output)\n";
    std::cout << "  -h, --html <文件>      指定HTML输出文件\n";
    std::cout << "  -c, --css <文件>       指定CSS输出文件\n";
    std::cout << "  -j, --js <文件>        指定JavaScript输出文件\n";
    std::cout << "  --minify               压缩输出文件\n";
    std::cout << "  --optimize             优化输出 (默认启用)\n";
    std::cout << "  --debug                启用调试模式\n";
    std::cout << "  --help                 显示此帮助信息\n";
    std::cout << "  --version              显示版本信息\n\n";
    std::cout << "示例:\n";
    std::cout << "  " << programName << " input.chtl\n";
    std::cout << "  " << programName << " -o ./dist input.chtl\n";
    std::cout << "  " << programName << " -h index.html -c style.css -j script.js input.chtl\n";
}

void printVersion() {
    std::cout << "CHTL编译器 v1.0.0\n";
    std::cout << "基于ANTLR4实现的CHTL、CSS、JavaScript和CHTL JS编译器\n";
    std::cout << "MIT许可证 - CHTL Team\n";
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filename);
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    return content;
}

void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法创建文件: " + filename);
    }
    
    file << content;
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string inputFile;
    std::string outputDir = "./output";
    std::string htmlFile = "index.html";
    std::string cssFile = "style.css";
    std::string jsFile = "script.js";
    
    std::map<std::string, std::string> options;
    options["optimize"] = "true";
    options["minify"] = "false";
    options["debug"] = "false";
    
    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            return 0;
        } else if (arg == "--version") {
            printVersion();
            return 0;
        } else if (arg == "--output" || arg == "-o") {
            if (i + 1 < argc) {
                outputDir = argv[++i];
            } else {
                std::cerr << "错误: --output 选项需要参数\n";
                return 1;
            }
        } else if (arg == "--html") {
            if (i + 1 < argc) {
                htmlFile = argv[++i];
            } else {
                std::cerr << "错误: --html 选项需要参数\n";
                return 1;
            }
        } else if (arg == "--css") {
            if (i + 1 < argc) {
                cssFile = argv[++i];
            } else {
                std::cerr << "错误: --css 选项需要参数\n";
                return 1;
            }
        } else if (arg == "--js") {
            if (i + 1 < argc) {
                jsFile = argv[++i];
            } else {
                std::cerr << "错误: --js 选项需要参数\n";
                return 1;
            }
        } else if (arg == "--minify") {
            options["minify"] = "true";
        } else if (arg == "--optimize") {
            options["optimize"] = "true";
        } else if (arg == "--debug") {
            options["debug"] = "true";
        } else if (arg[0] != '-') {
            inputFile = arg;
        } else {
            std::cerr << "未知选项: " << arg << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }
    
    if (inputFile.empty()) {
        std::cerr << "错误: 请指定输入文件\n";
        printUsage(argv[0]);
        return 1;
    }
    
    try {
        // 读取输入文件
        std::cout << "正在读取文件: " << inputFile << std::endl;
        std::string sourceCode = readFile(inputFile);
        
        // 创建编译器
        chtl::MainCompiler compiler;
        compiler.setOptions(options);
        
        // 编译代码
        std::cout << "正在编译..." << std::endl;
        if (!compiler.compile(sourceCode)) {
            std::cerr << "编译失败: " << compiler.getError() << std::endl;
            return 1;
        }
        
        // 获取编译结果
        std::string html = compiler.getHTML();
        std::string css = compiler.getCSS();
        std::string js = compiler.getJavaScript();
        
        // 创建输出目录
        std::string cmd = "mkdir -p " + outputDir;
        system(cmd.c_str());
        
        // 写入输出文件
        std::string htmlPath = outputDir + "/" + htmlFile;
        std::string cssPath = outputDir + "/" + cssFile;
        std::string jsPath = outputDir + "/" + jsFile;
        
        if (!html.empty()) {
            writeFile(htmlPath, html);
            std::cout << "HTML输出: " << htmlPath << std::endl;
        }
        
        if (!css.empty()) {
            writeFile(cssPath, css);
            std::cout << "CSS输出: " << cssPath << std::endl;
        }
        
        if (!js.empty()) {
            writeFile(jsPath, js);
            std::cout << "JavaScript输出: " << jsPath << std::endl;
        }
        
        // 显示统计信息
        auto stats = compiler.getStats();
        std::cout << "\n编译完成!\n";
        std::cout << "统计信息:\n";
        for (const auto& stat : stats) {
            std::cout << "  " << stat.first << ": " << stat.second << "\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}