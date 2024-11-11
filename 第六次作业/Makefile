# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -std=c++11 -Wall

# 定义链接选项
LDFLAGS = 

# 定义目标文件
TARGET = test

# 定义源文件
SOURCES = test.cpp

# 定义对象文件
OBJECTS = $(SOURCES:.cpp=.o)

# 定义LaTeX文件
LATEX_FILE = report.tex

# 默认目标
all: $(TARGET) report.pdf

# 链接目标
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

# 编译源文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 编译LaTeX文档
report.pdf: $(LATEX_FILE)
	pdflatex $(LATEX_FILE)

# 清理构建产物
clean:
	rm -f $(OBJECTS) $(TARGET) report.pdf report.aux report.log

# 伪目标，避免与文件名冲突
.PHONY: all clean