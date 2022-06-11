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
void new_grid (int grid_size, Grid* gr);

//frees grid 
void free_memory(Grid* gr);


//initializes the grid
void grid_initializer(Grid* gr);


//turning given cells to alive cell
static inline void aliveSetter(int i, int j, Grid gr){gr.cells[i][j] = 1;}

//if cells is alive or not
static inline int isLiving(int i, int j, Grid gr){return gr.cells[i][j] == 1;}

//setting given cell into dead cell
static inline void deadSetter(int i, int j, Grid gr){gr.cells[i][j] = 0;}


//if cell is dead or not
static inline int isDead(int i, int j, Grid g){return g.cells[i][j] == 0;}

//function for copying grid
void gridDuplicate (Grid gs, Grid gd);

//returns number of neighbours
int neighbourCount(int i, int j, Grid gr);


//function for reforming cells
void reform (Grid *gr, Grid *gc);

#endif
