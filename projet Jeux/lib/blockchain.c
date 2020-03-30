#include "blockchain.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYERS 10
#define HASH_SIZE		37987	/* Prime number */
#define BASE			128



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
    hash = hash_index(index) + hash_author(author) + hash_timestamp(timestamp);
    block->info->hash = hash;
}

unsigned long hash_index(int index)
{
    unsigned long hashValue = 0;
    int i = 0;
    char* date = itoa(timestamp);   //convertit un entier en char ASCII
    while ((*date) != '\0')
    {
        hashValue += hashValue % HASH_SIZE + ((*string) * (int) pow (BASE, i) )% HASH_SIZE;
        i++;
        string++;
    }
    return hashValue % HASH_SIZE;
}

unsigned long hash_author(char* author)
{
    unsigned long hashValue = 0;
    int i = 0;
    while ((*author) != '\0')
    {
        hashValue += hashValue % HASH_SIZE + ((*string) * (int) pow (BASE, i) )% HASH_SIZE;
        i++;
        string++;
    }
    return hashValue % HASH_SIZE;
}

unsigned long hash_timestamp(int timestamp)
{
    unsigned long hashValue = 0;
    int i = 0;
    char* date = itoa(timestamp);   //convertit un entier en char ASCII
    while ((*date) != '\0')
    {
        hashValue += hashValue % HASH_SIZE + ((*string) * (int) pow (BASE, i) )% HASH_SIZE;
        i++;
        string++;
    }
    return hashValue % HASH_SIZE;
}

void stock(char* file_name, Block* block, Blockchain* Chains)     //On ajoute un bloc a la chaine, a repeter pour tout les joueurs
{
    if (proof_of_work(block, Chains)) //Si le block est valide on l'ajoute sur la chaine de chaque joueur
    {
        for (int player = 0; player<length(Players); player ++)
        {
            Chains[player].size ++;
            block->previous_hash = Chains[player].head->info->hash;
            Chains[player].head = block;
        }
        save_write(file_name, block);
    }
    else
    {
        printf("Arretez de faire de la mierda on est serieux ici XD")
    }
    
}

//!!\\ reste a voir pour que les maisons ne se superposent pas
bool proof_of_work(Block* block, Blockchain* Chains)      //On teste que le nouveau bloc est bien present chez tout les joueurs
{
    if ((block->info->house_info->total_rooms < 3) || (block->info->house_info->nb_kitchen < 1) || (block->info->house_info->nb_bedroom < 1) || (block->info->house_info->nb_WC < 1)
            {
                return false; //On suppose qu'une maison doit comporter au moins une chambre, une salle de bain et une cuisine donc au moins 3 pieces
            }
    //Si la maison est valide on verifie quelle est bien coherente avec toute les chaines du reseau
    int correct, wrong;
    for (int player = 0; player<length(Players); player ++)
    {
        
        else if (Chains[player].head->info->hash == block->previous_hash && Chains[player].head->info->index == block->info->index-1)
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
        return true;
    }
    else
    {
        return false;
    }
}

//Procedures de recuperation et sauvegarde de blockchains
void save_write(char* file_name, Block* block);
{

}

Blockchain* get_save(char* file_name, Blockchain* Chains);
{
    Blockchain* new_chain;
    init_blockchain(new_chain);
    File file;
    file = fopen(file_name, "w");
    Block* block;
    while (fscanf(file, "%s %s %s %s %s %s",block->info->index, block->info->author, block->info->timestamp, block->info->message, block->info->hash, block->previous_hash) == 6)
    {
        new_chain->size ++;
        block->previous_hash = new_chain->head->info->hash;
        new_chain->head = block;
    }
    //il faut ajouter la nouvelle chaine a Chains !!!!!!!!!!!!!
    return new_chain;
}
