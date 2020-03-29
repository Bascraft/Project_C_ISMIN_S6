//image de la taille de 40x40
#include "SDL_base.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h" 
#include <string.h>
#include "SDL_perso.h"

#define Buffer_size 5000
typedef char blockind;
typedef struct
{
	SDL_Rect R;
	int env;
} TileProp;

typedef struct Map
{
    //recuperation dans le fichier level.txt
    int LARGEUR_TILE,HAUTEUR_TILE;//dimension block
    int largeur_fenetre,hauteur_fenetre;//dimension fenetre
    int nb_block_largeur_monde,nb_block_hauteur_monde;//dimension du monde
    int nb_blockX_tileset,nb_blockY_tileset;
    SDL_Surface *image_block;//tileset
    TileProp *props;//tableau des propriete de chaque block
    blockind **tab_map;  
}Map;

//fonction qui initialise la map en mettant tous avec de la grass
//void init_map(Map *map);
void Bouge_sprite(SDL_Event event,Sprite *sprite,int *quit,Map map);
void Afficher(SDL_Surface* screen,Map map,Sprite *sprite);
void ChargerMap_level(char *nom_fichier_prop,char* nom_fichier_level,Map* map);
void FreeMap(Map* map);
