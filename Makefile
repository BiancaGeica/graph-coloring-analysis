# Makefile for Graph Coloring Problem (Pure C Implementation)

CC = gcc
CFLAGS = -std=c99 -O2 -Wall -Wextra
TARGETS = backtracking greedy
SOURCES = backtracking.c greedy.c
HEADER = graph_coloring.h
TESTS = tests/test1.in tests/test2.in tests/test3.in tests/test4.in tests/test5.in

.PHONY: all clean test test-backtracking test-greedy run-backtracking run-greedy help

all: $(TARGETS)

backtracking: backtracking.c $(HEADER)
	$(CC) $(CFLAGS) -o backtracking backtracking.c

greedy: greedy.c $(HEADER)
	$(CC) $(CFLAGS) -o greedy greedy.c

test: $(TARGETS)
	@echo "Running all tests..."
	@for test in $(TESTS); do \
		echo ""; \
		echo "=== $$test ==="; \
		./backtracking < $$test; \
		./greedy < $$test; \
	done

test-backtracking: backtracking
	@echo "Running backtracking tests..."
	@for test in $(TESTS); do \
		echo ""; \
		echo "=== $$test ==="; \
		./backtracking < $$test; \
	done

test-greedy: greedy
	@echo "Running greedy tests..."
	@for test in $(TESTS); do \
		echo ""; \
		echo "=== $$test ==="; \
		./greedy < $$test; \
	done

run-backtracking: backtracking
	@echo "Enter graph data (N M, then M edges):"
	./backtracking

run-greedy: greedy
	@echo "Enter graph data (N M, then M edges):"
	./greedy

clean:
	rm -f $(TARGETS)

help:
	@echo "Available targets:"
	@echo "  make                  - Compile both programs"
	@echo "  make backtracking     - Compile backtracking program"
	@echo "  make greedy           - Compile greedy program"
	@echo "  make test             - Run all test cases on both programs"
	@echo "  make test-backtracking - Run tests on backtracking program"
	@echo "  make test-greedy      - Run tests on greedy program"
	@echo "  make run-backtracking - Run backtracking interactively"
	@echo "  make run-greedy       - Run greedy interactively"
	@echo "  make clean            - Remove compiled files"
	@echo "  make help             - Show this help message"
