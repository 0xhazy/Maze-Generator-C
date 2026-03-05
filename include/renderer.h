#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "maze.h"

void render_maze(SDL_Renderer *renderer, Maze *maze);

#endif
