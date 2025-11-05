# Makefile for Lexical Analyzer (lexc)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
TARGET = lexc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: directories $(BIN_DIR)/$(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Link the executable
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Build complete: $(BIN_DIR)/$(TARGET)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
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
