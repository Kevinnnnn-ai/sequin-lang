#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

enum TokenType {
    KEYWORD,
    FLAG,
    IDENTIFIER,
    COMMENT,
    WHITESPACE,
    NEWLINE,

    LITERAL_STRING,
    LITERAL_NUMBER,
    LITERAL_TIMESTAMP,
    LITERAL_DURATION,

    DELIMITER_COLON,
    DELIMITER_COMMA,
    DELIMITER_OPEN_PARENTHESES,
    DELIMITER_CLOSE_PARENTHESES,
    DELIMITER_OPEN_BRACES,
    DELIMITER_CLOSE_BRACES,

    END_OF_FILE,
};

struct Token {
    enum TokenType type;
    const char *lexeme;
    int length;
    int line;
    int column;
};

struct TokenList {
    struct Token *token_list;
    int count;
    int capacity;
};

char* ToString(const char *source_path, long int *string_length);
struct TokenList* Tokenize(const char *source_string, int source_length);
struct TokenList* RunLexer(const char *source_string, int source_length);

char* ToString(const char *source_path, long int *string_length) {
    FILE *source_file = fopen(source_path, "r");
    if (source_file == NULL) {
        return NULL; // error
    }

    if (fseek(source_file, 0, SEEK_END) != 0) {
        fclose(source_file);
        return NULL; // error
    }

    long int source_length = ftell(source_file);
    if (source_length == -1) {
        fclose(source_file);
        return NULL; // error
    }

    rewind(source_file);

    char *source_string = malloc(source_length + 1);
    if (source_string == NULL) {
        fclose(source_file);
        return NULL; // error
    }

    size_t bytes_read = fread(source_string, sizeof(char), source_length, source_file);
    source_string[bytes_read] = '\0';
    fclose(source_file);

    if (string_length != NULL) {
        *string_length = source_length;
    }
    
    return source_string;
}

struct TokenList* Tokenize(const char *source_string, int source_length) {
    struct TokenList token_list;
    token_list.count = 0;
    token_list.capacity = 0;

    int current_position = 0;
    int line = 0;
    int column = 0;

    while (current_position <= source_length) {
        struct Token token;
        int lexeme_start_position = current_position;
        char character = source_string[current_position++];

        switch (character) {
            case '"':
                lexeme_start_position++;

                do {
                    current_position++;
                } while (source_string[current_position + 1] != '"' && current_position <= source_length);

                if (!(current_position <= source_length)) {
                    return NULL; // error
                }
        }
    }
}

struct TokenList* RunLexer(const char* source_path) {
    long int source_length;
    const char *source_string = ToString(source_path, &source_length);
    if (source_string == NULL) {
        return NULL; // error
    }

    free(source_string);
    return NULL;
}

int main() {
    const char *source_path = "C:\\Users\\Admin\\files\\projects\\sequin-lang\\examples\\example_1.sqn";
    RunLexer(source_path);
}