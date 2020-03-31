#include <stdio.h>
#include <stdlib.h>


//#include "blockchain.h"
#include "../lib/SDL_env.h"



int main(int argc, char* args[])
{
	init_SDL();
    SDL_Surface *screen;
    Sprite *perso;
    perso = InitialiserSprite(320,240,320,240,"image_block/perso.bmp");
	Map W;
    SDL_Event event;
    int quit_menu = 0;
    int quit_game = 1;
    MainMenu menu;
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF); // Ouverture de la fenêtre
	    
    SDL_WM_SetCaption("Fantom Building", NULL);//faut choisir un nom :)
	while (!quit_menu){
        main_Menu(&menu,event,&quit_menu,&quit_game,screen,640,480);
        SDL_Flip(screen);}
	if (quit_game == 2){
        ChargerMap_level("level/level_prop.txt","level/level.txt",&W);
    	world("level/level_prop.txt","level/level.txt",screen,event,perso,W);}
		
	

    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}
 
