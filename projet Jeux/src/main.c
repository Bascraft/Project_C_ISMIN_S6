#include <stdio.h>
#include <stdlib.h>


//#include "blockchain.h"
#include "../lib/reseau.h"



int main(int argc, char* args[])
{
	init_SDL();
    SDL_Surface *screen;
    Sprite *perso;
    perso = InitialiserSprite(320,240,320,240,"image_block/perso.bmp");
	Map* W;
    Map maison;
    W = malloc(sizeof(Map));
    SDL_Event event;
    int quit_menu = 0;
    int quit_game = 1;
    int in_house = 0;
    int quit;
    quit = 0;
    MainMenu menu;
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF); // Ouverture de la fenêtre
    new_house(5,5,10,10);
    SDL_WM_SetCaption("Fantom Building", NULL);
	while (!quit_menu){
        main_Menu(&menu,event,&quit_menu,&quit_game,screen,640,480);
        SDL_Flip(screen);}
    while (!quit)
    {
        if (quit_game == 2){
            ChargerMap_level("level/level_prop.txt","level/levelcopy.txt",&maison);
            ChargerMap_level("level/level_prop.txt","level/world.txt",W);
            world("level/level_prop.txt","level/level.txt",screen,event,perso,(*W),maison);
            }
        quit = 1;
    }	
	

    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}
 
