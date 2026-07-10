CC     = gcc
CFLAGS = -Wall -Wpedantic -Wextra -Iinclude -Iarena -Icliargs -lm

NAME = stak

SRCS = main.c           \
       src/*	        \
       deps/arena/arena.c    \
       deps/cliargs/cliargs.c

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

clean:
	rm $(NAME)