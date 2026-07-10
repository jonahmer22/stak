#ifndef GENERAL_H
#define GENERAL_H

typedef enum ErrorType{
    ERROR_FATAL,
    ERROR_SOFT
} ErrorType;

void error(ErrorType type, unsigned code, const char *str, ...);

char *readFile(const char *path);


#endif
