//image de la taille de 40x40
#include "SDL_base.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h" 
#define nb_block_X largeur/40
#define nb_block_Y hauteur/40
//fonction qui initialise la map en mettant tous avec de la grass
void init_map(SDL_Surface ***tab_map,SDL_Rect **tab_position);