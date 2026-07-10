#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "general.h"
#include "deps/arena/arena.h"

int main(int argc, char **argv){
    // used for interpreter internals and "global state"
    arenaInit();

    if(argc > 1){
        char *src = readFile(argv[1]);

        puts(src);

        goto end;
    }
    printf("Hello, World!\n");

    end:
        arenaDestroy();
        return EXIT_SUCCESS;
}
