#include "v2/Parser/ChtlParser.h"
#include "v2/Generator/ChtlGenerator.h"
#include "v2/Import/ImportSystem.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;
using namespace chtl::v2;

// 版本信息
const char* VERSION = "2.0.0";
const char* BUILD_DATE = __DATE__;

// 显示帮助信息
void showHelp(const char* programName) {
    std::cout << "CHTL Compiler v" << VERSION << " (built " << BUILD_DATE << ")\n";
    std::cout << "\nUsage: " << programName << " [command] [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  compile <input>     Compile a CHTL file\n";
    std::cout << "  help               Show this help message\n";
    std::cout << "  version            Show version information\n\n";
    std::cout << "Options:\n";
    std::cout << "  -o, --output <dir>  Output directory (default: ./output)\n";
    std::cout << "  -v, --verbose       Enable verbose output\n";
    std::cout << "  --no-minify        Disable output minification\n";
    std::cout << "  --source-map       Generate source maps\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " compile index.chtl\n";
    std::cout << "  " << programName << " compile src/app.chtl -o dist/\n";
    std::cout << "  " << programName << " compile component.chtl --verbose\n";
}

// 显示版本信息
void showVersion() {
    std::cout << "CHTL Compiler v" << VERSION << "\n";
    std::cout << "Built on " << BUILD_DATE << "\n";
    std::cout << "Copyright (c) 2024 CHTL Project\n";
}

// 读取文件内容
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    return content;
}

// 写入文件
void writeFile(const std::string& path, const std::string& content) {
    // 创建目录
    fs::path filePath(path);
    fs::create_directories(filePath.parent_path());
    
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot write file: " + path);
    }
    
    file << content;
}

// 编译选项
struct CompileOptions {
    std::string inputFile;
    std::string outputDir = "./output";
    bool verbose = false;
    bool minify = true;
    bool sourceMap = false;
};

// 解析命令行参数
CompileOptions parseArgs(int argc, char* argv[]) {
    CompileOptions options;
    
    // 跳过程序名和命令
    int i = 2;
    
    // 输入文件
    if (i < argc && argv[i][0] != '-') {
        options.inputFile = argv[i++];
    }
    
    // 解析选项
    while (i < argc) {
        std::string arg = argv[i];
        
        if (arg == "-o" || arg == "--output") {
            if (++i >= argc) {
                throw std::runtime_error("Missing output directory");
            }
            options.outputDir = argv[i];
        } else if (arg == "-v" || arg == "--verbose") {
            options.verbose = true;
        } else if (arg == "--no-minify") {
            options.minify = false;
        } else if (arg == "--source-map") {
            options.sourceMap = true;
        } else {
            throw std::runtime_error("Unknown option: " + arg);
        }
        
        i++;
    }
    
    if (options.inputFile.empty()) {
        throw std::runtime_error("No input file specified");
    }
    
    return options;
}

// 编译 CHTL 文件
void compile(const CompileOptions& options) {
    if (options.verbose) {
        std::cout << "Compiling: " << options.inputFile << "\n";
        std::cout << "Output directory: " << options.outputDir << "\n";
    }
    
    try {
        // 读取源文件
        std::string source = readFile(options.inputFile);
        
        // 解析
        if (options.verbose) {
            std::cout << "Parsing...\n";
        }
        
        ChtlParser parser;
        auto parseResult = parser.parse(source);
        
        // 检查解析错误
        if (!parseResult.errors.empty()) {
            std::cerr << "Parse errors:\n";
            for (const auto& error : parseResult.errors) {
                std::cerr << "  " << error << "\n";
            }
            
            if (!parseResult.ast) {
                throw std::runtime_error("Failed to parse CHTL file");
            }
        }
        
        // 显示警告
        if (!parseResult.warnings.empty() && options.verbose) {
            std::cout << "Warnings:\n";
            for (const auto& warning : parseResult.warnings) {
                std::cout << "  " << warning << "\n";
            }
        }
        
        // 生成代码
        if (options.verbose) {
            std::cout << "Generating code...\n";
        }
        
        ChtlGenerator generator;
        GeneratorOptions genOptions;
        genOptions.minify = options.minify;
        // Source map generation not yet implemented
        generator.setOptions(genOptions);
        
        auto genResult = generator.generate(parseResult.ast);
        
        // 检查生成错误
        if (!genResult.errors.empty()) {
            std::cerr << "Generation errors:\n";
            for (const auto& error : genResult.errors) {
                std::cerr << "  " << error << "\n";
            }
        }
        
        // 确定输出文件名
        fs::path inputPath(options.inputFile);
        std::string baseName = inputPath.stem().string();
        
        // 写入文件
        if (options.verbose) {
            std::cout << "Writing output files...\n";
        }
        
        // HTML
        if (!genResult.html.empty()) {
            std::string htmlPath = options.outputDir + "/" + baseName + ".html";
            writeFile(htmlPath, genResult.html);
            if (options.verbose) {
                std::cout << "  Wrote: " << htmlPath << "\n";
            }
        }
        
        // CSS
        if (!genResult.css.empty()) {
            std::string cssPath = options.outputDir + "/styles.css";
            writeFile(cssPath, genResult.css);
            if (options.verbose) {
                std::cout << "  Wrote: " << cssPath << "\n";
            }
        }
        
        // JavaScript
        if (!genResult.javascript.empty()) {
            std::string jsPath = options.outputDir + "/scripts.js";
            writeFile(jsPath, genResult.javascript);
            if (options.verbose) {
                std::cout << "  Wrote: " << jsPath << "\n";
            }
        }
        
        std::cout << "Compilation successful!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        throw;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showHelp(argv[0]);
        return 1;
    }
    
    std::string command = argv[1];
    
    try {
        if (command == "compile") {
            CompileOptions options = parseArgs(argc, argv);
            compile(options);
        } else if (command == "help" || command == "--help" || command == "-h") {
            showHelp(argv[0]);
        } else if (command == "version" || command == "--version" || command == "-v") {
            showVersion();
        } else {
            std::cerr << "Unknown command: " << command << "\n";
            std::cerr << "Run '" << argv[0] << " help' for usage information.\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}