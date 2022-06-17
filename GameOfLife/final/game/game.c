#include "game.h"



void grid_initializer (Grid* gr){

	int i,j,n,size,exist;

	printf("Enter the size to be in the matrix, maximum 10: ");
	while(1){
		scanf("%d", &size);
		if(size > 0 && size <= 10)
			break;
		else
			printf("The matrix size must be between 0 and 10: \n");
	}

	new_grid(size,gr);

	printf("Enter the number of existing cells in grid: ");
	while(1){
		scanf("%d", &exist);
		if(exist < (gr->rowNum * gr->colNum))
			break;
		else
			printf("The number must be less than %d\n", gr->rowNum*gr->colNum);
	}
	
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
}



void new_grid(int grid_size, Grid*  gr){
	gr->rowNum = grid_size;
	gr->colNum = grid_size;
  	gr->age = 0;

	gr->cells = calloc(gr->rowNum, 2*sizeof(int*)); //allocating memory for cells
	if(gr->cells != NULL){
        for(int i = 0; i < gr->rowNum; ++i) {
            gr->cells[i] = calloc(gr->colNum, 2*sizeof(int)); //allocating memory for each column
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



int countNeighbourCircular(int i, int j, Grid gr){
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



int countNeighbourClipped(int i, int j, Grid gr){
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

void init_grid_from_file (char * filename, Grid* g){
	FILE * pfile;
	pfile = fopen(filename, "r");
	int i,j,n,size,alive;

	fscanf(pfile, "%d", & size);


	new_grid(size,g);

	fscanf(pfile, "%d", & alive);
	for (n=0; n< alive; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		aliveSetter(i,j,*g);
	}
	
	fclose (pfile);

	g->age = 0;
	return;
}

