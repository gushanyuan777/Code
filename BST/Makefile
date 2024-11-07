# 定义编译器和编译选项
CXX = g++
CXXFLAGS = -Wall -g

# 定义源文件和目标文件
SRC = BinarySearchTree.h main.cpp
OBJ = $(SRC:.cpp=.o)

# 定义可执行文件名
TARGET = bst_test

# 定义报告文件
REPORT = report.pdf

# 默认目标
all: $(TARGET)

# 编译可执行文件
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# 运行测试
run: $(TARGET)
	./$(TARGET)

# 编译报告
report: report.tex
	pdflatex report.tex

# 清理目标文件和可执行文件
clean:
	rm -f $(OBJ) $(TARGET)

# 清理报告文件
clean_report:
	rm -f $(REPORT)

# 伪目标
.PHONY: all run clean report clean_report