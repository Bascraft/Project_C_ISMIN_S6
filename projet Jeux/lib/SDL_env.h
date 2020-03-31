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

typedef struct MainMenu {
    SDL_Surface *image_play_default;
    SDL_Surface *image_play_enfonce;
    SDL_Surface *image_exit_default;
    SDL_Surface *image_exit_enfonce;
    int play_enfonce;
    int exit_enfonce;

}MainMenu;

//fonction qui initialise la map en mettant tous avec de la grass
//void init_map(Map *map);
void Bouge_sprite(SDL_Event event,Sprite *sprite,int *quit,Map map);
void Afficher(SDL_Surface* screen,Map map,Sprite *sprite);
void ChargerMap_level(char *nom_fichier_prop,char* nom_fichier_level,Map* map);
void save_map(char* file_name, char* nom_fichier_level,Map* map, char* player, Blockchain* Chains);
void FreeMap(Map* map);
void main_Menu(MainMenu *menu,SDL_Event event,int* quit_menu,int* quit_game,SDL_Surface* screen,int largeurscreen,int hauteurscreen);

void new_house(char* nom_fichier_level,int x,int y);
void world(char* nom_fichier_prop,char* nom_fichier_level,SDL_Surface* screen,SDL_Event event,Sprite *perso,Map monde);
void editor(char* nom_fichier_prop,char* nom_fichier_level,Map* map);
void game();
void affichersprite(SDL_Surface* screen,Sprite *sprite);
