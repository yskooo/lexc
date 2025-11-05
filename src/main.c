#define _POSIX_C_SOURCE 200809L
#include "../include/lexer.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *input = NULL;
    
    if (argc > 1) {
        /* Read from file */
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "Error: Could not open file '%s'\n", argv[1]);
            return 1;
        }
        
        /* Get file size */
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        /* Read file contents */
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            fclose(file);
            return 1;
        }
        
        fread(buffer, 1, size, file);
        buffer[size] = '\0';
        fclose(file);
        
        input = buffer;
    } else {
        /* Use default test input */
        input = strdup(
            "int main() {\n"
            "    int x = 42;\n"
            "    float y = 3.14;\n"
            "    if (x > 10) {\n"
            "        return x + y;\n"
            "    } else {\n"
            "        return 0;\n"
            "    }\n"
            "}\n"
        );
    }
    
    printf("Lexical Analysis Results:\n");
    printf("=========================\n\n");
    
    Lexer lexer;
    lexer_init(&lexer, input);
    
    Token token;
    do {
        token = lexer_next_token(&lexer);
        
        printf("Line %d, Col %d: %-20s", token.line, token.column, token_type_to_string(token.type));
        if (token.value != NULL) {
            printf(" '%s'", token.value);
        }
        printf("\n");
        
        token_free(&token);
    } while (token.type != TOKEN_EOF);
    
    free((void *)input);
    
    return 0;
}
