#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "general.h"
#include "../deps/arena/arena.h"

void error(ErrorType type, unsigned code, const char *str, ...){
    va_list args;
    va_start(args, str);

    fprintf(stderr, type == ERROR_FATAL ? "[FATAL 0x%04X]:\t" : "[ERROR 0x%04X]:\t", code);
    vfprintf(stderr, str, args);
    fprintf(stderr, "\r\n");

    va_end(args);
    fflush(stderr);

    if(type == ERROR_FATAL)
        exit(EXIT_FAILURE);
}

char *readFile(const char *path, size_t *length){
    if(!path)   // actually the name is just non existent, but idk a better way to convey this
        error(ERROR_FATAL, 0x0001, "Impropper file name.");

    FILE *file = fopen(path, "r");
    if(!file)
        error(ERROR_FATAL, 0x0002, "Could not open file at path:\t\'%s\'", path);

    fseek(file, 0, SEEK_END);
    long end = ftell(file);
    fseek(file, 0, SEEK_SET);
    long start = ftell(file);

    long size = end - start;
    char *buff = arenaAlloc(sizeof(char) * size);
    if(!buff)
        error(ERROR_FATAL, 0x0003, "Could not allocate (%d) characters to read file.", (size / sizeof(char)));

    fread(buff, sizeof(char), (size / sizeof(char)), file);

    if(length)
        *length = (size_t)size;
    
    fclose(file);
    return buff;
}
