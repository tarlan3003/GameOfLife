#ifndef __GAME_SDL_H__
#define __GAME_SDL_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <string.h>


//struct for grid
typedef struct grid {
    int rowNum;       //number of rows
    int colNum;       //number of columns
    int **cells;      //cells table
    int age;          //grid age
} Grid;


//function for allocation grid size of row*column
void new_grid (int grid_size, Grid* g);

void gridInitFromFile(char * filename, Grid* gr);

//free grid
void free_memory(Grid* gr);


void grid_initializer(Grid* gr);



//setting cells into alive cells
static inline void aliveSetter(int i, int j, Grid gr){gr.cells[i][j] = 1;}

//if cell is alive or not
static inline int isLiving(int i, int j, Grid gr){return gr.cells[i][j] == 1;}

//setting cells into dead cells
static inline void deadSetter(int i, int j, Grid gr){gr.cells[i][j] = 0;}

//if cell is dead or not
static inline int isDead(int i, int j, Grid gr){return gr.cells[i][j] == 0;}


void gridDuplicate (Grid gs, Grid gd);

//counting circular neighbours
int countNeighbourCircular(int i, int j, Grid gr);

//counting clipped neighbours
int countNeighbourClipped(int i, int j, Grid gr);

//updating cell
void reform (Grid *gr, Grid *gc, int (*check_neighbours)(int, int, Grid));

//finds the module 
static inline int moduleOfNum(int a, int b){ return ((a+b)%b); }

//displaying the grid
void gridDisplayer ( Grid g , SDL_Renderer *renderer, int mode);


#endif
