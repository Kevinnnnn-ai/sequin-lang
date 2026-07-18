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

char* ToString(const char *source_path, long int *string_length);

// TODO: void return hides realloc failure,but caller can't stop lexing.
void AddToken(TokenList *token_list, Token *token) {
    if ((*token_list).token_count < (*token_list).capacity + 1) {
        int capacity = ((*token_list).capacity + 1) * sizeof(Token);

        Token *temp = realloc((*token_list).token_list, capacity);
        if (temp == NULL) {
            // Error handling here.
            return;
        }

        (*token_list).capacity++;
        (*token_list).token_list = temp;
        (*token_list).token_list[(*token_list).token_count] = *token;
        (*token_list).token_count++;

    } else {
        // Error handling here.
        return;
    }
}

char* ToString(const char *source_path, long int *string_length) {
    FILE *source_file = fopen(source_path, "rb");
    if (source_file == NULL) {
        // Error handling here.
        return NULL;
    }

    if (fseek(source_file, 0, SEEK_END) != 0) {
        // Error handling here.
        fclose(source_file);
        return NULL;
    }

    // NOTE: fseek(SEEK_END) with ftell() is not a guaranteed size in ISO C, and
    // long int caps files at 2 GB on Windows. long int should be treated as an allocation upper bound.
    long int source_length = ftell(source_file);
    if (source_length == -1) {
        // Error handling here.
        fclose(source_file);
        return NULL;
    }

    rewind(source_file);

    char *source_string = malloc(source_length + 1);
    if (source_string == NULL) {
        // Error handling here.
        fclose(source_file);
        return NULL;
    }

    // FIXME: ferror() is unchecked
    size_t bytes_read = fread(source_string, sizeof(char), source_length, source_file);
    source_string[bytes_read] = '\0';
    fclose(source_file);

    // FIXME: this reports ftell()'s on-disk size, but only bytes_read bytes are in the buffer.
    // The '\0' above already admits they can differ, which number describes the contents?
    if (string_length != NULL) {
        *string_length = source_length;
    }
    
    return source_string;
}

TokenList* Tokenize(const char *source_string, int source_length) {

}

TokenList* RunLexer(const char* source_path) {
    long int source_length;
    // FIXME: this variable owns mutable malloc()'d memory, so const-qualifying it misstates
    // ownership, and passing it to free() below discards the qualifier (warning; fails -Werror)
    const char *source_string = ToString(source_path, &source_length);
    if (source_string == NULL) {
        return NULL;
    }

    // TODO: once Tokenize is wired in, tokens hold views into this buffer, free()ing here would
    // dangle every lexeme; decide who owns the source string and for how long
    free(source_string);
    return NULL;
}

int main() {
    // TODO: machine-specific absolute path breaks on any other clone, take it from argv[1];
    // also RunLexer's result is ignored, so failure never reaches the exit code
    const char *source_path = "C:\\Users\\Admin\\files\\projects\\sequin-lang\\examples\\example_1.sqn";
    RunLexer(source_path);
}