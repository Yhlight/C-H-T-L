// CHTL Compiler Main Entry Point
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstring>
#include "chtl/CHTLContext.h"
#include "chtl/CHTLGenerator.h"
#include "chtl/CHTLUnifiedScanner.h"
#include "chtl/CHTLCMOD.h"
#include "chtl/scanner/ScannerParserIntegration.h"
#include "chtl/CHTLTreeVisitor.h"

namespace fs = std::filesystem;

void printUsage(const char* programName) {
    std::cout << "CHTL Compiler v1.0.0" << std::endl;
    std::cout << "Usage: " << programName << " [options] <input-file>" << std::endl;
    std::cout << "\nOptions:" << std::endl;
    std::cout << "  -o <output>    Specify output file (default: a.html)" << std::endl;
    std::cout << "  -m <dir>       Module search directory (default: ./module)" << std::endl;
    std::cout << "  --no-optimize  Disable optimization" << std::endl;
    std::cout << "  --verbose      Verbose output" << std::endl;
    std::cout << "  --help         Show this help message" << std::endl;
    std::cout << "\nExamples:" << std::endl;
    std::cout << "  " << programName << " input.chtl" << std::endl;
    std::cout << "  " << programName << " -o output.html input.chtl" << std::endl;
    std::cout << "  " << programName << " -m /usr/share/chtl/module input.chtl" << std::endl;
}

int main(int argc, char* argv[]) {
    // 解析命令行参数
    std::string inputFile;
    std::string outputFile = "a.html";
    std::string moduleDir = "./module";
    bool optimize = true;
    bool verbose = false;
    
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            moduleDir = argv[++i];
        } else if (strcmp(argv[i], "--no-optimize") == 0) {
            optimize = false;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printUsage(argv[0]);
            return 0;
        } else if (argv[i][0] != '-') {
            inputFile = argv[i];
        } else {
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            printUsage(argv[0]);
            return 1;
        }
    }
    
    if (inputFile.empty()) {
        std::cerr << "Error: No input file specified" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    // 检查输入文件是否存在
    if (!fs::exists(inputFile)) {
        std::cerr << "Error: Input file does not exist: " << inputFile << std::endl;
        return 1;
    }
    
    try {
        // 读取输入文件
        std::ifstream ifs(inputFile);
        if (!ifs) {
            std::cerr << "Error: Cannot open input file: " << inputFile << std::endl;
            return 1;
        }
        
        std::string content((std::istreambuf_iterator<char>(ifs)),
                           std::istreambuf_iterator<char>());
        ifs.close();
        
        if (verbose) {
            std::cout << "Processing: " << inputFile << std::endl;
            std::cout << "Output: " << outputFile << std::endl;
            std::cout << "Module directory: " << moduleDir << std::endl;
        }
        
        // 创建CHTL上下文
        auto context = std::make_shared<chtl::CHTLContext>();
        
        // 设置模块搜索路径
        if (fs::exists(moduleDir)) {
            // TODO: 添加模块路径到上下文
            if (verbose) {
                std::cout << "Module directory found: " << moduleDir << std::endl;
            }
        }
        
        // 创建统一扫描器
        chtl::CHTLUnifiedScanner scanner(content, context);
        
        // 配置扫描器
        chtl::ScannerConfig config;
        config.processGenerativeComments = true;
        config.expandStyleGroups = true;
        config.expandVarGroups = true;
        scanner.setConfig(config);
        
        // 执行扫描
        if (verbose) {
            std::cout << "Scanning CHTL source..." << std::endl;
        }
        scanner.scan();
        
        // 创建生成器
        chtl::CHTLGenerator generator;
        
        // 配置生成器选项
        chtl::CHTLGenerator::GeneratorOptions options;
        options.enableOptimization = optimize;
        options.minifyOutput = optimize;
        options.generateComments = !optimize;
        generator.setOptions(options);
        
        // 使用Scanner-Parser集成进行解析
        scanner::ScannerParserIntegration integration(context);
        integration.setConfigurationEnabled(true);
        
        auto parseResult = integration.parse(content, "");  // 使用content而不是input
        
        if (!parseResult.success) {
            std::cerr << "Parse error: " << parseResult.errorMessage << std::endl;
            return 1;
        }
        
        // 使用解析树生成输出
        chtl::CHTLTreeVisitor visitor(context);
        if (parseResult.chtlTree) {
            visitor.visit(parseResult.chtlTree);
        }
        
        // 生成最终输出
        std::string html = generator.getHTML();
        std::string css = generator.getCSS();
        std::string js = generator.getJS();
        
        // 组合最终输出
        std::ostringstream output;
        output << "<!DOCTYPE html>\n";
        output << "<html>\n";
        output << "<head>\n";
        output << "    <meta charset=\"UTF-8\">\n";
        output << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
        if (!css.empty()) {
            output << "    <style>\n" << css << "\n    </style>\n";
        }
        output << "</head>\n";
        output << "<body>\n";
        output << html;
        if (!js.empty()) {
            output << "    <script>\n" << js << "\n    </script>\n";
        }
        output << "</body>\n";
        output << "</html>\n";
        
        // 写入输出文件
        std::ofstream ofs(outputFile);
        if (!ofs) {
            std::cerr << "Error: Cannot create output file: " << outputFile << std::endl;
            return 1;
        }
        
        ofs << output.str();
        ofs.close();
        
        if (verbose) {
            std::cout << "Compilation successful!" << std::endl;
            std::cout << "Output written to: " << outputFile << std::endl;
        }
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}