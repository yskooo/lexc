#define _POSIX_C_SOURCE 200809L
#include "../include/lexer.h"
#include <string.h>
#include <ctype.h>

/* Helper function to check if we've reached the end */
static int is_at_end(Lexer *lexer) {
    return lexer->position >= lexer->length;
}

/* Get the current character */
static char current_char(Lexer *lexer) {
    if (is_at_end(lexer)) return '\0';
    return lexer->source[lexer->position];
}

/* Advance to the next character */
static char advance(Lexer *lexer) {
    if (is_at_end(lexer)) return '\0';
    char c = lexer->source[lexer->position];
    lexer->position++;
    lexer->column++;
    if (c == '\n') {
        lexer->line++;
        lexer->column = 1;
    }
    return c;
}

/* Peek at the next character without consuming it */
static char peek(Lexer *lexer) {
    if (is_at_end(lexer)) return '\0';
    return lexer->source[lexer->position];
}

/* Peek ahead by n characters */
static char peek_next(Lexer *lexer) {
    if (lexer->position + 1 >= lexer->length) return '\0';
    return lexer->source[lexer->position + 1];
}

/* Skip whitespace */
static void skip_whitespace(Lexer *lexer) {
    while (!is_at_end(lexer)) {
        char c = current_char(lexer);
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance(lexer);
        } else if (c == '/' && peek_next(lexer) == '/') {
            /* Skip single-line comments */
            while (!is_at_end(lexer) && current_char(lexer) != '\n') {
                advance(lexer);
            }
        } else {
            break;
        }
    }
}

/* Create a token */
static Token make_token(TokenType type, const char *value, int line, int column) {
    Token token;
    token.type = type;
    token.line = line;
    token.column = column;
    if (value != NULL) {
        token.value = strdup(value);
    } else {
        token.value = NULL;
    }
    return token;
}

/* Check if a string matches a keyword */
static TokenType check_keyword(const char *str) {
    if (strcmp(str, "if") == 0) return TOKEN_KEYWORD_IF;
    if (strcmp(str, "else") == 0) return TOKEN_KEYWORD_ELSE;
    if (strcmp(str, "while") == 0) return TOKEN_KEYWORD_WHILE;
    if (strcmp(str, "return") == 0) return TOKEN_KEYWORD_RETURN;
    if (strcmp(str, "int") == 0) return TOKEN_KEYWORD_INT;
    if (strcmp(str, "float") == 0) return TOKEN_KEYWORD_FLOAT;
    if (strcmp(str, "void") == 0) return TOKEN_KEYWORD_VOID;
    return TOKEN_IDENTIFIER;
}

/* Scan an identifier or keyword */
static Token scan_identifier(Lexer *lexer) {
    int start_line = lexer->line;
    int start_column = lexer->column;
    size_t start = lexer->position;
    
    while (!is_at_end(lexer) && (isalnum(current_char(lexer)) || current_char(lexer) == '_')) {
        advance(lexer);
    }
    
    size_t length = lexer->position - start;
    char *value = (char *)malloc(length + 1);
    strncpy(value, lexer->source + start, length);
    value[length] = '\0';
    
    TokenType type = check_keyword(value);
    Token token = make_token(type, value, start_line, start_column);
    free(value);
    return token;
}

/* Scan a number */
static Token scan_number(Lexer *lexer) {
    int start_line = lexer->line;
    int start_column = lexer->column;
    size_t start = lexer->position;
    
    while (!is_at_end(lexer) && isdigit(current_char(lexer))) {
        advance(lexer);
    }
    
    /* Check for decimal point */
    if (!is_at_end(lexer) && current_char(lexer) == '.' && isdigit(peek_next(lexer))) {
        advance(lexer); /* Consume the '.' */
        while (!is_at_end(lexer) && isdigit(current_char(lexer))) {
            advance(lexer);
        }
    }
    
    size_t length = lexer->position - start;
    char *value = (char *)malloc(length + 1);
    strncpy(value, lexer->source + start, length);
    value[length] = '\0';
    
    Token token = make_token(TOKEN_NUMBER, value, start_line, start_column);
    free(value);
    return token;
}

/* Scan a string literal */
static Token scan_string(Lexer *lexer) {
    int start_line = lexer->line;
    int start_column = lexer->column;
    advance(lexer); /* Consume opening quote */
    size_t start = lexer->position;
    
    while (!is_at_end(lexer) && current_char(lexer) != '"') {
        if (current_char(lexer) == '\n') {
            return make_token(TOKEN_ERROR, "Unterminated string", start_line, start_column);
        }
        advance(lexer);
    }
    
    if (is_at_end(lexer)) {
        return make_token(TOKEN_ERROR, "Unterminated string", start_line, start_column);
    }
    
    size_t length = lexer->position - start;
    char *value = (char *)malloc(length + 1);
    strncpy(value, lexer->source + start, length);
    value[length] = '\0';
    
    advance(lexer); /* Consume closing quote */
    
    Token token = make_token(TOKEN_STRING, value, start_line, start_column);
    free(value);
    return token;
}

/* Initialize the lexer */
void lexer_init(Lexer *lexer, const char *source) {
    lexer->source = source;
    lexer->position = 0;
    lexer->length = strlen(source);
    lexer->line = 1;
    lexer->column = 1;
}

/* Get the next token */
Token lexer_next_token(Lexer *lexer) {
    skip_whitespace(lexer);
    
    if (is_at_end(lexer)) {
        return make_token(TOKEN_EOF, NULL, lexer->line, lexer->column);
    }
    
    int start_line = lexer->line;
    int start_column = lexer->column;
    char c = advance(lexer);
    
    /* Identifiers and keywords */
    if (isalpha(c) || c == '_') {
        lexer->position--;
        lexer->column--;
        return scan_identifier(lexer);
    }
    
    /* Numbers */
    if (isdigit(c)) {
        lexer->position--;
        lexer->column--;
        return scan_number(lexer);
    }
    
    /* String literals */
    if (c == '"') {
        lexer->position--;
        lexer->column--;
        return scan_string(lexer);
    }
    
    /* Operators and punctuation */
    switch (c) {
        case '+': return make_token(TOKEN_PLUS, "+", start_line, start_column);
        case '-': return make_token(TOKEN_MINUS, "-", start_line, start_column);
        case '*': return make_token(TOKEN_MULTIPLY, "*", start_line, start_column);
        case '/': return make_token(TOKEN_DIVIDE, "/", start_line, start_column);
        case '(': return make_token(TOKEN_LPAREN, "(", start_line, start_column);
        case ')': return make_token(TOKEN_RPAREN, ")", start_line, start_column);
        case '{': return make_token(TOKEN_LBRACE, "{", start_line, start_column);
        case '}': return make_token(TOKEN_RBRACE, "}", start_line, start_column);
        case ';': return make_token(TOKEN_SEMICOLON, ";", start_line, start_column);
        case ',': return make_token(TOKEN_COMMA, ",", start_line, start_column);
        case '=':
            if (peek(lexer) == '=') {
                advance(lexer);
                return make_token(TOKEN_EQUALS, "==", start_line, start_column);
            }
            return make_token(TOKEN_ASSIGN, "=", start_line, start_column);
        case '!':
            if (peek(lexer) == '=') {
                advance(lexer);
                return make_token(TOKEN_NOT_EQUALS, "!=", start_line, start_column);
            }
            return make_token(TOKEN_UNKNOWN, "!", start_line, start_column);
        case '<':
            if (peek(lexer) == '=') {
                advance(lexer);
                return make_token(TOKEN_LESS_EQUAL, "<=", start_line, start_column);
            }
            return make_token(TOKEN_LESS_THAN, "<", start_line, start_column);
        case '>':
            if (peek(lexer) == '=') {
                advance(lexer);
                return make_token(TOKEN_GREATER_EQUAL, ">=", start_line, start_column);
            }
            return make_token(TOKEN_GREATER_THAN, ">", start_line, start_column);
        default:
            return make_token(TOKEN_UNKNOWN, NULL, start_line, start_column);
    }
}

/* Free token memory */
void token_free(Token *token) {
    if (token->value != NULL) {
        free(token->value);
        token->value = NULL;
    }
}

/* Convert token type to string */
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_STRING: return "STRING";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_MULTIPLY: return "MULTIPLY";
        case TOKEN_DIVIDE: return "DIVIDE";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_EQUALS: return "EQUALS";
        case TOKEN_NOT_EQUALS: return "NOT_EQUALS";
        case TOKEN_LESS_THAN: return "LESS_THAN";
        case TOKEN_GREATER_THAN: return "GREATER_THAN";
        case TOKEN_LESS_EQUAL: return "LESS_EQUAL";
        case TOKEN_GREATER_EQUAL: return "GREATER_EQUAL";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_KEYWORD_IF: return "KEYWORD_IF";
        case TOKEN_KEYWORD_ELSE: return "KEYWORD_ELSE";
        case TOKEN_KEYWORD_WHILE: return "KEYWORD_WHILE";
        case TOKEN_KEYWORD_RETURN: return "KEYWORD_RETURN";
        case TOKEN_KEYWORD_INT: return "KEYWORD_INT";
        case TOKEN_KEYWORD_FLOAT: return "KEYWORD_FLOAT";
        case TOKEN_KEYWORD_VOID: return "KEYWORD_VOID";
        case TOKEN_ERROR: return "ERROR";
        case TOKEN_UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}
