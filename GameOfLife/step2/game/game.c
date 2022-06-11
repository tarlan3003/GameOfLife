#include "game.h"



void grid_initializer (Grid* gr){

	int i,j,n,size,exist;

	printf("Enter the matrix size(MAX 10): ");
	while(1){
		scanf("%d", &size);
		if(size > 0 && size <= 10)
			break;
		else
			printf("Please enter size between 0-10\n");
	}

	new_grid(size,gr);

	printf("Enter the number of existing cells: ");
	while(1){
		scanf("%d", &exist);
		if(exist < (gr->rowNum * gr->colNum))
			break;
		else
			printf("Enter less than %d \n", gr->rowNum*gr->colNum);
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
              fprintf(stderr, "Failed to allocate memory\n"); //error case
              exit(0);
            }
        }
	}else{
        fprintf(stderr, "Failed to allocate memory\n"); //error case
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
	return;
}



int neighbourCount(int i, int j, Grid gr){
	//checking for neighbours in different directions
	int neighbour = 0;

	// top left
	neighbour += i > 0 && j > 0 && isLiving(i-1, j-1, gr); 
	//at top and same column					
	neighbour += i > 0 && isLiving(i-1, j, gr);
	//top right 								
	neighbour += i > 0 && j < gr.colNum && isLiving(i-1, j+1, gr); 
	//same row and left			// right top
	neighbour += j > 0 && isLiving(i, j-1, gr); 
	//same row and right								
	neighbour += j < gr.colNum && isLiving(i, j+1, gr); 
	//at bottom and left						
	neighbour += i < gr.rowNum -1 && j > 0 && isLiving(i+1, j-1, gr); 
	//at bottom and same column		
	neighbour += i < gr.rowNum -1 && isLiving(i+1, j, gr); 
	//at bottom and right					
	neighbour += i < gr.rowNum -1 && j < gr.colNum && isLiving(i+1, j+1, gr); 

	return neighbour;
}




void reform (Grid *gr, Grid *gc){
    gridDuplicate(*gr,*gc); 
    int i,j, neighbour;
    for (i = 0; i < gr->rowNum; i++){
  		for (j = 0; j < gr->colNum; j++){
		    
			neighbour = neighbourCount(i, j, *gc);
			if (isLiving(i,j,*gr)){ 
			  if ( neighbour != 2 && neighbour != 3 ){
			  	deadSetter(i,j,*gr);
			  }
			}else if ( neighbour == 3 ) {
			    aliveSetter(i,j,*gr);
			}
			
        }
  	}
  	gc->age++;
}


