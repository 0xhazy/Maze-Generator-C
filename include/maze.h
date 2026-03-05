#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct 
{
    bool wall_north;
    bool wall_south;
    bool wall_east;
    bool wall_west;

    bool visited;
}Cell;
 typedef struct 
 {
    size_t rows;
    size_t cols;
    Cell *grid;
    // Generation state
    size_t current_row;
    size_t current_col;

    // Stack for backtracking
    size_t *stack_rows;
    size_t *stack_cols;
    size_t stack_size;
    size_t stack_capacity;

    bool finished;

 }Maze;
 
bool maze_init(Maze *maze, size_t rows, size_t cols);

void maze_destroy(Maze *maze);

Cell *maze_get_cell(Maze *maze, size_t rows, size_t cols);

void maze_step(Maze *maze);



#endif