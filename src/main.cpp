#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <memory>
#include "Lexer/StandardLexer.h"
#include "Parser/StandardParser.h"
#include "Generator/Generator.h"
#include "Context/StandardContext.h"
#include "Context/EnhancedContext.h"
#include "Error/ErrorHandler.h"
#include "Utils/FileUtils.h"
#include "Cmod/CmodPacker.h"

namespace fs = std::filesystem;

void printUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " [options] <input-file>\n";
    std::cout << "Options:\n";
    std::cout << "  -o, --output <dir>      Output directory (default: ./dist)\n";
    std::cout << "  -p, --platform <name>   Target platform: web, react, vue (default: web)\n";
    std::cout << "  --inline-styles         Inline CSS in HTML\n";
    std::cout << "  --inline-scripts        Inline JS in HTML\n";
    std::cout << "  --no-scope-styles       Disable CSS scoping\n";
    std::cout << "  --minify                Minify output\n";
    std::cout << "  --source-map            Generate source maps\n";
    std::cout << "  --pack-cmod <dir>       Pack a directory as CMOD module\n";
    std::cout << "  -h, --help              Show this help message\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    // 解析命令行参数
    chtl::GeneratorOptions options;
    std::string inputFile;
    std::string packCmodDir;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            printUsage(argv[0]);
            return 0;
        } else if (arg == "--pack-cmod") {
            if (i + 1 < argc) {
                packCmodDir = argv[++i];
            } else {
                std::cerr << "Error: Missing directory for --pack-cmod\n";
                return 1;
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                options.outputPath = argv[++i];
            } else {
                std::cerr << "Error: Missing output directory\n";
                return 1;
            }
        } else if (arg == "-p" || arg == "--platform") {
            if (i + 1 < argc) {
                options.targetPlatform = argv[++i];
            } else {
                std::cerr << "Error: Missing platform name\n";
                return 1;
            }
        } else if (arg == "--inline-styles") {
            options.inlineStyles = true;
        } else if (arg == "--inline-scripts") {
            options.inlineScripts = true;
        } else if (arg == "--no-scope-styles") {
            options.scopeStyles = false;
        } else if (arg == "--minify") {
            options.minify = true;
        } else if (arg == "--source-map") {
            options.sourceMap = true;
        } else if (arg[0] != '-') {
            inputFile = arg;
        } else {
            std::cerr << "Error: Unknown option: " << arg << "\n";
            return 1;
        }
    }
    
    if (inputFile.empty()) {
        std::cerr << "Error: No input file specified\n";
        printUsage(argv[0]);
        return 1;
    }
    
    // 如果是打包CMOD模式
    if (!packCmodDir.empty()) {
        chtl::CmodPackOptions packOptions;
        packOptions.verbose = true;
        
        chtl::CmodPacker packer(packOptions);
        auto result = packer.pack(packCmodDir);
        
        if (result.success) {
            std::cout << "Successfully created CMOD: " << result.outputFile << "\n";
            std::cout << "Files packed: " << result.fileCount << "\n";
            std::cout << "Size: " << result.compressedSize << " bytes\n";
        } else {
            std::cerr << "Error: " << result.errorMessage << "\n";
            return 1;
        }
        
        return 0;
    }
    
    // 读取输入文件
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file: " << inputFile << "\n";
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();
    file.close();
    
    // 创建增强上下文（带错误处理）
    auto context = chtl::createEnhancedContext();
    context->setSourceFile(inputFile);
    context->setSourceCode(input);
    
    // 词法分析
    std::cout << "Lexing...\n";
    auto lexer = std::make_shared<chtl::StandardLexer>();
    
    // 初始化词法分析器
    std::unique_ptr<std::istream> stream = std::make_unique<std::istringstream>(input);
    if (!lexer->initialize(std::move(stream), inputFile)) {
        std::cerr << "Failed to initialize lexer\n";
        return 1;
    }
    
    // 设置上下文
    lexer->setContext(context);
    
    // 语法分析
    std::cout << "Parsing...\n";
    chtl::StandardParser parser(lexer, context);
    
    // 检测是否是CMOD文件并设置模式
    bool isCmod = chtl::FileUtils::isCmodFile(inputFile);
    parser.setCmodMode(isCmod);
    
    if (isCmod) {
        std::cout << "Note: Parsing as CMOD file ([Info] and [Export] blocks enabled)\n";
    }
    
    auto ast = parser.parse();
    
    if (!ast || context->hasErrors()) {
        std::cerr << "\n" << context->formatErrors() << "\n";
        std::cerr << context->formatSummary() << "\n";
        return 1;
    }
    
    // 代码生成
    std::cout << "Generating code for platform: " << options.targetPlatform << "\n";
    auto generator = chtl::createGenerator(options.targetPlatform, options);
    auto result = generator->generate(ast);
    
    // 检查生成错误
    if (!result.errors.empty()) {
        std::cerr << "Generation errors:\n";
        for (const auto& error : result.errors) {
            std::cerr << "  " << error << "\n";
        }
        return 1;
    }
    
    // 显示警告
    if (!result.warnings.empty()) {
        std::cout << "Warnings:\n";
        for (const auto& warning : result.warnings) {
            std::cout << "  " << warning << "\n";
        }
    }
    
    // 创建输出目录
    fs::create_directories(options.outputPath);
    
    // 写入输出文件
    if (options.inlineStyles && options.inlineScripts) {
        // 所有内容都内联在HTML中
        std::string outputFile = fs::path(options.outputPath) / "index.html";
        std::ofstream out(outputFile);
        if (!out.is_open()) {
            std::cerr << "Error: Cannot create output file: " << outputFile << "\n";
            return 1;
        }
        out << result.html;
        out.close();
        std::cout << "Generated: " << outputFile << "\n";
    } else {
        // 分别输出文件
        
        // HTML
        std::string htmlFile = fs::path(options.outputPath) / "index.html";
        std::ofstream htmlOut(htmlFile);
        if (!htmlOut.is_open()) {
            std::cerr << "Error: Cannot create HTML file: " << htmlFile << "\n";
            return 1;
        }
        htmlOut << result.html;
        htmlOut.close();
        std::cout << "Generated: " << htmlFile << "\n";
        
        // CSS
        if (!result.css.empty() && !options.inlineStyles) {
            std::string cssFile = fs::path(options.outputPath) / "styles.css";
            std::ofstream cssOut(cssFile);
            if (!cssOut.is_open()) {
                std::cerr << "Error: Cannot create CSS file: " << cssFile << "\n";
                return 1;
            }
            cssOut << result.css;
            cssOut.close();
            std::cout << "Generated: " << cssFile << "\n";
        }
        
        // JavaScript
        if (!result.js.empty() && !options.inlineScripts) {
            std::string jsFile = fs::path(options.outputPath) / "app.js";
            std::ofstream jsOut(jsFile);
            if (!jsOut.is_open()) {
                std::cerr << "Error: Cannot create JS file: " << jsFile << "\n";
                return 1;
            }
            jsOut << result.js;
            jsOut.close();
            std::cout << "Generated: " << jsFile << "\n";
        }
        
        // Source Map
        if (!result.sourceMap.empty()) {
            std::string mapFile = fs::path(options.outputPath) / "app.js.map";
            std::ofstream mapOut(mapFile);
            if (!mapOut.is_open()) {
                std::cerr << "Error: Cannot create source map file: " << mapFile << "\n";
                return 1;
            }
            mapOut << result.sourceMap;
            mapOut.close();
            std::cout << "Generated: " << mapFile << "\n";
        }
    }
    
    std::cout << "Compilation completed successfully!\n";
    return 0;
}