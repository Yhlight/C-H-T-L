CXX = g++
CXXFLAGS = -std=c++17 -I./include -O2 -Wall
LDFLAGS = -lstdc++fs -ldl

# 核心源文件
SOURCES = \
    src/main-simple.cpp \
    src/Lexer/StandardLexer.cpp \
    src/Parser/StandardParser.cpp \
    src/Generator/WebGenerator.cpp \
    src/Context/ChtlContext.cpp \
    src/Context/BasicContext.cpp \
    src/Node/Node.cpp \
    src/Node/Template.cpp \
    src/Node/Custom.cpp \
    src/Node/Style.cpp \
    src/Node/Script.cpp \
    src/Node/Comment.cpp \
    src/Node/Import.cpp \
    src/Node/Export.cpp \
    src/Node/Config.cpp \
    src/Node/Info.cpp \
    src/Node/Operate.cpp \
    src/Node/Origin.cpp \
    src/Node/Namespace.cpp \
    src/Node/Delete.cpp \
    src/Loader/ImportResolver.cpp \
    src/CJmod/CJmodLoader.cpp \
    src/CJmod/CJmodProcessor.cpp

# 目标
TARGET = chtl

.PHONY: all build clean test install format lint docs docker-build docker-test

# Default target
all: build

# Build the project
build:
	@mkdir -p build
	@cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cd build && make -j4

# Debug build
debug:
	@mkdir -p build-debug
	@cd build-debug && cmake .. -DCMAKE_BUILD_TYPE=Debug
	@cd build-debug && make -j4

# Clean build artifacts
clean:
	@rm -rf build build-debug

# Run tests
test: build
	@echo "Running unit tests..."
	@cd build && ctest --output-on-failure
	@echo "Running integration tests..."
	@./scripts/run-tests.sh

# Install to system
install: build
	@cd build && sudo make install

# Format code
format:
	@echo "Formatting C++ code..."
	@find include src -name "*.h" -o -name "*.cpp" | xargs clang-format-14 -i
	@echo "Code formatting complete."

# Run linters
lint:
	@echo "Running clang-tidy..."
	@cd build && run-clang-tidy-14 -p .
	@echo "Running cppcheck..."
	@cppcheck --enable=all --inconclusive --std=c++17 -I include src

# Generate documentation
docs:
	@echo "Generating documentation..."
	@doxygen Doxyfile

# Build Docker image
docker-build:
	@docker build -t chtl:latest .

# Build development Docker image
docker-dev:
	@docker build -f Dockerfile.dev -t chtl:dev .

# Run tests in Docker
docker-test: docker-build
	@docker run --rm -v $(PWD)/test:/workspace chtl:latest test-var-function-fixed.chtl -o output

# Start development container
dev:
	@docker-compose run --rm chtl-dev

# Package for distribution
package: build
	@mkdir -p dist
	@cp build/chtl dist/
	@cp -r modules dist/
	@tar -czf dist/chtl-$(shell git describe --tags --always).tar.gz -C dist chtl modules
	@echo "Package created: dist/chtl-$(shell git describe --tags --always).tar.gz"

# Check code coverage
coverage:
	@mkdir -p build-coverage
	@cd build-coverage && cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage"
	@cd build-coverage && make
	@cd build-coverage && ctest
	@lcov --capture --directory build-coverage --output-file coverage.info
	@lcov --remove coverage.info '/usr/*' --output-file coverage.info
	@lcov --list coverage.info

# Quick compile and test cycle
quick: build
	@./build/chtl test-var-function-fixed.chtl -o test-output
	@cat test-output/index.html