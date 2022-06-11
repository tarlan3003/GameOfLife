#include "drawer.h"
#include "game.h"


int main() {
	//testing all functions
	Grid gr;
	
	grid_initializer(&gr);
	gridSetter(gr);
	gameStart(&gr);
	free_memory (&gr);

	return 0;
}
