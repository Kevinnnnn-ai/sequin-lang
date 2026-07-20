#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    KEYWORD,
    IDENTIFIER,
    FLAG,
    STRING,
    NUMBER,
    TIMESTAMP,
    DURATION,
    DELIMITER,
    NEWLINE,
    END_OF_FILE,
} TokenType;

typedef struct {
    TokenType token_type;
    char *lexeme;
    int length;
    int line;
    int column;
} Token;

typedef struct {
    Token *token_list;
    int token_count;
    int capacity;
} TokenList;

void AddToken(TokenList *token_list, Token *token);
char* ToString(const char *source_path, long int *string_length);

void AddToken(TokenList *token_list, Token *token) {
    if ((*token_list).token_count < (*token_list).capacity + 1) {
        int capacity = ((*token_list).capacity + 1) * sizeof(Token);

        Token *temp = realloc((*token_list).token_list, capacity);
        if (temp == NULL) {
            return; // TODO: add error handling here.
        }

        (*token_list).capacity++;
        (*token_list).token_list = temp;
        (*token_list).token_list[(*token_list).token_count] = *token;
        (*token_list).token_count++;

    } else {
        return; // TODO: add error handling here.
    }
}

char* ToString(const char *source_path, long int *string_length) {
    FILE *source_file = fopen(source_path, "rb");
    if (source_file == NULL) {
        return NULL; // TODO: add error handling here.
    }

    if (fseek(source_file, 0, SEEK_END) != 0) {
        fclose(source_file); // TODO: add error handling here.
        return NULL;
    }

    long int source_length = ftell(source_file); // NOTE: fseek and SEEK_END with ftell is not a guaranteed size in ISO C
    if (source_length == -1) {
        fclose(source_file); // TODO: add error handling here.
        return NULL;
    }

    rewind(source_file);

    char *source_string = malloc(source_length + 1);
    if (source_string == NULL) {
        fclose(source_file); // TODO: add error handling here.
        return NULL;
    }

    size_t bytes_read = fread(source_string, sizeof(char), source_length, source_file); // FIXME: ferror is unchecked
    source_string[bytes_read] = '\0';
    fclose(source_file);

    if (string_length != NULL) {
        *string_length = source_length; // FIXME: The '\0' above already admits they can differ, which number describes the contents?
    }
    
    return source_string;
}

TokenList* Tokenize(const char *source_string, int source_length) {

}

TokenList* RunLexer(const char* source_path) {
    long int source_length;
    const char *source_string = ToString(source_path, &source_length); // FIXME: this variable owns mutable malloc'd memory.
    if (source_string == NULL) {
        return NULL; // TODO: add error handling here.
    }

    free(source_string); // TODO: decide who owns the source string and for how long.
    return NULL; // TODO: add return here.
}

int main() { // TODO: remove main, integrate lexer into compiling process.
    const char *source_path = "C:\\Users\\Admin\\files\\projects\\sequin-lang\\examples\\example_1.sqn";
    RunLexer(source_path);
}