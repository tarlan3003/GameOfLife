#include "./console/drawer.h"
#include "./game/game.h"



int main() {

	Grid gr, gc;
	grid_initializer(&gr);
	new_grid (gr.rowNum, &gc);
	gridDuplicate(gr, gc);

	gameStart(&gr, &gc);

	free_memory(&gr);
	free_memory(&gc);
	return 0;
}
