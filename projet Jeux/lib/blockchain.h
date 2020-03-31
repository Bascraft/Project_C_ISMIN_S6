#include "../lib/SDL_env.c"

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

typedef struct
{
    Info* info;
    int previous_hash;
} Block;

typedef struct
{
    int size;
    Block* head;
    char* player;
} Blockchain;

typedef struct
{
    int nb_players;
    char* list;
} Arena;

//Procedures de bases des blockchains
void init_blockchain(Blockchain* chain);
void calc_new_hash(Block* block);
unsigned long hash_index(int index);
unsigned long hash_author(char* author);
unsigned long hash_timestamp(int timestamp);
void stock(char* file_name, Block* block, Blockchain* chain, Arena* Players);
int proof_of_work(Block* block, Blockchain* Chains, Arena* Players);

//Procedures de recuperation et sauvegarde de la blockchain
void save_write(char* file_name, Block* block);
Blockchain* get_save(char* file_name, Blockchain* Chains);
void save_map(char* file_name, char* nom_fichier_level,Map* map, char* player, Blockchain* Chains, Arena* Players);
