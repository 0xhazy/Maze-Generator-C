#include "renderer.h"
#include "config.h"



void render_maze(SDL_Renderer *renderer, Maze *maze)
{
    if(!maze || !maze->grid)
    {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white lines
    for (size_t r = 0; r < ROWS; r++)
    {
        for (size_t c = 0; c < COLS; c++)
        {
            Cell *cell = &maze->grid[r * COLS + c];
            int x = c * CELL_SIZE;
            int y = r * CELL_SIZE;


            // Draw visited cells (gray)
            if (cell->visited)
            {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // gray
                SDL_Rect rect = { x, y, CELL_SIZE, CELL_SIZE };
                SDL_RenderFillRect(renderer, &rect);
            }
            // Highlight current cell (green)
            if (r == maze->current_row && c == maze->current_col)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
                SDL_Rect rect = { x, y, CELL_SIZE, CELL_SIZE };
                SDL_RenderFillRect(renderer, &rect);
            }

            SDL_Rect rect = {
                c * CELL_SIZE,
                r * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE};

            // Color based on state
            if (r == maze->current_row && c == maze->current_col)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Bright green
            }
            else if (cell->visited)
            {
                SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); // Dark gray
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
            }

            SDL_RenderFillRect(renderer, &rect);
            // Draw walls (white)
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            if (cell->wall_north)
                SDL_RenderDrawLine(renderer, x, y, x + CELL_SIZE, y);

            // Bottom wall
            if (cell->wall_south)
                SDL_RenderDrawLine(renderer, x, y + CELL_SIZE, x + CELL_SIZE, y + CELL_SIZE);

            // Left wall
            if (cell->wall_west)
                SDL_RenderDrawLine(renderer, x, y, x, y + CELL_SIZE);

            // Right wall
            if (cell->wall_east)
                SDL_RenderDrawLine(renderer, x + CELL_SIZE, y, x + CELL_SIZE, y + CELL_SIZE);

        }
        
    }   


}