#include "./game_sdl/game_sdl.h"


int main() {

	Grid gr, gc;
    char c;
    int n;
    char filename[20];    
    grid_initializer(&gr);
    
	new_grid (gr.rowNum, &gc);
	gridDuplicate(gr, gc);

	// start_game(&g, &gc);
    SDL_Renderer *g_renderer = NULL; //drawing on screen
    SDL_Window   *g_window   = NULL; //OS window
    int circular = 1;
    int (*pt_neighbours)(int, int, Grid) = countNeighbourClipped;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr,"Failed to initilize SDL\n");
        return 0;
    }

    g_window = SDL_CreateWindow("Game Of Life",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          420, 420, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
    g_renderer = SDL_CreateRenderer(g_window, -1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    assert (g_renderer != NULL);

    int quit = 0;
    while (!quit)
    {
        SDL_Event event;
        while (!quit && SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    quit = 1;
                    break;
                }
                
                case SDL_KEYDOWN:
                {
                    
                    switch(event.key.keysym.sym){
                        case SDLK_c:
                        {
                            circular = !circular;
                            if(circular) pt_neighbours = &countNeighbourCircular;
                            else pt_neighbours = &countNeighbourClipped;
                            break;
                        } 
                        case SDLK_n:
                        {
                            reform(&gr, &gc, pt_neighbours);
                            break;
                        }
                    }
                    break;

                }
            }
        }

        gridDisplayer(gc, g_renderer, circular );

    }


        
	free_memory(&gr);
	free_memory(&gc);

    //cleaning things up
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    
    return 0;
}
