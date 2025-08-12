#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "CompilerDispatcher.h"

void printUsage(const char* programName) {
    std::cout << "用法: " << programName << " [选项] <输入文件>" << std::endl;
    std::cout << "选项:" << std::endl;
    std::cout << "  -o <文件>    指定输出文件名（默认与输入文件同名）" << std::endl;
    std::cout << "  -h           输出HTML文件" << std::endl;
    std::cout << "  -c           输出CSS文件" << std::endl;
    std::cout << "  -j           输出JavaScript文件" << std::endl;
    std::cout << "  -a           输出所有文件（HTML、CSS、JS）" << std::endl;
    std::cout << "  --minify     压缩输出" << std::endl;
    std::cout << "  --prettify   美化输出（默认）" << std::endl;
    std::cout << "  --help       显示此帮助信息" << std::endl;
    std::cout << "  --version    显示版本信息" << std::endl;
}

void printVersion() {
    std::cout << "CHTL编译器 版本 1.0.0" << std::endl;
    std::cout << "基于ANTLR4实现的超文本语言编译器" << std::endl;
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

std::string getBaseName(const std::string& filename) {
    size_t lastDot = filename.find_last_of('.');
    if (lastDot != std::string::npos) {
        return filename.substr(0, lastDot);
    }
    return filename;
}

int main(int argc, char* argv[]) {
    // 默认选项
    std::string inputFile;
    std::string outputBase;
    bool outputHTML = false;
    bool outputCSS = false;
    bool outputJS = false;
    bool minify = false;
    bool prettify = true;
    
    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "--version") == 0) {
            printVersion();
            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputBase = argv[++i];
        }
        else if (strcmp(argv[i], "-h") == 0) {
            outputHTML = true;
        }
        else if (strcmp(argv[i], "-c") == 0) {
            outputCSS = true;
        }
        else if (strcmp(argv[i], "-j") == 0) {
            outputJS = true;
        }
        else if (strcmp(argv[i], "-a") == 0) {
            outputHTML = outputCSS = outputJS = true;
        }
        else if (strcmp(argv[i], "--minify") == 0) {
            minify = true;
            prettify = false;
        }
        else if (strcmp(argv[i], "--prettify") == 0) {
            prettify = true;
            minify = false;
        }
        else if (argv[i][0] != '-') {
            inputFile = argv[i];
        }
        else {
            std::cerr << "错误: 未知选项 " << argv[i] << std::endl;
            printUsage(argv[0]);
            return 1;
        }
    }
    
    // 检查输入文件
    if (inputFile.empty()) {
        std::cerr << "错误: 未指定输入文件" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    // 如果没有指定输出选项，默认输出所有文件
    if (!outputHTML && !outputCSS && !outputJS) {
        outputHTML = outputCSS = outputJS = true;
    }
    
    // 如果没有指定输出基础名，使用输入文件名
    if (outputBase.empty()) {
        outputBase = getBaseName(inputFile);
    }
    
    try {
        // 读取输入文件
        std::string content = readFile(inputFile);
        
        // 创建编译器调度器
        CHTL::CompilerDispatcher dispatcher;
        
        // 设置配置
        if (minify) {
            dispatcher.setConfiguration("minify", "true");
        }
        if (prettify) {
            dispatcher.setConfiguration("prettify", "true");
        }
        
        // 编译
        std::cout << "正在编译 " << inputFile << "..." << std::endl;
        CHTL::CompilationResult result = dispatcher.compile(content);
        
        if (!result.success) {
            std::cerr << "编译失败！" << std::endl;
            
            // 输出错误信息
            for (const auto& error : result.errors) {
                std::cerr << "错误: " << error << std::endl;
            }
            
            // 输出警告信息
            for (const auto& warning : result.warnings) {
                std::cerr << "警告: " << warning << std::endl;
            }
            
            return 1;
        }
        
        // 输出成功
        std::cout << "编译成功！" << std::endl;
        
        // 输出警告信息
        for (const auto& warning : result.warnings) {
            std::cout << "警告: " << warning << std::endl;
        }
        
        // 写入输出文件
        if (outputHTML && !result.html.empty()) {
            std::string htmlFile = outputBase + ".html";
            writeFile(htmlFile, result.html);
            std::cout << "已生成 " << htmlFile << std::endl;
        }
        
        if (outputCSS && !result.css.empty()) {
            std::string cssFile = outputBase + ".css";
            writeFile(cssFile, result.css);
            std::cout << "已生成 " << cssFile << std::endl;
        }
        
        if (outputJS && !result.javascript.empty()) {
            std::string jsFile = outputBase + ".js";
            writeFile(jsFile, result.javascript);
            std::cout << "已生成 " << jsFile << std::endl;
        }
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
}