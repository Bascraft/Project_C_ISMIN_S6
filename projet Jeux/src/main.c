#include <stdio.h>
#include <stdlib.h>


//#include "blockchain.h"
#include "/home/herrrouin/Bureau/ProjetC_Bastien/lib/SDL_env.h"



int main(int argc, char* args[])
{
    init_SDL();
    SDL_Surface *screen;
    Sprite *perso;
    perso = InitialiserSprite(320,240,320,240,"image_block/perso.bmp");
    SDL_Event event;
    Map map;
    int quit = 0;
    ChargerMap_level("level/level_prop.txt","level/level.txt",&map);
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF); // Ouverture de la fenêtre
    SDL_WM_SetCaption("Blockcraft XD", NULL);//faut choisir un nom :)
    while (!quit)
    {   
        Bouge_sprite(event,perso,&quit,map);
        Afficher(screen,map,perso);
        affichersprite(screen,perso);
        SDL_Flip(screen);
    }
    
    
    
    //pause(); // Mise en pause du programme
    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}
 
