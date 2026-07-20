# Changelog
This document records all notable development activity for Sequin, including major and minor changes to the codebase. Entries are grouped by date, with the most recent first.

<br>



## 7-19-2026
### Changed
- Made all comments in-line and brief to prevent over-commenting ([lexer.c](../src/lexer.c)).

<br>



## 7-18-2026
### Added
- Implemented tokenizer pseudocode into lexer process ([tokenizer.txt](../res/tokenizer.txt), [lexer.c](../src/lexer.c)).
- Defined the Token structure (type, lexeme view, length, line, column) and the TokenList growable-array structure ([lexer.c](../src/lexer.c)).
- Implemented AddToken: appends a token to the list, growing the heap array by one slot per call via realloc with the temp-pointer safety pattern and a failure check ([lexer.c](../src/lexer.c)).

### Changed
- Put flowcharts into their own folder ([flowcharts/](../res/flowcharts/)).
- Converted the token structures to typedefs and updated Tokenize/RunLexer signatures to match ([lexer.c](../src/lexer.c)).
- Settled token storage design: lexemes are pointer+length views into the source buffer (no copies), positions are 1-based line and column, and the token list owns a contiguous heap array of Token values.

### Notes
- AddToken is intentionally correct-but-slow for now: it reallocates on every append. A TODO marks the planned upgrade to a count == capacity guard with capacity doubling, plus a real failure signal instead of a silent void return.
- Known debts still open in RunLexer/ToString: source-buffer ownership once tokens hold views into it, and the long int vs int source-length mismatch.

<br>



## 7-17-2026
### Added
- Added 2 references from SeqN to model Sequin syntax and output after.

### Changed
- Finished adding Sequin components for lexing.
- Refactored ToString into RunLexer, finalized tenative token types, and began working on the token list generator ([lexer.c](../src/lexer.c)).
- Restyled pipeline and lexer flowcharts ([lexer.txt](../res/lexer.txt), [pipeline.txt](../res/pipeline.txt)).
- Compiled a tokenizer pseudocode excerpt ([tokenizer.txt](../res/tokenizer.txt)).

### Research
- Researched about helpful lexer functions and checks.

<br>



## 7-16-2026
### Added
- Created a general programming language pipeline workflow ([pipeline.txt](../res/pipeline.txt)).
- Created a general lexer workflow ([lexer.txt](../res/lexer.txt)).
- Started the initial lexer implementation ([lexer.c](../src/lexer.c)).

### Changed
- Restructured changelog entries to use bulleted lists with inline links.
- Restructured syntax to resemble something similar to that of NASA's SeqN.

### Research
- Studied lexer design and implementation ([How I Wrote a Lexer](https://yc.prosetech.com/how-i-wrote-a-lexer-39f4f79d2980), [Crafting Interpreters: Scanning](https://craftinginterpreters.com/scanning.html)).
- Studied token characteristics ([Tokens and Lexemes](https://www.geeksforgeeks.org/compiler-design/token-patterns-and-lexems/)).
- Reviewed the C standard library file I/O functions [fseek](https://www.geeksforgeeks.org/cpp/fseek-in-c-with-example/), [ftell](https://www.geeksforgeeks.org/techtips/ftell-c-example/), and [fread](https://www.geeksforgeeks.org/c/fread-function-in-c/).

### Notes
- Discovered SeqN, an existing programming language very similar to this project's concept. Sequin remains a personal building exercise, so development continues as planned.