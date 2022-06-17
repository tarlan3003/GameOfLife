#include "./console/drawer.h"
#include "./game/game.h"


int main() {

	Grid g, gc;
	char c;
	int n;
	char filename[20];

	printf("Would you like to enter your own configuration? (Y/N) ");

	scanf("%c", &c);
	if(c == 'Y' || c == 'y'){
		grid_initializer(&g);
	}else{
		printf("Enter filename num, which is between 0 and 9\n");
		while(1){
			scanf("%d", &n);
			if(n > 0 && n < 10)
				break;
		}

		sprintf(filename, "../grids/grid%d.txt", n);
		printf("%s\n",filename);
		init_grid_from_file(filename,&g);
	}

	new_grid (g.rowNum, &gc);
	gridDuplicate(g, gc);

	gameStart(&g, &gc);

	free_memory(&g);
	free_memory(&gc);
	return 0;
}
