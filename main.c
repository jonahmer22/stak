#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "general.h"
#include "tokenizer.h"
#include "deps/arena/arena.h"

#define MAX_REPL_LINE_LENGTH 1024

int main(int argc, char **argv){
    // used for interpreter internals and "global state"
    arenaInit();

    if(argc > 1){
        char *src = readFile(argv[1], NULL);
        Token *tokens = tokenizeSrc(src, NULL);

        printTokens(tokens);

        goto end;
    }

    // repl
    fprintf(stdout, "STAK\nA stack based programming language.\nType \'bye\' to exit.\n");
    fflush(stdout);
    while(true){
        fprintf(stdout, "$ ");
        fflush(stdout);

        char line[MAX_REPL_LINE_LENGTH] = {0};
        fgets(line, MAX_REPL_LINE_LENGTH, stdin);

        // i think the only way you get "bye\n\0" is by typing only that, the eof is right after anyway, idrc
        if(memcmp(line, "bye\n\0", 5) == 0)
            break;
    }

    end:
        arenaDestroy();
        return EXIT_SUCCESS;
}
