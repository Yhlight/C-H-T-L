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
    src/Node/Element.cpp \
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

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean