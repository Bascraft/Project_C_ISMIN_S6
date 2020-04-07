//image de la taille de 40x40
#include "SDL_base.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include "SDL/SDL_ttf.h"
#include <string.h>
#include "SDL_perso.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define Buffer_size 5000


#define MAX_PLAYERS 10
//On met en place les parametres de hachage
#define HASH_SIZE		37987	/* Prime number */
#define HASH_KEY		127

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
typedef struct
{
    int index;
    char* author;
    int timestamp;
    char* name_house;
    Map* house_info;
    int posx, posy;
    int hash;
} Info;

typedef struct Block Block;
struct Block
{
    Info* info;
    int previous_hash;
    Block* suivant;
};

typedef struct
{
    int size;
    Block* head;
    Block* courant;
    char player;
} Blockchain;

typedef struct
{
    int nb_players;
    char list[9];
} Arena;


//fonction qui initialise la map en mettant tous avec de la grass
//void init_map(Map *map);
void new_house(int x,int y,int taille_x,int taille_y);
int Bouge_sprite(SDL_Event event,Sprite *sprite,int *quit,Map map);
void Afficher(SDL_Surface* screen,Map map,Sprite *sprite);
void ChargerMap_level(char *nom_fichier_prop,char* nom_fichier_level,Map* map);
void save_map(char* nom_fichier_level,Map* map);
void FreeMap(Map* map);
void main_Menu(MainMenu *menu,SDL_Event event,int* quit_menu,int* quit_game,SDL_Surface* screen,int largeurscreen,int hauteurscreen);

int world(int nb_house,char* file_name_blockchain, char* player, Blockchain* Chains[9], Arena* Players,char* nom_fichier_prop,char* nom_fichier_level,SDL_Surface* screen,SDL_Event event,Sprite *perso,Map monde,Map maison);
void in_house(char* file_name_blockchain, char* player, Blockchain* Chains[9], Arena* Players,int* nb_house,SDL_Surface* screen,SDL_Event event,Sprite *perso,Map map,Block *block);
void game();
void affichersprite(SDL_Surface* screen,Sprite *sprite);



//Procedures de bases des blockchains
Blockchain* init_blockchain(int player);
void calc_new_hash(Block* block);
unsigned long hash_timestamp(int timestamp);
void stock(char* file_name, Block* block, Blockchain* Chains[9], Arena* Players, int* nb_house);
int proof_of_work(Block* block, Blockchain* Chains[9], Arena* Players);

//Procedures de recuperation et sauvegarde de la blockchain
void save_write(char* file_name_blockchain, Block* block);
Blockchain* get_save(char* file_name_blockchain, int player);
void make_block(char* file_name_blockchain, char* player, Blockchain* Chains[9], Arena* Players, int* nb_house, Sprite* perso, Map* map,int sauv,Block *block);
Block* find_block(Blockchain* chain, int x, int y);
void new_player(char* file_name_blockchain, Arena* Players, Blockchain* Chains[9]);