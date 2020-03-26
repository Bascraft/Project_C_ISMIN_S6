#include "SDL/SDL.h"
#include "SDL/SDL_image.h" 
#include "SDL_base.h"



void init_SDL(){
    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
}

void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset; 
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}


void ErrorQuit(const char* error)
{
	puts(error);
	SDL_Quit();
}
