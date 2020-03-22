#include <stdio.h>
#include <stdlib.h>


//#include "blockchain.h"
#include "/home/herrrouin/Bureau/ProjetC_Bastien/lib/SDL_env.h"

 
int main(int argc, char* args[])
{
    init_SDL();
    SDL_Surface ***tab_map;
    SDL_Rect **tab_position;
    init_map(tab_map,tab_position);
    pause(); // Mise en pause du programme
    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}
 
