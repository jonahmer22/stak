#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#include "general.h"
#include "tokenizer.h"
#include "../deps/arena/arena.h"

// this is only to make dynamically resizing easier while I need to
// e.g. only when I am tokenizing the source buffer
typedef struct TokenList{
    Token *tokens;
    size_t used;
    size_t size;
} TokenList;

static void tokenListEnsureSize(TokenList *list, size_t size){
    if(list->size <= size){
        list->size = list->size == 0 ? 256 : list->size * 2;

        Token *temp = realloc(list->tokens, list->size);
        if(!temp)
            error(ERROR_FATAL, 0x3108, "Could not expand token list lenght to:\t%zu", list->size);
        
        free(list->tokens); // idk if this is necessary or even might break something
        list->tokens = temp;
    }
}

static inline bool isNum(char c){
    return c >= '0' && c <= '9';
}

static inline bool isAlpha(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static inline bool isAlNum(char c){
    return isAlpha(c) || isNum(c);
}

Token *tokenizeSrc(char *src, size_t *length){
    char *head = src;

    TokenList list = {
        .tokens = NULL,
        .used = 0,
        .size = 0
    };

    // the amount of tokens we are going to need
    size_t tokensAmt = 0;
    // maybe this macro will make it slighlty easier to tell what I am doing
    #define EXPAND_LIST_BY_ONE tokenListEnsureSize(&list, ++tokensAmt);
    
    // for giving each token it's line
    size_t line = 1;
    // "maybe this macro will make it slighlty easier to tell what I am doing"
    #define SET_TOKEN_LINE list.tokens[list.used].line = line;
    while(*head != '\0'){
        switch(*head){
            case '\n':{
                line++;
            }
            case ' ':
            case '\t':
            case '\r':
            case '\v':{
                head++;
            }
            case '+':{
                EXPAND_LIST_BY_ONE
                SET_TOKEN_LINE
                list.tokens[list.used].type = TOK_PLUS;
                list.used++;
                head++;
                break;
            }
            default:{
                // handle any left over things here, like identifiers


                // lastly panic
                error(ERROR_FATAL, 0x6479, "Unknown character type:\t%c", *head);
                break;
            }
        }
    }
    #undef SET_TOKEN_LINE

    // add on the end token
    EXPAND_LIST_BY_ONE
    list.tokens[list.used].type = TOK_END;
    list.used++;

    // done making the list so we can remove this
    #undef EXPAND_LIST_BY_ONE

    // move the list to the arena
    Token *result = arenaAlloc(sizeof(Token) * list.used);
    if(!result)
        error(ERROR_FATAL, 0x2145, "Could not allocate space for (%zu) tokens in arena.", list.used);
    
    memcpy(result, list.tokens, list.used);
    if(length)
        *length = list.used;

    // get rid of the old stuff we don't need
    free(list.tokens);
    list.size = list.used = 0;

    return result;
}

void printTokens(Token *tokens){
    for(size_t i = 0; tokens[i].type != TOK_END; i++){
        switch(tokens[i].type){
            case TOK_PLUS:{
                printf("-[PLUS]-");
                break;
            }
            default:{
                error(ERROR_FATAL, 0x4279, "Encountered unknown token type while printing:\t%d", tokens[i].type);
                break;  // not necessary, but I like having these breaks anyway... looks nice ig
            }
        }
    }
    putchar('\n');
}
