# Makefile for Lexical Analyzer (lexc)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = lexc
SRC_DIR = src
BIN_DIR = bin

# Source file
SOURCE = $(SRC_DIR)/lexer.c

# Default target
all: directories $(BIN_DIR)/$(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BIN_DIR)

# Compile the executable directly from source
$(BIN_DIR)/$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $< -o $@
	@echo "Build complete: $(BIN_DIR)/$(TARGET)"

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)
	@echo "Clean complete"

# Run the program with default input
run: all
	./$(BIN_DIR)/$(TARGET)

# Run with a specific file
run-file: all
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make run-file FILE=<filename>"; \
	else \
		./$(BIN_DIR)/$(TARGET) $(FILE); \
	fi

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  run       - Build and run with default input"
	@echo "  run-file  - Build and run with a file: make run-file FILE=<filename>"
	@echo "  help      - Show this help message"

.PHONY: all clean run run-file help directories
