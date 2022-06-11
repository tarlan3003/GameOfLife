#include "./game_sdl/game_sdl.h"


int main() {

	Grid g, gc;
    char c;
    int n;
    char filename[20];

    printf("Would you like to  enter your own configuration? (Y/N) ");

    scanf("%c", &c);
    if(c == 'Y' || c == 'y'){
        grid_initializer(&g);
    }else{
        printf("Add filename by choosing nums between 0 and 9\n");
        while(1){
            scanf("%d", &n);
            if(n > 0 && n < 10)
                break;
        }

        sprintf(filename, "../grids/grid%d.txt", n);
        printf("%s\n",filename);
        gridInitFromFile(filename,&g);
    }
    
	new_grid (g.rowNum, &gc);
	gridDuplicate(g, gc);

	
    SDL_Renderer *g_renderer = NULL; 
    SDL_Window   *g_window   = NULL; 
    int circular = 1;
    int (*pt_neighbours)(int, int, grid) = check_neighbours_clipped;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr,"Failed to init SDL2 \n");
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
                            evoluation(&g, &gc, pt_neighbours);
                            break;
                        }
                    }
                    break;

                }
            }
        }

        display_grid(gc, g_renderer, circular );

        // SDL_RenderPresent(g_renderer);
    }


        
	free_grid(&g);
	free_grid(&gc);

    /* clean up when we're done */
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    
    return 0;
}
