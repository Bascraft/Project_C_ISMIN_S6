#include "../lib/SDL_env.h"


typedef struct
{
    int index;
    char* author;
    int timestamp;
    char* name_house;
    Map house_info;
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
    char* player;
} Blockchain;

typedef struct
{
    int nb_players;
    char list[9];
} Arena;

//Procedures de bases des blockchains
Blockchain* init_blockchain(int player);
void calc_new_hash(Block* block);
unsigned long hash_timestamp(int timestamp);
void stock(char* file_name, Block* block, Blockchain* Chains[9], Arena* Players);
int proof_of_work(Block* block, Blockchain* Chains[9], Arena* Players);

//Procedures de recuperation et sauvegarde de la blockchain
void save_write(char* file_name, Block* block);
Blockchain* get_save(char* file_name, int player);
//void save_map(char* file_name, char* nom_fichier_level,Map* map, char* player, Blockchain* Chains[9], Arena* Players, int nb_house);
