# Maze Generator in C (SDL2)

A real-time maze generator implemented in C using the 
Depth-First Search backtracking algorithm and visualized with SDL2.

## Maze Generation Demo

![Maze Demo](demo/maze.gif)

## Features

- Randomized DFS maze generation
- Stack-based backtracking
- Real-time animation
- Grid-based rendering with SDL2

## Algorithm

The maze is generated using a randomized depth-first search:

1. Start at a random cell
2. Visit unvisited neighbors
3. Remove walls between cells
4. Backtrack when no neighbors remain

## Build

Requires SDL2.

gcc main.c maze.c renderer.c -o maze `sdl2-config --cflags --libs`


## Run

./maze




