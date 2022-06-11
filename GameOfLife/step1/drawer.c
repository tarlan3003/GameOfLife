#include "drawer.h"



void gridSetter (Grid gr){
	cleanAll();

	printf("---------------------------\n");
	printf("This is random board test\n");
	printf("---------------------------\n");
	printf("For exiting from program, press q then enter\n");
	printf("---------------------------------------------\n");
	cursorHider();

	for(int i= 0; i<gr.rowNum; ++i){
		cursorMover(i+2,10);
		for(int j= 0; j<gr.colNum; ++j){
			(isLiving(i, j, gr)) ? colorSetter(41) : colorSetter(47); //41 for red & 47 for white
		}
	}

	reset();
	cursorAppear();
	cursorMover(gr.rowNum+5,0);

}



void gameStart(Grid *gr){
	char c = getchar();
	while (c != 'q'){
		switch (c) {
            case 'n' :
    		{   
                break;
            }
            
            default :
            {
                printf("\n\e[1A");
                break;
            }
        }
        gridSetter(*gr);
        c = getchar();
    }
}


