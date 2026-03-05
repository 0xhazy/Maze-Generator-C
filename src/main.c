#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "maze.h"
#include "renderer.h"

int main() {
  // Disable stdout buffering so debug prints appear immediately
  setvbuf(stdout, NULL, _IONBF, 0);
  srand(time(NULL)); // seed rand for DFS randomness

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!window) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Initialize maze
  Maze maze;
  maze_init(&maze, ROWS, COLS);

  bool running = true;
  SDL_Event event;

  while (running) {
    // Event handling
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
    }

    // Perform one DFS step if maze not finished
    if (!maze.finished) {
      maze_step(&maze);

      // Debug: print current cell and neighbor count
      Cell *cell = &maze.grid[maze.current_row * maze.cols + maze.current_col];
      int count = 0;
      if (maze.current_row > 0 &&
          !maze.grid[(maze.current_row - 1) * maze.cols + maze.current_col]
               .visited)
        count++;
      if (maze.current_row + 1 < maze.rows &&
          !maze.grid[(maze.current_row + 1) * maze.cols + maze.current_col]
               .visited)
        count++;
      if (maze.current_col > 0 &&
          !maze.grid[maze.current_row * maze.cols + (maze.current_col - 1)]
               .visited)
        count++;
      if (maze.current_col + 1 < maze.cols &&
          !maze.grid[maze.current_row * maze.cols + (maze.current_col + 1)]
               .visited)
        count++;
      printf("Current: (%zu,%zu), neighbors=%d\n", maze.current_row,
             maze.current_col, count);
    }

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw maze
    render_maze(renderer, &maze);

    // Present frame
    SDL_RenderPresent(renderer);

    SDL_Delay(50); // control animation speed
  }

  // Cleanup
  maze_destroy(&maze);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
