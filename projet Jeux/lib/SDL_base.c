#include "SDL/SDL.h"
#include "SDL/SDL_image.h" 
#include "SDL_base.h"



void init_SDL(){
    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
 
    screen = SDL_SetVideoMode(hauteur, largeur, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    
 
    SDL_WM_SetCaption("Blockcraft XD", NULL);//faut choisir un nom :)



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