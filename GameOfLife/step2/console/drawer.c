#include "drawer.h"

void gridSetter (Grid gr){
	cleanAll();

	printf("PRESS ENTER\n");
	printf("STEP 2 of the game\n\n");
	printf("GROWTH: %d\n", gr.age);
	printf("press q then enter for exit\n");
	cursorHider();

	for(int i= 0; i < gr.rowNum; ++i){
		cursorMover(i+2,10);
		for(int j= 0; j < gr.colNum; ++j){
			( isLiving(i, j, gr) ) ? colorSetter(41) : colorSetter(47); //41 for red & 47 for white
		}
	}

	reset();
	cursorAppear();
	cursorMover(gr.rowNum+5,0);

}



void gameStart(Grid *gr, Grid *gc){
	char input = getchar();
	while (input != 'q')
	{
        switch (input) {
            case '\n' :
            { 
                reform(gr, gc);
                break;
            }
            
            default :
            {
                printf("\n\e[1A");
                break;
            }
        }
        
        gridSetter(*gc);
        input = getchar();
    	
    }
}

