# Makefile for Graph Coloring Problem

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = graph_coloring
SOURCE = graph_coloring.cpp
TESTS = tests/test1.in tests/test2.in tests/test3.in tests/test4.in tests/test5.in

.PHONY: all clean test run

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

test: $(TARGET)
	@echo "Running all tests..."
	@for test in $(TESTS); do \
		echo ""; \
		echo "=== $$test ==="; \
		./$(TARGET) < $$test; \
	done

run: $(TARGET)
	@echo "Enter graph data (N M, then M edges):"
	./$(TARGET)

clean:
	rm -f $(TARGET)

help:
	@echo "Available targets:"
	@echo "  make         - Compile the program"
	@echo "  make test    - Run all test cases"
	@echo "  make run     - Run interactively"
	@echo "  make clean   - Remove compiled files"
	@echo "  make help    - Show this help message"
