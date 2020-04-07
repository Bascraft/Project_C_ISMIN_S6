#include <stdio.h>
#include <stdlib.h>


//#include "blockchain.h"
#include "../lib/SDL_env.h"



int main(int argc, char* args[])
{
    int player = 0;
    Blockchain* chain = init_blockchain(player);
    //chain->courant->info->hash = 0;
    printf("hash : %d\n", chain->courant->info->hash);

    char* save_name = "Blockchain.txt";
    Blockchain* Chains[9];
    Chains[0] = chain;
    Chains[1] = chain;
    Chains[2] = chain;
    Arena* Players = malloc(sizeof(Arena));
    Players->nb_players = 3;
    Players->list[0] = 0;
    Players->list[1] = 1;
    Players->list[2] = 2;





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
    new_house(110,10,10,10);
    SDL_WM_SetCaption("Fantom Building", NULL);
	while (!quit_menu){
        main_Menu(&menu,event,&quit_menu,&quit_game,screen,640,480);
        SDL_Flip(screen);}
    while (!quit)
    {
        if (quit_game == 2){
            ChargerMap_level("level/level_prop.txt","level/levelcopy.txt",&maison);
            ChargerMap_level("level/level_prop.txt","level/level.txt",W);
            world(0,save_name,player,Chains,Players,"level/level_prop.txt","level/level.txt",screen,event,perso,(*W),maison);
            }
        quit = 1;
    }	
	//save_map("level/world.txt",W);

    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}
 
