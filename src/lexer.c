#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

enum TokenType {

};

struct Token {

};

struct TokenList {

};

char* ToString(const char *source_path, long int *string_length);

char* ToString(const char *source_path, long int *string_length) {
    // FIXME: text mode on Windows translates CRLF and stops at a 0x1A byte, so the size
    // measured below won't match the bytes fread actually delivers (your own example_1.sqn: 1776 vs 1745)
    FILE *source_file = fopen(source_path, "r");
    if (source_file == NULL) {
        // TODO: four failure modes in this function all collapse to a bare NULL —
        // the caller can't tell file-not-found from out-of-memory
        return NULL; // error
    }

    if (fseek(source_file, 0, SEEK_END) != 0) {
        fclose(source_file);
        return NULL; // error
    }

    // NOTE: fseek(SEEK_END)+ftell is not a guaranteed size in ISO C, and long caps files
    // at 2 GiB on Windows — treat this value as an allocation upper bound, never the content length
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

    // FIXME: a short read here is never distinguished from an I/O error (ferror is unchecked)
    size_t bytes_read = fread(source_string, sizeof(char), source_length, source_file);
    source_string[bytes_read] = '\0';
    fclose(source_file);

    // FIXME: this reports ftell's on-disk size, but only bytes_read bytes are in the buffer
    // (the '\0' above already admits they can differ) — which number describes the contents?
    if (string_length != NULL) {
        *string_length = source_length;
    }
    
    return source_string;
}

struct TokenList* Tokenize(const char *source_string, int source_length) {

}

// FIXME: signature disagrees with the line-45 prototype — one of the two must change
struct TokenList* RunLexer(const char* source_path) {
    long int source_length;
    // FIXME: this variable owns mutable malloc'd memory, so const-qualifying it misstates
    // ownership — and passing it to free() below discards the qualifier (warning; fails -Werror)
    const char *source_string = ToString(source_path, &source_length);
    if (source_string == NULL) {
        return NULL; // error
    }

    // TODO: once Tokenize is wired in, tokens hold views into this buffer — freeing here would
    // dangle every lexeme; decide who owns the source string and for how long
    free(source_string);
    return NULL;
}

int main() {
    // TODO: machine-specific absolute path breaks on any other clone — take it from argv[1];
    // also RunLexer's result is ignored, so failure never reaches the exit code
    const char *source_path = "C:\\Users\\Admin\\files\\projects\\sequin-lang\\examples\\example_1.sqn";
    RunLexer(source_path);
}