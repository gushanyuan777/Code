CXX = g++

CXXFLAGS = -Wall -Wextra -O2

TARGET = expression_evaluator

OBJS = main.o expression_evaluator.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp expression_evaluator.h
	$(CXX) $(CXXFLAGS) -c main.cpp

expression_evaluator.o: expression_evaluator.cpp expression_evaluator.h
	$(CXX) $(CXXFLAGS) -c expression_evaluator.cpp

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean