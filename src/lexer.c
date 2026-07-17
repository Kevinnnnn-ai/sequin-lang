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

struct TokenList* GetTokenList(const char *src_string, int src_length);
struct TokenList* RunLexer(const char *src_string, int src_length);

void AppendToken(struct TokenList *token_list, struct Token token) {
    
}

struct TokenList* GetTokenList(const char *src_string, int src_length) {
    struct TokenList token_list;
    token_list.count = 0;
    token_list.capacity = 0;

    int position = 0;
    int line = 1;
    int column = 1;

    while (position <= src_length) {
        int lexeme_start = 0;
        char character = src_string[position];

        if (character == ' ' || character == '\t') {
            column++;
            position++;
        }

        switch (character) {
            
        }

    }
}

struct TokenList* RunLexer(const char* src_path) {
    FILE *src_file = fopen(src_path, "r");
    if (src_file == NULL) {
        return NULL;
    }

    if (fseek(src_file, 0, SEEK_END) != 0) {
        fclose(src_file);
        return NULL;
    }

    long src_length = ftell(src_file);
    if (src_length == -1) {
        fclose(src_file);
        return NULL;
    }

    rewind(src_file);

    char *src_string = malloc(src_length + 1);
    if (src_string == NULL) {
        fclose(src_file);
        return NULL;
    }

    size_t bytes_read = fread(src_string, sizeof(char), src_length, src_file);
    src_string[bytes_read] = '\0';
    fclose(src_file);

    return NULL;
}

int main() {
    const char *src_path = "C:\\Users\\Admin\\files\\projects\\sequin-lang\\examples\\example_1.sqn";
    RunLexer(src_path);
}