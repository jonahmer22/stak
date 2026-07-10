#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum TokenType{
    TOK_END = 0,
    TOK_PLUS
} TokenType;

typedef struct Token{
    TokenType type;

    union{
        double num;
        // if it needs to hold a string it should always allocate it's own buffer in the arena then memcpy
        // NOTE: I think I am going to reuse this field for both identifiers and actual strings
        char *str;
    } data;

    // for errors and shit
    size_t line;
} Token;

Token *tokenizeSrc(char *src, size_t *length);
void printTokens(Token *tokens);

// 

#endif
