#include "game_sdl.h"


void grid_initializer (Grid* gr){

	int i,j,n,size,exist;

	printf("Enter matrix size: ");
	scanf("%d", &size);
	
	new_grid(size,gr);

	printf("Enter active cells number: ");
	scanf("%d", &exist);
	for (n = 0; n < exist; ++n){
	
		while(1){
			i = rand() % (gr->rowNum);
			j = rand() % (gr->colNum);

			if( !isLiving(i, j, *gr))
				break;
		}	
		aliveSetter(i,j,*gr);
	}

	gr->age = 0;
	return;
}


void gridInitFromFile(char * filename, Grid* gr){
    FILE * pfile;
    pfile = fopen(filename, "r");
    if(!pfile) fprintf(stderr, "Error while opening the file\n" );
    int i,j,n,size,exist;

    fscanf(pfile, "%d", & size);

    new_grid(size,gr);

    fscanf(pfile, "%d", & exist);
    for (n=0; n< exist; ++n){
        fscanf(pfile, "%d", & i);
        fscanf(pfile, "%d", & j);
        aliveSetter(i,j,*gr);
    }
    
    fclose (pfile);
    gr->age = 0;
}


void new_grid(int grid_size, Grid*  gr){
	gr->rowNum = grid_size;
	gr->colNum = grid_size;
  	gr->age = 0;

	gr->cells = calloc(gr->rowNum, 2*sizeof(int*));
	if(gr->cells != NULL){
        for(int i = 0; i < gr->rowNum; ++i) {
            gr->cells[i] = calloc(gr->colNum, 2*sizeof(int));
            if (gr->cells[i] == NULL) {
              fprintf(stderr, "Failed to allocate memory.\n");
              exit(0);
            }
        }
	}else{
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
	}
}

void free_memory(Grid* gr){
	for(int i = 0; i < gr->rowNum; ++i){
		free(gr->cells[i]);
	}
	free(gr->cells);
}


void gridDuplicate (Grid gs, Grid gd){
	int i, j;
	for (i=0; i<gs.rowNum; ++i) {
		for (j=0; j<gs.colNum; ++j) {
			gd.cells[i][j] = gs.cells[i][j];
		}
	}
}


int countNeighboursCircular(int i, int j, Grid gr){
	int neighbour = 0, r = gr.rowNum, c = gr.colNum;

	// at top left
	neighbour+= isLiving(moduleOfNum(i-1,r),moduleOfNum(j-1,c),gr);
	// at top same column	
	neighbour+= isLiving(moduleOfNum(i-1,r),moduleOfNum(j,c),gr); 
	// at right top		
	neighbour+= isLiving(moduleOfNum(i-1,r),moduleOfNum(j+1,c),gr);
	// at same row left	
	neighbour+= isLiving(moduleOfNum(i,r),moduleOfNum(j-1,c),gr);
	// at same row right		
	neighbour+= isLiving(moduleOfNum(i,r),moduleOfNum(j+1,c),gr);
	// at bottom left		
	neighbour+= isLiving(moduleOfNum(i+1,r),moduleOfNum(j-1,c),gr);	
	//at bottom same col
	neighbour+= isLiving(moduleOfNum(i+1,r),moduleOfNum(j,c),gr);
	//at bottom right		
	neighbour+= isLiving(moduleOfNum(i+1,r),moduleOfNum(j+1,c),gr);	

	return neighbour;
}



int clippedNeighbourCount(int i, int j, Grid gr){
	int neighbour = 0, r = gr.rowNum, c = gr.colNum;

	// at left top
	neighbour += i > 0 && j > 0 && isLiving(i-1, j-1, gr);
	// at top same col 		
	neighbour += i > 0 && isLiving(i-1, j, gr); 
	// at right top					
	neighbour += i > 0 && j < c && isLiving(i-1, j+1, gr); 
	// at same row left		
	neighbour += j > 0 && isLiving(i, j-1, gr); 
	// at same row right					
	neighbour += j < c && isLiving(i, j+1, gr); 
	// at bottom left					
	neighbour += i < r -1 && j > 0 && isLiving(i+1, j-1, gr); 	
	// at bottom same col
	neighbour += i < r -1 && isLiving(i+1, j, gr); 	
	// at bottom right			
	neighbour += i < r -1 && j < c && isLiving(i+1, j+1, gr); 
		
	return neighbour;
}




void reform (Grid *gr, Grid *gc, int (*neighbourCount)(int, int, Grid)){
    gridDuplicate(*gr,*gc); 
    int i,j,r = gr->rowNum, c = gr->colNum, neighbour;
    for (i = 0; i < r; i++){
  		for (j = 0; j < c; ++j){
			
			neighbour = neighbourCount(i, j, *gc);
			if (isLiving(i,j,*gr)){ 
			  if ( neighbour != 2 && neighbour != 3 ) {
			  	deadSetter(i, j, *gr);
			  }
			}else if ( neighbour == 3 ) {
			    aliveSetter(i, j, *gr);
			}
			
        }
  	}
  gc->age++;
}



void gridDisplayer ( Grid gr , SDL_Renderer *renderer, int mode) {
	
    printf("\e[1;1H\e[2J"); // deleting ecran
    printf("\033[31m");
    printf("\033[%d;%dH", 2, 0); //cursorMover
    printf("Evoluation: %d\n", gr.age);
    if(mode) printf("circular mode\n\n");
    else  printf("clipped mode\n");
    printf("For growing please click n\n");
    printf("For changing the mode please click c\n");
    printf("For exit from program click q\n");
    printf("\033[?25l"); // cursorHider


       
    //setting color to white
    SDL_SetRenderDrawColor(renderer, 0, 43, 54, SDL_ALPHA_OPAQUE);
    
    int CELL_SIZE = 400 / gr.rowNum;

    //clean the screen
    SDL_RenderClear(renderer);

    //drawing with black
    SDL_SetRenderDrawColor(renderer, 34, 108, 128, SDL_ALPHA_OPAQUE);

    //setting lines for rows
    for(int i=0; i<=gr.rowNum; i++) {
        SDL_RenderDrawLine(renderer, 
            	//coordinates: x1 y1 and x2 y2
                10, CELL_SIZE*i+10,         
                410, CELL_SIZE*i+10 
        );
    }

    //same operation for column lines
    for(int i=0; i<=gr.colNum; i++) {            
        SDL_RenderDrawLine(renderer,                 
                CELL_SIZE*i+10, 10,                    
                CELL_SIZE*i+10, 410  
        );
    }

    //setting drawing color to blue
    SDL_SetRenderDrawColor(renderer, 220, 50, 47, SDL_ALPHA_OPAQUE);

    for( int y=0; y<gr.rowNum; y++ ) {
        for( int x=0; x<gr.colNum; x++) {
            if(isLiving(y, x, gr)) {
                SDL_Rect r = {
                    x*CELL_SIZE+11, 
                    y*CELL_SIZE+11, 
                    CELL_SIZE-1,   // width  
                    CELL_SIZE-1    // height
                };

                SDL_RenderFillRect(renderer, &r);
            }
        }
    }

    SDL_RenderPresent(renderer);

    printf("\033[0m"); // reset
    printf("\033[?25h"); // cursorAppear
    printf("\033[%d;%dH", gr.rowNum+5, 0); //cursorMover
}