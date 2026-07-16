#include <stdio.h>

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

int main() {
    const char *src_path = "C:\\Users\\Admin\\files\\projects\\sequin-lang\\examples\\example_1.sqn";

    return 0;
}