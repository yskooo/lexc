#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

/* Token types */
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_EQUALS,
    TOKEN_NOT_EQUALS,
    TOKEN_LESS_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_WHILE,
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_INT,
    TOKEN_KEYWORD_FLOAT,
    TOKEN_KEYWORD_VOID,
    TOKEN_ERROR,
    TOKEN_UNKNOWN
} TokenType;

/* Token structure */
typedef struct {
    TokenType type;
    char *value;
    int line;
    int column;
} Token;

/* Lexer structure */
typedef struct {
    const char *source;
    size_t position;
    size_t length;
    int line;
    int column;
} Lexer;

/* Function declarations */
void lexer_init(Lexer *lexer, const char *source);
Token lexer_next_token(Lexer *lexer);
void token_free(Token *token);
const char* token_type_to_string(TokenType type);

#endif /* LEXER_H */
