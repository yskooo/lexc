# LexC
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
├── src/             # Source files
│   └── lexer.c      # Complete lexer implementation (all-in-one file)
├── examples/        # Example input files
│   └── sample.c     # Sample C-like code
├── Makefile         # Build configuration
└── README.md        # This file
```

The lexer is implemented as a single standalone C file for simplicity and educational purposes, with all type definitions, implementation, and main function contained in one file.

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
Lightweight Enhanced Execution Code, or Lex-C, is a programming language made
for "newbie coders". Its goal is to help new learners focus on problem-solving and logic rather
than memorizing complicated commands. Inspired by the pioneer language C, Lex-C employs
concise and intuitive words to ensure writing code feels natural and unambiguous.

This new programming language follows an imperative approach to coding. It keeps only
the basic and important features of the C language while focusing on making the syntax clear and
simple. To achieve this, only a few easy-to-understand reserved words and functions were used.

Lex-C seeks to address common challenges in readability and syntax understanding by
applying a simpler lexical and syntactical design, while retaining the efficiency and procedural
nature of C. Replacing unnecessary and cryptic syntax (technical jargon) with a more natural
language makes it easier to read, understand, and maintain code, especially for beginners. This
provides an avenue where learners can focus more on developing programs without being
overwhelmed by the language's syntactic complexity.
