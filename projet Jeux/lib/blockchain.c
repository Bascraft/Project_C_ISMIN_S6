#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_PLAYERS 10
//On met en place les parametres de hachage
#define HASH_SIZE		37987	/* Prime number */
#define HASH_KEY		127


//Procedures de bases des blockchains
void init_blockchain(Blockchain* chain)     //Initialise la chaine de bloc
{
    chain->size = 0;
    chain->head = NULL;
}

void calc_new_hash(Block* block)    //Calcule le hash du nouveau bloc
{
    int hash;
    int index = block->info->index;
    char* author = block->info->author;
    int timestamp = block->info->timestamp;
    hash = (index*HASH_KEY + (int) author) * hash_timestamp(timestamp);
    block->info->hash = hash;
}


unsigned long hash_timestamp(int timestamp)
{
    unsigned long hashValue = 0;
    hashValue = timestamp / 8;	//on cherche a perdre de la donnee binaire
    hashValue = hashValue*HASH_KEY;
    return hashValue % HASH_SIZE;
}

void stock(char* file_name, Block* block, Blockchain* Chains, Arena* Players)     //On ajoute un bloc a la chaine, a repeter pour tout les joueurs
{
    if (proof_of_work(block, Chains, Players)) //Si le block est valide on l'ajoute sur la chaine de chaque joueur
    {
        for (int player = 0; player<Players->nb_players; player ++)
        {
            Chains[player].size ++;
            block->previous_hash = Chains[player].head->info->hash;
            Chains[player].head = block;
        }
        save_write(file_name, block);
    }
    else
    {
        printf("C'est insalubre comme etablissement");
    }
    
}

//!!\\ reste a voir pour que les maisons ne se superposent pas
int proof_of_work(Block* block, Blockchain* Chains, Arena* Players)      //On teste que le nouveau bloc est bien present chez tout les joueurs
{
	FILE *f_house; 
    f_house = fopen(block->info->name_house, "r");
	int x_size, y_size;
	fscanf(&f_house, "%d %d", &x_size, &y_size);
    int house_size;
	house_size = x_size * y_size;
    if (house_size < 25)
            {
                return 0; //On suppose qu'une maison doit avoir une taille minimum de 25m2
            }
    //Si la maison est valide on verifie quelle est bien coherente avec toute les chaines du reseau
    int correct = 0;
	int wrong = 0;
    for (int player = 0; player<Players->nb_players; player ++)
    {
        
        if (Chains[player].head->info->hash == block->previous_hash && Chains[player].head->info->index == block->info->index-1)
        {
            correct ++;
        }
        else
        {
            wrong ++;
        }
    }
    if (correct >= wrong)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Procedures de recuperation et sauvegarde de blockchains
void save_write(char* file_name, Block* block)
{
	FILE* file;
	file = fopen(file_name, "a+");
	if (file!= NULL)
	{
		fprintf(file, "%d %s %d %s %d %d",&block->info->index, block->info->author, &block->info->timestamp, block->info->name_house, &block->info->hash, &block->previous_hash);
	}
	fclose(file);
}

Blockchain* get_save(char* file_name)
{
    Blockchain* new_chain;
    init_blockchain(new_chain);
    FILE file;
    file = fopen(file_name, "r");
    Block* block;
    while (fscanf(&file, "%d %s %d %s %d %d",&block->info->index, block->info->author, &block->info->timestamp, block->info->name_house, &block->info->hash, &block->previous_hash) == 6)
    {
        new_chain->size ++;
        block->previous_hash = new_chain->head->info->hash;
        new_chain->head = block;
    }
	fclose(file);
    //il faut ajouter la nouvelle chaine a Chains !!!!!!!!!!!!!
    return new_chain;
}

void save_map(char* file_name, char* nom_fichier_level,Map* map, char* player, Blockchain* Chains, Arena* Players){
	FILE* fichier_level;
    fichier_level = fopen(nom_fichier_level,"w");
	int x,y;
	x = map->nb_block_largeur_monde;
	y = map->nb_block_hauteur_monde;
	fprintf(fichier_level,"%d %d\n",x,y);
	for (int i =0;i<y;i++){
		for (int j = 0; j < x; j++)
		{
			fprintf(fichier_level,"%c",map->tab_map[x][y]);
		}
		fprintf(fichier_level,"\n");
	}
	fclose(fichier_level);
	Block *block;
	block->info->index = chains->size +1;
	block->info->author = player;
	block->info->timestamp = (int) time();
	block->info->name_house = nom_fichier_level;
	block->info->posx = x;
	block->info->posy = y;
	block->info->hash = calc_new_hash(block);
	stock(file_name, block, Chains, Players);
}
