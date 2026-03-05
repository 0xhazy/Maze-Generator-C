CC = gcc

CFLAGS = -Wall -Wextra -Iinclude
SDLFLAGS = `sdl2-config --cflags --libs`

SRC = src/main.c src/maze.c src/renderer.c
OUT = maze

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(SDLFLAGS)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
