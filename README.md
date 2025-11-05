# lexc
Lightweight Enhanced eXecution Code (Lex-C)

A lexical analyzer (lexer/tokenizer) built with C for parsing source code and converting it into a stream of tokens.

## Features

- Token recognition for identifiers, numbers, strings, and operators
- Support for common C-like keywords (if, else, while, return, int, float, void)
- Single-line comment support (//)
- Line and column tracking for error reporting
- Simple and extensible design

## Building

To build the project, simply run:

```bash
make
```

This will compile the source code and create the executable in the `bin/` directory.

## Usage

### Run with default input

```bash
make run
```

### Run with a custom file

```bash
make run-file FILE=examples/sample.c
```

Or directly:

```bash
./bin/lexc examples/sample.c
```

## Project Structure

```
lexc/
├── include/          # Header files
│   └── lexer.h      # Lexer interface and token definitions
├── src/             # Source files
│   ├── lexer.c      # Lexer implementation
│   └── main.c       # Main program
├── examples/        # Example input files
│   └── sample.c     # Sample C-like code
├── Makefile         # Build configuration
└── README.md        # This file
```

## Supported Tokens

### Keywords
- `if`, `else`, `while`, `return`
- `int`, `float`, `void`

### Operators
- Arithmetic: `+`, `-`, `*`, `/`
- Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Assignment: `=`

### Delimiters
- Parentheses: `(`, `)`
- Braces: `{`, `}`
- Semicolon: `;`
- Comma: `,`

### Literals
- Identifiers: variable and function names
- Numbers: integers and floating-point numbers
- Strings: text enclosed in double quotes

## Cleaning

To clean build artifacts:

```bash
make clean
```

## License

MIT License - see LICENSE file for details
