#ifndef __GAME_H__
#define __GAME_H__

#include <stdlib.h>
#include <stdio.h>

//struct for grid
typedef struct grid {
    int rowNum;       //number of rows
    int colNum;       //number of columns
    int **cells;      //cells table
    int age;          //grid age
} Grid;


//allocate a memory for cells and set all cells to dead
void new_grid (int grid_size, Grid* g);

//frees the grid
void free_memory(Grid* g);


//initializes the grid
void grid_initializer(Grid* gr);



//turns given cells into alive cells
static inline void aliveSetter(int i, int j, Grid gr){gr.cells[i][j] = 1;}

//if alive or not
static inline int isLiving(int i, int j, Grid gr){return gr.cells[i][j] == 1;}


//set given cells into dead cell
static inline void deadSetter(int i, int j, Grid gr){gr.cells[i][j] = 0;}

//if cell is dead or not
static inline int isDead(int i, int j, Grid gr){return gr.cells[i][j] == 0;}


void gridDuplicate (Grid gs, Grid gd);


int neighboursCircularCount(int i, int j, Grid gr);

//checks how many clipped neighbours cell has
int clippedNeighbourCount(int i, int j, Grid gr);

//updating cell
void reform (Grid *gr, Grid *gc, int (*check_neighbours)(int, int, Grid));

static inline int moduleOfNum(int a, int b){ return ((a+b)%b); }


#endif
