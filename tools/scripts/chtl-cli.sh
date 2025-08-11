#!/bin/bash

# CHTL CLI - 命令行接口包装器

set -e

# CHTL可执行文件路径
CHTL_BIN="chtl"

# 检查CHTL是否在PATH中
if ! command -v "$CHTL_BIN" &> /dev/null; then
    # 尝试使用本地构建的版本
    if [ -f "./build/chtl" ]; then
        CHTL_BIN="./build/chtl"
    else
        echo "Error: CHTL compiler not found!"
        echo "Please build CHTL first: ./scripts/build.sh"
        exit 1
    fi
fi

# 命令函数
cmd_new() {
    local project_name="$1"
    if [ -z "$project_name" ]; then
        echo "Error: Project name required"
        echo "Usage: chtl new <project-name>"
        exit 1
    fi
    
    echo "Creating new CHTL project: $project_name"
    
    # 创建项目目录结构
    mkdir -p "$project_name"/{src,components,styles,scripts,dist}
    
    # 创建主文件
    cat > "$project_name/src/main.chtl" << 'EOF'
// Main CHTL file
Import @Core from "Chtholly.Core.*"

[Config] {
    title: "My CHTL App"
    lang: "zh-CN"
}

div {
    class: "app"
    
    h1 { "Welcome to CHTL!" }
    
    p {
        "Start editing "
        code { "src/main.chtl" }
        " to begin development."
    }
    
    style {
        .app {
            max-width: 1200px;
            margin: 0 auto;
            padding: 40px;
            font-family: system-ui, -apple-system, sans-serif;
        }
        
        h1 {
            color: #67C3CC;
            text-align: center;
        }
        
        code {
            background: #f4f4f4;
            padding: 2px 6px;
            border-radius: 3px;
            font-family: monospace;
        }
    }
}
EOF
    
    # 创建package.json
    cat > "$project_name/package.json" << EOF
{
  "name": "$project_name",
  "version": "1.0.0",
  "description": "A CHTL project",
  "scripts": {
    "build": "chtl src/main.chtl -o dist",
    "dev": "chtl src/main.chtl -o dist --watch",
    "clean": "rm -rf dist/*"
  }
}
EOF
    
    # 创建README
    cat > "$project_name/README.md" << EOF
# $project_name

A CHTL (Component HTML Template Language) project.

## Getting Started

\`\`\`bash
# Build the project
npm run build

# Development mode (with watch)
npm run dev

# Clean build artifacts
npm run clean
\`\`\`

## Project Structure

- \`src/\` - Source files
- \`components/\` - Reusable components
- \`styles/\` - Global styles
- \`scripts/\` - JavaScript files
- \`dist/\` - Build output
EOF
    
    echo "Project created successfully!"
    echo "Next steps:"
    echo "  cd $project_name"
    echo "  npm run build"
}

cmd_build() {
    local input_file="$1"
    shift
    
    if [ -z "$input_file" ]; then
        # 尝试查找默认文件
        if [ -f "src/main.chtl" ]; then
            input_file="src/main.chtl"
        elif [ -f "main.chtl" ]; then
            input_file="main.chtl"
        elif [ -f "index.chtl" ]; then
            input_file="index.chtl"
        else
            echo "Error: No input file specified and no default file found"
            echo "Usage: chtl build <file.chtl> [options]"
            exit 1
        fi
    fi
    
    echo "Building: $input_file"
    "$CHTL_BIN" "$input_file" "$@"
}

cmd_watch() {
    local input_file="$1"
    shift
    
    if [ -z "$input_file" ]; then
        if [ -f "src/main.chtl" ]; then
            input_file="src/main.chtl"
        else
            echo "Error: No input file specified"
            exit 1
        fi
    fi
    
    echo "Watching: $input_file"
    echo "Press Ctrl+C to stop"
    
    # 简单的文件监视实现
    while true; do
        "$CHTL_BIN" "$input_file" "$@"
        echo "Waiting for changes..."
        
        # 使用inotifywait如果可用
        if command -v inotifywait &> /dev/null; then
            inotifywait -q -e modify,create,delete -r . --exclude "dist/|build/|\.git/"
        else
            # 否则使用简单的轮询
            sleep 2
        fi
    done
}

cmd_serve() {
    local port="${1:-8080}"
    local dir="${2:-dist}"
    
    echo "Starting development server..."
    echo "Serving: $dir"
    echo "URL: http://localhost:$port"
    
    # 尝试使用不同的HTTP服务器
    if command -v python3 &> /dev/null; then
        cd "$dir" && python3 -m http.server "$port"
    elif command -v python &> /dev/null; then
        cd "$dir" && python -m SimpleHTTPServer "$port"
    elif command -v php &> /dev/null; then
        cd "$dir" && php -S "localhost:$port"
    else
        echo "Error: No suitable HTTP server found"
        echo "Please install Python or PHP"
        exit 1
    fi
}

cmd_help() {
    cat << EOF
CHTL CLI - Component HTML Template Language Command Line Interface

Usage: chtl <command> [options]

Commands:
  new <name>        Create a new CHTL project
  build [file]      Build a CHTL file (default: src/main.chtl)
  watch [file]      Watch and rebuild on changes
  serve [port]      Start a development server (default port: 8080)
  help              Show this help message

Build Options:
  -o, --output <dir>    Output directory (default: ./dist)
  -p, --platform <name> Target platform: web, react, vue (default: web)
  --inline-styles       Inline CSS in HTML
  --inline-scripts      Inline JS in HTML
  --minify              Minify output

Examples:
  chtl new my-app           Create a new project
  chtl build                Build src/main.chtl
  chtl build app.chtl -o public
  chtl watch --inline-styles
  chtl serve 3000

For more information, visit: https://github.com/yourusername/chtl
EOF
}

# 主命令分发
case "${1:-help}" in
    new)
        shift
        cmd_new "$@"
        ;;
    build)
        shift
        cmd_build "$@"
        ;;
    watch)
        shift
        cmd_watch "$@"
        ;;
    serve)
        shift
        cmd_serve "$@"
        ;;
    help|--help|-h)
        cmd_help
        ;;
    *)
        # 如果没有子命令，假设是build
        if [[ "$1" == *.chtl ]]; then
            cmd_build "$@"
        else
            echo "Error: Unknown command: $1"
            echo "Run 'chtl help' for usage information"
            exit 1
        fi
        ;;
esac