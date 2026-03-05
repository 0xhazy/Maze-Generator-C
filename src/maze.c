#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "maze.h"
#include <stdlib.h> // for rand()
#include <time.h>


bool maze_init(Maze *maze, size_t rows, size_t cols)
{
    if(!maze || rows == 0 || cols == 0)
        return false;
    
    maze->rows = rows;
    maze->cols = cols;
    maze->grid = malloc(rows * cols * sizeof(Cell));

    if(!maze->grid)
        return false;

    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < cols; c++)
        {
            Cell *cell = &maze->grid[r * cols + c];

            cell->wall_north = true;
            cell->wall_south = true;
            cell->wall_east = true;
            cell->wall_west = true;
            cell->visited = false;
        }
        
    }

    //DFS Stack
    maze->stack_capacity = rows * cols;
    maze->stack_rows = malloc(sizeof(size_t) * maze->stack_capacity);
    maze->stack_cols = malloc(sizeof(size_t) * maze->stack_capacity);
    if(!maze->stack_rows || !maze->stack_cols)
    {
        free(maze->grid);
        return false;
    }
    maze->stack_size = 0;

    // Start at top-left
    maze->current_row = 0;
    maze->current_col = 0;

    maze->finished = false;
    return true;

};


void maze_destroy(Maze *maze)
{
    if (!maze) return;
    free(maze->grid);
    free(maze->stack_rows);
    free(maze->stack_cols);
    maze->grid = NULL;
    maze->stack_rows = NULL;
    maze->stack_cols = NULL;
    maze->rows = 0;
    maze->cols = 0;
    maze->stack_size = 0;
};

Cell *maze_get_cell(Maze *maze, size_t row, size_t col)
{
    if (!maze || !maze->grid)
        return NULL;

    if (row >= maze->rows || col >= maze->cols)
        return NULL;

    return &maze->grid[row * maze->cols + col];

};

#include <stdlib.h>   // rand
#include <time.h>     // for srand
#include "maze.h"

typedef struct {
    int dr;
    int dc;
    int wall_current;
    int wall_neighbor;
} NeighborInfo;

void maze_step(Maze *maze)
{
    if (!maze || maze->finished)
        return;

    // Get signed row/col for arithmetic
    int r = (int)maze->current_row;
    int c = (int)maze->current_col;
    
    NeighborInfo neighbors[4];
    int count = 0;

    // North
    if (r > 0)
    {
        Cell *n = &maze->grid[(r - 1) * maze->cols + c];
        if (!n->visited)
            neighbors[count++] = (NeighborInfo){-1, 0, 0, 1};
    }
    // South
    if (r + 1 < (int)maze->rows)
    {
        Cell *n = &maze->grid[(r + 1) * maze->cols + c];
        if (!n->visited)
            neighbors[count++] = (NeighborInfo){1, 0, 1, 0};
    }
    // West
    if (c > 0)
    {
        Cell *n = &maze->grid[r * maze->cols + (c - 1)];
        if (!n->visited)
            neighbors[count++] = (NeighborInfo){0, -1, 2, 3};
    }
    // East
    if (c + 1 < (int)maze->cols)
    {
        Cell *n = &maze->grid[r * maze->cols + (c + 1)];
        if (!n->visited)
            neighbors[count++] = (NeighborInfo){0, 1, 3, 2};
    }

    if (count > 0)
    {
        int idx = rand() % count;
        int nr = r + neighbors[idx].dr;
        int nc = c + neighbors[idx].dc;
        printf("Removing wall between (%d,%d) and (%d,%d)\n", r, c, nr, nc);
        Cell *neighbor = &maze->grid[nr * maze->cols + nc];

        // Remove walls...
        switch (neighbors[idx].wall_current)
        {
        case 0:
            maze->grid[r * maze->cols + c].wall_north = false;
            break;
        case 1:
            maze->grid[r * maze->cols + c].wall_south = false;
            break;
        case 2:
            maze->grid[r * maze->cols + c].wall_west = false;
            break;
        case 3:
            maze->grid[r * maze->cols + c].wall_east = false;
            break;
        }
        switch (neighbors[idx].wall_neighbor)
        {
        case 0:
            neighbor->wall_north = false;
            break;
        case 1:
            neighbor->wall_south = false;
            break;
        case 2:
            neighbor->wall_west = false;
            break;
        case 3:
            neighbor->wall_east = false;
            break;
        }

        // Push current onto stack
        maze->stack_rows[maze->stack_size] = r;
        maze->stack_cols[maze->stack_size] = c;
        maze->stack_size++;

        // Mark neighbor visited immediately
        neighbor->visited = true;
        // Move to neighbor
        maze->current_row = nr;
        maze->current_col = nc;
    }

    else if (maze->stack_size > 0)
    {
        // Backtrack if no unvisited neighbors
        maze->stack_size--;
        maze->current_row = maze->stack_rows[maze->stack_size];
        maze->current_col = maze->stack_cols[maze->stack_size];
    }
    else
    {
        // Maze generation finished
        maze->finished = true;
    }
    
}
