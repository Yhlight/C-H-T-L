# CHTL编译器 Makefile

.PHONY: all clean build test install help

# 默认目标
all: build

# 构建项目
build:
	@echo "🚀 构建CHTL编译器..."
	@mkdir -p build
	@cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cd build && make -j$(shell nproc)
	@echo "✅ 构建完成!"

# 调试构建
debug:
	@echo "🐛 构建调试版本..."
	@mkdir -p build
	@cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug
	@cd build && make -j$(shell nproc)
	@echo "✅ 调试构建完成!"

# 清理构建文件
clean:
	@echo "🧹 清理构建文件..."
	@rm -rf build
	@echo "✅ 清理完成!"

# 运行测试
test: build
	@echo "🧪 运行测试..."
	@cd build && make test
	@echo "✅ 测试完成!"

# 安装
install: build
	@echo "📦 安装CHTL编译器..."
	@cd build && sudo make install
	@echo "✅ 安装完成!"

# 卸载
uninstall:
	@echo "🗑️  卸载CHTL编译器..."
	@sudo rm -f /usr/local/bin/chtl-compiler
	@sudo rm -rf /usr/local/include/chtl-compiler
	@sudo rm -rf /usr/local/share/chtl-compiler
	@echo "✅ 卸载完成!"

# 运行示例
example: build
	@echo "📝 运行示例..."
	@cd build && ./chtl-compiler ../examples/simple.chtl
	@echo "✅ 示例运行完成!"

# 显示帮助
help:
	@echo "CHTL编译器 Makefile 帮助"
	@echo ""
	@echo "可用目标:"
	@echo "  all      - 构建项目 (默认)"
	@echo "  build    - 构建项目"
	@echo "  debug    - 构建调试版本"
	@echo "  clean    - 清理构建文件"
	@echo "  test     - 运行测试"
	@echo "  install  - 安装编译器"
	@echo "  uninstall- 卸载编译器"
	@echo "  example  - 运行示例"
	@echo "  help     - 显示此帮助信息"
	@echo ""
	@echo "示例:"
	@echo "  make build    # 构建项目"
	@echo "  make test     # 运行测试"
	@echo "  make install  # 安装编译器"