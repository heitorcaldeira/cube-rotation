CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2`
LIBS    = `pkg-config --libs sdl2` -lm

cube: cube.c
	$(CC) $(CFLAGS) -o cube cube.c $(LIBS)
