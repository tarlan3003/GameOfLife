#include "game.h"

void grid_initializer (Grid* gr){

	int i,j,n,size,exist;

	printf("Enter the matrix size(MAX 10): ");
	while(1){
		scanf("%d", &size);
		if(size > 0 && size <= 10)
			break;
		else
			printf("Enter correct size(0, 10)\n");
	}
	
	new_grid(size,gr);

	printf("How many cells do you want to be alive: ");
	
	while(1){
		scanf("%d", &exist);
		if(exist < (gr->rowNum * gr->colNum))
			break;
		else
			printf("The nb of existing cells must be less than %d\n", gr->rowNum*gr->colNum);
	}

	for (n = 0; n < exist; ++n){
	
		while(1){
			//choosing random cells
			i = rand() % (gr->rowNum);
			j = rand() % (gr->colNum);

			if( !isLiving(i, j, *gr) ) //if they are not alive we break
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

	gr->cells =  calloc(gr->rowNum , sizeof(int*)); //allocating memory for cells
	if(gr->cells != NULL){
        for(int i = 0; i < gr->rowNum; ++i) {
            gr->cells[i] = calloc(gr->colNum, sizeof(int)); //allocating memory for each cell columns
            if (gr->cells[i] == NULL) {
              printf("Failed to allocate memory\n");
              exit(0);
            }
        }
	}else{
        printf("Failed to allocate memory.\n");
        exit(0);
	}
}


void free_memory(Grid* gr){
	for(int i = 0; i < gr->rowNum; ++i){
		free(gr->cells[i]);
	}
	free(gr->cells);
}




