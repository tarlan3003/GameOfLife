#include "drawer.h"



void set_grid (Grid gr, int mode){
	cleanAll();

	if(mode) 
		printf("Welcome to circular mode\n");
	else 
		printf("You're at clipped mode\n");
	printf("PRESS ENTER \n\n");
	printf("GROWTH: %d\n", gr.age);
	printf("Press q to exit then enter\n");
	cursorHider();

	for(int i= 0; i < gr.rowNum; ++i){
		cursorMover(i+2,10);
		for(int j= 0; j < gr.colNum; ++j){
			( isLiving(i, j, gr) ) ? colorSetter(41) : colorSetter(47); //41 for red  & 40 for white 
		}
	}

	reset();
	cursorAppear();
	cursorMover(gr.rowNum+5,0);
}



void gameStart(Grid *gr, Grid *gc){
	int circular = 1;
	char input = getchar();
	int (*neighbours)(int, int, Grid) = clippedNeighbourCount;
	while (input != 'q') 
	{
		switch (input) {
            case '\n' :
            { 
                reform(gr, gc, neighbours);
                break;
            }
            
            case 'c':
            { 
                circular = !circular;
                if(circular) 
                	neighbours = &clippedNeighbourCount;
                else 
                	neighbours = &clippedNeighbourCount;
                getchar ();
                break;
            }
            
            default :
            {
                printf("\n\e[1A");
                break;
            }
        }
		
        set_grid(*gc,circular);
        input = getchar();
    	
    }
}

