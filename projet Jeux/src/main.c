#include <stdio.h>
#include <stdlib.h>


//#include "blockchain.h"
#include "../lib/SDL_env.h"



int main(int argc, char* args[])
{
    int player = 3;
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

    //get_save(save_name,0);
	init_SDL();
    int *nb_house;

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
    ChargerMap_level("level/level_prop.txt","level/levelcopy.txt",&maison);
    save_map("level/levelcopy.txt",&maison);
	while (!quit_menu){
        main_Menu(&menu,event,&quit_menu,&quit_game,screen,640,480);
        SDL_Flip(screen);}
    while (!quit)
    {
        if (quit_game == 2){
            
            ChargerMap_level("level/level_prop.txt","level/level.txt",W);
            world(save_name, &Players->list[0], Chains, Players, "level/level_prop.txt", "level/level.txt", screen, event, perso, (*W), maison);
            }
        quit = 1;
    }	
	//save_map("level/world.txt",W);

    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme


    /*int nb_house = 0;
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
    
    Map* map = malloc(sizeof(Map));
    Sprite* perso;
    perso = InitialiserSprite(20,10,25,10,"image_block/perso.bmp");
    make_block(save_name, &Players->list[0], Chains, Players,  &nb_house, perso, map);
    perso = InitialiserSprite(20,10,25,20,"image_block/perso.bmp");
    make_block(save_name, &Players->list[0], Chains, Players, &nb_house, perso, map);
    perso = InitialiserSprite(20,10,25,30,"image_block/perso.bmp");
    make_block(save_name, &Players->list[0], Chains, Players, &nb_house, perso, map);
    
    Block* block = malloc(sizeof(Block));
    block->info = malloc(sizeof(Info));
    block = find_block(Chains[0], 25, 20);
    if (block == NULL)
    {
        printf("pedu ca marche pas...\n");
    }
    if (block != NULL)
    {
        printf("BG !!!\n");
    }
    new_player(save_name, Players, Chains);*/
}
 
