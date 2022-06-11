#ifndef __DRAWER_H__
#define __DRAWER_H__

#include <stdio.h>
#include "../game/game.h"


//ANSI code 

//function for clearing the screen
static inline void screenCleaner(){ printf("\033[2J"); }

//function for hiding the cursor
static inline void cursorHider(){ printf("\033[?25l"); }

//function for showing the cursor 
static inline void cursorAppear(){ printf("\033[?25h"); }

//function for moving the cursion using coordinates: x,y
static inline void cursorMover(int y,int x){ printf("\033[%d;%dH", y + 5, x); }

//function for setting specific color
static inline void colorSetter(int c){ printf("\033[%dm  ", c); }

//function for reseting everything
static inline void reset(){ printf("\033[0m"); }

//function for deleting screen
static inline void cleanAll(){ printf("\e[1;1H\e[2J"); }

//Function for setting a grid in terminal window
void gridSetter (Grid gr);



//Function for Setting grid in the terminal
void set_grid (Grid gr);


//Function for starting the game
void gameStart(Grid *gr, Grid *gc);

#endif
