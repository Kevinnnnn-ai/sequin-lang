#include <stdio.h>
#include <string.h>

char* ToString(const char *source_code_path);

enum TokenType {
    KEYWORD_MISSION,
    OPERATOR_ASSIGNMENT,
    IDENTIFIER_MISSION_NAME,
    DELIMITER_SEMICOLON,
};

struct Token {
    int type;
    const char *lexeme;
    int line;
    int column;
};

char* ToString(const char *source_code_path) {
    FILE *source_code = fopen(source_code_path, "rb");
    if (source_code == NULL) {
        return NULL;
    }

    if (fseek(source_code, 0, SEEK_END) != 0) {
        fclose(source_code);
        return NULL;
    }

    long source_code_length = ftell(source_code);
    if (source_code_length == -1) {
        fclose(source_code);
        return NULL;
    }

    rewind(source_code);

    char *buffer = malloc(source_code_length + 1);
    if (buffer == NULL) {
        fclose(source_code);
        return NULL;
    }

    size_t bytes_read = fread(buffer, sizeof(char), source_code_length, source_code);
    buffer[bytes_read] = '\0';
    fclose(source_code);
    return buffer;
}

int main() {
    const char *source_code_path = "C:\\Users\\Admin\\files\\projects\\sequin-lang\\examples\\example_1.sqn";

    return 0;
}